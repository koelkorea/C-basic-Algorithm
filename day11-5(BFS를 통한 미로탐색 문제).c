// 너비 우선 탐색(Breadth First Search)
//  : 그래프를 시작점에서 더 가까운 곳을 순회 (노드를 레벨별로 순회한다는게 정확)
//    -> 보통 큐를 사용해 구현
// 
//  # BFS를 사용하여 미로 탐색 문제해결 예시
//     : 미로를 탐색할 때, 일단 어디에 갈림길이 있는지 체크하고, 하나하나 경우의 수를 다 확인해가며 진행하는 경우
//        -> 경우를 확인하면, 일단 더 진행하지 않고 갈림길로 복귀후 다른 방향으로 다시 탐색을 반복하는 식으로 문제를 해결하는 것과 유사함
//           (1) 하나의 정점을 queue에 enqueue 추가해 둠
//           (2) queue의 정점을 dequeue(= print) 제거 후, 그 정점에 대한 방문노드체크 배열의 해당 노드항목을 방문으로 변경(pop = print 로 간주함)
//           (3) queue가 빌 때까지 이를 2번을 반복
//           (4) 현재 정점에서 방문하지 않은 방문하지 않은 인접한 정점들을 전부 queue에 순차적으로 추가
//           (5) 큐가 빌 때까지 2번 3번 4번을 반복, 더 이상 방문하지 않은 정점이 나올때까지 이를 계속 반복(whlie문 쓰면 쉽다)

// BFS와 미로 예시 구현
#include <stdio.h>
#include <stdlib.h>

// 노드 구조체
typedef struct node {

    // 도착지
    int dst;      

    // 다음 노드의 주소 저장
    struct node* next;  
}node;

// 그래프 구조체 ()
typedef struct graph {//간선을 저장하기 위한 그래프

    // 정점의 개수
    int count;

    // 정점의 개수만큼 할당 된 node(출발지)
    node* arr;  
}graph;

// queue 구조체
typedef struct queue {

    // 다음 꺼내야 하는 데이터의 주소
    int front;    

    // queue 가장 뒤의 마지막에 집어넣은 데이터의 주소
    int rear;    

    //동적할당 된 메모리의 주소 저장
    int* arr;    

    //요소 개수
    int count;    

    //큐의 최대 용량
    int capacity;  
}queue;

// 그래프 함수
void graph_initialize(graph* grp, int count);
void adddirectedEdge(graph* grp, int src, int dst);
void addUndirectedEdge(graph* grp, int src, int dst);
void graph_display(const graph* grp);
void memoryFree(graph* grp);

// 큐 함수
void queue_initialize(queue* que, int size);
int dequeue(queue* que);
int enqueue(queue* que, int value);
int queue_size(const queue* que);

// 그래프구조체 주소값을 받는 큐 메서드 
void BFS_queue(graph* grp, int source);

int main() {
    graph grp;
    graph_initialize(&grp, 9);
    addUndirectedEdge(&grp, 0, 1);
    addUndirectedEdge(&grp, 1, 2);
    addUndirectedEdge(&grp, 1, 4);
    addUndirectedEdge(&grp, 2, 5);
    addUndirectedEdge(&grp, 3, 4);
    addUndirectedEdge(&grp, 3, 6);
    addUndirectedEdge(&grp, 4, 5);
    addUndirectedEdge(&grp, 4, 7);
    addUndirectedEdge(&grp, 5, 8);
    addUndirectedEdge(&grp, 6, 7);
    graph_display(&grp);
    BFS_queue(&grp, 0); //너비(큐) 우선 탐색
    memoryFree(&grp);
    return 0;
}

//---------------------------------------[queue 함수]---------------------------------------

// queue 구조체 초기화
void queue_initialize(queue* que, int size) {// 매개변수 : 큐, 원소 수 // 구성 요소 초기화
    que->count = que->front = que->rear = 0;
    que->arr = (int*)calloc(size, sizeof(int));
    que->capacity = size;
}

// 큐에 저장된 원소 수 확인 함수
int queue_size(const queue* que) { 
    return que->count; //저장 된 개수 리턴
}

// 큐 후단에 데이터 삽입
int enqueue(queue* que, int value) { 

    if (que->count >= que->capacity) {
        return -1; //queue overflow
    }

    que->arr[que->rear] = value;
    ++(que->rear);   //rear
    ++(que->count); //요소의 개수 증가

    if (que->rear == que->capacity) {
        que->rear = 0; // 원형 큐
    }

    return 0; //enqueue 성공 시
}

// 큐 앞단의 데이터 삭제후 반환
int dequeue(queue* que) {
    int delVal;
    if (que->count <= 0) {
        return -1;
    }

    --(que->count); //요소의 개수 감수
    delVal = que->arr[que->front]; //삭제
    ++(que->front);

    if (que->front == que->capacity) {
        que->front = 0; // 원형 큐
    }

    return delVal; //dequeue에 성공 시
}

//---------------------------------------[graph 함수]---------------------------------------
void graph_initialize(graph* grp, int count) {
    grp->count = count;
    grp->arr = (node*)calloc(count, sizeof(node));
}
void adddirectedEdge(graph* grp, int src, int dst) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->dst = dst;
    newNode->next = grp->arr[src].next;
    grp->arr[src].next = newNode;
}
void addUndirectedEdge(graph* grp, int src, int dst) {
    adddirectedEdge(grp, src, dst);
    adddirectedEdge(grp, dst, src);
}
void graph_display(const graph* grp) {
    node* cur = NULL;
    if (grp == NULL) return;
    for (int i = 0; i < grp->count; i++) { //정점의 개수만큼 반복  
        cur = grp->arr[i].next;
        printf("출발지 노드 : %d ==> ", i);
        while (cur) {//다음 노드로
            printf("%d ", cur->dst);
            cur = cur->next;
        }
        printf("\n");
    }
}
void memoryFree(graph* grp) {
    int i;
    node* delNode;
    for (i = 0; i < grp->count; i++) {
        while (grp->arr[i].next) {
            delNode = grp->arr[i].next;
            grp->arr[i].next = delNode->next;
            free(delNode);
        }
    }
    free(grp->arr);
}

//-----------------------------------------------[BFS_queue]-------------------------------------------------

void BFS_queue(graph* grp, int source) { // 매개변수 : 그래프, 출발지

    int* visited = (int*)calloc(grp->count, sizeof(int)); //int visited[count];
    visited[source] = 1; // 방문지 체크
    queue que;
    queue_initialize(&que, 9); // 큐 초기화
    enqueue(&que, source); // 출발지 삽입 - > 탐색 시작

    while (queue_size(&que) != 0) { // 큐의 정점을 모두 Pop 할 때까지 반복

        int traversal = dequeue(&que);  // 방문한 정점
        printf("%d ", traversal); // 방문한 정점 출력
        node* curNode = grp->arr[traversal].next; // 방문한 정점에서 간선으로 연결한 다음 목적지 저장

        // 목적지의 존재 유무
        while (curNode) { 
            int dst = curNode->dst;

            // 방문한 적이 없으면
            if (visited[dst] == 0) { 
                enqueue(&que, dst); // 큐에 넣기
                visited[dst] = 1; // 방문지 체크
            }

            // 방문한 적이 있으면 다음 간선 주소로
            curNode = curNode->next; 
        }
    }
    printf("\n");
    free(que.arr); //큐 메모리 해제
}

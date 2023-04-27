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

// 정점(=노드) 구조체
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

// queue 구조체 (curcular queue를 가정)
typedef struct queue {

    // 다음 꺼내야 하는 데이터의 동적배열 index
    int front;

    // queue 가장 뒤의 마지막에 집어넣은 데이터의 동적배열 index (이 녀석이 capacity와 같아지면 0으로 회귀)
    int rear;

    //동적 int배열 할당된 메모리 주소 저장변수
    int* arr;

    //현재 queue에 들어간 데이터 개수
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

// queue 구조체 초기화 (매개변수 : queue 구조체 주소위치, queue의 용량)
void queue_initialize(queue* que, int size) {

    // 현재 데이터값
    // 다음에 나올 데이터가 위치한 queue구조체에 위치한 배열의 위치 주소
    // 최근에 들어간 데이터가 위치한 queue구조체에 위치한 배열의 위치 주소
    // -> 전부 0으로 초기화
    que->count = que->front = que->rear = 0;

    // 실질적으로 데이터가 들어갈 queue구조체의 멤버인 동적배열 메모리할당 후 시작주소 대입 
    que->arr = (int*)calloc(size, sizeof(int));

    // queue의 용량을 파라미터에 넣은 값으로 설정
    que->capacity = size;
}

// 큐에 저장된 원소 수 확인 함수
int queue_size(const queue* que) {
    return que->count; //저장 된 개수 리턴
}

// 큐 후단에 데이터 삽입
int enqueue(queue* que, int value) {

    // 현재 queue의 데이터가 용량을 다 썼다면? -1 반환
    if (que->count >= que->capacity) {
        return -1;
    }

    // queue에 넣은 데이터를 대입하고,
    que->arr[que->rear] = value;

    // 현재 queue 데이터의 개수 증가
    ++(que->count);  

    // 그 위치값(rear)은 배열이 동적할당 되었음으로 기존 rear index값을 증가시켜서 해결가능
    ++(que->rear);

    // (원형 queue 가정) 현재 추가한 데이터의 index가 queue 용량의 크기와 같다면?
    //  -> 현재 queue의 가장 최근에 추가된 데이터가 위치한 배열의 index를 0으로 회귀시킴
    if (que->rear == que->capacity) {
        que->rear = 0; // 원형 큐
    }

    return 0; //enqueue 성공 시
}

// 큐 앞단의 데이터 삭제후 반환
int dequeue(queue* que) {

    int delVal;
    
    // 현재 queue의 데이터가 없다면? 0을 반환
    if (que->count <= 0) {
        return -1;
    }

    // 변수에 queue에서 꺼낼 데이터를 대입
    delVal = que->arr[que->front]; 

    // 현재 queue 데이터의 개수 감수
    --(que->count); 
    
    // 다음에 꺼낼 queue의 index를 +1함
    ++(que->front);

    // (원형 queue 가정) 당장 꺼내야할 데이터의 index가 queue 용량의 크기와 같다면?
    //  -> 다음에 꺼낼 index를 0으로 회귀시킴
    if (que->front == que->capacity) {
        que->front = 0; // 
    }

    // 데이터 삭제에 성공했다면, 그 데이터 값을 반환
    return delVal;
}

//---------------------------------------[graph 함수]---------------------------------------

// 그래프 구조체 구성 멤버 초기화
void graph_initialize(graph* grp, int count) {

    // 정점 갯수 초기화
    grp->count = count;

    // node arr[count]; 개별 정점의 데이터들, 개수만큼 동적배열로 할당 후, 그 시작주소 그래프 구조체 node포인터변수 arr에 대입
    grp->arr = (node*)calloc(count, sizeof(node));
}

// 방향간선 그래프에 추가
// -> (중요!) 정확히는 진짜 정점을 추가하는게 아니라, 어떤 정점의 인접정점 리스트에 누가누가 붙어있다는 내용을 추가하기 위한 것이니 여러개 만들어도 상관없음
//     -> 그러니까 간선을 연결한다고, next_node에 진짜로 초기화 때 설정된 정점들과 정점들을 연결하는게 아니라, 
//        그 정점의 연결리스트만을 위해 만들어진 또 다른 노드 구조체들과 연결되는 것을 알아두면 대가리가 안 복잡해짐 
//        (= 그렇게 간선이 연결되면 또 다른 생성노드와 생성노드끼리 연결되서 어떤 정점과 연결된 정점들이 줄줄이 소시지 처럼 나옴)
void adddirectedEdge(graph* grp, int src, int dst) {

    // 인접정점으로 추가할 정점 구조체 변수를 동적할당하고 주소위치를 받음
    node* newNode = (node*)malloc(sizeof(node));

    // 인접정점으로 추가할 정점의 정보 입력 (연결정점의 역할로서 간선의 도착지 index 번호가 일단 들어감)
    newNode->dst = dst;

    // 새로 생성된 도착정점의 다음 정점에 원래 출발정점에 있던 다음정점의 주소 대입 (시작정점의 다음 정점이 NULL이면 그냥 NULL이 들어가면 되니 문제 없음)
    newNode->next = grp->arr[src].next;

    // 그 후 출발정점의 다음 정점의 주소에 도착점으로 설정된 정점 자신의 주소를 대입 
    grp->arr[src].next = newNode;
}

// 그래프 양방향 간선 설정 (방향 그래프를 시작, 끝 반전시켜 추가)
void addUndirectedEdge(graph* grp, int src, int dst) {
    adddirectedEdge(grp, src, dst);
    adddirectedEdge(grp, dst, src);
}

// 현재 그래프 각 정점들의 인접정점들을 모두 보여줘서, 그래프 연결현황을 전부 파악 가능하게 함
void graph_display(const graph* grp) {

    // 연결노드 추적시 현재의 노드위치를 받기 위한 변수
    node* cur = NULL;

    if (grp == NULL) return;

    // 각 정점마다 인접노드 토해내게 반복문
    for (int i = 0; i < grp->count; i++) {

        // 현재 위치 정점 = 현 정점의 다음 정점주소
        cur = grp->arr[i].next;

        printf("출발지 노드 : %d ==> ", i); // 출발지 노드 출력

        //출발정점 간선 따라가며, 연결된 정점들 다 출력하기
        while (cur) {

            printf("%d ", cur->dst);

            // 다다음 정점 주소값 저장 
            cur = cur->next; // 다음 노드로
        }

        printf("\n");
    }
}

// 해당 그래프에 할당된 모든 메모리 수거.. 
// -> 잊지 말아야 할게, 연결정점으로 만든거 하나하나가 다 할당된거니 전부 수거해야함
void memoryFree(graph* grp) {

    node* delNode;

    // 그래프에 놓인 정점배열의 index에 해당하는 개별 요소에 붙어있는 연결리스트들을 다음 노드가 없을떄까지 모조리 추적해서 지움
    for (int i = 0; i < grp->count; i++) {

        // 해당 정점에 더 이상 연결된 노드가 없을떄까지 동적할당 생성한 노드 삭제
        while (grp->arr[i].next) {

            // 삭제할 연결된 노드 주소 저장
            delNode = grp->arr[i].next;

            // 정점의 다음노드 주소를 다다음 노드 주소로 변경
            grp->arr[i].next = delNode->next;

            free(delNode);
        }
    }
    free(grp->arr); // 출발지 노드 삭제
}

//-----------------------------------------------[BFS_queue]-------------------------------------------------

// 해결법) 그래프를 queue(= 먼저 들어간걸 먼저 보는 성질 이용)를 활용한 BFS 방식으로 문제해결 
//  -> queue에 출발점 정점의 주소를 투입(점화 시작)
//     -> while 1번 : queue에서 정점을 하나씩 pop하고, 그 정점과 인접한 다른 인접정점들의 index를 queue에 넣어두고, 언급된 노드는 방문처리하기
//     -> while 2번 : 1번을 반복해서, 새로 방문한 정점들과 인접한 다른 인접정점들의 index들 중 방문 안한 정점들만 queue에 넣어두고, queue가 텅텅 빌때까지 반복하기
void BFS_queue(graph* grp, int source) { // 매개변수 : 그래프, 출발지

    // int visited[count] : boolean visited array 정점 방문 배열을 동적할당 후, 그 시작주소 반환
    int* visited = (int*)calloc(grp->count, sizeof(int));

    // queue 구조체 선언
    queue que;

    // 해당 queue 용량 9개로 초기화
    queue_initialize(&que, 9);

    // 출발지 정점의 index를 스택에 삽입 (= queue에 출발점 정점의 주소를 투입(점화 시작))
    enqueue(&que, source);

    // 출발지에 해당하는 노드 방문체크
    visited[source] = 1;

    // whlle의 목적(있는 queue의 정점 index값 순차적으로 빼내기)
    //  : queue에 들어온 정점을 모두 Pop 할 때까지 반복
    while (queue_size(&que) != 0) {

        // stack에 들어온 첫번째 요소(= 방문한 정점) Pop
        int startNode = dequeue(&que);  
        printf("%d ", startNode); 

        // 현재 노드의 위치를 받기 위한 node구조체의 포인터변수 생성 후, 방문한 정점의 인접 정점 주소
        node* curNode = grp->arr[startNode].next;

        // while의 목적(index 채울 용도로 pop한 정점index와 인접한 다른 인접정점들의 index들 중 방문처리 안된 애들만 queue에 넣어두고, 현재 방문한 노드는 방문처리하기
        //  : 현재 정점에 인접 정점 주소가 있으면 계속 반복 (= 추후 그 현재 정점과 연결된 노드들이 줄줄이 다 나올때까지 계속 반복)
        while (curNode) {

            // 현재 보고 있는 인접 정점의 index
            int dst = curNode->dst;

            // 그 인접 정점에 방문한 적이 없으면
            if (visited[dst] == 0) {

                // 현재 해당 인접정점의 queue를 스택에 넣음
                enqueue(&que, dst);

                // 현재 해당 인접정점을 방문처리
                visited[dst] = 1; 
            }

            // 그 인접 정점에 해당하는 정점에 방문한 적이 있으면, 그 인접정점의 다음 인접정점의 주소를 대입 (= 이렇게 한 정점의 연결 정점 리스트가 더 이상 없어 NULL이 나오면 종료)
            curNode = curNode->next;
        }
    }

    printf("\n");

    free(que.arr); //큐 메모리 해제
}
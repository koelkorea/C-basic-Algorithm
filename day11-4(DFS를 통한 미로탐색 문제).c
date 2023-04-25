// 깊이 우선 탐색 (DFS : Depth First Search)
//  : 그래프를 하나의 정점(보통 root)으로부터 시작하여, 차례대로 모든 정점들을 한번씩 방문
//     -> 보통 stack 자료구조를 활용해서 구현

//  # DFS를 사용하여 미로 탐색 문제해결 예시
//     : 미로를 탐색할 때처럼 한 방향으로 갈 수 있을 때까지 계속 진행하는 경우
//        -> 이를 더 이상 갈 수 없게 되면, 다시 가장 가까운 갈림길로 복귀후 다른 방향으로 다시 탐색을 반복하는 식으로 문제를 해결하는 것과 유사함

//    - 해결법 1) 
//       : 'stack 자료구조'와 boolean형식의 배열을 사용하여 해결
//          (1) 하나의 정점을 stack에 push해둠
//          (2) stack이 빌때까지 그 정점을 pop 하고, 그 정점에 대한 방문노드체크 배열의 해당 노드항목을 방문으로 변경 (pop = print 로 간주함)
//          (3) pop 된 정점에서 방문하지 않은 인접한 정점들을 다시 stack에 push
//          (4) stack이 빌 때까지 2번 3번을 반복하고, 더 이상 방문하지 않은 정점이 나올때까지 이를 계속 반복 (whlie문 쓰면 쉽다)

//    - 해결법 2)
//       : '재귀함수'와 boolean형식의 배열을 사용하여 해결 (= 재귀함수를 쓰는거 또한 stack을 쓰는 셈)
//          -> 함수는 메모리의 stack영역에서 함수프레임을 형성하며, 그 안에서 다른 함수를 호출하면 stack구조로 쌓이고 빠지고하며 LIFO방식 작동
//             (1) 하나의 정점을 출발지로 정함
//             (2) 방문 메서드 수행 후, 그 정점에 대한 방문노드체크 배열의 해당 노드항목을 방문으로 변경 (pop = print 로 간주함)
//             (3) 현재 정점에서 방문하지 않은 인접한 정점들중 하나를 잡고 이동
//             (4) 2번 3번을 반복하고 인접정점이 NULL이면 이전 갈림길로 돌아가서 계속, 더 이상 방문하지 않은 정점이 나올때까지 이를 계속 반복


// DFS와 미로 예시 구현 (STACK, 재귀 둘다 포함)
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

// stack 구조체
typedef struct stack {

    //저장하려는 위치
    int top;    

    //동적할당된 스택의 주소를 저장
    int* arr;    

    //스택의 최대 용량
    int capacity;  
}stack;

// GRAPH 함수
void stack_initialize(stack* stk, int count);
void push(stack* stk, int val);
void graph_initialize(graph* grp, int count);
void addDirectedEdge(graph* grp, int src, int dst);
void addUndirectedEdge(graph* grp, int src, int dst);
void graph_display(const graph* grp);
void memoryFree(graph* grp);

// STACK 함수
int pop(stack* stk);
int getCapacity(const stack* stk);
int getSize(const stack* stk);

// DFS 함수
void DFSReculsive(graph* grp, int index, int* visited);
void DFS(graph* grp, int source);
void DFS_stack(graph* grp, int source);

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

    // 해결법 2) 점화식으로 '재귀함수' 사용한 DFS
    DFS(&grp, 0); 
    printf("\n");

    // 해결법 1) 'stack 자료구조' 사용한 DFS
    DFS_stack(&grp, 0); 
    memoryFree(&grp);
    return 0;
}

//---------------------------------------[stack 함수]---------------------------------------

//stack 구조체 초기화 : 구성 멤버 초기화
void stack_initialize(stack* stk, int count) {
    stk->arr = (int*)malloc(sizeof(int) * count);// int arr[count]; 스택 배열 공간 동적 할당
    stk->top = 0; // 보유 개수 0으로 초기화
    stk->capacity = count; // 총 용량 count 개 설정
}

// stack 뒷단에 값 추가
void push(stack* stk, int val) {
    if (stk->top >= stk->capacity) { // 스택 용량 초과시 경고
        printf("\n\n\t\tstack overflow\n");
        return;
    }
    stk->arr[stk->top++] = val; // 스택 arr 배열에 목적지(dst) 삽입 후 top++
}


int pop(stack* stk) {
    if (stk->top <= 0) { // 공백 에러
        printf("\n\n\t\tstack underflow\n");
        return -1;
    }
    return stk->arr[--(stk->top)]; // dst를 arr배열에서 삭제 (pop)
}


int getCapacity(const stack* stk) { // 스택 총 용량 확인 함수
    return stk->capacity;
}


int getSize(const stack* stk) { // 스택 자료 개수 확인
    return stk->top;
}


//---------------------------------------[graph 함수]---------------------------------------

// 그래프 구조체 구성 멤버 초기화
void graph_initialize(graph* grp, int count) { 
    grp->count = count; // 정점 갯수 초기화
    grp->arr = (node*)calloc(count, sizeof(node)); // node arr[count]; 정점 개수 동적 할당
}

// 방향간선 그래프에 추가
void addDirectedEdge(graph* grp, int src, int dst) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->dst = dst;
    newNode->next = grp->arr[src].next;
    grp->arr[src].next = newNode;
} // 연결 리스트 노드 추가, 정점에서 목적지 설정

// 그래프 양방향 간선 설정
void addUndirectedEdge(graph* grp, int src, int dst) { 
    addDirectedEdge(grp, src, dst);
    addDirectedEdge(grp, dst, src);
}

// 그래프 내용 출력
void graph_display(const graph* grp) { // 출발 정점 -> 간선 연결 표 출력
    node* cur = NULL;
    if (grp == NULL) return;
    for (int i = 0; i < grp->count; i++) { //정점의 개수만큼 반복
        cur = grp->arr[i].next; // 1번 정점의 인접 정점 주소 대입
        printf("출발지 노드 : %d ==> ", i); // 출발지 노드 출력
        while (cur) { // 다음노드 NULL 값 확인(종점 설정)
            printf("%d ", cur->dst); // 간선의 목적지 출력
            cur = cur->next; // 다음 노드로
        }
        printf("\n");
    }
}

void memoryFree(graph* grp) {
    node* delNode;
    for (int i = 0; i < grp->count; i++) {
        while (grp->arr[i].next) { // 연결 리스트 노드 삭제
            delNode = grp->arr[i].next; // 삭제 노드 주소 저장
            grp->arr[i].next = delNode->next; // 다음 노드 주소로 변경
            free(delNode);
        }
    }
    free(grp->arr); // 출발지 노드 삭제
}

//---------------------------------------[DFS 함수]---------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
// 해결법 2) '재귀함수'와 boolean형식의 배열을 사용하여 해결 (= 재귀함수를 쓰는거 또한 stack을 쓰는 셈)

// DFS 점화식 시작
void DFS(graph* grp, int source) { // 매개변수 : 그래프, 출발지

    int* visited = (int*)calloc(grp->count, sizeof(int)); //int visited[count]; boolean visited array 정점 방문 배열
    printf("%d ", source); //출발지 정점 출력 "0"
    DFSReculsive(grp, source, visited); 
}

//DFS재귀호출 (그래프, 출발지, 방문지)
void DFSReculsive(graph* grp, int index, int* visited) {// 매개변수 : 그래프, 출발지, 방문지

    node* curNode = grp->arr[index].next; // 출발지에 연결된 간선의 목적지 노드 주소(인접 정점)
    visited[index] = 1; // 방문지 체크

    while (curNode) { // 인접 정점 유무

        int destination = curNode->dst; // 인접 정점 목적지로 설정

        if (visited[destination] == 0) { // 방문한 적이 없으면
            printf("%d ", destination); // 목적지 출력
            DFSReculsive(grp, destination, visited); // 목적지를 기준으로 다음 목적지로 재귀 함수
        }

        curNode = curNode->next; // 방문한 적이 있으면 다음 간선 주소로
    }
}
//--------------------------------------------------------------------------------------------------------------------

// 해결법 1) 그래프를 stack을 활용한 DFS 방식으로 문제해결 
void DFS_stack(graph* grp, int source) { // 매개변수 : 그래프, 출발지

    int* visited = (int*)calloc(grp->count, sizeof(int)); //int visited[count]; boolean visited array 정점 방문 배열

    stack stk;
    stack_initialize(&stk, 9); // stack 초기화 총 용량 9개
    push(&stk, source); //출발지 정점 스택에 삽입
    visited[source] = 1; // 방문지 체크

    // 스택의 정점을 모두 Pop 할 때까지 반복
    while (getSize(&stk) != 0) {

        int traversal = pop(&stk); // 방문한 정점 Pop
        printf("%d ", traversal); // 방문한 정점 출력
        node* curNode = grp->arr[traversal].next; // 방문한 정점의 인접 정점 주소 대입

        // 인접 정점 주소가 있을 때
        while (curNode) {

            // 인접 정점 목적지
            int dst = curNode->dst;

            // 방문한 적이 없으면
            if (visited[dst] == 0) {

                push(&stk, dst); // 스택에 넣기
                visited[dst] = 1; // 방문지 체크
            }

            curNode = curNode->next; // 방문한 적이 있으면 다음 간선 주소로
        }
    }
    printf("\n");
    free(stk.arr); //스택 메모리 해제
}
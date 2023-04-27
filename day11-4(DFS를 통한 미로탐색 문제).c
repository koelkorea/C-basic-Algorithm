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

// 정점(=노드) 구조체
typedef struct node {

    // 도착지
    int dst;

    // 다음 노드의 주소 저장
    struct node* next;

}node;

// 그래프 구조체
typedef struct graph {

    // 정점의 개수
    int count;

    // 정점의 개수만큼 할당한 node배열의 출발주소 (출발지)
    node* arr;

}graph;

// stack 구조체
typedef struct stack {

    // 현재 스택에 들어온 데이터의 수
    int top;

    // 동적할당된 스택의 주소를 저장
    int* arr;

    // 스택의 최대 용량
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
//----------------[재귀함수식]----------------
void DFSReculsive(graph* grp, int index, int* visited);
void DFS(graph* grp, int source);

//----------------[stack식]----------------
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

    // int arr[count] : stack의 멤버로서 실질적으로 stack에 들어온 데이터값을 저장할 배열 공간 동적 할당
    stk->arr = (int*)malloc(sizeof(int) * count);

    // stack의 보유 개수 0으로 초기화
    stk->top = 0; 

    // 총 용량 count 개 설정
    stk->capacity = count; 

}

// stack 뒷단에 값 추가
void push(stack* stk, int val) {

    // 현재 stack 용량이 가득찬 상태거나 초과시 경고
    if (stk->top >= stk->capacity) { 

        printf("\n\n\t\tstack overflow\n");

        return;
    }

    // 스택 arr 배열에 목적지(dst) 삽입 후 top++
    stk->arr[stk->top++] = val; 

}

// stack의 가장 뒷단의 값 뺴기
int pop(stack* stk) {
    if (stk->top <= 0) { // 공백 에러
        printf("\n\n\t\tstack underflow\n");
        return -1;
    }
    return stk->arr[--(stk->top)]; // dst를 arr배열에서 삭제 (pop)
}

// 스택 총 용량 확인 함수
int getCapacity(const stack* stk) {
    return stk->capacity;
}

// 현재 stack 내 데이터 개수 확인
int getSize(const stack* stk) {
    return stk->top;
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
void addDirectedEdge(graph* grp, int src, int dst) {

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
    addDirectedEdge(grp, src, dst);
    addDirectedEdge(grp, dst, src);
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

//---------------------------------------[DFS 함수]---------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
// 해결법 2) '재귀함수'와 boolean형식의 배열을 사용하여 해결 (= 재귀함수를 쓰는거 또한 stack을 쓰는 셈)

// DFS 점화식 (매개변수 : 초기화한 그래프 구조체 주소위치, 출발지)
void DFS(graph* grp, int source) {

    //=======================재귀 이전 세팅=======================

    // int visited[count] : boolean visited array 정점 방문 배열을 동적할당 후, 그 시작주소 반환
    int* visited = (int*)calloc(grp->count, sizeof(int)); 
    printf("%d ", source);

    //============================================================

    // 재귀메서드 시작!
    DFSReculsive(grp, source, visited);
}

// DFS재귀호출 (그래프, 출발지, 방문지)
void DFSReculsive(graph* grp, int index, int* visited) {

    // 현재 정점에 연결된 인접 정점의 노드 주소 (= 간선 추적)
    node* curNode = grp->arr[index].next; 

    // 현재 정점을 방문했음을 체크
    visited[index] = 1; 

    // 현재 노드(인접정점)의 인접 정점이 없을때까지 반복
    while (curNode) { 

        // 현재 노드(인접정점)의 인접 정점을 목적지로 설정
        int destination = curNode->dst; 

        // 그 인접정점에 해당하는 정점을 방문한 적이 없음이 판명되면?
        if (visited[destination] == 0) { 

            // 도착지로 설정된 정점의 index를 출력
            printf("%d ", destination);

            // 그 정점을 출발지로 설정하고 다음 목적지를 향해 재귀 ㄱㄱ
            DFSReculsive(grp, destination, visited); 
        }

        // 해당 노드에 방문한 적이 있으면, 그 노드의 다음 인접정점의 주소를 대입
        curNode = curNode->next; 
    }
}
//--------------------------------------------------------------------------------------------------------------------

// 해결법 1) 그래프를 stack(= 나중에 들어간걸 먼저 보는 성질 이용)을 활용한 DFS 방식으로 문제해결 
//  -> stack에 출발점 정점의 주소를 투입(점화 시작)
//     -> while 1번 : stack에서 정점을 하나씩 pop해서, 연결된 줄줄이 정점들을 stack에 넣어두고 언급된 노드는 방문처리하기
//     -> while 2번 : 1번을 반복해서, 새로 방문한 정점의 연결된 줄줄이 정점들중 방문 안한 정점들만 stack에 넣어두고, stack이 텅텅 빌때까지 하기
void DFS_stack(graph* grp, int source) { // 매개변수 : 그래프, 출발지

    // int visited[count] : boolean visited array 정점 방문 배열을 동적할당 후, 그 시작주소 반환
    int* visited = (int*)calloc(grp->count, sizeof(int));

    // stack 구조체 선언
    stack stk;

    // 해당 stack 용량 9개로 초기화
    stack_initialize(&stk, 9);

    //출발지 정점의 index를 스택에 삽입 (= stack에 출발점 정점의 주소를 투입(점화 시작))
    push(&stk, source); 

    // 출발지에 해당하는 노드 방문체크
    visited[source] = 1;

    // whlle의 목적(있는 stack의 정점 index값 빼내기)
    //  : stack에 들어온 정점을 모두 Pop 할 때까지 반복
    while (getSize(&stk) != 0) {

        // stack에 들어온 첫번째 요소(= 방문한 정점) Pop
        int startNode = pop(&stk); 
        printf("%d ", startNode);

        // 현재 노드의 위치를 받기 위한 node구조체의 포인터변수 생성 후, 방문한 정점의 인접 정점 주소
        node* curNode = grp->arr[startNode].next;

        // while의 목적(stack 채울 용도로 pop한 정점index와 연결된 정점 index 짜내서 방문안되었으면 stack에 넣기)
        //  : 현재 정점에 인접 정점 주소가 있으면 계속 반복 (= 추후 그 현재 정점과 연결된 노드들이 줄줄이 다 나올때까지 계속 반복)
        while (curNode) {

            // 현재 보고 있는 인접 정점의 index
            int dst = curNode->dst;

            // 그 인접 정점에 방문한 적이 없으면
            if (visited[dst] == 0) {

                // 현재 해당 인접정점의 index를 스택에 넣음
                push(&stk, dst); 

                // 현재 해당 인접정점을 방문처리
                visited[dst] = 1; 
            }

            // 그 인접 정점에 해당하는 정점에 방문한 적이 있으면, 그 인접정점의 다음 인접정점의 주소를 대입 (= 이렇게 한 정점의 연결 정점 리스트가 더 이상 없어 NULL이 나오면 종료)
            curNode = curNode->next; 
        }
    }

    printf("\n");

    free(stk.arr); //스택 메모리 해제
}
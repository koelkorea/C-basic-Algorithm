// 그래프를 표현하는 방법
//  1. 인접 행렬
//     : 2차원 배열로 그래프 표현 
//       -> (방법) x축을 시작노드, y축을 도착점으로 단방향 형식 간선을 그래프에 표기
//       -> (문제점) 정점이 10개 이상만 넘어가도 ㅈㄴ게 복잡함

// (모범예시) 인접행렬을 통한 graph 구현 - 2차원 배열을 이용한 간선 저장 (0 1 2 삼각형에 3이 2에 연결된 구조)
#include <stdio.h>
#include <stdlib.h>

// 그래프 구조체
typedef struct graph {

    // 정점의 개수
    int verCount;

    // 동적 할당 된 2차원 배열의 주소 저장할 2중 int 포인터변수 arr
    //  -> 배열도 일종의 포인터라는 점 기억 + int형식 배열의 위치를 저장해 둔 int포인터 형식 변수들로 이뤄진 배열의 위치를 저장할 수 있는 변수 타입 = 2중 int 포인터 형식의 변수 arr
    //     -> *arr = int 형식 포인터의 동적배열 시작점 (= *(arr + i)로  int 형식 포인터의 동적배열의 각 행에 접근 가능!)
    //         -> *(arr + i) = int 배열명[i][0] 메모리 위치에 접근효과
    //            -> *(arr + i) + k = int 배열명[i][k] 메모리 위치에 접근효과 
    //            -> *( *(arr + i) + k ) = int 배열명[i][k] 값
    //  -> 그런데 이녀석이 graph 구조체의 일부다? = 역참조를 더 손쉽게 할 옵션이 늘어남 (->를 가르치면 그냥 끝까지 역참조 간다는 의미)
    //     -> (결론) graph->arr[i][k] = *(graph->arr[i] + k) 의미 
    //         -> *(arr + i) = graph->arr[i]의 메모리 위치 = graph->arr[i][0]의 메모리 위치
    //            -> *(arr + i) + k = graph->arr[i] + k = graph->arr[i][k]의 메모리 위치
    //            -> (중요!) *( *(arr + i) + k ) = *(graph->arr[i] + k) = graph->arr[i][k] 성립 
    int** arr;

}graph;

// 그래프 구조체 초기화(그래프 구조체 메모리 위치주소, 원하는 정점의 갯수를 파라미터)
void graphInitialize(graph* p, int count) {

    // 정점의 갯수를 그래프 정보에 입력 
    p->verCount = count;

    // 그래프 간선에 쓰일 int포인터변수를 받는 동적배열(각 행에는 또 각기 다른 int배열에 접근 가능한 int배열 주소를 배치함) 생성을 위한 메모리 할당하고 그 시작주소인 2중 포인터변수를 리턴
    p->arr = (int**)calloc(count, sizeof(int*));

    // 2차원 배열을 표현하기 위한 int배열을 동적생성하고
    //  -> 그 주소를 2중 int 포인터변수인 p->arr의 각 행(p->arr[i] == *( (p->arr) + 1) )마다에 입력
    for (int i = 0; i < count; i++) {

        // 기존 int포인터배열의 각 행에 int배열의 메모리 시작주소값을 입력 (할당 자체는 노드의 수 * int 크기 만큼)
        p->arr[i] = (int*)calloc(count, sizeof(int)); ;
    }
}

// 방향(Directed)이 있는 그래프 간선 추가하기
//  -> 시작점 x축, 도착적 y축인 좌표에 1을 넣는식
void addDirectedEdge(graph* p, int src, int dest) {
    p->arr[src][dest] = 1;
}

// 무방향(Undirected)이 있는 그래프 간선 추가하기 (방향 그래프를 시작, 끝 반전시켜 추가)
void addUndirectedEdge(graph* p, int src, int dest) {

    addDirectedEdge(p, src, dest);
    addDirectedEdge(p, dest, src);
}

// 그래프 내용 출력
void display(graph* p) {

    printf("\n\n *** 간선 연결 현황 ***\n\n");

    for (int i = 0; i < p->verCount; i++) {  //vertex의 개수만큼 반복

        printf("출발지 %d => ", i);

        for (int j = 0; j < p->verCount; j++) {

            // (결론) graph->arr[i][k] = *(graph->arr[i] + k) 의미 (->를 가르치면 그냥 끝까지 역참조 간다는 의미)
            printf("%d ", p->arr[i][j]);
        }

        printf("\n");
    }
}

// 그래프 메모리 동적할당 해제
void memoryFree(graph* p) {

    for (int i = 0; i < p->verCount; i++) {

        free(p->arr[i]); //free(포인터); 포인터가 가리키는 메모리가 해제
        printf("%d행 동적 메모리 해제\n", i);
    }

    free(p->arr);
    printf("포인터 배열 동적 메모리 해제\n");
}

int main() {

    graph grp;
    graphInitialize(&grp, 4); //구조체, 정점의 개수

    // 의도한 간선 추가
    addUndirectedEdge(&grp, 0, 1); //구조체, 출발지, 도착지
    addUndirectedEdge(&grp, 0, 2); //구조체, 출발지, 도착지
    addUndirectedEdge(&grp, 1, 2); //구조체, 출발지, 도착지
    addUndirectedEdge(&grp, 2, 3); //구조체, 출발지, 도착지

    display(&grp);
    memoryFree(&grp);

    return 0;
}

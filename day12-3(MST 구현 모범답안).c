// 탐욕(Greedy) 알고리즘
//  : 일단 주어진 현재의 조건에서 가장 최상의 선택을 하다보면 가장 좋은 선택으로 이어진다는 방법에 착안한 최적해 알고리즘
//    ex) A에서 B로 이동하는 최단 경로 찾기
//        최단 작업 우선 스케줄링 (shortest job first scheduling)
//        분할 가능 배낭 문제 (fractional knapsack problem)
//        모든 거점을 연결하고 연결된 전체 비용을 최소화(= 최소 신장 트리)

//  # 그리디 알고리즘 요구 조건
//    1. 최적 부분 구조(optimal substructure)
//        : 부분의 최적 결과가 전체에도 그대로 적용되어야 할 것
//    2. 그리디 선택(greedy choice)
//        : 그 이전의 선택이 이후에 영향을 주지 않음

// 최소 신장 트리 (MST, Minimum Spanning Tree)
//  : 모든 정점을 연결하고 연결된 간선의 가중치 합이 최소인 트리
//    ex) 상수도관 네트워크 설계 -> 모든 사람에게 수돗물이 전달, 전체 길이는 최소가 되는 것
//        도로 네트워크 설계     -> 필요한 지점에 도로가 연결, 전체 길이는 최소화 되는 것

//  # 최소 신장 트리 (MST, Minimum Spanning Tree) 로직 (얘도 그리디 알고리즘)
//     1. 간선들의 가중치를 기준으로 오름차순으로 정렬
//     2. 가중치 낮은 간선을 선택 (BUT! 선택할 간선이 cycle이 형성되면 제외 -> how? 합집합 찾기, 서로소 집합)
//     3. 정점 - 1개의 간선 수가 될 때까지 2번 반복

// 크루스칼 알고리즘 - 최소 신장 트리 (MST, Minimum Spanning Tree) 구현 예시1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX_VERTEX 10 // 정점의 갯수

// linked list 구조체 사용 예정
typedef struct LIST {

    // 정점의 번호 저장
    int vx;
    // 정점과 연결되는 모든 정점의 데이터를 저장
    struct LIST* link; 

}List;

// 그래프 구조체
typedef struct GRAPH {

    // 현재 그래프에 연결되어 있는 정점의 갯수
    int n;
    // 헤드 정점을 기준으로 인접한 정점의 데이터를 저장
    List* adj_list[MAX_VERTEX];  

}Graph;

// 간선 구조체 : 간선과 연결된 정점 데이터와 가중치를 저장하기 위한 구조체
typedef struct EDGE {  
    int v1; // 정점 1
    int v2; // 정점 2
    int key;// 간선 (1,2) 가중치
}Edge;

// 가장 적은 가중치를 가진 간선부터 차례로 그래프 포함하기 위해서 사용
typedef struct HEAP {  

    // 그래프에 존재하는 간선의 갯수
    int n;

    // 크기가 정점 * 정점인, 간선 구조체 정적 배열 시작위치 주소
    Edge* heap[MAX_VERTEX * MAX_VERTEX];

}Heap;

int parent[MAX_VERTEX];

//------------------------------[cycle 판별, 합집합, 서로소 알고리즘]----------------------------
void union_parent_init();
int get_parent(int index);
void union_parent(int x, int y);
int find_parent(int x, int y);

//s1, s2의 합집합 여부를 검사한 뒤 그래프에 추가
int Link_Vertex_gm(int s1, int s2, int key); 

//------------------------------[MST 알고리즘]--------------------------------------------------

// 간선과 가중치를 랜덤으로 생성, 최소 힙에 저장 (n:가중치의 최대값)
void Init_Graph(Heap* h, int n);

// 생성된 간선을 힙에 저장
void Insert_Edge(int v1, int v2, int key, Heap* h); 

//====================힙 자료구조===========================

// 최소 힙 트리를 구성하기 위한 구조체를 초기화
Heap* Init_Heap(void);

// 간선을 최소힙 트리에 저장하고 heapify해서 간선데이터를 최소힙 구조로 재구성
void Input_Heap(Edge* e, Heap* h);

// 현재 최소힙 트리에서 가장 작은 가중치를 가진 간선 주소를 삭제 후 반환
Edge* Delete_Heap(Heap* h);

// 최소 힙 내부 요소 출력
void Print_Heap(Heap* h);   

// MST작동 시작 = 가중치가 최소이고 현재 그래프의 정점들과 사이클을 이루지 않는 정점부터 그래프를 구성
void Start_Kruskal(Heap* h);

int main() {

    // 간선 담을 힙 자료구조 초기화
    Heap* h = Init_Heap();

    // 그 힙 구조체에 그래프 간선 정보 생성해서 담고, 최소힙으로 heapify
    Init_Graph(h, 300);

    // 
    Print_Heap(h);

    Start_Kruskal(h);

    return 0;
}
/////////////////////union_find//////////////////////
void union_parent_init(void) { for (int i = 0; i < MAX_VERTEX; i++) parent[i] = i; } // 합집합 찾기 초기화
int get_parent(int index) { // 부모노드 확인, 작은값 가진 집합을 확인
    if (parent[index] == index)  return index;
    return get_parent(parent[index]);
}
void union_parent(int x, int y) { // 부모노드 합치기, 큰 인덱스 집합을 작은 인덱스 값으로 변경
    x = get_parent(x); //부모의 인덱스를 얻어 옴
    y = get_parent(y);
    if (x < y) parent[y] = x;
    else parent[x] = y;
}
int find_parent(int x, int y) { // 부모노드 비교 & 확인
    x = get_parent(x); //부모의 인덱스를 얻어 옴
    y = get_parent(y);
    if (x == y)  return 1;
    else return 0;
}



/////////////////////graph//////////////////////
void Init_Graph(Heap* h, int n) {//-------------간선과 가중치를 랜덤으로 생성, 최소 힙에 저장 (n:가중치의 최대값)
    srand((unsigned int)time(NULL));
    int ran_num;
    for (int i = 0; i < MAX_VERTEX; i++) { // 출발지
        for (int j = 0; j < MAX_VERTEX; j++) { // 도착지
            ran_num = (rand() % n) + 1; // 출발지 -> 도착지 까지 가중치
            printf("n = %3d  ", h->n); // 간선 번호(수량)
            printf("  Random number: %d\n", ran_num);
            Insert_Edge(i, j, ran_num, h); //    만들어진 간선을 구조체 Edge로 묶어준다.
        }
    }
}
/////////////////////Heap//////////////////////
Heap* Init_Heap(void) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->n = 0;  //    힙 트리 내에 저장된 데이터의 갯수를 초기화해준다.
    return h;
}
void Input_Heap(Edge* e, Heap* h) { // 최소 힙 추가
    int i = ++(h->n); // 마지막 힙 번호 & 힙의 원소 수
    while (i != 1 && e->key < h->heap[i / 2]->key) {// 부모노드와 비교 후 교환
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = e;
}
Edge* Delete_Heap(Heap* h) { //힙의 정점에 있는 최소 가중치 간선 정보를 반환
    Edge* re = h->heap[1]; // 가중치 가장 낮은 root 간선
    Edge* tmp = h->heap[(h->n)--]; // 마지막 힙 원소 저장 & 원소 수 1 감소
    int pr = 1, ch = 2;
    while (ch <= h->n) { // shift down 반복문
        if (ch < h->n && h->heap[ch]->key > h->heap[ch + 1]->key) ch++; // 자식 노드 왼쪽 & 오른쪽 비교
        if (tmp->key <= h->heap[ch]->key) break; // 부모 노드와 자식 노드 중 작은값 비교
        h->heap[pr] = h->heap[ch]; //부모 & 자식 교환
        pr = ch; // 자식 - > 부모 인덱스로 변경
        ch *= 2; // 자식 - > 더 아래 자식 인덱스로 변경
    }
    h->heap[pr] = tmp; // 마지막 노드 최종 위치 삽입
    return re; // 루트 노드 반환
}
void Print_Heap(Heap* h) { // 완전 이진 트리 레벨에 따라 출력 pow(2, n)
    if (h->n != 0) {
        printf("\n");
        int n = 1;
        for (int i = 1; i <= h->n; i++) {
            printf("%3d   ", h->heap[i]->key);
            if (i == (int)pow(2, n) - 1) {
                printf("\n");
                n++;
            }
        }
        printf("\n\n");
    }
}
/////////////////////Edge 생성//////////////////////
void Insert_Edge(int v1, int v2, int key, Heap* h) {//생성된 변수와 간선을 구조체로 묶고, 최소 힙 추가
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->v1 = v1;
    e->v2 = v2;
    e->key = key;
    Input_Heap(e, h);
}
/////////////////////최소 신장 트리(MST, Minimum Spanning Tree)//////////////////////
int Link_Vertex_gm(int s1, int s2, int key) {//s1, s2의 합집합 여부를 검사한 뒤 그래프에 추가
    if (!find_parent(s1, s2)) {//두 노드의 부모노드가 같이 않음 == 합집합이 아님 == 사이클을 형성하지 않음
        union_parent(s1, s2);
        printf("Success Link(key=%d): [%d] and [%d]\n\n", key, s1, s2);
        return 1;
    }
    else { // s1, s2 사이클을 형성
        printf("Fail Link(key=%d): [%d] and [%d]\n\n", key, s1, s2); return 0;
    }
}
void Start_Kruskal(Heap* h) {
    Edge* tmp;
    int end = 0;
    int n = h->n;
    union_parent_init();
    for (int i = 0; i < n; i++) {
        tmp = Delete_Heap(h); // 최소 가중치 간선 추출 (최소 힙 루트 노드)
        end += Link_Vertex_gm(tmp->v1, tmp->v2, tmp->key);
        //if (end == MAX_VERTEX - 1) break; // 노드의 수 - 1 == 간선의 수
    }
}

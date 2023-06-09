// 탐욕(Greedy) 알고리즘
//  : 일단 주어진 현재의 조건에서 가장 최상의 선택을 하다보면 가장 좋은 선택으로 이어진다는 방법에 착안한 최적해 알고리즘
//    ex) A에서 B로 이동하는 최단 경로 찾기
//        최단 작업 우선 스케줄링 (shortest job first scheduling)
//        분할 가능 배낭 문제 (fractional knapsack problem)
//        모든 거점을 연결하고 연결된 전체 길이를 최소화(최소 신장 트리)

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

// 크루스칼 알고리즘 - 최소 신장 트리 (MST, Minimum Spanning Tree) 구현 예시
#include <stdio.h>
#include <stdlib.h> // malloc(), calloc(), srand(), rand()
#include <time.h>  // time()
#include <math.h> // pow()
#define MAX_VERTEX 10

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

// 정점별 속한 세력 판별용 배열 (정점이 속한 세력 = 부모) <- 전역변수화 해서 메서드 작성 좀 편하게..
int parent[MAX_VERTEX];

//------------------------------[cycle 판별, 합집합, 서로소 알고리즘]----------------------------
void union_parent_init();
int get_parent(int index);
void union_parent(int x, int y);
int find_parent(int x, int y);

//s1, s2의 합집합 여부를 검사한 뒤 그래프에 추가
int Link_Vertex_gm(int s1, int s2, int key);

//------------------------------[MST 알고리즘]--------------------------------------------------

//====================그래프===============================

// 간선과 가중치를 랜덤으로 생성, 최소 힙에 저장 (n:가중치의 최대값)
void Init_Graph(Heap* h, int n);

// 생성된 간선을 힙에 저장
void Insert_Edge(int v1, int v2, int key, Heap* h);

// MST작동 시작 = 가중치가 최소이고 현재 그래프의 정점들과 사이클을 이루지 않는 정점부터 그래프를 구성
void Start_Kruskal(Heap* h);

//====================힙 자료구조===========================

// 최소 힙 트리를 구성하기 위한 구조체를 초기화
Heap* Init_Heap(void);

// 1개의 간선정보를 최소힙 트리에 저장하고 heapify해서 간선데이터를 최소힙 구조로 재구성
void Input_Heap(Edge* e, Heap* h);

// 현재 최소힙 트리에서 가장 작은 가중치를 가진 간선 주소를 삭제 후 반환
Edge* Delete_Heap(Heap* h);

// 최소 힙 내부 순서대로 간선내용 출력
void Print_Heap(Heap* h);

int main() {

    // 간선 담을 힙 자료구조 초기화
    Heap* h = Init_Heap();

    // 그 힙 구조체에 그래프 간선 정보 생성해서 담고, 최소힙으로 heapify
    Init_Graph(h, 300);

    // 현재 저장된 힙의 간선데이터 가중치기준 오름차순 출력
    Print_Heap(h);

    // MST사용한 크루스칼 알고리즘 시작
    Start_Kruskal(h);

    return 0;
}

//------------------------------[cycle 판별, 합집합, 서로소 알고리즘]----------------------------

// 합집합 판별용 세력집단 PK값 초기화
void union_parent_init(void) {

    for (int i = 0; i < MAX_VERTEX; i++) {
        parent[i] = i;  // 전역변수 : 정점별 소속 세력값 표현 배열
    }
}

// 해당 정점의 소속 집합(= 부모) 확인 (두 정점의 소속 집합 비교하는 find_parent의 부분집합) 
int get_parent(int index) {

    // if 해당 정점 INDEX에 해당하는 집합배열의 요소값 = 현재 정점의 INDEX값 
    //  -> 그 정점의 index를 출력하기
    if (parent[index] == index) {
        return index;
    }

    // 연결된 정점없는 고립 상태가 아님이 판명나면?
    //  -> 재귀적인 방법으로 현재 세력의 pk값을 가지는 오야 정점이 위치한 index를 찾아나서기
    return get_parent(parent[index]);
}

// 두 정점이 속한 집합들 하나로 합치기 = 두 세력 합병하기
void union_parent(int x, int y) {

    // 두 정점이 각각 속한 세력(집합)의 오야 index가 누군지 확인
    x = get_parent(x);
    y = get_parent(y);

    // 코드1) 오야의 pk값이 큰 쪽으로, 없어지는 세력 오야의 pk값 갈아치우기(단 그 조직원들 pk까지는 안 바꿨음)
    //if (x < y) {
    //	parent[y] = x;
    //}
    //else {
    //	parent[x] = y;
    //}

    // 코드2) 오야의 pk값이 큰 쪽으로, 없어지는 세력 조직원 전원의 pk값 갈아치우기 (이쪽이 좀 더 직관적임)
    if (x < y) {

        for (int i = 0; i < 10; i++) {
            if (parent[i] == y) {
                parent[i] = x;
            }
        }

    }
    else {

        for (int i = 0; i < 10; i++) {

            if (parent[i] == x) {
                parent[i] = y;
            }
        }
    }
}

// 두 정점의 같은 집합 소속여부 확인
int find_parent(int x, int y) {

    // 두 정점이 각각 속한 세력(집합)의 오야 index가 누군지 확인
    x = get_parent(x);
    y = get_parent(y);

    // 오야가 같다 = 세력이 같음
    if (x == y) {
        return 1;
    }
    else {
        return 0;
    }
}

// s1, s2의 합집합 여부를 검사한 뒤 그래프에 추가
int Link_Vertex_gm(int s1, int s2, int key) {

    // 두 노드의 부모노드가 같이 않음 == 합집합이 아님 == 사이클을 형성하지 않는 관계
    if (!find_parent(s1, s2)) {

        union_parent(s1, s2);

        printf("Success Link(key=%d): [%d] and [%d]\n\n", key, s1, s2);
        return 1;
    }
    // 두 노드의 부모노드가 같음 = s1, s2는 사이클을 형성하는 관계
    else {
        printf("Fail Link(key=%d): [%d] and [%d]\n\n", key, s1, s2);
        return 0;
    }
}

//------------------------------[MST 알고리즘]--------------------------------------------------

//====================그래프===============================

// 그래프 정보 초기화 : 간선과 가중치를 랜덤으로 생성, 그 간선 정보를 최소 힙에 저장 (n : 가중치의 최대값)
void Init_Graph(Heap* h, int n) {

    srand((unsigned int)time(NULL));

    // 랜덤생성 된 어떤 간선의 가중치를 일시적으로 담기 위한 변수
    int ran_num;

    // for문을 통해 모든 정점들이 서로에게 연결되도록 대한 간선정보를 생성 + 그 가중치를 랜덤으로.. 
    // i = 출발정점
    for (int i = 0; i < MAX_VERTEX; i++) {

        // j = 도착정점
        for (int j = 0; j < MAX_VERTEX; j++) {

            ran_num = (rand() % n) + 1;

            // 간선 번호 출력(= 현재 제시된 간선의 갯수)
            printf("n = %3d  ", h->n);

            // 해당 간선의 가중치
            printf("  Random number: %d\n", ran_num);

            // 만들어진 간선정보를 파라미터로 들어간 힙 구조체의 멤버인 구조체 Edge 배열 위치에 맞게 대입해 줌
            Insert_Edge(i, j, ran_num, h);
        }
    }
}

//생성된 간선(v1 -> v2)과 가중치 key를 저장할 간선 구조체를 생성 후, heap 구조체의 멤버인 구조체 Edge 배열 위치에 맞게 대입해 주고 -> 이 간선 구조체를 간선 구조체를 데이터로 받는 최소 힙 배열에 입력
void Insert_Edge(int v1, int v2, int key, Heap* h) {

    // 간선(Edge) 구조체를 저장하는 영역을 메모리에 동적할당하고 그 시작점 반환
    Edge* e = (Edge*)malloc(sizeof(Edge));

    // 간선의 시작, 끝, 가중치 입력
    e->v1 = v1;
    e->v2 = v2;
    e->key = key;

    Input_Heap(e, h);
}

//====================힙 자료구조===========================

// 간선정보를 받을 힙 구조 초기화
Heap* Init_Heap(void) {

    // heap 구조체 저장할 메모리 공간 동적할당 후, 그 시작 위치를 Heap 구조체 포인터변수 h에 할당
    Heap* h = (Heap*)malloc(sizeof(Heap));

    //  힙 구조에 현재 저장된 데이터의 갯수를 0으로 초기화해준다.
    h->n = 0;

    // heap구조체 시작주소를 return
    return h;
}

// 1개의 간선(Edge) 구조체 정보를 간선을 데이터로 받는 지정된 최소힙(Heap) 트리 구조체 에 저장 후 -> heapify해서 간선데이터를 최소힙 구조로 재구성
void Input_Heap(Edge* e, Heap* h) {

    // 최소힙(Heap) 트리 구조체의 마지막 힙 번호 & 힙의 원소 수를 나타내는 멤버변수 n에 +1 해줌
    int i = ++(h->n);

    // 힙 추가 연산(shiftup) : 부모노드와 비교 후 교환 (heapify)
    //  -> i가 부모노드가 없는 루트노드 index를 가르키거나, edge배열 i위치에 놓인 간선의 가중치보다 그 부모index 위치에 놓인 간선의 가중치가 낮은값이 나올때까지 값을 교환함
    while (i != 1 && e->key < h->heap[i / 2]->key) {

        // 간선(edge)를 데이터로 받고, 가중치를 기준으로 최소 힙 구조에 맞게 값을 정렬해야 하므로, 조건에 맞으면 부모index edge, 자식index edge 간 위치 변경
        h->heap[i] = h->heap[i / 2];

        // 값이 교환되었으니, 현재 배열상의 위치를 이전 부모의 위치로 격상
        i /= 2;
    }

    // 최종적으로 힙 구조에 새로 입력된 간선정보 e의 구조는 간선데이터를 받는 heap배열의 i번째에 배치
    h->heap[i] = e;
}

// 현재 최소힙 트리에서 가장 작은 가중치를 가진 간선 주소를 삭제 후 반환
Edge* Delete_Heap(Heap* h) {

    // 가중치 가장 낮은 root 간선
    Edge* re = h->heap[1];

    // 마지막 힙 원소 저장 & 원소 수 1 감소
    Edge* tmp = h->heap[(h->n)--];

    // 부모, 자식의 인덱스
    int pr = 1, ch = 2;

    // 힙 삭제 연산(shift down) : 자식노드와 비교 후 교환 (heapify)
    while (ch <= h->n) {

        // 자식 노드 왼쪽 & 오른쪽 비교 -> 오른쪽 자식이 높으면, ch의 인덱스를 1올려서 오른쪽 index대입
        if (ch < h->n && h->heap[ch]->key > h->heap[ch + 1]->key) {
            ch++;
        }

        // 부모 노드와 자식 노드 중 작은값 비교 -> 부모가 더 작으면 break
        if (tmp->key <= h->heap[ch]->key) {
            break;
        }

        // 부모 & 자식 교환
        h->heap[pr] = h->heap[ch];

        // 자식 - > 부모 인덱스로 변경
        pr = ch;

        // 자식 - > 더 아래 자식 인덱스로 변경
        ch *= 2;
    }

    // 마지막 노드 최종 위치 삽입
    h->heap[pr] = tmp;

    // 루트 노드 반환
    return re;
}

// 완전 이진트리 형식을 이루는 heap배열의 가중치 정보를 레벨(=높이)에 따라 출력 
//  -> pow(2, n)
void Print_Heap(Heap* h) {

    if (h->n != 0) {

        printf("\n");

        // 노드의 레벨 (1로 초기화)
        int n = 1;

        // 레벨1 ~ 레벨n에 해당하는 값을 레벨을 기준으로 줄바꿈하여 출력 (heap 데이터의 크기보다 현재 index인 i는 작다고 설정)
        for (int i = 1; i <= h->n; i++) {

            // index 1번 ~ n개의 가중치를 순차적으로 출력하되
            printf("%3d   ", h->heap[i]->key);

            // 현재 레벨의 마지막 index인 2^n - 1이 걸리면?
            //  -> 줄바꿈하고, n을 +1해서 다음 높이 변경시 줄바꿈이 가능하게 조치
            if (i == (int) pow(2, n) - 1) {

                printf("\n");
                n++;
            }
        }

        printf("\n\n");
    }
}

// MST작동 시작 = 가중치가 최소이고 현재 그래프의 정점들과 사이클을 이루지 않는 정점부터 그래프를 구성
//  -> 이 녀석을 실행하면, 어떤 간선이 필요하고, 쓸모 없는지 결과를 출력해줌
void Start_Kruskal(Heap* h) {

    Edge* tmp;

    int end = 0;
    int n = h->n;

    // 합집합 판별용 세력집단 PK값 초기화
    union_parent_init();

    // 가중치 기준 오름차순대로 간선데이터 추출 (최소 힙 루트 노드) -> 최소 힙정렬 실행
    for (int i = 0; i < n; i++) {

        // 최소 힙 구조에서 루트노드(= 가중치 최소값인 간선데이터)를 삭제 후 이를 반환하여, 간선(Edge) 구조체 포인터변수 tmp에 저장
        tmp = Delete_Heap(h);

        // 시작정점, 도착정점들이 현재 같은 세력인지 판별하며, 
        //  -> 같은 세력이 아니면 해당 간선에 대한 데이터를 출력한다
        end += Link_Vertex_gm(tmp->v1, tmp->v2, tmp->key);

        // 노드의 수 - 1 == 간선의 수
        if (end == MAX_VERTEX - 1) {
            break;
        }
    }
}
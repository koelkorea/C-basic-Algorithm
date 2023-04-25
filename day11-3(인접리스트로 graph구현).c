// 그래프를 표현하는 방법
//  2. 인접 리스트
//     : 각 정점에 인접한 정점들을 연결리스트로 표현
//       -> (방법) 각 정점에서 자신에게 연결된 정점들에 대해서만 linkedlist 방식을 통해 연결주소를 붙혀둠

// (모범예시) 인접리스트을 통한 graph 구현 - 연결리스트를 이용한 간선 저장 (0 1 2 삼각형에 3이 2에 연결된 구조)

//정점들이 다닐 수 있는 길 -> 간선저장
//연결리스트를 이용한 저장
#include <stdio.h>
#include <stdlib.h>

// 노드 구조체
typedef struct node {

    //정점
    int vertex;    

    //다음 노드의 주소
    struct node* next;    
}node;

// 그래프 구조체
typedef struct graph {

    //동적 할당된 노드배열의 주소 저장(출발지 노드)
    node* head;   

    //정점의 개수
    int vertexCount;    
}graph;

// 그래프 구조체 초기화(그래프 구조체 메모리 위치주소, 원하는 정점의 갯수를 파라미터)
void graphInitialize(graph* p, int count) {

    // 정점의 갯수를 그래프 정보에 입력 
    p->vertexCount = count;

    // 시작노드 정보 담을 구조체 동적 생성 = 노드들의 갯수에 해당하는 만큼, 구조체의 메모리 동적할당 후 그 주소를 그래프 구조체의 head에 대입
    p->head = (node*)calloc(count, sizeof(node));

    // 정점의 번호 동적 노드배열에 정보 입력
    for (int i = 0; i < count; i++) {

        p->head[i].vertex = i;
        p->head[i].next = NULL;
    }
}

//방향 그래프(단방향) 간선 추가
void addDirectedEdge(graph* p, int src, int dst) {

    node* newNode = (node*)malloc(sizeof(node));

    newNode->vertex = dst;
    newNode->next = NULL;

    //노드가 없을 때 
    if (p->head[src].next == NULL) { 

        p->head[src].next = newNode;
        return;
    }

    //맨 앞 추가
    newNode->next = p->head[src].next;

    p->head[src].next = newNode;
}

//무방향 그래프 (방향 그래프를 시작, 끝 반전시켜 추가)
void addUnDirectedEdge(graph* p, int src, int dst) {
    addDirectedEdge(p, src, dst);
    addDirectedEdge(p, dst, src);
}

void display(graph* p) {
    node* curNode;
    for (int i = 0; i < p->vertexCount; i++) {

        curNode = p->head[i].next;
        printf("출발지 노드 : %d => ", p->head[i].vertex);

        //다음 노드로
        while (curNode != NULL) {

            printf("%d ", curNode->vertex);

            //다음 노드 주소값 저장  
            curNode = curNode->next; 
        }
        printf("\n");
    }
}

void memoryFree(graph* p) {

    node* delNode;

    for (int i = 0; i < p->vertexCount; i++) {

        while (p->head[i].next != NULL) {
            delNode = p->head[i].next; //delNode변경
            p->head[i].next = delNode->next; //head변경
            printf("출발지 %d, 도착지 %d노드 제거\n", i, delNode->vertex);
            free(delNode); //노드 제거
        }
    }
    free(p->head);
    printf("헤드 노드 제거\n");
}

int main() {
    graph grp;
    graphInitialize(&grp, 4); //그래프, 정점의 개수
    addUnDirectedEdge(&grp, 0, 1);
    addUnDirectedEdge(&grp, 0, 2);
    addUnDirectedEdge(&grp, 1, 2);
    addUnDirectedEdge(&grp, 2, 3);
    display(&grp);
    memoryFree(&grp);
    return 0;
}

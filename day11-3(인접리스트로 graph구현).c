// 그래프를 표현하는 방법
//  2. 인접 리스트
//     : 각 정점에 인접한 정점들을 연결리스트로 표현
//       -> (방법) 각 정점에서 자신에게 연결된 정점들에 대해서만 linkedlist 방식을 통해 연결주소를 붙혀둠

// (모범예시) 인접리스트을 통한 graph 구현 - 연결리스트를 이용한 간선 저장 (0 1 2 삼각형에 3이 2에 연결된 구조)
#include <stdio.h>
#include <stdlib.h>

// 정점 구조체(= 정점도 노드므로 node구조체로 go)
typedef struct node {

    // 정점 index
    int vertex;

    // 연결된 다른 노드가 위치한 메모리 주소 (= 정점들이 다닐 수 있는 간선들 = 동적할당을 통한 노드의 배열화로 간선저장효과 낼수 있음)
    struct node* next_node;

}node;

// 그래프 구조체
typedef struct graph {

    // 동적 할당된 노드배열의 시작주소 저장(출발지 노드)
    node* node_array;

    // 해당 그래프의 정점들 총 갯수
    int vertexCount;

}graph;

// 그래프 구조체 초기화(그래프 구조체 메모리 위치주소, 원하는 정점의 갯수를 파라미터)
void graphInitialize(graph* graph, int count) {

    // 정점의 갯수를 그래프 정보에 입력 
    graph->vertexCount = count;

    // 동적 정점 배열을 구현하고자, 정점 갯수들에 해당하는 만큼 메모리 크기 동적할당 후
    //  -> 그 시작 주소를 그래프 구조체의 시작점(node_array)에 대입
    graph->node_array = (node*)calloc(count, sizeof(node));

    // 그래프 구조체의 멤버인 동적 정점배열의 각 요소에 각 정점의 index만 입력
    //  -> 각 정점의 연결된 정점정보(= 간선정보)는 추후 메서드(addDirectedEdge, addUnDirectedEdge)를 통해 입력
    for (int i = 0; i < count; i++) {

        graph->node_array[i].vertex = i;
        graph->node_array[i].next_node = NULL;
    }
}

//방향 그래프(단방향) 간선 추가
void addDirectedEdge(graph* graph, int node_index, int node_destination) {

    // 도착노드에 해당하는 노드의 순번이 없을때, 정점을 추가하기 위한 node구조체 동적할당 후, 그 node 시작 주소
    node* newNode = (node*)malloc(sizeof(node));

    newNode->vertex = node_destination;
    newNode->next_node = NULL;

    // 출발노드에 연결된 간선이 없을 때 
    if (graph->node_array[node_index].next_node == NULL) {

        // 도착점으로 설정된 정점 자신의 주소를 시작정점의 다음 정점의 주소에 대입
        graph->node_array[node_index].next_node = newNode;

    }
    // 출발노드에 연결된 간선이 있을 때?
    //  -> 출발노드와 기존 연결노드의 사이에 자기가 끼어들어 출발노드와 자신의 연결정보를 변경(최종적으로는 연결된 놈들끼리는 순환구조.. )
    else {

        // 출발정점에 있던 다음정점의 주소를 새로 생성된 도착정점의 다음 정점으로 대입
        newNode->next_node = graph->node_array[node_index].next_node;

        // 그 후 도착점으로 설정된 정점 자신의 주소를 시작정점의 다음 정점의 주소에 대입
        graph->node_array[node_index].next_node = newNode;

    }
}

//무방향 그래프 (방향 그래프를 시작, 끝 반전시켜 추가)
void addUnDirectedEdge(graph* graph, int node_index, int node_destination) {
    addDirectedEdge(graph, node_index, node_destination);
    addDirectedEdge(graph, node_destination, node_index);
}

void display(graph* graph) {

    // 현재 위치 정점
    node* curNode;

    for (int i = 0; i < graph->vertexCount; i++) {

        curNode = graph->node_array[i].next_node;

        printf("출발지 노드 : %d => ", graph->node_array[i].vertex);

        //다음 노드로
        while (curNode != NULL) {

            printf("%d ", curNode->vertex);

            //다음 노드 주소값 저장  
            curNode = curNode->next_node;
        }
        printf("\n");
    }
}

void memoryFree(graph* p) {

    node* delNode;

    for (int i = 0; i < p->vertexCount; i++) {

        while (p->node_array[i].next_node != NULL) {

            delNode = p->node_array[i].next_node; //delNode변경
            p->node_array[i].next_node = delNode->next_node; //start_point변경

            printf("출발지 %d, 도착지 %d노드 제거\n", i, delNode->vertex);

            free(delNode); //노드 제거
        }
    }
    free(p->node_array);
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
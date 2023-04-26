// 그래프를 표현하는 방법
//  2. 인접 리스트
//     : 각 정점에 인접한 정점들을 연결리스트로 표현
//       -> (방법) 각 정점에서 자신에게 연결된 정점들에 대해서만 linkedlist 방식을 통해 생성된 정점을 만들어 연결주소를 붙혀두고, 그 연결에 다른 정점과 연결된게 확인되면, 마찬가지로 또 정점을 생성해서 붙이는 방식
//           -> 그렇게 모든 정점을 대상으로 자신에게서 연결된 생성노드 정보를 출력해보면 줄줄이 소시지처럼 나옴

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
    //  -> 각 정점의 연결된 정점정보(= 간선정보)는 추후 메서드(addDirectedEdge, addUnDirectedEdge)를 통해 인접정보 표기만을 위해 생성된 노드들과 연결됨
    for (int i = 0; i < count; i++) {

        graph->node_array[i].vertex = i;
        graph->node_array[i].next_node = NULL;
    }
}

//방향 그래프(단방향) 간선 추가 
// -> (중요!) 정확히는 진짜 정점을 추가하는게 아니라, 어떤 정점의 인접정점 리스트에 누가누가 붙어있다는 내용을 추가하기 위한 것이니 여러개 만들어도 상관없음
//     -> 그러니까 간선을 연결한다고, next_node에 진짜로 초기화 때 설정된 정점들과 정점들을 연결하는게 아니라, 
//        그 정점의 연결리스트만을 위해 만들어진 또 다른 노드 구조체들과 연결되는 것을 알아두면 대가리가 안 복잡해짐 
//        (= 그렇게 간선이 연결되면 또 다른 생성노드와 생성노드끼리 연결되서 어떤 정점과 연결된 정점들이 줄줄이 소시지 처럼 나옴)
void addDirectedEdge(graph* graph, int node_index, int node_destination) {

    // 인접정점으로 추가할 정점 구조체 변수를 동적할당하고 주소위치를 받음
    node* newNode = (node*)malloc(sizeof(node));

    // 인접정점으로 추가할 정점의 정보 입력 (연결정점의 역할로서 간선의 도착지 index 번호가 일단 들어감)
    newNode->vertex = node_destination;
    newNode->next_node = NULL;

    //----------------------------------------------------------------------------------------------
    // 
    //// 출발노드에 연결된 간선이 없음이 탐지?
    //if (graph->node_array[node_index].next_node == NULL) {

    //    // 출발정점의 다음 정점의 주소에 도착점으로 설정된 정점 자신의 주소를 대입 
    //    graph->node_array[node_index].next_node = newNode;

    //}
    //// 출발정점으로 지정된 정점index에 기록된 인접정점 있음이 탐지? (끼워넣기 시작함)
    ////  -> 출발정점으로 지정된 정점index에 기록된 인접정점 주소에 새로 만들어진 인접정점 자신의 주소를 연결 + 새로 만들어진 인접정점 자신의 인접정점에는 기존 출발정점으로 지정된 정점index에 기록된 인접정점을 대입
    ////     -> 출발정점 => 기존 인접정점  to 출발정점 => 새 인접정점 => 기존 인접정점
    //else {

    //    // 새로 생성된 도착정점의 다음 정점에 원래 출발정점에 있던 다음정점의 주소 대입
    //    newNode->next_node = graph->node_array[node_index].next_node;

    //    // 그 후 출발정점의 다음 정점의 주소에 도착점으로 설정된 정점 자신의 주소를 대입 
    //    graph->node_array[node_index].next_node = newNode;

    //}
    // 
    //----------------------------------------------------------------------------------------------
    // -> (중요) 사실 조건문 없어도 되는게, 간선의 시작정점의 기존 다음 정점이 없어도 로직 진행에는 전혀 문제가 없음

    // 새로 생성된 도착정점의 다음 정점에 원래 출발정점에 있던 다음정점의 주소 대입 (시작정점의 다음 정점이 NULL이면 그냥 NULL이 들어가면 되니 문제 없음)
    newNode->next_node = graph->node_array[node_index].next_node;

    // 그 후 출발정점의 다음 정점의 주소에 도착점으로 설정된 정점 자신의 주소를 대입 
    graph->node_array[node_index].next_node = newNode;

}

//무방향 그래프 (방향 그래프를 시작, 끝 반전시켜 추가)
void addUnDirectedEdge(graph* graph, int node_index, int node_destination) {
    addDirectedEdge(graph, node_index, node_destination);
    addDirectedEdge(graph, node_destination, node_index);
}

// 현재 그래프 각 정점들의 인접정점들을 모두 보여줘서, 그래프 연결현황을 전부 파악 가능하게 함
void display(graph* graph) {

    // 현재 위치 정점
    node* curNode;

    // 각 정점마다 인접노드 토해내게 반복문
    for (int i = 0; i < graph->vertexCount; i++) {

        // 현재 위치 정점 = 현 정점의 다음 정점주소
        curNode = graph->node_array[i].next_node;

        printf("출발지 노드 : %d => ", graph->node_array[i].vertex);

        //출발정점 간선 따라가며, 연결된 정점들 다 출력하기
        while (curNode != NULL) {

            printf("%d ", curNode->vertex);

            // 다다음 정점 주소값 저장  
            curNode = curNode->next_node;
        }
        printf("\n");
    }
}

// 해당 그래프에 할당된 모든 메모리 수거.. 
// -> 잊지 말아야 할게, 연결정점으로 만든거 하나하나가 다 할당된거니 전부 수거해야함
void memoryFree(graph* p) {

    node* delNode;

    // 그래프에 놓인 정점배열의 index에 해당하는 개별 요소에 붙어있는 연결리스트들을 다음 노드가 없을떄까지 모조리 추적해서 지움
    for (int i = 0; i < p->vertexCount; i++) {

        while (p->node_array[i].next_node != NULL) {

            delNode = p->node_array[i].next_node; //delNode변경
            p->node_array[i].next_node = delNode->next_node; //start_point변경

            printf("출발지 %d, 도착지 %d노드 제거\n", i, delNode->vertex);

            free(delNode); //노드 제거
        }
    }

    // 마지막으로 그래프 구조체를 위해 할당된 메모리까지 전부 수거하면 끝

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
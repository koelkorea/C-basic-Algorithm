// �׷����� ǥ���ϴ� ���
//  2. ���� ����Ʈ
//     : �� ������ ������ �������� ���Ḯ��Ʈ�� ǥ��
//       -> (���) �� �������� �ڽſ��� ����� �����鿡 ���ؼ��� linkedlist ����� ���� �����ּҸ� ������

// (�������) ��������Ʈ�� ���� graph ���� - ���Ḯ��Ʈ�� �̿��� ���� ���� (0 1 2 �ﰢ���� 3�� 2�� ����� ����)
#include <stdio.h>
#include <stdlib.h>

// ���� ����ü(= ������ ���Ƿ� node����ü�� go)
typedef struct node {

    // ���� index
    int vertex;

    // ����� �ٸ� ��尡 ��ġ�� �޸� �ּ� (= �������� �ٴ� �� �ִ� ������ = �����Ҵ��� ���� ����� �迭ȭ�� ��������ȿ�� ���� ����)
    struct node* next_node;

}node;

// �׷��� ����ü
typedef struct graph {

    // ���� �Ҵ�� ���迭�� �����ּ� ����(����� ���)
    node* node_array;

    // �ش� �׷����� ������ �� ����
    int vertexCount;

}graph;

// �׷��� ����ü �ʱ�ȭ(�׷��� ����ü �޸� ��ġ�ּ�, ���ϴ� ������ ������ �Ķ����)
void graphInitialize(graph* graph, int count) {

    // ������ ������ �׷��� ������ �Է� 
    graph->vertexCount = count;

    // ���� ���� �迭�� �����ϰ���, ���� �����鿡 �ش��ϴ� ��ŭ �޸� ũ�� �����Ҵ� ��
    //  -> �� ���� �ּҸ� �׷��� ����ü�� ������(node_array)�� ����
    graph->node_array = (node*)calloc(count, sizeof(node));

    // �׷��� ����ü�� ����� ���� �����迭�� �� ��ҿ� �� ������ index�� �Է�
    //  -> �� ������ ����� ��������(= ��������)�� ���� �޼���(addDirectedEdge, addUnDirectedEdge)�� ���� �Է�
    for (int i = 0; i < count; i++) {

        graph->node_array[i].vertex = i;
        graph->node_array[i].next_node = NULL;
    }
}

//���� �׷���(�ܹ���) ���� �߰�
void addDirectedEdge(graph* graph, int node_index, int node_destination) {

    // ������忡 �ش��ϴ� ����� ������ ������, ������ �߰��ϱ� ���� node����ü �����Ҵ� ��, �� node ���� �ּ�
    node* newNode = (node*)malloc(sizeof(node));

    newNode->vertex = node_destination;
    newNode->next_node = NULL;

    // ��߳�忡 ����� ������ ���� �� 
    if (graph->node_array[node_index].next_node == NULL) {

        // ���������� ������ ���� �ڽ��� �ּҸ� ���������� ���� ������ �ּҿ� ����
        graph->node_array[node_index].next_node = newNode;

    }
    // ��߳�忡 ����� ������ ���� ��?
    //  -> ��߳��� ���� �������� ���̿� �ڱⰡ ������ ��߳��� �ڽ��� ���������� ����(���������δ� ����� ��鳢���� ��ȯ����.. )
    else {

        // ��������� �ִ� ���������� �ּҸ� ���� ������ ���������� ���� �������� ����
        newNode->next_node = graph->node_array[node_index].next_node;

        // �� �� ���������� ������ ���� �ڽ��� �ּҸ� ���������� ���� ������ �ּҿ� ����
        graph->node_array[node_index].next_node = newNode;

    }
}

//������ �׷��� (���� �׷����� ����, �� �������� �߰�)
void addUnDirectedEdge(graph* graph, int node_index, int node_destination) {
    addDirectedEdge(graph, node_index, node_destination);
    addDirectedEdge(graph, node_destination, node_index);
}

void display(graph* graph) {

    // ���� ��ġ ����
    node* curNode;

    for (int i = 0; i < graph->vertexCount; i++) {

        curNode = graph->node_array[i].next_node;

        printf("����� ��� : %d => ", graph->node_array[i].vertex);

        //���� ����
        while (curNode != NULL) {

            printf("%d ", curNode->vertex);

            //���� ��� �ּҰ� ����  
            curNode = curNode->next_node;
        }
        printf("\n");
    }
}

void memoryFree(graph* p) {

    node* delNode;

    for (int i = 0; i < p->vertexCount; i++) {

        while (p->node_array[i].next_node != NULL) {

            delNode = p->node_array[i].next_node; //delNode����
            p->node_array[i].next_node = delNode->next_node; //start_point����

            printf("����� %d, ������ %d��� ����\n", i, delNode->vertex);

            free(delNode); //��� ����
        }
    }
    free(p->node_array);
    printf("��� ��� ����\n");
}

int main() {

    graph grp;
    graphInitialize(&grp, 4); //�׷���, ������ ����

    addUnDirectedEdge(&grp, 0, 1);
    addUnDirectedEdge(&grp, 0, 2);
    addUnDirectedEdge(&grp, 1, 2);
    addUnDirectedEdge(&grp, 2, 3);

    display(&grp);
    memoryFree(&grp);

    return 0;
}
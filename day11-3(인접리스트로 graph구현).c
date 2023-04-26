// �׷����� ǥ���ϴ� ���
//  2. ���� ����Ʈ
//     : �� ������ ������ �������� ���Ḯ��Ʈ�� ǥ��
//       -> (���) �� �������� �ڽſ��� ����� �����鿡 ���ؼ��� linkedlist ����� ���� ������ ������ ����� �����ּҸ� �����ΰ�, �� ���ῡ �ٸ� ������ ����Ȱ� Ȯ�εǸ�, ���������� �� ������ �����ؼ� ���̴� ���
//           -> �׷��� ��� ������ ������� �ڽſ��Լ� ����� ������� ������ ����غ��� ������ �ҽ���ó�� ����

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
    //  -> �� ������ ����� ��������(= ��������)�� ���� �޼���(addDirectedEdge, addUnDirectedEdge)�� ���� �������� ǥ�⸸�� ���� ������ ����� �����
    for (int i = 0; i < count; i++) {

        graph->node_array[i].vertex = i;
        graph->node_array[i].next_node = NULL;
    }
}

//���� �׷���(�ܹ���) ���� �߰� 
// -> (�߿�!) ��Ȯ���� ��¥ ������ �߰��ϴ°� �ƴ϶�, � ������ �������� ����Ʈ�� �������� �پ��ִٴ� ������ �߰��ϱ� ���� ���̴� ������ ���� �������
//     -> �׷��ϱ� ������ �����Ѵٰ�, next_node�� ��¥�� �ʱ�ȭ �� ������ ������� �������� �����ϴ°� �ƴ϶�, 
//        �� ������ ���Ḯ��Ʈ���� ���� ������� �� �ٸ� ��� ����ü��� ����Ǵ� ���� �˾Ƶθ� �밡���� �� �������� 
//        (= �׷��� ������ ����Ǹ� �� �ٸ� �������� ������峢�� ����Ǽ� � ������ ����� �������� ������ �ҽ��� ó�� ����)
void addDirectedEdge(graph* graph, int node_index, int node_destination) {

    // ������������ �߰��� ���� ����ü ������ �����Ҵ��ϰ� �ּ���ġ�� ����
    node* newNode = (node*)malloc(sizeof(node));

    // ������������ �߰��� ������ ���� �Է� (���������� ���ҷμ� ������ ������ index ��ȣ�� �ϴ� ��)
    newNode->vertex = node_destination;
    newNode->next_node = NULL;

    //----------------------------------------------------------------------------------------------
    // 
    //// ��߳�忡 ����� ������ ������ Ž��?
    //if (graph->node_array[node_index].next_node == NULL) {

    //    // ��������� ���� ������ �ּҿ� ���������� ������ ���� �ڽ��� �ּҸ� ���� 
    //    graph->node_array[node_index].next_node = newNode;

    //}
    //// ����������� ������ ����index�� ��ϵ� �������� ������ Ž��? (�����ֱ� ������)
    ////  -> ����������� ������ ����index�� ��ϵ� �������� �ּҿ� ���� ������� �������� �ڽ��� �ּҸ� ���� + ���� ������� �������� �ڽ��� ������������ ���� ����������� ������ ����index�� ��ϵ� ���������� ����
    ////     -> ������� => ���� ��������  to ������� => �� �������� => ���� ��������
    //else {

    //    // ���� ������ ���������� ���� ������ ���� ��������� �ִ� ���������� �ּ� ����
    //    newNode->next_node = graph->node_array[node_index].next_node;

    //    // �� �� ��������� ���� ������ �ּҿ� ���������� ������ ���� �ڽ��� �ּҸ� ���� 
    //    graph->node_array[node_index].next_node = newNode;

    //}
    // 
    //----------------------------------------------------------------------------------------------
    // -> (�߿�) ��� ���ǹ� ��� �Ǵ°�, ������ ���������� ���� ���� ������ ��� ���� ���࿡�� ���� ������ ����

    // ���� ������ ���������� ���� ������ ���� ��������� �ִ� ���������� �ּ� ���� (���������� ���� ������ NULL�̸� �׳� NULL�� ���� �Ǵ� ���� ����)
    newNode->next_node = graph->node_array[node_index].next_node;

    // �� �� ��������� ���� ������ �ּҿ� ���������� ������ ���� �ڽ��� �ּҸ� ���� 
    graph->node_array[node_index].next_node = newNode;

}

//������ �׷��� (���� �׷����� ����, �� �������� �߰�)
void addUnDirectedEdge(graph* graph, int node_index, int node_destination) {
    addDirectedEdge(graph, node_index, node_destination);
    addDirectedEdge(graph, node_destination, node_index);
}

// ���� �׷��� �� �������� ������������ ��� �����༭, �׷��� ������Ȳ�� ���� �ľ� �����ϰ� ��
void display(graph* graph) {

    // ���� ��ġ ����
    node* curNode;

    // �� �������� ������� ���س��� �ݺ���
    for (int i = 0; i < graph->vertexCount; i++) {

        // ���� ��ġ ���� = �� ������ ���� �����ּ�
        curNode = graph->node_array[i].next_node;

        printf("����� ��� : %d => ", graph->node_array[i].vertex);

        //������� ���� ���󰡸�, ����� ������ �� ����ϱ�
        while (curNode != NULL) {

            printf("%d ", curNode->vertex);

            // �ٴ��� ���� �ּҰ� ����  
            curNode = curNode->next_node;
        }
        printf("\n");
    }
}

// �ش� �׷����� �Ҵ�� ��� �޸� ����.. 
// -> ���� ���ƾ� �Ұ�, ������������ ����� �ϳ��ϳ��� �� �Ҵ�ȰŴ� ���� �����ؾ���
void memoryFree(graph* p) {

    node* delNode;

    // �׷����� ���� �����迭�� index�� �ش��ϴ� ���� ��ҿ� �پ��ִ� ���Ḯ��Ʈ���� ���� ��尡 ���������� ������ �����ؼ� ����
    for (int i = 0; i < p->vertexCount; i++) {

        while (p->node_array[i].next_node != NULL) {

            delNode = p->node_array[i].next_node; //delNode����
            p->node_array[i].next_node = delNode->next_node; //start_point����

            printf("����� %d, ������ %d��� ����\n", i, delNode->vertex);

            free(delNode); //��� ����
        }
    }

    // ���������� �׷��� ����ü�� ���� �Ҵ�� �޸𸮱��� ���� �����ϸ� ��

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
// �׷����� ǥ���ϴ� ���
//  2. ���� ����Ʈ
//     : �� ������ ������ �������� ���Ḯ��Ʈ�� ǥ��
//       -> (���) �� �������� �ڽſ��� ����� �����鿡 ���ؼ��� linkedlist ����� ���� �����ּҸ� ������

// (�������) ��������Ʈ�� ���� graph ���� - ���Ḯ��Ʈ�� �̿��� ���� ���� (0 1 2 �ﰢ���� 3�� 2�� ����� ����)

//�������� �ٴ� �� �ִ� �� -> ��������
//���Ḯ��Ʈ�� �̿��� ����
#include <stdio.h>
#include <stdlib.h>

// ��� ����ü
typedef struct node {

    //����
    int vertex;    

    //���� ����� �ּ�
    struct node* next;    
}node;

// �׷��� ����ü
typedef struct graph {

    //���� �Ҵ�� ���迭�� �ּ� ����(����� ���)
    node* head;   

    //������ ����
    int vertexCount;    
}graph;

// �׷��� ����ü �ʱ�ȭ(�׷��� ����ü �޸� ��ġ�ּ�, ���ϴ� ������ ������ �Ķ����)
void graphInitialize(graph* p, int count) {

    // ������ ������ �׷��� ������ �Է� 
    p->vertexCount = count;

    // ���۳�� ���� ���� ����ü ���� ���� = ������ ������ �ش��ϴ� ��ŭ, ����ü�� �޸� �����Ҵ� �� �� �ּҸ� �׷��� ����ü�� head�� ����
    p->head = (node*)calloc(count, sizeof(node));

    // ������ ��ȣ ���� ���迭�� ���� �Է�
    for (int i = 0; i < count; i++) {

        p->head[i].vertex = i;
        p->head[i].next = NULL;
    }
}

//���� �׷���(�ܹ���) ���� �߰�
void addDirectedEdge(graph* p, int src, int dst) {

    node* newNode = (node*)malloc(sizeof(node));

    newNode->vertex = dst;
    newNode->next = NULL;

    //��尡 ���� �� 
    if (p->head[src].next == NULL) { 

        p->head[src].next = newNode;
        return;
    }

    //�� �� �߰�
    newNode->next = p->head[src].next;

    p->head[src].next = newNode;
}

//������ �׷��� (���� �׷����� ����, �� �������� �߰�)
void addUnDirectedEdge(graph* p, int src, int dst) {
    addDirectedEdge(p, src, dst);
    addDirectedEdge(p, dst, src);
}

void display(graph* p) {
    node* curNode;
    for (int i = 0; i < p->vertexCount; i++) {

        curNode = p->head[i].next;
        printf("����� ��� : %d => ", p->head[i].vertex);

        //���� ����
        while (curNode != NULL) {

            printf("%d ", curNode->vertex);

            //���� ��� �ּҰ� ����  
            curNode = curNode->next; 
        }
        printf("\n");
    }
}

void memoryFree(graph* p) {

    node* delNode;

    for (int i = 0; i < p->vertexCount; i++) {

        while (p->head[i].next != NULL) {
            delNode = p->head[i].next; //delNode����
            p->head[i].next = delNode->next; //head����
            printf("����� %d, ������ %d��� ����\n", i, delNode->vertex);
            free(delNode); //��� ����
        }
    }
    free(p->head);
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

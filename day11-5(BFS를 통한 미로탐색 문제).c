// �ʺ� �켱 Ž��(Breadth First Search)
//  : �׷����� ���������� �� ����� ���� ��ȸ (��带 �������� ��ȸ�Ѵٴ°� ��Ȯ)
//    -> ���� ť�� ����� ����
// 
//  # BFS�� ����Ͽ� �̷� Ž�� �����ذ� ����
//     : �̷θ� Ž���� ��, �ϴ� ��� �������� �ִ��� üũ�ϰ�, �ϳ��ϳ� ����� ���� �� Ȯ���ذ��� �����ϴ� ���
//        -> ��츦 Ȯ���ϸ�, �ϴ� �� �������� �ʰ� ������� ������ �ٸ� �������� �ٽ� Ž���� �ݺ��ϴ� ������ ������ �ذ��ϴ� �Ͱ� ������
//           (1) �ϳ��� ������ queue�� enqueue �߰��� ��
//           (2) queue�� ������ dequeue(= print) ���� ��, �� ������ ���� �湮���üũ �迭�� �ش� ����׸��� �湮���� ����(pop = print �� ������)
//           (3) queue�� �� ������ �̸� 2���� �ݺ�
//           (4) ���� �������� �湮���� ���� �湮���� ���� ������ �������� ���� queue�� ���������� �߰�
//           (5) ť�� �� ������ 2�� 3�� 4���� �ݺ�, �� �̻� �湮���� ���� ������ ���ö����� �̸� ��� �ݺ�(whlie�� ���� ����)

// BFS�� �̷� ���� ����
#include <stdio.h>
#include <stdlib.h>

// ��� ����ü
typedef struct node {

    // ������
    int dst;      

    // ���� ����� �ּ� ����
    struct node* next;  
}node;

// �׷��� ����ü ()
typedef struct graph {//������ �����ϱ� ���� �׷���

    // ������ ����
    int count;

    // ������ ������ŭ �Ҵ� �� node(�����)
    node* arr;  
}graph;

// queue ����ü
typedef struct queue {

    // ���� ������ �ϴ� �������� �ּ�
    int front;    

    // queue ���� ���� �������� ������� �������� �ּ�
    int rear;    

    //�����Ҵ� �� �޸��� �ּ� ����
    int* arr;    

    //��� ����
    int count;    

    //ť�� �ִ� �뷮
    int capacity;  
}queue;

// �׷��� �Լ�
void graph_initialize(graph* grp, int count);
void adddirectedEdge(graph* grp, int src, int dst);
void addUndirectedEdge(graph* grp, int src, int dst);
void graph_display(const graph* grp);
void memoryFree(graph* grp);

// ť �Լ�
void queue_initialize(queue* que, int size);
int dequeue(queue* que);
int enqueue(queue* que, int value);
int queue_size(const queue* que);

// �׷�������ü �ּҰ��� �޴� ť �޼��� 
void BFS_queue(graph* grp, int source);

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
    BFS_queue(&grp, 0); //�ʺ�(ť) �켱 Ž��
    memoryFree(&grp);
    return 0;
}

//---------------------------------------[queue �Լ�]---------------------------------------

// queue ����ü �ʱ�ȭ
void queue_initialize(queue* que, int size) {// �Ű����� : ť, ���� �� // ���� ��� �ʱ�ȭ
    que->count = que->front = que->rear = 0;
    que->arr = (int*)calloc(size, sizeof(int));
    que->capacity = size;
}

// ť�� ����� ���� �� Ȯ�� �Լ�
int queue_size(const queue* que) { 
    return que->count; //���� �� ���� ����
}

// ť �Ĵܿ� ������ ����
int enqueue(queue* que, int value) { 

    if (que->count >= que->capacity) {
        return -1; //queue overflow
    }

    que->arr[que->rear] = value;
    ++(que->rear);   //rear
    ++(que->count); //����� ���� ����

    if (que->rear == que->capacity) {
        que->rear = 0; // ���� ť
    }

    return 0; //enqueue ���� ��
}

// ť �մ��� ������ ������ ��ȯ
int dequeue(queue* que) {
    int delVal;
    if (que->count <= 0) {
        return -1;
    }

    --(que->count); //����� ���� ����
    delVal = que->arr[que->front]; //����
    ++(que->front);

    if (que->front == que->capacity) {
        que->front = 0; // ���� ť
    }

    return delVal; //dequeue�� ���� ��
}

//---------------------------------------[graph �Լ�]---------------------------------------
void graph_initialize(graph* grp, int count) {
    grp->count = count;
    grp->arr = (node*)calloc(count, sizeof(node));
}
void adddirectedEdge(graph* grp, int src, int dst) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->dst = dst;
    newNode->next = grp->arr[src].next;
    grp->arr[src].next = newNode;
}
void addUndirectedEdge(graph* grp, int src, int dst) {
    adddirectedEdge(grp, src, dst);
    adddirectedEdge(grp, dst, src);
}
void graph_display(const graph* grp) {
    node* cur = NULL;
    if (grp == NULL) return;
    for (int i = 0; i < grp->count; i++) { //������ ������ŭ �ݺ�  
        cur = grp->arr[i].next;
        printf("����� ��� : %d ==> ", i);
        while (cur) {//���� ����
            printf("%d ", cur->dst);
            cur = cur->next;
        }
        printf("\n");
    }
}
void memoryFree(graph* grp) {
    int i;
    node* delNode;
    for (i = 0; i < grp->count; i++) {
        while (grp->arr[i].next) {
            delNode = grp->arr[i].next;
            grp->arr[i].next = delNode->next;
            free(delNode);
        }
    }
    free(grp->arr);
}

//-----------------------------------------------[BFS_queue]-------------------------------------------------

void BFS_queue(graph* grp, int source) { // �Ű����� : �׷���, �����

    int* visited = (int*)calloc(grp->count, sizeof(int)); //int visited[count];
    visited[source] = 1; // �湮�� üũ
    queue que;
    queue_initialize(&que, 9); // ť �ʱ�ȭ
    enqueue(&que, source); // ����� ���� - > Ž�� ����

    while (queue_size(&que) != 0) { // ť�� ������ ��� Pop �� ������ �ݺ�

        int traversal = dequeue(&que);  // �湮�� ����
        printf("%d ", traversal); // �湮�� ���� ���
        node* curNode = grp->arr[traversal].next; // �湮�� �������� �������� ������ ���� ������ ����

        // �������� ���� ����
        while (curNode) { 
            int dst = curNode->dst;

            // �湮�� ���� ������
            if (visited[dst] == 0) { 
                enqueue(&que, dst); // ť�� �ֱ�
                visited[dst] = 1; // �湮�� üũ
            }

            // �湮�� ���� ������ ���� ���� �ּҷ�
            curNode = curNode->next; 
        }
    }
    printf("\n");
    free(que.arr); //ť �޸� ����
}

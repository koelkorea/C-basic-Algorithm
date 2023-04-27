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

// ����(=���) ����ü
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

// queue ����ü (curcular queue�� ����)
typedef struct queue {

    // ���� ������ �ϴ� �������� �����迭 index
    int front;

    // queue ���� ���� �������� ������� �������� �����迭 index (�� �༮�� capacity�� �������� 0���� ȸ��)
    int rear;

    //���� int�迭 �Ҵ�� �޸� �ּ� ���庯��
    int* arr;

    //���� queue�� �� ������ ����
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

// queue ����ü �ʱ�ȭ (�Ű����� : queue ����ü �ּ���ġ, queue�� �뷮)
void queue_initialize(queue* que, int size) {

    // ���� �����Ͱ�
    // ������ ���� �����Ͱ� ��ġ�� queue����ü�� ��ġ�� �迭�� ��ġ �ּ�
    // �ֱٿ� �� �����Ͱ� ��ġ�� queue����ü�� ��ġ�� �迭�� ��ġ �ּ�
    // -> ���� 0���� �ʱ�ȭ
    que->count = que->front = que->rear = 0;

    // ���������� �����Ͱ� �� queue����ü�� ����� �����迭 �޸��Ҵ� �� �����ּ� ���� 
    que->arr = (int*)calloc(size, sizeof(int));

    // queue�� �뷮�� �Ķ���Ϳ� ���� ������ ����
    que->capacity = size;
}

// ť�� ����� ���� �� Ȯ�� �Լ�
int queue_size(const queue* que) {
    return que->count; //���� �� ���� ����
}

// ť �Ĵܿ� ������ ����
int enqueue(queue* que, int value) {

    // ���� queue�� �����Ͱ� �뷮�� �� ��ٸ�? -1 ��ȯ
    if (que->count >= que->capacity) {
        return -1;
    }

    // queue�� ���� �����͸� �����ϰ�,
    que->arr[que->rear] = value;

    // ���� queue �������� ���� ����
    ++(que->count);  

    // �� ��ġ��(rear)�� �迭�� �����Ҵ� �Ǿ������� ���� rear index���� �������Ѽ� �ذᰡ��
    ++(que->rear);

    // (���� queue ����) ���� �߰��� �������� index�� queue �뷮�� ũ��� ���ٸ�?
    //  -> ���� queue�� ���� �ֱٿ� �߰��� �����Ͱ� ��ġ�� �迭�� index�� 0���� ȸ�ͽ�Ŵ
    if (que->rear == que->capacity) {
        que->rear = 0; // ���� ť
    }

    return 0; //enqueue ���� ��
}

// ť �մ��� ������ ������ ��ȯ
int dequeue(queue* que) {

    int delVal;
    
    // ���� queue�� �����Ͱ� ���ٸ�? 0�� ��ȯ
    if (que->count <= 0) {
        return -1;
    }

    // ������ queue���� ���� �����͸� ����
    delVal = que->arr[que->front]; 

    // ���� queue �������� ���� ����
    --(que->count); 
    
    // ������ ���� queue�� index�� +1��
    ++(que->front);

    // (���� queue ����) ���� �������� �������� index�� queue �뷮�� ũ��� ���ٸ�?
    //  -> ������ ���� index�� 0���� ȸ�ͽ�Ŵ
    if (que->front == que->capacity) {
        que->front = 0; // 
    }

    // ������ ������ �����ߴٸ�, �� ������ ���� ��ȯ
    return delVal;
}

//---------------------------------------[graph �Լ�]---------------------------------------

// �׷��� ����ü ���� ��� �ʱ�ȭ
void graph_initialize(graph* grp, int count) {

    // ���� ���� �ʱ�ȭ
    grp->count = count;

    // node arr[count]; ���� ������ �����͵�, ������ŭ �����迭�� �Ҵ� ��, �� �����ּ� �׷��� ����ü node�����ͺ��� arr�� ����
    grp->arr = (node*)calloc(count, sizeof(node));
}

// ���Ⱓ�� �׷����� �߰�
// -> (�߿�!) ��Ȯ���� ��¥ ������ �߰��ϴ°� �ƴ϶�, � ������ �������� ����Ʈ�� �������� �پ��ִٴ� ������ �߰��ϱ� ���� ���̴� ������ ���� �������
//     -> �׷��ϱ� ������ �����Ѵٰ�, next_node�� ��¥�� �ʱ�ȭ �� ������ ������� �������� �����ϴ°� �ƴ϶�, 
//        �� ������ ���Ḯ��Ʈ���� ���� ������� �� �ٸ� ��� ����ü��� ����Ǵ� ���� �˾Ƶθ� �밡���� �� �������� 
//        (= �׷��� ������ ����Ǹ� �� �ٸ� �������� ������峢�� ����Ǽ� � ������ ����� �������� ������ �ҽ��� ó�� ����)
void adddirectedEdge(graph* grp, int src, int dst) {

    // ������������ �߰��� ���� ����ü ������ �����Ҵ��ϰ� �ּ���ġ�� ����
    node* newNode = (node*)malloc(sizeof(node));

    // ������������ �߰��� ������ ���� �Է� (���������� ���ҷμ� ������ ������ index ��ȣ�� �ϴ� ��)
    newNode->dst = dst;

    // ���� ������ ���������� ���� ������ ���� ��������� �ִ� ���������� �ּ� ���� (���������� ���� ������ NULL�̸� �׳� NULL�� ���� �Ǵ� ���� ����)
    newNode->next = grp->arr[src].next;

    // �� �� ��������� ���� ������ �ּҿ� ���������� ������ ���� �ڽ��� �ּҸ� ���� 
    grp->arr[src].next = newNode;
}

// �׷��� ����� ���� ���� (���� �׷����� ����, �� �������� �߰�)
void addUndirectedEdge(graph* grp, int src, int dst) {
    adddirectedEdge(grp, src, dst);
    adddirectedEdge(grp, dst, src);
}

// ���� �׷��� �� �������� ������������ ��� �����༭, �׷��� ������Ȳ�� ���� �ľ� �����ϰ� ��
void graph_display(const graph* grp) {

    // ������ ������ ������ �����ġ�� �ޱ� ���� ����
    node* cur = NULL;

    if (grp == NULL) return;

    // �� �������� ������� ���س��� �ݺ���
    for (int i = 0; i < grp->count; i++) {

        // ���� ��ġ ���� = �� ������ ���� �����ּ�
        cur = grp->arr[i].next;

        printf("����� ��� : %d ==> ", i); // ����� ��� ���

        //������� ���� ���󰡸�, ����� ������ �� ����ϱ�
        while (cur) {

            printf("%d ", cur->dst);

            // �ٴ��� ���� �ּҰ� ���� 
            cur = cur->next; // ���� ����
        }

        printf("\n");
    }
}

// �ش� �׷����� �Ҵ�� ��� �޸� ����.. 
// -> ���� ���ƾ� �Ұ�, ������������ ����� �ϳ��ϳ��� �� �Ҵ�ȰŴ� ���� �����ؾ���
void memoryFree(graph* grp) {

    node* delNode;

    // �׷����� ���� �����迭�� index�� �ش��ϴ� ���� ��ҿ� �پ��ִ� ���Ḯ��Ʈ���� ���� ��尡 ���������� ������ �����ؼ� ����
    for (int i = 0; i < grp->count; i++) {

        // �ش� ������ �� �̻� ����� ��尡 ���������� �����Ҵ� ������ ��� ����
        while (grp->arr[i].next) {

            // ������ ����� ��� �ּ� ����
            delNode = grp->arr[i].next;

            // ������ ������� �ּҸ� �ٴ��� ��� �ּҷ� ����
            grp->arr[i].next = delNode->next;

            free(delNode);
        }
    }
    free(grp->arr); // ����� ��� ����
}

//-----------------------------------------------[BFS_queue]-------------------------------------------------

// �ذ��) �׷����� queue(= ���� ���� ���� ���� ���� �̿�)�� Ȱ���� BFS ������� �����ذ� 
//  -> queue�� ����� ������ �ּҸ� ����(��ȭ ����)
//     -> while 1�� : queue���� ������ �ϳ��� pop�ϰ�, �� ������ ������ �ٸ� ������������ index�� queue�� �־�ΰ�, ��޵� ���� �湮ó���ϱ�
//     -> while 2�� : 1���� �ݺ��ؼ�, ���� �湮�� ������� ������ �ٸ� ������������ index�� �� �湮 ���� �����鸸 queue�� �־�ΰ�, queue�� ���� �������� �ݺ��ϱ�
void BFS_queue(graph* grp, int source) { // �Ű����� : �׷���, �����

    // int visited[count] : boolean visited array ���� �湮 �迭�� �����Ҵ� ��, �� �����ּ� ��ȯ
    int* visited = (int*)calloc(grp->count, sizeof(int));

    // queue ����ü ����
    queue que;

    // �ش� queue �뷮 9���� �ʱ�ȭ
    queue_initialize(&que, 9);

    // ����� ������ index�� ���ÿ� ���� (= queue�� ����� ������ �ּҸ� ����(��ȭ ����))
    enqueue(&que, source);

    // ������� �ش��ϴ� ��� �湮üũ
    visited[source] = 1;

    // whlle�� ����(�ִ� queue�� ���� index�� ���������� ������)
    //  : queue�� ���� ������ ��� Pop �� ������ �ݺ�
    while (queue_size(&que) != 0) {

        // stack�� ���� ù��° ���(= �湮�� ����) Pop
        int startNode = dequeue(&que);  
        printf("%d ", startNode); 

        // ���� ����� ��ġ�� �ޱ� ���� node����ü�� �����ͺ��� ���� ��, �湮�� ������ ���� ���� �ּ�
        node* curNode = grp->arr[startNode].next;

        // while�� ����(index ä�� �뵵�� pop�� ����index�� ������ �ٸ� ������������ index�� �� �湮ó�� �ȵ� �ֵ鸸 queue�� �־�ΰ�, ���� �湮�� ���� �湮ó���ϱ�
        //  : ���� ������ ���� ���� �ּҰ� ������ ��� �ݺ� (= ���� �� ���� ������ ����� ������ ������ �� ���ö����� ��� �ݺ�)
        while (curNode) {

            // ���� ���� �ִ� ���� ������ index
            int dst = curNode->dst;

            // �� ���� ������ �湮�� ���� ������
            if (visited[dst] == 0) {

                // ���� �ش� ���������� queue�� ���ÿ� ����
                enqueue(&que, dst);

                // ���� �ش� ���������� �湮ó��
                visited[dst] = 1; 
            }

            // �� ���� ������ �ش��ϴ� ������ �湮�� ���� ������, �� ���������� ���� ���������� �ּҸ� ���� (= �̷��� �� ������ ���� ���� ����Ʈ�� �� �̻� ���� NULL�� ������ ����)
            curNode = curNode->next;
        }
    }

    printf("\n");

    free(que.arr); //ť �޸� ����
}
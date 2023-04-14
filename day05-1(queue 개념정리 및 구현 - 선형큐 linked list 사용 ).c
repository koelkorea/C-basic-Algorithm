// ť(Queue)
//  : ���� ���� �����Ͱ� ���� ������ �ڷᱸ�� 
//    (= ���� �� ��� '����ȣ'��� ó���ϴ� ��⿭ �� ��ü)

//  # ���Լ��� FIFO
//    : First-In, First-Out

//  # Queue�� ����
//    1. ���� ť(linear quere)   : ������ ������ �޸𸮸� ����Ͽ� Queue�� ���� (= linked list(���Ḯ��Ʈ)�� ����)
//    2. ���� ť(circliar queue) : ������ ������ �޸𸮸� ����Ͽ� Queue�� ���� (= circular linked list(���� ���Ḯ��Ʈ), �����迭�� ����)
//       -> ���� ��½� �ö󰡴� index, �Է½� �ö󰡴� index�� ������ �ΰ� üũ�ؼ� ��

//  # Queue ����ü ( ���� ��� )
//    typedef int QueueElement;

//    typedef struct QueueNode {
//        QueueElement data;
//        struct QueueNode* link;
//    } QueueNode;

//    typedef struct Queue {
//        QueueNode* front, * rear;
//    } LinkedQueueType;

//  # Queue ADT
//    - void QueueInit(LinkedQueueType* queue); �ʱ�ȭ
//    - int QueueIsEmpty(LinkedQueueType* queue); Node�� ������ Ȯ��
//    - void Enqueue(LinkedQueueType* queue, QueueElement data); Node ����
//    - QueueElement Dequeue(LinkedQueueType* queue); Node ����
//    - void PrintQueue(LinkedQueueType* queue); Node ���
//    - void FreeQueue(LinkedQueueType* queue); Queue ����


// ��(deque) = double-ended queue
//  : ť�� ����(front)�� �Ĵ�(rear)���� ��� ���԰� ������ ������ ť 
//    (= stack�� queue�� ��� ���� ����� �����ϴٴ� ��..)
//     -> ���� ��ü�� double linked ����Ʈ�� ������ ����.. (�����Ҵ����ε� ������ �ѵ� �޸� ���� �������� �ؼ� �ð�ȿ���� �������� ��ȿ����)

// ����ť�� Queue ADT ���� �����غ��� (linked list ����ؼ�..)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <conio.h>		// (���) conio.h (console and port I/0�� ����) :  c����� �ܼ� ����� �Լ��� ����


typedef int QueueElement;

typedef struct QueueNode {
    QueueElement data;
    struct QueueNode* link;
} QueueNode;

// Queue ����ü���� front, rear�� ���� ť�� �� �հ� �� ���� �ּҰ��� �����ϴ� �����ͺ���
typedef struct Queue {
    QueueNode* front, * rear;
} LinkedQueueType;


// Queue �ʱ�ȭ 
LinkedQueueType* QueueInit1(LinkedQueueType* queue);
void QueueInit2(LinkedQueueType** queue);

// ������ Queue�� Node�� ������ Ȯ��
int QueueIsEmpty(LinkedQueueType* queue);

// ���ο� ��� ���� �� �߰�(= �� �ڿ� �߰�)
void Enqueue(LinkedQueueType* queue, QueueElement data);

// ������ Queue�� ������ ������ ù��° Node ����
QueueElement Dequeue(LinkedQueueType* queue);

// ������ Queue�� �����ϴ� ��� Node ���
void PrintQueue(LinkedQueueType* queue); 

// Queue�� ���� �Ҵ�� ��� �޸� �Ҵ� ����
void FreeQueue(LinkedQueueType* queue); 


int main(void) {

    srand((unsigned int)time(NULL));

    LinkedQueueType* linear_queue = NULL;
    LinkedQueueType* linear_queue2 = NULL;

    linear_queue = QueueInit1(linear_queue);
    QueueInit2(&linear_queue2);

    for (int i = 0; i <= 5; i++) {
        Enqueue(linear_queue, i * 3);
        Enqueue(linear_queue2, rand() % 50 + 1);
    }

    PrintQueue(linear_queue);
    PrintQueue(linear_queue2);

    for (int i = 0; i <= 3; i++) {
        Dequeue(linear_queue);
    }

    PrintQueue(linear_queue);

    for (int i = 0; i <= 3; i++) {
        Enqueue(linear_queue, rand() % 50 + 1);
    }
    PrintQueue(linear_queue);
    FreeQueue(linear_queue);

    return 0;
}

// Queue �ʱ�ȭ (call by reference)
LinkedQueueType* QueueInit1(LinkedQueueType* queue) {

    queue = (LinkedQueueType*)malloc(sizeof(LinkedQueueType));

    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

// Queue �ʱ�ȭ (call by reference)
void QueueInit2(LinkedQueueType** queue) {

    *queue = (LinkedQueueType*)malloc(sizeof(LinkedQueueType));

    (*queue)->front = NULL;
    (*queue)->rear = NULL;
}

// ������ Queue�� Node�� ������ Ȯ�� (queue�� �Ǿ��̳� �ڿ� ��ġ�� ����� �ּҰ� �������)
int QueueIsEmpty(LinkedQueueType* queue) {

    if (queue->front == NULL && queue->rear == NULL) {
        return 0;
    }

    return 1;
}

// �� �ڿ� Node �߰�(���� ���� �༮�� �ڷ� �и��� ���)
void Enqueue(LinkedQueueType* queue, QueueElement data) {

    printf_s("\n\n------------------------------[queue�� %d �ֱ� ����!]------------------------------\n", data);

    QueueNode* Newnode = (QueueNode*)malloc(sizeof(QueueNode));

    // ��带 ���� �޸� ������ ���ٸ�?? ���� ����
    if (Newnode == NULL) {
        printf("�޸� ����");
        return NULL;
    }

    // Queue�� �����ϴ� 1��° ��忡 ���� �����ּ� ����
    Newnode->data = data;
    Newnode->link = NULL;

    // queue�� �� ���� �ִ��� Ȯ��
    if (QueueIsEmpty(queue) == 0) {

        printf_s("(�ȳ�!) ������ Queue�� �� �ִ� ���� �����Ƿ� 1��° ��带 ����\n");

        // queue�� ���� �հ� �޳���� �ּҰ��� Newnode�� ����
        queue->front = Newnode;
        queue->rear = Newnode;

        printf_s("queue�� ó������ ������ ���� %d�� �Է¿Ϸ�\n", queue->rear->data);
    }
    else if (QueueIsEmpty(queue) == 1) {

        // ���� ������ ����� rear�� Newnode�� ����
        queue->rear->link = Newnode;

        // queue�� �޳���� �ּҸ� ���� ������� Newnode�� ����
        queue->rear = Newnode;

        printf_s("queue�� ������ ���� %d�� �Է¿Ϸ�\n", queue->rear->data);
    }

}


// ������ Queue�� ������ ������ ù��° Node ����
QueueElement Dequeue(LinkedQueueType* queue) {

    printf_s("\n\n------------------------------[delete_first�� ù��° ��� ���� ����!]------------------------------\n");

    // queue�� �� ���� �ִ��� Ȯ��
    if (QueueIsEmpty(queue) == 0) {

        printf_s("(���!) ������ Queue�� �� �ִ� ���� �����Ƿ� ���� ���� �� �����ϴ�.\n");

        return 1;
    }
    else if (QueueIsEmpty(queue) == 1) {

        // ���� ��� = ���� ���� 1��° ���
        QueueNode* deleteNode = queue->front;

        // queue�� ���� �ճ���� �ּҰ��� ���� 2��° ����� ������ ����
        queue->front = queue->front->link;

        printf_s("queue�� ó�� ���� %d�� �����Ϸ�\n", queue->front->data);
        free(deleteNode);

        return 0;
    }

}

// ������ Queue�� �����ϴ� ��� Node ���
void PrintQueue(LinkedQueueType* queue) {

    printf_s("\n\n------------------------------[�ּҰ� %d�� ��ġ�� queue�� linked list �ּҰ��� ��� PrintQueue ����!]------------------------------\n\n", queue);

    QueueNode* printed_index = queue->front;

    printf("queue ��� : ");

    while (printed_index != NULL) {
        printf("%3d", printed_index->data);

        if (printed_index->link != NULL) {
            printf(" -> ");
        }

        printed_index = printed_index->link;
    }
}

// Queue�� ���� �Ҵ�� ��� �޸� �Ҵ� ����
void FreeQueue(LinkedQueueType* queue) {

    QueueNode* free_index = queue->front;

    while (free_index != NULL) {

        QueueNode* next_address = free_index->link;
        free(free_index);
        free_index = next_address;
    }

    queue->front = NULL;
    queue->rear = NULL;

    free(queue);
}
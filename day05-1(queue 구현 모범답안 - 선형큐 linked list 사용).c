#include <stdio.h>
#include <stdlib.h>
#include <time.h>
enum menu { Enq = 1, Deq, End, Ded, Prt };

typedef int QueueElement;

typedef struct QueueNode {
    QueueElement data;
    struct QueueNode* link;
} QueueNode;

typedef struct Queue {
    QueueNode* front, * rear;
} LinkedQueueType;

// Queue 초기화
void QueueInit(LinkedQueueType* queue)
;
// Queue에 Node가 없는지 확인
int QueueIsEmpty(LinkedQueueType* queue);

// Queue Node 생성
void Enqueue(LinkedQueueType* queue, QueueElement data);

// Queue Node 삭제
QueueElement Dequeue(LinkedQueueType* queue);

// Queue Node 출력
void PrintQueue(LinkedQueueType* queue);

// Queue 삭제
void FreeQueue(LinkedQueueType* queue);

#define FRONT 1
#define REAR 2

// Deque 구현
void Endeque(LinkedQueueType* queue, QueueElement data, int direction);
QueueElement Dedeque(LinkedQueueType* queue, int direction);

int main(void) {
    srand((unsigned)time(NULL));
    int menu = 0, de_F_R = 0;
    QueueElement value;
    LinkedQueueType queue;
    QueueInit(&queue);
    for (int i = 10; i < 100; i += 20) Enqueue(&queue, i);
    while (1) {
        printf("1. Queue enqueue\n");
        printf("2. Queue dequeue\n");
        printf("3. Deque endeque\n");
        printf("4. Deque dedeque\n");
        printf("5. Print Queue\n");
        printf("메뉴를 입력 하세요. :");
        scanf_s("%d", &menu);
        while (getchar() != '\n');
        switch (menu) {
        case Enq:
            printf("값을 입력하세요. : ");
            scanf_s("%d", &value);
            while (getchar() != '\n');
            Enqueue(&queue, value);
            printf("%d 값을 넣었습니다.\n\n", value);
            break;
        case Deq:
            printf("값을 출력합니다.\n");
            printf("%d\n\n", Dequeue(&queue));
            break;
        case End:
            printf("Front 1 / Rear 2 (전단 1 / 후단 2) : ");
            scanf_s("%d", &de_F_R);
            while (getchar() != '\n');
            printf("값을 입력하세요. : ");
            scanf_s("%d", &value);
            while (getchar() != '\n');
            Endeque(&queue, value, de_F_R);
            printf("%d 값을 넣었습니다.\n\n", value);
            break;
        case Ded:
            printf("Front 1 / Rear 2 (전단 1 / 후단 2) : ");
            scanf_s("%d", &de_F_R);
            printf("값을 출력합니다.\n");
            printf("%d\n\n", Dedeque(&queue, de_F_R));
            break;
        case Prt:
            PrintQueue(&queue);
            break;
        default:
            FreeQueue(&queue);
            exit(0);
        }
    }
    return 0;
}

void QueueInit(LinkedQueueType* queue) {
    queue->front = queue->rear = NULL; 
}

int QueueIsEmpty(LinkedQueueType* queue) {
    return (queue->front == NULL); 
}

void Enqueue(LinkedQueueType* queue, QueueElement data) {

    QueueNode* NewNode = (QueueNode*)malloc(sizeof(QueueNode));

    if (NewNode == NULL) {
        printf("새 노드 동적 할당 실패!\n"), exit(1); 
    }

    NewNode->data = data;
    NewNode->link = NULL;

    if (QueueIsEmpty(queue)) {
        queue->front = NewNode;
        queue->rear = NewNode;
    }
    else {
        queue->rear->link = NewNode;
        queue->rear = NewNode;
    }
}

QueueElement Dequeue(LinkedQueueType* queue) {

    if (QueueIsEmpty(queue)) {
        printf(" Queue is empty.\n");
        return 0;
    }
    else {

        QueueNode* DeleteNode = queue->front;
        QueueElement data = DeleteNode->data;

        queue->front = queue->front->link;

        if (queue->front == NULL) {
            queue->rear = NULL;
        }
        free(DeleteNode);

        return data;
    }
}

void PrintQueue(LinkedQueueType* queue) {

    printf(" Queue -> ");

    for (QueueNode* pNode = queue->front; pNode != NULL; pNode = pNode->link) {
        printf("%4d -> ", pNode->data);
    }

    printf(" NULL\n\n");
}

void FreeQueue(LinkedQueueType* queue){

    for (QueueNode* pNode = queue->front; pNode != NULL; ) {

        QueueNode* DeleteNode = pNode;
        pNode = pNode->link;
        free(DeleteNode);
    }

    queue->front = queue->rear = NULL;
}

void Endeque(LinkedQueueType* queue, QueueElement data, int direction) {

    QueueNode* NewNode = (QueueNode*)malloc(sizeof(QueueNode));

    if (NewNode == NULL) {
        printf("새 노드 동적 할당 실패!\n"), exit(1);
    }

    NewNode->data = data;
    NewNode->link = NULL;
    
    if (QueueIsEmpty(queue)) {
        queue->front = NewNode;
        queue->rear = NewNode;
    }
    else if (direction == FRONT) {
        NewNode->link = queue->front;
        queue->front = NewNode;
    }
    else {
        queue->rear->link = NewNode;
        queue->rear = NewNode;
    }
}

QueueElement Dedeque(LinkedQueueType* queue, int direction) {

    if (QueueIsEmpty(queue)) {

        printf(" Queue is empty.\n");
        return 0;
    }
    else {
        QueueNode* DeleteNode = queue->front;

        if (queue->front->link == NULL) {
            queue->front = queue->rear = NULL; //0
        }
        else if (direction == REAR) {

            DeleteNode = queue->rear;
            QueueNode* LastNode = queue->front;

            while (LastNode->link != queue->rear) {
                LastNode = LastNode->link;
            }

            queue->rear = LastNode;
            queue->rear->link = NULL;

        }
        else { //FRONT
            queue->front = queue->front->link;
        }

        QueueElement data = DeleteNode->data;
        free(DeleteNode);

        return data;
    }
}

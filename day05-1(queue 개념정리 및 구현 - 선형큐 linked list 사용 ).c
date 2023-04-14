// 큐(Queue)
//  : 먼저 들어온 데이터가 먼저 나가는 자료구조 
//    (= 먼저 온 사람 '대기번호'대로 처리하는 대기열 그 자체)

//  # 선입선출 FIFO
//    : First-In, First-Out

//  # Queue의 종류
//    1. 선형 큐(linear quere)   : 선형식 구조로 메모리를 사용하여 Queue를 구현 (= linked list(연결리스트)로 구현)
//    2. 원형 큐(circliar queue) : 원형식 구조로 메모리를 사용하여 Queue를 구현 (= circular linked list(원형 연결리스트), 정적배열로 구현)
//       -> 대충 출력시 올라가는 index, 입력시 올라가는 index를 변수로 두고 체크해서 함

//  # Queue 구조체 ( 구성 요소 )
//    typedef int QueueElement;

//    typedef struct QueueNode {
//        QueueElement data;
//        struct QueueNode* link;
//    } QueueNode;

//    typedef struct Queue {
//        QueueNode* front, * rear;
//    } LinkedQueueType;

//  # Queue ADT
//    - void QueueInit(LinkedQueueType* queue); 초기화
//    - int QueueIsEmpty(LinkedQueueType* queue); Node가 없는지 확인
//    - void Enqueue(LinkedQueueType* queue, QueueElement data); Node 생성
//    - QueueElement Dequeue(LinkedQueueType* queue); Node 삭제
//    - void PrintQueue(LinkedQueueType* queue); Node 출력
//    - void FreeQueue(LinkedQueueType* queue); Queue 삭제


// 덱(deque) = double-ended queue
//  : 큐의 전단(front)와 후단(rear)에서 모두 삽입과 삭제가 가능한 큐 
//    (= stack과 queue의 기능 전부 사용이 가능하다는 말..)
//     -> 구현 자체는 double linked 리스트로 구현이 편함.. (동적할당으로도 가능은 한데 메모리 ㅈㄴ 움직여야 해서 시간효율성 관점에서 비효율적)

// 선형큐로 Queue ADT 전부 구현해보자 (linked list 사용해서..)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <conio.h>		// (헤더) conio.h (console and port I/0의 약자) :  c언어의 콘솔 입출력 함수를 제공


typedef int QueueElement;

typedef struct QueueNode {
    QueueElement data;
    struct QueueNode* link;
} QueueNode;

// Queue 구조체에서 front, rear는 각각 큐의 맨 앞과 맨 뒤의 주소값을 저장하는 포인터변수
typedef struct Queue {
    QueueNode* front, * rear;
} LinkedQueueType;


// Queue 초기화 
LinkedQueueType* QueueInit1(LinkedQueueType* queue);
void QueueInit2(LinkedQueueType** queue);

// 현재의 Queue에 Node가 없는지 확인
int QueueIsEmpty(LinkedQueueType* queue);

// 새로운 노드 생성 및 추가(= 맨 뒤에 추가)
void Enqueue(LinkedQueueType* queue, QueueElement data);

// 현재의 Queue에 기존에 존재한 첫번째 Node 삭제
QueueElement Dequeue(LinkedQueueType* queue);

// 현재의 Queue에 존재하는 모든 Node 출력
void PrintQueue(LinkedQueueType* queue); 

// Queue를 위해 할당된 모든 메모리 할당 해제
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

// Queue 초기화 (call by reference)
LinkedQueueType* QueueInit1(LinkedQueueType* queue) {

    queue = (LinkedQueueType*)malloc(sizeof(LinkedQueueType));

    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

// Queue 초기화 (call by reference)
void QueueInit2(LinkedQueueType** queue) {

    *queue = (LinkedQueueType*)malloc(sizeof(LinkedQueueType));

    (*queue)->front = NULL;
    (*queue)->rear = NULL;
}

// 현재의 Queue에 Node가 없는지 확인 (queue의 맨앞이나 뒤에 위치한 노드의 주소가 없을경우)
int QueueIsEmpty(LinkedQueueType* queue) {

    if (queue->front == NULL && queue->rear == NULL) {
        return 0;
    }

    return 1;
}

// 맨 뒤에 Node 추가(전에 만든 녀석은 뒤로 밀리는 방식)
void Enqueue(LinkedQueueType* queue, QueueElement data) {

    printf_s("\n\n------------------------------[queue에 %d 넣기 시작!]------------------------------\n", data);

    QueueNode* Newnode = (QueueNode*)malloc(sizeof(QueueNode));

    // 노드를 만들 메모리 공간이 없다면?? 에러 띄우기
    if (Newnode == NULL) {
        printf("메모리 부족");
        return NULL;
    }

    // Queue를 구성하는 1번째 노드에 값과 다음주소 자정
    Newnode->data = data;
    Newnode->link = NULL;

    // queue에 들어간 값이 있는지 확인
    if (QueueIsEmpty(queue) == 0) {

        printf_s("(안내!) 현재의 Queue에 들어가 있는 값이 없으므로 1번째 노드를 만듦\n");

        // queue의 가장 앞과 뒷노드의 주소값을 Newnode로 지정
        queue->front = Newnode;
        queue->rear = Newnode;

        printf_s("queue의 처음이자 마지막 값인 %d을 입력완료\n", queue->rear->data);
    }
    else if (QueueIsEmpty(queue) == 1) {

        // 기존 마지막 노드의 rear값 Newnode로 갱신
        queue->rear->link = Newnode;

        // queue의 뒷노드의 주소만 새로 만들어진 Newnode로 지정
        queue->rear = Newnode;

        printf_s("queue의 마지막 값인 %d을 입력완료\n", queue->rear->data);
    }

}


// 현재의 Queue에 기존에 존재한 첫번째 Node 삭제
QueueElement Dequeue(LinkedQueueType* queue) {

    printf_s("\n\n------------------------------[delete_first로 첫번째 노드 삭제 시작!]------------------------------\n");

    // queue에 들어간 값이 있는지 확인
    if (QueueIsEmpty(queue) == 0) {

        printf_s("(경고!) 현재의 Queue에 들어가 있는 값이 없으므로 값은 지울 수 없습니다.\n");

        return 1;
    }
    else if (QueueIsEmpty(queue) == 1) {

        // 없앨 노드 = 현재 가장 1번째 노드
        QueueNode* deleteNode = queue->front;

        // queue의 가장 앞노드의 주소값을 기존 2번째 노드의 값으로 변경
        queue->front = queue->front->link;

        printf_s("queue의 처음 값인 %d을 삭제완료\n", queue->front->data);
        free(deleteNode);

        return 0;
    }

}

// 현재의 Queue에 존재하는 모든 Node 출력
void PrintQueue(LinkedQueueType* queue) {

    printf_s("\n\n------------------------------[주소값 %d에 위치한 queue의 linked list 주소값에 기반 PrintQueue 시작!]------------------------------\n\n", queue);

    QueueNode* printed_index = queue->front;

    printf("queue 출력 : ");

    while (printed_index != NULL) {
        printf("%3d", printed_index->data);

        if (printed_index->link != NULL) {
            printf(" -> ");
        }

        printed_index = printed_index->link;
    }
}

// Queue를 위해 할당된 모든 메모리 할당 해제
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
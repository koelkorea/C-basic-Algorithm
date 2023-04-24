// 이진검색 트리(binery search tree)
//  : 이진트리의 모든 노드의 값이 'key(왼쪽서브트리) < key(부모[루트]노드) < key(오른쪽서브트리)'의 특성으로 정렬배치 된 특수한 이진트리

//    ex)        5
//            3      7   
//          2   4  6   8
//        1              9

//   # 이진검색 트리의 특징 
//     1. 같은 값을 갖는 노드는 없음
//     2. 중위 순회를 하면 최소값 ~ 최대값의 전체수를 오름차순으로 출력할 수 있음 ( <-> 내림차순은 그 반대 오른쪽 - 부모 - 왼쪽)
//     3. 레벨과 별개로 가장 좌측에 위치하는 수가 최소값, 가장 우측에 위치하는 수가 최대값
//     4. 가급적 중위값이 가장 위에 있어야 트리 구조가 대칭에 가까워짐
//        (= 중위값이 최상단에 있어야 어떤 숫자를 검색하던 이진검색이 효율적 -> red black tree가 나온 이유)

//   # 이진검색 트리의 목적? -> 발전형인 red black tree가 나온 이유
//     : 애초에 이런 트리를 짜는 목적이 효율적인 이진검색을 위한 것..
//       -> how to? 중위값을 기준으로 크고 작음을 비교한다면, 어떤 수를 검색해도 최대 log(2)N+1 번이면 검색이 끝남을 알수 있음
//          -> 중위값을 루트로 둔 대칭구조의 이진트리라면 이를 실현가능한 극도로 효율적인 구조임 발견!
//              -> 입력되는 데이터마다 중위값이 최상단 '루트'로 가게하고, 이진트리적으로 대칭을 이루게 하도록 배치하는 방법을 모색하자 (red black tree가 나온 이유)

//   # red black tree와 이진검색트리 관계
//     : 개념적으로 이진검색트리 > red black tree인 관계 
//       (= 쉽게 설명하면, 매번 중위값이 루트가 되어 대칭을 이루도록 하는 이진트리가 red black tree)


//   # 이진 검색트리 삭제 알고리즘
//     1. 삭제하려는 노드가 리프(말단 노드)일 경우
//        : 말단 노드의 부모 노드를 찾아서 link를 끊음
//     2. 삭제하려는 노드가 하나의 왼쪽이나 오른쪽 자식을 가지고 있는 경우
//        : 노드는 삭제하고, 그 트리가 가지는 자식들인 서브 트리는 삭제된 노드의 부모 노드에 붙여줌 
//          -> 재귀적 방법으로 이를 역참조한 값에 대입해줌
//     3. 삭제하려는 노드가 두 개의 자식을 모두 가지고 있는 경우
//        : 삭제노드와 가장 근사값을 가진 노드값을 삭제할 노드위치의 값으로 대입 (= 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값)
//          -> (중요!) 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값.. 이들은 결과적으로 '리프노드'로 자식이 없음
//              -> 결과적으로 리프노드의 값을 삭제할 노드의 값으로 옮김 
//                 (= 결과적으로 삭제할 녀석은 리프노드를 의미함 -> 사실상 값을 이식 + 리프노드 삭제하는 경우1의 문제가 됨)


// 이진검색 트리(여기서는 처음에 들어온 값을 루트로 하고 이걸 영원히 바꾸지 않는 트리로 가정... red black tree가 아님)의 조회 기능 구현 코드
#include <stdio.h>
#include <stdlib.h>       //	srand(), rand() 함수 사용 가능하게 함
#include <time.h>


//-------------------------------------------------------------------------------------[큐]----------------------------------------------------------------

// 트리 구현 구조체
typedef int element;
typedef struct treeNode {
    element value;               // 값
    struct treeNode* left;       // (현재 노드기준) 왼쪽 노드의 주소값 
    struct treeNode* right;      // (현재 노드기준) 오른쪽 노드의 주소값 
}treeNode;

// 트리의 포인터를 값으로 받는 큐 생성
typedef treeNode* QueueElement;

typedef struct QueueNode {
    QueueElement data;
    struct QueueNode* link;
} QueueNode;

// Queue 구조체에서 front, rear는 각각 큐의 맨 앞과 맨 뒤의 주소값을 저장하는 포인터변수
typedef struct Queue {
    QueueNode* front, * rear;
} LinkedQueueType;

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

    // printf_s("\n\n------------------------------[queue에 %d 넣기 시작!]------------------------------\n", data);

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

        // printf_s("queue의 처음이자 마지막 값인 %d을 입력완료\n", queue->rear->data);
    }
    else if (QueueIsEmpty(queue) == 1) {

        // 기존 마지막 노드의 rear값 Newnode로 갱신
        queue->rear->link = Newnode;

        // queue의 뒷노드의 주소만 새로 만들어진 Newnode로 지정
        queue->rear = Newnode;

        // printf_s("queue의 마지막 값인 %d을 입력완료\n", queue->rear->data);
    }

}

// 현재의 Queue에 기존에 존재한 첫번째 Node 삭제후, 삭제했던 트리노드 주소값 리턴
QueueElement Dequeue(LinkedQueueType* queue) {

    // printf_s("\n\n------------------------------[Dequeue로 첫번째 노드 삭제 시작!]------------------------------\n");

    // queue에 들어간 값이 있는지 확인
    if (QueueIsEmpty(queue) == 0) {

        printf_s("(경고!) 현재의 Queue에 들어가 있는 값이 없으므로 값은 지울 수 없습니다.\n");

        return NULL;
    }
    else if (QueueIsEmpty(queue) == 1) {

        // 없앨 노드 = 현재 가장 1번째 노드
        QueueNode* deleteNode = queue->front;

        // 없앨 노드의 값인 tree노드의 주소값은 미리 복사
        //  -> 이 값을 역참조하여 나열할 예정
        QueueElement result = deleteNode->data;

        //printf_s("queue의 처음 값인 %d을 삭제완료\n", queue->front->data);

        // queue의 가장 앞노드의 주소값을 기존 2번째 노드의 값으로 변경
        queue->front = queue->front->link;

        // 큐에 남은 노드가 하나뿐이 없는 경우
        //  -> queue의 가장 뒷 노드의 주소도 다시 NULL인 queue->front와 일치
        if (queue->front == NULL) {

            queue->rear == NULL;
        }

        free(deleteNode);

        return result;
    }

}

// 현재의 Queue에 존재하는 모든 Node 출력
void PrintQueue(LinkedQueueType* queue) {

    printf_s("\n\n------------------------------[주소값 %d에 위치한 queue의 linked list 주소값에 기반 PrintQueue 시작!]------------------------------\n\n", queue);

    QueueNode* printed_index = queue->front;

    while (printed_index != NULL) {

        printf("%3d ", printed_index->data);
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
//---------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------[트리]-------------------------------------------------------------------------------------------

// 이진검색트리에 노드 추가 메서드 (= 사실상 이진트리에 노드 추가하는 메서드와 같은 기능)
//  -> 이진검색 트리는 루트가 사실상 중위값이 되어야 하는 구조로 트리가 구성되어 있어야 검색과 삭제가 가능
//     (= 애초부터 트리에 값이 들어갈 때 이진검색트리 구조를 만족시켜야 함)
treeNode* addNode(treeNode* t, element data) {

    // 경우1) 파라미터로 들어간 트리구조체 포인터변수에 주소값이 없음 (= 주소값이 NULL)
    // -> 이진탐색 실패 위치가 삽입 위치 & 노드가 없을 때
    if (!t) {
        t = (treeNode*)malloc(sizeof(treeNode));
        t->value = data;
        t->left = NULL;
        t->right = NULL;
    }
    // 경우2) 파라미터로 들어간 검색값을 가진 트리노드(처음에는 루트노드가 대상)가 발견
    else if (data == t->value) {
        printf("\n\n\t\t%d는 이미 등록 된 값 입니다.\n", data);
    }
    // 경우3) 파라미터로 들어간 검색값보다 작은 값을 가진 가진 트리노드(처음에는 루트노드가 대상)가 발견
    //  -> 왼쪽 노드를 뒤져보며, 이를 재귀적으로 실행해서 해당 값을 가진 노드를 이진검색트리에 추가할 위치를 찾는다
    else if (data < t->value) {
        t->left = addNode(t->left, data);
    }
    // 경우4) 파라미터로 들어간 검색값보다 큰 값을 가진 가진 트리노드(처음에는 루트노드가 대상)가 발견
    //  -> 오른쪽 노드를 뒤져보며, 이를 재귀적으로 실행해서 해당 값을 가진 노드를 이진검색트리에 추가할 위치를 찾는다
    else /* data > t->value */ {
        t->right = addNode(t->right, data);
    }

    return t;
}

// 해당 트리를 BFS(너비우선탐색)방식(= 레벨대로 순환)으로 조회하는 메서드 
void displayBFS(LinkedQueueType* queue) {

    QueueElement pop_data = NULL;

    while (queue->front != NULL) {

        pop_data = Dequeue(queue);
        printf("%d ", pop_data->value);

        if (pop_data->left != NULL) {
            Enqueue(queue, pop_data->left);
        }

        if (pop_data->right != NULL) {
            Enqueue(queue, pop_data->right);
        }

    }
}



// 해당 트리를 전위순회( [기준 노드] 부모 -> 왼쪽 -> 오른쪽 순으로 조회)하여 조회하는 메서드
//  -> 원칙적으로는 부모, 왼쪽, 오른쪽 노드가 NULL일시 그 노드의 값을 찍으라고 코드를 짜야하나.. 
//     -> 굉장히 논리적으로나 성능적으로나 번거롭기 그지없으므로, 부모노드를 보는 대신 자신의 값을 찍는거로 대체
void displayPreOrder(treeNode* t) {
    if (t) {
        // 원칙적으로는 부모노드를 타고 올라가라고 지정해야 하나.. 루트부터 시작시 어차피 자기자신의 값을 찍어도 같음
        //  : 루트 -> 루트 부모 null -> 루트 왼쪽 노드(r_left) -> r_left의 부모노드 = 루트값 출력
        //  : 루트값 출력 -> 루트 왼쪽 노드(r_left) 값 출력 -> 
        printf("%d ", t->value);
        displayPreOrder(t->left);
        displayPreOrder(t->right);
    }
}

// 해당 트리를 중위순회( [기준 노드] 왼쪽 -> 부모 -> 오른쪽 순으로 조회)하여 조회하는 메서드
//  -> 원칙적으로는 부모, 왼쪽, 오른쪽 노드가 NULL일시 그 노드의 값을 찍으라고 코드를 짜야하나.. 
//     -> 굉장히 논리적으로나 성능적으로나 번거롭기 그지없으므로, 부모노드를 보는 대신 자신의 값을 찍는거로 대체
void displayInOrder(treeNode* t) {
    if (t) {
        displayInOrder(t->left);
        printf("%d ", t->value);
        displayInOrder(t->right);
    }
}

// 해당 트리를 후위순회( [기준 노드] 왼쪽 -> 오른쪽 -> 부모 순으로 조회)하여 조회하는 메서드
//  -> 원칙적으로는 부모, 왼쪽, 오른쪽 노드가 NULL일시 그 노드의 값을 찍으라고 코드를 짜야하나.. 
//     -> 굉장히 논리적으로나 성능적으로나 번거롭기 그지없으므로, 부모노드를 보는 대신 자신의 값을 찍는거로 대체
void displayPostOrder(treeNode* t) {
    if (t) {
        displayPostOrder(t->left);
        displayPostOrder(t->right);
        printf("%d ", t->value);
    }
}

// 트리구조 해체의 순서는 노드를 모드 깔끔하게 삭제해야 하니, 부모노드를 가장 나중에 보는 걸로 한다
void freeTree(treeNode* t) {
    if (t) {
        freeTree(t->left);
        freeTree(t->right);
        printf("\n노드 삭제 : %d\n", t->value);
        free(t);
    }
}

// 해당 노드를 기준으로, 그 아래 레벨에 있는 값중 가장 큰 값을 구하는 메서드 
// (= 해당 노드의 값보다는 작지만, 그 아래에 있는 값 중 가장 오른쪽에 위치한, '작은자 중에서 최대값'을 구해야 함)
treeNode* findMax(treeNode* t) {

    treeNode* minMax_address = t;

    if (minMax_address) {

        while (t->right != NULL) {
            minMax_address = t->right;
        }
    }

    return minMax_address;
}

// 해당 노드를 기준으로, 그 아래 레벨에 있는 값중 가장 작은 값을 구하는 메서드 
// (= 해당 노드의 값보다는 크지만, 그 아래에 있는 값 중 가장 왼쪽에 위치한, '큰자 중에서 최소값'을 구해야 함)
treeNode* findMin(treeNode* t) {

    treeNode* maxMin_address = t;

    if (maxMin_address) {

        while (t->left != NULL) {
            maxMin_address = t->left;
        }
    }

    return maxMin_address;
}


// 이진검색트리 구조 검색 메서드 (= 기본적으로 이진트리 구조는 재귀적 방법을 사용)
//  -> 해당 트리 검색 로직은 이진검색트리의 구조적 특성이 기반이 됨
//     -> 과정1) 루트를 기반으로 값을 검사
//        과정2) 값이 작으면 왼쪽루트로.. 크면 오른쪽 루트로
//        과정3) 이 짓을 재귀를 통해 반복... 값이 도중에 나오면 트리노드 주소값 리턴.. 아니면 null 
treeNode* searchNode(treeNode* t, element data) {

    // [최종 탐색 실패]
    // 만약 현재 트리가 존재하지 않는다면(= 아무리 뒤져봤지만, 검색할 값이 존재하지 않았음)
    //  -> NULL 리턴
    if (!t) {
        return NULL;
    }

    // [검색 성공]
    //  -> 해당 노드의 주소값 출력
    if (data == t->value) {
        return t;
    }

    // [현재 탐색 실패 = 다음 노드를 봐야함]

    // 현재 노드 data값이 작음 = 이진 트리 구조상 자신의 값보다 작은게 왼쪽에 존재하니 왼쪽으로..
    if (data < t->value) {
        return searchNode(t->left, data);
    }
    // 현재 노드 data값이 큼 = 이진 트리 구조상 자신의 값보다 큰게 오른쪽에 존재하니 오른쪽으로..
    else /* data > t->value */ {
        return searchNode(t->right, data); // 오른쪽 탐색
    }
}

// 이진검색트리 구조 삭제 메서드 (= 기본적으로 트리구조는 재귀적 방법을 사용)
//  -> 해당 트리 삭제 로직은 이진검색트리의 구조적 특성이 기반이 됨
//     -> 과정1) 루트를 기반으로 값을 검사
//        과정2) 값이 작으면 왼쪽루트로.. 크면 오른쪽 루트로
//        과정3) 이 짓을 재귀를 통해 반복... 값이 도중에 나오면.. 또 경우의 수를 따짐 아니면 null 
//        과정4) 삭제할 노드의 자식노드가 몇개냐?
//               -> 0개 : 삭제할 노드의 부모 노드를 찾아서 link를 끊고, 메모리 반환하기
//                  1개 : 삭제할 노드의 부모 노드를 찾아서, 노드 삭제후, 그 노드의 남은 자식노드를 부모노드의 link에 연결 (어차피 재귀를 통해 어디 방향 link로 들어갈지 답 나옴)
//                  2개 : 삭제할 노드의 자식들중 좌, 우의 근사값(= 리프노드) 중 하나를 골라서, 값을 이전시키고 남은 리프노드 찌꺼기 삭제후 메모리 반환

//   # 이진 검색트리 삭제 알고리즘
//     1. 삭제하려는 노드가 리프(말단 노드)일 경우
//        : 말단 노드의 부모 노드를 찾아서 link를 끊음
//     2. 삭제하려는 노드가 하나의 왼쪽이나 오른쪽 자식을 가지고 있는 경우
//        : 노드는 삭제하고, 그 트리가 가지는 자식들인 서브 트리는 삭제된 노드의 부모 노드에 붙여줌 
//          -> 재귀적 방법으로 이를 역참조한 값에 대입해줌
//     3. 삭제하려는 노드가 두 개의 자식을 모두 가지고 있는 경우
//        : 삭제노드와 가장 근사값을 가진 노드값을 삭제할 노드위치의 값으로 대입 (= 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값)
//          -> (중요!) 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값.. 이들은 결과적으로 '리프노드'로 자식이 없음
//              -> 결과적으로 리프노드의 값을 삭제할 노드의 값으로 옮김 
//                 (= 결과적으로 삭제할 녀석은 리프노드를 의미함 -> 사실상 값을 이식 + 리프노드 삭제하는 경우1의 문제가 됨)
treeNode* removeNode(treeNode* t, element data) {
    treeNode* temp = NULL;

    // 해당 tree노드가 위치한 주소값이 있다면?
    if (t) {

        // 삭제할 값 노드가 루트에 존재함을 확인
        //  -> 루트에 없으면, 재귀를 통해 dfs방식으로 탐색해서 진행
        if (data == t->value) {

            // 경우1) 노드가 리프인 경우 (= left, right가 가르키는 노드주소 없음)
            if (t->left == NULL && t->right == NULL) {
                free(t);
                return NULL;
            }
            // 경우2, 3) 노드가 리프가 아니라 자식을 가질수 있는 경우 
            else {
                // 경우2 - 1) 해당 노드의 오른쪽에만 자식만 있음(= left만 null)
                // -> 해당 right의 주소값을 tmp에 대입하고, 해당 노드의 메모리할당을 해제후 해당 노드를 리턴
                //    -> 그렇게 하면, 그 이전 노드의 left나 right로 연결되는 노드의 주소값이 제거되는 노드의 유일한 자식노드로 연결이 되어 이진검색트리 구조가 유지
                if (t->left == NULL) {
                    // (미완)
                    temp = t->right;
                    free(t);
                    return temp;
                }

                // 경우2 - 2)해당 노드의 왼쪽에만 자식만 있음(= right만 null)
                // -> 해당 left의 주소값을 tmp에 대입하고, 해당 노드의 메모리할당을 해제후 해당 노드를 리턴
                //    -> 그렇게 하면, 그 이전 노드의 left나 right로 연결되는 노드의 주소값이 제거되는 노드의 유일한 자식노드로 연결이 되어 이진검색트리 구조가 유지
                if (t->right == NULL) {
                    // (미완)
                    temp = t->left;
                    free(t);
                    return temp;
                }

                // 경우3) 해당 노드의 양쪽에 자식만 있음
                // -> 삭제노드와 가장 근사값을 가진 노드값을 삭제할 노드위치의 값으로 대입 (= 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값 중 더 가까운 녀석을 고르자)
                //   -> (중요!) 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값.. 이들은 결과적으로 '리프노드'로 자식이 없음
                //       -> 결과적으로 리프노드의 값을 삭제할 노드의 값으로 옮김 
                //          (= 결과적으로 삭제할 녀석은 리프노드를 의미함 -> 사실상 값을 이식 + 리프노드 삭제하는 경우1의 문제가 됨)

                // 오른쪽 & 왼쪽 모두 자식이 있어,
                // -> 왼쪽 가장 큰 값 & 오른쪽에서 가장 작은 값의 노드의 주소값를 각각 저장 
                //    (중요!) 이들은 '리프노드'로 자식이 없음
                treeNode* left_close_value = findMax(t->left);
                treeNode* right_close_value = findMin(t->right);
                
                // 각 근사치 중 더 삭제예정 값에 근접한 놈 찾아서..
                // -> 왼쪽에서 가장 큰 값이 더 근접하면, 대체값은 왼쪽에서 가장 큰 값
                if (t->value - left_close_value->value < right_close_value->value - t->value) {
                    temp = left_close_value;
                }
                // -> 오른쪽에서 가장 작은값이 더 근접하면, 대체값은 오른쪽에서 가장 작은 값
                else {
                    temp = right_close_value;
                }

                // 더 가까운 근사치에 있는 노드에 있는 값을 삭제값이 위치한 노드의 값으로 대입해 저장
                t->value = temp->value;

                // '리프노드'로 자식이 없어 사실상 값 이주를 끝내 찌꺼기만 남은 노드를 제거해야함
                //  -> temp값이 왼쪽 가장 큰 값 & 오른쪽에서 가장 작은 값인지를 조건으로
                //     -> '왼쪽 가장 큰 값'을 이주했으면, 삭제값이 위치한 노드의 왼편 노드를 시작으로 왼쪽 가장 큰 값이 존재했던 원래 노드를 이진검색트리 논리로 찾아 추적해 삭제하도록 재귀삭제문 작성
                if (temp = left_close_value) {
                    t->left = removeNode(t->left, temp->value);
                }
                //     -> '오른쪽에서 가장 작은값'을 이주했으면, 삭제값이 위치한 노드의 오른편 노드를 시작으로 오른쪽 가장 작은 값이 존재했던 원래 노드를 이진검색트리 논리로 찾아 추적해 삭제하도록 재귀삭제문 작성
                else {
                    t->right = removeNode(t->right, temp->value);
                }


            }
        }
        // 루트에 값이 없으면, 재귀를 통해 dfs방식으로 탐색해서 진행
        else {

            // 해당 노드의 값이 검색값보다 크냐? 작냐에 따라 left, right로 노드이동
            if (data < t->value) {
                t->left = removeNode(t->left, data);
            }
            else/* data > t->value */ {
                t->right = removeNode(t->right, data);
            }
        }
    }

    // 삭제를 하게되면, 삭제한 노드의 주소 리턴.. 아니면 NULL 리턴
    return t;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------



int main() {

    srand((unsigned int)time(NULL));

    // 동적배열의 위치를 받아낼 포인터
    int* array_address = NULL;
    // 동적배열의 길이값
    int array_num = 0;

    treeNode* root = NULL;

    printf("----------------------------------------------------------------------------\n");
    printf("[이진검색트리]를 만들고 관련 기능을 수행해봅니다. 배열 크기에 해당하는 값을 입력하면,\n 배열의 값은 1~ 배열크기 * 3 중 랜덤 생성 됩니다.");
    printf("----------------------------------------------------------------------------\n\n");

    printf("검색의 대상이 되는 배열의 크기를 입력하세요 (0이외의 값을 좀 부탁드려용~) : ");
    scanf_s("%d", &array_num);

    if (array_num == 0) {
        printf("배열의 크기가 0이므로 시스템을 종료합니다\n");
        exit(0);
    }

    // 동적할당 시행
    array_address = (int*)calloc(array_num, sizeof(int));

    // 동적할당한 메모리 각각의 값이 정렬된 효과를 낳게, 랜덤한 값이 들어갈수 있게하되, 무조건 자기 이전의 값에 추가값을 더하는 식으로 설계
    for (int i = 0; i < array_num; i++) {

        *(array_address + i) = rand() % (array_num * 3) + 1;

        printf("%d ", *(array_address + i));
        root = addNode(root, *(array_address + i));
    }

    printf("\n\n값 입력이 완료되었습니다.\n");
    printf("hint : 가장 작은 값 = %d, 가장 높은 값 = %d)\n\n", *(array_address), *(array_address + array_num - 1));

    LinkedQueueType* queue_BFS = NULL;
    queue_BFS = QueueInit1(queue_BFS);

    Enqueue(queue_BFS, root);

    printf("\nBFS(너비우선탐색)\n");
    displayBFS(queue_BFS);

    printf("\n전위 순회\n");
    displayPreOrder(root);

    printf("\n\n중위 순회\n");
    displayInOrder(root);

    printf("\n\n후위 순회\n");
    displayPostOrder(root);

    freeTree(root);

    return 0;
}
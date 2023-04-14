// 스택(stack)
//  : '창고에 물건을 쌓아두듯' 자료를 한 곳에 쌓아두는 자료구조 유형
//    (= 가장 나중에 들어온 녀석이 가장 나중에 나가는 구조)

//  # 후입선출 LIFO 
//    : Last-In, First-Out  

//  # stack 구조체 ( 구성 요소 )
// 
//    typedef int stack_element;

//    typedef struct {
//        stack_element* data; // 스택에 넣은 값들의 공간 (= 이 포인터변수는 동적할당 메서드를 통해 return값을 받게 될 시... 그 위치를 저장하기 위한 용도)
//        int capacity;        // 스택의 총 저장 용량 갯수
//        int top;             // 현재 저장된 자료 개수
//    } StackType;

//  # Stack ADT
//    - init_stack(stack) : 스택의 구성요소 초기화
//    - is_empty(stack)   : 스택 안에 값이 없는지 확인
//    - is_full(stack)    : 스택이 가득 찼는지를 확인
//    - push(stack, item) : 스택 자료의 맨 위에 요소 item 추가
//    - pop(stack)        : 스택의 맨 위에 있는 요소를 삭제하지 않고 반환


// stack ADT 전부 구현해보자 (double linked list 사용해서..)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함

typedef int Stack_DoublelistElement;

// (주의!) 구조체가 재정의 된 이름이 있을 때 [재정의명 != 원구조체명]인 경우, 멤버변수로 스스로의 포인터변수명이 재정의된 구조체명을 기준으로 삼는다면?
//  -> 이를 여러번 역참조하기 시작하면 없는 구조체로 인식한다..
//     -> [결론 : 구조체의 멤버변수 중 스스로의 포인터변수를 자료형으로 가져가는 경우가 있다면, 반드시 이름을 원구조체명으로 적는게 안정성이 높다!]
typedef struct Stack_DoublelistNode
{
    Stack_DoublelistElement data;
    struct Stack_DoublelistNode* Llink;
    struct Stack_DoublelistNode* Rlink;
} Stack_DoubleListNode;

typedef struct
{
    Stack_DoubleListNode* head; // 스택에 넣은 값들이 위치하는 메모리 주소의 시작점 (= 이 포인터변수는 동적할당 메서드를 통해 return값을 받게 될 시... 그 위치를 저장하기 위한 용도)
    int capacity;        // 스택의 총 저장 용량 갯수
    int top;             // 현재 저장된 자료 개수
}StackType;

// stack 초기화
StackType* init_stack(StackType* stack);

// 해당 stack안에 값이 없는지 확인
int is_empty(StackType* stack);

// 해당 stack이 가득찼는지 여부
int is_full(StackType* stack);

// 해당 stack에 값을 추가 (값이 들어간 노드 바로 다음 노드)
void push(StackType* stack, Stack_DoublelistElement item);

// stack에서 값을 제거 return값은 stack의 요소 (값이 있는 마지막 노드)
void pop(StackType* stack);

// 해당 메모리 위치에 존재하는 stack 메모리 전체 해제
void free_stack(StackType* stack);

// 해당 메모리 위치에 존재하는 stack 내용 확인
void print(StackType* stack);

Stack_DoubleListNode* DoubleInitial(Stack_DoubleListNode* head);                                    // done
Stack_DoubleListNode* DoubleInsertLast(Stack_DoubleListNode* head, Stack_DoublelistElement item);   // done
void DoubleDeleteLast(Stack_DoubleListNode* head);                                                  // done
void DoubleDisplay(Stack_DoubleListNode* head);                                                     // done 
void FreeDoubleList(Stack_DoubleListNode* head);                                                    // done

int main(void)
{

    StackType* stack_address1 = NULL;
    stack_address1 = init_stack(stack_address1);

    for (int i = 1; i <= stack_address1->capacity; i++)
    {

        push(stack_address1, i * 3);
    }

    print(stack_address1);

    for (int i = 1; i <= stack_address1->capacity; i++)
    {

        pop(stack_address1);
    }

    print(stack_address1);

    return 0;
}

// stack 초기화
StackType* init_stack(StackType* stack)
{

    // stack 구조체가 위치하는 메모리주소를 저장함
    stack = (StackType*)malloc(sizeof(StackType));

    // top : 스택 현재 보유 수량
    stack->top = 0;
    // capacity : 스택 총 보유 가능 수량
    stack->capacity = 5;
    // head : 스택에 넣은 값들이 위치할 '이중연결리스트'의 메모리 주소의 시작점 head주소 (= 이 포인터변수는 동적할당 메서드를 통해 return값을 받게 될 시... 그 위치를 저장하기 위한 용도)
    stack->head = DoubleInitial(stack->head);

    return stack;
}

// 해당 stack안에 값이 없는지 확인 (있으면 0, 없으면 1)
int is_empty(StackType* stack)
{

    if (stack->top == 0)
    {
        return 1;
    }

    return 0;
}

// 해당 stack이 가득찼는지 여부 (여유 있으면 0, 가득찼으면 1)
int is_full(StackType* stack)
{

    // (중요) stack의 값이 위치하는 메모리 주소는 값이 추가된 후 top++가 된다는 점을 기억해야함
    // (= capacity가 3이라 치면, 마지막 값의 주소 = '시작주소' + capacity - 1 = '시작주소' + capacity - 1)
    if (stack->top >= stack->capacity)
    {
        return 1;
    }

    return 0;
}

// 해당 stack에 값을 추가 (값이 들어간 노드 바로 다음 노드에 추가)
void push(StackType* stack, Stack_DoublelistElement item)
{

    // 값을 추가하기 전 stack의 공간이 가득찼는지 확인
    int result = is_full(stack);

    // stack 공간에 여유가 있다면? 값 추가진행
    if (result == 0)
    {
        stack->head = DoubleInsertLast(stack->head, item);

        // top의 값 = double 연결리스트 총 노드 값 저장하는 head의 데이터값 (여기서는 top을 통해 메모리에 접근하지 않으므로, )
        (stack->top) = stack->head->data;

        printf("메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값 = %d \n", stack, stack->top, stack->head->Rlink->data);
    }
    else if (result == 1)
    {

        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 이미 가지고 있는 %d개 공간을 전부 채웠습니다.\n", stack, stack->capacity);
    }
}

// stack에서 값을 제거 return값은 stack의 요소 (값이 있는 마지막 노드)
void pop(StackType* stack)
{

    // 값을 추가하기 전 stack의 공간이 비었는지 확인
    int result = is_empty(stack);

    // 안 비었으면 값 
    if (result == 0)
    {
        int delete_int = stack->head->Rlink->data;

        DoubleDeleteLast(stack->head);

        // top의 값 = double 연결리스트 총 노드 값 저장하는 head의 데이터값
        (stack->top) = stack->head->data;
        printf("(STACK 값 제거) : 메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값인 %d를 제거했습니다. \n", stack, stack->top + 1, delete_int);
        printf(" -> 메모리 주소 %d부터 할당된 stack구조의 현재 마지막 공간 %d번째 공간의 값 = %d \n", stack, stack->top, stack->head->Rlink->data);
    }
    else if (result == 1)
    {

        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 입력된 값이 없습니다.\n", stack);
    }

}

// stack 메모리 해제
void free_stack(StackType* stack)
{

    // 먼저 stack의 값이 더블링크드 리스트의 
    FreeDoubleList(stack->head);
    // 그 다음 stack 구조체 위치의 메모리 해제
    free(stack);
}

// stack 내용 확인
void print(StackType* stack)
{

    int result = is_empty(stack);

    if (result == 0)
    {

        printf("현재 stack인 double linked list 한계 공간크기 : %d\n", stack->capacity);
        printf("현재 stack에 입력된 값들 : ");

        DoubleDisplay(stack->head);

        printf("\n");

    }
    else
    {
        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 입력된 값이 없습니다.\n", stack);
    }

}

//-------------------------------------------------------------------------------------------------------------------------
// 더블링크드 리스트 head 노드 생성(= 사실상 입력절차)
Stack_DoubleListNode* DoubleInitial(Stack_DoubleListNode* head)
{

    Stack_DoubleListNode* head_node = (Stack_DoubleListNode*)malloc(sizeof(Stack_DoubleListNode));

    // 헤드의 데이터 값은 노드의 총 노드수 (만들때는 당연히 총 노드수는 0)
    head_node->data = 0;
    head_node->Llink = head_node;
    head_node->Rlink = head_node;

    printf_s("(dl 생성 초기화) : %d에 더블링크드 리스트의 헤드노드가 추가되었습니다. 해당 주소값은 %d에 위치에 기록되어 있습니다. \n", head_node, &head);

    head = head_node;

    return head;
}

// 해당 head가 가르키는 더블링크드 리스트의 마지막 노드로 item값 추가
Stack_DoubleListNode* DoubleInsertLast(Stack_DoubleListNode* head, Stack_DoublelistElement item)
{

    Stack_DoubleListNode* insert_last_node = (Stack_DoubleListNode*)malloc(sizeof(Stack_DoubleListNode));

    if (insert_last_node == NULL)
    {
        printf("메모리 부족");
        return NULL;
    }

    // 이중연결리스트를 통해 stack을 구현하는 것이기에, 마지막의 오른쪽 값은 아무것도 가르키는게 없어야 함 (= 단 head는 Llink로 마지막에 접근 가능)
    insert_last_node->Rlink = NULL;
    insert_last_node->data = item;


    // (case1) 현재 리스트에 존재하는 노드가 헤더노드 혼자일 경우? (= 헤더노드의 양link가 스스로를 가리킴)
    //  -> 헤더노드의 양 link의 값을 insert_last_node 주소값으로 + insert_first_node 오른쪽 주소도 head를 가리키게 함
    //  -> 마지막 노드의 왼쪽노드(= 이전 노드)는 NULL로 입력
    if (head->Llink == head && head->Rlink == head)
    {

        insert_last_node->Llink = NULL;
        head->Llink = insert_last_node;
        head->Rlink = insert_last_node;
    }

    // (case2) 해당 더블링크드 리스트에 다른 노드들이 있는 경우 (= 헤드노드의 오른쪽link가 다른 노드를 가르킬경우)
    //  -> head의 Rlink 정보 변경
    //  -> 마지막 노드의 왼쪽노드(= 이전 노드)는 head에서 Llink를 통해 접근가능한 기존 마지막 노드의 주소로
    //  -> 마지막 노드 스스로의 왼쪽노드 주소도 예전 마지막 노드의 주소값으로 갱신
    else if (head->Rlink != head)
    {
        insert_last_node->Llink = head->Rlink;
        head->Rlink->Rlink = insert_last_node;
        head->Rlink = insert_last_node;
    }

    // 헤드의 데이터 값은 노드의 총 노드수
    head->data++;

    return head;
}

// 해당 head가 가르키는 더블링크드 리스트의 마지막 노드 삭제
void DoubleDeleteLast(Stack_DoubleListNode* head)
{

    printf_s("\n\n------------------------------[DoubleDeleteLast 시작!]------------------------------\n\n");

    Stack_DoubleListNode* delete_node = head->Rlink;

    // (case1) 현재 리스트에 존재하는 노드가 헤더노드 혼자일 경우? (= 헤더노드의 양link가 스스로를 가리킴)
    //  -> 경고를 끝내기
    if (head->Llink == head && head->Rlink == head && head->data == 0)
    {

        printf_s("(경고) : 해당 더블링크드 리스트에는 헤드 외에 다른 노드가 없어서 삭제가 불가능합니다.\n");
    }
    // (case2) 해당 더블링크드 리스트에 1번째 노드만 있는 경우 (= 자기 왼쪽에 아무것도 잡히는게 없음)
    //  -> head의 L, Rlink가 초기화처럼 스스로의 주소를 받으면 됨
    else if (delete_node->Llink == NULL && head->data == 1)
    {

        // head의 왼 오른 노드정보 다시 head로 초기화
        head->Llink = head;
        head->Rlink = head;

        printf_s("해당 리스트의 주소 %d에 위치한 마지막 남은 노드의 data값 %d 삭제완료! \n", delete_node, delete_node->data);
        free(delete_node);
    }

    // (case3) 해당 더블링크드 리스트에 2개 이상의 노드 존재 (= 1번째노드의 오른쪽link가 head를 가르킬경우 or head의 data가 1초과)
    //  -> head의 Rlink가 새로 마지막 노드가 될 기존 마지막 노드의 Llink의 주소값을 받으면 됨
    //  -> 새로 마지막 노드가 될 기존 마지막 노드의 Llink->Rlink가 NULL로 변경
    else if (delete_node->Rlink != head && head->data > 1)
    {

        delete_node->Llink->Rlink = NULL;
        head->Rlink = delete_node->Llink;

        printf_s("해당 리스트의 주소 %d에 위치한 마지막 노드의 %d번째 연결리스트 data값 %d 삭제완료! \n", delete_node, head->data, delete_node->data);
        free(delete_node);
    }

    // 헤드의 데이터 값은 노드의 총 노드수
    head->data--;
    printf_s("해당 리스트의 주소 %d에 위치한 노드 총 개수 : %d \n", head, head->data);
}

// 더블링크드 리스트의 모든 노드의 data값 순차적으로 출력(Rlink 따라가면 됨)
void DoubleDisplay(Stack_DoubleListNode* head)
{

    printf_s("\n\n------------------------------[주소값 %d DoubleDisplay 시작!]------------------------------\n\n", head);

    if (head->data == 0)
    {

        printf_s("(경고) : 해당 더블링크드 리스트에는 헤드 외에 다른 노드가 없습니다.\n");

    }
    else
    {

        printf("해당 dlist의 노드개수 %d개인 리스트의 값들 출력 : ", head->data);

        Stack_DoubleListNode* current_node = head->Llink;

        printf("head -> ");

        for (int i = 1; i <= head->data; i++)
        {  // 데이터끼리만 순환 증명

            printf_s("%3d -> ", current_node->data);
            current_node = current_node->Rlink;
        }

        printf("head\n");
    }
}

// 동적할당한 더블링크드 리스트 메모리 할당 해제
void FreeDoubleList(Stack_DoubleListNode* head)
{

    printf_s("\n\n------------------------------[주소값 %d FreeDoubleList 시작!]------------------------------\n\n", head);

    printf_s("(해당 dlist의 노드의 개수) : %d개 \n", head->data);

    Stack_DoubleListNode* free_address = head;

    // 해당 더블링크드 리스트에 헤더 외의 노드가 하나라도 있다면?
    //  -> 하나씩 따라가며 그 개수에 해당하는 노드 해제
    if (head->data != 0)
    {

        free_address = free_address->Rlink;

        for (int i = 1; i <= head->data; i++)
        {

            Stack_DoubleListNode* next_address = free_address->Rlink;

            printf_s("해당 dlist %d번째 노드 해제 : 노드의 값이 %d이며 주소값 %d부터 시작하는 해당 노드에 할당된 메모리 영역이 해제되었습니다.\n", i, free_address->data, free_address);

            free(free_address);
            free_address = next_address;
        }
    }

    // 해당 더블링크드 리스트에 헤더 밖에 노드가 없는 상태면(해제를 하던, 원래부터 그렇던), 헤더노드도 해제
    printf_s("\n-----------------[FreeDoubleList 완료] 주소값 %d부터 시작하는 해당 더블 dlist의 헤더노드에 할당된 메모리 영역이 해제되었습니다.---------------\n", free_address);
    free(free_address);
}

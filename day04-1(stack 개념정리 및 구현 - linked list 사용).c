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
typedef struct Stack_DoublelistNode {
    Stack_DoublelistElement data;
    struct DoublelistNode* Llink;
    struct DoublelistNode* Rlink;
} Stack_DoubleListNode;

typedef struct {
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

DoubleListNode* DoubleInitial(DoubleListNode* head);                              // done
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoublelistElement item);  // done
void DoubleDeleteFirst(DoubleListNode* head);                                     // done
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2);       // done
void DoubleDisplay(DoubleListNode* head);                                         // done 
void DoubleDisplayReverse(DoubleListNode* head);                                  // done
void FreeDoubleList(DoubleListNode* head);                                        // done

int main(void) {

    StackType* stack_address1 = NULL;
    stack_address1 = init_stack(stack_address1);
    
    for (int i = 1; i <= stack_address1->capacity; i++) {

        push(stack_address1, i * 3);
    }

    print(stack_address1);

    for (int i = 1; i <= stack_address1->capacity; i++) {

        pop(stack_address1);
    }

    print(stack_address1);

	return 0;
}

// stack 초기화
StackType* init_stack(StackType* stack) {

    // stack 구조체가 위치하는 메모리주소를 저장함
    stack = (StackType*) malloc(sizeof(StackType));

    // top : 스택 현재 보유 수량
    stack->top = 0; 
    // capacity : 스택 총 보유 가능 수량
    stack->capacity = 5; 
    // head : 스택에 넣은 값들이 위치하는 메모리 주소의 시작점 (= 이 포인터변수는 동적할당 메서드를 통해 return값을 받게 될 시... 그 위치를 저장하기 위한 용도)
    stack->head = (Stack_DoubleListNode*) malloc(stack->capacity * sizeof(Stack_DoubleListNode));
    // element data[s->capacity];

    return stack;
}

// 해당 stack안에 값이 없는지 확인 (있으면 0, 없으면 1)
int is_empty(StackType* stack) {

    if (stack->top == 0) {
        return 1;
    }

    return 0;
}

// 해당 stack이 가득찼는지 여부 (여유 있으면 0, 가득찼으면 1)
int is_full(StackType* stack) {

	// (중요) stack의 값이 위치하는 메모리 주소는 값이 추가된 후 top++가 된다는 점을 기억해야함
	// (= capacity가 3이라 치면, 마지막 값의 주소 = '시작주소' + capacity - 1 = '시작주소' + capacity - 1)
    if (stack->top >= stack->capacity) {
        return 1;
    }

    return 0;
}

// 해당 stack에 값을 추가 (값이 들어간 노드 바로 다음 노드에 추가)
void push(StackType* stack, Stack_DoublelistElement item) {

    // 값을 추가하기 전 stack의 공간이 가득찼는지 확인
    int result = is_full(stack);

    // stack 공간에 여유가 있다면? 값 추가진행
    if (result == 0) {
			
        // (중요) stack의 값이 위치하는 메모리 주소는 값이 추가된 후 top++가 된다는 점을 기억해야함 
        // (= capacity가 3이라 치면, 마지막 값의 주소 = '시작주소' + capacity - 1 = '시작주소' + capacity - 1)

        // stack에 넣고자 하는 값 item은 값들이 위치하는 메모리 주소의 시작값 head를 기준으로 stack에 존재하는 값들의 현 개수 - 1 를 더해서 얻은 메모리주소를 역참조한 값으로 둔다
        *(stack->head + stack->top) = item;
        printf("메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값 = %d \n", stack, stack->top, *(stack->head + stack->top));

        // 새로운 값 메모리 주소위치 = head + top - 1인 이유가 top의 값이 item이 들어간 이후에 연산이 되는 이유
        (stack->top)++;

        // (보너스) realloc을 통해, 현재의 stack이 쓸데없이 메모리를 많이/적게 먹는 경우 알맞은 수준으로 메모리 할당을 변경 가능 (= 가변 할당을 통한 메모리 관리 가능)
        //  -> push를 새로 할 때마다, stack요소를 저장하는데 쓸 메모리의 할당하는 양을 늘려서 할당하고 그 시작주소 재대입 
        stack->head = (stack_element*) realloc(stack->head, (sizeof(stack_element) * stack->top));
    }
    else if (result == 1) {

        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 이미 가지고 있는 %d개 공간을 전부 채웠습니다.\n", stack, stack->capacity);
    }
}

// stack에서 값을 제거 return값은 stack의 요소 (값이 있는 마지막 노드)
void pop(StackType* stack) {

    // 값을 추가하기 전 stack의 공간이 비었는지 확인
    int result = is_empty(stack);

    // 안 비었으면 값 
    if (result == 0) {

         // (중요) stack의 값이 위치하는 메모리 주소는 값이 추가된 후 top++가 된다는 점을 기억해야함 
         // (= capacity가 3이라 치면, 마지막 값의 주소 = '시작주소' + capacity - 1 = '시작주소' + capacity - 1)
         //  -> '시작주소' + capacity - 1 때문에 제거할 값을 찾기 위해서 먼저 top을 -1 처리해야 함
         (stack->top)--;
         printf("메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값인 %d를 제거했습니다. \n", stack, stack->top, *(stack->head + stack->top));
         
         // 해당 위치에 존재하는 값을 제거할 목적으로 0대입 (어차피 top의 값이 이 위치의 접근가능 여부를 결정함 = push할떄 새로운 값으로 대입되므로 안 해줘도 됨)
         *(stack->head + stack->top) = 0;

         // (보너스) realloc을 통해, 현재의 stack이 쓸데없이 메모리를 많이/적게 먹는 경우 알맞은 수준으로 메모리 할당을 변경 가능 (= 가변 할당을 통한 메모리 관리 가능)
         //  -> push를 새로 할 때마다, stack요소를 저장하는데 쓸 메모리의 할당하는 양을 줄여서 할당하고 그 시작주소 재대입 
         stack = realloc(stack, (sizeof(stack_element) * stack->top));
    }
    else if (result == 1) {

        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 입력된 값이 없습니다.\n", stack);
    }

}

// stack 메모리 해제
void free_stack(StackType* stack) {
    
	// 먼저 stack의 값이 위치한 주소의 메모리 할당 해제
    free(stack->head);
	// 그 다음 stack 구조체 위치의 메모리 해제
    free(stack);
}

// stack 내용 확인
void print(StackType* stack) {
    
    int result = is_empty(stack);

    if (result == 0) {

        printf("현재 stack의 개수 : %d\n", stack->capacity);
        printf("현재 stack에 입력된 값들 : ");

        for (int i = 0; i < stack->top; i++) {

            printf("%d ", *(stack->head + i));
        }

        printf("\n");

    }
    else{
        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 입력된 값이 없습니다.\n", stack);
    }

}

//-------------------------------------------------------------------------------------------------------------------------
// 더블링크드 리스트 head 노드 생성(= 사실상 입력절차)
DoubleListNode* DoubleInitial(DoubleListNode* head) {

    DoubleListNode* head_node = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    // 헤드의 데이터 값은 노드의 총 노드수 (만들때는 당연히 총 노드수는 0)
    head_node->data = 0;
    head_node->Llink = head_node;
    head_node->Rlink = head_node;

    printf_s("(dl 생성 초기화) : %d에 더블링크드 리스트의 헤드노드가 추가되었습니다. 해당 주소값은 %d에 위치에 기록되어 있습니다. \n", head_node, &head);

    head = head_node;

    return head;
}

// 해당 head가 가르키는 더블링크드 리스트의 1번째 노드로 item값 추가
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoublelistElement item) {

    DoubleListNode* insert_first_node = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    if (insert_first_node == NULL) {
        printf("메모리 부족");
        return NULL;
    }

    insert_first_node->data = item;
    insert_first_node->Llink = head;

    // (case1) 현재 리스트에 존재하는 노드가 헤더노드 혼자일 경우? (= 헤더노드의 양link가 스스로를 가리킴)
    //  -> 헤더노드의 양 link의 값을 insert_first_node의 주소값으로 + insert_first_node 오른쪽 주소도 head를 가리키게 함
    if (head->Llink == head && head->Rlink == head) {

        head->Llink = insert_first_node;
        head->Rlink = insert_first_node;

        insert_first_node->Rlink = head;
    }

    // (case2) 해당 더블링크드 리스트에 다른 노드들이 있는 경우 (= 헤드노드의 오른쪽link가 다른 노드를 가르킬경우)
    //  -> insert_first_node 오른쪽 주소가 head의 오른쪽link를 가지게 함 + 헤더노드의 오른쪽 link값을 insert_first_node로 변경 + 기존 1번째노드의 왼쪽 Link값을 insert_first_node의 주소값으로 수정
    if (head->Rlink != head) {

        // 기존에 1번째 노드였던 노드의 주소값(= 굴러들어온 노드에 의해 2번째로 밀려날 예정)
        DoubleListNode* move_to_2nd_node = head->Rlink;

        insert_first_node->Rlink = head->Rlink;
        move_to_2nd_node->Llink = insert_first_node;
        head->Rlink = insert_first_node;
    }

    // 헤드의 데이터 값은 노드의 총 노드수
    head->data++;

    return head;
}

// 해당 head가 가르키는 더블링크드 리스트의 1번째 노드 삭제
void DoubleDeleteFirst(DoubleListNode* head) {

    DoubleListNode* delete_node = head->Rlink;

    printf_s("\n\n------------------------------[DoubleDeleteFirst 시작!]------------------------------\n\n");

    // (case1) 현재 리스트에 존재하는 노드가 헤더노드 혼자일 경우? (= 헤더노드의 양link가 스스로를 가리킴)
    //  -> 경고를 끝내기
    if (head->Llink == head && head->Rlink == head && head->data == 0) {

        printf_s("(경고) : 해당 더블링크드 리스트에는 헤드 외에 다른 노드가 없어서 삭제가 불가능합니다.\n");
    }
    // (case2) 해당 더블링크드 리스트에 1번째 노드만 있는 경우 (= 헤드노드의 오른쪽link의 오른쪽link값이 head가 저장하는 주소값을 가르킬경우 or head의 data가 1)
    //  -> head의 L, Rlink가 초기화처럼 스스로의 주소를 받으면 됨
    else if (delete_node->Rlink == head && head->data == 1) {

        // head의 왼 오른 노드정보 다시 head로 초기화
        head->Llink = head;
        head->Rlink = head;

        printf_s("해당 리스트의 주소 %d에 위치한 1번째 노드의 data값 %d 삭제완료! \n", delete_node, delete_node->data);
        free(delete_node);
    }

    // (case3) 해당 더블링크드 리스트에 2개 이상의 노드 존재 (= 1번째노드의 오른쪽link가 head를 가르킬경우 or head의 data가 1초과)
    //  -> head의 Rlink가 기존의 1번째 노드의 Rlink의 주소값을 받으면 됨
    else if (delete_node->Rlink != head && head->data > 1) {
        head->Rlink = delete_node->Rlink;

        printf_s("해당 리스트의 주소 %d에 위치한 1번째 노드의 data값 %d 삭제완료! \n", delete_node, delete_node->data);
        free(delete_node);
    }

    // 헤드의 데이터 값은 노드의 총 노드수
    head->data--;
    printf_s("해당 리스트의 주소 %d에 위치한 노드 총 개수 : %d \n", head, head->data);
}

// 두개의 더블링크드 리스트 head1, head2 결합
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2) {

    // (case1) 1번째 더블링크드 리스트의 노드가 헤더밖에 없다면?
    // -> concat헤드의 주체는 head2로 고정 (head2도 마찬가지라도 상관이 없음)
    if (head1->data == 0) {
        return head2;
    }

    // (case2) 2번째 더블링크드 리스트의 노드가 헤더밖에 없다면?
    // -> concat헤드의 주체는 head1로 고정
    if (head2->data == 0) {
        return head1;
    }

    // (중요!) 1번 연결리스트의 head의 data에 표기된 노드의 숫자 + 2번 연결리스트의 head의  data에 표기된 노드의 숫자가 둘 다 0이 아니면 concat개시

    // current_head1_index : 1번 연결리스트의 마지막 노드의 주소를 알아내기 위한 ListNode의 주소값을 받는 포인터변수
    DoubleListNode* current_head1_index = head1;

    // current_head1_index(현재의 노드 주소값)에 위치한 Rlink가 head1이 나올때까지(= current_head1_index가 마지막 노드의 주소값을 나타낼까지)... 계속 수행
    for (int i = 1; i <= head1->data; i++) {

        printf_s("다음주소.. %d -> %d로..\n", current_head1_index, current_head1_index->Rlink);

        // current_head1_index(현재의 노드 주소값)에 위치한 Rlink가 head1의 주소값을 가르키지 않는이상 current_head1_index->Rlink를 current_head1_index의 값으로 갱신
        if (current_head1_index->Rlink == head1) {
            break;
        }
        else {
            current_head1_index = current_head1_index->Rlink;
        }
    }

    // current_head2_index : 2번 연결리스트의 마지막 노드의 주소를 알아내기 위한 ListNode의 주소값을 받는 포인터변수
    DoubleListNode* current_head2_index = head2;

    // current_head2_index(현재의 노드 주소값)에 위치한 Rlink가 head2이 나올때까지(= current_head2_index가 마지막 노드의 주소값을 나타낼까지)... 계속 수행
    for (int i = 1; i <= head2->data; i++) {

        printf_s("다음주소.. %d -> %d로..\n", current_head2_index, current_head2_index->Rlink);

        // current_head2_index(현재의 노드 주소값)에 위치한 Rlink가 head2의 주소값을 가르키지 않는이상 current_head1_index->Rlink를 current_head2_index의 값으로 갱신
        if (current_head2_index->Rlink == head2) {
            break;
        }
        else {
            current_head2_index = current_head2_index->Rlink;
        }
    }

    // [변경해줘야 할 녀석들] head1 Llink, head1 1번째노드 Llink, head1 마지막노드 Rlink, head2 1번째노드 Llink, head2 마지막노드 Rlink,

    // 1. head1이었던 current_head1_index(현재의 노드 주소값)에 위치한 link값을 2번 연결리스트의 head가 나타내는 1번째노드의 주소값인 head2->Rlink로 대입
    current_head1_index->Rlink = head2->Rlink;

    // 2. head2의 1번째 노드의 Llink값도 head의 마지막 노드의 주소값으로 갱신
    DoubleListNode* second_dlist_1st_node = head2->Rlink;
    second_dlist_1st_node->Llink = current_head1_index;

    // 3. 1번 연결리스트의 헤드 노드의 왼쪽link 주소값을 2번 연결리스트 마지막노드의 주소로 갱신
    head1->Llink = current_head2_index;

    // 4. 2번 연결리스트 마지막노드의 오른쪽link 1번 연결리스트의 헤드 노드의 주소로 갱신
    current_head2_index->Rlink = head1;

    // 총 노드수 갱신하기
    head1->data = head1->data + head2->data;

    // 더이상 연결대상의 이전헤드는 사용안함
    free(head2);
    head2 = NULL;

    printf_s("----------------------------[concat 붙이기 완료] : head1의 마지막 link값 = %d -> %d(%d)로.. 변경-----------------------------\n", head1, current_head1_index->Rlink);

    // 1번, 2번 연결이 완료된 연결리스트의 시작점인 1번 연결리스트의 헤드값을 받은 concat_head리턴
    return head1;

}

// 더블링크드 리스트의 모든 노드의 data값 순차적으로 출력(Rlink 따라가면 됨)
void DoubleDisplay(DoubleListNode* head) {

    printf_s("\n\n------------------------------[주소값 %d DoubleDisplay 시작!]------------------------------\n\n", head);

    if (head->data == 0) {

        printf_s("(경고) : 해당 더블링크드 리스트에는 헤드 외에 다른 노드가 없습니다.\n");

    }
    else {

        printf("해당 dlist의 노드개수 %d개인 리스트의 값들 출력 : ", head->data);

        DoubleListNode* current_node = head->Rlink;

        printf("head -> ");

        for (int i = 1; i <= head->data + 2; i++) {  // 데이터끼리만 순환 증명

            printf("%3d -> ", current_node->data);
            current_node = current_node->Rlink;
        }

        printf("head\n");
    }
}

// 더블링크드 리스트의 모든 노드의 data값 역순으로 출력 (Llink 따라가면 됨)
void DoubleDisplayReverse(DoubleListNode* head) {

    printf_s("\n\n------------------------------[주소값 %d DoubleDisplayReverse 시작!]------------------------------\n\n", head);

    if (head->data == 0) {

        printf_s("(경고) : 해당 더블링크드 리스트에는 헤드 외에 다른 노드가 없습니다.\n");

    }
    else {

        printf("해당 dlist의 노드개수 %d개인 리스트의 값들 출력 : ", head->data);

        DoubleListNode* current_node = head->Llink;

        printf("head -> ");

        for (int i = 1; i <= head->data + 2; i++) {  // 데이터끼리만 순환 증명

            printf("%3d -> ", current_node->data);
            current_node = current_node->Llink;
        }

        printf("head\n");
    }

}

// 동적할당한 더블링크드 리스트 메모리 할당 해제
void FreeDoubleList(DoubleListNode* head) {

    printf_s("\n\n------------------------------[주소값 %d FreeDoubleList 시작!]------------------------------\n\n", head);

    printf("(해당 dlist의 노드의 개수) : %d개 \n", head->data);

    DoubleListNode* free_address = head;

    // 해당 더블링크드 리스트에 헤더 외의 노드가 하나라도 있다면?
    //  -> 하나씩 따라가며 그 개수에 해당하는 노드 해제
    if (head->data != 0) {

        free_address = free_address->Rlink;

        for (int i = 1; i <= head->data; i++) {

            DoubleListNode* next_address = free_address->Rlink;

            printf("해당 dlist %d번째 노드 해제 : 노드의 값이 %d이며 주소값 %d부터 시작하는 해당 노드에 할당된 메모리 영역이 해제되었습니다.\n", i, free_address->data, free_address);

            free(free_address);
            free_address = next_address;
        }
    }

    // 해당 더블링크드 리스트에 헤더 밖에 노드가 없는 상태면(해제를 하던, 원래부터 그렇던), 헤더노드도 해제
    printf("\n-----------------[FreeDoubleList 완료] 주소값 %d부터 시작하는 해당 더블 dlist의 헤더노드에 할당된 메모리 영역이 해제되었습니다.---------------\n", free_address);
    free(free_address);
}

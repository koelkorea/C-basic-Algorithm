// 스택(stack)
//  : '창고에 물건을 쌓아두듯' 자료를 한 곳에 쌓아두는 자료구조 유형
//    (= 가장 나중에 들어온 녀석이 가장 나중에 나가는 구조)

//  # 후입선출 LIFO 
//    : Last-In, First-Out  

//  # stack 구조체 ( 구성 요소 )
// 
//    typedef int stack_element;

//    typedef struct {
//        stack_element* data; // 스택에 넣은 값들의 공간
//        int capacity; // 스택의 총 저장 용량
//        int top; // 저장된 자료 개수
//    } StackType;

//  # Stack ADT
//    - init_stack(stack) : 스택의 구성요소 초기화
//    - is_empty(stack)   : 스택 안에 값이 없는지 확인
//    - is_full(stack)    : 스택이 가득 찼는지를 확인
//    - push(stack, item) : 스택 자료의 맨 위에 요소 item 추가
//    - pop(stack)        : 스택의 맨 위에 있는 요소를 삭제하지 않고 반환


// stack ADT 전부 구현해보자 (동적할당 사용해서..)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함

typedef int stack_element;
typedef struct {
    stack_element* data; // 스택에 넣은 값들의 공간
    int capacity; // 스택의 총 저장 용량
    int top; // 저장된 자료 개수
}StackType;

// stack 초기화
StackType* init_stack(StackType* stack);

// 해당 stack안에 값이 없는지 확인
int is_empty(StackType* stack);

// 해당 stack이 가득찼는지 여부
int is_full(StackType* stack);

// 해당 stack에 값을 추가 (값이 들어간 노드 바로 다음 노드)
void push(StackType* stack, stack_element item);

// stack에서 값을 뺴는 동시에 출력(값이 있는 마지막 노드)
stack_element pop(StackType* stack);

// stack 메모리 해제
void free_stack(StackType* stack);

// stack 내용 확인
void print(StackType* stack);

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

    stack = (StackType*) malloc(sizeof(StackType));

    // top : 스택 현재 보유 수량
    stack->top = 0; 
    // capacity : 스택 총 보유 가능 수량
    stack->capacity = 5; 
    stack->data = (stack_element*) malloc(stack->capacity * sizeof(stack_element));
    // element data[s->capacity];

    return stack;
}

// 해당 stack안에 값이 없는지 확인
int is_empty(StackType* stack) {

    if (stack->top == 0) {
        return 1;
    }

    return 0;
}

// 해당 stack이 가득찼는지 여부
int is_full(StackType* stack) {

    if (stack->top >= stack->capacity) {
        return 1;
    }

    return 0;
}

// 해당 stack에 값을 추가 (값이 들어간 노드 바로 다음 노드에 추가)
void push(StackType* stack, stack_element item) {

    int result = is_full(stack);

    if (result == 0) {

        *(stack->data + stack->top) = item;
        printf("메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값 = %d \n", stack, stack->top, *(stack->data + stack->top));
        (stack->top)++;

        stack->data = (stack_element*) realloc(stack->data, (sizeof(stack_element) * stack->top));
    }
    else if (result == 1) {

        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 이미 가지고 있는 %d개 공간을 전부 채웠습니다.\n", stack, stack->capacity);
    }
}

// stack에서 값을 뺴는 동시에 출력(값이 있는 마지막 노드)
stack_element pop(StackType* stack) {

    int result = is_empty(stack);

    if (result == 0) {

        (stack->top)--;
        printf("메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값인 %d를 제거했습니다. \n", stack, stack->top, *(stack->data + stack->top));
        *(stack->data + stack->top) = 0;

        stack = realloc(stack, (sizeof(stack_element) * stack->top));
    }
    else if (result == 1) {

        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 입력된 값이 없습니다.\n", stack);
    }

}

// stack 메모리 해제
void free_stack(StackType* stack) {
    
    free(stack->data);
    free(stack);
}

// stack 내용 확인
void print(StackType* stack) {
    
    int result = is_empty(stack);

    if (result == 0) {

        printf("현재 stack의 개수 : %d\n", stack->capacity);
        printf("현재 stack의 값 : ");

        for (int i = 0; i < stack->top; i++) {

            printf("%d ", *(stack->data + i));
        }

        printf("\n");

    }
    else{
        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 입력된 값이 없습니다.\n", stack);
    }

}
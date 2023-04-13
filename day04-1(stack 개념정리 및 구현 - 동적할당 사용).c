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


// stack ADT 전부 구현해보자 (동적할당 사용해서..)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함

typedef int stack_element;
typedef struct {
    stack_element* data; // 스택에 넣은 값들이 위치하는 메모리 주소의 시작점 (= 이 포인터변수는 동적할당 메서드를 통해 return값을 받게 될 시... 그 위치를 저장하기 위한 용도)
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
void push(StackType* stack, stack_element item);

// stack에서 값을 제거 return값은 stack의 요소 (값이 있는 마지막 노드)
void pop(StackType* stack);

// 해당 메모리 위치에 존재하는 stack 메모리 전체 해제
void free_stack(StackType* stack);

// 해당 메모리 위치에 존재하는 stack 내용 확인
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

	// stack 구조체가 위치하는 메모리주소를 저장함
	stack = (StackType*) malloc(sizeof(StackType));

	// top : 스택 현재 보유 수량
	stack->top = 0; 
	// capacity : 스택 총 보유 가능 수량
	stack->capacity = 5; 
	// data : 스택에 넣은 값들이 위치하는 메모리 주소의 시작점 (= 이 포인터변수는 동적할당 메서드를 통해 return값을 받게 될 시... 그 위치를 저장하기 위한 용도)
	stack->data = (stack_element*) malloc(stack->capacity * sizeof(stack_element));
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
void push(StackType* stack, stack_element item) {

	// 값을 추가하기 전 stack의 공간이 가득찼는지 확인
	int result = is_full(stack);

	// stack 공간에 여유가 있다면? 값 추가진행
	if (result == 0) {
			
	// (중요) stack의 값이 위치하는 메모리 주소는 값이 추가된 후 top++가 된다는 점을 기억해야함 
	// (= capacity가 3이라 치면, 마지막 값의 주소 = '시작주소' + capacity - 1 = '시작주소' + capacity - 1)

	// stack에 넣고자 하는 값 item은 값들이 위치하는 메모리 주소의 시작값 data를 기준으로 stack에 존재하는 값들의 현 개수 - 1 를 더해서 얻은 메모리주소를 역참조한 값으로 둔다
	*(stack->data + stack->top) = item;
	printf("메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값 = %d \n", stack, stack->top, *(stack->data + stack->top));

	// 새로운 값 메모리 주소위치 = data + top - 1인 이유가 top의 값이 item이 들어간 이후에 연산이 되는 이유
	(stack->top)++;

	// (보너스) realloc을 통해, 현재의 stack이 쓸데없이 메모리를 많이/적게 먹는 경우 알맞은 수준으로 메모리 할당을 변경 가능 (= 가변 할당을 통한 메모리 관리 가능)
	//  -> push를 새로 할 때마다, stack요소를 저장하는데 쓸 메모리의 할당하는 양을 늘려서 할당하고 그 시작주소 재대입 
	stack->data = (stack_element*) realloc(stack->data, (sizeof(stack_element) * stack->top));
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
		printf("메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값인 %d를 제거했습니다. \n", stack, stack->top, *(stack->data + stack->top));
		
		// 해당 위치에 존재하는 값을 제거할 목적으로 0대입 (어차피 top의 값이 이 위치의 접근가능 여부를 결정함 = push할떄 새로운 값으로 대입되므로 안 해줘도 됨)
		*(stack->data + stack->top) = 0;

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
    free(stack->data);
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

            printf("%d ", *(stack->data + i));
        }

        printf("\n");

    }
    else{
        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 입력된 값이 없습니다.\n", stack);
    }

}

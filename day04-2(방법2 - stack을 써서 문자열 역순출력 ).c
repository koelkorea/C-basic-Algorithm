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


// quiz : stack을 사용해서 문자열[최대 256개. 종료 end 입력]을 입력받고 거꾸로 뒤집는 코드를 작성하라
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <conio.h>		// (헤더) conio.h (console and port I/0의 약자) :  c언어의 콘솔 입출력 함수를 제공

typedef char stack_element;
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

// str_len(문자열 주소) : 해당 문자열의 길이 반환
int str_len(char* p) {

    int n = 0;                       // 현재 문자열 길이을 나타냄
    while (*p++)n++;        // 현재 참고하는 문자열 주소 위치의 값을 역참조한 값이 null이 아니면? 숫자를 1개씩 올린다.    -> 이걸 문자열이 null이 나와 끝날때까지 계속하면, 문자열 길이 체크 가능
    return n;
}

//5. strchr() : 두 개의 문자열을 아스키 코드 값으로 비교 (2문자열의 각 자리수를 비교하다가 판정이 나오면 리턴값 주기)
//  - str1 < str2 인 경우 - 1 반환
//  - str1 > str2 인 경우 1 반환
//  - str1 == str2 인 경우 0 반환 <- 최종
int str_cmp(char* str1, char* str2) {

    int n1 = 0;
    int n2 = 0;
    int n = 0;
    int result = 0;

    char* sx1 = str1;
    char* sx2 = str2;

    // 문자열1의 길이 구하기
    while (*str1) {
        n1++;
        str1 = str1 + 1;
    }

    // 문자열1의 길이 구하기
    while (*str2) {
        n2++;
        str2 = str2 + 1;
    }

    str1 = sx1;
    str2 = sx2;

    if (n1 != n2) {

        if (n1 > n2) {
            n = n1;
        }
        else if (n1 < n2) {
            n = n2;
        }
    }
    else {

        n = n1;
    }

    // printf("%d\n", n);

    for (int i = 0; i < n; i++) {

        if (*(str1 + i) > *(str2 + i)) {
            result = 1;
            break;

        }
        else if (*(str1 + i) < *(str2 + i)) {
            result = -1;
            break;
        }

    }

    return result;
}


int main(void) {

    char tmp[256] = { 0 };

    printf("문자열을 입력해주세요 : ");
    scanf_s("%s", &tmp, sizeof(tmp));
    while (getchar() != '\n');

    if (str_cmp(tmp, "end") != 0) {

        StackType* stack_address1 = NULL;
        stack_address1 = init_stack(stack_address1);

        char* reversed = (char*)calloc(str_len(tmp) + 1, sizeof(char));

        for (int i = 0; i < str_len(tmp); i++) {
            push(stack_address1, tmp[i]);
        }
        printf("\n");

        printf("문자열 반전 결과 : ");
        for (int i = 0; i < str_len(tmp); i++) {

            char popped = pop(stack_address1);
            *(reversed + i) = popped;

        }

        printf("%s", reversed, sizeof(reversed));
        printf("\n");
    }
    else {
        printf("프로그램이 종료되었습니다. \n");
        exit(0);
    }

    return 0;
}

// stack 초기화
StackType* init_stack(StackType* stack) {

    stack = (StackType*)malloc(sizeof(StackType));

    // top : 스택 현재 보유 수량
    stack->top = 0;
    // capacity : 스택 총 보유 가능 수량
    stack->capacity = 256;
    stack->data = (stack_element*)malloc(stack->capacity * sizeof(stack_element));
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
        // printf("메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값 = %c \n", stack, stack->top, *(stack->data + stack->top));
        (stack->top)++;

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
        // printf("메모리 주소 %d부터 할당된 stack구조의 %d번째 공간의 값인 %c를 제거했습니다. \n", stack, stack->top, *(stack->data + stack->top));
        // *(stack->data + stack->top) = 0;

        return *(stack->data + stack->top);

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

        printf("현재 stack의 최대공간 : %d\n", stack->capacity);
        printf("현재 stack의 값 : ");

        for (int i = 0; i <= stack->top; i++) {

            printf("%c ", *(stack->data + i));
        }

        printf("\n");

    }
    else {
        printf("(주의!) 메모리 주소 %d부터 할당된 stack은 입력된 값이 없습니다.\n", stack);
    }

}
// ����(stack)
//  : 'â�� ������ �׾Ƶε�' �ڷḦ �� ���� �׾Ƶδ� �ڷᱸ�� ����
//    (= ���� ���߿� ���� �༮�� ���� ���߿� ������ ����)

//  # ���Լ��� LIFO 
//    : Last-In, First-Out  

//  # stack ����ü ( ���� ��� )
// 
//    typedef int stack_element;

//    typedef struct {
//        stack_element* data; // ���ÿ� ���� ������ ����
//        int capacity; // ������ �� ���� �뷮
//        int top; // ����� �ڷ� ����
//    } StackType;

//  # Stack ADT
//    - init_stack(stack) : ������ ������� �ʱ�ȭ
//    - is_empty(stack)   : ���� �ȿ� ���� ������ Ȯ��
//    - is_full(stack)    : ������ ���� á������ Ȯ��
//    - push(stack, item) : ���� �ڷ��� �� ���� ��� item �߰�
//    - pop(stack)        : ������ �� ���� �ִ� ��Ҹ� �������� �ʰ� ��ȯ


// stack ADT ���� �����غ��� (�����Ҵ� ����ؼ�..)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��

typedef int stack_element;
typedef struct {
    stack_element* data; // ���ÿ� ���� ������ ����
    int capacity; // ������ �� ���� �뷮
    int top; // ����� �ڷ� ����
}StackType;

// stack �ʱ�ȭ
StackType* init_stack(StackType* stack);

// �ش� stack�ȿ� ���� ������ Ȯ��
int is_empty(StackType* stack);

// �ش� stack�� ����á���� ����
int is_full(StackType* stack);

// �ش� stack�� ���� �߰� (���� �� ��� �ٷ� ���� ���)
void push(StackType* stack, stack_element item);

// stack���� ���� ���� ���ÿ� ���(���� �ִ� ������ ���)
stack_element pop(StackType* stack);

// stack �޸� ����
void free_stack(StackType* stack);

// stack ���� Ȯ��
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

// stack �ʱ�ȭ
StackType* init_stack(StackType* stack) {

    stack = (StackType*) malloc(sizeof(StackType));

    // top : ���� ���� ���� ����
    stack->top = 0; 
    // capacity : ���� �� ���� ���� ����
    stack->capacity = 5; 
    stack->data = (stack_element*) malloc(stack->capacity * sizeof(stack_element));
    // element data[s->capacity];

    return stack;
}

// �ش� stack�ȿ� ���� ������ Ȯ��
int is_empty(StackType* stack) {

    if (stack->top == 0) {
        return 1;
    }

    return 0;
}

// �ش� stack�� ����á���� ����
int is_full(StackType* stack) {

    if (stack->top >= stack->capacity) {
        return 1;
    }

    return 0;
}

// �ش� stack�� ���� �߰� (���� �� ��� �ٷ� ���� ��忡 �߰�)
void push(StackType* stack, stack_element item) {

    int result = is_full(stack);

    if (result == 0) {

        *(stack->data + stack->top) = item;
        printf("�޸� �ּ� %d���� �Ҵ�� stack������ %d��° ������ �� = %d \n", stack, stack->top, *(stack->data + stack->top));
        (stack->top)++;

        stack->data = (stack_element*) realloc(stack->data, (sizeof(stack_element) * stack->top));
    }
    else if (result == 1) {

        printf("(����!) �޸� �ּ� %d���� �Ҵ�� stack�� �̹� ������ �ִ� %d�� ������ ���� ä�����ϴ�.\n", stack, stack->capacity);
    }
}

// stack���� ���� ���� ���ÿ� ���(���� �ִ� ������ ���)
stack_element pop(StackType* stack) {

    int result = is_empty(stack);

    if (result == 0) {

        (stack->top)--;
        printf("�޸� �ּ� %d���� �Ҵ�� stack������ %d��° ������ ���� %d�� �����߽��ϴ�. \n", stack, stack->top, *(stack->data + stack->top));
        *(stack->data + stack->top) = 0;

        stack = realloc(stack, (sizeof(stack_element) * stack->top));
    }
    else if (result == 1) {

        printf("(����!) �޸� �ּ� %d���� �Ҵ�� stack�� �Էµ� ���� �����ϴ�.\n", stack);
    }

}

// stack �޸� ����
void free_stack(StackType* stack) {
    
    free(stack->data);
    free(stack);
}

// stack ���� Ȯ��
void print(StackType* stack) {
    
    int result = is_empty(stack);

    if (result == 0) {

        printf("���� stack�� ���� : %d\n", stack->capacity);
        printf("���� stack�� �� : ");

        for (int i = 0; i < stack->top; i++) {

            printf("%d ", *(stack->data + i));
        }

        printf("\n");

    }
    else{
        printf("(����!) �޸� �ּ� %d���� �Ҵ�� stack�� �Էµ� ���� �����ϴ�.\n", stack);
    }

}
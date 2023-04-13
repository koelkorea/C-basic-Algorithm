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


// quiz : stack�� ����ؼ� ���ڿ�[�ִ� 256��. ���� end �Է�]�� �Է¹ް� �Ųٷ� ������ �ڵ带 �ۼ��϶�
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <conio.h>		// (���) conio.h (console and port I/0�� ����) :  c����� �ܼ� ����� �Լ��� ����

typedef char stack_element;
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

// str_len(���ڿ� �ּ�) : �ش� ���ڿ��� ���� ��ȯ
int str_len(char* p) {

    int n = 0;                       // ���� ���ڿ� ������ ��Ÿ��
    while (*p++)n++;        // ���� �����ϴ� ���ڿ� �ּ� ��ġ�� ���� �������� ���� null�� �ƴϸ�? ���ڸ� 1���� �ø���.    -> �̰� ���ڿ��� null�� ���� ���������� ����ϸ�, ���ڿ� ���� üũ ����
    return n;
}

//5. strchr() : �� ���� ���ڿ��� �ƽ�Ű �ڵ� ������ �� (2���ڿ��� �� �ڸ����� ���ϴٰ� ������ ������ ���ϰ� �ֱ�)
//  - str1 < str2 �� ��� - 1 ��ȯ
//  - str1 > str2 �� ��� 1 ��ȯ
//  - str1 == str2 �� ��� 0 ��ȯ <- ����
int str_cmp(char* str1, char* str2) {

    int n1 = 0;
    int n2 = 0;
    int n = 0;
    int result = 0;

    char* sx1 = str1;
    char* sx2 = str2;

    // ���ڿ�1�� ���� ���ϱ�
    while (*str1) {
        n1++;
        str1 = str1 + 1;
    }

    // ���ڿ�1�� ���� ���ϱ�
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

    printf("���ڿ��� �Է����ּ��� : ");
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

        printf("���ڿ� ���� ��� : ");
        for (int i = 0; i < str_len(tmp); i++) {

            char popped = pop(stack_address1);
            *(reversed + i) = popped;

        }

        printf("%s", reversed, sizeof(reversed));
        printf("\n");
    }
    else {
        printf("���α׷��� ����Ǿ����ϴ�. \n");
        exit(0);
    }

    return 0;
}

// stack �ʱ�ȭ
StackType* init_stack(StackType* stack) {

    stack = (StackType*)malloc(sizeof(StackType));

    // top : ���� ���� ���� ����
    stack->top = 0;
    // capacity : ���� �� ���� ���� ����
    stack->capacity = 256;
    stack->data = (stack_element*)malloc(stack->capacity * sizeof(stack_element));
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
        // printf("�޸� �ּ� %d���� �Ҵ�� stack������ %d��° ������ �� = %c \n", stack, stack->top, *(stack->data + stack->top));
        (stack->top)++;

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
        // printf("�޸� �ּ� %d���� �Ҵ�� stack������ %d��° ������ ���� %c�� �����߽��ϴ�. \n", stack, stack->top, *(stack->data + stack->top));
        // *(stack->data + stack->top) = 0;

        return *(stack->data + stack->top);

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

        printf("���� stack�� �ִ���� : %d\n", stack->capacity);
        printf("���� stack�� �� : ");

        for (int i = 0; i <= stack->top; i++) {

            printf("%c ", *(stack->data + i));
        }

        printf("\n");

    }
    else {
        printf("(����!) �޸� �ּ� %d���� �Ҵ�� stack�� �Էµ� ���� �����ϴ�.\n", stack);
    }

}
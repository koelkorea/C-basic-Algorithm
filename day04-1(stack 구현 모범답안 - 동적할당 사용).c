#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef char StackElement; // ���� ������ ���������� ����

typedef struct {
    StackElement* data;
    int capacity;
    int top;
}StackType;

void init_stack(StackType* s);
int is_empty(StackType* s);
int is_full(StackType* s);
void push(StackType* s, StackElement item);
StackElement pop(StackType* s);
void free_stack(StackType* s);
void print(StackType* s);

int main() {
    StackElement ch = 0;
    StackType s;
    init_stack(&s);
    while (1) {
        printf("���ڿ� �Է� : ");
        do {//���� ���� �Է�
            ch = getchar();
            printf("%c", ch);
            push(&s, ch);
        } while (ch != '\n');
        while (!is_empty(&s)) {
            printf("%c", pop(&s));
        }
        printf("\n\n");
        printf("����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . . [���� : 0 �Է�] \n");
        if ((ch = _getch()) == '0') break;
    }
    printf("\n\t\t[���α׷� ���� �մϴ�.] \n");
    free_stack(&s);
    return 0;
}
void init_stack(StackType* s) {
    s->top = 0;
    s->capacity = 1;
    s->data = (StackElement*)malloc(s->capacity * sizeof(StackElement)); // element data[s->capacity];
}
int is_empty(StackType* s) {
    return (s->top == 0);
}
int is_full(StackType* s) {
    return (s->top == s->capacity);
}
void push(StackType* s, StackElement item) {
    if (is_full(s)) {
        s->capacity *= 2;
        s->data = (StackElement*)realloc(s->data, s->capacity * sizeof(StackElement));
    }
    s->data[(s->top)++] = item;
}
StackElement pop(StackType* s) {
    if (is_empty(s)) {
        printf("stack empty error\n");
        return 0;
    }
    if (s->top < s->capacity / 2) {
        s->capacity /= 2;
        s->data = (StackElement*)realloc(s->data, s->capacity * sizeof(StackElement));
    }
    return s->data[--(s->top)];
}
void free_stack(StackType* s) {
    free(s->data);
}
void print(StackType* s) {
    if (is_empty(s)) {
        printf("stack empty\n");
        return;
    }
    for (int i = s->top - 1; i >= 0; i--) {
        printf("%2d : %7d  \n", i, s->data[i]);
    }
}

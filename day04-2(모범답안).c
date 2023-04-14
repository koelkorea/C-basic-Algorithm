#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char StackElement; // 저장 데이터 문자형으로 변경

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

    StackElement buf[257];
    StackType s;

    init_stack(&s);

    while (1) {

        printf("문자열 입력 [최대 256개, 종료 end 입력] : ");
        gets_s(buf, sizeof(buf));

        printf("%s\n", buf);

        if (strcmp(buf, "end") == 0) {
            break;
        }

        for (int i = 0; i < strlen(buf); i++) {
            push(&s, buf[i]);
        }

        for (int i = 0; i < strlen(buf); i++) {
            buf[i] = pop(&s);
        }

        printf("%s\n", buf);
    }
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

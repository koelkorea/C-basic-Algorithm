#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}
void bubble(int* pArr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (pArr[j] > pArr[j + 1]) swap(int, pArr[j], pArr[j + 1]);
        }
    }
}
void improvedBubble(int* pArr, int size) {
    int i, j, swapped;
    for (i = 0; i < size - 1; i++) {
        swapped = 0;
        for (j = 0; j < size - 1 - i; j++) {
            if (pArr[j] > pArr[j + 1]) {
                swap(int, pArr[j], pArr[j + 1]);
                swapped++;
            }
        }
        if (!swapped) break;
    }
}
void display(int* pArr, int size) {
    for (int i = 0; i < size; i++) printf("%d  ", pArr[i]);
    printf("\n");
}
void randomize(int* pArr, int size, int st, int end) {
    /*
    ���� - int rand (void);
    seed(����)���� ���� 0~32767 ���� ���� ��ȯ
    ���� - (void) srand (unsigned int seed);
    seed���� �����Ų��.
    ���� - (long long) time (time_t * timer);
    �Ű������� NULL�� ������ ������ ���� �ð��� ��ȯ
    ��� : ���α׷� ���� �ð��� ���� ���� ���� �߻�
    */
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) pArr[i] = rand() % (end - st + 1) + st;
}
int main() {
    int size, st, end;
    int* arr;
    printf("�迭 ũ�� �Է� : ");
    scanf_s("%d", &size);
    arr = (int*)calloc(size, sizeof(int)); //���� �Ҵ�, �� 0 �ʱ�ȭ
    printf("���� ���� �� / �� �� �Է� (���� ����) : ");
    scanf_s("%d %d", &st, &end);
    randomize(arr, size, st, end);
    printf("\n\n*** ���� �� �ڷ� ��� ***\n");
    display(arr, size);
    bubble(arr, size);
    //improvedBubble(arr, size);
    printf("\n\n*** ���� �� �ڷ� ��� ***\n");
    display(arr, size);
    free(arr); //���� �޸� ����
    return 0;
}

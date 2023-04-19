#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
void insertion(int* pArr, int size) {
    int i, j, temp;
    for (i = 1; i < size; i++) {
        temp = pArr[i];
        for (j = i; j > 0 && (pArr[j - 1] > temp); j--) {
            pArr[j] = pArr[j - 1];
        }
        pArr[j] = temp;
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
    arr = (int*)calloc(size, sizeof(int));//���� �Ҵ�, 0�ʱ�ȭ
    printf("���� ���� �� / �� �� �Է� (���� ����) : ");
    scanf_s("%d %d", &st, &end);
    randomize(arr, size, st, end);
    printf("\n\n*** ���� �� �ڷ� ��� ***\n");
    display(arr, size);
    insertion(arr, size);
    printf("\n\n*** ���� �� �ڷ� ��� ***\n");
    display(arr, size);
    free(arr); //���� �޸� ����
    return 0;
}

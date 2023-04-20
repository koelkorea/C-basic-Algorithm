#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}
void radomize(int* arr, int size, int st, int end) {
    if (st > end) swap(int, st, end);
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) arr[i] = rand() % (end - st + 1) + st;
}
void display(int* pArr, int size) {
    for (int i = 0; i < size; i++) printf("%d  ", pArr[i]);
    printf("\n");
}
void quick(int* arr, int left, int right) {
    int pl = left, pr = right, pivot = arr[(pl + pr) / 2];
    do {
        while (arr[pl] < pivot)  pl++;
        while (arr[pr] > pivot)  pr--;
        if (pl <= pr) {
            swap(int, arr[pl], arr[pr]);
            pl++;
            pr--;
        }
    } while (pl <= pr);
    if (left < pr) quick(arr, left, pr);
    if (right > pl)  quick(arr, pl, right);
}
void quickSort(int* arr, int size) {
    quick(arr, 0, size - 1);
}
int main() {
    int size, st, end;
    int* arr;
    printf("배열의 크기 입력 : ");
    scanf_s("%d", &size);
    arr = (int*)calloc(size, sizeof(int));
    printf("시작 수 / 끝 수 입력 : ");
    scanf_s("%d %d", &st, &end);
    radomize(arr, size, st, end);
    printf("\n\n정렬 전 자료 출력 ***\n\n");
    display(arr, size);
    quickSort(arr, size);
    printf("\n\n정렬 후 자료 출력 ***\n\n");
    display(arr, size);
    free(arr);
    return 0;
}

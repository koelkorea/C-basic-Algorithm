#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}
void display(int* arr, int size) {
    for (int i = 0; i < size; i++) printf("%7d ", arr[i]);
    printf("\n");
}
void randomize(int* arr, int st, int end, int size) {
    if (st > end) swap(int, st, end);
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) arr[i] = rand() % (end - st + 1) + st;
}
void merge(int* arr, int* arrMerge, int left, int mid, int right) {
    int p1 = left, p2 = mid + 1, pM = left;
    for (int i = left; i <= right; i++)  arrMerge[i] = arr[i];
    while (p1 <= mid && p2 <= right) {
        if (arrMerge[p1] < arrMerge[p2]) {
            arr[pM++] = arrMerge[p1++];
        }
        else {
            arr[pM++] = arrMerge[p2++];
        }
    }
    while (p1 <= mid) arr[pM++] = arrMerge[p1++];
    while (p2 <= right) arr[pM++] = arrMerge[p2++];
}
void mergeSortUtil(int* arr, int* arrMerge, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortUtil(arr, arrMerge, left, mid);
        mergeSortUtil(arr, arrMerge, mid + 1, right);
        merge(arr, arrMerge, left, mid, right);
    }
}
void mergeSort(int* arr, int size) {
    int* arrMerge = (int*)malloc(sizeof(int) * size);
    mergeSortUtil(arr, arrMerge, 0, size - 1);
    free(arrMerge);
}
int main() {
    int size, st, end;
    int* arr;
    printf("배열의 크기 입력 : ");
    scanf_s("%d", &size);
    arr = (int*)malloc(sizeof(int) * size);
    printf("시작 수 / 끝 수 입력 : ");
    scanf_s("%d %d", &st, &end);
    randomize(arr, st, end, size);
    printf("\n\n **** 정렬 전 자료 출력 ***\n\n");
    display(arr, size);
    mergeSort(arr, size);
    printf("\n\n **** 정렬 후 자료 출력 ***\n\n");
    display(arr, size);
    free(arr);
    return 0;
}

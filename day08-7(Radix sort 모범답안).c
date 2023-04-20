#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}
void display(int* arr, int size) {
	for (int i = 0; i < size; i++)  printf("%d  ", arr[i]);
	printf("\n");
}
void randomize(int* arr, int size, int st, int end) {
	if (st > end) swap(int, st, end);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < size; i++) arr[i] = rand() % (end - st + 1) + st;
}
void bucket(int* arr, int size, int range) {
	int i, j = 0;
	int* count = (int*)calloc(range, sizeof(int));
	for (i = 0; i < size; i++) count[arr[i]]++;
	for (i = 0; i < range; i++)  for (; count[i] > 0; count[i]--) arr[j++] = i;
}
int main() {
	int size, st, end;
	int* arr;
	printf("�迭 ũ�� �Է� : ");
	scanf_s("%d", &size);
	arr = (int*)calloc(size, sizeof(int));
	printf("���� �� / �� �� �Է� : ");
	scanf_s("%d %d", &st, &end);
	randomize(arr, size, st, end);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	bucket(arr, size, end);
	printf("\n\n*** ���� �� �ڷ� ��� ***\n");
	display(arr, size);
	free(arr);
	return 0;
}

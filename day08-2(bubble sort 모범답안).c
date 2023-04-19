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
    원형 - int rand (void);
    seed(고정)값에 따라 0~32767 값을 랜덤 반환
    원형 - (void) srand (unsigned int seed);
    seed값을 변경시킨다.
    원형 - (long long) time (time_t * timer);
    매개변수가 NULL일 때에는 실행한 현재 시간을 반환
    결론 : 프로그램 실행 시간에 따라 랜덤 변수 발생
    */
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) pArr[i] = rand() % (end - st + 1) + st;
}
int main() {
    int size, st, end;
    int* arr;
    printf("배열 크기 입력 : ");
    scanf_s("%d", &size);
    arr = (int*)calloc(size, sizeof(int)); //동적 할당, 값 0 초기화
    printf("랜덤 시작 수 / 끝 수 입력 (공백 구분) : ");
    scanf_s("%d %d", &st, &end);
    randomize(arr, size, st, end);
    printf("\n\n*** 정렬 전 자료 출력 ***\n");
    display(arr, size);
    bubble(arr, size);
    //improvedBubble(arr, size);
    printf("\n\n*** 정렬 후 자료 출력 ***\n");
    display(arr, size);
    free(arr); //동적 메모리 해제
    return 0;
}

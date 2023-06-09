#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
void display(int* pArr, int size) {
    for (int i = 0; i < size; i++) printf("%5d  ", pArr[i]);
    printf("\n");
}
int insertion_shell(int* pArr, int first, int last, int gap) {
    int i, j, temp;
    for (i = first + gap; i < last; i = i + gap) {
        temp = pArr[i];
        for (j = i; j - gap >= first && pArr[j - gap] > temp; j = j - gap)
        {
            pArr[j] = pArr[j - gap];
        }
        pArr[j] = temp;
    }
}
void shell_sort(int* pArr, int size) {
    int i, gap;
    for (gap = size / 2; gap > 0; gap = gap / 2) {
        if ((gap % 2) == 0) gap++;
        for (i = 0; i < gap; i++) {
            insertion_shell(pArr, i, size, gap);
        }
        display(pArr, size); // 갭 차이별 정렬 보기
    }
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
    arr = (int*)calloc(size, sizeof(int));//동적 할당, 0초기화
    printf("랜덤 시작 수 / 끝 수 입력 (공백 구분) : ");
    scanf_s("%d %d", &st, &end);
    randomize(arr, size, st, end);
    printf("\n\n*** 정렬 전 자료 출력 ***\n");
    display(arr, size);
    shell_sort(arr, size);
    printf("\n\n*** 정렬 후 자료 출력 ***\n");
    display(arr, size);
    free(arr); //동적 메모리 해제
    return 0;
}

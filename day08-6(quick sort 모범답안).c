#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}

// 배열에 숫자를 랜덤생성
void radomize(int* array, int length, int start, int end) {

    srand((unsigned int)time(NULL));

    // 배열의 최소값이 최대값보다 크다면... 그 두 수치를 바꿔서 말이 되게 함
    if (start > end) {
        swap(int, start, end);
    }

    // 각 배열공간에 최소값 ~ 최대값이 나오게 값을 채워줌
    for (int i = 0; i < length; i++) {

        array[i] = rand() % (end - start + 1) + start;
    }
}

// 해당 동적배열의 요소값을 순차적 출력 (for문으로 length만큼 반복)
void display(int* pArr, int start, int size) {
    for (int i = start; i < size; i++) {
        printf("%d  ", pArr[i]);
    }
    printf("\n\n");
}

// 퀵소트(재귀사용을 통한 마무리)
void quick(int* array, int leftest, int rightest) {

    // 왼쪽 포인터 시작점, 오른쪽 포인터 시작점
    int left_point = leftest;
    int right_point = rightest;

    // (중요) left <-> right 교환을 위한 기준값 = 배열의 중간위치의 값으로.. 
    //  -> 그렇게 안하고 배열 내부의 아무 값이나 잡아도 되지만, 너무 극단적인 값을 기준값으로 잡으면 퀵소트의 효율이 바닥을 친다
    //int pivot = array[(left_point + right_point) / 2];
    int pivot = array[left_point];

    printf("\n---------------------[기준값 : %d, 배열 시작 : %d, 배열 끝 : %d]------------------------------------\n\n[원본] : ", pivot, left_point, right_point);

    display(array, leftest, rightest + 1);

    // left_point가 right_point보다 크게 될 때까지 반복 (상황이 아니라 쳐도 일단 실행해봄)
    do {

        printf("(교환값 검색전)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, array[left_point], right_point, array[right_point]);

        // 배열[left_point]값이 기준값보다 크거나 같은 상황이 될떄까지 left_point를 왼쪽으로 옮김
        while (array[left_point] < pivot) {
            left_point++;
        }

        // 배열[right_point]값이 기준값보다 작거나 같은 상황이 될떄까지 right_point를 오룬쪽으로 옮김
        while (array[right_point] > pivot) {
            right_point--;
        }

        printf("(교환값 검색후!)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, array[left_point], right_point, array[right_point]);

        // left포인트와 right포인트가 현재 멈춘 지점에서 left지점이 right지점보다 같거나 낮은 위치라면?
        //  -> 두 위치의 값을 바꿔주고, 각 포인터를 가던 방향으로 1칸씩 옮긴다
        if (left_point <= right_point) {
            printf("  ->> (left - right 교환!) arr[%d] : %d <-> arr[%d] : %d \n\n", left_point, array[left_point], right_point, array[right_point]);
            swap(int, array[left_point], array[right_point]);
            left_point++;
            right_point--;
        }

        printf("      ");

        // 바뀐 결과 보기
        display(array, leftest, rightest + 1);

    // 그렇게 반복후 left지점이 right지점보다 큰 상황이면 중단
    } while (left_point <= right_point);

    printf("=====================================[싸이클 end]==================================================\n\n");

    // 배열 가장 왼쪽위치가 현재 오른쪽 포인터보다 작으면?
    //  -> 배열 가장 왼쪽위치 ~ 현재 오른쪽 포인터까지를 잘라서 퀵소트 실행
    if (leftest < right_point) {

        printf("<전 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", leftest, right_point);
        quick(array, leftest, right_point);
    }

    // 배열 가장 오른쪽위치가 현재 왼쪽 포인터보다 크면?
    //  -> 현재 왼쪽 포인터 ~ 배열 가장 오른쪽위치까지 잘라서 퀵소트 실행
    if (rightest > left_point) {

        printf("<후 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", left_point, rightest);
        quick(array, left_point, rightest);
    }
}

// 퀵소트 시작시 트리거용 메서드
void quickSort(int* arr, int size) {
    quick(arr, 0, size - 1);
}


int main() {

    // 동적배열 시작주소 받을 int 포인트 주소
    int* array_address;

    // 배열길이, 최소값, 최대값
    int length, min, max;

    printf("배열의 크기 입력 : ");
    scanf_s("%d", &length);

    // 길이를 입력하면, 그만큼 동적배열을 생성하고, 시작위치를 가져다준다
    array_address = (int*)calloc(length, sizeof(int));

    printf("최소값 / 최대값 입력 : ");
    scanf_s("%d %d", &min, &max);

    // 배열값 기입
    radomize(array_address, length, min, max);

    printf("\n\n정렬 전 자료 출력 ***\n\n");
    display(array_address, 0, length);

    // 퀵소트 트리거 (시작점)
    quickSort(array_address, length);

    printf("\n\n정렬 후 자료 출력 ***\n\n");
    display(array_address, 0,length);

    // 동적배열 메모리 해제
    free(array_address);
    return 0;
}

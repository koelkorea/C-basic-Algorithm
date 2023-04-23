// 정렬
//  : 데이터 그룹 요소를 특정 기준으로 오름차순이나 내림차순으로 정리
//    -> 데이터를 집합으로 그룹화할 때 가장 기본적이고 중요한 알고리즘

//  5. 퀵 정렬(Quick sort)
//     : 리스트 안에 존재하는 임의의 값을 기준값으로 정해두고, 
//       -> 왼쪽에서부터 데이터를 기준값과 정렬방법에 따라 크고 작은지 비교 정렬방법에 따라 조건이 안 맞으면 다음 값으로, 맞으면 오른쪽부터 데이터를 기준값과 비교해서 정반대의 경우가 존재하는지 확인
//          -> 오른쪽에도 존재가 맞는 값이 보이면? ->  왼쪽과 오른쪽의 값을 교환하고, 그 다음 왼쪽위치의 다음 값부터 똑같이 계속 진행
//       -> 왼쪽이던 오른쪽이던 포인터가 겹치게 된다면? 그 부분을 중심으로 리스트를 토막내서 다시 같은 방식으로 비교 반복
//       -> 모든 부분리스트가 더 이상 분할이 불가능한 최소 단위(1개)로 분할 될 때까지 이를 반복

//     # 평균적으로 가장 빠른 정렬 방법
//     # top-bottom(= 큰 문제를 해결하는 과정에서 분할해서 작은 문제를 해결하기) 방식 사용

// 정적할당을 사용한 퀵정렬 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define ARRAY_LENGTH 10
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define 매크로 영역 (형태처리 전처리 기문)			ex) A <-> : A와 B를 해당하는 타입을 빈공간으로 사용하여 교환


// 해당 동적배열의 요소값을 순차적 출력 (for문으로 length만큼 반복)
void display(int arr[], int start, int size) {

    for (int i = start; i < size; i++) {

        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

//  5. 퀵 정렬(Quick sort)
//     : 리스트 안에 존재하는 임의의 값을 기준값으로 정해두고, 
//       -> 왼쪽에서부터 데이터를 기준값과 정렬방법에 따라 크고 작은지 비교 정렬방법에 따라 조건이 안 맞으면 다음 값으로, 맞으면 오른쪽부터 데이터를 기준값과 비교해서 정반대의 경우가 존재하는지 확인
//          -> 오른쪽에도 존재가 맞는 값이 보이면? ->  왼쪽과 오른쪽의 값을 교환하고, 그 다음 왼쪽위치의 다음 값부터 똑같이 계속 진행
//       -> 왼쪽이던 오른쪽이던 포인터가 겹치게 된다면? 그 부분을 중심으로 리스트를 토막내서 다시 같은 방식으로 비교 반복
//       -> 모든 부분리스트가 더 이상 분할이 불가능한 최소 단위(1개)로 분할 될 때까지 이를 반복
void quick_sort(int arr[], int direction, int leftest, int rightest) {

    int left_point = leftest;
    int right_point = rightest;
    int pivot = arr[left_point];

    printf("\n---------------------[기준값 : %d, 시작부분 : %d, 끝부분 : %d]------------------------------------\n\n", pivot, leftest, rightest);

    display(arr, leftest, rightest + 1);

    // 오름차순 (큰 수를 뒤로.. )
    if (direction == ascending_order) {

        // left_point가 right_point보다 같게 될 때까지 반복 (상황이 아니라 쳐도 일단 실행해봄)
        do {

            printf("(교환값 검색전)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

            // 배열[left_point]값이 기준값보다 크거나 같은 상황이 될떄까지 left_point를 왼쪽으로 옮김
            while (arr[left_point] < pivot){
                left_point++;
            }

            if (left_point == right_point) {
                printf(" ->> (left 커서 move 중단!) left = right : 현재 위치가 %d로 같은 상황입니다\n\n");
            }
            else {
                printf(" ->> (교환 left발견) arr[%d] : %d (arr[%d](기준값) : %d 보다 큰 값)   ----->> right값을 움직이겠음\n", left_point, arr[left_point], leftest, pivot);
            }

            // 배열[right_point]값이 기준값보다 작거나 같은 상황이 될떄까지 right_point를 오룬쪽으로 옮김
            while (arr[right_point] > pivot){
                right_point--;
            }

            if (left_point == right_point) {
                printf(" ->> (right 커서 move 중단!) left = right : 현재 위치가 %d로 같은 상황입니다\n\n");
            }
            else if (left_point < right_point){
                printf(" ->> (교환 right발견) arr[%d] : %d (arr[%d](기준값) : %d 보다 작은 값)\n", right_point, arr[right_point], leftest, pivot);
            }

            printf("(교환값 검색후!)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

            if (left_point <= right_point) {
                printf("  ->> (left - right 교환!) arr[%d] : %d <-> arr[%d] : %d \n\n", left_point, arr[left_point], right_point, arr[right_point]);
                swap(int, arr[left_point], arr[right_point]);
                left_point++;
                right_point--;
            }

            display(arr, leftest, rightest + 1);

        } while (left_point <= right_point);

        printf("=====================================[싸이클 end]==================================================\n\n");

        printf("leftest : %d , rightest : %d , left_point : %d , right_point : %d \n\n", leftest , rightest , left_point , right_point);


        // 배열 가장 왼쪽위치가 현재 오른쪽 포인터보다 작으면?
        //  -> 배열 가장 왼쪽위치 ~ 현재 오른쪽 포인터까지를 잘라서 퀵소트 실행
        if (leftest < right_point) {

            // 좌분할
            printf("<전 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", leftest, right_point);
            quick_sort(arr, direction, leftest, right_point);
        }

        // 배열 가장 오른쪽위치가 현재 왼쪽 포인터보다 크면?
        //  -> 현재 왼쪽 포인터 ~ 배열 가장 오른쪽위치까지 잘라서 퀵소트 실행
        if (rightest > left_point) {

            // 우분할
            printf("<후 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", left_point, rightest);
            quick_sort(arr, direction, left_point, rightest);
        }

    }
    // 내림차순 (작은 수를 뒤로.. )
    else {

        // left_point가 right_point보다 같게 될 때까지 반복 (상황이 아니라 쳐도 일단 실행해봄)
        do {

            printf("(교환값 검색전)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

            // 배열[left_point]값이 기준값보다 작거나 같은 상황이 될떄까지 left_point를 왼쪽으로 옮김
            while (arr[left_point] > pivot) {
                left_point++;
            }

            if (left_point == right_point) {
                printf(" ->> (left 커서 move 중단!) left = right : 현재 위치가 %d로 같은 상황입니다\n\n");
            }
            else {
                printf(" ->> (교환 left발견) arr[%d] : %d (arr[%d](기준값) : %d 보다 큰 값)   ----->> right값을 움직이겠음\n", left_point, arr[left_point], leftest, pivot);
            }

            // 배열[right_point]값이 기준값보다 크거나 같은 상황이 될떄까지 right_point를 오룬쪽으로 옮김
            while (arr[right_point] < pivot) {
                right_point--;
            }

            if (left_point == right_point) {
                printf(" ->> (right 커서 move 중단!) left = right : 현재 위치가 %d로 같은 상황입니다\n\n");
            }
            else if (left_point < right_point) {
                printf(" ->> (교환 right발견) arr[%d] : %d (arr[%d](기준값) : %d 보다 작은 값)\n", right_point, arr[right_point], leftest, pivot);
            }

            printf("(교환값 검색후!)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

            if (left_point <= right_point) {
                printf("  ->> (left - right 교환!) arr[%d] : %d <-> arr[%d] : %d \n\n", left_point, arr[left_point], right_point, arr[right_point]);
                swap(int, arr[left_point], arr[right_point]);
                left_point++;
                right_point--;
            }

            display(arr, leftest, rightest + 1);

        } while (left_point <= right_point);

        printf("=====================================[싸이클 end]==================================================\n\n");

        printf("leftest : %d , rightest : %d , left_point : %d , right_point : %d \n\n", leftest, rightest, left_point, right_point);


        // 배열 가장 왼쪽위치가 현재 오른쪽 포인터보다 작으면?
        //  -> 배열 가장 왼쪽위치 ~ 현재 오른쪽 포인터까지를 잘라서 퀵소트 실행
        if (leftest < right_point) {

            // 좌분할
            printf("<전 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", leftest, right_point);
            quick_sort(arr, direction, leftest, right_point);
        }

        // 배열 가장 오른쪽위치가 현재 왼쪽 포인터보다 크면?
        //  -> 현재 왼쪽 포인터 ~ 배열 가장 오른쪽위치까지 잘라서 퀵소트 실행
        if (rightest > left_point) {

            // 우분할
            printf("<후 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", left_point, rightest);
            quick_sort(arr, direction, left_point, rightest);
        }
    }

}

int main() {

    srand((unsigned int)time(NULL));

    printf("----------------------------------------------------------------------------\n");
    printf("배열의 길이는 100이며, quick sort를 수행해봅니다.\n각 배열값은 각 배열의 이전 배열값 + a(1~5) 에 대응하는 값으로 입력됩니다.\n");
    printf("----------------------------------------------------------------------------\n\n");

    int ary_test[ARRAY_LENGTH] = { 0 };
    int input = 0;
    int direction = ascending_order;
    int array_length = ARRAY_LENGTH - 1;

    // 랜덤한 값이 들어갈수 있게 설계 (0 ~ 500)
    for (int i = 0; i < ARRAY_LENGTH; i++) {

        ary_test[i] = rand() % 501;

        printf("%d ", ary_test[i]);
    }

    printf("\n\n값 입력이 완료되었습니다. \n");

    //int divider;

    //printf("shell 소트를 위해 집단을 나눌값을 정해주세요 : ");
    //scanf_s("%d", &divider);

    //// shell 부분 정렬 알고리즘의 간격
    //int interval = (ARRAY_LENGTH - 1) / divider;

    printf("원하시는 방식의 정렬방식이 오름차순인가요? (0 : 오름차순, 그 이외 값 입력: 내림차순) : ");
    scanf_s("%d", &direction);

    // 머지 소트 실행
    quick_sort(ary_test, direction, 0, array_length);

    printf("\n[quick sort 결과] \n");

    display(ary_test, 0, ARRAY_LENGTH);

    printf("\n");

    return 0;
}

// 정렬
//  : 데이터 그룹 요소를 특정 기준으로 오름차순이나 내림차순으로 정리
//    -> 데이터를 집합으로 그룹화할 때 가장 기본적이고 중요한 알고리즘

//  5. 퀵 정렬(Quick sort)
//     : 기준값을 정해두고, 왼쪽에서부터 i + 1번째 데이터와 n - i + 1번째 데이터를 비교하고, 정렬방법에 따라 이들을 교환함
//       -> 포인터가 중앙점인 교차점을 넘어가게 되면, 그 부분을 중심으로 리스트를 반토막내서 다시 같은 방식으로 비교 반복
//       -> 더 이상 분할이 불가능한 최소 단위(1개)로 분할 될 때까지 이를 반복

//     # 평균적으로 가장 빠른 정렬 방법
//     # top-bottom(= 큰 문제를 해결하는 과정에서 분할해서 작은 문제를 해결하기) 방식 사용

// 정적할당을 사용한 퀵정렬 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define ARRAY_LENGTH 10
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define 매크로 영역 (형태처리 전처리 기문)			ex) A <-> : A와 B를 해당하는 타입을 빈공간으로 사용하여 교환

//  5. 퀵 정렬(Quick sort)
//     : 기준값을 정해두고, 왼쪽에서부터 i + 1번째 데이터와 n - i + 1번째 데이터를 비교하고, 정렬방법에 따라 이들을 교환함
//       -> 포인터가 중앙점인 교차점을 넘어가게 되면, 그 부분을 중심으로 리스트를 반토막내서 다시 같은 방식으로 비교 반복
//       -> 더 이상 분할이 불가능한 최소 단위(1개)로 분할 될 때까지 이를 반복
void quick_sort(int arr[], int direction, int start, int array_length) {

    if (array_length <= 0) {
        return;
    }

    int standard = arr[start];
    int left_start = start;
    int right_start = array_length;

    // 오름차순 (큰 수를 뒤로.. )
    if (direction == ascending_order) {

        // 배열 크기만큼 부분정렬 그룹별 싸이클 돌 수 있게 함
        for (int i = 0; i <= array_length; i++) {

            if (left_start == right_start) {
                printf("left와 right가 같은 지점 배열[%d]에 모임!\n", left_start);
                swap(int, arr[left_start], arr[start]);

                if (left_start > 0 && left_start <= array_length) {

                    quick_sort(arr, direction, start, left_start - 1);
                    quick_sort(arr, direction, left_start + 1, array_length);
                }

                break;
            }
            else if (left_start > right_start) {
                printf("left와 right가 배열[%d],  배열[%d]를 기준으로 교차함!\n", left_start, right_start);
                swap(int, arr[right_start], arr[start]);

                if (left_start > 0 && left_start <= array_length) {
                    quick_sort(arr, direction, start, right_start);
                    quick_sort(arr, direction, left_start, array_length);
                }
                break;
            }
            else if (left_start < right_start) {

                while(arr[left_start] < standard && left_start < array_length) left_start++;
                while (arr[right_start] > standard && right_start > start) right_start--;
                if (left_start <= right_start) {
					swap(int, arr[left_start], arr[right_start]);

                    if (left_start < array_length) {
                        left_start++;
                    }
                    if (right_start > start) {
                        right_start--;
                    }
				}
            }
            for (int i = 0; i < ARRAY_LENGTH; i++) {

                printf("%d ", arr[i]);
            }
            printf("\n");

        }

    }
    // 내림차순 (작은 수를 뒤로.. )
    else {

        // 배열 크기만큼 부분정렬 그룹별 싸이클 돌 수 있게 함
        for (int i = 0; i < array_length; i++) {

            if (i == array_length - 1 - i) {
                quick_sort(arr, direction, 0, i - 1);
                quick_sort(arr, direction, i + 1, array_length);
                break;
            }
            else if (i > array_length - 1 - i) {
                quick_sort(arr, direction, 0, array_length - 1 - i);
                quick_sort(arr, direction, i, array_length);
                break;
            }
            else if (i < array_length - 1 - i) {

                if (arr[i] < arr[array_length - 1 - i]) {
                    swap(int, arr[i], arr[array_length - 1 - i]);
                }
            }
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

    for (int i = 0; i < ARRAY_LENGTH; i++) {

        printf("%d ", ary_test[i]);
    }

    printf("\n");

    return 0;
}

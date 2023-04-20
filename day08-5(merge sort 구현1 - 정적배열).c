// 정렬
//  : 데이터 그룹 요소를 특정 기준으로 오름차순이나 내림차순으로 정리
//    -> 데이터를 집합으로 그룹화할 때 가장 기본적이고 중요한 알고리즘

//  4. 합병 정렬 (Merge sort)
//     : 합병정렬은 집합을 2개로 나누고 나누고 계속 나눠서, 더 이상 분할하면 정렬이 불가능해지는 수준까지 나눈 뒤, 각각을 정렬하고 이를 다시 하나로 합쳐서 정렬하는 방식으로 순서바꾸는 횟수를 최소화

//     # 합병 정렬의 의의?
//       : 시간복잡도 = 비교횟수 + 교환횟수...  
//         -> 교환횟수를 줄이면? 시간복잡도가 줄어든다 
//         -> 2개씩 묶어서 정렬한 묶음들을 또 2의 배수씩 붙여서, 다시 정렬하다보면 더 효율적이지 않것냐?
//            (= 분할정복법 사용 = 작은 해를 종합해서 큰 문제를 해결하기)

//     # 분할정복법(bottom-top)
//       : 문제를 최소단위로 분리(단순화) -> 최소단위 1개를 해결하며 나머지를 반복  -> 해결된 최소단위의 결과를 모아서 원래의 문제를 해결하는 전략
//         -> if 분리된 문제가 아직도 해결하기 어렵다면, 다시 분할 적용 (재귀호출을 활용한 녀석)

//     # 쉘정렬 vs 합병정렬
//       - 공통점 : 분할정복법 사용
//       - 차이점 : 부분리스트를 만드는 방법의 차이.. (쉘정렬 : x의 배수별로 n/x에 수렴하는 리스트의 수 -> 2개로 수렴, 합병정렬 : n/2에 해당하는 수의 부분리스트 -> 2개로 수렴)

// 정적할당을 사용한 합병정렬 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define ARRAY_LENGTH 100
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define 매크로 영역 (형태처리 전처리 기문)			ex) A <-> : A와 B를 해당하는 타입을 빈공간으로 사용하여 교환

//  4. 합병 정렬 (Merge sort)
//     : 합병정렬은 집합을 2개로 나누고 나누고 계속 나눠서, 더 이상 분할하면 정렬이 불가능해지는 수준까지 나눈 뒤, 각각을 정렬하고 이를 다시 하나로 합쳐서 정렬하는 방식으로 순서바꾸는 횟수를 최소화
void merge_sort(int arr[], int direction, int array_length) {

    // 오름차순 (큰 수를 뒤로.. )
    if (direction == ascending_order) {

        // 배열 크기만큼 부분정렬 그룹별 싸이클 돌 수 있게 함
        for (int i = 0; i < array_length; i++) {

            if (arr[i] > arr[array_length - 1 - i]) {
                swap(int, arr[i], arr[array_length - 1 - i]);
            }

        }

    }
    // 내림차순 (작은 수를 뒤로.. )
    else {

        // 배열 크기만큼 부분정렬 그룹별 싸이클 돌 수 있게 함
        for (int i = 0; i < ARRAY_LENGTH; i++) {

            for (int j = i; j < ARRAY_LENGTH - interval; j = j + interval) {

                for (int z = j + interval; z < ARRAY_LENGTH; z = z + interval) {

                    if (arr[j] < arr[z]) {
                        swap(int, arr[j], arr[z]);
                    }
                }
            }
        }
    }


    if (finish_flag == 1) {
        return;
    }

    // shell 부분 정렬 알고리즘을 위한 비교 싸이클
    interval /= divider;

    if (interval == 0) {
        interval = 1;
        finish_flag = 1;
    }
    else if (interval == 1) {

        finish_flag = 1;
    }

    shell_sort(arr, direction, interval, divider, finish_flag);

}

int main() {

    srand((unsigned int)time(NULL));

    printf("----------------------------------------------------------------------------\n");
    printf("배열의 길이는 50이며, 이진검색과 순차검색을 수행해봅니다.\n각 배열값은 각 배열의 이전 배열값 + a(1~5) 에 대응하는 값으로 입력됩니다.\n");
    printf("----------------------------------------------------------------------------\n\n");

    int ary_test[ARRAY_LENGTH] = { 0 };
    int input = 0;
    int direction = ascending_order;
    int array_length = ARRAY_LENGTH;

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
    merge_sort(ary_test, direction, array_length);

    printf("\n[merge sort 결과] \n");

    for (int i = 0; i < ARRAY_LENGTH; i++) {

        printf("%d ", ary_test[i]);
    }

    printf("\n");

    return 0;
}

// 정렬
//  : 데이터 그룹 요소를 특정 기준으로 오름차순이나 내림차순으로 정리
//    -> 데이터를 집합으로 그룹화할 때 가장 기본적이고 중요한 알고리즘

//  2. 삽입 정렬(insertion sort)
//     : 1싸이클당 데이터 그룹 요소의 비교대상 선정은 왼쪽부터 정렬 할 값을 선택하고, 그 녀석이 위치할 자리를 찾아 타요소들과 1:1로 전부 비교 
//       -> 값 비교 결과 배열의 오름차순(or 내림차순)을 기준으로 맞지 않는 결과가 나올시 N번째 요소와 교환
//          (= 대상값이 정렬된 배열에서 위치할 자리를 찾아 삽입하는 것과 같은 정렬방식)
//       -> 다음 싸이클의 비교대상은 2번째 자리 <-> 3 ~ n번째까지 비교

//     # 시간 복잡도 : n * (n + 1) / 2 = n^2  


// 정적할당을 사용한 삽입정렬 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define ARRAY_LENGTH 100
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define 매크로 영역 (형태처리 전처리 기문)			ex) A <-> : A와 B를 해당하는 타입을 빈공간으로 사용하여 교환

// 삽입 정렬(insertion sort)
//     : 1싸이클당 데이터 그룹 요소의 비교대상 선정은 왼쪽부터 정렬 할 값을 선택하고, 그 녀석이 위치할 자리를 찾아 타요소들과 1:1로 전부 비교 
//       -> 값 비교 결과 배열의 오름차순(or 내림차순)을 기준으로 맞지 않는 결과가 나올시 N번째 요소와 교환
//          (= 대상값이 정렬된 배열에서 위치할 자리를 찾아 삽입하는 것과 같은 정렬방식)
//       -> 다음 싸이클의 비교대상은 2번째 자리 <-> 3 ~ n번째까지 비교
void insertion_sort(int arr[], int direction) {

    // 오름차순 (큰 수를 뒤로.. )
    if (direction == ascending_order) {

        // 배열 크기만큼 싸이클 돌 수 있게 함
        for (int i = 0; i < ARRAY_LENGTH - 1; i++) {

            for (int j = i + 1; j < ARRAY_LENGTH; j++) {

                if (arr[i] > arr[j]) {
                    swap(int, arr[i], arr[j]);
                }
            }
        }

    }
    // 내림차순 (작은 수를 뒤로.. )
    else {

        // 배열 크기만큼 싸이클 돌 수 있게 함
        for (int i = 0; i < ARRAY_LENGTH - 1; i++) {

            for (int j = i + 1; j < ARRAY_LENGTH; j++) {

                if (arr[i] < arr[j]) {
                    swap(int, arr[i], arr[j]);
                }
            }
        }
    }

}

int main() {

    srand((unsigned int)time(NULL));

    printf("----------------------------------------------------------------------------\n");
    printf("배열의 길이는 50이며, 이진검색과 순차검색을 수행해봅니다.\n각 배열값은 각 배열의 이전 배열값 + a(1~5) 에 대응하는 값으로 입력됩니다.\n");
    printf("----------------------------------------------------------------------------\n\n");

    int ary_test[ARRAY_LENGTH] = { 0 };
    int input = 0;
    int direction = ascending_order;

    // 랜덤한 값이 들어갈수 있게 설계 (0 ~ 500)
    for (int i = 0; i < ARRAY_LENGTH; i++) {

        ary_test[i] = rand() % 501;

        printf("%d ", ary_test[i]);
    }

    printf("\n\n값 입력이 완료되었습니다. \n");

    printf("원하시는 방식의 정렬방식이 오름차순인가요? (0 : 오름차순, 그 이외 값 입력: 내림차순) : ");
    scanf_s("%d", &direction);

    // 버블 소트 실행
    insertion_sort(ary_test, direction);

    printf("\n[insertion sort 결과] \n");

    for (int i = 0; i < ARRAY_LENGTH; i++) {

        printf("%d ", ary_test[i]);
    }

    printf("\n");

    return 0;
}

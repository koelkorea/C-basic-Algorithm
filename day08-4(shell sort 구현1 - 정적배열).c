// 정렬
//  : 데이터 그룹 요소를 특정 기준으로 오름차순이나 내림차순으로 정리
//    -> 데이터를 집합으로 그룹화할 때 가장 기본적이고 중요한 알고리즘

//  3. 쉘 정렬(Shell sort)
//     : 1싸이클당 데이터 그룹 요소의 전체 리스트를 일정 숫자로 나눈 숫자의 결과값을 간격으로 정함
//       -> 1번째 값을 기준으로 간격별로 떨어진 값을 모아서, 부분 리스트로 나눔
//       -> 그렇게 만들어진 부분 리스트를 정렬해줌
//       -> 2번째 ~ 간격 -1 까지의 값들도 마찬가지로 부분리스트 정렬을 마침
//       -> 2번째 싸이클부터는 간격/(나누는수 * n)으로 간격을 점점 좁힌다
//          (= 그렇게 하면 간격이 1인 녀석을 수행 가능하게 됨)

//     # 시간 복잡도 : n^1.5  
//     # 논문에서는 나누는 값은 2가 가장 이상적이라고 함 (= 해보니까 어차피 최대공약수가 1인 녀석을 나누는 수로 쓰는 경우 부분리스트가 축소되지 않음)
//     # 쉘 정렬의 의의?
//       : 시간복잡도 = 비교횟수 + 교환횟수...  
//         -> 교환횟수를 줄이면? 시간복잡도가 줄어든다 
//            (= 애초에 비교를 효율적으로 해서 오름차순, 내림차순에 맞는 수가 최대한 빨리 자기 자리에 가까운 곳에 위치하면? 교환횟수가 줄지 않겠냐?
//         -> 각 시작점의 간격별로 부분 리스트를 만들고 비교를 해서, 각 그룹에서 가장 높거나 작은수를 앞으로 보내는걸 반복하면 좋겠지?
//            (= 분할정복법 = 작은 해를 종합해서 큰 문제를 해결하기)
//     # 분할정복법
//       : 문제를 최소단위로 분리(단순화) -> 최소단위 1개를 해결하며 나머지를 반복  -> 해결된 최소단위의 결과를 모아서 원래의 문제를 해결하는 전략
//         -> if 분리된 문제가 아직도 해결하기 어렵다면, 다시 분할 적용 (재귀호출을 활용한 녀석)

//     # 시간 복잡도 : n^1.5  

//        ex)  입력 배열
//             10	8	6	20	4	3	22	1	0	15	16
//             
//             간격 5를 기준 - 비교대상 정리
//             10					3					16
//                 8					22
//                     6					1
//                         20					0
//                             4					15
//             
//             간격 5를 기준 - 부분적 리스트 정렬 후
//             3					10					16
//                 8					22
//                     1					6
//                         0					20
//                             4					15
//             
//             간격 5 배열 정렬 후
//             3	8	1	0	4	10	22	6	20	15	16
//             
//             간격 3를 기준 - 비교대상 정리
//             3			0			22			15
//                 8			4			6			16
//                     1			10			20
//             
//             간격 3를 기준 - 부분적 리스트 정렬 후
//             0			3			15			22
//                 4			6			8			16
//                     1			10			20
//             
//             간격 3 배열 정렬 후
//             0	4	1	3	6	10	15	8	20	22	16
//             
//             간격 1 배열 정렬 후
//             0	1	3	4	6	8	10	15	16	20	22

// 정적할당을 사용한 버블소트 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define ARRAY_LENGTH 100
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define 매크로 영역 (형태처리 전처리 기문)			ex) A <-> : A와 B를 해당하는 타입을 빈공간으로 사용하여 교환

//  3. 쉘 정렬(Shell sort)
//     : 데이터 그룹 요소의 전체 리스트를 일정 간격으로 커팅해서 부분 리스트로 나눔
//       -> 그리고 각 부분 리스트를 정렬 정렬해 줌
void shell_sort(int arr[], int direction, int interval, int divider, int finish_flag) {

    // 오름차순 (큰 수를 뒤로.. )
    if (direction == ascending_order) {

        // 배열 크기만큼 부분정렬 그룹별 싸이클 돌 수 있게 함
        for (int i = 0; i < interval; i++) {

            for (int j = i; j < ARRAY_LENGTH - interval; j = j + interval) {

                for (int z = j + interval; z < ARRAY_LENGTH; z = z + interval) {

                    if (arr[j] > arr[z]) {
                        swap(int, arr[j], arr[z]);
                    }
                }
            }
        }

    }
    // 내림차순 (작은 수를 뒤로.. )
    else {

        // 배열 크기만큼 부분정렬 그룹별 싸이클 돌 수 있게 함
        for (int i = 0; i < interval; i++) {

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
    int finish_flag = 0;

    // 랜덤한 값이 들어갈수 있게 설계 (0 ~ 500)
    for (int i = 0; i < ARRAY_LENGTH; i++) {

        ary_test[i] = rand() % 501;

        printf("%d ", ary_test[i]);
    }

    printf("\n\n값 입력이 완료되었습니다. \n");

    int divider;

    printf("shell 소트를 위해 집단을 나눌값을 정해주세요 : ");
    scanf_s("%d", &divider);

    // shell 부분 정렬 알고리즘의 간격
    int interval = (ARRAY_LENGTH - 1) / divider;

    printf("원하시는 방식의 정렬방식이 오름차순인가요? (0 : 오름차순, 그 이외 값 입력: 내림차순) : ");
    scanf_s("%d", &direction);

    // 쉘 소트 실행
    shell_sort(ary_test, direction, interval, divider, finish_flag);

    printf("\n[shell sort 결과] \n");

    for (int i = 0; i < ARRAY_LENGTH; i++) {

        printf("%d ", ary_test[i]);
    }

    printf("\n");

    return 0;
}

// 유클리드의 최대공약수 알고리즘
//	-> 2개의 수를 제시하면, 그 수의 최대공약수를 만들어라 
//	   ex) 12, 66 -> 최대공약수 = 6
//	   ex) 56056, 14157 -> 최대공약수 143

// (구현 1)
//  1. m의 약수 리스트 구하기 -> list_1 - 12 : { 1, 2, 3, 4, 6, 12 }
//  2. n의 약수 리스트 구하기 -> list_2 - 66 : { 1, 2, 3, 6, 11, 22, 33, 66 }
//  3. list_1과 list_2에 공통으로 들어가 있는 수 -> list_3 : { 1, 2, 3, 6 }
//  4. list_3의 가장 큰 수 -> 최대 공약수 : 6

// (구현 2)
//  1. m과 n중 작은 수를 t로 넣는다
//  2. t로 m과 n을 나누어 둘 다 나머지가 0이면 종료. 아니면 t = t - 1 반복
//  3. t는 최대공약수

// (구현 3 : m과 n중 큰 수를 A, 작은 수를 B로 정의)
//  1. A를 B로 나누고 그 나머지를 R이라고 한다
//  2. R이 0이 아니면 B를 A에 대입, R을 B에 대입 후, 1번 과정 반복
//  3. R이 0이면 B가 최대공약수, 반복 종료.


// (구현1) 방식
#include <stdio.h>
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define 매크로 영역 (형태처리 전처리 기문)			ex) A <-> : A와 B를 해당하는 타입을 빈공간으로 사용하여 교환

int main(void) {

    int big = 0, small = 0, result = 0;

    // (중요) visual studio의 기본 stack단위는 1MB... 따라서 동적할당을 통한 Heap으로 넘기지 않는 바에야, 정적할당으로는 1mb이상으로 배열을 못 만든다 명심해야 함 
    int big_devider[100000], small_devider[100000] = { 0 };

    printf_s("지금부터 최대공약수를 구할겁니다. 당신이 생각하는 2개의 수를 입력해주세요 : ");
    scanf_s("%d %d", &big, &small);

    if (small > big) {
        swap(int, big, small);
    }

    for (int i = 1; i <= big; i++) {

        if (big % i == 0) {
            big_devider[i - 1] = i;
            printf("%d ", big_devider[i - 1]);
        }
    }

    printf("\n");

    for (int i = 1; i <= small; i++) {

        if (small % i == 0) {
            small_devider[i - 1] = i;
            printf("%d ", small_devider[i - 1]);
        }
    }

    printf("\n");

    for (int i = big; i >= 1; i--) {

        if (big_devider[i - 1] != 0) {

            for (int j = small; j >= 1; j--) {

                if (small_devider[j - 1] != 0 && big_devider[i - 1] == small_devider[j - 1]) {

                    printf("big %d, small %d \n", big_devider[i - 1], small_devider[j - 1]);
                    result = big_devider[i - 1];
                    break;
                }
            }
        }

        if (result != 0) {
            break;
        }
    }


    printf_s("\n\n입력하신 %d와 %d의 최대공약수는 %d입니다.\n", big, small, result);

    return 0;
}

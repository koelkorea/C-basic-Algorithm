// 재귀함수 알고리즘(Recursion Function)
//  : 함수가 수행 도중에 자기 자신을 다시 호출하여 큰 문제를 작은 연산으로 쪼개는 방식(TOP-DOWN)으로 문제를 해결하는 기법
//    -> 정의자체가 순환적으로 되어 있는 경우에 적합한 방법

//    ex) 팩토리얼(factorial), 피보나치 수열(Fibonacci), 하노이의 탑, 거듭제곱 연산

//  # 재귀함수 장점
//     : 반복문을 짜서 문제를 해결하는 것보다 단순 + 더 효율적인 순환적인 방법

//  # 재귀함수 단점
//    1. 일단 설계하기가 힘들다.
//    2. 계산의 단위가 커질수록, 쪼개다보면 같은 중복된 내용 계산을 반복하는 일을 어떻게 할 수가 없음 -> 이 문제를 해결하기 위해 배열을 사용하여 값을 저장하는 동적계획법(dyanamic programming) 존재
//       (ex) 피보나치 수열의 계산
//            : 같은 항이 중복해서 계산되는 순환 호출을 사용했을 경우의 비효율성 (이러한 현상은 n이 커지면 더 심해짐)
//               ex) fib(6) -> fib(4)이 2번, fib(3)이 3번 중복 계산


// 최대공약수(GCD) & 최소공배수(LCM)을 다음의 조건을 만족시키는 재귀함수 형식의 메서드로 구현해라
//  - 최대공약수(GCD)
//    1. A,B 정수를 parameter로 받는다
//    2 R = A % B   ->  R != 0 ->  A = B, B = R
//                  ->  R == 0 ->  B = 최대 공약수

//  - 최소공배수(LCM)
//    1. A,B 정수를 parameter로 받는다
//    2. A * B / 최대공약수(GCD) = 최소공배수(LCM)

#include <stdio.h>
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define 매크로 영역 (형태처리 전처리 기문)			ex) A <-> : A와 B를 해당하는 타입을 빈공간으로 사용하여 교환

// 최대공약수
int GCD(int big, int small) {

    int rest_as_recuriable = big % small;

    if (rest_as_recuriable != 0) {

        big = small;
        small = rest_as_recuriable;
        
        return GCD(big, small);

    }
    
    return small;
}

// 최소공배수
int LCM(int big, int small) {
    return big * small / GCD(big, small);
}

int main(void) {

    int big = 0, small = 0, result_GCD = 0, result_LCM = 0;

    printf_s("지금부터 최대공약수, 최소공배수를 구할겁니다. 당신이 생각하는 2개의 수를 입력해주세요 : ");
    scanf_s("%d %d", &big, &small);

    if (small > big) {
        swap(int, big, small);
    }

    result_GCD = GCD(big, small);
    result_LCM = LCM(big, small);

    printf_s("입력하신 %d와 %d의 최대공약수는 %d, 최소공배수는 %d입니다.\n", big, small, result_GCD, result_LCM);

    return 0;
}

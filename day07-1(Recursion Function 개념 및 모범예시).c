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


// 재귀함수의 예시들 - 팩토리얼(factorial), 피보나치 수열(Fibonacci), 하노이의 탑, 거듭제곱 연산
#include <stdio.h>

// 팩토리얼(factorial)(재귀함수 ver)
int factorial(int n) {
    printf("factorial(%d)\n", n);
    if (n <= 1) return 1;
    else return (n * factorial(n - 1));
}

// 팩토리얼(factorial)(for문 ver)
int factorial_for(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) result = result * i;
    return result;
}

// 거듭제곱 연산(재귀함수 ver)
double power(double x, int n) {
    if (n == 0)return 1;
    else if ((n % 2) == 0) return power(x * x, n / 2);
    else return x * power(x * x, (n - 1) / 2);
}

// 거듭제곱 연산(for문 ver)
double power_for(double x, int n) {
    double result = 1.0;
    for (int i = 0; i < n; i++)  result = result * x;
    return result;
}

// 피보나치 수열(Fibonacci)(재귀함수 ver)
int fib(int n) {
    printf("fibonacci %d \n", n);
    if (n == 0) return 0;
    if (n == 1) return 1;
    return (fib(n - 1) + fib(n - 2));
}

// 피보나치 수열(Fibonacci)(for문 ver)
int fib_for(int n) {
    int n_2 = 0, n_1 = 1, result = 0;
    if (n == 0) return n_2;
    if (n == 1) return n_1;
    for (int i = 2; i <= n; i++) {
        result = n_2 + n_1;
        n_2 = n_1;
        n_1 = result;
    }
    return result;
}

// 하노이의 탑
void hanio_tower(int n, char from, char tmp, char to) {
    if (n == 1) printf("원판 1 : %c에서 %c으로 옮긴다.\n", from, to);
    else {
        for (int i = 0; i < n; i++) printf("%d", n);
        printf("\n");
        hanio_tower(n - 1, from, to, tmp);
        for (int i = 0; i < n; i++) printf("%d", n);
        printf("\n");
        printf("원판 %d : %c에서 %c으로 옮긴다.\n", n, from, to);
        for (int i = 0; i < n; i++) printf("%d", n);
        printf("\n");
        hanio_tower(n - 1, tmp, from, to);
        for (int i = 0; i < n; i++) printf("%d", n);
        printf("\n");
    }
}

// 두 수의 최대공약수
int gcd(int a, int b) {
    int r = a % b;
    if (r == 0) return b;
    else return gcd(b, r);
}

// 두 수의 최소공배수
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    printf("5 factorial %d\n", factorial(5));
    printf("6 factorial %d\n\n", factorial_for(6));
    printf("9.9^9 %20.2lf\n", power(9.9, 9));
    printf("10^10 %20.2lf\n\n", power_for(10.0, 10));
    printf("7 fibonacci %d\n", fib(7));
    printf("8 fibonacci %d\n\n", fib_for(8));

    printf("11 GCD : %5d, LCM : %5d \n\n", gcd(12, 66), lcm(12, 66));
    hanio_tower(4, 'A', 'B', 'C');
    return 0;
}

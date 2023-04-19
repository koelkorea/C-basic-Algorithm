// ����Լ� �˰���(Recursion Function)
//  : �Լ��� ���� ���߿� �ڱ� �ڽ��� �ٽ� ȣ���Ͽ� ū ������ ���� �������� �ɰ��� ���(TOP-DOWN)���� ������ �ذ��ϴ� ���
//    -> ������ü�� ��ȯ������ �Ǿ� �ִ� ��쿡 ������ ���

//    ex) ���丮��(factorial), �Ǻ���ġ ����(Fibonacci), �ϳ����� ž, �ŵ����� ����

//  # ����Լ� ����
//     : �ݺ����� ¥�� ������ �ذ��ϴ� �ͺ��� �ܼ� + �� ȿ������ ��ȯ���� ���

//  # ����Լ� ����
//    1. �ϴ� �����ϱⰡ �����.
//    2. ����� ������ Ŀ������, �ɰ��ٺ��� ���� �ߺ��� ���� ����� �ݺ��ϴ� ���� ��� �� ���� ���� -> �� ������ �ذ��ϱ� ���� �迭�� ����Ͽ� ���� �����ϴ� ������ȹ��(dyanamic programming) ����
//       (ex) �Ǻ���ġ ������ ���
//            : ���� ���� �ߺ��ؼ� ���Ǵ� ��ȯ ȣ���� ������� ����� ��ȿ���� (�̷��� ������ n�� Ŀ���� �� ������)
//               ex) fib(6) -> fib(4)�� 2��, fib(3)�� 3�� �ߺ� ���


// ����Լ��� ���õ� - ���丮��(factorial), �Ǻ���ġ ����(Fibonacci), �ϳ����� ž, �ŵ����� ����
#include <stdio.h>

// ���丮��(factorial)(����Լ� ver)
int factorial(int n) {
    printf("factorial(%d)\n", n);
    if (n <= 1) return 1;
    else return (n * factorial(n - 1));
}

// ���丮��(factorial)(for�� ver)
int factorial_for(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) result = result * i;
    return result;
}

// �ŵ����� ����(����Լ� ver)
double power(double x, int n) {
    if (n == 0)return 1;
    else if ((n % 2) == 0) return power(x * x, n / 2);
    else return x * power(x * x, (n - 1) / 2);
}

// �ŵ����� ����(for�� ver)
double power_for(double x, int n) {
    double result = 1.0;
    for (int i = 0; i < n; i++)  result = result * x;
    return result;
}

// �Ǻ���ġ ����(Fibonacci)(����Լ� ver)
int fib(int n) {
    printf("fibonacci %d \n", n);
    if (n == 0) return 0;
    if (n == 1) return 1;
    return (fib(n - 1) + fib(n - 2));
}

// �Ǻ���ġ ����(Fibonacci)(for�� ver)
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

// �ϳ����� ž
void hanio_tower(int n, char from, char tmp, char to) {
    if (n == 1) printf("���� 1 : %c���� %c���� �ű��.\n", from, to);
    else {
        for (int i = 0; i < n; i++) printf("%d", n);
        printf("\n");
        hanio_tower(n - 1, from, to, tmp);
        for (int i = 0; i < n; i++) printf("%d", n);
        printf("\n");
        printf("���� %d : %c���� %c���� �ű��.\n", n, from, to);
        for (int i = 0; i < n; i++) printf("%d", n);
        printf("\n");
        hanio_tower(n - 1, tmp, from, to);
        for (int i = 0; i < n; i++) printf("%d", n);
        printf("\n");
    }
}

// �� ���� �ִ�����
int gcd(int a, int b) {
    int r = a % b;
    if (r == 0) return b;
    else return gcd(b, r);
}

// �� ���� �ּҰ����
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

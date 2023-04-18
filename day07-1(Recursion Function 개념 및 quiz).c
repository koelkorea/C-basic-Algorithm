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


// �ִ�����(GCD) & �ּҰ����(LCM)�� ������ ������ ������Ű�� ����Լ� ������ �޼���� �����ض�
//  - �ִ�����(GCD)
//    1. A,B ������ parameter�� �޴´�
//    2 R = A % B   ->  R != 0 ->  A = B, B = R
//                  ->  R == 0 ->  B = �ִ� �����

//  - �ּҰ����(LCM)
//    1. A,B ������ parameter�� �޴´�
//    2. A * B / �ִ�����(GCD) = �ּҰ����(LCM)

#include <stdio.h>
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define ��ũ�� ���� (����ó�� ��ó�� �⹮)			ex) A <-> : A�� B�� �ش��ϴ� Ÿ���� ��������� ����Ͽ� ��ȯ

// �ִ�����
int GCD(int big, int small) {

    int rest_as_recuriable = big % small;

    if (rest_as_recuriable != 0) {

        big = small;
        small = rest_as_recuriable;
        
        return GCD(big, small);

    }
    
    return small;
}

// �ּҰ����
int LCM(int big, int small) {
    return big * small / GCD(big, small);
}

int main(void) {

    int big = 0, small = 0, result_GCD = 0, result_LCM = 0;

    printf_s("���ݺ��� �ִ�����, �ּҰ������ ���Ұ̴ϴ�. ����� �����ϴ� 2���� ���� �Է����ּ��� : ");
    scanf_s("%d %d", &big, &small);

    if (small > big) {
        swap(int, big, small);
    }

    result_GCD = GCD(big, small);
    result_LCM = LCM(big, small);

    printf_s("�Է��Ͻ� %d�� %d�� �ִ������� %d, �ּҰ������ %d�Դϴ�.\n", big, small, result_GCD, result_LCM);

    return 0;
}

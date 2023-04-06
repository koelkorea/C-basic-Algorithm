// ��Ŭ������ �ִ����� �˰���
//	-> 2���� ���� �����ϸ�, �� ���� �ִ������� ������ 
//	   ex) 12, 66 -> �ִ����� = 6
//	   ex) 56056, 14157 -> �ִ����� 143

// (���� 1)
//  1. m�� ��� ����Ʈ ���ϱ� -> list_1 - 12 : { 1, 2, 3, 4, 6, 12 }
//  2. n�� ��� ����Ʈ ���ϱ� -> list_2 - 66 : { 1, 2, 3, 6, 11, 22, 33, 66 }
//  3. list_1�� list_2�� �������� �� �ִ� �� -> list_3 : { 1, 2, 3, 6 }
//  4. list_3�� ���� ū �� -> �ִ� ����� : 6

// (���� 2)
//  1. m�� n�� ���� ���� t�� �ִ´�
//  2. t�� m�� n�� ������ �� �� �������� 0�̸� ����. �ƴϸ� t = t - 1 �ݺ�
//  3. t�� �ִ�����

// (���� 3 : m�� n�� ū ���� A, ���� ���� B�� ����)
//  1. A�� B�� ������ �� �������� R�̶�� �Ѵ�
//  2. R�� 0�� �ƴϸ� B�� A�� ����, R�� B�� ���� ��, 1�� ���� �ݺ�
//  3. R�� 0�̸� B�� �ִ�����, �ݺ� ����.


// (����1) ���
#include <stdio.h>
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define ��ũ�� ���� (����ó�� ��ó�� �⹮)			ex) A <-> : A�� B�� �ش��ϴ� Ÿ���� ��������� ����Ͽ� ��ȯ

int main(void) {

    int big = 0, small = 0, result = 0;

    // (�߿�) visual studio�� �⺻ stack������ 1MB... ���� �����Ҵ��� ���� Heap���� �ѱ��� �ʴ� �ٿ���, �����Ҵ����δ� 1mb�̻����� �迭�� �� ����� ����ؾ� �� 
    int big_devider[100000], small_devider[100000] = { 0 };

    printf_s("���ݺ��� �ִ������� ���Ұ̴ϴ�. ����� �����ϴ� 2���� ���� �Է����ּ��� : ");
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


    printf_s("\n\n�Է��Ͻ� %d�� %d�� �ִ������� %d�Դϴ�.\n", big, small, result);

    return 0;
}

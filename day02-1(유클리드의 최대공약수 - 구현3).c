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


// (����3) ���
#include <stdio.h>
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define ��ũ�� ���� (����ó�� ��ó�� �⹮)			ex) A <-> : A�� B�� �ش��ϴ� Ÿ���� ��������� ����Ͽ� ��ȯ

int main(void) {

    int big = 0, small = 0, result = 0, changable_big = 0, changable_small = 0, changable_rest = 0;

    printf_s("���ݺ��� �ִ������� ���Ұ̴ϴ�. ����� �����ϴ� 2���� ���� �Է����ּ��� : ");
    scanf_s("%d %d", &big, &small);

    if (small > big) {
        swap(int, big, small);
    }

    result = small;

    if (big % small != 0) {

        changable_big = big;
        changable_small = small;
        changable_rest = big % small;

        do {

            changable_big = changable_small;
            changable_small = changable_rest;
            changable_rest = changable_big % changable_small;
            
            if (changable_rest == 0) {
                result = changable_small;
            }

        } while (changable_rest != 0);

    }

    printf_s("�Է��Ͻ� %d�� %d�� �ִ������� %d�Դϴ�.\n", big, small, result);

    return 0;
}

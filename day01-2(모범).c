#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TERMS 20

// [������] ���׽� ��¿� �Լ� (���׽� ����ü ������, ���� ���׽��� ��Ұ��� ���� �ִ�ġ(0,0)�� �� �� index������ �ݺ��� ����)
typedef struct {
    int coef; // ���
    int expon; // ����
}polynomial;

char compare(int a, int b) {
    if (a > b) return '>';
    else if (a == b) return '=';
    else return '<';
}

int AddPoly(polynomial arr1[], int size1, polynomial arr2[], int size2, polynomial result[]) {

    int tempcoef, IdxArr1 = 0, IdxArr2 = 0, IdxResult = 0;

    while (IdxArr1 < size1 && IdxArr2 < size2) {

        switch (compare(arr1[IdxArr1].expon, arr2[IdxArr2].expon)) {
        case '>':
            result[IdxResult].coef = arr1[IdxArr1].coef;
            result[IdxResult].expon = arr1[IdxArr1].expon;
            IdxArr1++;
            IdxResult++;
            break;
        case '=':
            result[IdxResult].coef = arr1[IdxArr1].coef + arr2[IdxArr2].coef;
            result[IdxResult].expon = arr1[IdxArr1].expon;
            IdxArr1++;
            IdxArr2++;
            IdxResult++;
            break;
        case '<':
            result[IdxResult].coef = arr2[IdxArr2].coef;
            result[IdxResult].expon = arr2[IdxArr2].expon;
            IdxArr2++;
            IdxResult++;
            break;
        }
    }

    for (; IdxArr1 < size1; IdxArr1++, IdxResult++) {
        result[IdxResult].coef = arr1[IdxArr1].coef;
        result[IdxResult].expon = arr1[IdxArr1].expon;
    }

    for (; IdxArr2 < size2; IdxArr2++, IdxResult++) {
        result[IdxResult].coef = arr2[IdxArr2].coef;
        result[IdxResult].expon = arr2[IdxArr2].expon;
    }

    for (int i = 0; i <= IdxResult; i++) {
        printf("----------");
    }

    printf("\n");
    return IdxResult;
}

void print(polynomial arr[], int size) {

    for (int i = 0; i < size - 1; i++) {

        printf("%3d x^%d + ", arr[i].coef, arr[i].expon);
    }

    printf("%3d x^%d\n", arr[size - 1].coef, arr[size - 1].expon);
}

int input(polynomial arr[], int size) {

    int k = 0;

    for (int i = 0; i < size; i++) {

        polynomial temp;
        temp.coef = rand() % 10;
        if (temp.coef == 0) continue;
        temp.expon = size - 1 - i;
        arr[k++] = temp;
    }

    return k;
}

int main(void) {

    srand((unsigned)time(NULL));

    polynomial expression1[MAX_TERMS] = { 0 };
    polynomial expression2[MAX_TERMS] = { 0 };
    polynomial result[MAX_TERMS] = { 0 };

    int ExCnt1, ExCnt2, ReCnt;

    ExCnt1 = input(expression1, sizeof(expression1) / sizeof(expression1[0]));
    print(expression1, ExCnt1);

    ExCnt2 = input(expression2, sizeof(expression2) / sizeof(expression2[0]));
    print(expression2, ExCnt2);

    ReCnt = AddPoly(expression1, ExCnt1, expression2, ExCnt2, result);
    print(result, ReCnt);

    return 0;
}

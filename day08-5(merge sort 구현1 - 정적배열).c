// ����
//  : ������ �׷� ��Ҹ� Ư�� �������� ���������̳� ������������ ����
//    -> �����͸� �������� �׷�ȭ�� �� ���� �⺻���̰� �߿��� �˰���

//  4. �պ� ���� (Merge sort)
//     : �պ������� ������ 2���� ������ ������ ��� ������, �� �̻� �����ϸ� ������ �Ұ��������� ���ر��� ���� ��, ������ �����ϰ� �̸� �ٽ� �ϳ��� ���ļ� �����ϴ� ������� �����ٲٴ� Ƚ���� �ּ�ȭ

//     # �պ� ������ ����?
//       : �ð����⵵ = ��Ƚ�� + ��ȯȽ��...  
//         -> ��ȯȽ���� ���̸�? �ð����⵵�� �پ��� 
//         -> 2���� ��� ������ �������� �� 2�� ����� �ٿ���, �ٽ� �����ϴٺ��� �� ȿ�������� �ʰͳ�?
//            (= ���������� ��� = ���� �ظ� �����ؼ� ū ������ �ذ��ϱ�)

//     # ����������(bottom-top)
//       : ������ �ּҴ����� �и�(�ܼ�ȭ) -> �ּҴ��� 1���� �ذ��ϸ� �������� �ݺ�  -> �ذ�� �ּҴ����� ����� ��Ƽ� ������ ������ �ذ��ϴ� ����
//         -> if �и��� ������ ������ �ذ��ϱ� ��ƴٸ�, �ٽ� ���� ���� (���ȣ���� Ȱ���� �༮)

//     # ������ vs �պ�����
//       - ������ : ���������� ���
//       - ������ : �κи���Ʈ�� ����� ����� ����.. (������ : x�� ������� n/x�� �����ϴ� ����Ʈ�� �� -> 2���� ����, �պ����� : n/2�� �ش��ϴ� ���� �κи���Ʈ -> 2���� ����)

// �����Ҵ��� ����� �պ����� ����
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <time.h>
#define ARRAY_LENGTH 100
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define ��ũ�� ���� (����ó�� ��ó�� �⹮)			ex) A <-> : A�� B�� �ش��ϴ� Ÿ���� ��������� ����Ͽ� ��ȯ

//  4. �պ� ���� (Merge sort)
//     : �պ������� ������ 2���� ������ ������ ��� ������, �� �̻� �����ϸ� ������ �Ұ��������� ���ر��� ���� ��, ������ �����ϰ� �̸� �ٽ� �ϳ��� ���ļ� �����ϴ� ������� �����ٲٴ� Ƚ���� �ּ�ȭ
void merge_sort(int arr[], int direction, int array_length) {

    // �������� (ū ���� �ڷ�.. )
    if (direction == ascending_order) {

        // �迭 ũ�⸸ŭ �κ����� �׷캰 ����Ŭ �� �� �ְ� ��
        for (int i = 0; i < array_length; i++) {

            if (arr[i] > arr[array_length - 1 - i]) {
                swap(int, arr[i], arr[array_length - 1 - i]);
            }

        }

    }
    // �������� (���� ���� �ڷ�.. )
    else {

        // �迭 ũ�⸸ŭ �κ����� �׷캰 ����Ŭ �� �� �ְ� ��
        for (int i = 0; i < ARRAY_LENGTH; i++) {

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

    // shell �κ� ���� �˰����� ���� �� ����Ŭ
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
    printf("�迭�� ���̴� 50�̸�, �����˻��� �����˻��� �����غ��ϴ�.\n�� �迭���� �� �迭�� ���� �迭�� + a(1~5) �� �����ϴ� ������ �Էµ˴ϴ�.\n");
    printf("----------------------------------------------------------------------------\n\n");

    int ary_test[ARRAY_LENGTH] = { 0 };
    int input = 0;
    int direction = ascending_order;
    int array_length = ARRAY_LENGTH;

    // ������ ���� ���� �ְ� ���� (0 ~ 500)
    for (int i = 0; i < ARRAY_LENGTH; i++) {

        ary_test[i] = rand() % 501;

        printf("%d ", ary_test[i]);
    }

    printf("\n\n�� �Է��� �Ϸ�Ǿ����ϴ�. \n");

    //int divider;

    //printf("shell ��Ʈ�� ���� ������ �������� �����ּ��� : ");
    //scanf_s("%d", &divider);

    //// shell �κ� ���� �˰����� ����
    //int interval = (ARRAY_LENGTH - 1) / divider;

    printf("���Ͻô� ����� ���Ĺ���� ���������ΰ���? (0 : ��������, �� �̿� �� �Է�: ��������) : ");
    scanf_s("%d", &direction);

    // ���� ��Ʈ ����
    merge_sort(ary_test, direction, array_length);

    printf("\n[merge sort ���] \n");

    for (int i = 0; i < ARRAY_LENGTH; i++) {

        printf("%d ", ary_test[i]);
    }

    printf("\n");

    return 0;
}

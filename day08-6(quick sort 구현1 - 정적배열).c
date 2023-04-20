// ����
//  : ������ �׷� ��Ҹ� Ư�� �������� ���������̳� ������������ ����
//    -> �����͸� �������� �׷�ȭ�� �� ���� �⺻���̰� �߿��� �˰���

//  5. �� ����(Quick sort)
//     : ���ذ��� ���صΰ�, ���ʿ������� i + 1��° �����Ϳ� n - i + 1��° �����͸� ���ϰ�, ���Ĺ���� ���� �̵��� ��ȯ��
//       -> �����Ͱ� �߾����� �������� �Ѿ�� �Ǹ�, �� �κ��� �߽����� ����Ʈ�� ���丷���� �ٽ� ���� ������� �� �ݺ�
//       -> �� �̻� ������ �Ұ����� �ּ� ����(1��)�� ���� �� ������ �̸� �ݺ�

//     # ��������� ���� ���� ���� ���
//     # top-bottom(= ū ������ �ذ��ϴ� �������� �����ؼ� ���� ������ �ذ��ϱ�) ��� ���

// �����Ҵ��� ����� ������ ����
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <time.h>
#define ARRAY_LENGTH 10
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define ��ũ�� ���� (����ó�� ��ó�� �⹮)			ex) A <-> : A�� B�� �ش��ϴ� Ÿ���� ��������� ����Ͽ� ��ȯ

//  5. �� ����(Quick sort)
//     : ���ذ��� ���صΰ�, ���ʿ������� i + 1��° �����Ϳ� n - i + 1��° �����͸� ���ϰ�, ���Ĺ���� ���� �̵��� ��ȯ��
//       -> �����Ͱ� �߾����� �������� �Ѿ�� �Ǹ�, �� �κ��� �߽����� ����Ʈ�� ���丷���� �ٽ� ���� ������� �� �ݺ�
//       -> �� �̻� ������ �Ұ����� �ּ� ����(1��)�� ���� �� ������ �̸� �ݺ�
void quick_sort(int arr[], int direction, int start, int array_length) {

    if (array_length <= 0) {
        return;
    }

    int standard = arr[start];
    int left_start = start;
    int right_start = array_length;

    // �������� (ū ���� �ڷ�.. )
    if (direction == ascending_order) {

        // �迭 ũ�⸸ŭ �κ����� �׷캰 ����Ŭ �� �� �ְ� ��
        for (int i = 0; i <= array_length; i++) {

            if (left_start == right_start) {
                printf("left�� right�� ���� ���� �迭[%d]�� ����!\n", left_start);
                swap(int, arr[left_start], arr[start]);

                if (left_start > 0 && left_start <= array_length) {

                    quick_sort(arr, direction, start, left_start - 1);
                    quick_sort(arr, direction, left_start + 1, array_length);
                }

                break;
            }
            else if (left_start > right_start) {
                printf("left�� right�� �迭[%d],  �迭[%d]�� �������� ������!\n", left_start, right_start);
                swap(int, arr[right_start], arr[start]);

                if (left_start > 0 && left_start <= array_length) {
                    quick_sort(arr, direction, start, right_start);
                    quick_sort(arr, direction, left_start, array_length);
                }
                break;
            }
            else if (left_start < right_start) {

                while(arr[left_start] < standard && left_start < array_length) left_start++;
                while (arr[right_start] > standard && right_start > start) right_start--;
                if (left_start <= right_start) {
					swap(int, arr[left_start], arr[right_start]);

                    if (left_start < array_length) {
                        left_start++;
                    }
                    if (right_start > start) {
                        right_start--;
                    }
				}
            }
            for (int i = 0; i < ARRAY_LENGTH; i++) {

                printf("%d ", arr[i]);
            }
            printf("\n");

        }

    }
    // �������� (���� ���� �ڷ�.. )
    else {

        // �迭 ũ�⸸ŭ �κ����� �׷캰 ����Ŭ �� �� �ְ� ��
        for (int i = 0; i < array_length; i++) {

            if (i == array_length - 1 - i) {
                quick_sort(arr, direction, 0, i - 1);
                quick_sort(arr, direction, i + 1, array_length);
                break;
            }
            else if (i > array_length - 1 - i) {
                quick_sort(arr, direction, 0, array_length - 1 - i);
                quick_sort(arr, direction, i, array_length);
                break;
            }
            else if (i < array_length - 1 - i) {

                if (arr[i] < arr[array_length - 1 - i]) {
                    swap(int, arr[i], arr[array_length - 1 - i]);
                }
            }
        }
    }

}

int main() {

    srand((unsigned int)time(NULL));

    printf("----------------------------------------------------------------------------\n");
    printf("�迭�� ���̴� 100�̸�, quick sort�� �����غ��ϴ�.\n�� �迭���� �� �迭�� ���� �迭�� + a(1~5) �� �����ϴ� ������ �Էµ˴ϴ�.\n");
    printf("----------------------------------------------------------------------------\n\n");

    int ary_test[ARRAY_LENGTH] = { 0 };
    int input = 0;
    int direction = ascending_order;
    int array_length = ARRAY_LENGTH - 1;

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
    quick_sort(ary_test, direction, 0, array_length);

    printf("\n[quick sort ���] \n");

    for (int i = 0; i < ARRAY_LENGTH; i++) {

        printf("%d ", ary_test[i]);
    }

    printf("\n");

    return 0;
}

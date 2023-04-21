// ����
//  : ������ �׷� ��Ҹ� Ư�� �������� ���������̳� ������������ ����
//    -> �����͸� �������� �׷�ȭ�� �� ���� �⺻���̰� �߿��� �˰���

//  5. �� ����(Quick sort)
//     : ����Ʈ �ȿ� �����ϴ� ������ ���� ���ذ����� ���صΰ�, 
//       -> ���ʿ������� �����͸� ���ذ��� ���Ĺ���� ���� ũ�� ������ �� ���Ĺ���� ���� ������ �� ������ ���� ������, ������ �����ʺ��� �����͸� ���ذ��� ���ؼ� ���ݴ��� ��찡 �����ϴ��� Ȯ��
//          -> �����ʿ��� ���簡 �´� ���� ���̸�? ->  ���ʰ� �������� ���� ��ȯ�ϰ�, �� ���� ������ġ�� ���� ������ �Ȱ��� ��� ����
//       -> �����̴� �������̴� �����Ͱ� ��ġ�� �ȴٸ�? �� �κ��� �߽����� ����Ʈ�� �丷���� �ٽ� ���� ������� �� �ݺ�
//       -> ��� �κи���Ʈ�� �� �̻� ������ �Ұ����� �ּ� ����(1��)�� ���� �� ������ �̸� �ݺ�

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
//     : ����Ʈ �ȿ� �����ϴ� ������ ���� ���ذ����� ���صΰ�, 
//       -> ���ʿ������� �����͸� ���ذ��� ���Ĺ���� ���� ũ�� ������ �� ���Ĺ���� ���� ������ �� ������ ���� ������, ������ �����ʺ��� �����͸� ���ذ��� ���ؼ� ���ݴ��� ��찡 �����ϴ��� Ȯ��
//          -> �����ʿ��� ���簡 �´� ���� ���̸�? ->  ���ʰ� �������� ���� ��ȯ�ϰ�, �� ���� ������ġ�� ���� ������ �Ȱ��� ��� ����
//       -> �����̴� �������̴� �����Ͱ� ��ġ�� �ȴٸ�? �� �κ��� �߽����� ����Ʈ�� �丷���� �ٽ� ���� ������� �� �ݺ�
//       -> ��� �κи���Ʈ�� �� �̻� ������ �Ұ����� �ּ� ����(1��)�� ���� �� ������ �̸� �ݺ�
void quick_sort(int arr[], int direction, int start, int array_length) {

    int flag = 0;

    if (array_length <= 0) {

        printf("�迭�� ���̰� 0���� �۰ų� �����Ƿ� ����X\n\n");
        return;
    }

    if (start >= array_length) {
        printf("�迭�� �������� �迭�� ���� %d���� ũ�ų� �����Ƿ� ����X\n\n", array_length);
        return;
    }

    int standard = arr[start];
    int left_start = start;
    int right_start = array_length;

    printf("\n---------------------[���ذ� : %d, ���ۺκ� : %d, ���κ� : %d]------------------------------------\n\n", standard, start, array_length);

    // �������� (ū ���� �ڷ�.. )
    if (direction == ascending_order) {

        // �迭 ũ�⸸ŭ �κ����� �׷캰 ����Ŭ �� �� �ְ� ��
        while (left_start <= right_start) {

            if (left_start == right_start) {
                printf("=============left�� right�� ���� ���� �迭[%d]�� ����!================\n", left_start);

                printf("-> ���ذ� %d�� ������ �ִ� arr[%d]�� ��ġ�� �б��� �迭[%d]�� ���� ����", standard, start, flag);
                printf("arr[%d] : %d <-> arr[%d] : %d!\n\n", start, arr[start], flag, arr[flag]);
                swap(int, arr[flag], arr[start]);

                for (int i = start; i <= array_length; i++) {

                    printf("%d ", arr[i]);
                }
                printf("\n\n");

                break;
            }
            //else if (left_start > right_start) {
            //    printf("left�� right�� �迭[%d],  �迭[%d]�� �������� ������!\n\n", left_start, right_start);
            //    swap(int, arr[right_start], arr[start]);

            //    if (left_start > 0 && left_start <= array_length) {
            //        quick_sort(arr, direction, start, right_start);
            //        quick_sort(arr, direction, left_start, array_length);
            //    }
            //    break;
            //}
            else if (left_start < right_start) {

                printf("(��ȯ�� �˻���) left_start -> %d, right_start -> %d\n", left_start, right_start);

                while (arr[left_start] <= standard && left_start < array_length) {
                    left_start++;
                    flag = left_start;
                }

                printf("(�߿�) ���� ��ȯ��� left : %d ,  �� ��ġ : %d   ----->> right���� �����̰���\n", arr[left_start], left_start);

                while (arr[right_start] > standard && right_start > start && left_start < right_start) {
                    right_start--;
                }

                printf("(��ȯ�� �߰���!) left_start -> %d, right_start -> %d\n\n", left_start, right_start);

                if (left_start <= right_start) {
                    printf("->> left : %d <= right : %d �̹Ƿ�..  arr[left_start] : %d <-> arr[right_start] : %d \n\n", left_start, right_start, arr[left_start], arr[right_start]);
                    swap(int, arr[left_start], arr[right_start]);
                }
            }

            for (int i = start; i <= array_length; i++) {

                printf("%d ", arr[i]);
            }
            printf("\n\n");

        }

        if (left_start == array_length && right_start == array_length) {

            printf("(�κ� ���� �Ϸ�) ���� left_start == right_start == %d �ش� �κй迭�� �迭�� �ϼ��Ǿ���, �� �κ����� ���� ������ �����ϴ�.\n\n", array_length);

        }
        // �κ� �迭 ������ ��
        else if (left_start >= 0 && left_start < array_length) {

            // �º���
            printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n", start, left_start);
            quick_sort(arr, direction, start, left_start);

            // �����
            printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n", left_start + 1, array_length);
            quick_sort(arr, direction, left_start + 1, array_length);
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
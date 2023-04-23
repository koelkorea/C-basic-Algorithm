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
#define ARRAY_LENGTH 100
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define ��ũ�� ���� (����ó�� ��ó�� �⹮)			ex) A <-> : A�� B�� �ش��ϴ� Ÿ���� ��������� ����Ͽ� ��ȯ


// �ش� �����迭�� ��Ұ��� ������ ��� (for������ length��ŭ �ݺ�)
void display(int arr[], int start, int size) {

    for (int i = start; i < size; i++) {

        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

//  5. �� ����(Quick sort)
//     : ����Ʈ �ȿ� �����ϴ� ������ ���� ���ذ����� ���صΰ�, 
//       -> ���ʿ������� �����͸� ���ذ��� ���Ĺ���� ���� ũ�� ������ �� ���Ĺ���� ���� ������ �� ������ ���� ������, ������ �����ʺ��� �����͸� ���ذ��� ���ؼ� ���ݴ��� ��찡 �����ϴ��� Ȯ��
//          -> �����ʿ��� ���簡 �´� ���� ���̸�? ->  ���ʰ� �������� ���� ��ȯ�ϰ�, �� ���� ������ġ�� ���� ������ �Ȱ��� ��� ����
//       -> �����̴� �������̴� �����Ͱ� ��ġ�� �ȴٸ�? �� �κ��� �߽����� ����Ʈ�� �丷���� �ٽ� ���� ������� �� �ݺ�
//       -> ��� �κи���Ʈ�� �� �̻� ������ �Ұ����� �ּ� ����(1��)�� ���� �� ������ �̸� �ݺ�
void quick_sort(int arr[], int direction, int leftest, int rightest) {

    int left_point = leftest;
    int right_point = rightest;
    int pivot = arr[left_point];

    printf("\n---------------------[���ذ� : %d, ���ۺκ� : %d, ���κ� : %d]------------------------------------\n\n", pivot, leftest, rightest);

    display(arr, leftest, rightest + 1);

    // �������� (ū ���� �ڷ�.. )
    if (direction == ascending_order) {

        // left_point�� right_point���� ���� �� ������ �ݺ� (��Ȳ�� �ƴ϶� �ĵ� �ϴ� �����غ�)
        do {

            printf("(��ȯ�� �˻���)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

            // �迭[left_point]���� ���ذ����� ũ�ų� ���� ��Ȳ�� �ɋ����� left_point�� �������� �ű�
            while (arr[left_point] < pivot && left_point <= right_point) {
                left_point++;
            }

            if (left_point <= right_point) {
                printf(" ->> (��ȯ left�߰�) arr[%d] : %d (arr[%d](���ذ�) : %d ���� ū ��)   ----->> right���� �����̰���\n", left_point, arr[left_point], leftest, pivot);
            }

            // �迭[right_point]���� ���ذ����� �۰ų� ���� ��Ȳ�� �ɋ����� right_point�� ���������� �ű�
            while (arr[right_point] > pivot){
                right_point--;
            }

            if (left_point == right_point) {
                printf(" ->> (right Ŀ�� move �ߴ�!) left = right : ���� ��ġ�� %d�� ���ذ��� %d�� �����մϴ�\n\n", left_point, arr[left_point]);
            }
            else if (left_point < right_point){
                printf(" ->> (��ȯ right�߰�) arr[%d] : %d (arr[%d](���ذ�) : %d ���� ���� ��)\n", right_point, arr[right_point], leftest, pivot);
            }

            printf("(��ȯ�� �˻���!)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

            if (left_point <= right_point) {
                printf("  ->> (left - right ��ȯ!) arr[%d] : %d <-> arr[%d] : %d \n\n", left_point, arr[left_point], right_point, arr[right_point]);
                swap(int, arr[left_point], arr[right_point]);
                left_point++;
                right_point--;
            }

            display(arr, leftest, rightest + 1);

        } while (left_point <= right_point);

        printf("=====================================[����Ŭ end]==================================================\n\n");

        printf("leftest : %d , rightest : %d , left_point : %d , right_point : %d \n\n", leftest , rightest , left_point , right_point);


        // �迭 ���� ������ġ�� ���� ������ �����ͺ��� ������?
        //  -> �迭 ���� ������ġ ~ ���� ������ �����ͱ����� �߶� ����Ʈ ����
        if (leftest < right_point) {

            // �º���
            printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", leftest, right_point);
            quick_sort(arr, direction, leftest, right_point);
        }

        // �迭 ���� ��������ġ�� ���� ���� �����ͺ��� ũ��?
        //  -> ���� ���� ������ ~ �迭 ���� ��������ġ���� �߶� ����Ʈ ����
        if (rightest > left_point) {

            // �����
            printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", left_point, rightest);
            quick_sort(arr, direction, left_point, rightest);
        }

    }
    // �������� (���� ���� �ڷ�.. )
    else {

        // left_point�� right_point���� ���� �� ������ �ݺ� (��Ȳ�� �ƴ϶� �ĵ� �ϴ� �����غ�)
        do {

            printf("(��ȯ�� �˻���)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

            // �迭[left_point]���� ���ذ����� �۰ų� ���� ��Ȳ�� �ɋ����� left_point�� �������� �ű�
            while (arr[left_point] > pivot) {
                left_point++;
            }

            if (left_point <= right_point) {
                printf(" ->> (��ȯ left�߰�) arr[%d] : %d (arr[%d](���ذ�) : %d ���� ū ��)   ----->> right���� �����̰���\n", left_point, arr[left_point], leftest, pivot);
            }

            // �迭[right_point]���� ���ذ����� ũ�ų� ���� ��Ȳ�� �ɋ����� right_point�� ���������� �ű�
            while (arr[right_point] < pivot) {
                right_point--;
            }

            if (left_point == right_point) {
                printf(" ->> (right Ŀ�� move �ߴ�!) left = right : ���� ��ġ�� %d�� ���ذ��� %d�� �����մϴ�\n\n", left_point, arr[left_point]);
            }
            else if (left_point < right_point) {
                printf(" ->> (��ȯ right�߰�) arr[%d] : %d (arr[%d](���ذ�) : %d ���� ���� ��)\n", right_point, arr[right_point], leftest, pivot);
            }

            printf("(��ȯ�� �˻���!)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

            if (left_point <= right_point) {
                printf("  ->> (left - right ��ȯ!) arr[%d] : %d <-> arr[%d] : %d \n\n", left_point, arr[left_point], right_point, arr[right_point]);
                swap(int, arr[left_point], arr[right_point]);
                //left_point++;
                //right_point--;
            }

            display(arr, leftest, rightest + 1);

        } while (left_point <= right_point);

        printf("=====================================[����Ŭ end]==================================================\n\n");

        printf("leftest : %d , rightest : %d , left_point : %d , right_point : %d \n\n", leftest, rightest, left_point, right_point);


        // �迭 ���� ������ġ�� ���� ������ �����ͺ��� ������?
        //  -> �迭 ���� ������ġ ~ ���� ������ �����ͱ����� �߶� ����Ʈ ����
        if (leftest < right_point) {

            // �º���
            printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", leftest, right_point);
            quick_sort(arr, direction, leftest, right_point);
        }

        // �迭 ���� ��������ġ�� ���� ���� �����ͺ��� ũ��?
        //  -> ���� ���� ������ ~ �迭 ���� ��������ġ���� �߶� ����Ʈ ����
        if (rightest > left_point) {

            // �����
            printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", left_point, rightest);
            quick_sort(arr, direction, left_point, rightest);
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

    printf("���Ͻô� ����� ���Ĺ���� ���������ΰ���? (0 : ��������, �� �̿� �� �Է�: ��������) : ");
    scanf_s("%d", &direction);

    // ���� ��Ʈ ����
    quick_sort(ary_test, direction, 0, array_length);

    printf("\n[quick sort ���] \n");

    display(ary_test, 0, ARRAY_LENGTH);

    printf("\n");

    return 0;
}
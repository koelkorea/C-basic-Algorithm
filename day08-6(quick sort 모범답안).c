// (���) �����Ҵ��� ����� ������ ����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(type, x, y) {type t = x; x = y; y = t;}

// �迭�� ���ڸ� ��������
void radomize(int* array, int length, int start, int end) {

    srand((unsigned int)time(NULL));

    // �迭�� �ּҰ��� �ִ밪���� ũ�ٸ�... �� �� ��ġ�� �ٲ㼭 ���� �ǰ� ��
    if (start > end) {
        swap(int, start, end);
    }

    // �� �迭������ �ּҰ� ~ �ִ밪�� ������ ���� ä����
    for (int i = 0; i < length; i++) {

        array[i] = rand() % (end - start + 1) + start;
    }
}

// �ش� �����迭�� ��Ұ��� ������ ��� (for������ length��ŭ �ݺ�)
void display(int* pArr, int start, int size) {
    for (int i = start; i < size; i++) {
        printf("%d  ", pArr[i]);
    }
    printf("\n\n");
}

// ����Ʈ(��ͻ���� ���� ������)
void quick(int* array, int leftest, int rightest) {

    // ���� ������ ������, ������ ������ ������
    int left_point = leftest;
    int right_point = rightest;

    // (�߿�) left <-> right ��ȯ�� ���� ���ذ� = �迭�� �߰���ġ�� ������.. 
    //  -> �׷��� ���ϰ� �迭 ������ �ƹ� ���̳� ��Ƶ� ������, �ʹ� �ش����� ���� ���ذ����� ������ ����Ʈ�� ȿ���� �ٴ��� ģ��
    //int pivot = array[(left_point + right_point) / 2];
    int pivot = array[left_point];

    printf("\n---------------------[���ذ� : %d, �迭 ���� : %d, �迭 �� : %d]------------------------------------\n\n[����] : ", pivot, left_point, right_point);

    display(array, leftest, rightest + 1);

    // left_point�� right_point���� ũ�� �� ������ �ݺ� (��Ȳ�� �ƴ϶� �ĵ� �ϴ� �����غ�)
    do {

        printf("(��ȯ�� �˻���)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, array[left_point], right_point, array[right_point]);

        // �迭[left_point]���� ���ذ����� ũ�ų� ���� ��Ȳ�� �ɋ����� left_point�� �������� �ű�
        while (array[left_point] < pivot) {
            left_point++;
        }

        // �迭[right_point]���� ���ذ����� �۰ų� ���� ��Ȳ�� �ɋ����� right_point�� ���������� �ű�
        while (array[right_point] > pivot) {
            right_point--;
        }

        printf("(��ȯ�� �˻���!)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, array[left_point], right_point, array[right_point]);

        // left����Ʈ�� right����Ʈ�� ���� ���� �������� left������ right�������� ���ų� ���� ��ġ���?
        //  -> �� ��ġ�� ���� �ٲ��ְ�, �� �����͸� ���� �������� 1ĭ�� �ű��
        if (left_point <= right_point) {
            printf("  ->> (left - right ��ȯ!) arr[%d] : %d <-> arr[%d] : %d \n\n", left_point, array[left_point], right_point, array[right_point]);
            swap(int, array[left_point], array[right_point]);
            left_point++;
            right_point--;
        }

        printf("      ");

        // �ٲ� ��� ����
        display(array, leftest, rightest + 1);

        // �׷��� �ݺ��� left������ right�������� ū ��Ȳ�̸� �ߴ�
    } while (left_point <= right_point);

    printf("=====================================[����Ŭ end]==================================================\n\n");

    // �迭 ���� ������ġ�� ���� ������ �����ͺ��� ������?
    //  -> �迭 ���� ������ġ ~ ���� ������ �����ͱ����� �߶� ����Ʈ ����
    if (leftest < right_point) {

        printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", leftest, right_point);
        quick(array, leftest, right_point);
    }

    // �迭 ���� ��������ġ�� ���� ���� �����ͺ��� ũ��?
    //  -> ���� ���� ������ ~ �迭 ���� ��������ġ���� �߶� ����Ʈ ����
    if (rightest > left_point) {

        printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", left_point, rightest);
        quick(array, left_point, rightest);
    }
}

// ����Ʈ ���۽� Ʈ���ſ� �޼���
void quickSort(int* arr, int size) {
    quick(arr, 0, size - 1);
}


int main() {

    // �����迭 �����ּ� ���� int ����Ʈ �ּ�
    int* array_address;

    // �迭����, �ּҰ�, �ִ밪
    int length, min, max;

    printf("�迭�� ũ�� �Է� : ");
    scanf_s("%d", &length);

    // ���̸� �Է��ϸ�, �׸�ŭ �����迭�� �����ϰ�, ������ġ�� �������ش�
    array_address = (int*)calloc(length, sizeof(int));

    printf("�ּҰ� / �ִ밪 �Է� : ");
    scanf_s("%d %d", &min, &max);

    // �迭�� ����
    radomize(array_address, length, min, max);

    printf("\n\n���� �� �ڷ� ��� ***\n\n");
    display(array_address, 0, length);

    // ����Ʈ Ʈ���� (������)
    quickSort(array_address, length);

    printf("\n\n���� �� �ڷ� ��� ***\n\n");
    display(array_address, 0, length);

    // �����迭 �޸� ����
    free(array_address);
    return 0;
}
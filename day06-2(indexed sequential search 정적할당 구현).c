//�˻�(Ž��) : ���� ���� �ڷ�� �߿��� ���ϴ� �ڷḦ ã�� �۾� (= ����� ������������ ���� ã�°� ���ɻ� ����..)

// 3. ���� ���� Ž��(indexed sequential search)
//    : �����˻� + �� �ڷ� ���տ��� ���� �������� ������ �ε���(index) ���̺� Ȱ�� (��! �� �ڷ� ������ ���հ� �ε��� ���̺��� ��� ���ĵǾ� �־�� �Ѵ�)
//      -> �׷��ϱ� �̸� ������ �������� ���� ����־� �� ���� ����� ��ġ���� �����ϴ� index ���̺��� �����, �ԷµǴ� ���� ��� ���� ������ �� index ���̺��� �����Ѵٴ� ��
//         (= �ε��� ���̺��� index�� ������������, �̸� �� �ڷῡ ������ ���̻��̰� ���� �� = �������� ã�µ��� �������� ���� �ȴ�)

#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��

typedef struct index {
    int index_sequence;
    int index_reference_value;
}index;

void sequentialSearch2(int a[], int begin, int end, int key) {

}

void makeIndexTable(int a[], int size) {

}
int indexSearch(int a[], int n, int key) {

}
int main() {

    // �˻� ��� �迭
    int target_array[100] = { 0 };

    // �˻� ��� �迭 ����
    int target_array_length = 100;

    // �˻� ��� �迭�� �� ä���
    for (int i = 0; i < target_array; i++) {

        int plus_a = rand() % 3 + 1;

        if (i == 0) {
            target_array[i] = i + plus_a;
        }
        else {
            target_array[i] = target_array[i - 1] + plus_a;
        }

        printf("%d ", target_array[i]);
    }

    printf("\n\t<< ���� ���� �˻� >>\n");
    makeIndexTable(target_array, target_array_length);

    while (1) {

        int search_value = 0;

        printf("�˻��� ���ϴ� ���� �Է����ּ��� (0 = �����ϱ�): ");
        scanf_s("%d", &search_value);

        if (search_value == 0) {

            printf("���α׷��� ����Ǿ����ϴ�.");
            exit(0);
        }

        indexSearch(target_array, target_array, search_value);
    }

    return 0;
}

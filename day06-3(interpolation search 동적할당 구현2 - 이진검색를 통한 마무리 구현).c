//�˻�(Ž��) : ���� ���� �ڷ�� �߿��� ���ϴ� �ڷḦ ã�� �۾� (= ����� ������������ ���� ã�°� ���ɻ� ����..)

// 4. ���� Ž��(interpolation search)
//    : ���ĵ� ������ ���տ��� ���� �ε���(�������� ��ġ)�� "���" ������ ����. key�� ������ ��ġ�� �뷫������ ã�� Ž���ϴ� ���
//      (= �� ���� �����͵鰣�� ������ �����ϴٴ� ������ �ʿ��ϴ�!)

// �����Ҵ��� ����� ����Ž�� ����2 (�����˻��� ���� ������)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <time.h>
#define ARRAY_LENGTH 100

// ���� Ž��(interpolation search)
//  : ���ĵ� ������ ���տ��� ���� �ε���(�������� ��ġ)�� "���" ������ ����. key�� ������ ��ġ�� �뷫������ ã�� Ž���ϴ� ���

// ���� �˻� ��� �迭�� �����ּҸ� ���� ���� ���� �༮�� 0, ���� ���� �ּҸ� '�迭�� ����-1'�� �����ϰ�, �ű⼭ key�� ã�� �˰���
int interpolation_search(int* arr, int key, int low, int high) {

    // ���� �˻� ������ ���� �� ��� (= �Ҽ��� �ٻ簪�̶� ����ȭ�� ���� �ٻ�ġ �˻� �ʿ�)
    float result = (key - *(arr + low)) / (*(arr + high) - *(arr + low)) * (high - low) + low;

    // ���� �˻� ����� result�� �ݿø��� ������ �ε����� ����������..
    int search_index = (int)(result + 0.5);

    // ���� ������ �������� �ְ����� �۴ٸ�, ��� ����
    if (low <= high) {

        // �迭�� �����ּ� + search_index�� �������� ���� key�� ���ٸ�? -> search_index�� �� ����
        if (*(arr + search_index) == key) {

            return search_index;
        }
        // �迭�� �����ּ� + search_index�� �������� ���� key���� ũ�ٸ�? -> high�� ���� search_index - 1 (�ش� �ּҰ����� 1���� �ּҿ� ��ġ�� �ּ�)�� �ΰ� �ٽ� ����
        else if (*(arr + search_index) > key) {

            return interpolation_search(arr, key, low, search_index - 1);
        }
        // �迭�� �����ּ� + search_index�� �������� ���� key�� �۴ٸ�? -> low�� ���� search_index + 1 (�ش� �ּҰ����� 1���� �ּҿ� ��ġ�� �ּ�)�� �ΰ� �ٽ� ����
        else if (*(arr + search_index) < key) {

            return interpolation_search(arr, key, search_index + 1, high);
        }
    }

    // �˻��� �������� ��� -1 ��ȯ
    return -1;
}

int main(void) {

    srand((unsigned int)time(NULL));

    // �����迭�� ��ġ�� �޾Ƴ� ������
    int* array_address = NULL;
    // �����迭�� ���̰�
    int array_num = 0;

    printf("----------------------------------------------------------------------------\n");
    printf("�˻������ �����غ��ϴ�. �迭 ũ�⿡ �ش��ϴ� ���� �Է��ϸ�,\n �迭�� ���� �� �迭�� index + a(1~5) �� �����ϴ� ������ �Էµ˴ϴ�.");
    printf("----------------------------------------------------------------------------\n\n");

    printf("�˻��� ����� �Ǵ� �迭�� ũ�⸦ �Է��ϼ��� (0�̿��� ���� �� ��Ź�����~) : ");
    scanf_s("%d", &array_num);

    if (array_num == 0) {
        printf("�迭�� ũ�Ⱑ 0�̹Ƿ� �ý����� �����մϴ�\n");
        exit(0);
    }

    // �����Ҵ� ����
    array_address = (int*)calloc(array_num, sizeof(int));

    // �����Ҵ��� �޸� ������ ���� ���ĵ� ȿ���� ����, ������ ���� ���� �ְ��ϵ�, ������ �ڱ� ������ ���� �߰����� ���ϴ� ������ ����
    for (int i = 0; i < array_num; i++) {

        int plus_a = rand() % 3 + 1;

        if (i == 0) {
            *(array_address + i) = i + plus_a;
        }
        else {
            *(array_address + i) = *(array_address + i - 1) + plus_a;
        }

        printf("%d ", *(array_address + i));
    }

    printf("\n\n�� �Է��� �Ϸ�Ǿ����ϴ�.\n");
    printf("hint : ���� ���� �� = %d, ���� ���� �� = %d)\n\n", *(array_address), *(array_address + array_num - 1));

    while (1) {

        // �˻��� ��
        int search_value = 0;

        printf("�̰Ŵ� ���� ���� �Է� ��Ź�帳�ϴ�(%d ~ %d) (0, ���� �� �Է� = �����ϱ�) : ", *(array_address), *(array_address + array_num - 1));
        scanf_s("%d", &search_value);

        if (search_value <= 0 || search_value > *(array_address + array_num - 1)) {
            printf("\n(���!)�迭������ ������ �Ѿ ���Դϴ�. ���α׷��� ����Ǿ����ϴ�.\n");
            exit(0);
        }

        // ���� �˻� ���� (-1 �̿��� ���� ���� = �ش� �迭 ���� ���� ����)
        int result = interpolation_search(array_address, search_value, 0, array_num - 1);

        if (result != -1) {

            // (�˻� ���� ��ġ) interpolation_search ( �˻� �迭, �˻� ��, ���� ���� ĭ, �ִ� ���� ĭ )
            printf(" ->> (����) ���� Ž�� : �˻��� [%d]�� �ش�迭�� %d��° ������ ��ġ�մϴ�.\n", search_value, result + 1);

        }
        else {

            printf(" ->> [%d]�� ���� Ž�� ����\n", search_value);
        }
        printf("\n");
    }

    return 0;

}
//�˻�(Ž��) : ���� ���� �ڷ�� �߿��� ���ϴ� �ڷḦ ã�� �۾� (= ����� ������������ ���� ã�°� ���ɻ� ����..)

// 4. ���� Ž��(interpolation search)
//    : ���ĵ� ������ ���տ��� ���� �ε���(�������� ��ġ)�� "���" ������ ����. key�� ������ ��ġ�� �뷫������ ã�� Ž���ϴ� ���
//      (= �� ���� �����͵鰣�� ������ �����ϴٴ� ������ �ʿ��ϴ�!)

// �����Ҵ��� ����� ����Ž�� ����
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <time.h>
#define ARRAY_LENGTH 100

// ���� Ž��(interpolation search)
//  : ���ĵ� ������ ���տ��� ���� �ε���(�������� ��ġ)�� "���" ������ ����. key�� ������ ��ġ�� �뷫������ ã�� Ž���ϴ� ���
int interpolation_search(int arr[], int key, int low, int high) {

    // ���� �˻� ������ ���� �� ��� (= �Ҽ��� �ٻ簪�̶� ����ȭ�� ���� �ٻ�ġ �˻� �ʿ�)
    float result = (key - arr[low]) / (arr[high] - arr[low]) * (high - low) + low;

    // ���� �˻� ����� result�� �ݿø��� ������ �ε����� ����������.. = �����˻� ������ ���� ���� ���� �迭��ġ
    int search_index = (int) (result + 0.5);

    // search_index�� �����Ǵ� ���� ���� �������� ���� ������ ���̿� ������ ��� ����
    //  -> ������ �̷��� ��Ƶ� ���ѷ����� Ż�� �� ����� 1��° if ���ǿ� ��
    while (search_index >= low || search_index < high) {

        if (low + 1 == high) {
            // �˻��� �������� ��� -1 ��ȯ
            return -1;
        }

        // �迭[search_index]�� ��ġ�� ���� key�� ���ٸ�? -> search_index�� �� ����
        if (arr[search_index] == key) {

            return search_index;
        }
        // �迭[search_index]�� ��ġ�� ���� key���� ũ�ٸ�?
        // -> �� �Ʒ��ּҿ� ���� �ִٴ� �ǹ� => high�� ���� search_index�� �ΰ�, ���� �����Ǵ� �����˻��� ���� �����Ǵ� ���� ��ġ�� search_index�� -1�Ѵ�
        else if (arr[search_index] > key) {

            high = search_index;
            search_index--;
        }
        // �迭[search_index]�� ��ġ�� ���� key���� �۴ٸ�?
        // -> �� ���ּҿ� ���� �ִٴ� �ǹ� => low�� ���� search_index�� �ΰ�, ���� �����Ǵ� �����˻��� ���� �����Ǵ� ���� ��ġ�� search_index�� +1�Ѵ�
        else if (arr[search_index] < key) {

            low = search_index;
            search_index++;
        }
    }

}

int main() {

    srand((unsigned int)time(NULL));

    printf("----------------------------------------------------------------------------\n");
    printf("�迭�� ���̴� 50�̸�, �����˻��� �����˻��� �����غ��ϴ�.\n�� �迭���� �� �迭�� ���� �迭�� + a(1~5) �� �����ϴ� ������ �Էµ˴ϴ�.\n");
    printf("----------------------------------------------------------------------------\n\n");

    int ary_test[ARRAY_LENGTH] = { 0 };
    int input = 0;

    // ������ ���� ���� �ְ��ϵ�, �迭�� �� ���� ���� ȿ���� ������ ������ �ڱ� ������ ���� �߰����� ���ϴ� ������ ����
    for (int i = 0; i < ARRAY_LENGTH; i++) {

        int plus_a = rand() % 4 + 1;

        if (i == 0) {
            ary_test[i] = plus_a;
        }
        else if (i != 0) {
            ary_test[i] = ary_test[i - 1] + plus_a;
        }

        printf("%d ", ary_test[i]);
    }

    printf("\n\n�� �Է��� �Ϸ�Ǿ����ϴ�. \n");
    printf("(hint : ���� ���� �� = %d, ���� ���� �� = %d)\n\n", ary_test[0], ary_test[ARRAY_LENGTH-1]);

    while (1) {

        printf("ã�� ���� ���ڸ� %d ~ %d���� �Է��ϼ���. (���� �� �Է� = ����) :", ary_test[0], ary_test[ARRAY_LENGTH - 1]);
        scanf_s("%d", &input);

        if (ary_test[0] <= 0 || input > ary_test[ARRAY_LENGTH - 1]) {
            printf("\n(���!)�迭������ ������ �Ѿ ���Դϴ�. ���α׷��� ����Ǿ����ϴ�.\n");
            exit(0);
        }

        // ���� �˻� ���� (-1 �̿��� ���� ���� = �ش� �迭 ���� ���� ����)
        int result = interpolation_search(ary_test, input, 0, ARRAY_LENGTH - 1);
        
        if (result != -1) {

            // (�˻� ���� ��ġ) search_binary ( �˻� �迭, �˻� ��, ���� ���� ĭ, �ִ� ���� ĭ )
            printf(" ->> (����) ���� Ž�� : �˻��� [%d]�� �ش�迭�� %d��° ������ ��ġ�մϴ�.\n", input, result + 1);

        }
        else {

            printf(" ->> [%d]�� ���� Ž�� ����\n", input);
        }
        printf("\n");

    }
    return 0;
}

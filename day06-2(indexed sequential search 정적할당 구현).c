//�˻�(Ž��) : ���� ���� �ڷ�� �߿��� ���ϴ� �ڷḦ ã�� �۾� (= ����� ������������ ���� ã�°� ���ɻ� ����..)

// 3. ���� ���� Ž��(indexed sequential search)
//    : �� �ڷ� ���տ��� ���� �������� ������ �ε���(index) ���̺� Ȱ�� (��! �� �ڷ� ������ ���հ� �ε��� ���̺��� ��� ���ĵǾ� �־�� �Ѵ�)
//      -> �׷��ϱ� �̸� ������ �������� ���� ����־�, �� ���� ���� ��ġ���� �����ϴ� ����(index)����Ʈ�� �����, �˻��Ǵ� ���� ��� ������ ã�°� �� ������ ���� �����ؼ� �˻������� ���Ѵٴ� �������� �޾Ƶ�����

//  # Ư¡�� �ִٸ� �˻��� �� ������ ���صдٴ� �� (= ������ �������� �� ������ � �˻��� �ص� �������)
//  # �ε��� ���̺��� index�� ������������, �̸� �� �ڷῡ ������ ���̻��̰� ���� �� = �������� ã�µ��� �������� ���� �ȴ�

// ���� ���� Ž�� �����迭�� ����Ͽ� ����
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <time.h>
#define INDEX_REFERENCE_LENGTH 10

// index ������ �����ϴ� ����ü�� ������ ���� ���� (�� �������� � ������ �ִ����� ǥ���ϴ� ������� �����ϸ� ����.. ���� �װ� ������ ���ڰ��� �������� �� ��) 
//  - �ش� index���� ��ġ�ϴ� �迭�� ���� ��ġ�� (�迭�� ��������� ��������)
//  - �ش� index�� �� ��ü (�����̶�� ��������)
typedef struct index {
    int index_checkpoint;
    int index_reference_value;
}index;

// index ����ü�� ������ �迭�� ���� ������ ����   <- �����迭������ ������ ������ ������ ���ص־� ��
index index_reference[INDEX_REFERENCE_LENGTH] = { {0,0} };

// 3�ܰ�) index�迭 ���������� �̿���, �����˻����� search���� �������� �˻�
void sequentialSearch2(int target_array[], int start, int end, int key) {

    printf("\n �˻��� [%d]�� target_array[%d] ~ [%d] ���� �����˻��Ͽ���!\n\n", key, start, end);

    // start ~ end ������ Ÿ�� �迭�� ��Ұ��� key���� ������Ű�� �����˻� ���
    for (int i = start; i <= end; i++) {

        if (target_array[i] == key) {
            printf(" ->> (���) �ش�迭 %d��°�� ��� %d�� �������� Ȯ���߽��ϴ�!\n\n", i + 1, key);
            return;
        }
        else {
            printf(" ->> �ش�迭 %d��°�� ��� %d�� ������ Ȯ����!\n", i + 1, key);
        }
    }

    printf(" ->> (���) %d�� ��� �迭���� �������� �ʴ� ���Դϴ�!\n\n", key);
}

// 2�ܰ�) �˻����� index �迭 ������ ����� ���Ͽ� ����뿡 ��ġ�ϴ��� ã�� (������ġ�� 2���� ������ ����ؾ� ��.. �׷��� �� ������ ã�� �����˻� ������)
void indexSearch(int target_array[], int target_array_length, int key) {

    // �����˻� ������ ~ ����
    int check_point1 = 0, check_point2 = target_array_length - 1;

    // �˻��� ���� Ÿ�� �迭�� 1���� ������ �۾Ƽ� �˻��� ������ ���ų�, ������ �迭�� ������ Ŀ�� �˻��� ������ ���� ���
    if (key < target_array[0] || key > target_array[target_array_length - 1]) {

        printf(" ->> (���� ����) %d�� ��� �迭�� ������ �Ѿ ���Դϴ�!\n\n", key);
        return;
    }

    // key���� index ���� �迭�� ��ġ�� �� ���� index_reference_value�� ���Ѵ� 
    for (int i = 0; i < INDEX_REFERENCE_LENGTH; i++) {

        // index �迭�� index_reference_value ���� 0�� ���, index ������ �����ϴ� ���� interval�� +1 �Ǵ� �ٶ��� �߰����� �ʾҴٴ� �ǹ��̴�, �ǹ̾��� ��ȸ�ϴ� �ݺ����� �����ش�
        if (index_reference[i].index_checkpoint == 0 && index_reference[i].index_reference_value == 0) {
            break;
        }

        // index_checkpoint���� index_reference_value�� 0�� �ƴ϶��, key���� �����غ���, �׿� ���� �б⿡ ���� ����� ó��

        // index_reference_value�� key���̸�.. -> �ٷ� ��� ��ǥ �� ����
        if (index_reference[i].index_reference_value == key) {

            printf(" ->> (���� ����) �ش�迭 %d��°�� ��� %d�� �������� Ȯ���߽��ϴ�!\n\n", index_reference[i].index_checkpoint, key);
            return;
        }
        // index_reference_value�� key������ �۴ٸ�.. -> check_point1�� �ش� ��ġ������ ����
        else if (index_reference[i].index_reference_value < key) {

            check_point1 = index_reference[i].index_checkpoint;
        }
        // index_reference_value�� key������ �۴ٸ�.. -> check_point2�� �ش� ��ġ������ ���� �� �ݺ��� ����
        else if (index_reference[i].index_reference_value > key) {

            check_point2 = index_reference[i].index_checkpoint;
            break;
        }
    }

    // �ݺ����� ���� ���� check_point1, check_point2�� ���̽��� �����˻� �ǽ�
    sequentialSearch2(target_array, check_point1, check_point2, key);
}

// 1�ܰ�) Ÿ�ٹ迭�� ������ ���� index ������ �ϼ���Ű�� (parameter : �ش� �迭�� ��ġ, �ش� �迭�� ũ��  <- �̰� ���� index_reference �迭 ũ�⿡ �°� index �������� ä��)
void makeIndexTable(int target_array[], int target_array_length) {

    // Ÿ�� �迭�� ���� / index �迭�� ���� = �� index�� ������ �󸶷� �����ؾ� ���� ���  
    int index_interval = target_array_length / INDEX_REFERENCE_LENGTH;

    // ���� Ÿ�� �迭�� ���� / index �迭�� ���̿� ������ ���� �����Ѵٸ�, ������ �����ϱ� ���� �� index�� ������ 1�������� index ������ ������
    if (target_array_length % INDEX_REFERENCE_LENGTH != 0) {
        index_interval++;
    }

    // index �迭 ������ ä��� ����
    for (int i = 0; i < INDEX_REFERENCE_LENGTH; i++) {

        // ���� ǥ��� �ε����� Ÿ�� ���̺��� ���ų�(= �迭�� ��ġ �ִ밪 = ���� - 1 �̱� ����) ũ��?
        //  -> ���̻� index�� ��������
        if (i * index_interval >= target_array_length) {

            break;

        }
        else if (i * index_interval < target_array_length) {

            // index����ü �� é�Ϳ� ä������ üũ����Ʈ index ��ġ���� �� üũ����Ʈ�� ��ġ�� index���� ����
            index_reference[i].index_checkpoint = i * index_interval;
            index_reference[i].index_reference_value = target_array[i * index_interval];

        }
    }

}

int main() {

    srand((unsigned int)time(NULL));

    // �˻� ��� �迭
    int target_array[100] = { 0 };

    // �˻� ��� �迭 ����
    int target_array_length = 100;

    // �˻� ��� �迭�� �� ä���
    for (int i = 0; i < target_array_length; i++) {

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

    // Ÿ�� �迭�� index �������� ����� 
    makeIndexTable(target_array, target_array_length);

    while (1) {

        int search_value = 0;

        printf("�˻��� ���ϴ� ���� �Է����ּ��� (0 = �����ϱ�): ");
        scanf_s("%d", &search_value);

        if (search_value <= 0 || search_value > target_array[target_array_length-1]) {

            printf("���α׷��� ����Ǿ����ϴ�.");
            exit(0);
        }

        // index ���������� ���� ���� �Ϸ��ϰ� ����?
        //  -> �� index ������ ���ؼ���, Ÿ�� �迭�� ���� �˻�(sequentialSearch2)�ϱ�
        indexSearch(target_array, target_array_length, search_value);
    }

    return 0;
}

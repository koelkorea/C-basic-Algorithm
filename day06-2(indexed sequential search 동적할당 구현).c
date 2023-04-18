//�˻�(Ž��) : ���� ���� �ڷ�� �߿��� ���ϴ� �ڷḦ ã�� �۾� (= ����� ������������ ���� ã�°� ���ɻ� ����..)

// 3. ���� ���� Ž��(indexed sequential search)
//    : �� �ڷ� ���տ��� ���� �������� ������ �ε���(index) ���̺� Ȱ�� (��! �� �ڷ� ������ ���հ� �ε��� ���̺��� ��� ���ĵǾ� �־�� �Ѵ�)
//      -> �׷��ϱ� �̸� ������ �������� ���� ����־�, �� ���� ���� ��ġ���� �����ϴ� ����(index)����Ʈ�� �����, �˻��Ǵ� ���� ��� ������ ã�°� �� ������ ���� �����ؼ� �˻������� ���Ѵٴ� �������� �޾Ƶ�����

//  # Ư¡�� �ִٸ� �˻��� �� ������ ���صдٴ� �� (= ������ �������� �� ������ � �˻��� �ص� �������)
//  # �ε��� ���̺��� index�� ������������, �̸� �� �ڷῡ ������ ���̻��̰� ���� �� = �������� ã�µ��� �������� ���� �ȴ�

#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <time.h>

typedef struct index {
    int index_sequence;
    int index_reference_value;
}index;

void sequentialSearch2(int* array_address, int begin, int end, int key) {

    int i = begin;

    printf("\n�ش� �迭���� �˻��� [%d]�� �˻��Ͽ���!\n\n", key);

    while (i < end && *(array_address + i) <= key) {

        if (*(array_address + i) == key) {
            printf(" ->> (���) �ش�迭 %d��°�� ��� %d�� �������� Ȯ���߽��ϴ�!\n", (i - begin) + 1, key);
            return;
        }
        else {
            printf(" ->> �ش�迭 %d��°�� ������ Ȯ����! \n", (i - begin) + 1);
        }

        i++;
    }

    printf(" ->> (���) %d�� ��� �迭���� �������� �ʴ� ���Դϴ�!\n", key);
}

int indexSearch(int* array_address, int array_num, int key, int index_length, index* index_address) {

    int i, begin = 0, end = array_num;

    if (key < *(array_address) || key > *(array_address + array_num - 1)) {
        return -1;
    }

    for (i = 1; i < index_length; i++) {
        if (((index_address + i - 1) -> index_reference_value <= key) && (((index_address + i - 1) -> index_reference_value > key))) {
            begin = (index_address + i - 1)->index_sequence;
            end = (index_address + i)->index_sequence;
            break;
        }
        else {
            begin = (index_address + i)->index_sequence;
            end = array_num;
        }
    }  
    
    sequentialSearch2(array_address, begin, end, key);
}



index* makeIndexTable(int* array_address, int max_size, int interval) {

    int the_number_of_index;
    index* index_start_address = NULL;

    the_number_of_index = max_size / interval;

    if (max_size % interval > 0) {
        the_number_of_index = the_number_of_index + 1;
    }

    index_start_address = (index*)calloc(the_number_of_index, sizeof(index));

    for (int i = 0; i < interval; i++) {
        (index_start_address + i)->index_sequence = i * the_number_of_index;
        (index_start_address + i)->index_reference_value = *(array_address + (i * the_number_of_index));
    }

    return index_start_address;
}


int main() {

    srand((unsigned int)time(NULL));

    int* array_address = NULL;
    int array_num = 0;
    int input = 0;

    printf("----------------------------------------------------------------------------\n");
    printf("�˻������ �����غ��ϴ�. �迭 ũ�⿡ �ش��ϴ� ���� �Է��ϸ�,\n �迭�� ���� �� �迭�� index + a(1~5) �� �����ϴ� ������ �Էµ˴ϴ�.");
    printf("----------------------------------------------------------------------------\n\n");

    printf("�˻��� ����� �Ǵ� �迭�� ũ�⸦ �Է��ϼ��� (0�̿��� ���� �� ��Ź�����~) : ");
    scanf_s("%d", &array_num);

    if (array_num == 0) {
        printf("�迭�� ũ�Ⱑ 0�̹Ƿ� �ý����� �����մϴ�\n");
        exit(0);
    }

    array_address = (int*)calloc(array_num, sizeof(int));

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

    printf("\n\n�� �Է��� �Ϸ�Ǿ����ϴ� (hint : ���� ���� �� = %d, ���� ���� �� = %d) \n", *(array_address), *(array_address + array_num - 1));

    int index_interval;
    printf("index�� ������ �����ּ��� : ");
    scanf_s("%d", &index_interval);

    printf("\n\t<< ���� ���� �˻� >>\n");

    int index_length = array_num / index_interval;
        
    index* index_address = makeIndexTable(array_address, array_num, index_interval);

    indexSearch(array_address, array_num, 1 , index_length, index_address);
    indexSearch(array_address, array_num, 2 , index_length, index_address);
    indexSearch(array_address, array_num, 8 , index_length, index_address);
    indexSearch(array_address, array_num, 9 , index_length, index_address);
    indexSearch(array_address, array_num, 11, index_length, index_address);
    indexSearch(array_address, array_num, 19, index_length, index_address);
    indexSearch(array_address, array_num, 29, index_length, index_address);
    indexSearch(array_address, array_num, 3 , index_length, index_address);
    indexSearch(array_address, array_num, 10, index_length, index_address);

    return 0;
}

//검색(탐색) : 여러 개의 자료들 중에서 원하는 자료를 찾는 작업 (= 방법은 여러가지지만 빨리 찾는게 성능상 유리..)

// 3. 색인 순차 탐색(indexed sequential search)
//    : 주 자료 집합에서 일정 간격으로 발췌한 인덱스(index) 테이블 활용 (단! 주 자료 데이터 집합과 인덱스 테이블은 모두 정렬되어 있어야 한다)
//      -> 그러니까 미리 일정한 간격으로 수를 집어넣어, 각 항의 값의 위치값을 참고하는 목차(index)리스트를 만들고, 검색되는 값이 어디에 있을지 찾는걸 그 목차를 먼저 참고해서 검색범위를 정한다는 개념으로 받아들이자

//  # 특징이 있다면 검색을 할 구간을 정해둔다는 것 (= 범위가 정해지면 그 다음은 어떤 검색을 해도 상관없음)
//  # 인덱스 테이블에서 index는 순차적이지만, 이를 주 자료에 쓰려면 사이사이가 비어야 함 = 영문사전 찾는듯한 개념으로 가면 된다

#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>

typedef struct index {
    int index_sequence;
    int index_reference_value;
}index;

void sequentialSearch2(int* array_address, int begin, int end, int key) {

    int i = begin;

    printf("\n해당 배열에서 검색값 [%d]를 검색하여라!\n\n", key);

    while (i < end && *(array_address + i) <= key) {

        if (*(array_address + i) == key) {
            printf(" ->> (결론) 해당배열 %d번째에 대상값 %d가 존재함을 확인했습니다!\n", (i - begin) + 1, key);
            return;
        }
        else {
            printf(" ->> 해당배열 %d번째에 없음을 확인함! \n", (i - begin) + 1);
        }

        i++;
    }

    printf(" ->> (결론) %d는 대상 배열에서 존재하지 않는 값입니다!\n", key);
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
    printf("검색기능을 수행해봅니다. 배열 크기에 해당하는 값을 입력하면,\n 배열의 값은 각 배열의 index + a(1~5) 에 대응하는 값으로 입력됩니다.");
    printf("----------------------------------------------------------------------------\n\n");

    printf("검색의 대상이 되는 배열의 크기를 입력하세요 (0이외의 값을 좀 부탁드려용~) : ");
    scanf_s("%d", &array_num);

    if (array_num == 0) {
        printf("배열의 크기가 0이므로 시스템을 종료합니다\n");
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

    printf("\n\n값 입력이 완료되었습니다 (hint : 가장 작은 값 = %d, 가장 높은 값 = %d) \n", *(array_address), *(array_address + array_num - 1));

    int index_interval;
    printf("index의 간격을 정해주세요 : ");
    scanf_s("%d", &index_interval);

    printf("\n\t<< 색인 순차 검색 >>\n");

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

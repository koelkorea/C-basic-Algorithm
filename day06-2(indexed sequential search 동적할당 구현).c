//검색(탐색) : 여러 개의 자료들 중에서 원하는 자료를 찾는 작업 (= 방법은 여러가지지만 빨리 찾는게 성능상 유리..)

// 3. 색인 순차 탐색(indexed sequential search)
//    : 주 자료 집합에서 일정 간격으로 발췌한 인덱스(index) 테이블 활용 (단! 주 자료 데이터 집합과 인덱스 테이블은 모두 정렬되어 있어야 한다)
//      -> 그러니까 미리 일정한 간격으로 수를 집어넣어, 각 항의 값의 위치값을 참고하는 목차(index)리스트를 만들고, 검색되는 값이 어디에 있을지 찾는걸 그 목차를 먼저 참고해서 검색범위를 정한다는 개념으로 받아들이자

//  # 특징이 있다면 검색을 할 구간을 정해둔다는 것 (= 범위가 정해지면 그 다음은 어떤 검색을 해도 상관없음)
//  # 인덱스 테이블에서 index는 순차적이지만, 이를 주 자료에 쓰려면 사이사이가 비어야 함 = 영문사전 찾는듯한 개념으로 가면 된다

// 색인 순차 탐색 정적배열을 사용하여 구현 (index 구간의 간격 입력 -> index 데이터 수를 도출하는 방법)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>

typedef struct index {
    int index_checkpoint;
    int index_reference_value;
}index;

void sequentialSearch2(int* array_address, int start, int end, int key) {

    int i = start;

    printf("\n해당 배열에서 검색값 [%d]를 검색하여라!\n\n", key);

    while (i < end && *(array_address + i) <= key) {

        if (*(array_address + i) == key) {
            printf(" ->> (결론) 해당배열 %d번째에 대상값 %d가 존재함을 확인했습니다!\n\n", (i - start) + 1, key);
            return;
        }
        else {
            printf(" ->> 해당배열 %d번째에 없음을 확인함! \n", (i - start) + 1);
        }

        i++;
    }

    printf(" ->> (결론) %d는 대상 배열에서 존재하지 않는 값입니다!\n\n", key);
}

// 2단계) 검색값을 index 배열 목차의 값들과 비교하여 어디쯤에 위치하는지 찾기 (구간위치는 2개의 값으로 기록해야 함.. 그래야 그 구간을 찾아 순차검색 ㄱㄱ함)
int indexSearch(int* array_address, int array_num, int key, int index_length, index* index_address) {

    int i, start = 0, end = array_num;

    // 검색할 값이 타겟 배열의 1번 값보다 작아서 검색할 이유가 없거나, 마지막 배열의 값보다 커서 검색할 이유가 없는 경우
    if (key < *(array_address) || key > *(array_address + array_num - 1)) {
        printf(" ->> (사전 판정) %d는 대상 배열의 범위를 넘어선 값입니다!\n\n", key);
        return;
    }

    // index 배열 정보를 도출한 index 데이터의 수만큼 채우기 시작
    for (i = 1; i < index_length; i++) {

        if (((index_address + i - 1)->index_reference_value <= key) && (((index_address + i - 1)->index_reference_value > key))) {

            start = (index_address + i - 1)->index_checkpoint;
            end = (index_address + i)->index_checkpoint;
            break;
        }
        else {

            start = (index_address + i)->index_checkpoint;
            end = array_num;
        }
    }

    sequentialSearch2(array_address, start, end, key);
}

// 1단계) 타겟배열의 정보를 통해 index 정보를 완성시키기 (parameter : 해당 배열의 위치, 해당 배열의 크기, index 간격  <- 이걸 재료로 index_reference 배열 크기에 맞게 index 페이지를 채움)
index* makeIndexTable(int* array_address, int max_size, int interval) {

    // index 구조체 포인터 (index 배열 동적할당 위치 저장용)
    index* index_start_address = NULL;

    // index 배열의 크기 
    int the_number_of_index = max_size / interval;

    // 만약 타겟 배열의 길이 / index 배열의 길이에 나머지 값이 존재한다면, 에러를 방지하기 위해 각 index의 구간을 1증가시켜 index 구간을 넓힌다
    if (max_size % interval > 0) {
        the_number_of_index = the_number_of_index + 1;
    }

    // index 배열 생성을 위한 메모리 공간 할당 후, 시작위치 알려줌
    index_start_address = (index*)calloc(the_number_of_index, sizeof(index));

    // index 배열 정보를 채우기 시작
    for (int i = 0; i < interval; i++) {
        (index_start_address + i)->index_checkpoint = i * the_number_of_index;
        (index_start_address + i)->index_reference_value = *(array_address + (i * the_number_of_index));
    }

    return index_start_address;
}


int main() {

    srand((unsigned int)time(NULL));

    // 검색 대상 동적 배열 시작 위치
    int* array_address = NULL;

    // 검색 대상 배열 길이 (초기화)
    int array_num = 0;

    // 검색값 (초기화)
    int input = 0;

    // 목차 index 배열의 요소들의 간격이 얼만지(초기화)
    //  -> 미리 길이를 정해놔야 하는 정적배열과 다르게, 동적배열에서는 필요한 길이를 제시하면, 그에 맞춰 만드는게 가능함
    int index_interval;


    printf("----------------------------------------------------------------------------\n");
    printf("검색기능을 수행해봅니다. 배열 크기에 해당하는 값을 입력하면,\n 배열의 값은 각 배열의 index + a(1~5) 에 대응하는 값으로 입력됩니다.");
    printf("----------------------------------------------------------------------------\n\n");

    printf("검색의 대상이 되는 배열의 크기를 입력하세요 (0이외의 값을 좀 부탁드려용~) : ");
    scanf_s("%d", &array_num);

    // 배열 길이가 없으면 시스템 종료
    if (array_num == 0) {
        printf("배열의 크기가 0이므로 시스템을 종료합니다\n");
        exit(0);
    }

    // 배열 길이가 정해졌으면, 그 길이만큼 메모리를 동적할당하고, 그 시작주소값을 array_address에 대입
    array_address = (int*)calloc(array_num, sizeof(int));

    // 동적할당한 메모리 각각의 값이 정렬된 효과를 낳게, 랜덤한 값이 들어갈수 있게하되, 무조건 자기 이전의 값에 추가값을 더하는 식으로 설계
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

    // (선) index 데이터의 간격 입력 -> 이를통해 index 동적배열 길이를 도출 (= index 데이터의 간격이 index 테이블 생성함수 내의 로직으로 가면 안되는 이유)
    printf("index의 간격을 정해주세요 : ");
    scanf_s("%d", &index_interval);

    // index 배열을 동적할당하고, 그 시작주소를 index_address에 할당
    index* index_address = makeIndexTable(array_address, array_num, index_interval);

    // (후) index 동적배열 길이 = 해당 배열길이 / index 데이터의 간격
    //  -> (중요) index 동적배열 길이를 main의 지역변수로 쓰는 이유?
    //     -> index 테이블에서의 구간을 찾기 위한 검색을 위해서는 index 데이터만큼을 for문을 돌리는게 안전한데, 그걸 위해서는 index_interval이 필요함
    //        -> index_interval을 파라미터로 보내서 index 동적배열 길이를 계산해도 괜찮지만, 코드의 의미분석에 짜증나지기에 이렇게 계산해서 파라미터로 넘기는게 나음
    int index_length = array_num / index_interval;


    printf("\n\t<< 색인 순차 검색 >>\n");

    while (1) {

        int search_value = 0;

        printf("검색을 원하는 값을 입력해주세요 (0 = 종료하기): ");
        scanf_s("%d", &search_value);

        // index 페이지에서 범위 설정 완료하고 나면?
        //  -> 그 index 범위에 대해서만, 타겟 배열을 순차 검색(sequentialSearch2)하기
        indexSearch(array_address, array_num, search_value, index_length, index_address);   // 메인애서 도출한 index_length 파라미터로 사용
    }

    return 0;
}

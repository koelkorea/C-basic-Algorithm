//검색(탐색) : 여러 개의 자료들 중에서 원하는 자료를 찾는 작업 (= 방법은 여러가지지만 빨리 찾는게 성능상 유리..)

// 3. 색인 순차 탐색(indexed sequential search)
//    : 주 자료 집합에서 일정 간격으로 발췌한 인덱스(index) 테이블 활용 (단! 주 자료 데이터 집합과 인덱스 테이블은 모두 정렬되어 있어야 한다)
//      -> 그러니까 미리 일정한 간격으로 수를 집어넣어, 각 항의 값의 위치값을 참고하는 목차(index)리스트를 만들고, 검색되는 값이 어디에 있을지 찾는걸 그 목차를 먼저 참고해서 검색범위를 정한다는 개념으로 받아들이자

//  # 특징이 있다면 검색을 할 구간을 정해둔다는 것 (= 범위가 정해지면 그 다음은 어떤 검색을 해도 상관없음)
//  # 인덱스 테이블에서 index는 순차적이지만, 이를 주 자료에 쓰려면 사이사이가 비어야 함 = 영문사전 찾는듯한 개념으로 가면 된다

// 색인 순차 탐색 정적배열을 사용하여 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define INDEX_REFERENCE_LENGTH 100

// index 정보를 구성하는 구조체는 다음과 같이 구성 (몇 페이지에 어떤 제목이 있는지를 표시하는 목차라고 생각하면 간단.. 단지 그걸 일정한 숫자값을 기준으로 할 뿐) 
//  - 해당 index값이 위치하는 배열의 공간 위치값 (배열의 페이지라고 생각하자)
//  - 해당 index값 그 자체 (제목이라고 생각하자)
typedef struct index {
    int index_checkpoint;
    int index_reference_value;
}index;

// index 구조체로 구성된 배열을 통해 목차를 생성   <- 정적배열인지라 목차의 간격은 사전에 정해둬야 함
index index_reference[INDEX_REFERENCE_LENGTH] = { {0,0} };

// 3단계) index배열 목차범위를 이용한, 순차검색으로 search값의 존재유무 검색
void sequentialSearch2(int target_array[], int start, int end, int key) {

    printf("\n 검색값 [%d]를 target_array[%d] ~ [%d] 까지 순차검색하여라!\n\n", key, start, end);

    // start ~ end 사이의 타겟 배열의 요소값을 key값과 대조시키는 순차검색 사용
    for (int i = start; i <= end; i++) {

        if (target_array[i] == key) {
            printf(" ->> (결론) 해당배열 %d번째에 대상값 %d가 존재함을 확인했습니다!\n\n", i + 1, key);
            return;
        }
        else {
            printf(" ->> 해당배열 %d번째에 대상값 %d가 없음을 확인함!\n", i + 1, key);
        }
    }

    printf(" ->> (결론) %d는 대상 배열에서 존재하지 않는 값입니다!\n\n", key);
}

// 2단계) 검색값을 index 배열 목차의 값들과 비교하여 어디쯤에 위치하는지 찾기 (구간위치는 2개의 값으로 기록해야 함.. 그래야 그 구간을 찾아 순차검색 ㄱㄱ함)
void indexSearch(int target_array[], int target_array_length, int key) {

    // 순차검색 시작점 ~ 끝점
    int check_point1 = 0, check_point2 = target_array_length - 1;

    // 검색할 값이 타겟 배열의 1번 값보다 작아서 검색할 이유가 없거나, 마지막 배열의 값보다 커서 검색할 이유가 없는 경우
    if (key < target_array[0] || key > target_array[target_array_length - 1]) {

        printf(" ->> (사전 판정) %d는 대상 배열의 범위를 넘어선 값입니다!\n\n", key);
        return;
    }

    // key값을 index 목차 배열에 위치한 각 방의 index_reference_value와 비교한다 
    for (int i = 0; i < INDEX_REFERENCE_LENGTH; i++) {

        // index 배열의 index_reference_value 값이 0인 경우, 그 부분부터는 index 정보가 없다는 의미니, 의미없이 순회하는 반복문을 끊어준다
        if (index_reference[i].index_checkpoint == 0 && index_reference[i].index_reference_value == 0) {
            break;
        }

        // index_checkpoint값과 index_reference_value가 0이 아니라면, key값과 대조해보며, 그에 따른 분기에 따라 명령을 처리

        // index_reference_value가 key값이면.. -> 바로 결과 공표 후 종료
        if (index_reference[i].index_reference_value == key) {

            printf(" ->> (사전 판정) 해당배열 %d번째에 대상값 %d가 존재함을 확인했습니다!\n\n", index_reference[i].index_checkpoint, key);
            return;
        }
        // index_reference_value가 key값보다 작다면.. -> check_point1울 해당 위치값으로 갱신
        else if (index_reference[i].index_reference_value < key) {

            check_point1 = index_reference[i].index_checkpoint;
        }
        // index_reference_value가 key값보다 작다면.. -> check_point2울 해당 위치값으로 갱신 후 반복문 해제
        else if (index_reference[i].index_reference_value > key) {

            check_point2 = index_reference[i].index_checkpoint;
            break;
        }
    }

    // 반복문을 통해 얻은 check_point1, check_point2를 베이스로 순차검색 실시
    sequentialSearch2(target_array, check_point1, check_point2, key);
}

// 1단계) 타겟배열의 정보를 통해 index 정보를 완성시키기 (parameter : 해당 배열의 위치, 해당 배열의 크기  <- 이걸 재료로 index_reference 배열 크기에 맞게 index 페이지를 채움)
void makeIndexTable(int target_array[], int target_array_length) {
  
	// (선) index 데이터의 간격 입력(당연히 index 데이터의 수를 구하는데 사용될 예정)
	int index_interval = 0;
	printf("index의 간격을 정해주세요 (배열의 길이 %d보단 작은 값 부탁드립니다): ", target_array_length);
	scanf_s("%d", &index_interval);

    // (후) index 데이터의 수 = 타겟 배열의 길이 / index 구간의 간격
    int the_number_of_index = max_size / interval;
	
    // 만약 타겟 배열의 길이 / index 데이터의 수에 나머지 값이 존재한다면, 에러를 방지하기 위해 각 index 데이터의 수를 1증가시켜 나머지도 포용할 수 있도록 index 데이터를 늘린다
    if (target_array_length % the_number_of_index != 0) {
        the_number_of_index++;
    }

    // index 배열 정보를 도출한 index 데이터의 수만큼 채우기 시작 (간격은 1로 하지 않는 이상 공간이 남게 )
    for (int i = 0; i < the_number_of_index; i++) {

        // 만약 표기될 인덱스가 타겟 길이보다 같거나(= 배열의 위치 최대값 = 길이 - 1 이기 때문) 크면?
        //  -> 더이상 index를 넣지않음
        if (i * index_interval >= target_array_length) {
            break;
        }
        else if (i * index_interval < target_array_length) {

            // index구조체 각 챕터에 채워넣을 체크포인트 index 위치값과 그 체크포인트에 위치한 index값을 대입
            index_reference[i].index_checkpoint = i * index_interval;
            index_reference[i].index_reference_value = target_array[i * index_interval];

        }
    }

}

int main() {

    srand((unsigned int)time(NULL));

    // 검색 대상 배열
    int target_array[100] = { 0 };

    // 검색 대상 배열 길이
    int target_array_length = 100;

    // 검색 대상 배열에 값 채우기
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

    printf("\n\t<< 색인 순차 검색 >>\n");

    // 타겟 배열의 index 페이지를 만들기 
    makeIndexTable(target_array, target_array_length);

    while (1) {

        int search_value = 0;

        printf("검색을 원하는 값을 입력해주세요 (0 = 종료하기): ");
        scanf_s("%d", &search_value);

        if (search_value <= 0 || search_value > target_array[target_array_length-1]) {

            printf("프로그램이 종료되었습니다.");
            exit(0);
        }

        // index 페이지에서 범위 설정 완료하고 나면?
        //  -> 그 index 범위에 대해서만, 타겟 배열을 순차 검색(sequentialSearch2)하기
        indexSearch(target_array, target_array_length, search_value);
    }

    return 0;
}

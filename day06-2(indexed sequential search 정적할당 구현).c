//검색(탐색) : 여러 개의 자료들 중에서 원하는 자료를 찾는 작업 (= 방법은 여러가지지만 빨리 찾는게 성능상 유리..)

// 3. 색인 순차 탐색(indexed sequential search)
//    : 순차검색 + 주 자료 집합에서 일정 간격으로 발췌한 인덱스(index) 테이블 활용 (단! 주 자료 데이터 집합과 인덱스 테이블은 모두 정렬되어 있어야 한다)
//      -> 그러니까 미리 일정한 간격으로 수를 집어넣어 각 수의 상대적 위치값을 참고하는 index 테이블을 만들고, 입력되는 값이 어디에 들어가야 할지를 그 index 테이블을 참고한다는 것
//         (= 인덱스 테이블에서 index는 순차적이지만, 이를 주 자료에 쓰려면 사이사이가 비어야 함 = 영문사전 찾는듯한 개념으로 가면 된다)

#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함

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

    // 검색 대상 배열
    int target_array[100] = { 0 };

    // 검색 대상 배열 길이
    int target_array_length = 100;

    // 검색 대상 배열에 값 채우기
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

    printf("\n\t<< 색인 순차 검색 >>\n");
    makeIndexTable(target_array, target_array_length);

    while (1) {

        int search_value = 0;

        printf("검색을 원하는 값을 입력해주세요 (0 = 종료하기): ");
        scanf_s("%d", &search_value);

        if (search_value == 0) {

            printf("프로그램이 종료되었습니다.");
            exit(0);
        }

        indexSearch(target_array, target_array, search_value);
    }

    return 0;
}

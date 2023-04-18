//검색(탐색) : 여러 개의 자료들 중에서 원하는 자료를 찾는 작업 (= 방법은 여러가지지만 빨리 찾는게 성능상 유리..)

// 1. 선형 검색(Linear Search) = 순차 검색(Sequential Search)
//    : 데이터 더미에서 처음부터 끝까지 하나씩 순서대로 비교하며 원하는 값을 찾아내는 알고리즘

//  # 선형 검색 특징
//   - 데이터를 정렬하거나 따로 건드릴 필요가 없음
//   - 데이터의 양이 많아지면 검색의 소요 시간도 비례
//   - 하나씩 일일이 비교하기 때문에 비효율적
//   - 연결리스트에서 자주 쓰임 (= sort가 되어있지 않으므로, 대조하는거 말고는 방법이 읍다)

//  # 구현 예시
//    int seq_search(int key, int low, int high){
//        int i;
//        for (i = low; i <= high; i++) {
//            if (list[i] == key) {
//                return i;
//            }
//          return -1;
//        }
//    }

//    ListNode* search(ListNode* head, int x){
// 
//        ListNode* p = head;
//        while (p != NULL) {
//            if (p->data == x) return p;
//            p = p->link;
//        }
//        return p;
//    }

// 2. 이진검색(Binary Search) = 이분(二分)검색
//    : 정렬(sort)되어 있는 데이터의 집합에서 원하는 값을 찾기 위해, 데이터의 중위값에 해당하는 녀석을 기준으로 큰지 작은지를 보고, 그 결과값에 따라 다음 검색 영역을 축소해서 같은 것을 계속 반복
// 
//  # 선형 검색 특징
//   - 반으로 나누어서 연산하는 방법(거듭제곱 식)
//   - 데이터의 집합이 반드시 정렬(Sort)이 필요
//   - 중간값부터 탐색, 트리구조에서 자주 쓰임
//   - 처리속도가 매우 빠르다

//  # 구현 예시 (low, high는 배열의 index에 해당)

// 3. 색인 순차 탐색(indexed sequential search)
//    : 주 자료 집합에서 일정 간격으로 발췌한 인덱스(index) 테이블 활용 (단! 주 자료 데이터 집합과 인덱스 테이블은 모두 정렬되어 있어야 한다)
//      -> 그러니까 미리 일정한 간격으로 수를 집어넣어, 각 항의 값의 위치값을 참고하는 목차(index)리스트를 만들고, 검색되는 값이 어디에 있을지 찾는걸 그 목차를 먼저 참고해서 검색범위를 정한다는 개념으로 받아들이자

//  # 특징이 있다면 검색을 할 구간을 정해둔다는 것 (= 범위가 정해지면 그 다음은 어떤 검색을 해도 상관없음)
//  # 인덱스 테이블에서 index는 순차적이지만, 이를 주 자료에 쓰려면 사이사이가 비어야 함 = 영문사전 찾는듯한 개념으로 가면 된다

// 4. 보간 탐색(interpolation search)
//    : 정렬된 데이터 집합에서 값과 인덱스(데이터의 위치)에 "비례" 정도를 기준. key가 존재할 위치를 대략적으로 찾아 탐색하는 방법
//      (= 각 항의 데이터들간의 간격이 일정하다는 가정이 필요하다!)



// 동적할당을 사용한 순차검색, 이진검색 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>

// 선형 검색(Linear Search) = 순차 검색(Sequential Search)
//  : 데이터 더미에서 처음부터 끝까지 하나씩 순서대로 비교하며 원하는 값을 찾아내는 알고리즘
//    -> 배열의 모든 주소값과 key값이 같은지 일일이 따져가는 방법
int seq_search(int* list, int key, int low, int high);

// 이진검색(Binary Search) = 이분(二分)검색
//  : 정렬(sort)되어 있는 데이터의 집합에서 원하는 값을 찾기 위해, 데이터의 중위값에 해당하는 녀석을 기준으로 큰지 작은지를 보고, 그 결과값에 따라 다음 검색 영역을 축소해서 같은 것을 계속 반복
int search_binary(int* arr, int key, int low, int high) {

    // 해당 배열 길이의 현재 중앙위치(이걸로 배열의 중위값 추출) 정하기 (= 이진검색이 진행됨에 따라 검색 범위가 축소됨)
    int reference_index = (low + high) / 2;

    // 만약 현재의 최저값이 최고값보다 작다면, 계속 진행
    if (low <= high) {

        // 값을 찾았으면, 그 배열의 주소 리턴
        if (key == *(arr + reference_index)) {

            return reference_index;
        }
        // 찾는 값보다 배열의 중위값이 작으면, 검색위치를 '중위값 + 1' ~ '현재 범위 끝 위치'로 놓고 이진검색을 재귀한다
        else if (key > *(arr + reference_index)) {

            return search_binary(arr, key, reference_index + 1, high);
        }
        // 찾는 값보다 배열의 중위값이 작으면, 검색위치를 '현재 범위 첫 위치' ~ '중위값 - 1'로 놓고 이진검색을 재귀한다
        else if (key < *(arr + reference_index)) {

            return search_binary(arr, key, low, reference_index - 1);
        }
    }

    // 검색에 실패했을 경우 -1 반환
    return -1;
}

int main(void) {

    srand((unsigned int)time(NULL));

    // 동적배열의 위치를 받아낼 포인터
    int* array_address = NULL;
    // 동적배열의 길이값
    int array_num = 0;
    // 검색할 값
    int input = 0;

    printf("----------------------------------------------------------------------------\n");
    printf("검색기능을 수행해봅니다. 배열 크기에 해당하는 값을 입력하면,\n 배열의 값은 각 배열의 index + a(1~5) 에 대응하는 값으로 입력됩니다.");
    printf("----------------------------------------------------------------------------\n\n");

    printf("검색의 대상이 되는 배열의 크기를 입력하세요(0이외의 값을 좀 부탁드려용~) : ");
    scanf_s("%d", &array_num);

    if (array_num == 0) {
        printf("배열의 크기가 0이므로 시스템을 종료합니다\n");
        exit(0);
    }

    // 동적할당 시행
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

    printf("값 입력이 완료되었습니다. \n");
    printf("hint : 가장 작은 값 = %d, 가장 높은 값 = %d)", *(array_address), *(array_address + array_num - 1));

    while (1) {

        int search_value = 0;

        printf("이거다 싶은 값을 입력 부탁드립니다(%d ~ %d) (0 = 종료하기) : ", *(array_address), *(array_address + array_num - 1));
        scanf_s("%d", &input);

        if (search_value <= 0 || search_value > *(array_address + array_num - 1)) {

            printf("\n(경고!)배열값들의 범위를 넘어선 값입니다. 프로그램이 종료되었습니다.\n");
            exit(0);
        }

        if (search_binary(array_address, input, 0, array_num - 1) != -1) {
            printf("이진 탐색 결과 -> %d는 %d번째\n\n", input, search_binary(array_address, input, 0, array_num - 1) + 1);
        }
        else {
            printf("이진 탐색 결과 -> %d는 존재하지 않는 값입니다.\n\n", input);
        }
    }

    return 0;

}
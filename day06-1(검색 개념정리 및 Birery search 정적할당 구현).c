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


// 정적할당을 사용한 순차검색, 이진검색 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define ARRAY_LENGTH 50

// 선형 검색(Linear Search) = 순차 검색(Sequential Search)
//  : 데이터 더미에서 처음부터 끝까지 하나씩 순서대로 비교하며 원하는 값을 찾아내는 알고리즘
//    -> 배열의 모든 주소값과 key값이 같은지 일일이 따져가는 방법
int seq_search(int* list, int key, int low, int high) {

    for (int i = low; i <= high; i++) {

        if (list[i] == key) {

            return i;
        }
    }

    return -1;
}

// 이진검색(Binary Search) = 이분(二分)검색
//  : 정렬(sort)되어 있는 데이터의 집합에서 원하는 값을 찾기 위해, 데이터의 중위값에 해당하는 녀석을 기준으로 큰지 작은지를 보고, 그 결과값에 따라 다음 검색 영역을 축소해서 같은 것을 계속 반복
int search_binary(int arr[], int key, int low, int high) {

    // 해당 배열 길이의 현재 중앙위치(이걸로 배열의 중위값 추출) 정하기 (= 이진검색이 진행됨에 따라 검색 범위가 축소됨)
    int reference_index = (low + high) / 2;

    // 만약 현재의 최저값이 최고값보다 작다면, 계속 진행
    if (low <= high) {

        // 값을 찾았으면, 그 배열의 주소 리턴
        if (key == arr[reference_index]) {

            return reference_index;
        }
        // 찾는 값보다 배열의 중위값이 작으면, 검색위치를 '중위값 + 1' ~ '현재 범위 끝 위치'로 놓고 이진검색을 재귀한다
        else if (key > arr[reference_index]) {

            return search_binary(arr, key, reference_index + 1, high);
        }
        // 찾는 값보다 배열의 중위값이 작으면, 검색위치를 '현재 범위 첫 위치' ~ '중위값 - 1'로 놓고 이진검색을 재귀한다
        else if (key < arr[reference_index]) {

            return search_binary(arr, key, low, reference_index - 1);
        }
    }

    // 검색에 실패했을 경우 -1 반환
    return -1;
}

int main() {

    srand((unsigned int)time(NULL));

    printf("----------------------------------------------------------------------------\n");
    printf("배열의 길이는 50이며, 이진검색과 순차검색을 수행해봅니다.\n각 배열값은 각 배열의 이전 배열값 + a(1~5) 에 대응하는 값으로 입력됩니다.\n");
    printf("----------------------------------------------------------------------------\n\n");

    int ary_test[ARRAY_LENGTH] = { 0 };
    int input = 0;

    // 랜덤한 값이 들어갈수 있게하되, 배열에 들어간 값이 정렬 효과를 낳도록 무조건 자기 이전의 값에 추가값을 더하는 식으로 설계
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

    printf("\n\n값 입력이 완료되었습니다. \n");
    printf("(hint : 가장 작은 값 = %d, 가장 높은 값 = %d)\n\n", ary_test[0], ary_test[49]);

    while (1) {

        printf("찾고 싶은 숫자를 %d ~ %d에서 입력하세요. (범위 밖 입력 = 종료) :", ary_test[0], ary_test[49]);
        scanf_s("%d", &input);

        if (ary_test[0] <= 0 || input > ary_test[49]) {
            printf("배열값들의 범위를 넘어선 값입니다. \n");
            break;
        }

        // 순차검색을 실행 (-1 이외의 값이 나옴 = 해당 배열 내에 값이 존재)
        if (seq_search(ary_test, input, 0, ARRAY_LENGTH) != -1) {

            // (검색 값의 위치) search_binary ( 검색 배열, 검색 값, 낮은 범위 칸, 최대 범위 칸 )
            printf(" ->> (성공) 순차 탐색 : 검색값 [%d]는 해당배열의 %d번째 공간에 위치합니다.\n", input, seq_search(ary_test, input, 0, ARRAY_LENGTH) + 1);
        }
        else {

            printf(" ->> [%d]는 순차 탐색 실패\n", input);
        }

        // 이진 검색 실행 (-1 이외의 값이 나옴 = 해당 배열 내에 값이 존재)
        if (search_binary(ary_test, input, 0, ARRAY_LENGTH) != -1) {

            // (검색 값의 위치) search_binary ( 검색 배열, 검색 값, 낮은 범위 칸, 최대 범위 칸 )
            printf(" ->> (성공) 이진 탐색 : 검색값 [%d]는 해당배열의 %d번째 공간에 위치합니다.\n", input, search_binary(ary_test, input, 0, ARRAY_LENGTH) + 1);

        }
        else {

            printf(" ->> [%d]는 이진 탐색 실패\n", input);
        }
        printf("\n");

    }
    return 0;
}

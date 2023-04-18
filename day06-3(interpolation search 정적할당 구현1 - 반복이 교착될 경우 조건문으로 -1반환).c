//검색(탐색) : 여러 개의 자료들 중에서 원하는 자료를 찾는 작업 (= 방법은 여러가지지만 빨리 찾는게 성능상 유리..)

// 4. 보간 탐색(interpolation search)
//    : 정렬된 데이터 집합에서 값과 인덱스(데이터의 위치)에 "비례" 정도를 기준. key가 존재할 위치를 대략적으로 찾아 탐색하는 방법
//      (= 각 항의 데이터들간의 간격이 일정하다는 가정이 필요하다!)

// 정적할당을 사용한 보간탐색 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define ARRAY_LENGTH 100

// 보간 탐색(interpolation search)
//  : 정렬된 데이터 집합에서 값과 인덱스(데이터의 위치)에 "비례" 정도를 기준. key가 존재할 위치를 대략적으로 찾아 탐색하는 방법
int interpolation_search(int arr[], int key, int low, int high) {

    // 보간 검색 공식을 통한 값 얻기 (= 소수점 근사값이라 정수화를 통해 근사치 검색 필요)
    float result = (key - arr[low]) / (arr[high] - arr[low]) * (high - low) + low;

    // 보간 검색 결과인 result를 반올림한 정수를 인덱스의 시작점으로.. = 보간검색 공식을 통해 얻은 추정 배열위치
    int search_index = (int) (result + 0.5);

    // search_index가 조정되는 가장 낮은 공간값와 높은 공간값 사이에 있으면 계속 진행
    //  -> 조건은 이렇게 잡아도 무한루프시 탈출 할 방법은 1번째 if 조건에 둠
    while (search_index >= low || search_index < high) {

        if (low + 1 == high) {
            // 검색에 실패했을 경우 -1 반환
            return -1;
        }

        // 배열[search_index]에 위치한 값이 key와 같다면? -> search_index의 값 리턴
        if (arr[search_index] == key) {

            return search_index;
        }
        // 배열[search_index]에 위치한 값이 key보다 크다면?
        // -> 그 아래주소에 값이 있다는 의미 => high의 값을 search_index로 두고, 현재 추정되는 보간검색을 통해 추정되는 값의 위치인 search_index를 -1한다
        else if (arr[search_index] > key) {

            high = search_index;
            search_index--;
        }
        // 배열[search_index]에 위치한 값이 key보다 작다면?
        // -> 그 윗주소에 값이 있다는 의미 => low의 값을 search_index로 두고, 현재 추정되는 보간검색을 통해 추정되는 값의 위치인 search_index를 +1한다
        else if (arr[search_index] < key) {

            low = search_index;
            search_index++;
        }
    }

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
    printf("(hint : 가장 작은 값 = %d, 가장 높은 값 = %d)\n\n", ary_test[0], ary_test[ARRAY_LENGTH-1]);

    while (1) {

        printf("찾고 싶은 숫자를 %d ~ %d에서 입력하세요. (범위 밖 입력 = 종료) :", ary_test[0], ary_test[ARRAY_LENGTH - 1]);
        scanf_s("%d", &input);

        if (ary_test[0] <= 0 || input > ary_test[ARRAY_LENGTH - 1]) {
            printf("\n(경고!)배열값들의 범위를 넘어선 값입니다. 프로그램이 종료되었습니다.\n");
            exit(0);
        }

        // 보간 검색 실행 (-1 이외의 값이 나옴 = 해당 배열 내에 값이 존재)
        int result = interpolation_search(ary_test, input, 0, ARRAY_LENGTH - 1);
        
        if (result != -1) {

            // (검색 값의 위치) search_binary ( 검색 배열, 검색 값, 낮은 범위 칸, 최대 범위 칸 )
            printf(" ->> (성공) 보간 탐색 : 검색값 [%d]는 해당배열의 %d번째 공간에 위치합니다.\n", input, result + 1);

        }
        else {

            printf(" ->> [%d]는 보간 탐색 실패\n", input);
        }
        printf("\n");

    }
    return 0;
}

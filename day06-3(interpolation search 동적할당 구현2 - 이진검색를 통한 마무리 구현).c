//검색(탐색) : 여러 개의 자료들 중에서 원하는 자료를 찾는 작업 (= 방법은 여러가지지만 빨리 찾는게 성능상 유리..)

// 4. 보간 탐색(interpolation search)
//    : 정렬된 데이터 집합에서 값과 인덱스(데이터의 위치)에 "비례" 정도를 기준. key가 존재할 위치를 대략적으로 찾아 탐색하는 방법
//      (= 각 항의 데이터들간의 간격이 일정하다는 가정이 필요하다!)

// 정적할당을 사용한 보간탐색 구현2 (이진검색을 통한 마무리)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define ARRAY_LENGTH 100

// 보간 탐색(interpolation search)
//  : 정렬된 데이터 집합에서 값과 인덱스(데이터의 위치)에 "비례" 정도를 기준. key가 존재할 위치를 대략적으로 찾아 탐색하는 방법

// 보간 검색 대상 배열의 시작주소를 기준 가장 낮은 녀석을 0, 가장 높은 주소를 '배열의 길이-1'로 가정하고, 거기서 key를 찾는 알고리즘
int interpolation_search(int* arr, int key, int low, int high) {

    // 보간 검색 공식을 통한 값 얻기 (= 소수점 근사값이라 정수화를 통해 근사치 검색 필요)
    float result = (key - *(arr + low)) / (*(arr + high) - *(arr + low)) * (high - low) + low;

    // 보간 검색 결과인 result를 반올림한 정수를 인덱스의 시작점으로..
    int search_index = (int)(result + 0.5);

    // 만약 현재의 최저값이 최고값보다 작다면, 계속 진행
    if (low <= high) {

        // 배열의 시작주소 + search_index를 역참조한 값이 key와 같다면? -> search_index의 값 리턴
        if (*(arr + search_index) == key) {

            return search_index;
        }
        // 배열의 시작주소 + search_index를 역참조한 값이 key보다 크다면? -> high의 값을 search_index - 1 (해당 주소값보다 1작은 주소에 위치한 주소)로 두고 다시 돌림
        else if (*(arr + search_index) > key) {

            return interpolation_search(arr, key, low, search_index - 1);
        }
        // 배열의 시작주소 + search_index를 역참조한 값이 key와 작다면? -> low의 값을 search_index + 1 (해당 주소값보다 1높은 주소에 위치한 주소)로 두고 다시 돌림
        else if (*(arr + search_index) < key) {

            return interpolation_search(arr, key, search_index + 1, high);
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

    printf("----------------------------------------------------------------------------\n");
    printf("검색기능을 수행해봅니다. 배열 크기에 해당하는 값을 입력하면,\n 배열의 값은 각 배열의 index + a(1~5) 에 대응하는 값으로 입력됩니다.");
    printf("----------------------------------------------------------------------------\n\n");

    printf("검색의 대상이 되는 배열의 크기를 입력하세요 (0이외의 값을 좀 부탁드려용~) : ");
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

    printf("\n\n값 입력이 완료되었습니다.\n");
    printf("hint : 가장 작은 값 = %d, 가장 높은 값 = %d)\n\n", *(array_address), *(array_address + array_num - 1));

    while (1) {

        // 검색할 값
        int search_value = 0;

        printf("이거다 싶은 값을 입력 부탁드립니다(%d ~ %d) (0, 범위 밖 입력 = 종료하기) : ", *(array_address), *(array_address + array_num - 1));
        scanf_s("%d", &search_value);

        if (search_value <= 0 || search_value > *(array_address + array_num - 1)) {
            printf("\n(경고!)배열값들의 범위를 넘어선 값입니다. 프로그램이 종료되었습니다.\n");
            exit(0);
        }

        // 보간 검색 실행 (-1 이외의 값이 나옴 = 해당 배열 내에 값이 존재)
        int result = interpolation_search(array_address, search_value, 0, array_num - 1);

        if (result != -1) {

            // (검색 값의 위치) interpolation_search ( 검색 배열, 검색 값, 낮은 범위 칸, 최대 범위 칸 )
            printf(" ->> (성공) 보간 탐색 : 검색값 [%d]는 해당배열의 %d번째 공간에 위치합니다.\n", search_value, result + 1);

        }
        else {

            printf(" ->> [%d]는 보간 탐색 실패\n", search_value);
        }
        printf("\n");
    }

    return 0;

}
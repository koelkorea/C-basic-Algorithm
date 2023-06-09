// 힙(Heap)
//  : 이진트리 구조를 쓰지만.. 목적은 여러 개의 데이터 값에서 '최대값', '최소값'을 빠르게 찾아내도록 만들어진 자료 구조 
//    -> 결론부터 말하면, 루트는 최대값 or 최소값이고, 최대힙 최소힙에 따라 부모가 자식보다 무조건 크거나 작은 구조를 유지하면 그만인 일종의 야매(?) 이진트리
//       -> 하지만 미리 기존 자료를 힙구조로 재구성하는 과정을 거쳐야.. 그 이점을 제대로 누릴수 있음 (= heapify 한다고 함)

//  # (중요) 왜 이진검색트리가 있는데? 또 다른 방식의 이진트리 자료구조인 힙 구조를 배워야 하나?
//    : 이진검색트리의 상위호환이나 다름없는게 힙 구조이기 때문이다..
//      (= 단도직입적으로 힙 구조는 완전이진트리의 모양을 보장하기에, 배열의 index를 따라가도 이진트리 어디에 위치하는지 예측, 관리가 쉬움 = 배열을 바로 heapify를 하면 원하는 heap구조로 자료정렬이 쌉가능하다) 
//       1. 범용성으로 보나 효율성으로 보나, 자료구성의 난이도로 보나 힙 구조가 더 쉽고 효율적
//       2. 검색에 필요한 시간복잡도는 o(log(2)⁡n), 정렬에 필요한 시간 복잡도도 o(n * log(2)⁡n)으로 사실상 최대 성능도 차이가 없기 때문... 
//          -> 근데 heap은 언제나 이 성능을 보장한다는 사실이 중요함..!
// 
//   # 이진검색트리 vs heap 구조 비교
//      1. 이진검색트리 (불편... 완진이진트리 보장X = 성능보장X)
//        - 처음부터 끝까지 이진검색트리의 구조대로 자료를 input해야 한다는 번거로움이 존재 
//        - 그러면서 처음에 들어간 값이 루트가 되는데, 그 값이 배열의 중위값이지 않으면 막상 구성된 이진검색트리의 모양이 완전이진트리의 모양을 보장하지 못함
//          (= 기껏 구성했는데 검색 시간복잡도 o(log(2)⁡n), 정렬에 시간 복잡도 o(n * log(2)⁡n)를 보장할 수 없음을 의미.. )
//             -> 심지어 재수가 없어 이진트리로 나눠지지 않고 세로로 쭉 나열되어 '데이터 수 - 1' = '레벨수'가 되어버리면? 타 정렬법이나 검색구조랑 차이가 없게됨
// 
//      2. heap 구조
//        - 구조 자체가 이해가 쉬움 (루트가 가장 크거나 작거나 + 부모가 자식보다 항상 크거나 작거나)
//        - 언제나 완전이진트리 구조를 보장
//          (= 검색에 필요한 시간복잡도는 o(log(2)⁡n), 정렬에 필요한 시간 복잡도도 o(n * log(2)⁡n)를 항상 보장할 수 있는 성능의 신뢰성이 더 좋음)
//        - 그러면서 무작위로 정렬되어 이미 존재하는 데이터집합(배열, linked list 전부 상관없음)도 힙구조로 쉽게 재구성이 가능한 방법론이 존재함
//          (= heapify 한다고 함, shiftup, shiftDown의 방법론이 있음)
//        - 완전이진트리 보장 + 무작위 배열도 heapify가 가능함
//          (= tree나 linked list방식이 아닌 일반 배열의 index를 따라가더라도, 이진트리 어디에 위치하는지 예측, 관리가 쉽기에 코드를 짜기 더 쉬움)
//             -> (중요) 그래서 완전이진트리 노드index 공식을 잘 외우자
//                   -> '왼쪽노드 index'   = 현재 index * 2 
//                      '오른쪽노드 index' = 현재 index * 2 + 1
//                      '부모노드 index'   = 현재 index / 2
//  
//  # heapify
//    : 어떤 이진트리를 힙 자료구조형으로 재구성하는 과정(= 방법론 : shift)을 의미
//       -> 보통 shiftDown을 많이 씀.. 상대적으로 리프노드를 첫시작에서 제외할 수 있기 때문에 시작점 = size / 2로 시간효율성에 도움을 주기 때문

//  # shift
//    : 루트노드 or 리프노드부터 힙구조 안의 데이터간의 서열정리로 자리를 바꿔 현상을 의미하며, 이를 통해 최종적으로 heapify를 달성하는 방법론 
//       -> shiftup   : 리프노드부터 상위노드를 향해 비교 & 교환(shift up)하여 자기 자리를 정함으로서 힙구조를 재정립
//       -> shiftDown : 루트노드부터 하위노드를 향해 비교 & 교환(shift up)하여 자기 자리를 정함으로서 힙구조를 재정립

//  # 힙 구조 특징
//    1. (중요!) 완전이진트리 기반으로 구성
//       -> 따라서 노드의 자식은 최대 2개까지 가짐
//       -> 이진트리 기반 시간복잡도 : o(log(2)⁡n)
//       -> 마지막 레벨을 제외한 모든 레벨은 노드로 가득 차야 함
//    2. 중복값이 허용 = 어떤 곳에서 쩌리인 값이 다른 곳에서는 상위레벨에 위치하는거도 가능
//    3. 노드를 채울 때는 순차적으로 채우고, 그 뒤 힙구조의 shift를 시작
//       -> shift는 노드 삭제에 따른 나머지 값들의 서열정리 정도로 이해하면 됨 (= 그 나머지 애들이 새로운 힙구조에 맞게 변화함)
//    4. 형제간의 shift 연산의 우선순위는 고려되지 않음

//  # 힙 구조 종류 
//    1. 최대 힙(Max Heap)
//       : 부모노드의 값이 자식노드의 값보다 항상 크거나 같은 이진트리 (= 루트노드의 값은 최대값)
//         (= 부모노드 key >= 왼쪽 or 오른쪽 자식노드)

//    2. 최소 힙(Min Heap)
//       : 부모노드의 값이 자식 노드의 값보다 항상 작거나 같은 이진 트리 (= 루트노드의 값은 최소값)
//         (= 부모노드 key <= 왼쪽 or 오른쪽 자식노드)

//  # 힙 연산 종류
//    1. 힙 삽입 연산
//       : 새로운 노드를 힙의 마지막 노드에 삽입 후, shiftup(= 힙의 재정렬, 힙의 성질 복원)을 통해 해당 데이터가 포함된 힙 구조를 최소힙, 최대힙 시스템에 맞게 정렬시키는 행위
//         -> 과정1) 새로운 노드를 히프의 마지막 노드에 이어서 삽입(완전 이진트리 룰 지키기)
//            과정2) shiftup = 삽입 후에 새로운 노드를 부모 노드들과 비교 & 교환(shift up)하여, 힙구조에 맞게 데이터를 재정렬시키기 (= 새로운 도전자의 서열을 정함)

//       - shiftup 
//         : 힙 삽입 연산의 과정2를 의미하는 단어로.. 가장 아래 레벨에 위치한 노드가 상위 노드들과 순차적 비교를 통해, 자기 자리를 위로 옮긴다는 개념에 가까움.. 

//    2. 힙 삭제 연산
//       : 가장 큰 값을 가진 노드(Root)를 삭제하는 행위, shiftDown(= 힙의 재정렬, 힙의 성질 복원)을 통해 해당 데이터가 없어진 힙 구조를 최소힙, 최대힙 시스템에 맞게 정렬시키는 행위
//         -> 과정1) 최대값 or 최소값인 Root 노드를 삭제한다
//            과정2) 기존의 마지막 노드를 Root 노드로 이동함
//            과정3) shiftDown = Root부터 leaf까지 경로에 있는 노드와 비교& 교환(shiftDown)하여, 힙구조에 맞게 데이터를 재정렬시키기 (= 새로운 챔피언과 그 아래의 서열을 정리함)

//       - shiftDown 
//         : 힙 삭제 연산 중 과정3을 의미하는 단어로.. 루트노드를 하위 노드들과 순차적 비교를 통해, 자기 자리를 서서히 아래로 옮겨서 자리를 정한다는 개념에 가까움.. 


// (중요) 힙 정렬(Heap Sort) <-> heapify
//  : 이미 heapify된 최대 힙(Max Heap), 최소 힙(Min Heap) 구조의 데이터의 힙 삭제 연산을 통해, 힙 구조의 데이터들을 '오름차순' or '내림차순' 으로 정렬하여 출력하는 방법론을 의미함
//    (= 1번에 1개씩 요소 삭제 + 출력을 반복 -> 데이터의 최대, 최소 값을 순차적으로 저장하여 정렬을 구성)
// 
//   # 힙 정렬(Heap Sort)의 시간복잡도 = o(n * log(2)⁡n)
//      : 기존의 최대/최소값 루트 제거 후, 이를 heapifiy하여 재구성하는 시간 o(log(2)⁡n)
//         -> 이런 삭제 + heapifiy를 힙구조의 데이터 수인 n번 반복


// 동적 배열을 통해 힙 정렬 구성 모범 코드
#include <stdio.h>
#include <stdlib.h>

// heapify시 파라미터로 최대힙 최소힙 선택을 위한 용도
#define MAX_HEAP 0
#define MIN_HEAP 1

typedef int element;

// 힙 자료구조 구조체
typedef struct Heap {

    // 배열의 최대용량
    int capacity;

    // 힙 배열의 현재 데이터 수
    int size;

    // 실제 힙구조 안의 데이터들을 힙구조에 맞는 순번으로 저장하는 동적 배열 (linked list로도 가능하며, 이걸로 만드는게 좀 더 맞는 의미일지도)
    element* array;

}Heap;

// -------------------------------------------------힙 정렬 ADT 리스트----------------------------------------------------------------
element heapTop(Heap* heap);

// 힙에 들어가 있는 현재 데이터의 수 출력
int heapSize(Heap* heap);

//=========(중요!) (핵심!) [heapify의 방법인 shift의 내용을 이행하기 위한 메서드들]======================

// (shift에 필요)최대힙이냐? 최소힙이냐?에 따라 각기 다른 비교할 두 수의 교환조건을 출력
int compare(int a, int b, int isMinHeap);

// 리프노드 중 가장 뒤의 노드가 루드노드를 향해서 상위노드와 값 비교 후, 값 교환하는 shiftUp 구현
// -> 최대힙, 최소힙에 따라 교환조건이 다름 <- compare의 존재 이유
// -> 현재 힙의 데이터의 갯수(size)가 파라미터로 들어가는 이유는 괜히 없는 노드랑 값교환을 하는걸 통제해야 하기 때문
void shiftDown(element* arr, int index, int size, int isMinHeap);

// 리프노드 중 가장 뒤의 노드가 루드노드를 향해서 상위노드와 값 비교 후, 값 교환하는 shiftUp 구현
// -> 최대힙, 최소힙에 따라 교환조건이 다름 <- compare의 존재 이유
void shiftUp(element* arr, int index, int isMinHeap);

//========================================================================================================

// shift를 이용해 존재하는 데이터그룹을 힙 구조가 적용된 이진트리 형식으로 재구성하는 메서드
void heapify(element* arr, int size, int isMinHeap);

// heap구조체를 초기화시킴(배열arr를 heap구조체의 멤버변수로서 연결된 배열주소를 시작으로 복사 후, 최소/최대힙에 따라 heapifty)
void heapInitialize(Heap* heap, element* arr, int size, int isMinHeap);

// heap에 데이터를 추가
void heapAdd(Heap* heap, element value, int isMinHeap);

// heap에 데이터를 삭제 후, 삭제한 데이터를 출력 (shiftDown을 통해 후
element heapRemove(Heap* heap, int isMinHeap);

void heapDisplay(const Heap* heap);

// (중요) heapify가 완료된 상태의 힙배열을 이용, 데이터를 오른차순, 내림차순으로 정렬하는 힙정렬 메서드
void heapSort(element* arr, int size, int cmp);

// 동적배열의 값을 순차적으로 출력 -> 힙정렬 완료된 배열을 출력하여 진짜 내림차순/올림차순인지 확인할 용도
void arrDisplay(element* arr, int size);

void heap_free(Heap* heap);
//------------------------------------------------------------------------------------------------------------------------------------

// 파라미터로 넣은 힙의 루트 노드 주소위치를 출력하는 메서드
element heapTop(Heap* heap) {
    return heap->array[0];
}

// 현재 힙을 이루는 데이터의 갯수를 출력하는 메서드
int heapSize(Heap* heap) {
    return heap->size;
}


// 현재 힙구조가 최소힙 구조인지 여부 판단 (0이면 거짓, 1이면 참)
int isMinHeap(element* arr, int size) {

    int left, right;

    for (int parent = 0; parent < (size / 2); parent++) {

        left = parent * 2 + 1;
        right = left + 1;

        // 순차적으로 노드를 부모노드로 잡고 그 값과 자신의 자식들인 왼쪽노드의 값이나 오른노드의 값이 그 자신보다 하나라도 작다면, 0(최대힙 아님) 출력) 
        if ((left < size && arr[parent] > arr[left]) || (right < size && arr[parent] > arr[right])) {
            return 0;
        }
    }

    return 1;
}

// 현재 힙구조가 최대힙 구조인지 여부 판단 (0이면 거짓, 1이면 참)
int isMaxHeap(element* arr, int size) {

    int left, right;

    for (int parent = 0; parent < (size / 2); parent++) {

        left = parent * 2 + 1;
        right = left + 1;

        // 순차적으로 노드를 부모노드로 잡고 그 값과 자신의 자식들인 왼쪽노드의 값이나 오른노드의 값이 그 자신보다 하나라도 크다면, 0(최대힙 아님) 출력) 
        if ((left < size && arr[parent] < arr[left]) || (right < size && arr[parent] < arr[right])) {
            return 0;
        }
    }
    return 1;
}

//=========(중요!) (핵심!) [heapify의 방법인 shift의 내용을 이행하기 위한 메서드들]======================

// 힙 안의 두개의 데이터를 어떻게 비교할지에 대해 말하는 메서드
//  -> 해당 힙이 최소힙이면, a > b가 참인지 여부를 출력
//     해당 힙이 최대힙이면, a < b가 참인지 여부를 출력
int compare(int a, int b, int isMinHeap) {

    // MIN_HEAP 최소 힙
    if (isMinHeap == 1) {
        return a > b;
    }
    // MAX_HEAP 최대 힙
    else if (isMinHeap == 0) {
        return a < b;
    }
    else {
        return -1;
    }
}

// 리프노드 중 가장 뒤의 노드가 루드노드를 향해서 상위노드와 값 비교 후, 값 교환하는 shiftUp 구현
// -> 최대힙, 최소힙에 따라 교환조건이 다름 <- compare의 존재 이유
void shiftUp(element* arr, int heap_node, int isMinHeap) {

    // 부모의 인덱스 계산식 (= 루트의 주소가 0이기에 다음과 같이 계산)
    int parent = (heap_node - 1) / 2;

    element temp;

    // 부모 노드 존재, 재귀 종점
    if (parent >= 0) {

        // 파라미터로 들어간 노드(= 자식 노드)를 기준으로 그 자신의 부모 노드와 비교(최대힙, 최소힙에 따라 비교식이 바뀜)한게 참이면?
        //  -> 부모의 값과 파라미터로 들어간 노드(= 자식 노드)의 값을 바꿔줌
        //     -> 그리고 그 녀석이 질때까지 똑같이 재귀를 통해 shiftup 계속함
        if (compare(arr[parent], arr[heap_node], isMinHeap)) {

            temp = arr[parent];
            arr[parent] = arr[heap_node];
            arr[heap_node] = temp;

            // root 노드까지 비교 & 교환 (재귀호출)
            // (= 정확히는 질때까지 계속 랭킹 올리는 서열정리 도전을 하게 함)
            shiftUp(arr, parent, isMinHeap);
        }
    }
}

// (best 중요!) 리프노드 중 가장 뒤의 노드가 루드노드를 향해서 상위노드와 값 비교 후, 값 교환하는 shiftUp 구현
// -> 최대힙, 최소힙에 따라 교환조건이 다름 <- compare의 존재 이유
// -> 현재 힙의 데이터의 갯수(size)가 파라미터로 들어가는 이유는 괜히 없는 노드랑 값교환을 하는걸 통제해야 하기 때문
void shiftDown(element* arr, int parent, int size, int isMinHeap) {

    // 현재 배열값 기준 왼쪽 자식의 배열 인덱스
    int left_node = 2 * parent + 1;

    // 현재 배열값 기준 오른쪽 자식의 배열 인덱스 (int r = 2 * parent + 2)
    int right_node = left_node + 1;

    // left, right중 교환대상으로 선정된 인덱스를 저장할 변수 (초기화는 인덱스로 사용할 수 없는 값 -1로 정함)
    int cmpr = -1;

    // 값 교환 자체를 위한 임시변수
    element temp;

    // 일단, 왼쪽 값을 교환 대상으로 설정 (= 어쨌든 완전이진트리라 최하위 레벨 아닌이상 자식은 다 2개씩)
    if (left_node < size) {
        cmpr = left_node;
    }

    // 오른쪽 인덱스 존재 하며, 오른쪽 자식이 더 크거나 작으면 교환 대상 변경
    if (right_node < size && compare(arr[left_node], arr[right_node], isMinHeap)) {
        cmpr = right_node;
    }

    // 정해진 교환 대상의 인덱스가 존재하고, arr[교환대상 index]가 더 크거나 작으면, 
    //  -> 파라미터로 들어간 노드(= 자식 노드)의 값과 자식노드의 값을 바꿔줌
    //     -> 그리고 그 녀석이 이길 때까지 똑같이 재귀를 통해 shiftDown 계속함
    if (cmpr != -1 && compare(arr[parent], arr[cmpr], isMinHeap)) {

        temp = arr[parent];
        arr[parent] = arr[cmpr];
        arr[cmpr] = temp;

        // 교환이 완료된 시점의 값과 인덱스를 부모로 두고, 자식이 없는 노드까지 비교 & 교환 (재귀호출)
        // (= 정확히는 이길때까지 계속 랭킹 올리는 서열정리 도전을 하게 함)
        shiftDown(arr, cmpr, size, isMinHeap);
    }
}

//========================================================================================================

// (heapInitialize의 부분함수) 목표한 데이터집합(= 여기서는 배열)을 최대힙 or 최소힙에 맞는 구조로 정렬시켜 줌
void heapify(element* arr, int size, int isMinHeap) {

    // (중요) heapify시 shiftdown은 자기 밑에 리프노드들이 있는 노드들을 시작으로 ~ 리프노드의 순으로 행할 수 있도록 함
    // ex) 힙 데이터가 8개면... 리프노드는 레벨2 = 5, 6, 7   레벨3 = 8이다.. 따라서 4번부터 자기 자식이자 리프노드인 8번을 대상으로 shift 다운을 시작.. 
    //     -> 사실 데이터의 갯수대로 반복해줘도 되긴함.. i = size / 2로 시작하는건 단지 효율을 위한 방식일 뿐
    for (int i = size / 2; i >= 0; i--) {
        shiftDown(arr, i, size, isMinHeap);
    }
}

// (중요) heap 구조를 초기화 (배열arr를 heap구조체의 멤버변수로서 연결된 배열주소를 시작으로 복사 후, 최소/최대힙에 따라 heapifty)
//  -> 과정1) 힙구조로 재구성을 원하는 배열 arr[] 값들을 heap 구조체의 멤버변수로서 동적할당된 동적배열 array에 복사
//     과정2) 그 동적배열에 메서드 heapify를 사용해서 array의 값들을 최대힙 or 최소힙에 맞는 구조로 정렬시켜줌
void heapInitialize(Heap* heap, element* arr, int size, int isMinHeap) {

    // ------------------------------------(과정1)---------------------------------------------

    // capacity 멤버 변수 초기화 (원하는 size의 2배를 최대용량으로)
    heap->capacity = size * 2;

    // size 멤버 변수 초기화
    heap->size = size;

    // array 멤버 동적 할당
    heap->array = (int*)calloc(heap->capacity, sizeof(element));

    // array 원본 복사
    for (int i = 0; i < size; i++) {
        heap->array[i] = arr[i];
    }

    // ------------------------------------(과정2)---------------------------------------------

    // 복사한 배열을 heap의 특징(= 최소힙, 최대힙 구조에 맞게) 갖추도록 재배열하기 
    heapify(heap->array, size, isMinHeap);
}

// 해당 힙의 데이터를 root 부터 순차적으로 출력, BFS(너비우선탐색)식으로 레벨별 노드를 순차적으로..
void heapDisplay(const Heap* heap) {

    for (int i = 0; i < heap->size; i++) {
        printf("%5d ", heap->array[i]);
    }
    printf("\n");
}


// 힙에 새로운 데이터를 추가하는 함수 (shiftUp이 도중에 같이 실행)
void heapAdd(Heap* heap, element value, int isMinHeap) {

    // heap 원소의 수가 총 용량과 같아지면 추가 불가능하도록 조치
    if (heap->size == heap->capacity) {
        printf("\n\n\t\theap overflow\n");
        return;
    }

    // 새로운 노드를 히프의 마지막 노드에 이어서 삽입 (완전 이진트리 구조 지키기)
    heap->array[heap->size] = value;

    // 현재 heap 구조를 이루는 데이터의 수가 1 증가
    heap->size++;

    // 새로운 도전자 노드를 부모 노드들과 비교 & 교환하는 서열정리 시작 (shift up)
    shiftUp(heap->array, heap->size - 1, isMinHeap);
}

// heap 삭제 연산 (= 대상 힙의 루트 노드 삭제 -> 이후 막내노드 그 자리로 불러서, shiftDown을 통한 힙구조 재정렬)
element heapRemove(Heap* heap, int isMinHeap) {

    //root 노드 반환을 위해 임시 저장
    element temp = heap->array[0];

    //마지막 노드의 값 = 루트값
    heap->array[0] = heap->array[heap->size - 1];

    // heap 원소의 수 1 감소
    heap->size--;

    // 대상 힙의 루트로 올라온 마지막노드의 값을 shiftDown시켜 환경변화에 따른 힙 구조 서열 다시 정리
    shiftDown(heap->array, 0, heap->size, isMinHeap);

    //부모 노드를 기준으로 자식 노드와 비교 후 자식 노드 값이 더 크거나 작으면 교환
    return temp; // root 노드 반환
}


// 힙 구조를 위해 할당한 메모리를 해제하는 메서드
void heap_free(Heap* heap) {

    free(heap->array);
    printf("Heap 할당 해제\n");
}

// (중요) heapify가 완료된 상태의 힙배열을 이용, 데이터를 오른차순, 내림차순으로 정렬하는 힙정렬 메서드
void heapSort(element* arr, int size, int isMinHeap) {

    Heap heap;

    // 복사본 최소 or 최대 힙 초기화하여 생성
    heapInitialize(&heap, arr, size, isMinHeap);

    // 힙 삭제를 한 루트노드의 값을 원본 배열에 순차적으로 저장 (= 이렇게 힙 데이터를 정렬된 데이터화)
    for (int i = 0; i < size; i++) {
        arr[i] = heapRemove(&heap, isMinHeap);
    }

    // 모든 힙의 데이터를 힙삭제하고 나면 힙을 위해 할당한 메모리를 해제한다
    heap_free(&heap);
}

// 동적배열의 값을 순차적으로 출력 -> 힙정렬 완료된 배열을 출력하여 진짜 내림차순/올림차순인지 확인할 용도
void arrDisplay(element* arr, int size) {

    for (int i = 0; i < size; i++) {
        printf("%5d ", arr[i]);
    }

    printf("\n");
}

// ------------------------------------------------[힙 구조에서 k번째로 작은 데이터값을 꺼내는 방법]--------------------------------------------

// 방법1) 힙정렬을 통해 오름차순으로 자료가 입력된 배열에서 k번째의 값을 꺼내는 것
//  -> 시간복잡도 : O(N log N)
element kthSmallest(element* arr, int size, int k) { //방법1 : 

    heapSort(arr, size, MIN_HEAP); //최소힙 정렬 후

    return arr[k - 1]; //리턴
}

// 방법2) 힙 구조 안에서 직접 힙 삭제를 k번 하여 k번째의 값을 꺼내는 것
//  -> 시간복잡도 : O(K log N)
element kthSmallest2(int* arr, int size, int k) {

    int i = 0;
    element value = 0;
    Heap heap;

    // 기존 배열을 기반으로 heap과 연결된 배열을 최소힙 구조로 만든다
    heapInitialize(&heap, arr, size, MIN_HEAP);

    // 최소값을 value에 k번 대입 (덮어쓰기)
    while (i < k && i < size) {
        value = heapRemove(&heap, MIN_HEAP);
        ++i;
    }

    // 모든 힙의 데이터를 힙삭제하고 나면 힙을 위해 할당한 메모리를 해제한다
    heap_free(&heap);

    return value;
}

int main() {

    // (방법1 실험) 기존 배열의 힙 구조 입력 기능 실험을 위한 배열 데이터
    element arr[] = { 12, 15, 21, 6, 30, 3, 24, 27, 9, 18 };
    int num;
    Heap heap;//원본 복사 & 정렬 결과 저장 힙

    printf("원본 배열 : ");
    arrDisplay(arr, sizeof(arr) / sizeof(element));

    // [힙 구조 생성방법]
    //  : 기존배열을 힙 자료구조 형식으로 이식하기
    //    -> 원본배열을 복사하여 Max heap 구성으로 초기화 
    heapInitialize(&heap, arr, sizeof(arr) / sizeof(element), MAX_HEAP);

    printf("Max Heap  : ");
    heapDisplay(&heap);

    // 최대힙 구성의 힙배열 -> 최소힙 구성의 힙배열로 heapify
    heapify(heap.array, heap.size, MIN_HEAP);

    printf("Min Heap  : ");
    heapDisplay(&heap);

    // 힙 구조를 이루는 데이터를 이용하여 힙정렬 하기
    //  -> 최대힙 : 내림차순 ㅇ
    //  -> 최소힙 : 오름차순
    heapSort(heap.array, sizeof(arr) / sizeof(element), MAX_HEAP);

    printf("Heap Sort : ");
    heapDisplay(&heap);

    // 힙 구조를 이루는 데이터를 이용하여 힙정렬 하기
    //  -> 최대힙 : 내림차순 
    //  -> 최소힙 : 오름차순 ㅇ
    heapSort(heap.array, sizeof(arr) / sizeof(element), MIN_HEAP);

    printf("Heap Sort : ");
    heapDisplay(&heap);

    // 최소힙 구성의 힙배열 -> 최대힙 구성의 힙배열로 heapify
    heapify(heap.array, heap.size, MAX_HEAP);

    printf("Heap      : ");
    heapDisplay(&heap);

    if (isMinHeap(heap.array, sizeof(arr) / sizeof(element))) {
        printf("최소힙 입니다.\n");
    }
    else {
        printf("최소힙이 아닙니다.\n");
    }

    if (isMaxHeap(heap.array, sizeof(arr) / sizeof(element))) {
        printf("최대힙 입니다.\n");
    }
    else {
        printf("최대힙이 아닙니다.\n");
    }

    do {

        printf("몇 번째로 작은 값을 찾으시겠습니까? ");
        scanf_s("%d", &num);

    } while (num < 0 || num > sizeof(arr) / sizeof(element));

    // ------------------------------------------------[힙 구조에서 k번째로 작은 데이터값을 꺼내는 방법]--------------------------------------------

    // 방법1) 힙정렬을 통해 오름차순으로 자료가 입력된 배열에서 k번째의 값을 꺼내는 것
    printf("kthSmallest  %d번째로 작은 값은 %d입니다.\n", num, kthSmallest(heap.array, sizeof(arr) / sizeof(element), num));

    // 방법2) 힙 구조 안에서 직접 힙 삭제를 k번 하여 k번째의 값을 꺼내는 것
    printf("kthSmallest2 %d번째로 작은 값은 %d입니다.\n", num, kthSmallest2(heap.array, sizeof(arr) / sizeof(element), num));

    heap_free(&heap);

    return 0;
}

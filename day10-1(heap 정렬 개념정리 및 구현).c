// 힙(Heap)
//  : 이진트리 구조를 쓰지만.. 목적은 여러 개의 데이터 값에서 '최대값', '최소값'을 빠르게 찾아내도록 만들어진 자료 구조 
//    -> 결론부터 말하면, 루트는 최대값 or 최소값이고, 최대힙 최소힙에 따라 부모가 자식보다 무조건 크거나 작은 구조를 유지하면 그만인 일종의 야매(?) 이진트리

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


// 힙 정렬(Heap Sort)
//  : 최대 힙(Max Heap), 최소 힙(Min Heap) 구조의 데이터를 이용, 힙 삭제 연산을 통해 정렬된 데이터를 입력 및 출력하는 것
//    (= 1번에 1개씩 요소 삭제 + 출력을 반복 -> 데이터의 최대, 최소 값을 순차적으로 저장하여 정렬을 구성)
//     -> 기존의 최대/최소값 루트 제거 후 이를 큐에서 pop하듯 빼서 입력... 다시 루트레 최대/최소값을 가지도록 데이터들이 힙을 구성하는데 걸리는 시간복잡도 o(log(2)⁡n).. 그렇게 n개를 삭제 출력 반복
//         -> (결론) 힙 정렬(Heap Sort)시간복잡도 = o(n * log(2)⁡n)


// 동적 배열을 통해 힙 정렬 구성 모범 코드
#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP 0
#define MIN_HEAP 1

typedef int element;

typedef struct Heap {
    int capacity;       // 배열의 최대용량
    int size;           // 배열의 원소 수
    element* array;     // 힙을 저장하는 배열
}Heap;

// -------------------------------------------------힙 정렬 ADT 리스트----------------------------------------------------------------
element heapTop(Heap* heap);
int heapSize(Heap* heap);
void shiftDown(element* arr, int index, int size, int isMinHeap);
void heapify(element* arr, int size, int isMinHeap);
void heapInitialize(Heap* heap, element* arr, int size, int isMinHeap);
void heap_free(Heap* heap);
void heapAdd(Heap* heap, element value, int isMinHeap);
void shiftUp(element* arr, int index, int isMinHeap);
void heapDisplay(const Heap* heap);
element heapRemove(Heap* heap, int isMinHeap);
int compare(int a, int b, int isMinHeap);
void heapSort(element* arr, int size, int cmp);
void arrDisplay(element* arr, int size);
//------------------------------------------------------------------------------------------------------------------------------------

// 파라미터로 넣은 힙의 루트 노드 주소위치를 출력하는 메서드
element heapTop(Heap* heap) { 
    return heap->array[0]; 
} 

// 현재 힙을 이루는 데이터의 갯수를 출력하는 메서드
int heapSize(Heap* heap) {
    return heap->size; 
} 

// (가장 중요한 함수!! 여러 메서드의 부분함수) 목표한 데이터 집합(= 여기서는 동적배열)가 힙구조를 형성하도록, 해당 집합의 요소 heap_node를 shiftDown시켜 자식 노드들과 값 비교 & 교환하는 서열정리 시작
//  -> heap_node는 부모 노드로서, 자신을 기준으로 자식 노드와 비교 후, 힙 종류에 따라 자식 노드 값이 더 크거나 작으면 교환
void shiftDown(element* arr, int parent, int size, int isMinHeap) {

    // 왼쪽 자식 인덱스
    int l = 2 * parent + 1; 

    // 오른쪽 자식 인덱스 (int r = 2 * parent + 2)
    int r = l + 1;      

    // left, right중 교환대상으로 선정된 인덱스를 저장할 변수 (초기화는 인덱스로 사용할 수 없는 값 -1로 정함)
    int cmpr = -1;    

    element temp;

    // 일단, 왼쪽 값을 교환 대상으로 설정 (= 어쨌든 완전이진트리라 최하위 레벨 아닌이상 자식은 다 2개씩)
    if (l < size) {
        cmpr = l; 
    }

    // 오른쪽 인덱스 존재 하며, 오른쪽 자식이 더 크거나 작으면 교환 대상 변경
    if (r < size && compare(arr[l], arr[r], isMinHeap)) {
        cmpr = r;
    }
    
    // 정해진 교환 대상의 인덱스가 존재하고, arr[교환대상 index]가 더 크거나 작으면, 
    //  -> 파라미터로 들어간 노드(= 자식 노드)의 값과 자식노드의 값을 바꿔줌
    //     -> 그리고 그 녀석이 이길 때까지 똑같이 재귀를 통해 shiftDown 계속함
    if (cmpr != -1 && compare(arr[parent], arr[cmpr], isMinHeap)) {

        temp = arr[parent];
        arr[parent] = arr[cmpr];
        arr[cmpr] = temp;

        // 자식이 없는 노드까지 비교 & 교환 (재귀호출)
        // (= 정확히는 이길때까지 계속 랭킹 올리는 서열정리 도전을 하게 함)
        shiftDown(arr, cmpr, size, isMinHeap); 
    }
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

// 목표한 데이터집합(= 여기서는 배열)을 아래부터 루트까지 최대힙 or 최소힙에 맞는 구조로 정렬 = 목표한 데이터집합을 힙으로서 기능하게 하기
void heapify(element* arr, int size, int isMinHeap) {

    for (int i = size / 2; i >= 0; i--) {
        shiftDown(arr, i, size, isMinHeap);
    }
}

// heap 구조를 초기화 (힙구조로 재구성을 원하는 배열 arr[] 값들을 heap 구조체의 멤버변수로서 동적할당된 동적배열 array에 복사하고, 그 동적배열 array의 값들을 최대힙 or 최소힙에 맞는 구조로 정렬시키는 것)
void heapInitialize(Heap* heap, element* arr, int size, int isMinHeap) {

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

    // 복사한 배열을 heap의 특징(= 최소힙, 최대힙 구조에 맞게) 갖추도록 재배열하기 
    heapify(heap->array, size, isMinHeap);             
}

// 힙 구조를 위해 할당한 메모리를 해제하는 메서드
void heap_free(Heap* heap) {

    free(heap->array);
    printf("Heap 할당 해제\n");
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

// (heapAdd의 부분함수) 목표한 데이터 집합(= 여기서는 동적배열)가 힙구조를 형성하도록, 해당 집합의 요소 heap_node를 shiftUp시켜 부모 노드들과 비교 & 교환하는 서열정리 시작
//  -> heap_node는 자식 노드로서, 자신을 기준으로 부모 노드와 비교 후, 힙 종류에 따라 자식 노드 값이 더 크거나 작으면 교환
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

// 해당 힙의 데이터를 root 부터 순차적으로 출력, BFS(너비우선탐색)식으로 레벨별 노드를 순차적으로..
void heapDisplay(const Heap* heap) { 

    for (int i = 0; i < heap->size; i++) {
        printf("%5d ", heap->array[i]);
    }
    printf("\n");
}

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

// 힙 정렬을 통해 채운 배열값 순차적 출력
void arrDisplay(element* arr, int size) {

    for (int i = 0; i < size; i++) {
        printf("%5d ", arr[i]);
    }

    printf("\n");
}

// 최대힙, 최소힙 구조의 힙을 shiftDown 한 뒤, 그 값을 순차적으로 배열에 받아 정렬된 데이터를 얻음
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


element kthSmallest(element* arr, int size, int k) { //방법1 : 시간복잡도 : O(N log N)

    heapSort(arr, size, MIN_HEAP); //최소힙 정렬 후

    return arr[k - 1]; //리턴
}

element kthSmallest2(int* arr, int size, int k) {//방법2 : k번의 삭제 수행 -> 시간복잡도 : O(K log N)

    int i = 0;
    element value = 0;
    Heap heap;

    // 배열을 최소힙으로 만든다
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

// 현재 힙구조가 최소힙 구조인지 여부 판단 (0이면 거짓, 1이면 참)
int isMinHeap(element* arr, int size) {

    int l, r;

    for (int parent = 0; parent < (size / 2); parent++) {

        l = parent * 2 + 1;
        r = l + 1;

        // 순차적으로 노드를 부모노드로 잡고 그 값과 자신의 자식들인 왼쪽노드의 값이나 오른노드의 값이 그 자신보다 하나라도 작다면, 0(최대힙 아님) 출력) 
        if ((l < size && arr[parent] > arr[l]) || (r < size && arr[parent] > arr[r])) {
            return 0;
        }
    }

    return 1;
}

// 현재 힙구조가 최대힙 구조인지 여부 판단 (0이면 거짓, 1이면 참)
int isMaxHeap(element* arr, int size) {

    int l, r;

    for (int parent = 0; parent < (size / 2); parent++) {

        l = parent * 2 + 1;
        r = l + 1;

        // 순차적으로 노드를 부모노드로 잡고 그 값과 자신의 자식들인 왼쪽노드의 값이나 오른노드의 값이 그 자신보다 하나라도 크다면, 0(최대힙 아님) 출력) 
        if ((l < size && arr[parent] < arr[l]) || (r < size && arr[parent] < arr[r])) {
            return 0;
        }
    }
    return 1;
}
int main() {
    element arr[] = { 12, 15, 21, 6, 30, 3, 24, 27, 9, 18 };
    int num;
    Heap heap;//원본 복사 & 정렬 결과 저장 힙

    printf("원본 배열 : ");
    arrDisplay(arr, sizeof(arr) / sizeof(element));

    // 원본배열을 복사하여 Max heap 구성으로 초기화 
    heapInitialize(&heap, arr, sizeof(arr) / sizeof(element), MAX_HEAP); 
    printf("Max Heap  : ");
    heapDisplay(&heap);

    heapify(heap.array, heap.size, MIN_HEAP);
    printf("Min Heap  : ");
    heapDisplay(&heap);

    heapSort(heap.array, sizeof(arr) / sizeof(element), MAX_HEAP);
    printf("Heap Sort : ");
    heapDisplay(&heap);

    heapSort(heap.array, sizeof(arr) / sizeof(element), MIN_HEAP);
    printf("Heap Sort : ");
    heapDisplay(&heap);

    heapify(heap.array, heap.size, MAX_HEAP); //최대 힙
    //heapify(heap.array, heap.size, MIN_HEAP); //최소 힙
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

    printf("kthSmallest  %d번째로 작은 값은 %d입니다.\n", num, kthSmallest(heap.array, sizeof(arr) / sizeof(element), num));
    printf("kthSmallest2 %d번째로 작은 값은 %d입니다.\n", num, kthSmallest2(heap.array, sizeof(arr) / sizeof(element), num));

    heap_free(&heap);

    return 0;
}


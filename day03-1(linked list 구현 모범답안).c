// [모범답안] 연결 리스트 ADT (나 와의 차이점)
//  1. 2중 포인터변수 적극 활용
//     - &포인터변수 까지도 사용함
//     - freelist구현시 파라미터에 ListNode** head를 투입
//  2. 해당 연결리스트를 요소값의 오름차순으로 연결시켜주는 ListSort를 요소값만 순차정렬 알고리즘 사용해서 값을 교환해 해결
//  3.  

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(type,a,b) {type t=a;a=b;b=t;}

typedef int list_element;
typedef struct ListNode {
    
    list_element data;
    struct ListNode* link;
} ListNode;

// 노드 맨 앞 생성
ListNode* insert_first(ListNode* head, list_element value);

// 노드 맨 뒤 생성
ListNode* insert_last(ListNode* head, list_element value);

// 노드 정렬 생성
ListNode* insert_sort(ListNode* head, list_element value);

// 노드 맨 앞 삭제
ListNode* delete_first(ListNode* head);

// 노드 맨 뒤 삭제
ListNode* delete_last(ListNode* head);

// 노드 검색 삭제
// 반환 값 = 삭제 성공 : 0, 삭제 실패 : -1
// 매개변수 ListNode** head = List Head의 주소
// 매개변수 list_element value = 삭제 요소
int delete_search(ListNode** head, list_element value);

// 노드 검색
ListNode* search(ListNode* head, list_element x);

// 리스트 결합 head1 + head2
ListNode* concat(ListNode* head1, ListNode* head2);

// 리스트 역순 연결
ListNode* reverse(ListNode* head);

// 노드 정렬
ListNode* ListSort(ListNode* head);

// 리스트 출력
void print_list(ListNode* head);

// 리스트 메모리 해제
// 매개변수 ListNode** head = List Head의 주소
void freelist(ListNode** head);

int main() {

    srand((unsigned)time(NULL));
    ListNode* list_head1 = NULL, * list_head2 = NULL;

    for (int i = 0; i < 110; i += 10) {
        list_head1 = insert_first(list_head1, i);
        printf("list 1 ");
        print_list(list_head1);
    }
    
    for (int i = 0; i <= 50; i += 20) {
        
        if (delete_search(&list_head1, i) == 0){
            printf("%4d 삭제 성공  ", i);
        }else{
            printf("%4d 삭제 실패  ", i);
        }
        
        printf("list 1 ");
        print_list(list_head1);
    }
    
    for (int i = 0; i < 50; i += 10) {
        list_head2 = insert_sort(list_head2, rand() % 5000);
        printf("list 2 ");
        print_list(list_head2);
    }
    
    for (int i = 0; i < 2; i++) {
        list_head1 = delete_first(list_head1);
        list_head1 = delete_last(list_head1);
        printf("list 1 ");
        print_list(list_head1);
    }
    
    ListNode* concat_list = concat(list_head1, list_head2);
    list_head1 = list_head2 = NULL;
    
    printf("list concat ");  print_list(concat_list);
    
    concat_list = reverse(concat_list);
    printf("list concat ");  print_list(concat_list);
    
    ListNode* p = search(concat_list, 80);
    
    if (p != NULL) {
        printf("탐색 성공 : %d\n", p->data);
    }else {
        printf("탐색 실패\n");
    }
    
    ListSort(concat_list);
    printf("list concat ");  print_list(concat_list);
    
    freelist(&concat_list);
    return 0;
}

// 해당 연결리스트의 1번쨰 노드에 추가 (= 같은 방법 구현)
ListNode* insert_first(ListNode* head, list_element value) {
    
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    
    if (NewNode == NULL) {
        printf("새 노드 동적 할당 실패!\n"), exit(1); 
    }
    
    NewNode->data = value;
    NewNode->link = head;
    
    return NewNode;
}

// 해당 연결리스트의 마지막 노드에 추가 (= 같은 방법 구현)
ListNode* insert_last(ListNode* head, list_element value) {
    
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    
    if (NewNode == NULL) {
        printf("새 노드 동적 할당 실패!\n"), exit(1); 
    }
    
    NewNode->data = value;
    NewNode->link = NULL;
    
    if (head == NULL) {
        head = NewNode; 
        return head;
    }
    
    ListNode* LastNode = head;
    
    while (LastNode->link != NULL){
        LastNode = LastNode->link;
    }
    
    LastNode->link = NewNode;
    
    return head;
}

// 리스트에 item의 값이 노드의 위치상 선택정렬 되도록 알맞은 노드 위치를 선정 후 값 추가 (<-> 케이스를 4개로 나눈 내 방법이랑 다르게 좀 단순화.. 대신 link값이 수시로 바뀌게 됨)
ListNode* insert_sort(ListNode* head, list_element value) {
    
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    
    if (NewNode == NULL) {
        printf("새 노드 동적 할당 실패!\n"), exit(1); 
    }
    
    NewNode->data = value;
    NewNode->link = NULL;
    
    // case1 노드가 없는 경우 (1번쨰 노드행)
    if (head == NULL) {
        return NewNode; // Node 없음
    }
    
    //NewNode 기준 rear : 앞노드, forward : 뒤노드(head가 초기값) 
    ListNode* forward = head, * rear = NULL; 
    
    // 뒷 노드의 주소값이 있으면 계속 진행 
    while (forward != NULL) {
        
        // 도중에 item값보다 큰 노드의 값을 찾으면 거기서 앞노드와 뒷노드를 결정(break문으로 탈출)
        if (forward->data > value){
            break;
        }
        // 어제의 앞노드가 내일의 뒤노드, 어제의 뒤노드 link가 내일의 뒷노드
        rear = forward;
        forward = forward->link;
    }
    
    // case2 새 노드 위치가 맨 앞(= item이 리스트에서 가장 작은 값)
    if (forward == head) { 
        NewNode->link = forward;
        return NewNode;
    }
    // case3 새 노드 위치가 중간, 맨 뒤
    else { 
        NewNode->link = forward; // 이렇게 되면 forward의 주소값이 NULL로 들어올 떄가 존재 (=기존 맨 뒤 값의 link가 NULL)
        rear->link = NewNode; 
    }
    
    return head;
}

// 1번쨰 노드 삭제(= 같은 방법 구현)
ListNode* delete_first(ListNode* head) {

    // Node 없음
    if (head == NULL) {
        return NULL; 
    }

    ListNode* DeleteNode = head;
    head = head->link; // 삭제 노드 다음 주소
    free(DeleteNode);

    return head;
}

// 마지막 노드 삭제 (<-> 노드가 한개만 있을때를 난 상정하지 않음..)
ListNode* delete_last(ListNode* head) {
    
    // Node 없는 경우
    if (head == NULL) {
        return NULL;
    } 
    
    ListNode* DeleteNode = head, * LastNode = NULL;
    
    while (DeleteNode->link != NULL) {
        LastNode = DeleteNode;
        DeleteNode = DeleteNode->link;
    }
    
    // case1. 해당 연결리스트에 Node 2개 이상인 경우
    if (DeleteNode != head) {
        LastNode->link = NULL;
    }
    // case2. 해당 연결리스트에 Node전체 Node 1개 경우 -> 해당 연결리스트의 head까지 삭제...
    else {
        /* DeleteNode == head */ 
        head = NULL; // 
    }
    
    free(DeleteNode);
    
    return head;
}

int delete_search(ListNode** head, list_element value) {

    if (*head == NULL) return 1; // 삭제 실패 (Node 없음)

    ListNode* DeleteNode = *head, * rear = NULL;

    while (DeleteNode != NULL) { // 삭제 노드 찾기
        if (DeleteNode->data == value) break;
        rear = DeleteNode;
        DeleteNode = DeleteNode->link;
    }

    if (DeleteNode != NULL) { // 삭제 노드 발견
        if (DeleteNode == *head) *head = DeleteNode->link;// 삭제 노드 = 맨 앞 노드
        else rear->link = DeleteNode->link; // 삭제 노드 = 중간, 맨 뒤 노드
        free(DeleteNode);
        return 0; // 삭제 성공
    }

    else /* DeleteNode == NULL */ return 1; // 삭제 실패
}

ListNode* search(ListNode* head, list_element item) {
    for (ListNode* pNode = head; pNode != NULL; pNode = pNode->link)
        if (pNode->data == item) return pNode;
    return NULL;
}

ListNode* concat(ListNode* head1, ListNode* head2) {
    if (head1 == NULL) return head2;
    else if (head2 == NULL) return head1;
    else {
        ListNode* pNode = head1;
        while (pNode->link != NULL) pNode = pNode->link;
        pNode->link = head2;
        return head1;
    }
}

ListNode* reverse(ListNode* head) { // 연결 방향 바꾸기
    ListNode* forward = head, * pNode = NULL, * rear = NULL;
    while (forward != NULL) {
        rear = pNode; // rear : 이미 역순으로 변경한 노드
        pNode = forward; // pNode : 역순으로 만들 노드
        forward = forward->link; // forward : 다음 노드
        pNode->link = rear;
    }
    return pNode;
}

ListNode* ListSort(ListNode* head) {
    for (ListNode* SortNode = head; SortNode != NULL; SortNode = SortNode->link) {
        
        for (ListNode* CompareNode = SortNode->link; CompareNode != NULL; CompareNode = CompareNode->link) {
            
            if (SortNode->data > CompareNode->data) {
                swap(list_element, SortNode->data, CompareNode->data);
            }
        }
    }
    return head;
}

void print_list(ListNode* head) {
    printf(" list -> ");
    for (ListNode* pNode = head; pNode != NULL; pNode = pNode->link)
        printf("%4d -> ", pNode->data);
    printf("NULL \n");
}

void freelist(ListNode** head) {
    
    ListNode* DeleteNode = NULL;
    
    while (*head) {
        DeleteNode = *head;
        *head = (*head)->link;
        free(DeleteNode);
    }
    
    *head = NULL;
}

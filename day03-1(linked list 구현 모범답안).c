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
        if (delete_search(&list_head1, i) == 0) printf("%4d 삭제 성공  ", i);
        else printf("%4d 삭제 실패  ", i);
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
    if (p != NULL) printf("탐색 성공 : %d\n", p->data);
    else printf("탐색 실패\n");
    ListSort(concat_list);
    printf("list concat ");  print_list(concat_list);
    freelist(&concat_list);
    return 0;
}

ListNode* insert_first(ListNode* head, list_element value) {
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    if (NewNode == NULL) { printf("새 노드 동적 할당 실패!\n"), exit(1); }
    NewNode->data = value;
    NewNode->link = head;
    return NewNode;
}

ListNode* insert_last(ListNode* head, list_element value) {
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    if (NewNode == NULL) { printf("새 노드 동적 할당 실패!\n"), exit(1); }
    NewNode->data = value;
    NewNode->link = NULL;
    if (head == NULL) { head = NewNode; return head; }
    ListNode* LastNode = head;
    while (LastNode->link != NULL) LastNode = LastNode->link;
    LastNode->link = NewNode;
    return head;
}

ListNode* insert_sort(ListNode* head, list_element value) {
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    if (NewNode == NULL) { printf("새 노드 동적 할당 실패!\n"), exit(1); }
    NewNode->data = value;
    NewNode->link = NULL;
    if (head == NULL) return NewNode; // Node 없음
    ListNode* forward = head, * rear = NULL; //NewNode 기준 앞, 뒤 노드 위치 찾기
    while (forward != NULL) {
        if (forward->data > value)break;
        rear = forward;
        forward = forward->link;
    }
    if (forward == head) { // 새 노드 위치가 맨 앞
        NewNode->link = forward;
        return NewNode;
    }
    else { // 새 노드 위치가 중간, 맨 뒤
        NewNode->link = forward;
        rear->link = NewNode;
    }
    return head;
}

ListNode* delete_first(ListNode* head) {

    if (head == NULL) return NULL; // Node 없음

    ListNode* DeleteNode = head;
    head = head->link; // 삭제 노드 다음 주소
    free(DeleteNode);

    return head;
}

ListNode* delete_last(ListNode* head) {
    if (head == NULL) return NULL; // Node 없음
    ListNode* DeleteNode = head, * LastNode = NULL;
    while (DeleteNode->link != NULL) {
        LastNode = DeleteNode;
        DeleteNode = DeleteNode->link;
    }
    if (DeleteNode != head) LastNode->link = NULL; // Node 2개 이상
    else /* DeleteNode == head */ head = NULL; // 전체 Node 1개 경우
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
            if (SortNode->data > CompareNode->data) swap(list_element, SortNode->data, CompareNode->data);
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

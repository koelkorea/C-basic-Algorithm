// 연결 리스트(Linked List)
//  : 구조체를 한 줄로 연결 시킨 데이터 구조 (= 구조체의 그룹화)
//     -> 데이터와 포인터를 한 쌍으로 가지고 한 줄로 연결된 자료구조

//  # 참고
//   1. 배열 : 같은 자료형의 그룹
//   2. 구조체 : 다양한 자료형의 재정의

//  # list 구조체 (구성 요소)
//     typedef int list_element;

//     typedef struct ListNode {
// 
//         list_element data;           <- 리스트의 값
//         struct ListNode* link;       <- 다음 리스트 요소가 위치한 주소
//     } ListNode;

//  # 연결리스트의 구성요소
//    - 머리(Head) : 연결 리스트에서 첫번째 노드의 주소를 저장한 포인터
//    - 노드(Node) : 연결 리스트의 요소
//    - 값(Value)  : 노드에 저장된 데이터
//    - 연결(Link) : 다른 노드로 연결을 위한 포인터

//  # 연결리스트의 종류
//   1. 단순 연결 리스트(Singly Linked List)
//      : 각 노드의 link에 다음 노드의 주소가 있음. 마지막 노드의 link는 NULL 값.


//   2. 원형 연결 리스트(Circular Linked List)
//      : 각 노드의 link에 다음 노드의 주소가 있다. 마지막 노드의 link는 헤드의 주소값.


//  # 연결 리스트 ADT(Abstract data type(추상적 데이터 유형) = 자료 구조를 어떻게 다룰지, 기능적 측면을 서술하고 구체화 과정)
//    - insert_first(list, item) : 맨 앞에 Node 추가
//    - delete_first(list) 맨 앞에 Node 제거
//    - search(list, item) : item이 list 안에 있는지 확인
//    - concat(list1, list2) : list1과 list2를 연결
//    - reverse(list1) : list1의 요소 전부를 반대로 연결
//    - display(list) : 리스트의 모든 요소를 표시
//    - insert_last(list, item) : 맨 뒤에 Node 추가
//    - delete_lsat(list) 맨 뒤에 Node 제거

// 연결 리스트 ADT 전부 구현해보자
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함

typedef int list_element;

typedef struct ListNode {

    list_element data;
    struct ListNode* link;
} ListNode;

// 맨 앞,뒤 에 Node 추가
ListNode* insert_first(ListNode* head, list_element item);
ListNode* insert_last(ListNode* head, list_element item);

// 맨 앞,뒤 에 Node 삭제
ListNode* delete_first(ListNode* head);
ListNode* delete_lsat(ListNode* head);

// item이 list 안에 있는지 확인
ListNode* search(ListNode* head, list_element item);

// list1과 list2를 연결
ListNode* concat(ListNode* head1, ListNode* head2);

// list1의 요소 전부를 반대로 연결
ListNode* reverse(ListNode* head);

// 리스트의 모든 요소를 표시
void display(ListNode* head);

int main(void) {

    ListNode* head1 = NULL, * head2 = NULL, * head3 = NULL, * head1_2 = NULL;

    ListNode* search_address = NULL;

    for (int i = 100; i > 0; i -= 10) {

        head1 = insert_first(head1, i);
    }
    display(head1);

    for (int i = 100; i > 20; i -= 10) {

        head1 = delete_first(head1);
        display(head1);
    }

    for (int i = 1; i <= 1000; i += 100) {

        head2 = insert_first(head2, i);
    }
    display(head2);

    head1_2 = concat(head1, head2);
    display(head1);

    search_address = search(head1, 100);
    

    return 0;
}

// 맨 앞에 Node 추가(전에 만든 녀석은 뒤로 밀리는 방식)
ListNode* insert_first(ListNode* head, list_element item) {

    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));

    if (Newnode == NULL) {
        printf("메모리 부족");
        return NULL;
    }
    
    Newnode->data = item;
    Newnode->link = head;

    head = Newnode;

    return head;
}

// item이 list 안에 있는지 확인
ListNode* search(ListNode* head, list_element item) {

    ListNode* address = NULL;
    printf_s("\nhead시작.. %d\n", head);

    while(head != NULL){

        if (head->data == item) {

            address = head;
            printf_s("검색한 내용 %d : 메모리주소 %d에 존재", item , address);
            break;
        }
        else {
            head = head->link;
            printf_s("다음주소로.. %d로..\n", head);
        }
    }
    
    return address;
}

// list1과 list2를 연결
ListNode* concat(ListNode* head1, ListNode* head2) {

    printf_s("\nhead1시작.. %d\n", head1);

    while (head1 != NULL) {

        ListNode* head1_original = head1;
        ListNode* temp = head1->link;

        if (temp == NULL) {

            head1 = head2;

            printf_s("head1의 마지막 link값 = %d -> %d(%d)로..\n", head1_original, head1, head2);
            break;
        }

        head1 = temp;

        printf_s("다음주소.. %d -> %d로..\n", head1_original ,head1);
    }

    return head1;
    
}



// 맨 앞의 Node 삭제
ListNode* delete_first(ListNode* head) {

    ListNode* delete = head;

    if (head == NULL) {

        return NULL;
    }

    head = head->link;

    free(delete);

    return head;
}

// 리스트의 모든 요소를 표시
void display(ListNode* head) {

    printf("list 출력 : ");
    while (head) {
        printf("%3d -> ", head->data);
        head = head->link;
    }
    printf("NULL\n");
}
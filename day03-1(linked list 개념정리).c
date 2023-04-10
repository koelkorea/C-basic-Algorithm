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
//    - 머리(Head) : 연결 리스트에서 첫번째 노드의 주소를 저장한 포인터 (= 연결리스트를 시작하려면, 일단 헤드의 주소값에 위치한 값을 역참조해야 함)
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
ListNode* insert_first(ListNode* head, list_element item);   // done
ListNode* insert_last(ListNode* head, list_element item);    // done

// 정렬을 염두에 두고 추가 (이건 단독으로 리스트)
ListNode* insert_sort(ListNode* head, list_element item);

// 맨 앞,뒤 에 Node 삭제
ListNode* delete_first(ListNode* head);                      // done
ListNode* delete_last(ListNode* head);                       // done
int delete_search(ListNode** head, list_element value);      // done

// item이 list 안에 있는지 확인
ListNode* search(ListNode* head, list_element item);         // done

// list1과 list2를 연결
ListNode* concat(ListNode* head1, ListNode* head2);          // done

// list1의 요소 전부를 반대로 연결
ListNode* reverse(ListNode* head);                           // done

// 리스트의 모든 요소를 표시
void display(ListNode* head);                                // done

// 해당 노드포인터의 메모리를 해제하는 함수
void freelist(ListNode* head);


int main(void) {

    srand((unsigned int)time(NULL));

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

    head2 = insert_last(head2, 890916);
    
    display(head2);

    if (delete_search(head2, 890916) == 0) {

        printf("[검색 삭제 성공]\n");
        display(head2);

    }

    // concat (연결) 실행
    head1_2 = concat(head1, head2);
    head1_2 = delete_last(head1_2);
    display(head1_2);

    // reverse (역순) 실행
    head1_2 = reverse(head1_2);
    display(head1_2);

    // search (검색) 실행
    search_address = search(head1_2, 100);

    // insert_sort(정렬 추가) 실행 
    for (int i = 1; i <= 10; i += 1) {

        head3 = insert_sort(head3, rand() % 10);
    }
    display(head3);

    return 0;
}

// 맨 앞에 Node 추가(전에 만든 녀석은 뒤로 밀리는 방식)
ListNode* insert_first(ListNode* head, list_element item) {

    // 새로운 맨 앞의 노드의 데이터를 넣을 주소값이 어딘지 알기 위해, ListNode의 포인트변수의 메모리를 할당함
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));

    // 노드를 만들 공간이 없다면?? 에러 띄우기
    if (Newnode == NULL) {
        printf("메모리 부족");
        return NULL;
    }
    
    // ListNode 포인터변수 Newnode의 메모리 공간이 역참조하는 값이 head, item이 되도록 함
    Newnode->data = item;
    Newnode->link = head;       // head가 NULL이라도 큰 문제없음(= 어차피 현 노드가 마지막이라는 의미가 통용됨)

    // 현재 첫 노드의 주소값을 저장하는 Head의 주소값을 ListNode 포인터변수 Newnode로 갱신
    head = Newnode;

    return head;
}

// 맨 뒤에 Node 추가(전에 만든 녀석은 뒤로 밀리는 방식)
ListNode* insert_last(ListNode* head, list_element item) {

    // 새로운 맨 뒤의 노드의 데이터를 넣을 주소값이 어딘지 알기 위해, ListNode의 포인트변수의 메모리를 할당함
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));
    ListNode* insert_address = head;

    // 노드를 만들 공간이 없다면?? 에러 띄우기
    if (Newnode == NULL) {
        printf("메모리 부족");
        return NULL;
    }

    while (insert_address->link != NULL) {

        printf_s("\n요소값 : %d", insert_address->data);

        insert_address = insert_address->link;

        printf_s(" -> %d\n", insert_address->data);
    }

    insert_address->link = Newnode;

    // ListNode 포인터변수 Newnode의 메모리 공간이 역참조하는 값이 head, item이 되도록 함
    Newnode->data = item;
    Newnode->link = NULL;       

    return head;
}

// 맨 뒤에 Node 추가(전에 만든 녀석은 뒤로 밀리는 방식)
ListNode* insert_sort(ListNode* head, list_element item) {

    // 새로운 맨 뒤의 노드의 데이터를 넣을 주소값이 어딘지 알기 위해, ListNode의 포인트변수의 메모리를 할당함
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));
    ListNode* insert_address = head;
    ListNode* front_link_address = NULL;

    // 노드를 만들 공간이 없다면?? 에러 띄우기
    if (Newnode == NULL) {
        printf("메모리 부족");
        return NULL;
    }

    if (insert_address == NULL) {

        return insert_first(head, item);
    }
    else {

        while (insert_address->link != NULL) {

            if (insert_address->data >= item) {
                printf_s("\n입력값 %d보다 큰 수 %d 감지", item, insert_address->data);
                break;
            }

            printf_s("\n요소값 : %d", insert_address->data);

            front_link_address = insert_address;
            insert_address = insert_address->link;

            printf_s(" -> %d\n", insert_address->data);
        }

        // ListNode 포인터변수 Newnode의 메모리 공간이 역참조하는 값이 head, item이 되도록 함
        Newnode->data = item;
        Newnode->link = front_link_address;

        front_link_address = Newnode;

    }

    return head;
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

// 맨 뒤의 Node 삭제
ListNode* delete_last(ListNode* head) {

    ListNode* delete_address = head;
    ListNode* new_end_address = NULL;

    if (head == NULL) {

        return NULL;
    }

    while (delete_address->link != NULL) {

        printf_s("\n요소값 : %d", delete_address->data);
        new_end_address = delete_address;
        delete_address = delete_address->link;

        printf_s(" -> %d\n", delete_address->data);
    }

    free(delete_address);
    new_end_address->link = NULL;

    return head;
}


// 검색후 찾아서 삭제
int delete_search(ListNode** head, list_element value) {

    if (head == NULL) {

        return 1;
    }

    ListNode* search_address = search(head, value);

    if (search_address == NULL) {

        return 1;
    }

    ListNode* delete_address = head;
    ListNode* new_end_address = NULL;

    while (delete_address->link != search_address) {

        printf_s("\n요소값 : %d", delete_address->data);
        new_end_address = delete_address;
        delete_address = delete_address->link;

        printf_s(" -> %d\n", delete_address->data);
    }

    new_end_address->link = search_address->link;
    free(search_address);

    return 0;
}


// item이 list 안에 있는지 확인
ListNode* search(ListNode* head, list_element item) {

    ListNode* address = NULL;
    printf_s("\n\n[search 시작] : head에 저장된 시작 주소는? %d\n", head);

    while(head != NULL){

        if (head->data == item) {

            address = head;
            printf_s("[검색어 %d 찾기 완료] : 메모리주소 %d에 존재\n", item , address);
            break;
        }
        else {
            head = head->link;
            printf_s("[다음 주소] : %d로..\n", head);
        }
    }

    return address;
}

// list1과 list2를 연결
ListNode* concat(ListNode* head1, ListNode* head2) {

    printf_s("\nhead1시작.. %d\n", head1);

    if (head1 == NULL) {
        return head2;
    }

    if (head2 == NULL) {
        return head1;
    }

    ListNode* head1_index = head1;

    while (head1_index->link != NULL) {

        printf_s("다음주소.. %d -> %d로..\n", head1_index, head1_index->link);
        head1_index = head1_index->link;
    }

    head1_index->link = head2;

    printf_s("head1의 마지막 link값 = %d -> %d(%d)로..\n", head1_index, head1_index->link, (head2));

    return head1;
    
}

// list1의 요소 전부를 반대로 연결
ListNode* reverse(ListNode* head) {

    ListNode* already_changed;
    ListNode* should_be_changed = NULL;
    ListNode* target_address = head;

    if (head == NULL) {
        return NULL;
    }

    while (target_address != NULL) {

        already_changed = should_be_changed;
        should_be_changed = target_address;

        target_address = target_address->link;
        should_be_changed->link = already_changed;

    }

    return should_be_changed;
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
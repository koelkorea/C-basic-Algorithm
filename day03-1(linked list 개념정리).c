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

//  # 연결리스트의 구성요소 : 
//    - 머리(Head) : 연결 리스트에서 첫번째 노드의 주소를 저장한 포인터 (= 연결리스트를 시작하려면, 일단 헤드의 주소값에 위치한 값을 역참조해야 함)
//    - 노드(Node) : 연결 리스트의 요소
//    - 값(Value)  : 노드에 저장된 데이터
//    - 연결(Link) : 다른 노드로 연결을 위한 포인터 -> (중요!) 마지막 노드의 link = NULL

//  # 연결리스트의 종류
//   1. 단순 연결 리스트(Singly Linked List)
//      : 각 노드의 link에 다음 노드의 주소가 있음. 
//        -> Head : 1번째노드 주소값 -> 1번 node(value, link :  1번째노드 주소값) -> .... -> n번 node(value, link : Null)

//      # 단순 연결 리스트(Singly Linked List)의 [마지막 노드의 link = NULL]

//   2. 원형 연결 리스트(Circular Linked List)
//      : 각 노드의 link에 다음 노드의 주소가 있어, 단방향이지만 모든 노드가 형으로 연결되어 있는 리스트
//        -> Head : 1번째노드 주소값 -> 1번 node(value, link :  1번째노드 주소값) -> .... -> n번 node(value, link : Head의 주소값)

//      # 원형 연결 리스트(Circular Linked List)의 [마지막 노드의 link =  head의 주소값]

//   3. 더블 원형 연결 리스트(Double Circular Linked List)
//      : head를 포함해서 각 노드의 link가 전노드link와 후노드link로 분화되어, 양방향으로 모든 노드가 원형으로 연결되어 있는 리스트
//        -> Head : 1번째노드 주소값 -> 1번 node(value, link :  1번째노드 주소값) -> .... -> n번 node(value, link : Head의 주소값)

//      # 더블 원형 연결 리스트(Double Circular Linked List)의 [마지막 노드의 후노드 link = head의 주소값]
//                                                             [head의 전노드 link = 마지막노드의 주소값]


//  # 연결 리스트 ADT(Abstract data type(추상적 데이터 유형) = 자료 구조를 어떻게 다룰지, 기능적 측면을 서술하고 구체화 과정)
//    - insert_first(list*, item) : 해당 list의 맨 앞에 Node 추가
//    - insert_last(list*, item)  : 해당 list의 맨 뒤에 Node 추가
//    - insert_sort(list*, item)  : 해당 list에서 item에 해당하는 값을 추가하는데, 오름차순에 맞는 순서로 Node에 추가
//    - delete_first(list*)  : 해당 list의 맨 앞에 Node 제거
//    - delete_last(list*)   : 해당 list의 맨 뒤에 Node 제거
//    - delete_search(list*, value) : 해당 list에서 item에 해당하는 값을 가진 노드를 찾아 삭제하고, 성공 실패값 리턴
//    - search(list*, item)  : item이 list 안에 있는지 확인
//    - concat(list1*, list2*) : list1과 list2를 연결
//    - reverse(list*) : list1의 요소 전부를 반대로 연결
//    - display(list*) : 해당 list의 모든 value를 연속적으로 모두 표시
//    - freelist(list*) : 해당 list를 위해 할당된 메모리 주소를 해제하기

// 연결 리스트 ADT 전부 구현해보자
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함

// int명칭 재정의용
typedef int list_element;

// 연결리스트 개별 노드를 구성하는 존재 (value, link)
typedef struct ListNode {

    list_element data;
    struct ListNode* link;

} ListNode;

// 맨 앞,뒤 에 Node 추가
ListNode* insert_first(ListNode* head, list_element item);   // done
ListNode* insert_last(ListNode* head, list_element item);    // done

// 정렬을 염두에 두고 추가 (이건 단독으로 리스트)
ListNode* insert_sort(ListNode* head, list_element item);    // done

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

    // head1 : insert_first, delete_first, concat의 파리미터로 테스트예정
    ListNode* head1 = NULL;

    // head2 : insert_first, insert_last, delete_search, concat의 파리미터로 테스트예정
    ListNode* head2 = NULL;

    // head3 : insert_sort 테스트 예정
    ListNode* head3 = NULL;

    // head1 채우기 : insert_first
    for (int i = 100; i > 0; i -= 10) {

        head1 = insert_first(head1, i);
    }
    display(head1);

    // head1 지우기 : delete_first
    for (int i = 100; i > 20; i -= 10) {

        head1 = delete_first(head1);
        display(head1);
    }

    // head2 채우기 : insert_first
    for (int i = 1; i <= 1000; i += 100) {

        head2 = insert_first(head2, i);
    }

    // head2 채우기 : insert_last로 890916라는 값을 value로 하는 노드를 맨 끝에 붙이기
    head2 = insert_last(head2, 890916);
    display(head2);

    // head2 지우기 : delete_search로 890916라는 값을 value로 하는 노드를 찾아 지우고, 결과값을 리턴
    if (delete_search(head2, 890916) == 0) {

        printf("[검색 삭제 성공]\n");
        display(head2);
    }


    // head1_2 : delete_last, concat, reverse, search의 파라미터 테스트예정

    // head1_2 만들기 : concat (연결) 실행해서, head1과 head2를 연결
    ListNode* head1_2 = concat(head1, head2);

    // head1_2 지우기 : delete_last
    head1_2 = delete_last(head1_2);
    display(head1_2);

    // head1_2 연결순서 바꾸기 : reverse (역순) 실행
    head1_2 = reverse(head1_2);
    display(head1_2);

    // search_address : search (검색) 실행 테스트 예정(결과값 받을 용도)
    ListNode* search_address = search(head1_2, 100);

    // head3 : insert_sort(정렬 추가) 실행 테스트 예정 
    for (int i = 1; i <= 10; i += 1) {

        // 랜덤으로 생성된 10이하의 값을 노드를 만들어 채울때마다, 그 위치를 오름차순에 맞는 순서로 놓기
        head3 = insert_sort(head3, rand() % 10);
        display(head3);
    }

    // (주의!) concat을 쓰고나면, 두 연결리스트의 연결구조가 변하게 됨. 따라서 concat의 대상이 된 두개의 연결리스트의 시작점을 무지성적으로 각각 메모리 해제하려다 보면... 
    //  -> 이미 해제되서 없는 메모리를 해제하라고 명령을 내리게 되는 경우가 종종 생기는데 이떄 에러가 발생하니 주의를 요한다
    freelist(head1_2);
    freelist(head3);

    return 0;
}

// insert_first : 맨 앞에 Node 추가(전에 만든 녀석은 뒤로 밀리는 방식)
ListNode* insert_first(ListNode* head, list_element item) {

    printf_s("\n\n------------------------------[insert_first로 %d 넣기 시작!]------------------------------\n", item);

    // 새로운 맨 앞의 노드의 데이터를 넣을 주소값이 어딘지 알기 위해, ListNode의 포인트변수의 메모리를 할당함
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));

    // 노드를 만들 메모리 공간이 없다면?? 에러 띄우기
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

    printf_s("\n\n------------------------------[insert_last로 %d 넣기 시작!]------------------------------\n", item);

    // 노드를 만들 공간이 없다면?? 에러 띄우기
    if (Newnode == NULL) {
        printf("메모리 부족");
        return NULL;
    }
    
    if (head == NULL) {
        return insert_first(head, item);
    }
    
    // 새로운 맨 뒤의 노드의 데이터를 넣을 주소값이 어딘지 알기 위해, ListNode의 포인트변수의 메모리를 할당함
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));
    ListNode* insert_address = head;

    while (insert_address->link != NULL) {

        printf_s("\n비교 노드 요소값 : %d", insert_address->data);

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

    // 끼어들어갈 새로운 ListNode의 멤버변수 값들을 저장하기 위한 메모리 공간이 위치한 주소의 시작값을 저장
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));

    // 검사중인 노드의 data값이 끼어들어갈 노드의 item보다 클 경우, 해당 노드의 위치 앞으로 끼어들어갈 노드의 위치가 정해짐에 따른 ListNode 주소값 저장용 (이 노드가 위치하는 주소값 = Newnode의 link값)
    ListNode* insert_arrivial_link_address = head;

    // 끼어들어갈 노드를 1차적으로 앞에서 연결해줄 ListNode 주속값 저장용
    ListNode* insert_front_link_address = head;

    // 노드가 들어갈 위치를 위해 data값을 비교하는 도중 맞는값이 나오는지 여부 기준이 1
    int search_complete_flag = 0;

    printf_s("\n\n------------------------------[insert_sort로 %d 넣기 시작!]------------------------------\n", item);

    // 노드를 만들 공간이 없다면?? 에러 띄우기
    if (Newnode == NULL) {
        printf("메모리 부족");
        return NULL;
    }

    // ---------------------(case1) : 연결리스트에 아무것도 안 들어있다?-------------------------------------
    //  => Newnode의 주소를 head와 연결해줘야 함 = insert_first를 실행하고 그 주소값 리턴

    // head가 가르키는 주소값이 없다면? 
    if (insert_arrivial_link_address == NULL) {

        // 1번 노드에 입장시키기
        return insert_first(head, item);
    }
    //----------------------------------------------------------------------------------------------------

    // head가 가르키는 주소값이 있다면?
    //  검사중인 노드의 data값이 끼어들어갈 노드의 기준이 되는 위치값인 insert_arrivial_link_address가 null (= 마지막 노드의 위치에 다다를때까지) 이 나올때까지 반복
    while (insert_arrivial_link_address != NULL) {

        // ---------------------(case2) : Newnode의 item값이 연결리스트의 모든 노드의 값보다 작은게 판정(= 가장 작은 값인 1번 값과 비교했을때 작음)?------------------
        //  => Newnode의 주소를 head와 연결해줘야 함 = insert_first를 실행하고 그 주소값 리턴

        // @입력되는 item값이 현재 가장 작은 값인지 확인하는 방법
        // 1. 현재 검사중인 노드의 주고값이 head가 가르키는 주소값인 1번 노드의 주소값 일치
        // 2. 1번에서 확인한 현재 검사중인 노드의 주소값(head)의 value값이 item보다 큰 경우
        if (insert_arrivial_link_address == head && insert_arrivial_link_address->data >= item) {

            printf_s("\n검색값 %d은 가장 작은 노드의 값 %d 보다 작음", item, insert_arrivial_link_address->data);
            return insert_first(head, item);
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------

        // ---------------------(case3) : 연결리스트의 노드의 값중 Newnode의 item값보다 큰게 존재한다?-------------------------------------------------
        //   => Newnode의 link값을 해당 노드의 주소값(해당 노드전의 노드의 link가 가진 원래값)과 연결 +  Newnode의 주소를 해당 노드전의 노드의 link와 연결

        // 현재 검사중인 노드의 주소값의 value값이 item보다 큰 경우
        if (insert_arrivial_link_address->data >= item) {

            printf_s("\n검색값 %d보다 크거나 같은 비교 노드 요소값 %d 발견", item, insert_arrivial_link_address->data);

            // 끼워넣을 Newnode의 data는 item대입
            Newnode->data = item;

            // 끼워넣을 Newnode의 다음 노드의 주소값을 나타내는 link의 값 = 찾아낸 끼워넣을 기준 노드의 주소값 insert_arrivial_link_address으로 넣기
            Newnode->link = insert_arrivial_link_address;

            // 현재 검사중인 노드의 이전 노드의 주소값을 저장한 insert_arrivial_link_address의 다음 노드의 주소값을 나타내는 link의 값 = 끼워넣을 노드 Newnode의 주소값으로 넣기
            insert_front_link_address->link = Newnode;

            return head;
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------

        // ---------------------------(case4) : Newnode의 item값이 연결리스트의 모든 노드의 값보다 크거나 같다?------------------------------------------
        //   => Newnode의 주소를 마지막 노드의 link와 연결해줘야 함 insert_last를 실행하고 그 주소값 리턴

        // @입력되는 item값이 현재 가장 작은 값인지 확인하는 방법
        //  -> 현재 검사중인 노드의 다음 노드의 주소값을 나타내는 link값이 없으면 됨
        if (insert_arrivial_link_address->link == NULL) {

            return insert_last(head, item);
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------

        // case234에 안 걸리면?

        // 현재 끼어넣을 기준이 되는 노드의 주소값을 찾는 insert_front_link_address의 주소값을 insert_front_link_address라는 끼워넣을 노드를 앞에서 연결해줄 노드값에 
        insert_front_link_address = insert_arrivial_link_address;

        // 끼어넣을 기준이 되는 노드의 주소값을 찾는 insert_front_link_address는 그가 역참조하는 link값으로 갱신하여, 끼어놓을 위치를 갱신해서 다시 item과 value의 관계를비교하는 로직을 탄다
        insert_arrivial_link_address = insert_arrivial_link_address->link;
    }

}

// 맨 앞의 Node 삭제
ListNode* delete_first(ListNode* head) {

    printf_s("\n\n------------------------------[delete_first로 첫번째 노드 삭제 시작!]------------------------------\n");

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

    printf_s("\n\n------------------------------[delete_last로 마지막 노드 삭제 시작!]------------------------------\n");

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

    printf_s("\n\n------------------------------[delete_search로 검색어 %d 갖는 노드 삭제 시작!]------------------------------\n", value);

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

    printf_s("\n\n------------------------------[search 시작! : head에 저장된 시작 주소는? %d]------------------------------\n\n", head);

    ListNode* address = NULL;

    while (head != NULL) {

        if (head->data == item) {

            address = head;
            printf_s("*******************[검색어 %d 찾기 완료] : 메모리주소 %d에 존재****************\n", item, address);
            break;
        }
        else {
            head = head->link;
            printf_s("[다음 주소] : %d로..\n", head);
        }
    }

    return address;
}

// concat : list1과 list2를 연결
ListNode* concat(ListNode* head1, ListNode* head2) {

    printf_s("\n\n------------------------------[concat 시작! : head1, head2 연결시작]------------------------------\n\n");

    printf_s("\nhead1 시작위치 : %d\n", head1);
    printf_s("\nhead2 시작위치 : %d\n", head2);

    // 1번 연결리스트의 head가 나타내는 1번째노드의 주소값이 없다면 (= 연결리스트 자체가 없음)?
    //  -> 2번 연결리스트의 head기 나타내는 1번째노드의 주소값을 출력 (NULL이던 주소값이 있던 상관없음)
    if (head1 == NULL) {
        return head2;
    }

    // 1번 연결리스트의 head가 나타내는 1번째노드의 주소값이 있는데? 2번 연결리스트의 head가 나타내는 1번째노드의 주소값이 없다면 (= 연결리스트 자체가 없음)?
    //  -> 1번 연결리스트의 head기 나타내는 1번째노드의 주소값을 출력 (NULL이던 주소값이 있던 상관없음)
    if (head2 == NULL) {
        return head1;
    }

    // (중요!) 1번 연결리스트의 head가 나타내는 1번째노드의 주소값 + 2번 연결리스트의 head가 나타내는 1번째노드의 주소값이 모두 null이 아니면 concat개시

    // current_head1_index : 1번 연결리스트의 마지막 노드의 주소를 알아내기 위한 ListNode의 주소값을 받는 포인터변수
    ListNode* current_head1_index = head1;

    // current_head1_index(현재의 노드 주소값)에 위치한 link가 null이 나올때까지(= current_head1_index가 마지막 노드의 주소값을 나타낼까지)... 계속 수행
    while (current_head1_index->link != NULL) {

        printf_s("다음주소.. %d -> %d로..\n", current_head1_index, current_head1_index->link);

        // current_head1_index(현재의 노드 주소값)에 위치한 link이 null이 아니면, 다음 노드의 주소값을 의미하는 current_head1_index->link가 current_head1_index의 값으로 갱신
        current_head1_index = current_head1_index->link;
    }

    // null이었던 current_head1_index(현재의 노드 주소값)에 위치한 link값을 2번 연결리스트의 head가 나타내는 1번째노드의 주소값인 head2로 대입
    current_head1_index->link = head2;

    // 새로운 concat head
    ListNode* concat_head = head1;

    // 더이상 연결전 이전헤드는 사용안함
    head1 = NULL;
    head2 = NULL;

    printf_s("----------------------------[concat 붙이기 완료] : head1의 마지막 link값 = %d -> %d(%d)로.. 변경-----------------------------\n", current_head1_index, current_head1_index->link, (head2));

    // 1번, 2번 연결이 완료된 연결리스트의 시작점인 1번 연결리스트의 헤드값을 받은 concat_head리턴
    return concat_head;

}

// reverse : list1의 요소 전부를 반대로 연결
ListNode* reverse(ListNode* head) {

    // 애초에 연결리스트의 노드가 없다면, null을반환
    if (head == NULL) {
        return NULL;
    }

    printf_s("\n\n------------------------------[reverse 시작! : head 역행시키기]---------------------------------------------\n\n");

    // 연결리스트의 노드가 하나라도 있다면, head에 저장된 1번 노드의 값을 target노드로 연속리스트 방향 역행시작

    // target_address : 현재 위치하는 중인 노드로.. head에서 시작하고, 작업이 끝나면 자신이 저장하는 주소값에 노드의 다음 노드의 주소를 저장한 link로 갱신됨
    ListNode* target_address = head;

    // already_reversed_node : 이미 역행처리가 완료된 노드로 시작값은 존재하지 않음
    ListNode* already_reversed_node;

    // should_be_reversed_node : 역행처리를 현재 수행해야할 노드의 주소로 시작값은 NULL
    ListNode* should_be_reversed_node = NULL;


    // 현재 역행작업 중인 노드의 주소값이 null (= 이 녀석이 역행한 연결리스트의 마지막 노드라는 의미)이 될까지 반복
    while (target_address != NULL) {

        // 이미 역행처리가 완료된 노드의 주소값 already_reversed_node을 앞선 차례에 변경한 노드의 주소값 should_be_reversed_node으로 갱신해서 저장 
        // -> 처음에는 역행완료된게 없으니 null
        already_reversed_node = should_be_reversed_node;

        // 역행처리를 현재 수행해야할 노드의 주소값 should_be_reversed_node을 현재 위치할 노드의 주소 target_address값으로 갱신해서 저장
        should_be_reversed_node = target_address;

        // 아직 작업안한 뒤의 노드의 주소를 타겟으로 갱신해줌
        target_address = target_address->link;

        // 현재 역행처리를 현재 수행할 노드의 다음 노드의 주소값을 저장하는 should_be_reversed_node의 link값을 이미 변경된 노드의 주소값 already_reversed_node으로 변경
        //  -> 처음에는 기존에 역행처리 완료된 노드가 없으니 당연히 null이 들어감 (= 처음 작업하는 노드는 결국 역행된 리스트에서는 끝번 노드를 의미)
        should_be_reversed_node->link = already_reversed_node;
    }

     printf_s("----------------------------[reverse 완료] : head1값 = %d -> %d(%d)로.. 변경-----------------------------\n", head, should_be_reversed_node);

     // 역행작업이 끝나고 나면, 현재 역행작업을 마친 노드의 주소값을 리턴(어차피 연결리스트의 1번째 주소를 저장하는 head는 메인에 존재하니 이 리턴값을 대입하면 reverse 완료)
    return should_be_reversed_node;
    
    //head = should_be_reversed_node;
    //return head;
}

// 리스트의 모든 요소를 표시
void display(ListNode* head) {

    printf_s("\n\n------------------------------[주소값 %d display 시작!]------------------------------\n\n", head);

    printf("list 출력 : ");

    while (head) {
        printf("%3d -> ", head->data);
        head = head->link;
    }
    printf("NULL\n");
}

void freelist(ListNode* head) {

    ListNode* free_address = head;
    
    while (free_address != NULL) {

        ListNode* next_address = free_address->link;
        free(free_address);
        free_address = next_address;
    }
}

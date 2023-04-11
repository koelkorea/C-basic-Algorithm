// 이중 연결 리스트(Doubly Linked List)
//  : head를 포함해서 각 노드의 link가 왼쪽 링크(Llink)와 오른쪽 링크(Rlink)를 가진 구조, 양방향으로 모든 노드가 원형으로 연결되어 있는 리스트

//  # 오른쪽 링크는 선행, 오른쪽 링크는 후속 노드를 가짐
//  # 헤더 또한 link를 가진 노드로 구성 (value = null) <-> linked list의 head 포인터

//  # Double list 구조체 ( 구성 요소 )

//		typedef int DlistElement;

//		typedef struct DlistNode {
// 
//		    DlistElement data;
//		    struct DlistNode* Llink;
//		    struct DlistNode* Rlink;
//		} DlistNode;

//  # 이중 연결 리스트(Doubly Linked List) ADT
//    - DoubleListNode* DoubleInitial(DoubleListNode* head) : 초기화
//    - DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoubleListElement item) : 노드 생성
//    - void DoubleDeleteFirst(DoubleListNode* head) : 노드 삭제
//    - DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2) : 결합 list1 + list2
//    - void DoubleDisplay(DoubleListNode * head)       :  정방향 출력
//    - void DoubleDisplayReverse(DoubleListNode* head) : 역방향 출력
//    - void FreeDoubleList(DoubleListNode* head)       : 리스트 전체 삭제

// 더블 연결 리스트 ADT 전부 구현해보자
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함

typedef int DoublelistElement;
typedef struct DlistNode {

    DoublelistElement data;
    struct DoublelistNode* Llink;
    struct DoublelistNode* Rlink;
} DoubleListNode;

DoubleListNode* DoubleInitial(DoubleListNode* head);                              // done
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoublelistElement item);  // done
void DoubleDeleteFirst(DoubleListNode* head);                                     // done
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2);       // done
void DoubleDisplay(DoubleListNode* head);                                         // done 
void DoubleDisplayReverse(DoubleListNode* head);                                  // done
void FreeDoubleList(DoubleListNode* head);                                        // done

int main(void) {

    srand((unsigned int)time(NULL));

    DoubleListNode* double_list1 = NULL;
    DoubleListNode* double_list2 = NULL;
    DoubleListNode* double_concat_list = NULL;

    double_list1 = DoubleInitial(double_list1);
    double_list2 = DoubleInitial(double_list2);

    DoubleDisplay(double_list1);

    for (int i = 1; i <= 10; i++) {
        double_list1 = DoubleInsertFirst(double_list1, rand() % 10);
        double_list2 = DoubleInsertFirst(double_list2, rand() % 10);
    }
    DoubleDisplay(double_list1);
    DoubleDisplayReverse(double_list1);

    DoubleDeleteFirst(double_list1);
    DoubleDeleteFirst(double_list1);

    DoubleDisplay(double_list1);
    DoubleDisplay(double_list2);

    double_concat_list = DoubleConcat(double_list1, double_list2);
    DoubleDisplay(double_concat_list);
    DoubleDisplayReverse(double_concat_list);

    FreeDoubleList(double_concat_list);

    return 0;
}

// 더블링크드 리스트 head 노드 생성(= 사실상 입력절차)
DoubleListNode* DoubleInitial(DoubleListNode* head) {

    DoubleListNode* head_node = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    // 헤드의 데이터 값은 노드의 총 노드수 (만들때는 당연히 총 노드수는 0)
    head_node->data = 0;
    head_node->Llink = head_node;
    head_node->Rlink = head_node;

    printf_s("(dl 생성 초기화) : %d에 더블링크드 리스트의 헤드노드가 추가되었습니다. 해당 주소값은 %d에 위치에 기록되어 있습니다. \n", head_node, &head);

    head = head_node;

    return head;
}

// 해당 head가 가르키는 더블링크드 리스트의 1번째 노드로 item값 추가
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoublelistElement item) {

    DoubleListNode* insert_first_node = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    if (insert_first_node == NULL) {
        printf("메모리 부족");
        return NULL;
    }

    insert_first_node->data = item;
    insert_first_node->Llink = head;

    // (case1) 현재 리스트에 존재하는 노드가 헤더노드 혼자일 경우? (= 헤더노드의 양link가 스스로를 가리킴)
    //  -> 헤더노드의 양 link의 값을 insert_first_node의 주소값으로 + insert_first_node 오른쪽 주소도 head를 가리키게 함
    if (head->Llink == head && head->Rlink == head) {

        head->Llink = insert_first_node;
        head->Rlink = insert_first_node;

        insert_first_node->Rlink = head;
    }

    // (case2) 해당 더블링크드 리스트에 다른 노드들이 있는 경우 (= 헤드노드의 오른쪽link가 다른 노드를 가르킬경우)
    //  -> insert_first_node 오른쪽 주소가 head의 오른쪽link를 가지게 함 + 헤더노드의 오른쪽 link값을 insert_first_node로 변경 + 기존 1번째노드의 왼쪽 Link값을 insert_first_node의 주소값으로 수정
    if (head->Rlink != head) {

        // 기존에 1번째 노드였던 노드의 주소값(= 굴러들어온 노드에 의해 2번째로 밀려날 예정)
        DoubleListNode* move_to_2nd_node = head->Rlink;

        insert_first_node->Rlink = head->Rlink;
        move_to_2nd_node->Llink = insert_first_node;
        head->Rlink = insert_first_node;
    }

    // 헤드의 데이터 값은 노드의 총 노드수
    head->data++;

    return head;
}

// 해당 head가 가르키는 더블링크드 리스트의 1번째 노드 삭제
void DoubleDeleteFirst(DoubleListNode* head) {

    DoubleListNode* delete_node = head->Rlink;

    printf_s("\n\n------------------------------[DoubleDeleteFirst 시작!]------------------------------\n\n");

    // (case1) 현재 리스트에 존재하는 노드가 헤더노드 혼자일 경우? (= 헤더노드의 양link가 스스로를 가리킴)
    //  -> 경고를 끝내기
    if (head->Llink == head && head->Rlink == head && head->data == 0) {

        printf_s("(경고) : 해당 더블링크드 리스트에는 헤드 외에 다른 노드가 없어서 삭제가 불가능합니다.\n");
    }
    // (case2) 해당 더블링크드 리스트에 1번째 노드만 있는 경우 (= 헤드노드의 오른쪽link가 head가 저장하는 주소값을 가르킬경우 or head의 data가 1)
    //  -> head의 Rlink가 기존의 1번째 노드의 head의 주소값을 받으면 됨
    else if (delete_node->Rlink == head && head->data == 1) {
        head->Rlink = head;

        printf_s("해당 리스트의 주소 %d에 위치한 1번째 노드의 data값 %d 삭제완료! \n", delete_node, delete_node->data);
        free(delete_node);
    }

    // (case3) 해당 더블링크드 리스트에 2개 이상의 노드 존재 (= 1번째노드의 오른쪽link가 head를 가르킬경우 or head의 data가 1초과)
    //  -> head의 Rlink가 기존의 1번째 노드의 Rlink의 주소값을 받으면 됨
    else if (delete_node->Rlink != head && head->data > 1) {
        head->Rlink = delete_node->Rlink;

        printf_s("해당 리스트의 주소 %d에 위치한 1번째 노드의 data값 %d 삭제완료! \n", delete_node, delete_node->data);
        free(delete_node);
    }

    // 헤드의 데이터 값은 노드의 총 노드수
    head->data--;
    printf_s("해당 리스트의 주소 %d에 위치한 노드 총 개수 : %d \n", head, head->data);
}

// 두개의 더블링크드 리스트 head1, head2 결합
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2) {

    // (case1) 1번째 더블링크드 리스트의 노드가 헤더밖에 없다면?
    // -> concat헤드의 주체는 head2로 고정 (head2도 마찬가지라도 상관이 없음)
    if (head1->data == 0) {
        return head2;
    }

    // (case2) 2번째 더블링크드 리스트의 노드가 헤더밖에 없다면?
    // -> concat헤드의 주체는 head1로 고정
    if (head2->data == 0) {
        return head1;
    }

    // (중요!) 1번 연결리스트의 head의 data에 표기된 노드의 숫자 + 2번 연결리스트의 head의  data에 표기된 노드의 숫자가 둘 다 0이 아니면 concat개시

    // current_head1_index : 1번 연결리스트의 마지막 노드의 주소를 알아내기 위한 ListNode의 주소값을 받는 포인터변수
    DoubleListNode* current_head1_index = head1;

    // current_head1_index(현재의 노드 주소값)에 위치한 link가 null이 나올때까지(= current_head1_index가 마지막 노드의 주소값을 나타낼까지)... 계속 수행
    for (int i = 1; i <= head1->data; i++) {

        printf_s("다음주소.. %d -> %d로..\n", current_head1_index, current_head1_index->Rlink);

        // current_head1_index(현재의 노드 주소값)에 위치한 Rlink가 head1의 주소값을 가르키지 않는이상 current_head1_index->Rlink를 current_head1_index의 값으로 갱신
        if (current_head1_index->Rlink == head1) {
            break;
        }
        else {
            current_head1_index = current_head1_index->Rlink;
        }
    }

    // current_head2_index : 2번 연결리스트의 마지막 노드의 주소를 알아내기 위한 ListNode의 주소값을 받는 포인터변수
    DoubleListNode* current_head2_index = head2;

    // current_head2_index(현재의 노드 주소값)에 위치한 link가 null이 나올때까지(= current_head1_index가 마지막 노드의 주소값을 나타낼까지)... 계속 수행
    for (int i = 1; i <= head2->data; i++) {

        printf_s("다음주소.. %d -> %d로..\n", current_head2_index, current_head2_index->Rlink);

        // current_head1_index(현재의 노드 주소값)에 위치한 Rlink가 head1의 주소값을 가르키지 않는이상 current_head1_index->Rlink를 current_head1_index의 값으로 갱신
        if (current_head2_index->Rlink == head2) {
            break;
        }
        else {
            current_head2_index = current_head2_index->Rlink;
        }
    }

    // [변경해줘야 할 녀석들]
    // 
    // 1. head1이었던 current_head1_index(현재의 노드 주소값)에 위치한 link값을 2번 연결리스트의 head가 나타내는 1번째노드의 주소값인 head2->Rlink로 대입
    current_head1_index->Rlink = head2->Rlink;

    // 2. head2의 1번째 노드의 Llink값도 head의 마지막 노드의 주소값으로 갱신
    DoubleListNode* second_dlist_1st_node = head2->Rlink;
    second_dlist_1st_node->Llink = current_head1_index;

    // 3. 1번 연결리스트의 헤드 노드의 왼쪽link 주소값을 2번 연결리스트 마지막노드의 주소로 갱신
    head1->Llink = current_head2_index;

    // 4. 2번 연결리스트 마지막노드의 오른쪽link 1번 연결리스트의 헤드 노드의 주소로 갱신
    current_head2_index->Rlink = head1;

    // 총 노드수 갱신하기
    head1->data = head1->data + head2->data;

    // 더이상 연결대상의 이전헤드는 사용안함
    free(head2);
    head2 = NULL;

    printf_s("----------------------------[concat 붙이기 완료] : head1의 마지막 link값 = %d -> %d(%d)로.. 변경-----------------------------\n", head1, current_head1_index->Rlink);

    // 1번, 2번 연결이 완료된 연결리스트의 시작점인 1번 연결리스트의 헤드값을 받은 concat_head리턴
    return head1;

}

// 더블링크드 리스트의 모든 노드의 data값 순차적으로 출력(Rlink 따라가면 됨)
void DoubleDisplay(DoubleListNode* head) {

    printf_s("\n\n------------------------------[주소값 %d DoubleDisplay 시작!]------------------------------\n\n", head);

    if (head->data == 0) {

        printf_s("(경고) : 해당 더블링크드 리스트에는 헤드 외에 다른 노드가 없습니다.\n");

    }
    else {

        printf("해당 dlist의 노드개수 %d개인 리스트의 값들 출력 : ", head->data);

        DoubleListNode* current_node = head->Rlink;

        printf("head -> ");

        for (int i = 1; i <= head->data; i++) {

            printf("%3d -> ", current_node->data);
            current_node = current_node->Rlink;
        }

        printf("head\n");
    }
}

// 더블링크드 리스트의 모든 노드의 data값 역순으로 출력 (Llink 따라가면 됨)
void DoubleDisplayReverse(DoubleListNode* head) {

    printf_s("\n\n------------------------------[주소값 %d DoubleDisplayReverse 시작!]------------------------------\n\n", head);

    if (head->data == 0) {

        printf_s("(경고) : 해당 더블링크드 리스트에는 헤드 외에 다른 노드가 없습니다.\n");

    }
    else {

        printf("해당 dlist의 노드개수 %d개인 리스트의 값들 출력 : ", head->data);

        DoubleListNode* current_node = head->Llink;

        printf("head -> ");

        for (int i = 1; i <= head->data; i++) {

            printf("%3d -> ", current_node->data);
            current_node = current_node->Llink;
        }

        printf("head\n");
    }

}

// 동적할당한 더블링크드 리스트 메모리 할당 해제
void FreeDoubleList(DoubleListNode* head) {

    printf_s("\n\n------------------------------[주소값 %d FreeDoubleList 시작!]------------------------------\n\n", head);

    printf("(해당 dlist의 노드의 개수) : %d개 \n", head->data);

    DoubleListNode* free_address = head;

    // 해당 더블링크드 리스트에 헤더 외의 노드가 하나라도 있다면?
    //  -> 하나씩 따라가며 그 개수에 해당하는 노드 해제
    if (head->data != 0) {

        free_address = free_address->Rlink;

        for (int i = 1; i <= head->data; i++) {

            DoubleListNode* next_address = free_address->Rlink;

            printf("해당 dlist %d번째 노드 해제 : 노드의 값이 %d이며 주소값 %d부터 시작하는 해당 노드에 할당된 메모리 영역이 해제되었습니다.\n", i, free_address->data ,  free_address);

            free(free_address);
            free_address = next_address;
        }
    }

    // 해당 더블링크드 리스트에 헤더 밖에 노드가 없는 상태면(해제를 하던, 원래부터 그렇던), 헤더노드도 해제
    printf("\n-----------------[FreeDoubleList 완료] 주소값 %d부터 시작하는 해당 더블 dlist의 헤더노드에 할당된 메모리 영역이 해제되었습니다.---------------\n",  free_address);
    free(free_address);
}

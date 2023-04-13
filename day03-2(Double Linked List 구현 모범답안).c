#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef int DoubleListElement;

typedef struct DoubleListNode {

    DoubleListElement data;
    struct DoubleListNode* Llink;
    struct DoubleListNode* Rlink;

}DoubleListNode;

int select;

// 이중 연결 리스트 초기화 (헤더 노드 생성)
DoubleListNode* DoubleInitial(DoubleListNode* head);

// 이중 연결 리스트 제일 앞 노드 생성
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoubleListElement item);

// 이중 연결 리스트 제일 앞 노드 삭제 
void DoubleDeleteFirst(DoubleListNode* head);

// 이중 연결 리스트 결합 list1 + list2
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2);

// 이중 연결 리스트 정방향 출력
void DoubleDisplay(DoubleListNode* head);

// 이중 연결 리스트 역방향 출력
void DoubleDisplayReverse(DoubleListNode* head);

// 이중 연결 리스트 전체 삭제
void FreeDoubleList(DoubleListNode* head);

int main() {

    srand((unsigned)time(NULL));

    int menu = 0, list_num = 0;

    DoubleListElement value, select_1, select_2;

    // 정적배열 형식
    DoubleListNode* head[5] = { 0 };

    // 동적배열 형식
    //DoubleListNode** head = NULL;
    //printf("리스트 생성 개수 입력 : ");
    //scanf_s("%d", &list_num);
    //head = (DoubleListNode*)malloc(sizeof(DoubleListNode*) * list_num);

    for (int i = 0; i < 5; i++) {

        head[i] = DoubleInitial(head[i]);
        for (int j = 0; j < 5; j++) head[i] = DoubleInsertFirst(head[i], rand() % 5000 + 1);
    }

    while (1) {

        printf("[ 현재 %d 번 Doubly Linked List ] \n", select);
        printf("1. Select List\n");
        printf("2. Insert List\n");
        printf("3. Delete List\n");
        printf("4. Forward Print List\n");
        printf("5. Reverse Print List\n");
        printf("6. Concatenate List\n");
        printf("1~6 외 모두 종료\n");
        printf("메뉴를 입력 하세요. :");

        scanf_s("%d", &menu);
        while (getchar() != '\n');

        switch (menu) {

            case 1:
                printf("List 번호를 입력하세요. (1~5) : ");

                scanf_s("%d", &value);
                while (getchar() != '\n');

                if (value >= 0 && value < 5) {
                    select = value;
                    printf("현재 %2d 번 리스트 \n", select);
                }
                else {
                    printf("잘못 입력했습니다.\n");
                    printf("현재 %2d 번 리스트 \n", select);
                }
                break;
            case 2:
                printf("값을 입력하세요. : ");

                scanf_s("%d", &value);
                while (getchar() != '\n');

                head[select] = DoubleInsertFirst(head[select], value);
                printf("%d 값을 넣었습니다.\n", value);

                break;
            case 3:
                printf("값을 삭제합니다.\n");
                DoubleDeleteFirst(head[select]);
                break;
            case 4:
                printf("정방향 값 출력\n");
                DoubleDisplay(head[select]);
                break;
            case 5:
                printf("역방향 값 출력\n");
                DoubleDisplayReverse(head[select]);
                break;
            case 6:
                printf("연결 할 List 번호를 입력하세요. (1~5) : \n");

                scanf_s("%d", &select_1);
                while (getchar() != '\n');

                printf(" [ %2d List 제외 ]\n", select_1);

                printf(" %2d List와 연결 할 List 번호를 입력하세요. (1~5) :", select_1);

                scanf_s("%d", &select_2);
                while (getchar() != '\n');

                if (0 <= select_1 && select_1 < 5 && 0 <= select_2 && select_2 < 5) {
                    head[select_1] = DoubleConcat(head[select_1], head[select_2]);
                }
                break;
            default: exit(0);
        }
    }

    for (int i = 0; i < 5; i++) {
        FreeDoubleList(head[i]);
    }

    return 0;
}

// 이중 연결 리스트 초기화 (= 헤더 노드 생성) (= 같은 방법 구현) 
DoubleListNode* DoubleInitial(DoubleListNode* head) {

    DoubleListNode* HeadNode = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    if (HeadNode == NULL) { 
        printf("새 노드 동적 할당 실패!\n"), exit(1); 
    }
    
    // 헤더 노드의 data 멤버를 노드 개수로 사용
    HeadNode->data = 0; 
    HeadNode->Llink = HeadNode;
    HeadNode->Rlink = HeadNode;

    return HeadNode;
}

// 이중 연결 리스트 제일 앞 노드 생성 (= 1번째 노드로 생성) (<-> 비슷하지만, 경우의 수 없이도 코드 구현)  
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoubleListElement item) {

    DoubleListNode* NewNode = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    if (NewNode == NULL) {
        printf("새 노드 동적 할당 실패!\n"), exit(1); 
    }
    
    NewNode->data = item;
    NewNode->Llink = head;
    NewNode->Rlink = head->Rlink;

    head->data++;

    // 해당 2중 연결리스트의 노드가 없다면 해당 Llink는 head 자신의 Llink를 의미하며, 다른 노드가 있다면 원래 1번째 노드의 Llink의 값을 의미하며, 이를 NewNode의 주소값으로 넣는것
    head->Rlink->Llink = NewNode;   // head->Rlink->Llink 이런식의 참조도 괜찮음
    head->Rlink = NewNode;

    return head;
}

// 이중 연결 리스트 제일 앞 노드 삭제 (= 1번째 노드로 삭제) (<-> 비슷하지만, 경우의 수 없이도 코드 구현)
//  - 다른점 : head->Rlink->Llink 이런식으로 조건 설정을 복잡히 하지 않고, 노드명 대신 역참조를 활용하여 필요한 주소값 변경을 쉽게 함
void DoubleDeleteFirst(DoubleListNode* head) {

    DoubleListNode* DeleteNode = head->Rlink;

    // 삭제할 노드의 위치가 head 자신을 가르키고 있는 경우 (= 현재 리스트에 존재하는 노드가 헤더노드 혼자일 경우)
    if (DeleteNode == head) {
        return;
    }
    
    // 삭제대상 노드의 왼노드의 오른쪽 주소값을 삭제대상노드 오른노드의 주소값으로 변경
    DeleteNode->Llink->Rlink = DeleteNode->Rlink;

    // 삭제대상 노드의 오른노드의 왼쪽 주소값을 삭제대상노드 왼노드의 주소값으로 변경
    DeleteNode->Rlink->Llink = DeleteNode->Llink;

    free(DeleteNode);

    head->data--;

}

// 두 이중 연결리스트 head1, head2를 하나의 이중연결리스트로 결합 (<-> 내가 for문으로 각 리스트의 끝을 복잡하게 찾은거랑 달리, head->Rlink->Llink 이런식의 참조를 통해 나보다 더 간결하게 표현)
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2) {//list 1 + list 2 이어 붙이기

    if (head1 == NULL || head1->Rlink == head1 ) {

        return head2;

    }else if (head2 == NULL || head2->Rlink == head2) {

        return head1;

    }else {

        // 1. head1의 왼노드 주소값을 head2의 마지막 노드의 주소값으로 변경 
        head1->Llink = head2->Llink;

        // 2. head1의 끝노드의 오른노드 주소값을 head2의 1번째 노드의 주소값으로 변경 
        head1->Llink->Rlink = head2->Rlink;

        // 3. head2의 1번째 노드의 왼노드 주소값을 head1의 마지막 노드의 주소값으로 변경
        head2->Rlink->Llink = head1->Llink;
        
        // 4. head2의 마지막 노드의 오른노드 주소값을 head1의 주소값으로 변경
        head2->Llink->Rlink = head1;

        //각 리스트의 노드의 수 변경
        head1->data = head1->data + head2->data;
        head2->data = 0;

        // head2의 헤드노드의 좌우노드 정보값을 헤드노드 스스로의 주소값으로 변경 (난 이거 안하고, 그냥 메모리 해제함)
        head2->Llink = head2;
        head2->Rlink = head2;

        return head1;
    }
}

// 이중 연결리스트 순차 출력 (<-> for문을 사용했지만, 나는 data의 수를 사용)
void DoubleDisplay(DoubleListNode* head) {

    DoubleListNode* pNode;

    for (pNode = head->Rlink; pNode != head; pNode = pNode->Rlink) {
        printf("<--| Node Left : %10p | Node : %10p [%3d] | Node Right : %10p |-->\n", pNode->Llink, pNode, pNode->data, pNode->Rlink);
    }
    printf("\n");
}


// 이중 연결리스트 역순 출력 (<-> for문을 사용했지만, 나는 data의 수를 사용)
void DoubleDisplayReverse(DoubleListNode* head) {

    DoubleListNode* pNode;

    for (pNode = head->Llink; pNode != head; pNode = pNode->Llink) {
        printf("<--| Node Left : %10p | Node : %10p [%3d] | Node Right : %10p |-->\n", pNode->Llink, pNode, pNode->data, pNode->Rlink);
    }
    printf("\n");
}

// 이중 연결리스트 전체 메모리 할당 해제 (<-> while 대신 for문 사용.. 변수 설정 다름)
//  - 다른점1 : while 대신 for문 사용.. 
//  - 다른점2 : 내가 삭제할녀석(함수 지역변수), 다음주소(반복 지역변수) <-> 삭제할녀석(반복 지역변수), 다음주소(반복 지역변수)
void FreeDoubleList(DoubleListNode* head) {

    // pNode가 현재 노드
    DoubleListNode* pNode, * DeleteNode;

    // pNode를 head->Rlink로 정의하고,  pNode가 head가 아닐때까지 반복 (for문을 while처럼 사용)
    for (pNode = head->Rlink; pNode != head; ) {

        DeleteNode = pNode;
        pNode = pNode->Rlink;

        free(DeleteNode);
    }

    free(head);
}

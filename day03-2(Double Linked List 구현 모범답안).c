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

// ���� ���� ����Ʈ �ʱ�ȭ (��� ��� ����)
DoubleListNode* DoubleInitial(DoubleListNode* head);

// ���� ���� ����Ʈ ���� �� ��� ����
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoubleListElement item);

// ���� ���� ����Ʈ ���� �� ��� ���� 
void DoubleDeleteFirst(DoubleListNode* head);

// ���� ���� ����Ʈ ���� list1 + list2
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2);

// ���� ���� ����Ʈ ������ ���
void DoubleDisplay(DoubleListNode* head);

// ���� ���� ����Ʈ ������ ���
void DoubleDisplayReverse(DoubleListNode* head);

// ���� ���� ����Ʈ ��ü ����
void FreeDoubleList(DoubleListNode* head);

int main() {

    srand((unsigned)time(NULL));

    int menu = 0, list_num = 0;

    DoubleListElement value, select_1, select_2;

    // �����迭 ����
    DoubleListNode* head[5] = { 0 };

    // �����迭 ����
    //DoubleListNode** head = NULL;
    //printf("����Ʈ ���� ���� �Է� : ");
    //scanf_s("%d", &list_num);
    //head = (DoubleListNode*)malloc(sizeof(DoubleListNode*) * list_num);

    for (int i = 0; i < 5; i++) {

        head[i] = DoubleInitial(head[i]);
        for (int j = 0; j < 5; j++) head[i] = DoubleInsertFirst(head[i], rand() % 5000 + 1);
    }

    while (1) {

        printf("[ ���� %d �� Doubly Linked List ] \n", select);
        printf("1. Select List\n");
        printf("2. Insert List\n");
        printf("3. Delete List\n");
        printf("4. Forward Print List\n");
        printf("5. Reverse Print List\n");
        printf("6. Concatenate List\n");
        printf("1~6 �� ��� ����\n");
        printf("�޴��� �Է� �ϼ���. :");

        scanf_s("%d", &menu);
        while (getchar() != '\n');

        switch (menu) {

            case 1:
                printf("List ��ȣ�� �Է��ϼ���. (1~5) : ");

                scanf_s("%d", &value);
                while (getchar() != '\n');

                if (value >= 0 && value < 5) {
                    select = value;
                    printf("���� %2d �� ����Ʈ \n", select);
                }
                else {
                    printf("�߸� �Է��߽��ϴ�.\n");
                    printf("���� %2d �� ����Ʈ \n", select);
                }
                break;
            case 2:
                printf("���� �Է��ϼ���. : ");

                scanf_s("%d", &value);
                while (getchar() != '\n');

                head[select] = DoubleInsertFirst(head[select], value);
                printf("%d ���� �־����ϴ�.\n", value);

                break;
            case 3:
                printf("���� �����մϴ�.\n");
                DoubleDeleteFirst(head[select]);
                break;
            case 4:
                printf("������ �� ���\n");
                DoubleDisplay(head[select]);
                break;
            case 5:
                printf("������ �� ���\n");
                DoubleDisplayReverse(head[select]);
                break;
            case 6:
                printf("���� �� List ��ȣ�� �Է��ϼ���. (1~5) : \n");

                scanf_s("%d", &select_1);
                while (getchar() != '\n');

                printf(" [ %2d List ���� ]\n", select_1);

                printf(" %2d List�� ���� �� List ��ȣ�� �Է��ϼ���. (1~5) :", select_1);

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

// ���� ���� ����Ʈ �ʱ�ȭ (= ��� ��� ����) (= ���� ��� ����) 
DoubleListNode* DoubleInitial(DoubleListNode* head) {

    DoubleListNode* HeadNode = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    if (HeadNode == NULL) { 
        printf("�� ��� ���� �Ҵ� ����!\n"), exit(1); 
    }
    
    // ��� ����� data ����� ��� ������ ���
    HeadNode->data = 0; 
    HeadNode->Llink = HeadNode;
    HeadNode->Rlink = HeadNode;

    return HeadNode;
}

// ���� ���� ����Ʈ ���� �� ��� ���� (= 1��° ���� ����) (<-> ���������, ����� �� ���̵� �ڵ� ����)  
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoubleListElement item) {

    DoubleListNode* NewNode = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    if (NewNode == NULL) {
        printf("�� ��� ���� �Ҵ� ����!\n"), exit(1); 
    }
    
    NewNode->data = item;
    NewNode->Llink = head;
    NewNode->Rlink = head->Rlink;

    head->data++;

    // �ش� 2�� ���Ḯ��Ʈ�� ��尡 ���ٸ� �ش� Llink�� head �ڽ��� Llink�� �ǹ��ϸ�, �ٸ� ��尡 �ִٸ� ���� 1��° ����� Llink�� ���� �ǹ��ϸ�, �̸� NewNode�� �ּҰ����� �ִ°�
    head->Rlink->Llink = NewNode;   // head->Rlink->Llink �̷����� ������ ������
    head->Rlink = NewNode;

    return head;
}

// ���� ���� ����Ʈ ���� �� ��� ���� (= 1��° ���� ����) (<-> ���������, ����� �� ���̵� �ڵ� ����)
//  - �ٸ��� : head->Rlink->Llink �̷������� ���� ������ ������ ���� �ʰ�, ���� ��� �������� Ȱ���Ͽ� �ʿ��� �ּҰ� ������ ���� ��
void DoubleDeleteFirst(DoubleListNode* head) {

    DoubleListNode* DeleteNode = head->Rlink;

    // ������ ����� ��ġ�� head �ڽ��� ����Ű�� �ִ� ��� (= ���� ����Ʈ�� �����ϴ� ��尡 ������ ȥ���� ���)
    if (DeleteNode == head) {
        return;
    }
    
    // ������� ����� �޳���� ������ �ּҰ��� ��������� ��������� �ּҰ����� ����
    DeleteNode->Llink->Rlink = DeleteNode->Rlink;

    // ������� ����� ��������� ���� �ּҰ��� ��������� �޳���� �ּҰ����� ����
    DeleteNode->Rlink->Llink = DeleteNode->Llink;

    free(DeleteNode);

    head->data--;

}

// �� ���� ���Ḯ��Ʈ head1, head2�� �ϳ��� ���߿��Ḯ��Ʈ�� ���� (<-> ���� for������ �� ����Ʈ�� ���� �����ϰ� ã���Ŷ� �޸�, head->Rlink->Llink �̷����� ������ ���� ������ �� �����ϰ� ǥ��)
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2) {//list 1 + list 2 �̾� ���̱�

    if (head1 == NULL || head1->Rlink == head1 ) {

        return head2;

    }else if (head2 == NULL || head2->Rlink == head2) {

        return head1;

    }else {

        // 1. head1�� �޳�� �ּҰ��� head2�� ������ ����� �ּҰ����� ���� 
        head1->Llink = head2->Llink;

        // 2. head1�� ������� ������� �ּҰ��� head2�� 1��° ����� �ּҰ����� ���� 
        head1->Llink->Rlink = head2->Rlink;

        // 3. head2�� 1��° ����� �޳�� �ּҰ��� head1�� ������ ����� �ּҰ����� ����
        head2->Rlink->Llink = head1->Llink;
        
        // 4. head2�� ������ ����� ������� �ּҰ��� head1�� �ּҰ����� ����
        head2->Llink->Rlink = head1;

        //�� ����Ʈ�� ����� �� ����
        head1->data = head1->data + head2->data;
        head2->data = 0;

        // head2�� ������� �¿��� �������� ����� �������� �ּҰ����� ���� (�� �̰� ���ϰ�, �׳� �޸� ������)
        head2->Llink = head2;
        head2->Rlink = head2;

        return head1;
    }
}

// ���� ���Ḯ��Ʈ ���� ��� (<-> for���� ���������, ���� data�� ���� ���)
void DoubleDisplay(DoubleListNode* head) {

    DoubleListNode* pNode;

    for (pNode = head->Rlink; pNode != head; pNode = pNode->Rlink) {
        printf("<--| Node Left : %10p | Node : %10p [%3d] | Node Right : %10p |-->\n", pNode->Llink, pNode, pNode->data, pNode->Rlink);
    }
    printf("\n");
}


// ���� ���Ḯ��Ʈ ���� ��� (<-> for���� ���������, ���� data�� ���� ���)
void DoubleDisplayReverse(DoubleListNode* head) {

    DoubleListNode* pNode;

    for (pNode = head->Llink; pNode != head; pNode = pNode->Llink) {
        printf("<--| Node Left : %10p | Node : %10p [%3d] | Node Right : %10p |-->\n", pNode->Llink, pNode, pNode->data, pNode->Rlink);
    }
    printf("\n");
}

// ���� ���Ḯ��Ʈ ��ü �޸� �Ҵ� ���� (<-> while ��� for�� ���.. ���� ���� �ٸ�)
//  - �ٸ���1 : while ��� for�� ���.. 
//  - �ٸ���2 : ���� �����ҳ༮(�Լ� ��������), �����ּ�(�ݺ� ��������) <-> �����ҳ༮(�ݺ� ��������), �����ּ�(�ݺ� ��������)
void FreeDoubleList(DoubleListNode* head) {

    // pNode�� ���� ���
    DoubleListNode* pNode, * DeleteNode;

    // pNode�� head->Rlink�� �����ϰ�,  pNode�� head�� �ƴҶ����� �ݺ� (for���� whileó�� ���)
    for (pNode = head->Rlink; pNode != head; ) {

        DeleteNode = pNode;
        pNode = pNode->Rlink;

        free(DeleteNode);
    }

    free(head);
}

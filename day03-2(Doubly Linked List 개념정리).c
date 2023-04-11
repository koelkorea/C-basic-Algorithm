// ���� ���� ����Ʈ(Doubly Linked List)
//  : head�� �����ؼ� �� ����� link�� ���� ��ũ(Llink)�� ������ ��ũ(Rlink)�� ���� ����, ��������� ��� ��尡 �������� ����Ǿ� �ִ� ����Ʈ

//  # ������ ��ũ�� ����, ������ ��ũ�� �ļ� ��带 ����
//  # ��� ���� link�� ���� ���� ���� (value = null) <-> linked list�� head ������

//  # Double list ����ü ( ���� ��� )

//		typedef int DlistElement;
	 
//		typedef struct DlistNode {
// 
//		    DlistElement data;
//		    struct DlistNode* Llink;
//		    struct DlistNode* Rlink;
//		} DlistNode;

//  # ���� ���� ����Ʈ(Doubly Linked List) ADT
//    - DoubleListNode* DoubleInitial(DoubleListNode* head) : �ʱ�ȭ
//    - DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoubleListElement item) : ��� ����
//    - void DoubleDeleteFirst(DoubleListNode* head) : ��� ����
//    - DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2) : ���� list1 + list2
//    - void DoubleDisplay(DoubleListNode * head)       :  ������ ���
//    - void DoubleDisplayReverse(DoubleListNode* head) : ������ ���
//    - void FreeDoubleList(DoubleListNode* head)       : ����Ʈ ��ü ����

// ���� ���� ����Ʈ ADT ���� �����غ���
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��

typedef int DoublelistElement;
typedef struct DlistNode {

    DoublelistElement data;
    struct DoublelistNode* Llink;
    struct DoublelistNode* Rlink;
} DoubleListNode;

DoubleListNode* DoubleInitial(DoubleListNode* head);
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoublelistElement item);
void DoubleDeleteFirst(DoubleListNode* head);
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2);
void DoubleDisplay(DoubleListNode * head);
void DoubleDisplayReverse(DoubleListNode* head);
void FreeDoubleList(DoubleListNode* head);

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

    DoubleDeleteFirst(double_list1);
    DoubleDeleteFirst(double_list1);

    DoubleDisplay(double_list1);
    DoubleDisplay(double_list2);

    double_concat_list = DoubleConcat(double_list1, double_list2);
    DoubleDisplay(double_concat_list);

    return 0;
}

// ����ũ�� ����Ʈ head ��� ����(= ��ǻ� �Է�����)
DoubleListNode* DoubleInitial(DoubleListNode* head) {

    DoubleListNode* head_node = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    // ����� ������ ���� ����� �� ���� (���鶧�� �翬�� �� ������ 0)
    head_node->data = 0;
    head_node->Llink = head_node;
    head_node->Rlink = head_node;

    printf_s("(dl ���� �ʱ�ȭ) : %d�� ����ũ�� ����Ʈ�� ����尡 �߰��Ǿ����ϴ�. �ش� �ּҰ��� %d�� ��ġ�� ��ϵǾ� �ֽ��ϴ�. \n", head_node, &head);

    head = head_node;

    return head;
}

// �ش� head�� ����Ű�� ����ũ�� ����Ʈ�� 1��° ���� item�� �߰�
DoubleListNode* DoubleInsertFirst(DoubleListNode* head, DoublelistElement item) {

    DoubleListNode* insert_first_node = (DoubleListNode*)malloc(sizeof(DoubleListNode));

    if (insert_first_node == NULL) {
        printf("�޸� ����");
        return NULL;
    }

    insert_first_node->data = item;
    insert_first_node->Llink = head;

    // (case1) ���� ����Ʈ�� �����ϴ� ��尡 ������ ȥ���� ���? (= �������� ��link�� �����θ� ����Ŵ)
    //  -> �������� �� link�� ���� insert_first_node�� �ּҰ����� + insert_first_node ������ �ּҵ� head�� ����Ű�� ��
    if (head->Llink == head && head->Rlink == head) {

        head->Llink = insert_first_node;
        head->Rlink = insert_first_node;

        insert_first_node->Rlink = head;
    }

    // (case2) �ش� ����ũ�� ����Ʈ�� �ٸ� ������ �ִ� ��� (= ������� ������link�� �ٸ� ��带 ����ų���)
    //  -> insert_first_node ������ �ּҰ� head�� ������link�� ������ �� + �������� ������ link���� insert_first_node�� ����
    if (head->Rlink != head) {

        insert_first_node->Rlink = head->Rlink;
        head->Rlink = insert_first_node;
    }

    // ����� ������ ���� ����� �� ����
    head->data++;

    return head;
}

// �ش� head�� ����Ű�� ����ũ�� ����Ʈ�� 1��° ��� ����
void DoubleDeleteFirst(DoubleListNode* head) {

    DoubleListNode* delete_node = head->Rlink;

    printf_s("\n\n------------------------------[DoubleDeleteFirst ����!]------------------------------\n\n");

    // (case1) ���� ����Ʈ�� �����ϴ� ��尡 ������ ȥ���� ���? (= �������� ��link�� �����θ� ����Ŵ)
    //  -> ��� ������
    if (head->Llink == head && head->Rlink == head && head->data == 0) {

        printf_s("(���) : �ش� ����ũ�� ����Ʈ���� ��� �ܿ� �ٸ� ��尡 ��� ������ �Ұ����մϴ�.\n");
    }
    // (case2) �ش� ����ũ�� ����Ʈ�� 1��° ��常 �ִ� ��� (= ������� ������link�� head�� �����ϴ� �ּҰ��� ����ų��� or head�� data�� 1)
    //  -> head�� Rlink�� ������ 1��° ����� head�� �ּҰ��� ������ ��
    else if (delete_node->Rlink == head && head->data == 1) {
        head->Rlink = head;

        printf_s("�ش� ����Ʈ�� �ּ� %d�� ��ġ�� 1��° ����� data�� %d �����Ϸ�! \n", delete_node, delete_node->data);
        free(delete_node);
    }

    // (case3) �ش� ����ũ�� ����Ʈ�� 2�� �̻��� ��� ���� (= 1��°����� ������link�� head�� ����ų��� or head�� data�� 1�ʰ�)
    //  -> head�� Rlink�� ������ 1��° ����� Rlink�� �ּҰ��� ������ ��
    else if (delete_node->Rlink != head && head->data > 1) {
        head->Rlink = delete_node->Rlink;

        printf_s("�ش� ����Ʈ�� �ּ� %d�� ��ġ�� 1��° ����� data�� %d �����Ϸ�! \n", delete_node, delete_node->data);
        free(delete_node);
    }

    // ����� ������ ���� ����� �� ����
    head->data--;
    printf_s("�ش� ����Ʈ�� �ּ� %d�� ��ġ�� ��� �� ���� : %d \n", head, head->data);
}

// �ΰ��� ����ũ�� ����Ʈ head1, head2 ����
DoubleListNode* DoubleConcat(DoubleListNode* head1, DoubleListNode* head2) {

    // (case1) 1��° ����ũ�� ����Ʈ�� ��尡 ����ۿ� ���ٸ�?
    // -> concat����� ��ü�� head2�� ���� (head2�� ���������� ����� ����)
    if (head1->data == 0) {
        return head2;
    }

    // (case2) 2��° ����ũ�� ����Ʈ�� ��尡 ����ۿ� ���ٸ�?
    // -> concat����� ��ü�� head1�� ����
    if (head2->data == 0) {
        return head1;
    }

    // (�߿�!) 1�� ���Ḯ��Ʈ�� head�� data�� ǥ��� ����� ���� + 2�� ���Ḯ��Ʈ�� head��  data�� ǥ��� ����� ���ڰ� �� �� 0�� �ƴϸ� concat����

    // current_head1_index : 1�� ���Ḯ��Ʈ�� ������ ����� �ּҸ� �˾Ƴ��� ���� ListNode�� �ּҰ��� �޴� �����ͺ���
    DoubleListNode* current_head1_index = head1;

    // current_head1_index(������ ��� �ּҰ�)�� ��ġ�� link�� null�� ���ö�����(= current_head1_index�� ������ ����� �ּҰ��� ��Ÿ��������)... ��� ����
    for (int i = 1; i <= head1->data; i++) {

        printf_s("�����ּ�.. %d -> %d��..\n", current_head1_index, current_head1_index->Rlink);

        // current_head1_index(������ ��� �ּҰ�)�� ��ġ�� Rlink�� head1�� �ּҰ��� ����Ű�� �ʴ��̻� current_head1_index->Rlink�� current_head1_index�� ������ ����
        if (current_head1_index->Rlink == head1) {
            break;
        }
        else {
            current_head1_index = current_head1_index->Rlink;
        }
    }

    // current_head2_index : 2�� ���Ḯ��Ʈ�� ������ ����� �ּҸ� �˾Ƴ��� ���� ListNode�� �ּҰ��� �޴� �����ͺ���
    DoubleListNode* current_head2_index = head2;

    // current_head2_index(������ ��� �ּҰ�)�� ��ġ�� link�� null�� ���ö�����(= current_head1_index�� ������ ����� �ּҰ��� ��Ÿ��������)... ��� ����
    for (int i = 1; i <= head2->data; i++) {

        printf_s("�����ּ�.. %d -> %d��..\n", current_head2_index, current_head2_index->Rlink);

        // current_head1_index(������ ��� �ּҰ�)�� ��ġ�� Rlink�� head1�� �ּҰ��� ����Ű�� �ʴ��̻� current_head1_index->Rlink�� current_head1_index�� ������ ����
        if (current_head2_index->Rlink == head2) {
            break;
        }
        else {
            current_head2_index = current_head2_index->Rlink;
        }
    }

    // head1�̾��� current_head1_index(������ ��� �ּҰ�)�� ��ġ�� link���� 2�� ���Ḯ��Ʈ�� head�� ��Ÿ���� 1��°����� �ּҰ��� head2->Rlink�� ����
    current_head1_index->Rlink = head2->Rlink;

    DoubleListNode* second_dlist_1st_node = head2->Rlink;

    // head2�� 1��° ����� Llink���� head�� ������ ����� �ּҰ����� ����
    second_dlist_1st_node->Llink = current_head1_index;

    // 1�� ���Ḯ��Ʈ�� ��� ����� ����link �ּҰ��� 2�� ���Ḯ��Ʈ ����������� �ּҷ� ����
    head1->Llink = current_head2_index;

    // 2�� ���Ḯ��Ʈ ����������� ������link 1�� ���Ḯ��Ʈ�� ��� ����� �ּҷ� ����
    current_head2_index->Rlink = head1;

    // �� ���� �����ϱ�
    head1->data = head1->data + head2->data;

    // ���̻� �������� �������� ������
    free(head2);
    head2 = NULL;

    printf_s("----------------------------[concat ���̱� �Ϸ�] : head1�� ������ link�� = %d -> %d(%d)��.. ����-----------------------------\n", head1, current_head1_index->Rlink);

    // 1��, 2�� ������ �Ϸ�� ���Ḯ��Ʈ�� �������� 1�� ���Ḯ��Ʈ�� ��尪�� ���� concat_head����
    return head1;

}

// ����ũ�� ����Ʈ�� ��� ����� data�� ���������� ���
void DoubleDisplay(DoubleListNode* head) {

    printf_s("\n\n------------------------------[�ּҰ� %d display ����!]------------------------------\n\n", head);

    if (head->data == 0) {

        printf_s("(���) : �ش� ����ũ�� ����Ʈ���� ��� �ܿ� �ٸ� ��尡 �����ϴ�.\n");

    }
    else {

        printf("�ش� dlist ��� %d�� ���� ��� : ", head->data);

        DoubleListNode* current_node = head->Rlink;

        printf("head\n");

        for (int i = 1; i <= head->data; i++) {

            printf("%3d -> ", current_node->data);
            current_node = current_node->Rlink;
        }

        printf("head\n");
    }
}
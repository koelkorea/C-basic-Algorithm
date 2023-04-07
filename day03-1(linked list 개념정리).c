// ���� ����Ʈ(Linked List)
//  : ����ü�� �� �ٷ� ���� ��Ų ������ ���� (= ����ü�� �׷�ȭ)
//     -> �����Ϳ� �����͸� �� ������ ������ �� �ٷ� ����� �ڷᱸ��

//  # ����
//   1. �迭 : ���� �ڷ����� �׷�
//   2. ����ü : �پ��� �ڷ����� ������

//  # list ����ü (���� ���)
//     typedef int list_element;

//     typedef struct ListNode {
// 
//         list_element data;           <- ����Ʈ�� ��
//         struct ListNode* link;       <- ���� ����Ʈ ��Ұ� ��ġ�� �ּ�
//     } ListNode;

//  # ���Ḯ��Ʈ�� �������
//    - �Ӹ�(Head) : ���� ����Ʈ���� ù��° ����� �ּҸ� ������ ������
//    - ���(Node) : ���� ����Ʈ�� ���
//    - ��(Value)  : ��忡 ����� ������
//    - ����(Link) : �ٸ� ���� ������ ���� ������

//  # ���Ḯ��Ʈ�� ����
//   1. �ܼ� ���� ����Ʈ(Singly Linked List)
//      : �� ����� link�� ���� ����� �ּҰ� ����. ������ ����� link�� NULL ��.


//   2. ���� ���� ����Ʈ(Circular Linked List)
//      : �� ����� link�� ���� ����� �ּҰ� �ִ�. ������ ����� link�� ����� �ּҰ�.


//  # ���� ����Ʈ ADT(Abstract data type(�߻��� ������ ����) = �ڷ� ������ ��� �ٷ���, ����� ������ �����ϰ� ��üȭ ����)
//    - insert_first(list, item) : �� �տ� Node �߰�
//    - delete_first(list) �� �տ� Node ����
//    - search(list, item) : item�� list �ȿ� �ִ��� Ȯ��
//    - concat(list1, list2) : list1�� list2�� ����
//    - reverse(list1) : list1�� ��� ���θ� �ݴ�� ����
//    - display(list) : ����Ʈ�� ��� ��Ҹ� ǥ��
//    - insert_last(list, item) : �� �ڿ� Node �߰�
//    - delete_lsat(list) �� �ڿ� Node ����

// ���� ����Ʈ ADT ���� �����غ���
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��

typedef int list_element;

typedef struct ListNode {

    list_element data;
    struct ListNode* link;
} ListNode;

// �� ��,�� �� Node �߰�
ListNode* insert_first(ListNode* head, list_element item);
ListNode* insert_last(ListNode* head, list_element item);

// �� ��,�� �� Node ����
ListNode* delete_first(ListNode* head);
ListNode* delete_lsat(ListNode* head);

// item�� list �ȿ� �ִ��� Ȯ��
ListNode* search(ListNode* head, list_element item);

// list1�� list2�� ����
ListNode* concat(ListNode* head1, ListNode* head2);

// list1�� ��� ���θ� �ݴ�� ����
ListNode* reverse(ListNode* head);

// ����Ʈ�� ��� ��Ҹ� ǥ��
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

// �� �տ� Node �߰�(���� ���� �༮�� �ڷ� �и��� ���)
ListNode* insert_first(ListNode* head, list_element item) {

    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));

    if (Newnode == NULL) {
        printf("�޸� ����");
        return NULL;
    }
    
    Newnode->data = item;
    Newnode->link = head;

    head = Newnode;

    return head;
}

// item�� list �ȿ� �ִ��� Ȯ��
ListNode* search(ListNode* head, list_element item) {

    ListNode* address = NULL;
    printf_s("\nhead����.. %d\n", head);

    while(head != NULL){

        if (head->data == item) {

            address = head;
            printf_s("�˻��� ���� %d : �޸��ּ� %d�� ����", item , address);
            break;
        }
        else {
            head = head->link;
            printf_s("�����ּҷ�.. %d��..\n", head);
        }
    }
    
    return address;
}

// list1�� list2�� ����
ListNode* concat(ListNode* head1, ListNode* head2) {

    printf_s("\nhead1����.. %d\n", head1);

    while (head1 != NULL) {

        ListNode* head1_original = head1;
        ListNode* temp = head1->link;

        if (temp == NULL) {

            head1 = head2;

            printf_s("head1�� ������ link�� = %d -> %d(%d)��..\n", head1_original, head1, head2);
            break;
        }

        head1 = temp;

        printf_s("�����ּ�.. %d -> %d��..\n", head1_original ,head1);
    }

    return head1;
    
}



// �� ���� Node ����
ListNode* delete_first(ListNode* head) {

    ListNode* delete = head;

    if (head == NULL) {

        return NULL;
    }

    head = head->link;

    free(delete);

    return head;
}

// ����Ʈ�� ��� ��Ҹ� ǥ��
void display(ListNode* head) {

    printf("list ��� : ");
    while (head) {
        printf("%3d -> ", head->data);
        head = head->link;
    }
    printf("NULL\n");
}
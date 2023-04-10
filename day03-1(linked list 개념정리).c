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
//    - �Ӹ�(Head) : ���� ����Ʈ���� ù��° ����� �ּҸ� ������ ������ (= ���Ḯ��Ʈ�� �����Ϸ���, �ϴ� ����� �ּҰ��� ��ġ�� ���� �������ؾ� ��)
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
ListNode* insert_first(ListNode* head, list_element item);   // done
ListNode* insert_last(ListNode* head, list_element item);    // done

// ������ ���ο� �ΰ� �߰� (�̰� �ܵ����� ����Ʈ)
ListNode* insert_sort(ListNode* head, list_element item);

// �� ��,�� �� Node ����
ListNode* delete_first(ListNode* head);                      // done
ListNode* delete_last(ListNode* head);                       // done
int delete_search(ListNode** head, list_element value);      // done

// item�� list �ȿ� �ִ��� Ȯ��
ListNode* search(ListNode* head, list_element item);         // done

// list1�� list2�� ����
ListNode* concat(ListNode* head1, ListNode* head2);          // done

// list1�� ��� ���θ� �ݴ�� ����
ListNode* reverse(ListNode* head);                           // done

// ����Ʈ�� ��� ��Ҹ� ǥ��
void display(ListNode* head);                                // done

// �ش� ����������� �޸𸮸� �����ϴ� �Լ�
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

        printf("[�˻� ���� ����]\n");
        display(head2);

    }

    // concat (����) ����
    head1_2 = concat(head1, head2);
    head1_2 = delete_last(head1_2);
    display(head1_2);

    // reverse (����) ����
    head1_2 = reverse(head1_2);
    display(head1_2);

    // search (�˻�) ����
    search_address = search(head1_2, 100);

    // insert_sort(���� �߰�) ���� 
    for (int i = 1; i <= 10; i += 1) {

        head3 = insert_sort(head3, rand() % 10);
    }
    display(head3);

    return 0;
}

// �� �տ� Node �߰�(���� ���� �༮�� �ڷ� �и��� ���)
ListNode* insert_first(ListNode* head, list_element item) {

    // ���ο� �� ���� ����� �����͸� ���� �ּҰ��� ����� �˱� ����, ListNode�� ����Ʈ������ �޸𸮸� �Ҵ���
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));

    // ��带 ���� ������ ���ٸ�?? ���� ����
    if (Newnode == NULL) {
        printf("�޸� ����");
        return NULL;
    }
    
    // ListNode �����ͺ��� Newnode�� �޸� ������ �������ϴ� ���� head, item�� �ǵ��� ��
    Newnode->data = item;
    Newnode->link = head;       // head�� NULL�̶� ū ��������(= ������ �� ��尡 �������̶�� �ǹ̰� ����)

    // ���� ù ����� �ּҰ��� �����ϴ� Head�� �ּҰ��� ListNode �����ͺ��� Newnode�� ����
    head = Newnode;

    return head;
}

// �� �ڿ� Node �߰�(���� ���� �༮�� �ڷ� �и��� ���)
ListNode* insert_last(ListNode* head, list_element item) {

    // ���ο� �� ���� ����� �����͸� ���� �ּҰ��� ����� �˱� ����, ListNode�� ����Ʈ������ �޸𸮸� �Ҵ���
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));
    ListNode* insert_address = head;

    // ��带 ���� ������ ���ٸ�?? ���� ����
    if (Newnode == NULL) {
        printf("�޸� ����");
        return NULL;
    }

    while (insert_address->link != NULL) {

        printf_s("\n��Ұ� : %d", insert_address->data);

        insert_address = insert_address->link;

        printf_s(" -> %d\n", insert_address->data);
    }

    insert_address->link = Newnode;

    // ListNode �����ͺ��� Newnode�� �޸� ������ �������ϴ� ���� head, item�� �ǵ��� ��
    Newnode->data = item;
    Newnode->link = NULL;       

    return head;
}

// �� �ڿ� Node �߰�(���� ���� �༮�� �ڷ� �и��� ���)
ListNode* insert_sort(ListNode* head, list_element item) {

    // ���ο� �� ���� ����� �����͸� ���� �ּҰ��� ����� �˱� ����, ListNode�� ����Ʈ������ �޸𸮸� �Ҵ���
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));
    ListNode* insert_address = head;
    ListNode* front_link_address = NULL;

    // ��带 ���� ������ ���ٸ�?? ���� ����
    if (Newnode == NULL) {
        printf("�޸� ����");
        return NULL;
    }

    if (insert_address == NULL) {

        return insert_first(head, item);
    }
    else {

        while (insert_address->link != NULL) {

            if (insert_address->data >= item) {
                printf_s("\n�Է°� %d���� ū �� %d ����", item, insert_address->data);
                break;
            }

            printf_s("\n��Ұ� : %d", insert_address->data);

            front_link_address = insert_address;
            insert_address = insert_address->link;

            printf_s(" -> %d\n", insert_address->data);
        }

        // ListNode �����ͺ��� Newnode�� �޸� ������ �������ϴ� ���� head, item�� �ǵ��� ��
        Newnode->data = item;
        Newnode->link = front_link_address;

        front_link_address = Newnode;

    }

    return head;
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

// �� ���� Node ����
ListNode* delete_last(ListNode* head) {

    ListNode* delete_address = head;
    ListNode* new_end_address = NULL;

    if (head == NULL) {

        return NULL;
    }

    while (delete_address->link != NULL) {

        printf_s("\n��Ұ� : %d", delete_address->data);
        new_end_address = delete_address;
        delete_address = delete_address->link;

        printf_s(" -> %d\n", delete_address->data);
    }

    free(delete_address);
    new_end_address->link = NULL;

    return head;
}


// �˻��� ã�Ƽ� ����
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

        printf_s("\n��Ұ� : %d", delete_address->data);
        new_end_address = delete_address;
        delete_address = delete_address->link;

        printf_s(" -> %d\n", delete_address->data);
    }

    new_end_address->link = search_address->link;
    free(search_address);

    return 0;
}


// item�� list �ȿ� �ִ��� Ȯ��
ListNode* search(ListNode* head, list_element item) {

    ListNode* address = NULL;
    printf_s("\n\n[search ����] : head�� ����� ���� �ּҴ�? %d\n", head);

    while(head != NULL){

        if (head->data == item) {

            address = head;
            printf_s("[�˻��� %d ã�� �Ϸ�] : �޸��ּ� %d�� ����\n", item , address);
            break;
        }
        else {
            head = head->link;
            printf_s("[���� �ּ�] : %d��..\n", head);
        }
    }

    return address;
}

// list1�� list2�� ����
ListNode* concat(ListNode* head1, ListNode* head2) {

    printf_s("\nhead1����.. %d\n", head1);

    if (head1 == NULL) {
        return head2;
    }

    if (head2 == NULL) {
        return head1;
    }

    ListNode* head1_index = head1;

    while (head1_index->link != NULL) {

        printf_s("�����ּ�.. %d -> %d��..\n", head1_index, head1_index->link);
        head1_index = head1_index->link;
    }

    head1_index->link = head2;

    printf_s("head1�� ������ link�� = %d -> %d(%d)��..\n", head1_index, head1_index->link, (head2));

    return head1;
    
}

// list1�� ��� ���θ� �ݴ�� ����
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

// ����Ʈ�� ��� ��Ҹ� ǥ��
void display(ListNode* head) {

    printf("list ��� : ");

    while (head) {
        printf("%3d -> ", head->data);
        head = head->link;
    }
    printf("NULL\n");
}
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

//  # ���Ḯ��Ʈ�� ������� : 
//    - �Ӹ�(Head) : ���� ����Ʈ���� ù��° ����� �ּҸ� ������ ������ (= ���Ḯ��Ʈ�� �����Ϸ���, �ϴ� ����� �ּҰ��� ��ġ�� ���� �������ؾ� ��)
//    - ���(Node) : ���� ����Ʈ�� ���
//    - ��(Value)  : ��忡 ����� ������
//    - ����(Link) : �ٸ� ���� ������ ���� ������ -> (�߿�!) ������ ����� link = NULL

//  # ���Ḯ��Ʈ�� ����
//   1. �ܼ� ���� ����Ʈ(Singly Linked List)
//      : �� ����� link�� ���� ����� �ּҰ� ����. 
//        -> Head : 1��°��� �ּҰ� -> 1���� node(value, link :  1��°��� �ּҰ�) -> .... -> n���� node(value, link : Null)

//      # �ܼ� ���� ����Ʈ(Singly Linked List)�� [������ ����� link = NULL]

//   2. ���� ���� ����Ʈ(Circular Linked List)
//      : �� ����� link�� ���� ����� �ּҰ� �־�, �ܹ��������� ��� ��尡 ������ ����Ǿ� �ִ� ����Ʈ
//        -> Head : 1��°��� �ּҰ� -> 1���� node(value, link :  1��°��� �ּҰ�) -> .... -> n���� node(value, link : Head�� �ּҰ�)

//      # ���� ���� ����Ʈ(Circular Linked List)�� [������ ����� link =  head�� �ּҰ�]

//   3. ���� ���� ���� ����Ʈ(Double Circular Linked List)
//      : head�� �����ؼ� �� ����� link�� �����link�� �ĳ��link�� ��ȭ�Ǿ�, ��������� ��� ��尡 �������� ����Ǿ� �ִ� ����Ʈ
//        -> Head : 1��°��� �ּҰ� -> 1���� node(value, link :  1��°��� �ּҰ�) -> .... -> n���� node(value, link : Head�� �ּҰ�)

//      # ���� ���� ���� ����Ʈ(Double Circular Linked List)�� [������ ����� �ĳ�� link = head�� �ּҰ�]
//                                                             [head�� ����� link = ����������� �ּҰ�]


//  # ���� ����Ʈ ADT(Abstract data type(�߻��� ������ ����) = �ڷ� ������ ��� �ٷ���, ����� ������ �����ϰ� ��üȭ ����)
//    - insert_first(list*, item) : �ش� list�� �� �տ� Node �߰�
//    - insert_last(list*, item)  : �ش� list�� �� �ڿ� Node �߰�
//    - insert_sort(list*, item)  : �ش� list���� item�� �ش��ϴ� ���� �߰��ϴµ�, ���������� �´� ������ Node�� �߰�
//    - delete_first(list*)  : �ش� list�� �� �տ� Node ����
//    - delete_last(list*)   : �ش� list�� �� �ڿ� Node ����
//    - delete_search(list*, value) : �ش� list���� item�� �ش��ϴ� ���� ���� ��带 ã�� �����ϰ�, ���� ���а� ����
//    - search(list*, item)  : item�� list �ȿ� �ִ��� Ȯ��
//    - concat(list1*, list2*) : list1�� list2�� ����
//    - reverse(list*) : list1�� ��� ���θ� �ݴ�� ����
//    - display(list*) : �ش� list�� ��� value�� ���������� ��� ǥ��
//    - freelist(list*) : �ش� list�� ���� �Ҵ�� �޸� �ּҸ� �����ϱ�

// ���� ����Ʈ ADT ���� �����غ���
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��

// int��Ī �����ǿ�
typedef int list_element;

// ���Ḯ��Ʈ ���� ��带 �����ϴ� ���� (value, link)
typedef struct ListNode {

    list_element data;
    struct ListNode* link;

} ListNode;

// �� ��,�� �� Node �߰�
ListNode* insert_first(ListNode* head, list_element item);   // done
ListNode* insert_last(ListNode* head, list_element item);    // done

// ������ ���ο� �ΰ� �߰� (�̰� �ܵ����� ����Ʈ)
ListNode* insert_sort(ListNode* head, list_element item);    // done

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

    // head1 : insert_first, delete_first, concat�� �ĸ����ͷ� �׽�Ʈ����
    ListNode* head1 = NULL;

    // head2 : insert_first, insert_last, delete_search, concat�� �ĸ����ͷ� �׽�Ʈ����
    ListNode* head2 = NULL;

    // head3 : insert_sort �׽�Ʈ ����
    ListNode* head3 = NULL;

    // head1 ä��� : insert_first
    for (int i = 100; i > 0; i -= 10) {

        head1 = insert_first(head1, i);
    }
    display(head1);

    // head1 ����� : delete_first
    for (int i = 100; i > 20; i -= 10) {

        head1 = delete_first(head1);
        display(head1);
    }

    // head2 ä��� : insert_first
    for (int i = 1; i <= 1000; i += 100) {

        head2 = insert_first(head2, i);
    }

    // head2 ä��� : insert_last�� 890916��� ���� value�� �ϴ� ��带 �� ���� ���̱�
    head2 = insert_last(head2, 890916);
    display(head2);

    // head2 ����� : delete_search�� 890916��� ���� value�� �ϴ� ��带 ã�� �����, ������� ����
    if (delete_search(head2, 890916) == 0) {

        printf("[�˻� ���� ����]\n");
        display(head2);
    }


    // head1_2 : delete_last, concat, reverse, search�� �Ķ���� �׽�Ʈ����

    // head1_2 ����� : concat (����) �����ؼ�, head1�� head2�� ����
    ListNode* head1_2 = concat(head1, head2);

    // head1_2 ����� : delete_last
    head1_2 = delete_last(head1_2);
    display(head1_2);

    // head1_2 ������� �ٲٱ� : reverse (����) ����
    head1_2 = reverse(head1_2);
    display(head1_2);

    // search_address : search (�˻�) ���� �׽�Ʈ ����(����� ���� �뵵)
    ListNode* search_address = search(head1_2, 100);

    // head3 : insert_sort(���� �߰�) ���� �׽�Ʈ ���� 
    for (int i = 1; i <= 10; i += 1) {

        // �������� ������ 10������ ���� ��带 ����� ä�ﶧ����, �� ��ġ�� ���������� �´� ������ ����
        head3 = insert_sort(head3, rand() % 10);
        display(head3);
    }

    freelist(head1_2);
    freelist(head3);

    return 0;
}

// insert_first : �� �տ� Node �߰�(���� ���� �༮�� �ڷ� �и��� ���)
ListNode* insert_first(ListNode* head, list_element item) {

    printf_s("\n\n------------------------------[insert_first�� %d �ֱ� ����!]------------------------------\n", item);

    // ���ο� �� ���� ����� �����͸� ���� �ּҰ��� ����� �˱� ����, ListNode�� ����Ʈ������ �޸𸮸� �Ҵ���
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));

    // ��带 ���� �޸� ������ ���ٸ�?? ���� ����
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

    printf_s("\n\n------------------------------[insert_last�� %d �ֱ� ����!]------------------------------\n", item);

    // ��带 ���� ������ ���ٸ�?? ���� ����
    if (Newnode == NULL) {
        printf("�޸� ����");
        return NULL;
    }

    while (insert_address->link != NULL) {

        printf_s("\n�� ��� ��Ұ� : %d", insert_address->data);

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

    // ����� ���ο� ListNode�� ������� ������ �����ϱ� ���� �޸� ������ ��ġ�� �ּ��� ���۰��� ����
    ListNode* Newnode = (ListNode*)malloc(sizeof(ListNode));

    // �˻����� ����� data���� ����� ����� item���� Ŭ ���, �ش� ����� ��ġ ������ ����� ����� ��ġ�� �������� ���� ListNode �ּҰ� ����� (�� ��尡 ��ġ�ϴ� �ּҰ� = Newnode�� link��)
    ListNode* insert_arrivial_link_address = head;

    // ����� ��带 1�������� �տ��� �������� ListNode �ּӰ� �����
    ListNode* insert_front_link_address = head;

    // ��尡 �� ��ġ�� ���� data���� ���ϴ� ���� �´°��� �������� ���� ������ 1
    int search_complete_flag = 0;

    printf_s("\n\n------------------------------[insert_sort�� %d �ֱ� ����!]------------------------------\n", item);

    // ��带 ���� ������ ���ٸ�?? ���� ����
    if (Newnode == NULL) {
        printf("�޸� ����");
        return NULL;
    }

    // ---------------------(case1) : ���Ḯ��Ʈ�� �ƹ��͵� �� ����ִ�?-------------------------------------
    //  => Newnode�� �ּҸ� head�� ��������� �� = insert_first�� �����ϰ� �� �ּҰ� ����

    // head�� ����Ű�� �ּҰ��� ���ٸ�? 
    if (insert_arrivial_link_address == NULL) {

        // 1�� ��忡 �����Ű��
        return insert_first(head, item);
    }
    //----------------------------------------------------------------------------------------------------

    // head�� ����Ű�� �ּҰ��� �ִٸ�?
    //  �˻����� ����� data���� ����� ����� ������ �Ǵ� ��ġ���� insert_arrivial_link_address�� null (= ������ ����� ��ġ�� �ٴٸ�������) �� ���ö����� �ݺ�
    while (insert_arrivial_link_address != NULL) {

        // ---------------------(case2) : Newnode�� item���� ���Ḯ��Ʈ�� ��� ����� ������ ������ ����(= ���� ���� ���� 1���� ���� �������� ����)?------------------
        //  => Newnode�� �ּҸ� head�� ��������� �� = insert_first�� �����ϰ� �� �ּҰ� ����

        // @�ԷµǴ� item���� ���� ���� ���� ������ Ȯ���ϴ� ���
        // 1. ���� �˻����� ����� �ְ��� head�� ����Ű�� �ּҰ��� 1���� ����� �ּҰ� ��ġ
        // 2. 1������ Ȯ���� ���� �˻����� ����� �ּҰ�(head)�� value���� item���� ū ���
        if (insert_arrivial_link_address == head && insert_arrivial_link_address->data >= item) {

            printf_s("\n�˻��� %d�� ���� ���� ����� �� %d ���� ����", item, insert_arrivial_link_address->data);
            return insert_first(head, item);
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------

        // ---------------------(case3) : ���Ḯ��Ʈ�� ����� ���� Newnode�� item������ ū�� �����Ѵ�?-------------------------------------------------
        //   => Newnode�� link���� �ش� ����� �ּҰ�(�ش� ������� ����� link�� ���� ������)�� ���� +  Newnode�� �ּҸ� �ش� ������� ����� link�� ����

        // ���� �˻����� ����� �ּҰ��� value���� item���� ū ���
        if (insert_arrivial_link_address->data >= item) {

            printf_s("\n�˻��� %d���� ũ�ų� ���� �� ��� ��Ұ� %d �߰�", item, insert_arrivial_link_address->data);

            // �������� Newnode�� data�� item����
            Newnode->data = item;

            // �������� Newnode�� ���� ����� �ּҰ��� ��Ÿ���� link�� �� = ã�Ƴ� �������� ���� ����� �ּҰ� insert_arrivial_link_address���� �ֱ�
            Newnode->link = insert_arrivial_link_address;

            // ���� �˻����� ����� ���� ����� �ּҰ��� ������ insert_arrivial_link_address�� ���� ����� �ּҰ��� ��Ÿ���� link�� �� = �������� ��� Newnode�� �ּҰ����� �ֱ�
            insert_front_link_address->link = Newnode;

            return head;
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------

        // ---------------------------(case4) : Newnode�� item���� ���Ḯ��Ʈ�� ��� ����� ������ ũ�ų� ����?------------------------------------------
        //   => Newnode�� �ּҸ� ������ ����� link�� ��������� �� insert_last�� �����ϰ� �� �ּҰ� ����

        // @�ԷµǴ� item���� ���� ���� ���� ������ Ȯ���ϴ� ���
        //  -> ���� �˻����� ����� ���� ����� �ּҰ��� ��Ÿ���� link���� ������ ��
        if (insert_arrivial_link_address->link == NULL) {

            return insert_last(head, item);
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------

        // case234�� �� �ɸ���?

        // ���� ������� ������ �Ǵ� ����� �ּҰ��� ã�� insert_front_link_address�� �ּҰ��� insert_front_link_address��� �������� ��带 �տ��� �������� ��尪�� 
        insert_front_link_address = insert_arrivial_link_address;

        // ������� ������ �Ǵ� ����� �ּҰ��� ã�� insert_front_link_address�� �װ� �������ϴ� link������ �����Ͽ�, ������� ��ġ�� �����ؼ� �ٽ� item�� value�� ���踦���ϴ� ������ ź��
        insert_arrivial_link_address = insert_arrivial_link_address->link;
    }

}

// �� ���� Node ����
ListNode* delete_first(ListNode* head) {

    printf_s("\n\n------------------------------[delete_first�� ù��° ��� ���� ����!]------------------------------\n");

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

    printf_s("\n\n------------------------------[delete_last�� ������ ��� ���� ����!]------------------------------\n");

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

    printf_s("\n\n------------------------------[delete_search�� �˻��� %d ���� ��� ���� ����!]------------------------------\n", value);

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

    printf_s("\n\n------------------------------[search ����! : head�� ����� ���� �ּҴ�? %d]------------------------------\n\n", head);

    ListNode* address = NULL;

    while (head != NULL) {

        if (head->data == item) {

            address = head;
            printf_s("*******************[�˻��� %d ã�� �Ϸ�] : �޸��ּ� %d�� ����****************\n", item, address);
            break;
        }
        else {
            head = head->link;
            printf_s("[���� �ּ�] : %d��..\n", head);
        }
    }

    return address;
}

// concat : list1�� list2�� ����
ListNode* concat(ListNode* head1, ListNode* head2) {

    printf_s("\n\n------------------------------[concat ����! : head1, head2 �������]------------------------------\n\n");

    printf_s("\nhead1 ������ġ : %d\n", head1);
    printf_s("\nhead2 ������ġ : %d\n", head2);

    // 1�� ���Ḯ��Ʈ�� head�� ��Ÿ���� 1��°����� �ּҰ��� ���ٸ� (= ���Ḯ��Ʈ ��ü�� ����)?
    //  -> 2�� ���Ḯ��Ʈ�� head�� ��Ÿ���� 1��°����� �ּҰ��� ��� (NULL�̴� �ּҰ��� �ִ� �������)
    if (head1 == NULL) {
        return head2;
    }

    // 1�� ���Ḯ��Ʈ�� head�� ��Ÿ���� 1��°����� �ּҰ��� �ִµ�? 2�� ���Ḯ��Ʈ�� head�� ��Ÿ���� 1��°����� �ּҰ��� ���ٸ� (= ���Ḯ��Ʈ ��ü�� ����)?
    //  -> 1�� ���Ḯ��Ʈ�� head�� ��Ÿ���� 1��°����� �ּҰ��� ��� (NULL�̴� �ּҰ��� �ִ� �������)
    if (head2 == NULL) {
        return head1;
    }

    // (�߿�!) 1�� ���Ḯ��Ʈ�� head�� ��Ÿ���� 1��°����� �ּҰ� + 2�� ���Ḯ��Ʈ�� head�� ��Ÿ���� 1��°����� �ּҰ��� ��� null�� �ƴϸ� concat����

    // current_head1_index : 1�� ���Ḯ��Ʈ�� ������ ����� �ּҸ� �˾Ƴ��� ���� ListNode�� �ּҰ��� �޴� �����ͺ���
    ListNode* current_head1_index = head1;

    // current_head1_index(������ ��� �ּҰ�)�� ��ġ�� link�� null�� ���ö�����(= current_head1_index�� ������ ����� �ּҰ��� ��Ÿ��������)... ��� ����
    while (current_head1_index->link != NULL) {

        printf_s("�����ּ�.. %d -> %d��..\n", current_head1_index, current_head1_index->link);

        // current_head1_index(������ ��� �ּҰ�)�� ��ġ�� link�� null�� �ƴϸ�, ���� ����� �ּҰ��� �ǹ��ϴ� current_head1_index->link�� current_head1_index�� ������ ����
        current_head1_index = current_head1_index->link;
    }

    // null�̾��� current_head1_index(������ ��� �ּҰ�)�� ��ġ�� link���� 2�� ���Ḯ��Ʈ�� head�� ��Ÿ���� 1��°����� �ּҰ��� head2�� ����
    current_head1_index->link = head2;

    // ���ο� concat head
    ListNode* concat_head = head1;

    // ���̻� ������ �������� ������
    head1 = NULL;
    head2 = NULL;

    printf_s("----------------------------[concat ���̱� �Ϸ�] : head1�� ������ link�� = %d -> %d(%d)��.. ����-----------------------------\n", current_head1_index, current_head1_index->link, (head2));

    // 1��, 2�� ������ �Ϸ�� ���Ḯ��Ʈ�� �������� 1�� ���Ḯ��Ʈ�� ��尪�� ���� concat_head����
    return concat_head;

}

// reverse : list1�� ��� ���θ� �ݴ�� ����
ListNode* reverse(ListNode* head) {

    // ���ʿ� ���Ḯ��Ʈ�� ��尡 ���ٸ�, null����ȯ
    if (head == NULL) {
        return NULL;
    }

    printf_s("\n\n------------------------------[reverse ����! : head �����Ű��]---------------------------------------------\n\n");

    // ���Ḯ��Ʈ�� ��尡 �ϳ��� �ִٸ�, head�� ����� 1���� ����� ���� target���� ���Ӹ���Ʈ ���� �������

    // target_address : ���� ��ġ�ϴ� ���� ����.. head���� �����ϰ�, �۾��� ������ �ڽ��� �����ϴ� �ּҰ��� ����� ���� ����� �ּҸ� ������ link�� ���ŵ�
    ListNode* target_address = head;

    // already_reversed_node : �̹� ����ó���� �Ϸ�� ���� ���۰��� �������� ����
    ListNode* already_reversed_node;

    // should_be_reversed_node : ����ó���� ���� �����ؾ��� ����� �ּҷ� ���۰��� NULL
    ListNode* should_be_reversed_node = NULL;


    // ���� �����۾� ���� ����� �ּҰ��� null (= �� �༮�� ������ ���Ḯ��Ʈ�� ������ ����� �ǹ�)�� �ɋ����� �ݺ�
    while (target_address != NULL) {

        // �̹� ����ó���� �Ϸ�� ����� �ּҰ� already_reversed_node�� �ռ� ���ʿ� ������ ����� �ּҰ� should_be_reversed_node���� �����ؼ� ���� 
        // -> ó������ ����Ϸ�Ȱ� ������ null
        already_reversed_node = should_be_reversed_node;

        // ����ó���� ���� �����ؾ��� ����� �ּҰ� should_be_reversed_node�� ���� ��ġ�� ����� �ּ� target_address������ �����ؼ� ����
        should_be_reversed_node = target_address;

        // ���� �۾����� ���� ����� �ּҸ� Ÿ������ ��������
        target_address = target_address->link;

        // ���� ����ó���� ���� ������ ����� ���� ����� �ּҰ��� �����ϴ� should_be_reversed_node�� link���� �̹� ����� ����� �ּҰ� already_reversed_node���� ����
        //  -> ó������ ������ ����ó�� �Ϸ�� ��尡 ������ �翬�� null�� �� (= ó�� �۾��ϴ� ���� �ᱹ ����� ����Ʈ������ ������ ��带 �ǹ�)
        should_be_reversed_node->link = already_reversed_node;
    }

     printf_s("----------------------------[reverse �Ϸ�] : head1�� = %d -> %d(%d)��.. ����-----------------------------\n", head, should_be_reversed_node);

     // �����۾��� ������ ����, ���� �����۾��� ��ģ ����� �ּҰ��� ����
     head = should_be_reversed_node;

     return head;
    //return should_be_reversed_node;
}

// ����Ʈ�� ��� ��Ҹ� ǥ��
void display(ListNode* head) {

    printf_s("\n\n------------------------------[�ּҰ� %d display ����!]------------------------------\n\n", head);

    printf("list ��� : ");

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
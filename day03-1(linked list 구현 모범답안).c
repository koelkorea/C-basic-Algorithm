#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(type,a,b) {type t=a;a=b;b=t;}
typedef int list_element;
typedef struct ListNode {
    list_element data;
    struct ListNode* link;
} ListNode;
// ��� �� �� ����
ListNode* insert_first(ListNode* head, list_element value);
// ��� �� �� ����
ListNode* insert_last(ListNode* head, list_element value);
// ��� ���� ����
ListNode* insert_sort(ListNode* head, list_element value);
// ��� �� �� ����
ListNode* delete_first(ListNode* head);
// ��� �� �� ����
ListNode* delete_last(ListNode* head);
// ��� �˻� ����
// ��ȯ �� = ���� ���� : 0, ���� ���� : -1
// �Ű����� ListNode** head = List Head�� �ּ�
// �Ű����� list_element value = ���� ���
int delete_search(ListNode** head, list_element value);
// ��� �˻�
ListNode* search(ListNode* head, list_element x);
// ����Ʈ ���� head1 + head2
ListNode* concat(ListNode* head1, ListNode* head2);
// ����Ʈ ���� ����
ListNode* reverse(ListNode* head);
// ��� ����
ListNode* ListSort(ListNode* head);
// ����Ʈ ���
void print_list(ListNode* head);
// ����Ʈ �޸� ����
// �Ű����� ListNode** head = List Head�� �ּ�
void freelist(ListNode** head);

int main() {

    srand((unsigned)time(NULL));
    ListNode* list_head1 = NULL, * list_head2 = NULL;

    for (int i = 0; i < 110; i += 10) {
        list_head1 = insert_first(list_head1, i);
        printf("list 1 ");
        print_list(list_head1);
    }
    for (int i = 0; i <= 50; i += 20) {
        if (delete_search(&list_head1, i) == 0) printf("%4d ���� ����  ", i);
        else printf("%4d ���� ����  ", i);
        printf("list 1 ");
        print_list(list_head1);
    }
    for (int i = 0; i < 50; i += 10) {
        list_head2 = insert_sort(list_head2, rand() % 5000);
        printf("list 2 ");
        print_list(list_head2);
    }
    for (int i = 0; i < 2; i++) {
        list_head1 = delete_first(list_head1);
        list_head1 = delete_last(list_head1);
        printf("list 1 ");
        print_list(list_head1);
    }
    ListNode* concat_list = concat(list_head1, list_head2);
    list_head1 = list_head2 = NULL;
    printf("list concat ");  print_list(concat_list);
    concat_list = reverse(concat_list);
    printf("list concat ");  print_list(concat_list);
    ListNode* p = search(concat_list, 80);
    if (p != NULL) printf("Ž�� ���� : %d\n", p->data);
    else printf("Ž�� ����\n");
    ListSort(concat_list);
    printf("list concat ");  print_list(concat_list);
    freelist(&concat_list);
    return 0;
}

ListNode* insert_first(ListNode* head, list_element value) {
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    if (NewNode == NULL) { printf("�� ��� ���� �Ҵ� ����!\n"), exit(1); }
    NewNode->data = value;
    NewNode->link = head;
    return NewNode;
}

ListNode* insert_last(ListNode* head, list_element value) {
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    if (NewNode == NULL) { printf("�� ��� ���� �Ҵ� ����!\n"), exit(1); }
    NewNode->data = value;
    NewNode->link = NULL;
    if (head == NULL) { head = NewNode; return head; }
    ListNode* LastNode = head;
    while (LastNode->link != NULL) LastNode = LastNode->link;
    LastNode->link = NewNode;
    return head;
}

ListNode* insert_sort(ListNode* head, list_element value) {
    ListNode* NewNode = (ListNode*)malloc(sizeof(ListNode));
    if (NewNode == NULL) { printf("�� ��� ���� �Ҵ� ����!\n"), exit(1); }
    NewNode->data = value;
    NewNode->link = NULL;
    if (head == NULL) return NewNode; // Node ����
    ListNode* forward = head, * rear = NULL; //NewNode ���� ��, �� ��� ��ġ ã��
    while (forward != NULL) {
        if (forward->data > value)break;
        rear = forward;
        forward = forward->link;
    }
    if (forward == head) { // �� ��� ��ġ�� �� ��
        NewNode->link = forward;
        return NewNode;
    }
    else { // �� ��� ��ġ�� �߰�, �� ��
        NewNode->link = forward;
        rear->link = NewNode;
    }
    return head;
}

ListNode* delete_first(ListNode* head) {

    if (head == NULL) return NULL; // Node ����

    ListNode* DeleteNode = head;
    head = head->link; // ���� ��� ���� �ּ�
    free(DeleteNode);

    return head;
}

ListNode* delete_last(ListNode* head) {
    if (head == NULL) return NULL; // Node ����
    ListNode* DeleteNode = head, * LastNode = NULL;
    while (DeleteNode->link != NULL) {
        LastNode = DeleteNode;
        DeleteNode = DeleteNode->link;
    }
    if (DeleteNode != head) LastNode->link = NULL; // Node 2�� �̻�
    else /* DeleteNode == head */ head = NULL; // ��ü Node 1�� ���
    free(DeleteNode);
    return head;
}

int delete_search(ListNode** head, list_element value) {

    if (*head == NULL) return 1; // ���� ���� (Node ����)

    ListNode* DeleteNode = *head, * rear = NULL;

    while (DeleteNode != NULL) { // ���� ��� ã��
        if (DeleteNode->data == value) break;
        rear = DeleteNode;
        DeleteNode = DeleteNode->link;
    }

    if (DeleteNode != NULL) { // ���� ��� �߰�
        if (DeleteNode == *head) *head = DeleteNode->link;// ���� ��� = �� �� ���
        else rear->link = DeleteNode->link; // ���� ��� = �߰�, �� �� ���
        free(DeleteNode);
        return 0; // ���� ����
    }

    else /* DeleteNode == NULL */ return 1; // ���� ����
}

ListNode* search(ListNode* head, list_element item) {
    for (ListNode* pNode = head; pNode != NULL; pNode = pNode->link)
        if (pNode->data == item) return pNode;
    return NULL;
}

ListNode* concat(ListNode* head1, ListNode* head2) {
    if (head1 == NULL) return head2;
    else if (head2 == NULL) return head1;
    else {
        ListNode* pNode = head1;
        while (pNode->link != NULL) pNode = pNode->link;
        pNode->link = head2;
        return head1;
    }
}

ListNode* reverse(ListNode* head) { // ���� ���� �ٲٱ�
    ListNode* forward = head, * pNode = NULL, * rear = NULL;
    while (forward != NULL) {
        rear = pNode; // rear : �̹� �������� ������ ���
        pNode = forward; // pNode : �������� ���� ���
        forward = forward->link; // forward : ���� ���
        pNode->link = rear;
    }
    return pNode;
}

ListNode* ListSort(ListNode* head) {
    for (ListNode* SortNode = head; SortNode != NULL; SortNode = SortNode->link) {
        for (ListNode* CompareNode = SortNode->link; CompareNode != NULL; CompareNode = CompareNode->link) {
            if (SortNode->data > CompareNode->data) swap(list_element, SortNode->data, CompareNode->data);
        }
    }
    return head;
}

void print_list(ListNode* head) {
    printf(" list -> ");
    for (ListNode* pNode = head; pNode != NULL; pNode = pNode->link)
        printf("%4d -> ", pNode->data);
    printf("NULL \n");
}

void freelist(ListNode** head) {
    ListNode* DeleteNode = NULL;
    while (*head) {
        DeleteNode = *head;
        *head = (*head)->link;
        free(DeleteNode);
    }
    *head = NULL;
}

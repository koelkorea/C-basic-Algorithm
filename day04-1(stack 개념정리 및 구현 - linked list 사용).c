// ����(stack)
//  : 'â�� ������ �׾Ƶε�' �ڷḦ �� ���� �׾Ƶδ� �ڷᱸ�� ����
//    (= ���� ���߿� ���� �༮�� ���� ���߿� ������ ����)

//  # ���Լ��� LIFO 
//    : Last-In, First-Out  

//  # stack ����ü ( ���� ��� )
// 
//    typedef int stack_element;

//    typedef struct {
//        stack_element* data; // ���ÿ� ���� ������ ���� (= �� �����ͺ����� �����Ҵ� �޼��带 ���� return���� �ް� �� ��... �� ��ġ�� �����ϱ� ���� �뵵)
//        int capacity;        // ������ �� ���� �뷮 ����
//        int top;             // ���� ����� �ڷ� ����
//    } StackType;

//  # Stack ADT
//    - init_stack(stack) : ������ ������� �ʱ�ȭ
//    - is_empty(stack)   : ���� �ȿ� ���� ������ Ȯ��
//    - is_full(stack)    : ������ ���� á������ Ȯ��
//    - push(stack, item) : ���� �ڷ��� �� ���� ��� item �߰�
//    - pop(stack)        : ������ �� ���� �ִ� ��Ҹ� �������� �ʰ� ��ȯ


// stack ADT ���� �����غ��� (double linked list ����ؼ�..)
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��

typedef int Stack_DoublelistElement;

// (����!) ����ü�� ������ �� �̸��� ���� �� [�����Ǹ� != ������ü��]�� ���, ��������� �������� �����ͺ������� �����ǵ� ����ü���� �������� ��´ٸ�?
//  -> �̸� ������ �������ϱ� �����ϸ� ���� ����ü�� �ν��Ѵ�..
//     -> [��� : ����ü�� ������� �� �������� �����ͺ����� �ڷ������� �������� ��찡 �ִٸ�, �ݵ�� �̸��� ������ü������ ���°� �������� ����!]
typedef struct Stack_DoublelistNode
{
    Stack_DoublelistElement data;
    struct Stack_DoublelistNode* Llink;
    struct Stack_DoublelistNode* Rlink;
} Stack_DoubleListNode;

typedef struct
{
    Stack_DoubleListNode* head; // ���ÿ� ���� ������ ��ġ�ϴ� �޸� �ּ��� ������ (= �� �����ͺ����� �����Ҵ� �޼��带 ���� return���� �ް� �� ��... �� ��ġ�� �����ϱ� ���� �뵵)
    int capacity;        // ������ �� ���� �뷮 ����
    int top;             // ���� ����� �ڷ� ����
}StackType;

// stack �ʱ�ȭ
StackType* init_stack(StackType* stack);

// �ش� stack�ȿ� ���� ������ Ȯ��
int is_empty(StackType* stack);

// �ش� stack�� ����á���� ����
int is_full(StackType* stack);

// �ش� stack�� ���� �߰� (���� �� ��� �ٷ� ���� ���)
void push(StackType* stack, Stack_DoublelistElement item);

// stack���� ���� ���� return���� stack�� ��� (���� �ִ� ������ ���)
void pop(StackType* stack);

// �ش� �޸� ��ġ�� �����ϴ� stack �޸� ��ü ����
void free_stack(StackType* stack);

// �ش� �޸� ��ġ�� �����ϴ� stack ���� Ȯ��
void print(StackType* stack);

Stack_DoubleListNode* DoubleInitial(Stack_DoubleListNode* head);                                    // done
Stack_DoubleListNode* DoubleInsertLast(Stack_DoubleListNode* head, Stack_DoublelistElement item);   // done
void DoubleDeleteLast(Stack_DoubleListNode* head);                                                  // done
void DoubleDisplay(Stack_DoubleListNode* head);                                                     // done 
void FreeDoubleList(Stack_DoubleListNode* head);                                                    // done

int main(void)
{

    StackType* stack_address1 = NULL;
    stack_address1 = init_stack(stack_address1);

    for (int i = 1; i <= stack_address1->capacity; i++)
    {

        push(stack_address1, i * 3);
    }

    print(stack_address1);

    for (int i = 1; i <= stack_address1->capacity; i++)
    {

        pop(stack_address1);
    }

    print(stack_address1);

    return 0;
}

// stack �ʱ�ȭ
StackType* init_stack(StackType* stack)
{

    // stack ����ü�� ��ġ�ϴ� �޸��ּҸ� ������
    stack = (StackType*)malloc(sizeof(StackType));

    // top : ���� ���� ���� ����
    stack->top = 0;
    // capacity : ���� �� ���� ���� ����
    stack->capacity = 5;
    // head : ���ÿ� ���� ������ ��ġ�� '���߿��Ḯ��Ʈ'�� �޸� �ּ��� ������ head�ּ� (= �� �����ͺ����� �����Ҵ� �޼��带 ���� return���� �ް� �� ��... �� ��ġ�� �����ϱ� ���� �뵵)
    stack->head = DoubleInitial(stack->head);

    return stack;
}

// �ش� stack�ȿ� ���� ������ Ȯ�� (������ 0, ������ 1)
int is_empty(StackType* stack)
{

    if (stack->top == 0)
    {
        return 1;
    }

    return 0;
}

// �ش� stack�� ����á���� ���� (���� ������ 0, ����á���� 1)
int is_full(StackType* stack)
{

    // (�߿�) stack�� ���� ��ġ�ϴ� �޸� �ּҴ� ���� �߰��� �� top++�� �ȴٴ� ���� ����ؾ���
    // (= capacity�� 3�̶� ġ��, ������ ���� �ּ� = '�����ּ�' + capacity - 1 = '�����ּ�' + capacity - 1)
    if (stack->top >= stack->capacity)
    {
        return 1;
    }

    return 0;
}

// �ش� stack�� ���� �߰� (���� �� ��� �ٷ� ���� ��忡 �߰�)
void push(StackType* stack, Stack_DoublelistElement item)
{

    // ���� �߰��ϱ� �� stack�� ������ ����á���� Ȯ��
    int result = is_full(stack);

    // stack ������ ������ �ִٸ�? �� �߰�����
    if (result == 0)
    {
        stack->head = DoubleInsertLast(stack->head, item);

        // top�� �� = double ���Ḯ��Ʈ �� ��� �� �����ϴ� head�� �����Ͱ� (���⼭�� top�� ���� �޸𸮿� �������� �����Ƿ�, )
        (stack->top) = stack->head->data;

        printf("�޸� �ּ� %d���� �Ҵ�� stack������ %d��° ������ �� = %d \n", stack, stack->top, stack->head->Rlink->data);
    }
    else if (result == 1)
    {

        printf("(����!) �޸� �ּ� %d���� �Ҵ�� stack�� �̹� ������ �ִ� %d�� ������ ���� ä�����ϴ�.\n", stack, stack->capacity);
    }
}

// stack���� ���� ���� return���� stack�� ��� (���� �ִ� ������ ���)
void pop(StackType* stack)
{

    // ���� �߰��ϱ� �� stack�� ������ ������� Ȯ��
    int result = is_empty(stack);

    // �� ������� �� 
    if (result == 0)
    {
        int delete_int = stack->head->Rlink->data;

        DoubleDeleteLast(stack->head);

        // top�� �� = double ���Ḯ��Ʈ �� ��� �� �����ϴ� head�� �����Ͱ�
        (stack->top) = stack->head->data;
        printf("(STACK �� ����) : �޸� �ּ� %d���� �Ҵ�� stack������ %d��° ������ ���� %d�� �����߽��ϴ�. \n", stack, stack->top + 1, delete_int);
        printf(" -> �޸� �ּ� %d���� �Ҵ�� stack������ ���� ������ ���� %d��° ������ �� = %d \n", stack, stack->top, stack->head->Rlink->data);
    }
    else if (result == 1)
    {

        printf("(����!) �޸� �ּ� %d���� �Ҵ�� stack�� �Էµ� ���� �����ϴ�.\n", stack);
    }

}

// stack �޸� ����
void free_stack(StackType* stack)
{

    // ���� stack�� ���� ����ũ�� ����Ʈ�� 
    FreeDoubleList(stack->head);
    // �� ���� stack ����ü ��ġ�� �޸� ����
    free(stack);
}

// stack ���� Ȯ��
void print(StackType* stack)
{

    int result = is_empty(stack);

    if (result == 0)
    {

        printf("���� stack�� double linked list �Ѱ� ����ũ�� : %d\n", stack->capacity);
        printf("���� stack�� �Էµ� ���� : ");

        DoubleDisplay(stack->head);

        printf("\n");

    }
    else
    {
        printf("(����!) �޸� �ּ� %d���� �Ҵ�� stack�� �Էµ� ���� �����ϴ�.\n", stack);
    }

}

//-------------------------------------------------------------------------------------------------------------------------
// ����ũ�� ����Ʈ head ��� ����(= ��ǻ� �Է�����)
Stack_DoubleListNode* DoubleInitial(Stack_DoubleListNode* head)
{

    Stack_DoubleListNode* head_node = (Stack_DoubleListNode*)malloc(sizeof(Stack_DoubleListNode));

    // ����� ������ ���� ����� �� ���� (���鶧�� �翬�� �� ������ 0)
    head_node->data = 0;
    head_node->Llink = head_node;
    head_node->Rlink = head_node;

    printf_s("(dl ���� �ʱ�ȭ) : %d�� ����ũ�� ����Ʈ�� ����尡 �߰��Ǿ����ϴ�. �ش� �ּҰ��� %d�� ��ġ�� ��ϵǾ� �ֽ��ϴ�. \n", head_node, &head);

    head = head_node;

    return head;
}

// �ش� head�� ����Ű�� ����ũ�� ����Ʈ�� ������ ���� item�� �߰�
Stack_DoubleListNode* DoubleInsertLast(Stack_DoubleListNode* head, Stack_DoublelistElement item)
{

    Stack_DoubleListNode* insert_last_node = (Stack_DoubleListNode*)malloc(sizeof(Stack_DoubleListNode));

    if (insert_last_node == NULL)
    {
        printf("�޸� ����");
        return NULL;
    }

    // ���߿��Ḯ��Ʈ�� ���� stack�� �����ϴ� ���̱⿡, �������� ������ ���� �ƹ��͵� ����Ű�°� ����� �� (= �� head�� Llink�� �������� ���� ����)
    insert_last_node->Rlink = NULL;
    insert_last_node->data = item;


    // (case1) ���� ����Ʈ�� �����ϴ� ��尡 ������ ȥ���� ���? (= �������� ��link�� �����θ� ����Ŵ)
    //  -> �������� �� link�� ���� insert_last_node �ּҰ����� + insert_first_node ������ �ּҵ� head�� ����Ű�� ��
    //  -> ������ ����� ���ʳ��(= ���� ���)�� NULL�� �Է�
    if (head->Llink == head && head->Rlink == head)
    {

        insert_last_node->Llink = NULL;
        head->Llink = insert_last_node;
        head->Rlink = insert_last_node;
    }

    // (case2) �ش� ����ũ�� ����Ʈ�� �ٸ� ������ �ִ� ��� (= ������� ������link�� �ٸ� ��带 ����ų���)
    //  -> head�� Rlink ���� ����
    //  -> ������ ����� ���ʳ��(= ���� ���)�� head���� Llink�� ���� ���ٰ����� ���� ������ ����� �ּҷ�
    //  -> ������ ��� �������� ���ʳ�� �ּҵ� ���� ������ ����� �ּҰ����� ����
    else if (head->Rlink != head)
    {
        insert_last_node->Llink = head->Rlink;
        head->Rlink->Rlink = insert_last_node;
        head->Rlink = insert_last_node;
    }

    // ����� ������ ���� ����� �� ����
    head->data++;

    return head;
}

// �ش� head�� ����Ű�� ����ũ�� ����Ʈ�� ������ ��� ����
void DoubleDeleteLast(Stack_DoubleListNode* head)
{

    printf_s("\n\n------------------------------[DoubleDeleteLast ����!]------------------------------\n\n");

    Stack_DoubleListNode* delete_node = head->Rlink;

    // (case1) ���� ����Ʈ�� �����ϴ� ��尡 ������ ȥ���� ���? (= �������� ��link�� �����θ� ����Ŵ)
    //  -> ��� ������
    if (head->Llink == head && head->Rlink == head && head->data == 0)
    {

        printf_s("(���) : �ش� ����ũ�� ����Ʈ���� ��� �ܿ� �ٸ� ��尡 ��� ������ �Ұ����մϴ�.\n");
    }
    // (case2) �ش� ����ũ�� ����Ʈ�� 1��° ��常 �ִ� ��� (= �ڱ� ���ʿ� �ƹ��͵� �����°� ����)
    //  -> head�� L, Rlink�� �ʱ�ȭó�� �������� �ּҸ� ������ ��
    else if (delete_node->Llink == NULL && head->data == 1)
    {

        // head�� �� ���� ������� �ٽ� head�� �ʱ�ȭ
        head->Llink = head;
        head->Rlink = head;

        printf_s("�ش� ����Ʈ�� �ּ� %d�� ��ġ�� ������ ���� ����� data�� %d �����Ϸ�! \n", delete_node, delete_node->data);
        free(delete_node);
    }

    // (case3) �ش� ����ũ�� ����Ʈ�� 2�� �̻��� ��� ���� (= 1��°����� ������link�� head�� ����ų��� or head�� data�� 1�ʰ�)
    //  -> head�� Rlink�� ���� ������ ��尡 �� ���� ������ ����� Llink�� �ּҰ��� ������ ��
    //  -> ���� ������ ��尡 �� ���� ������ ����� Llink->Rlink�� NULL�� ����
    else if (delete_node->Rlink != head && head->data > 1)
    {

        delete_node->Llink->Rlink = NULL;
        head->Rlink = delete_node->Llink;

        printf_s("�ش� ����Ʈ�� �ּ� %d�� ��ġ�� ������ ����� %d��° ���Ḯ��Ʈ data�� %d �����Ϸ�! \n", delete_node, head->data, delete_node->data);
        free(delete_node);
    }

    // ����� ������ ���� ����� �� ����
    head->data--;
    printf_s("�ش� ����Ʈ�� �ּ� %d�� ��ġ�� ��� �� ���� : %d \n", head, head->data);
}

// ����ũ�� ����Ʈ�� ��� ����� data�� ���������� ���(Rlink ���󰡸� ��)
void DoubleDisplay(Stack_DoubleListNode* head)
{

    printf_s("\n\n------------------------------[�ּҰ� %d DoubleDisplay ����!]------------------------------\n\n", head);

    if (head->data == 0)
    {

        printf_s("(���) : �ش� ����ũ�� ����Ʈ���� ��� �ܿ� �ٸ� ��尡 �����ϴ�.\n");

    }
    else
    {

        printf("�ش� dlist�� ��尳�� %d���� ����Ʈ�� ���� ��� : ", head->data);

        Stack_DoubleListNode* current_node = head->Llink;

        printf("head -> ");

        for (int i = 1; i <= head->data; i++)
        {  // �����ͳ����� ��ȯ ����

            printf_s("%3d -> ", current_node->data);
            current_node = current_node->Rlink;
        }

        printf("head\n");
    }
}

// �����Ҵ��� ����ũ�� ����Ʈ �޸� �Ҵ� ����
void FreeDoubleList(Stack_DoubleListNode* head)
{

    printf_s("\n\n------------------------------[�ּҰ� %d FreeDoubleList ����!]------------------------------\n\n", head);

    printf_s("(�ش� dlist�� ����� ����) : %d�� \n", head->data);

    Stack_DoubleListNode* free_address = head;

    // �ش� ����ũ�� ����Ʈ�� ��� ���� ��尡 �ϳ��� �ִٸ�?
    //  -> �ϳ��� ���󰡸� �� ������ �ش��ϴ� ��� ����
    if (head->data != 0)
    {

        free_address = free_address->Rlink;

        for (int i = 1; i <= head->data; i++)
        {

            Stack_DoubleListNode* next_address = free_address->Rlink;

            printf_s("�ش� dlist %d��° ��� ���� : ����� ���� %d�̸� �ּҰ� %d���� �����ϴ� �ش� ��忡 �Ҵ�� �޸� ������ �����Ǿ����ϴ�.\n", i, free_address->data, free_address);

            free(free_address);
            free_address = next_address;
        }
    }

    // �ش� ����ũ�� ����Ʈ�� ��� �ۿ� ��尡 ���� ���¸�(������ �ϴ�, �������� �׷���), �����嵵 ����
    printf_s("\n-----------------[FreeDoubleList �Ϸ�] �ּҰ� %d���� �����ϴ� �ش� ���� dlist�� �����忡 �Ҵ�� �޸� ������ �����Ǿ����ϴ�.---------------\n", free_address);
    free(free_address);
}

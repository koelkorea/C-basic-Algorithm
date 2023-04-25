// ���� �켱 Ž�� (DFS : Depth First Search)
//  : �׷����� �ϳ��� ����(���� root)���κ��� �����Ͽ�, ���ʴ�� ��� �������� �ѹ��� �湮
//     -> ���� stack �ڷᱸ���� Ȱ���ؼ� ����

//  # DFS�� ����Ͽ� �̷� Ž�� �����ذ� ����
//     : �̷θ� Ž���� ��ó�� �� �������� �� �� ���� ������ ��� �����ϴ� ���
//        -> �̸� �� �̻� �� �� ���� �Ǹ�, �ٽ� ���� ����� ������� ������ �ٸ� �������� �ٽ� Ž���� �ݺ��ϴ� ������ ������ �ذ��ϴ� �Ͱ� ������

//    - �ذ�� 1) 
//       : 'stack �ڷᱸ��'�� boolean������ �迭�� ����Ͽ� �ذ�
//          (1) �ϳ��� ������ stack�� push�ص�
//          (2) stack�� �������� �� ������ pop �ϰ�, �� ������ ���� �湮���üũ �迭�� �ش� ����׸��� �湮���� ���� (pop = print �� ������)
//          (3) pop �� �������� �湮���� ���� ������ �������� �ٽ� stack�� push
//          (4) stack�� �� ������ 2�� 3���� �ݺ��ϰ�, �� �̻� �湮���� ���� ������ ���ö����� �̸� ��� �ݺ� (whlie�� ���� ����)

//    - �ذ�� 2)
//       : '����Լ�'�� boolean������ �迭�� ����Ͽ� �ذ� (= ����Լ��� ���°� ���� stack�� ���� ��)
//          -> �Լ��� �޸��� stack�������� �Լ��������� �����ϸ�, �� �ȿ��� �ٸ� �Լ��� ȣ���ϸ� stack������ ���̰� �������ϸ� LIFO��� �۵�
//             (1) �ϳ��� ������ ������� ����
//             (2) �湮 �޼��� ���� ��, �� ������ ���� �湮���üũ �迭�� �ش� ����׸��� �湮���� ���� (pop = print �� ������)
//             (3) ���� �������� �湮���� ���� ������ �������� �ϳ��� ��� �̵�
//             (4) 2�� 3���� �ݺ��ϰ� ���������� NULL�̸� ���� ������� ���ư��� ���, �� �̻� �湮���� ���� ������ ���ö����� �̸� ��� �ݺ�


// DFS�� �̷� ���� ���� (STACK, ��� �Ѵ� ����)
#include <stdio.h>
#include <stdlib.h>

// ��� ����ü
typedef struct node {

    // ������
    int dst;

    // ���� ����� �ּ� ����
    struct node* next;
}node;

// �׷��� ����ü ()
typedef struct graph {//������ �����ϱ� ���� �׷���

    // ������ ����
    int count;

    // ������ ������ŭ �Ҵ� �� node(�����)
    node* arr;
}graph;

// stack ����ü
typedef struct stack {

    //�����Ϸ��� ��ġ
    int top;    

    //�����Ҵ�� ������ �ּҸ� ����
    int* arr;    

    //������ �ִ� �뷮
    int capacity;  
}stack;

// GRAPH �Լ�
void stack_initialize(stack* stk, int count);
void push(stack* stk, int val);
void graph_initialize(graph* grp, int count);
void addDirectedEdge(graph* grp, int src, int dst);
void addUndirectedEdge(graph* grp, int src, int dst);
void graph_display(const graph* grp);
void memoryFree(graph* grp);

// STACK �Լ�
int pop(stack* stk);
int getCapacity(const stack* stk);
int getSize(const stack* stk);

// DFS �Լ�
void DFSReculsive(graph* grp, int index, int* visited);
void DFS(graph* grp, int source);
void DFS_stack(graph* grp, int source);

int main() {

    graph grp;

    graph_initialize(&grp, 9);
    addUndirectedEdge(&grp, 0, 1);
    addUndirectedEdge(&grp, 1, 2);
    addUndirectedEdge(&grp, 1, 4);
    addUndirectedEdge(&grp, 2, 5);
    addUndirectedEdge(&grp, 3, 4);
    addUndirectedEdge(&grp, 3, 6);
    addUndirectedEdge(&grp, 4, 5);
    addUndirectedEdge(&grp, 4, 7);
    addUndirectedEdge(&grp, 5, 8);
    addUndirectedEdge(&grp, 6, 7);

    graph_display(&grp);

    // �ذ�� 2) ��ȭ������ '����Լ�' ����� DFS
    DFS(&grp, 0); 
    printf("\n");

    // �ذ�� 1) 'stack �ڷᱸ��' ����� DFS
    DFS_stack(&grp, 0); 
    memoryFree(&grp);
    return 0;
}

//---------------------------------------[stack �Լ�]---------------------------------------

//stack ����ü �ʱ�ȭ : ���� ��� �ʱ�ȭ
void stack_initialize(stack* stk, int count) {
    stk->arr = (int*)malloc(sizeof(int) * count);// int arr[count]; ���� �迭 ���� ���� �Ҵ�
    stk->top = 0; // ���� ���� 0���� �ʱ�ȭ
    stk->capacity = count; // �� �뷮 count �� ����
}

// stack �޴ܿ� �� �߰�
void push(stack* stk, int val) {
    if (stk->top >= stk->capacity) { // ���� �뷮 �ʰ��� ���
        printf("\n\n\t\tstack overflow\n");
        return;
    }
    stk->arr[stk->top++] = val; // ���� arr �迭�� ������(dst) ���� �� top++
}


int pop(stack* stk) {
    if (stk->top <= 0) { // ���� ����
        printf("\n\n\t\tstack underflow\n");
        return -1;
    }
    return stk->arr[--(stk->top)]; // dst�� arr�迭���� ���� (pop)
}


int getCapacity(const stack* stk) { // ���� �� �뷮 Ȯ�� �Լ�
    return stk->capacity;
}


int getSize(const stack* stk) { // ���� �ڷ� ���� Ȯ��
    return stk->top;
}


//---------------------------------------[graph �Լ�]---------------------------------------

// �׷��� ����ü ���� ��� �ʱ�ȭ
void graph_initialize(graph* grp, int count) { 
    grp->count = count; // ���� ���� �ʱ�ȭ
    grp->arr = (node*)calloc(count, sizeof(node)); // node arr[count]; ���� ���� ���� �Ҵ�
}

// ���Ⱓ�� �׷����� �߰�
void addDirectedEdge(graph* grp, int src, int dst) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->dst = dst;
    newNode->next = grp->arr[src].next;
    grp->arr[src].next = newNode;
} // ���� ����Ʈ ��� �߰�, �������� ������ ����

// �׷��� ����� ���� ����
void addUndirectedEdge(graph* grp, int src, int dst) { 
    addDirectedEdge(grp, src, dst);
    addDirectedEdge(grp, dst, src);
}

// �׷��� ���� ���
void graph_display(const graph* grp) { // ��� ���� -> ���� ���� ǥ ���
    node* cur = NULL;
    if (grp == NULL) return;
    for (int i = 0; i < grp->count; i++) { //������ ������ŭ �ݺ�
        cur = grp->arr[i].next; // 1�� ������ ���� ���� �ּ� ����
        printf("����� ��� : %d ==> ", i); // ����� ��� ���
        while (cur) { // ������� NULL �� Ȯ��(���� ����)
            printf("%d ", cur->dst); // ������ ������ ���
            cur = cur->next; // ���� ����
        }
        printf("\n");
    }
}

void memoryFree(graph* grp) {
    node* delNode;
    for (int i = 0; i < grp->count; i++) {
        while (grp->arr[i].next) { // ���� ����Ʈ ��� ����
            delNode = grp->arr[i].next; // ���� ��� �ּ� ����
            grp->arr[i].next = delNode->next; // ���� ��� �ּҷ� ����
            free(delNode);
        }
    }
    free(grp->arr); // ����� ��� ����
}

//---------------------------------------[DFS �Լ�]---------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
// �ذ�� 2) '����Լ�'�� boolean������ �迭�� ����Ͽ� �ذ� (= ����Լ��� ���°� ���� stack�� ���� ��)

// DFS ��ȭ�� ����
void DFS(graph* grp, int source) { // �Ű����� : �׷���, �����

    int* visited = (int*)calloc(grp->count, sizeof(int)); //int visited[count]; boolean visited array ���� �湮 �迭
    printf("%d ", source); //����� ���� ��� "0"
    DFSReculsive(grp, source, visited); 
}

//DFS���ȣ�� (�׷���, �����, �湮��)
void DFSReculsive(graph* grp, int index, int* visited) {// �Ű����� : �׷���, �����, �湮��

    node* curNode = grp->arr[index].next; // ������� ����� ������ ������ ��� �ּ�(���� ����)
    visited[index] = 1; // �湮�� üũ

    while (curNode) { // ���� ���� ����

        int destination = curNode->dst; // ���� ���� �������� ����

        if (visited[destination] == 0) { // �湮�� ���� ������
            printf("%d ", destination); // ������ ���
            DFSReculsive(grp, destination, visited); // �������� �������� ���� �������� ��� �Լ�
        }

        curNode = curNode->next; // �湮�� ���� ������ ���� ���� �ּҷ�
    }
}
//--------------------------------------------------------------------------------------------------------------------

// �ذ�� 1) �׷����� stack�� Ȱ���� DFS ������� �����ذ� 
void DFS_stack(graph* grp, int source) { // �Ű����� : �׷���, �����

    int* visited = (int*)calloc(grp->count, sizeof(int)); //int visited[count]; boolean visited array ���� �湮 �迭

    stack stk;
    stack_initialize(&stk, 9); // stack �ʱ�ȭ �� �뷮 9��
    push(&stk, source); //����� ���� ���ÿ� ����
    visited[source] = 1; // �湮�� üũ

    // ������ ������ ��� Pop �� ������ �ݺ�
    while (getSize(&stk) != 0) {

        int traversal = pop(&stk); // �湮�� ���� Pop
        printf("%d ", traversal); // �湮�� ���� ���
        node* curNode = grp->arr[traversal].next; // �湮�� ������ ���� ���� �ּ� ����

        // ���� ���� �ּҰ� ���� ��
        while (curNode) {

            // ���� ���� ������
            int dst = curNode->dst;

            // �湮�� ���� ������
            if (visited[dst] == 0) {

                push(&stk, dst); // ���ÿ� �ֱ�
                visited[dst] = 1; // �湮�� üũ
            }

            curNode = curNode->next; // �湮�� ���� ������ ���� ���� �ּҷ�
        }
    }
    printf("\n");
    free(stk.arr); //���� �޸� ����
}
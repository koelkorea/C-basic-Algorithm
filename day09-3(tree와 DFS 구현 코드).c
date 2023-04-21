#include <stdio.h>  
#include <stdlib.h> // malloc(), rand() srand()
#include <time.h> // time()
/////////////////////////////Ʈ�� ���  ////////////////////////
typedef int element;
typedef enum {
    TERMINATE, ADD, REMOVE, SEARCH, PRINT, MIN, MAX
}menu;
typedef struct tNode {
    element value;
    int level;   // level ��� ��� ����
    struct tNode* left;
    struct tNode* right;
}treeNode;
treeNode* addNode(treeNode* t, element data);
treeNode* removeNode(treeNode* t, element data);
treeNode* searchNode(treeNode* t, element data);
int displayInOrder(treeNode* t);
treeNode* findMin(treeNode* t);
treeNode* findMax(treeNode* t);
void freeTree(treeNode* t);
/////////////////////////////Ʈ�� ��� ť////////////////////////
typedef struct QueueNode {
    treeNode* item;
    struct QueueNode* link;
} QueueNode;
typedef struct {
    QueueNode* front, * rear;
} QueueType;
void init(QueueType* q) { q->front = q->rear = 0; }
int is_empty(QueueType* q) { return (q->front == NULL); }
int is_full(QueueType* q) { return 0; }
void enqueue(QueueType* q, treeNode* item);
treeNode* dequeue(QueueType* q);
void level_order(treeNode* ptr);
//////////////////////////////////////////////////////////////////
void random_value(treeNode** t, int cnt, int range) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < cnt; i++) {
        *t = addNode(*t, rand() % range + 1);
    }
}
int main() {
    int select, i = 100, random = 2000;
    element val;
    treeNode* root = NULL, * findNode = NULL;
    random_value(&root, i, random);
    while (1) {
        system("cls");
        printf("1. add\n");
        printf("2. remove\n");
        printf("3. search\n");
        printf("4. print\n");
        printf("5. min\n");
        printf("6. max\n");
        printf("0. terminate\n");
        printf("select menu : ");
        scanf_s("%d", &select);
        switch (select) {
        case ADD:
            printf("\n\n���� �Է� : ");
            scanf_s("%d", &val);
            root = addNode(root, val);
            break;
        case REMOVE:
            printf("\n\n\t\t������ ���� �Է� : ");
            scanf_s("%d", &val);
            root = removeNode(root, val);
            break;
        case SEARCH:
            printf("\n\n\t\t�˻��� ���� �Է� : ");
            scanf_s("%d", &val);
            findNode = searchNode(root, val);
            if (!findNode) printf("\n\n\t\t�˻��� ������ �������� �ʽ��ϴ�.\n");
            else {
                printf("\n\n\t\t�˻��� ���� %d�� �ֽ��ϴ�\n", findNode->value);
                printf("\n\n\t\t�˻��� ���� ������ %d �Դϴ�\n", findNode->level);
            }
            break;
        case MIN:
            findNode = findMin(root);
            if (!findNode) printf("\n\n\t\t��尡 �������� �ʽ��ϴ�.\n");
            else printf("\n\n\t\t�ּڰ��� %d�Դϴ�.\n", findNode->value);
            break;
        case MAX:
            findNode = findMax(root);
            if (!findNode) printf("\n\n\t\t��尡 �������� �ʽ��ϴ�.\n");
            else printf("\n\n\t\t�ִ��� %d�Դϴ�.\n", findNode->value);
            break;
        case PRINT:
            displayInOrder(root);
            level_order(root);
            break;
        case TERMINATE:
            freeTree(root);
            exit(0); //���α׷� ���� ����
            break;
        }
        printf("\n\n");
        system("pause");
    }
    return 0;
}
treeNode* addNode(treeNode* t, element data) {
    if (!t) {//����Ž�� ���� ��ġ�� ���� ��ġ & ��尡 ���� ��
        t = (treeNode*)malloc(sizeof(treeNode));
        t->value = data;
        t->level = 0;
        t->left = NULL;
        t->right = NULL;
    }
    else if (data == t->value) printf("\n\n\t\t%d�� �̹� ��� �� �� �Դϴ�.\n", data);
    else if (data < t->value) t->left = addNode(t->left, data);
    else /* data > t->value */t->right = addNode(t->right, data);
    return t;
}
treeNode* removeNode(treeNode* t, element data) {
    treeNode* temp = NULL;
    if (t) {
        if (data == t->value) {// ������ �� ��� ã��
            if (t->left == NULL && t->right == NULL) {//��尡 ������ ���
                free(t);
                return NULL;
            }
            else {
                if (t->left == NULL) {//������ �ڽĸ� �ִ�.
                    temp = t->right;
                    free(t);
                    return temp;
                }
                if (t->right == NULL) {//���� �ڽĸ� �ִ�.
                    temp = t->left;
                    free(t);
                    return temp;
                }
                temp = findMax(t->left);//������ & ���� ��� �ڽ��� �־�, ���� ���� ū �� ȣ��
                t->value = temp->value;//���� ���� ū �� ����
                t->left = removeNode(t->left, temp->value);//���� ���� ū �� ���� ���
            }
        }
        else {// �� ã��, ��;˰���
            if (data < t->value) t->left = removeNode(t->left, data);
            else/* data > t->value */t->right = removeNode(t->right, data);
        }
    }
    return t;
}
treeNode* searchNode(treeNode* t, element data) {
    static int level_search;
    if (!t) {
        level_search = 0;
        return NULL; //Ž�� ����
    }
    if (data == t->value) {
        t->level = level_search;
        level_search = 0;
        return t; //Ž�� ����
    }
    if (data < t->value) {
        level_search++;
        return searchNode(t->left, data); // data���� �۾� ���� Ž��
    }
    else {
        level_search++;
        return searchNode(t->right, data); // data���� Ŀ ������ Ž��
    }
}
int displayInOrder(treeNode* t) {//���� ��ȸ : ���� - �θ� - ������
    static int level_InOrder;
    ++level_InOrder;
    if (t) {
        displayInOrder(t->left); // ����
        t->level = level_InOrder - 1;
        printf("Value : %5d , Level : %5d\n", t->value, t->level); // �θ�
        displayInOrder(t->right); // ������
    }
    return --level_InOrder;
}
treeNode* findMin(treeNode* t) { // ���� ������ �ּҰ�
    if (t) while (t->left) t = t->left;
    return t;
}
treeNode* findMax(treeNode* t) { // ���� �������� ū ��
    if (t) while (t->right) t = t->right;
    return t;
}
void freeTree(treeNode* t) { // ���� ��ȸ : ���� - ������ - �θ�
    if (t) {
        freeTree(t->left); // ����
        freeTree(t->right); // ������
        printf("%d��� ����\n", t->value); // �θ�
        free(t); // �޸� ���� (��Ʈ ��� ���� �������� ����)
    }
}
void enqueue(QueueType* q, treeNode* item) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    if (temp == NULL) printf("�޸𸮸� �Ҵ��� �� �����ϴ�");
    else {
        temp->item = item;
        temp->link = NULL;
        if (is_empty(q)) {
            q->front = temp;
            q->rear = temp;
        }
        else {
            q->rear->link = temp;
            q->rear = temp;
        }
    }
}
treeNode* dequeue(QueueType* q) {
    QueueNode* temp = q->front;
    treeNode* item;
    if (is_empty(q)) printf("ť�� ��� �����ϴ�");
    else {
        item = temp->item;
        q->front = q->front->link;
        if (q->front == NULL) q->rear = NULL;
        free(temp);
        return item;
    }
}
void level_order(treeNode* ptr) {
    QueueType q;
    int level = 0;
    init(&q);
    if (!ptr) return;
    printf("\n\nlevel order\n");
    enqueue(&q, ptr);
    while (!is_empty(&q)) {
        ptr = dequeue(&q);
        if (level != ptr->level) {
            level = ptr->level;
            printf("\n");
        }
        printf("%5d", ptr->value);
        if (ptr->left) enqueue(&q, ptr->left);
        if (ptr->right) enqueue(&q, ptr->right);

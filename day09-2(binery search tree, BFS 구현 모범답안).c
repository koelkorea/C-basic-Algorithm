#include <stdio.h>  
#include <stdlib.h> // malloc(), rand() srand()
#include <time.h> // time()
/////////////////////////////트리 노드  ////////////////////////
typedef int element;
typedef enum {
    TERMINATE, ADD, REMOVE, SEARCH, PRINT, MIN, MAX
}menu;
typedef struct tNode {
    element value;
    int level;   // level 멤버 노드 포함
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
/////////////////////////////트리 노드 큐////////////////////////
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
            printf("\n\n정수 입력 : ");
            scanf_s("%d", &val);
            root = addNode(root, val);
            break;
        case REMOVE:
            printf("\n\n\t\t삭제할 정수 입력 : ");
            scanf_s("%d", &val);
            root = removeNode(root, val);
            break;
        case SEARCH:
            printf("\n\n\t\t검색할 정수 입력 : ");
            scanf_s("%d", &val);
            findNode = searchNode(root, val);
            if (!findNode) printf("\n\n\t\t검색한 정수는 존재하지 않습니다.\n");
            else {
                printf("\n\n\t\t검색한 정수 %d는 있습니다\n", findNode->value);
                printf("\n\n\t\t검색한 값의 레벨은 %d 입니다\n", findNode->level);
            }
            break;
        case MIN:
            findNode = findMin(root);
            if (!findNode) printf("\n\n\t\t노드가 존재하지 않습니다.\n");
            else printf("\n\n\t\t최솟값은 %d입니다.\n", findNode->value);
            break;
        case MAX:
            findNode = findMax(root);
            if (!findNode) printf("\n\n\t\t노드가 존재하지 않습니다.\n");
            else printf("\n\n\t\t최댓값은 %d입니다.\n", findNode->value);
            break;
        case PRINT:
            displayInOrder(root);
            level_order(root);
            break;
        case TERMINATE:
            freeTree(root);
            exit(0); //프로그램 강제 종료
            break;
        }
        printf("\n\n");
        system("pause");
    }
    return 0;
}
treeNode* addNode(treeNode* t, element data) {
    if (!t) {//이진탐색 실패 위치가 삽입 위치 & 노드가 없을 때
        t = (treeNode*)malloc(sizeof(treeNode));
        t->value = data;
        t->level = 0;
        t->left = NULL;
        t->right = NULL;
    }
    else if (data == t->value) printf("\n\n\t\t%d는 이미 등록 된 값 입니다.\n", data);
    else if (data < t->value) t->left = addNode(t->left, data);
    else /* data > t->value */t->right = addNode(t->right, data);
    return t;
}
treeNode* removeNode(treeNode* t, element data) {
    treeNode* temp = NULL;
    if (t) {
        if (data == t->value) {// 삭제할 값 노드 찾기
            if (t->left == NULL && t->right == NULL) {//노드가 리프인 경우
                free(t);
                return NULL;
            }
            else {
                if (t->left == NULL) {//오른쪽 자식만 있다.
                    temp = t->right;
                    free(t);
                    return temp;
                }
                if (t->right == NULL) {//왼쪽 자식만 있다.
                    temp = t->left;
                    free(t);
                    return temp;
                }
                temp = findMax(t->left);//오른쪽 & 왼쪽 모두 자식이 있어, 왼쪽 가장 큰 값 호출
                t->value = temp->value;//왼쪽 가장 큰 값 저장
                t->left = removeNode(t->left, temp->value);//왼쪽 가장 큰 값 삭제 재귀
            }
        }
        else {// 값 찾기, 재귀알고리즘
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
        return NULL; //탐색 실패
    }
    if (data == t->value) {
        t->level = level_search;
        level_search = 0;
        return t; //탐색 성공
    }
    if (data < t->value) {
        level_search++;
        return searchNode(t->left, data); // data값이 작아 왼쪽 탐색
    }
    else {
        level_search++;
        return searchNode(t->right, data); // data값이 커 오른쪽 탐색
    }
}
int displayInOrder(treeNode* t) {//중위 순회 : 왼쪽 - 부모 - 오른쪽
    static int level_InOrder;
    ++level_InOrder;
    if (t) {
        displayInOrder(t->left); // 왼쪽
        t->level = level_InOrder - 1;
        printf("Value : %5d , Level : %5d\n", t->value, t->level); // 부모
        displayInOrder(t->right); // 오른쪽
    }
    return --level_InOrder;
}
treeNode* findMin(treeNode* t) { // 가장 왼쪽이 최소값
    if (t) while (t->left) t = t->left;
    return t;
}
treeNode* findMax(treeNode* t) { // 가장 오른쪽이 큰 값
    if (t) while (t->right) t = t->right;
    return t;
}
void freeTree(treeNode* t) { // 후위 순회 : 왼쪽 - 오른쪽 - 부모
    if (t) {
        freeTree(t->left); // 왼쪽
        freeTree(t->right); // 오른쪽
        printf("%d노드 삭제\n", t->value); // 부모
        free(t); // 메모리 해제 (루트 노드 가장 마지막에 해제)
    }
}
void enqueue(QueueType* q, treeNode* item) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    if (temp == NULL) printf("메모리를 할당할 수 없습니다");
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
    if (is_empty(q)) printf("큐가 비어 있읍니다");
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

// Ž��(Greedy) �˰���
//  : �ϴ� �־��� ������ ���ǿ��� ���� �ֻ��� ������ �ϴٺ��� ���� ���� �������� �̾����ٴ� ����� ������ ������ �˰���
//    ex) A���� B�� �̵��ϴ� �ִ� ��� ã��
//        �ִ� �۾� �켱 �����ٸ� (shortest job first scheduling)
//        ���� ���� �賶 ���� (fractional knapsack problem)
//        ��� ������ �����ϰ� ����� ��ü ����� �ּ�ȭ(= �ּ� ���� Ʈ��)

//  # �׸��� �˰��� �䱸 ����
//    1. ���� �κ� ����(optimal substructure)
//        : �κ��� ���� ����� ��ü���� �״�� ����Ǿ�� �� ��
//    2. �׸��� ����(greedy choice)
//        : �� ������ ������ ���Ŀ� ������ ���� ����

// �ּ� ���� Ʈ�� (MST, Minimum Spanning Tree)
//  : ��� ������ �����ϰ� ����� ������ ����ġ ���� �ּ��� Ʈ��
//    ex) ������� ��Ʈ��ũ ���� -> ��� ������� �������� ����, ��ü ���̴� �ּҰ� �Ǵ� ��
//        ���� ��Ʈ��ũ ����     -> �ʿ��� ������ ���ΰ� ����, ��ü ���̴� �ּ�ȭ �Ǵ� ��

//  # �ּ� ���� Ʈ�� (MST, Minimum Spanning Tree) ���� (�굵 �׸��� �˰���)
//     1. �������� ����ġ�� �������� ������������ ����
//     2. ����ġ ���� ������ ���� (BUT! ������ ������ cycle�� �����Ǹ� ���� -> how? ������ ã��, ���μ� ����)
//     3. ���� - 1���� ���� ���� �� ������ 2�� �ݺ�

// ũ�罺Į �˰��� - �ּ� ���� Ʈ�� (MST, Minimum Spanning Tree) ���� ����1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX_VERTEX 10 // ������ ����

// linked list ����ü ��� ����
typedef struct LIST {

    // ������ ��ȣ ����
    int vx;
    // ������ ����Ǵ� ��� ������ �����͸� ����
    struct LIST* link; 

}List;

// �׷��� ����ü
typedef struct GRAPH {

    // ���� �׷����� ����Ǿ� �ִ� ������ ����
    int n;
    // ��� ������ �������� ������ ������ �����͸� ����
    List* adj_list[MAX_VERTEX];  

}Graph;

// ���� ����ü : ������ ����� ���� �����Ϳ� ����ġ�� �����ϱ� ���� ����ü
typedef struct EDGE {  
    int v1; // ���� 1
    int v2; // ���� 2
    int key;// ���� (1,2) ����ġ
}Edge;

// ���� ���� ����ġ�� ���� �������� ���ʷ� �׷��� �����ϱ� ���ؼ� ���
typedef struct HEAP {  

    // �׷����� �����ϴ� ������ ����
    int n;

    // ũ�Ⱑ ���� * ������, ���� ����ü ���� �迭 ������ġ �ּ�
    Edge* heap[MAX_VERTEX * MAX_VERTEX];

}Heap;

int parent[MAX_VERTEX];

//------------------------------[cycle �Ǻ�, ������, ���μ� �˰���]----------------------------
void union_parent_init();
int get_parent(int index);
void union_parent(int x, int y);
int find_parent(int x, int y);

//s1, s2�� ������ ���θ� �˻��� �� �׷����� �߰�
int Link_Vertex_gm(int s1, int s2, int key); 

//------------------------------[MST �˰���]--------------------------------------------------

// ������ ����ġ�� �������� ����, �ּ� ���� ���� (n:����ġ�� �ִ밪)
void Init_Graph(Heap* h, int n);

// ������ ������ ���� ����
void Insert_Edge(int v1, int v2, int key, Heap* h); 

//====================�� �ڷᱸ��===========================

// �ּ� �� Ʈ���� �����ϱ� ���� ����ü�� �ʱ�ȭ
Heap* Init_Heap(void);

// ������ �ּ��� Ʈ���� �����ϰ� heapify�ؼ� ���������͸� �ּ��� ������ �籸��
void Input_Heap(Edge* e, Heap* h);

// ���� �ּ��� Ʈ������ ���� ���� ����ġ�� ���� ���� �ּҸ� ���� �� ��ȯ
Edge* Delete_Heap(Heap* h);

// �ּ� �� ���� ��� ���
void Print_Heap(Heap* h);   

// MST�۵� ���� = ����ġ�� �ּ��̰� ���� �׷����� ������� ����Ŭ�� �̷��� �ʴ� �������� �׷����� ����
void Start_Kruskal(Heap* h);

int main() {

    // ���� ���� �� �ڷᱸ�� �ʱ�ȭ
    Heap* h = Init_Heap();

    // �� �� ����ü�� �׷��� ���� ���� �����ؼ� ���, �ּ������� heapify
    Init_Graph(h, 300);

    // 
    Print_Heap(h);

    Start_Kruskal(h);

    return 0;
}
/////////////////////union_find//////////////////////
void union_parent_init(void) { for (int i = 0; i < MAX_VERTEX; i++) parent[i] = i; } // ������ ã�� �ʱ�ȭ
int get_parent(int index) { // �θ��� Ȯ��, ������ ���� ������ Ȯ��
    if (parent[index] == index)  return index;
    return get_parent(parent[index]);
}
void union_parent(int x, int y) { // �θ��� ��ġ��, ū �ε��� ������ ���� �ε��� ������ ����
    x = get_parent(x); //�θ��� �ε����� ��� ��
    y = get_parent(y);
    if (x < y) parent[y] = x;
    else parent[x] = y;
}
int find_parent(int x, int y) { // �θ��� �� & Ȯ��
    x = get_parent(x); //�θ��� �ε����� ��� ��
    y = get_parent(y);
    if (x == y)  return 1;
    else return 0;
}



/////////////////////graph//////////////////////
void Init_Graph(Heap* h, int n) {//-------------������ ����ġ�� �������� ����, �ּ� ���� ���� (n:����ġ�� �ִ밪)
    srand((unsigned int)time(NULL));
    int ran_num;
    for (int i = 0; i < MAX_VERTEX; i++) { // �����
        for (int j = 0; j < MAX_VERTEX; j++) { // ������
            ran_num = (rand() % n) + 1; // ����� -> ������ ���� ����ġ
            printf("n = %3d  ", h->n); // ���� ��ȣ(����)
            printf("  Random number: %d\n", ran_num);
            Insert_Edge(i, j, ran_num, h); //    ������� ������ ����ü Edge�� �����ش�.
        }
    }
}
/////////////////////Heap//////////////////////
Heap* Init_Heap(void) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->n = 0;  //    �� Ʈ�� ���� ����� �������� ������ �ʱ�ȭ���ش�.
    return h;
}
void Input_Heap(Edge* e, Heap* h) { // �ּ� �� �߰�
    int i = ++(h->n); // ������ �� ��ȣ & ���� ���� ��
    while (i != 1 && e->key < h->heap[i / 2]->key) {// �θ���� �� �� ��ȯ
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = e;
}
Edge* Delete_Heap(Heap* h) { //���� ������ �ִ� �ּ� ����ġ ���� ������ ��ȯ
    Edge* re = h->heap[1]; // ����ġ ���� ���� root ����
    Edge* tmp = h->heap[(h->n)--]; // ������ �� ���� ���� & ���� �� 1 ����
    int pr = 1, ch = 2;
    while (ch <= h->n) { // shift down �ݺ���
        if (ch < h->n && h->heap[ch]->key > h->heap[ch + 1]->key) ch++; // �ڽ� ��� ���� & ������ ��
        if (tmp->key <= h->heap[ch]->key) break; // �θ� ���� �ڽ� ��� �� ������ ��
        h->heap[pr] = h->heap[ch]; //�θ� & �ڽ� ��ȯ
        pr = ch; // �ڽ� - > �θ� �ε����� ����
        ch *= 2; // �ڽ� - > �� �Ʒ� �ڽ� �ε����� ����
    }
    h->heap[pr] = tmp; // ������ ��� ���� ��ġ ����
    return re; // ��Ʈ ��� ��ȯ
}
void Print_Heap(Heap* h) { // ���� ���� Ʈ�� ������ ���� ��� pow(2, n)
    if (h->n != 0) {
        printf("\n");
        int n = 1;
        for (int i = 1; i <= h->n; i++) {
            printf("%3d   ", h->heap[i]->key);
            if (i == (int)pow(2, n) - 1) {
                printf("\n");
                n++;
            }
        }
        printf("\n\n");
    }
}
/////////////////////Edge ����//////////////////////
void Insert_Edge(int v1, int v2, int key, Heap* h) {//������ ������ ������ ����ü�� ����, �ּ� �� �߰�
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->v1 = v1;
    e->v2 = v2;
    e->key = key;
    Input_Heap(e, h);
}
/////////////////////�ּ� ���� Ʈ��(MST, Minimum Spanning Tree)//////////////////////
int Link_Vertex_gm(int s1, int s2, int key) {//s1, s2�� ������ ���θ� �˻��� �� �׷����� �߰�
    if (!find_parent(s1, s2)) {//�� ����� �θ��尡 ���� ���� == �������� �ƴ� == ����Ŭ�� �������� ����
        union_parent(s1, s2);
        printf("Success Link(key=%d): [%d] and [%d]\n\n", key, s1, s2);
        return 1;
    }
    else { // s1, s2 ����Ŭ�� ����
        printf("Fail Link(key=%d): [%d] and [%d]\n\n", key, s1, s2); return 0;
    }
}
void Start_Kruskal(Heap* h) {
    Edge* tmp;
    int end = 0;
    int n = h->n;
    union_parent_init();
    for (int i = 0; i < n; i++) {
        tmp = Delete_Heap(h); // �ּ� ����ġ ���� ���� (�ּ� �� ��Ʈ ���)
        end += Link_Vertex_gm(tmp->v1, tmp->v2, tmp->key);
        //if (end == MAX_VERTEX - 1) break; // ����� �� - 1 == ������ ��
    }
}

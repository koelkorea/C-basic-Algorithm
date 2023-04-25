// �׷����� ǥ���ϴ� ���
//  1. ���� ���
//     : 2���� �迭�� �׷��� ǥ�� 
//       -> (���) x���� ���۳��, y���� ���������� �ܹ��� ���� ������ �׷����� ǥ��
//       -> (������) ������ 10�� �̻� �Ѿ�� ������ ������

// (�������) ��������� ���� graph ���� - 2���� �迭�� �̿��� ���� ���� (0 1 2 �ﰢ���� 3�� 2�� ����� ����)
#include <stdio.h>
#include <stdlib.h>

// �׷��� ����ü
typedef struct graph {

    // ������ ����
    int verCount;

    // ���� �Ҵ� �� 2���� �迭�� �ּ� ������ 2�� int �����ͺ��� arr
    //  -> �迭�� ������ �����Ͷ�� �� ��� + int���� �迭�� ��ġ�� ������ �� int������ ���� ������� �̷��� �迭�� ��ġ�� ������ �� �ִ� ���� Ÿ�� = 2�� int ������ ������ ���� arr
    //     -> *arr = int ���� �������� �����迭 ������ (= *(arr + i)��  int ���� �������� �����迭�� �� �࿡ ���� ����!)
    //         -> *(arr + i) = int �迭��[i][0] �޸� ��ġ�� ����ȿ��
    //            -> *(arr + i) + k = int �迭��[i][k] �޸� ��ġ�� ����ȿ�� 
    //            -> *( *(arr + i) + k ) = int �迭��[i][k] ��
    //  -> �׷��� �̳༮�� graph ����ü�� �Ϻδ�? = �������� �� �ս��� �� �ɼ��� �þ (->�� ����ġ�� �׳� ������ ������ ���ٴ� �ǹ�)
    //     -> (���) graph->arr[i][k] = *(graph->arr[i] + k) �ǹ� 
    //         -> *(arr + i) = graph->arr[i]�� �޸� ��ġ = graph->arr[i][0]�� �޸� ��ġ
    //            -> *(arr + i) + k = graph->arr[i] + k = graph->arr[i][k]�� �޸� ��ġ
    //            -> (�߿�!) *( *(arr + i) + k ) = *(graph->arr[i] + k) = graph->arr[i][k] ���� 
    int** arr;

}graph;

// �׷��� ����ü �ʱ�ȭ(�׷��� ����ü �޸� ��ġ�ּ�, ���ϴ� ������ ������ �Ķ����)
void graphInitialize(graph* p, int count) {

    // ������ ������ �׷��� ������ �Է� 
    p->verCount = count;

    // �׷��� ������ ���� int�����ͺ����� �޴� �����迭(�� �࿡�� �� ���� �ٸ� int�迭�� ���� ������ int�迭 �ּҸ� ��ġ��) ������ ���� �޸� �Ҵ��ϰ� �� �����ּ��� 2�� �����ͺ����� ����
    p->arr = (int**)calloc(count, sizeof(int*));

    // 2���� �迭�� ǥ���ϱ� ���� int�迭�� ���������ϰ�
    //  -> �� �ּҸ� 2�� int �����ͺ����� p->arr�� �� ��(p->arr[i] == *( (p->arr) + 1) )���ٿ� �Է�
    for (int i = 0; i < count; i++) {

        // ���� int�����͹迭�� �� �࿡ int�迭�� �޸� �����ּҰ��� �Է� (�Ҵ� ��ü�� ����� �� * int ũ�� ��ŭ)
        p->arr[i] = (int*)calloc(count, sizeof(int)); ;
    }
}

// ����(Directed)�� �ִ� �׷��� ���� �߰��ϱ�
//  -> ������ x��, ������ y���� ��ǥ�� 1�� �ִ½�
void addDirectedEdge(graph* p, int src, int dest) {
    p->arr[src][dest] = 1;
}

// ������(Undirected)�� �ִ� �׷��� ���� �߰��ϱ� (���� �׷����� ����, �� �������� �߰�)
void addUndirectedEdge(graph* p, int src, int dest) {

    addDirectedEdge(p, src, dest);
    addDirectedEdge(p, dest, src);
}

// �׷��� ���� ���
void display(graph* p) {

    printf("\n\n *** ���� ���� ��Ȳ ***\n\n");

    for (int i = 0; i < p->verCount; i++) {  //vertex�� ������ŭ �ݺ�

        printf("����� %d => ", i);

        for (int j = 0; j < p->verCount; j++) {

            // (���) graph->arr[i][k] = *(graph->arr[i] + k) �ǹ� (->�� ����ġ�� �׳� ������ ������ ���ٴ� �ǹ�)
            printf("%d ", p->arr[i][j]);
        }

        printf("\n");
    }
}

// �׷��� �޸� �����Ҵ� ����
void memoryFree(graph* p) {

    for (int i = 0; i < p->verCount; i++) {

        free(p->arr[i]); //free(������); �����Ͱ� ����Ű�� �޸𸮰� ����
        printf("%d�� ���� �޸� ����\n", i);
    }

    free(p->arr);
    printf("������ �迭 ���� �޸� ����\n");
}

int main() {

    graph grp;
    graphInitialize(&grp, 4); //����ü, ������ ����

    // �ǵ��� ���� �߰�
    addUndirectedEdge(&grp, 0, 1); //����ü, �����, ������
    addUndirectedEdge(&grp, 0, 2); //����ü, �����, ������
    addUndirectedEdge(&grp, 1, 2); //����ü, �����, ������
    addUndirectedEdge(&grp, 2, 3); //����ü, �����, ������

    display(&grp);
    memoryFree(&grp);

    return 0;
}

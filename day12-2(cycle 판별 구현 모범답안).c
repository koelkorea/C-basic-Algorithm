//  # ������ ã��(Union-Find) & ���μ� ����(DisJoint-Set) -> Cycle �Ǻ���
//     1. �� �����鿡 ���� �ٸ� PK��(= ������ index)�� �ο��� �迭�� �ϳ� �ż� �� �ʱ�ȭ (���: �׷����� �����ϴ� ���� �׷� ��Ÿ�� PK��)
//     2. �� ���� ���� ��, ���� PK�� ������ ���� Ȯ�� (= ���� ���� �׷쿡 ���ϴ��� Ȯ��)
//        -> ����   Ȯ��  => �ش� ��Ʈ�� �ǳ� ��
//        -> ���� X Ȯ��  => �� ���� ����ó���ϰ�, �� ���� �� �� ���� �׷� ���� ������ ������, ������ 1���� ���� ��� �������� �׷찪�� ���� (= ���������δ� 0�� index�� ����)
//     3. 2���� �ݺ��ؼ�, �迭 ��� ����� ���� �ּҰ�(= 0)�̸� ����ó�� ��

// ���ο��� ���ø� ���� ������ ã��(Union-Find) & ���μ� ����(DisJoint-Set) ���� �ڵ�
//  -> ������ ����Ȯ��, �պ������ �����ϳ�.. ���� �̰ɷ� cycle ���� ������� �����Ѱ� �ƴ� = �ּҽ���Ʈ�� ������ Ǯ �� ����
#include <stdio.h>

// �ش� ������ �Ҽ� ����(= �θ�) Ȯ�� (�� ������ �Ҽ� ���� ���ϴ� find_parent�� �κ�����) 
int get_parent(int* parent, int index) {

	// if �ش� ���� INDEX�� �ش��ϴ� ���չ迭�� ��Ұ� = ���� ������ INDEX�� 
	//  -> �� ������ index�� ����ϱ�
	if (parent[index] == index) {
		return index;
	}

	// ����� �������� �� ���°� �ƴ��� �Ǹ���?
	//  -> ������� ������� ���� ������ pk���� ������ ���� ������ ��ġ�� index�� ã�Ƴ�����
	return get_parent(parent, parent[index]);
}

// �� ������ ���� ���յ� �ϳ��� ��ġ�� = �� ���� �պ��ϱ�
void union_parent(int* parent, int x, int y) {

	// �� ������ ���� ���� ����(����)�� ���� index�� ������ Ȯ��
	x = get_parent(parent, x);
	y = get_parent(parent, y);

	// �ڵ�1) ������ pk���� ū ������, �������� ���� ������ pk�� ����ġ���(�� �� �������� pk������ �� �ٲ���)
	//if (x < y) {
	//	parent[y] = x;
	//}
	//else {
	//	parent[x] = y;
	//}

	// �ڵ�2) ������ pk���� ū ������, �������� ���� ������ ������ pk�� ����ġ��� (������ �� �� ��������)
	if (x < y) {

		for (int i = 0; i < 10; i++) {
			if (parent[i] == y) {
				parent[i] = x;
			}
		}

	}
	else {

		for (int i = 0; i < 10; i++) {

			if (parent[i] == x) {
				parent[i] = y;
			}
		}
	}

}

// �� ������ ���� ���� �Ҽӿ��� Ȯ��
int find_parent(int* parent, int x, int y) {

	// �� ������ ���� ���� ����(����)�� ���� index�� ������ Ȯ��
	x = get_parent(parent, x);
	y = get_parent(parent, y);

	// ���߰� ���� = ������ ����
	if (x == y) {
		return 1;
	}
	else {
		return 0;
	}
}

// �� ������ ���� ����PK���� �����ִ� �迭 ��ü ��ȸ
//  -> ���� ������ ���� ������ ��� �ǵ��� üũ
void display(int* arr, int num) {

	for (int i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {

	// ������ ���� ���� �Ǻ��� �迭 (������ ���� ���� = �θ�)
	int parent[10];

	// �ϴ� �������� ���Ǿ� �����Ƿ�, ���� �ٸ����� ����PK������ ��
	for (int i = 0; i < 10; i++) {
		parent[i] = i;
	}

	display(parent, 10);

	union_parent(parent, 0, 1);
	display(parent, 10);

	union_parent(parent, 1, 2);
	display(parent, 10);

	union_parent(parent, 2, 3);
	display(parent, 10);

	union_parent(parent, 4, 5);
	display(parent, 10);

	union_parent(parent, 5, 6);
	display(parent, 10);

	union_parent(parent, 6, 7);
	display(parent, 10);

	union_parent(parent, 8, 9);
	display(parent, 10);

	if (find_parent(parent, 3, 6) == 1) {
		printf("3�� 6�� ����Ǿ� �ֽ��ϴ�.\n");
	}
	else {
		printf("3�� 6�� ����Ǿ� ���� �ʽ��ϴ�.\n");
	}

	union_parent(parent, 3, 6);
	display(parent, 10);

	if (find_parent(parent, 1, 5) == 1) {
		printf("1�� 5�� ����Ǿ� �ֽ��ϴ�.\n");
	}
	else {
		printf("1�� 5�� ����Ǿ� ���� �ʽ��ϴ�.\n");
	}

	if (find_parent(parent, 2, 6) == 1) {
		printf("2�� 6�� ����Ǿ� �ֽ��ϴ�.\n");
	}
	else {
		printf("2�� 6�� ����Ǿ� ���� �ʽ��ϴ�.\n");
	}

	if (find_parent(parent, 3, 7) == 1) {
		printf("3�� 7�� ����Ǿ� �ֽ��ϴ�.\n");
	}
	else {
		printf("3�� 7�� ����Ǿ� ���� �ʽ��ϴ�.\n");
	}

	return 0;
}



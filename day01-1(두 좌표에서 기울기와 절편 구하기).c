// �� ��ǥ�� ����ü�� �־�������, �� ��ǥ�� ����� y������ ���ض�
#include <stdio.h>

typedef struct {
	int x;
	int y;
}PointType;

// ���⸦ ���� �� �̻��� ������ 0�� ��ȯ(<-> �и� 0�� ��� ��� ���� �Ұ��ϴ�, ����ó�� -1�� ��ȯ�ϰ� ��)
int get_line_parameter(PointType p1, PointType p2, float* slope, float* yintercept) {

	// �и� 0�� �� ��� -> ���� ó��
	if (p1.y == p2.y) {
		return -1;
	}

	// �� ��ǥ�� ����-> �̸� slope�� ������ ������ �ּҸ� ������ �ϴ� ������ �־�� (slope�� �����ض�)
	*slope = (float)(p2.y - p1.y) / (p2.x - p1.x);

	// y������ ���� -> �̸� yintercept�� ������ ������ �ּҸ� ������ �ϴ� ������ �־�� (yintercept�� �����ض�)
	*yintercept = p1.y - (*slope * p1.x);

	return 0;
}

int main() {

	PointType point1;		// ��ǥ1
	PointType point2;		// ��ǥ2

	float slope;			// ����
	float yintercept;		// y����

	printf_s("Point 1 : ");
	scanf_s("%d %d", &(point1.x), &(point1.y));

	printf_s("Point 2 : ");
	scanf_s("%d %d", &(point2.x), &(point2.y));

	if (get_line_parameter(point1, point2, &slope, &yintercept) == 0) {
		printf_s("[����]  : %f , [y����] : %f", slope, yintercept);
	}
	else {
		printf_s("[����] : y1�� y2�� ���� �����ϴ�. �ٽ� �Է����ּ���.... \n\n");
	}


	//printf_s("[����]  : %f , [y����] : %f");

	return 0;
}
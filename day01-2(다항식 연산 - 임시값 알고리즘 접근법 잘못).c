// ���׽� ����ü�� ���, ������ ǥ�� ��, �̸� �迭�� �ؼ� �� ǥ��..
//	-> �� 2���� ����ü �迭�� �̿��ؼ�, �����ϴ� �˰��� ¥����
//		-> temp ����ü�� �̿��ؼ� �õ��غ�����.. ���� (index ��ü �̵����� ����, temp�� �� ������ �������� ����)
#include <stdio.h>
#define MAX 3

typedef struct {
	int coef;		// ���
	int expose;		// ����
}Polynomial;

// �� ���� ������ �� ��, �������� temp�� ������ ��� �����ߴµ�, �׷� ���� ����� 3���� �ǰ�, �����ؾ� �� ���� 1�� �̻��� �Ǹ� ��� ���̴� ���� �߻�
void polynomial_go(Polynomial* t1, Polynomial* t2, Polynomial* answer) {

	Polynomial temp = {0, 0};

	for (int i = 0; i < MAX; i++) {

		if(t1[i].coef != 0){

			if (i != 0) {
				printf_s(" + ");
			}

			printf_s("%2d ^%2d", t1[i].coef, t1[i].expose);

		}
	}

	printf_s("\n");

	for (int i = 0; i < MAX; i++) {

		if (t2[i].coef != 0) {

			if (i != 0) {
				printf_s(" + ");
			}

			printf_s("%2d ^%2d", t2[i].coef, t2[i].expose);
		}
	}

	printf_s("\n");
	printf_s("--------------------------------------------------------------------------\n");

	for (int i = 0; i < MAX; i++) {

		if (i != 0) {
			printf_s(" + ");
		}

		if (t1[i].expose == t2[i].expose) {

			if (t1[i].expose == 0) {

				answer[i].coef = t1[i].coef + t2[i].coef + temp.coef;
				answer[i].expose = t1[i].expose;

			}else {

				answer[i].coef = t1[i].coef + t2[i].coef;
				answer[i].expose = t1[i].expose;
			}

			printf_s("%2d ^%2d", answer[i].coef, answer[i].expose);

		}else if (t1[i].expose > t2[i].expose) {

			if (temp.expose == t1[i].expose) {

				answer[i].coef = t1[i].coef + temp.coef;

			}else {

				answer[i].coef = t1[i].coef;
			}

			temp = t2[i];
			answer[i].expose = t1[i].expose;

			printf_s("%2d ^%2d", answer[i].coef, answer[i].expose);

		}else if (t1[i].expose < t2[i].expose) {

			if (temp.expose == t2[i].expose) {

				answer[i].coef = t2[i].coef + temp.coef;

			}else {
				answer[i].coef = t2[i].coef;
			}

			temp = t1[i];
			answer[i].expose = t2[i].expose;

			printf_s("%2d ^%2d", answer[i].coef, answer[i].expose);

		}

	}

}

int main() {

	Polynomial terms1[MAX] = { { 2, 1 }, { 2, 0 } };
	Polynomial terms2[MAX] = { { 2, 2 }, { 10, 1 }, { 3, 0 } };
	Polynomial answer[MAX];

	polynomial_go(terms1, terms2, answer);



	//printf_s("[����]  : %f , [y����] : %f");

	return 0;
}
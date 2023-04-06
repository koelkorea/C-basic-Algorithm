#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <time.h>				// time () �Լ� ��� �����ϰ� ��
#define MAX 10

typedef struct {
	int coef;		// ���
	int expose;		// ����
}Polynomial;

// ���׽� ��¿� �Լ� (���׽� ����ü ������, ���� ���׽��� ��Ұ��� ���� �ִ�ġ(0,0)�� �� �� index������ �ݺ��� ����)
void polynomial_print(Polynomial* polynomial, int num) {

	// ���׽��� �ִ� �������� ����� 0�� ���ö������� �ݺ�
	for (int i = 0; i < num; i++) {

		if (polynomial[i].coef != 0) {

			// +�� ù �׿� �ش��ϴ� �Լ� ���Ŀ��� �� �������� ����
			if (i != num - 1) {

				printf_s("%2d ^%2d + ", polynomial[i].coef, polynomial[i].expose);
			}
			else {
				printf_s("%2d ^%2d", polynomial[i].coef, polynomial[i].expose);
			}
		}
	}
}

// ���׽�1, ���׽�2�� index 0������ ����� ���ذ���, answer �迭�� ���� �߰� + ��� �� index 1 �߰� (���׽�1,2�� ����� �� �� 0�� ������ ����)
//	-> ������ ������, ����� ���ؼ� ����ϰ�, ������ index�� 1�߰�
//	-> ������ �ٸ���, ������ ū ���� ����� ������ ����ϰ�, ū ���� index�� 1�߰�
//	-> �Էµ� �迭�� index���ظ� return
int polynomial_go(Polynomial* t1, Polynomial* t2, Polynomial* answer) {

	int index_t1 = 0, index_t2 = 0, result_index = 0;

	while (result_index != MAX) {

		if (t1[index_t1].coef != 0 || t2[index_t2].coef != 0) {

			if (t1[index_t1].expose == t2[index_t2].expose) {

				answer[result_index].coef = t1[index_t1].coef + t2[index_t2].coef;
				answer[result_index].expose = t1[index_t1].expose;

				index_t1++;
				index_t2++;

			}else if (t1[index_t1].expose > t2[index_t2].expose) {

				answer[result_index] = t1[index_t1];
				index_t1++;

			}else if (t1[index_t1].expose < t2[index_t2].expose) {

				answer[result_index] = t2[index_t2];
				index_t2++;
			}

			result_index++;

		}else {

			break;
		}
	}

	return result_index;
}

// ���׽Ŀ� �� �Է�
//	-> ���� ����� 0�̿��� ���� ������, ���� �����ϰ� console�� ������� ���� ���� print �Լ��� ���� index��ġ�� �����ϴ� ��ġ�� 1�ø��� 
//	-> ����� 0�� ���� ���� ���׽� �迭�� ���� ���� ����.. (�迭�� �ִ�ġ���� �ݺ��� ������, ����� 0�� ���� ��ġ��ŭ ������ �迭���� ����ְ�, max���� num_tern�� ��ġ�� ����)
int polynomial_input(Polynomial* polynomial, int max) {

	int num_of_term = 0;

	for (int i = 0; i < max; i++) {

		Polynomial temp;

		temp.coef = rand() % 10;
		temp.expose = MAX - 1 - i;

		if (temp.coef != 0) {
			polynomial[num_of_term].coef = temp.coef;
			polynomial[num_of_term].expose = temp.expose;
			num_of_term++;
		}
	}
	return num_of_term;
}

int main() {

	srand((unsigned int)time(NULL));

	// ���׽� 1 �迭
	Polynomial terms1[MAX] = {0};
	// ���׽� 2 �迭
	Polynomial terms2[MAX] = {0};
	// ����� ���׽� �迭 
	Polynomial answer[MAX] = {0};

	int terms1_num = polynomial_input(terms1, MAX);
	int terms2_num = polynomial_input(terms2, MAX);

	polynomial_print(terms1, terms1_num);
	printf_s("\n");

	polynomial_print(terms2, terms2_num);
	printf_s("\n");

	printf_s("--------------------------------------------------------------------------\n");
	int answer_num = polynomial_go(terms1, terms2, answer);
	polynomial_print(answer, answer_num);

	return 0;
}
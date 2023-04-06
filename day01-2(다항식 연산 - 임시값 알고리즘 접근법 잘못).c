// 다항식 구조체를 계수, 차수로 표현 후, 이를 배열로 해서 식 표현..
//	-> 이 2개의 구조체 배열을 이용해서, 덧셈하는 알고리즘 짜봐라
//		-> temp 구조체를 이용해서 시도해봤지만.. 실패 (index 전체 이동으로 인해, temp에 들어갈 내용이 많아지면 실패)
#include <stdio.h>
#define MAX 3

typedef struct {
	int coef;		// 계수
	int expose;		// 차수
}Polynomial;

// 두 항의 차수를 비교 후, 작은쪽을 temp로 보내고 계속 가려했는데, 그럼 비교의 대상이 3개가 되고, 보관해야 할 수가 1개 이상이 되면 계산 꼬이는 문제 발생
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



	//printf_s("[기울기]  : %f , [y절편] : %f");

	return 0;
}
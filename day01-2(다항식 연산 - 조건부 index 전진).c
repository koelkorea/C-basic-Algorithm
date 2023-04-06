#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>				// time () 함수 사용 가능하게 함
#define MAX 10

typedef struct {
	int coef;		// 계수
	int expose;		// 차수
}Polynomial;

// 다항식 출력용 함수 (다항식 구조체 포인터, 현재 다항식의 요소값의 개수 최대치(0,0)이 안 들어간 index까지만 반복을 목적)
void polynomial_print(Polynomial* polynomial, int num) {

	// 다항식의 최대 차수까지 계수가 0이 나올때까지만 반복
	for (int i = 0; i < num; i++) {

		if (polynomial[i].coef != 0) {

			// +는 첫 항에 해당하는 함수 이후에는 안 찍히도록 조건
			if (i != num - 1) {

				printf_s("%2d ^%2d + ", polynomial[i].coef, polynomial[i].expose);
			}
			else {
				printf_s("%2d ^%2d", polynomial[i].coef, polynomial[i].expose);
			}
		}
	}
}

// 다항식1, 다항식2의 index 0번부터 계수를 비교해가며, answer 배열에 값을 추가 + 출력 후 index 1 추가 (다항식1,2의 계수가 둘 다 0이 나오면 종료)
//	-> 차수가 같으면, 계수를 더해서 출력하고, 양자의 index를 1추가
//	-> 차수가 다르면, 차수가 큰 쪽의 계수와 차수만 출력하고, 큰 쪽의 index만 1추가
//	-> 입력된 배열의 index수준만 return
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

// 다항식에 값 입력
//	-> 만약 계수가 0이외의 값이 나오면, 값을 투입하고 console에 결과값을 띄우기 위한 print 함수를 위한 index수치를 저장하는 수치를 1올린다 
//	-> 계수가 0이 나올 경우는 다항식 배열에 값을 넣지 않음.. (배열의 최대치까지 반복을 돌리면, 계수가 0이 나온 수치만큼 뒷쪽의 배열들이 비어있고, max값과 num_tern의 수치가 차이)
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

	// 다항식 1 배열
	Polynomial terms1[MAX] = {0};
	// 다항식 2 배열
	Polynomial terms2[MAX] = {0};
	// 정답용 다항식 배열 
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
// 두 좌표가 구조체로 주어졌을때, 그 좌표의 기울기와 y절편을 구해라
#include <stdio.h>

typedef struct {
	int x;
	int y;
}PointType;

// 기울기를 구할 때 이상이 없으면 0을 반환(<-> 분모가 0인 경우 계산 성립 불가하니, 에러처리 -1을 반환하게 함)
int get_line_parameter(PointType p1, PointType p2, float* slope, float* yintercept) {

	// 분모가 0이 될 경우 -> 에러 처리
	if (p1.y == p2.y) {
		return -1;
	}

	// 두 좌표의 기울기-> 이를 slope의 포인터 변수의 주소를 역참조 하는 값으로 넣어라 (slope에 대입해라)
	*slope = (float)(p2.y - p1.y) / (p2.x - p1.x);

	// y절편의 기울기 -> 이를 yintercept의 포인터 변수의 주소를 역참조 하는 값으로 넣어라 (yintercept에 대입해라)
	*yintercept = p1.y - (*slope * p1.x);

	return 0;
}

int main() {

	PointType point1;		// 좌표1
	PointType point2;		// 좌표2

	float slope;			// 기울기
	float yintercept;		// y절편

	printf_s("Point 1 : ");
	scanf_s("%d %d", &(point1.x), &(point1.y));

	printf_s("Point 2 : ");
	scanf_s("%d %d", &(point2.x), &(point2.y));

	if (get_line_parameter(point1, point2, &slope, &yintercept) == 0) {
		printf_s("[기울기]  : %f , [y절편] : %f", slope, yintercept);
	}
	else {
		printf_s("[에러] : y1와 y2의 값이 같습니다. 다시 입력해주세요.... \n\n");
	}


	//printf_s("[기울기]  : %f , [y절편] : %f");

	return 0;
}
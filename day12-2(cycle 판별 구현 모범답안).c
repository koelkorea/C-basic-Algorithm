//  # 합집합 찾기(Union-Find) & 서로소 집합(DisJoint-Set) -> Cycle 판별법
//     1. 각 정점들에 각기 다른 PK값(= 정점의 index)을 부여한 배열을 하나 신설 후 초기화 (요소: 그래프에 존재하는 연결 그룹 나타낸 PK값)
//     2. 두 정점 연결 시, 같은 PK를 가진거 여부 확인 (= 서로 같은 그룹에 속하는지 확인)
//        -> 같음   확인  => 해당 루트는 건너 뜀
//        -> 같지 X 확인  => 그 둘을 연결처리하고, 두 정점 중 더 작은 그룹 값을 가지는 쪽으로, 나머지 1쪽이 속한 모든 정점들의 그룹값을 통일 (= 최종적으로는 0번 index를 가짐)
//     3. 2번을 반복해서, 배열 모든 요소의 값이 최소값(= 0)이면 종료처리 함

// 도로연결 예시를 통한 합집합 찾기(Union-Find) & 서로소 집합(DisJoint-Set) 구현 코드
//  -> 정점별 세력확인, 합병기능은 존재하나.. 아직 이걸로 cycle 여부 연계까지 구현한건 아님 = 최소신장트리 문제는 풀 수 없음
#include <stdio.h>

// 해당 정점의 소속 집합(= 부모) 확인 (두 정점의 소속 집합 비교하는 find_parent의 부분집합) 
int get_parent(int* parent, int index) {

	// if 해당 정점 INDEX에 해당하는 집합배열의 요소값 = 현재 정점의 INDEX값 
	//  -> 그 정점의 index를 출력하기
	if (parent[index] == index) {
		return index;
	}

	// 연결된 정점없는 고립 상태가 아님이 판명나면?
	//  -> 재귀적인 방법으로 현재 세력의 pk값을 가지는 오야 정점이 위치한 index를 찾아나서기
	return get_parent(parent, parent[index]);
}

// 두 정점이 속한 집합들 하나로 합치기 = 두 세력 합병하기
void union_parent(int* parent, int x, int y) {

	// 두 정점이 각각 속한 세력(집합)의 오야 index가 누군지 확인
	x = get_parent(parent, x);
	y = get_parent(parent, y);

	// 코드1) 오야의 pk값이 큰 쪽으로, 없어지는 세력 오야의 pk값 갈아치우기(단 그 조직원들 pk까지는 안 바꿨음)
	//if (x < y) {
	//	parent[y] = x;
	//}
	//else {
	//	parent[x] = y;
	//}

	// 코드2) 오야의 pk값이 큰 쪽으로, 없어지는 세력 조직원 전원의 pk값 갈아치우기 (이쪽이 좀 더 직관적임)
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

// 두 정점의 같은 집합 소속여부 확인
int find_parent(int* parent, int x, int y) {

	// 두 정점이 각각 속한 세력(집합)의 오야 index가 누군지 확인
	x = get_parent(parent, x);
	y = get_parent(parent, y);

	// 오야가 같다 = 세력이 같음
	if (x == y) {
		return 1;
	}
	else {
		return 0;
	}
}

// 각 정점이 속한 집합PK값을 보여주는 배열 전체 조회
//  -> 현재 정점과 간선 연결이 어떤지 판도를 체크
void display(int* arr, int num) {

	for (int i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {

	// 정점별 속한 집합 판별용 배열 (정점이 속한 세력 = 부모)
	int parent[10];

	// 일단 정점별로 고립되어 있으므로, 각각 다른값을 집합PK값으로 줌
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
		printf("3과 6는 연결되어 있습니다.\n");
	}
	else {
		printf("3과 6는 연결되어 있지 않습니다.\n");
	}

	union_parent(parent, 3, 6);
	display(parent, 10);

	if (find_parent(parent, 1, 5) == 1) {
		printf("1과 5는 연결되어 있습니다.\n");
	}
	else {
		printf("1과 5는 연결되어 있지 않습니다.\n");
	}

	if (find_parent(parent, 2, 6) == 1) {
		printf("2과 6는 연결되어 있습니다.\n");
	}
	else {
		printf("2과 6는 연결되어 있지 않습니다.\n");
	}

	if (find_parent(parent, 3, 7) == 1) {
		printf("3과 7는 연결되어 있습니다.\n");
	}
	else {
		printf("3과 7는 연결되어 있지 않습니다.\n");
	}

	return 0;
}



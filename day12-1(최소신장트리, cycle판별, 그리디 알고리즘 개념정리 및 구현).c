// 합집합 찾기(Union-Find) & 서로소 집합(DisJoint-Set)
//  : 그래프의 Cycle 간선 판별법
// 
//  # 합집합 찾기(Union-Find) & 서로소 집합(DisJoint-Set) 로직
//     1. 각 정점들에 각기 다른 PK값(= 정점의 index)을 부여한 배열을 하나 신설 후 초기화 (요소: 그래프에 존재하는 연결 그룹 나타낸 PK값)
//     2. 두 정점 연결 시, 같은 PK를 가진거 여부 확인 (= 서로 같은 그룹에 속하는지 확인)
//        -> 같음   확인  => 해당 루트는 건너 뜀
//        -> 같지 X 확인  => 그 둘을 연결처리하고, 두 정점 중 더 작은 그룹 값을 가지는 쪽으로, 나머지 1쪽이 속한 모든 정점들의 그룹값을 통일 (= 최종적으로는 0번 index를 가짐)
//     3. 2번을 반복해서, 배열 모든 요소의 값이 최소값(= 0)이면 종료처리 함

// 탐욕(Greedy) 알고리즘
//  : 일단 주어진 현재의 조건에서 가장 최상의 선택을 하다보면 가장 좋은 선택으로 이어진다는 방법에 착안한 최적해 알고리즘
//    ex) A에서 B로 이동하는 최단 경로 찾기
//        최단 작업 우선 스케줄링 (shortest job first scheduling)
//        분할 가능 배낭 문제 (fractional knapsack problem)
//        모든 거점을 연결하고 연결된 전체 길이를 최소화(최소 신장 트리)

//  # 그리디 알고리즘 요구 조건
//    1. 최적 부분 구조(optimal substructure)
//        : 부분의 최적 결과가 전체에도 그대로 적용되어야 할 것
//    2. 그리디 선택(greedy choice)
//        : 그 이전의 선택이 이후에 영향을 주지 않음

// 최소 신장 트리 (MST, Minimum Spanning Tree)
//  : 모든 정점을 연결하고 연결된 간선의 가중치 합이 최소인 트리
//    ex) 상수도관 네트워크 설계 -> 모든 사람에게 수돗물이 전달, 전체 길이는 최소가 되는 것
//        도로 네트워크 설계     -> 필요한 지점에 도로가 연결, 전체 길이는 최소화 되는 것

//  # 최소 신장 트리 (MST, Minimum Spanning Tree) 로직 (얘도 그리디 알고리즘)
//     1. 간선들의 가중치를 기준으로 오름차순으로 정렬
//     2. 가중치 낮은 간선을 선택 (BUT! 선택할 간선이 cycle이 형성되면 제외 -> how? 합집합 찾기, 서로소 집합)
//     3. 정점 - 1개의 간선 수가 될 때까지 2번 반복
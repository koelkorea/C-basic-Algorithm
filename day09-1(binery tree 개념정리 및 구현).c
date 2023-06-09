﻿// 트리(Tree)
//  : 계층적인 구조를 나타내는 자료구조.

//  # 트리의 요소
//    - 루트(root)
//       : 트리의 최상위 노드 (arr[0])
//    - 노드(node)
//       : 각 노드는 자식을 가리키는 포인터와 자신의 데이터가 존재 (= linked list적인 특성 존재)
//    - 간선(edge)
//       : 두 노드를 연결하는 데 사용 (= node의 포인터가 명시적으로 연결된 개념)
//    - 리프(leaf)
//       : 자식이 없는 노드 = 말단 노드 (= 자식을 가리키는 포인터가 없는 linked list)
//    - 높이 or 깊이 (height or depth)
//       : 루트부터 리프까지 가장 긴 경로의 간선 수
//    - 레벨(level)
//       : 루트 ~ 리프노드까지의 경로에 있는 간선 수
//         -> 루트의 레벨 = 0, 거기서 아래로 가지가 하나씩 뻗어 나갈 때 마다 레벨이 1씩 증가
//    - 차수(degree)
//       : 노드가 갖는 자식의 수
//    - 서브트리(subtree) 
//       : 트리 안에서 다시 어떤 노드를 루트로 정하고 그 자손으로 이루어 진 트리

//  # 트리의 개념적 요소
//    - 자식(children)
//       : 한 노드로부터 간선으로 연결 된 바로 아래 레벨의 노드
//    - 부모(parent)
//       : 한 노드에서 가지로 연결 된 바로 위 레벨의 노드
//    - 형제(sibling)
//       : 같은 부모를 가지는 노드들

// 이진 트리(binery tree)
//  : 노드가 '왼쪽 자식'과 '오른쪽 자식'을 갖는 트리 
//    (= 1개의 노드는 최대 이렇게 2개만 자식으로 가질수 있음) 

//  # 특징 및 주의점
//    1. 순서 없이 삽입 시 편향 이진 트리가 될 수 있다.(비효율적)5
//    2. 레벨 i에 속하는 최대 노드수는 2^(i-1)개
//       (= 자신의 위치값 * 2 = 왼쪽자식노드 위치, 자신의 위치값 * 2 + 1 = 오른쪽 자식노드 위치) <-> (부모노드 위치값 = 자신/2)
//       ex) 레벨1(= 높이0)인 노드의 최대숫자 = 1개 (루트 노드)
//           레벨2(= 높이1)인 노드의 최대숫자 = 2개 (루트의 자식 2개)
//           레벨3(= 높이2)인 노드의 최대숫자 = 4개 (루트의 자식 2개의 자식들 4개)
//    3. 높이가 k인 노드의 최댓값은 2^(k+1)-1
//       ex) 레벨1(= 높이0)인 노드의 최대값 = 1 (루트 노드)
//           레벨2(= 높이1)인 노드의 최대값 = 3 (루트 + 자식 2개)
//           레벨3(= 높이2)인 노드의 최대값 = 7 (루트 + 자식 2개 + 자식들의 자식 4개)
//    4. N개의 노드를 가진 트리는 노드를 연결하는 간선이 N-1개
//       ex) 레벨1(= 높이0)인 노드 1개의 간선개수 = 0개 
//           레벨2(= 높이1)인 노드 3개의 간선개수 = 2개 (루트 - 자식 2개)
//           레벨3(= 높이2)인 노드 7개의 간선개수 = 6개 (루트 - 자식 2개 - 자식들의 자식 4개)
//    5. N개의 노드를 가지는 '완전이진트리'의 높이 = log(2)N+1
//       -> N+1 = 2^높이(x)
//       -> 높이(x) = log(2)N+1

//  # 이진트리의 종류(가정 : 아래 번호 순으로 트리 구성)
//    1. 완전 이진트리(포화 이진트리의 정의를 포괄)
//       : 마지막 레벨을 제외한 모든 레벨은 무조건 노드들로 가득 차야 함
//         -> 단! 마지막 레벨은 왼쪽부터 오른쪽 방향으로 노드를 채워야 함
//
//    2. 정 이진트리
//       : 각 노드가 모두 0개 또는 2개의 자식이 있어야 함 (= 자식이 있을거면 무조건 2개가 있어야 함)
//
//    3. 포화 이진트리(완전 이진트리를 완성하면 됨)
//       : leaf 노드(= 자식이 없는 최하 말단노드)들은 반드시 가장 아래에 모여있어야 하며,
//         그 외 모든 레벨의 노드들은 모두 2개의 자식노드가 존재해야 함 
//         (= 포화 = 노드가 존재하는 모든 레벨이 전부 노드로 가득차야 함) 
//          -> 따라서 무조건 대칭형의 모양이 나옴

// 이진트리 탐색법
//  1. 너비 우선 탐색(BFS : Breadth First Search)
//     : 낮은 레벨(0: root)에서 시작해 왼쪽에서 오른쪽 방향으로 노드를 검색 (일반적으로 queue를 이용해서 구현함)
//       -> 한 레벨에서의 검색이 모두 끝나면 다음 레벨 왼쪽으로 내려가는 것
//          ex)           1
//                     2     3
//                   4   5 6   7   순서


//  2. 깊이 우선 탐색(DFS : Depth First Search)
//     : 가장 하단에 위치한 리프까지 내려가면서 노드를 검색하는 방법
//       -> 리프노드에 도달해 더 이상 검색을 진행할 곳이 없을 경우 그 부모에게 돌아가서, 다시 다른쪽 자식 노드로 검색함

//   # DFS(DFS : Depth First Search)의 트리형 자료 조회 원칙 (= 깊이 우선 탐색) 
//     - 해당 노드에 왼쪽과 오른쪽에도 노드가 있다면, 무조건 왼쪽의 노드를 먼저 조회
//     - 앞선 원칙을 지킨다면, 부모노드 순서를 끼워넣을 때 다음과 같이 3가지 순서가 정해지는데, 이 순서는 부모노드를 몇번째(전 - 중 - 후)로 조회하는지에 따라 명칭을 부여
//        -> 부모를 타고 올라갈때도, 결국 루트노드를 보게 되는것도 원래의 원칙에서 기인
//        -> 재귀적인 특성을 가지며, 실제로도 재귀적으로 코드를 구성함
//     - 값의 출력은 노드 - 노드를 타고 나아가다 최종적으로 도달된 노드에 값이 없을 때 이를 출력하는게 원래의 논리
//       (= 원칙적으로는 부모, 왼쪽, 오른쪽 노드가 NULL일시 그 노드의 값을 찍으라고 코드를 짜야하나.. )
//          -> 굉장히 논리적으로나 성능적으로나 번거롭기 그지없으므로, 부모노드를 보는 대신 자신의 값을 찍는거로 대체 (물론 다른 메서드를 통해 원칙적으로 구현은 가능하다..)

//   #  DFS(DFS : Depth First Search)의 트리형 자료 조회법 종류 (= 깊이 우선 탐색) 
//     : 왼쪽과 오른쪽에도 노드가 있다면, 무조건 왼쪽의 노드를 먼저 조회시,
//       부모노드 순서를 끼워넣을 때 다음과 같이 3가지 순서가 정해지는데, 이 순서는 부모노드를 몇번째(전 - 중 - 후)로 조회하는지에 따라 명칭을 부여

//       1. 전위순회(pre-order) : (해당노드의) 부모노드 -> 왼쪽노드 -> 오른쪽노드

//          ex)           1
//                     2     5
//                   3   4 6   7   순서

//       2. 중위순회(in-order)  : 해당노드의) 왼쪽노드 -> 부모노드 -> 오른쪽노드

//          ex)           4
//                     2     6
//                   1   3 5   7   순서

//       3. 후위순회(post-order)  : (해당노드의) 왼쪽노드 -> 오른쪽노드 -> 부모노드

//          ex)           7
//                     3     6
//                   1   2 4   5   순서


// 이진트리 (<-> 이진검색트리)의 깊이우선탐색(DFS)조회 기능 3종세트 구현 코드
//  -> DFS 조회 3종 세트 중 중위순회시 오름차순으로 정렬되는걸 보여주기 위해, 이진검색트리 구조로 정렬이 완료된 정적배열을 사용함
//     (= 원래는 이진트리구조에 값 넣을때 이진검색트리 구조로 값을 정렬하는 로직이 필요)
#include <stdio.h>
#include <stdlib.h>       //	srand(), rand() 함수 사용 가능하게 함
#include <time.h>

typedef int element;

// 이진트리 구현 구조체 (linked list적)
typedef struct treeNode {
    element value;               // 값
    struct treeNode* left;       // (현재 노드기준) 왼쪽 노드의 주소값 
    struct treeNode* right;      // (현재 노드기준) 오른쪽 노드의 주소값 
}treeNode;

// 배열의 데이터 -> 이진트리형식으로 옮기기 (배열의 시작주소, 배열크기, 배열공간 번호)
treeNode* setBinTreeNode(int* arr, int count, int idx) {

    // 트리구조를 저장하기 위한 메모리 동적할당 시작주소값을 받기위한 트리구조체 포인터변수
    treeNode* cur;

    // 동적할당
    cur = (treeNode*)malloc(sizeof(treeNode));

    // 동적할당한 트리 구조체의 역참조값에 파라미터로 입력한 idx(= 배열 공간값)을 참조하여 배열값을 넣어줌
    cur->value = *(arr + idx);
    cur->left = NULL;
    cur->right = NULL;

    // 해당 노드의 left, right에 해당하는 값이 위치한 배열의 공간번호를 담기위한 변수
    int left_from_array_num, right_from_array_num;

    // 해당 노드의 left, right에 해당하는 값이 위치한 배열의 공간번호를 계산
    // (= 자신의 위치값 * 2 = 왼쪽자식노드 위치, 자신의 위치값 * 2 + 1 = 오른쪽 자식노드 위치) <-> (부모노드 위치값 = 자신/2)
    left_from_array_num = idx * 2 + 1;
    right_from_array_num = idx * 2 + 2;

    // 해당 노드의 left, right에 해당하는 배열의 공간값이 위치한 배열의 공간번호가 배열의 크기보다 작으면? (= 왼쪽, 오른쪽 노드가 존재한다면?)
    // -> 그 공간번호를 사용하여 트리노드를 생성하고, 그 주소값을 현재 tree구조체의 왼쪽 노드의 주소를 담는 left, right에 대입
    if (left_from_array_num < count) {
        cur->left = setBinTreeNode(arr, count, left_from_array_num);
    }

    if (right_from_array_num < count) {
        cur->right = setBinTreeNode(arr, count, right_from_array_num);
    }

    return cur;
}

// 해당 트리를 전위순회( [기준 노드] 부모 -> 왼쪽 -> 오른쪽 순으로 조회)하여 조회하는 메서드
//  -> 원칙적으로는 부모, 왼쪽, 오른쪽 노드가 NULL일시 그 노드의 값을 찍으라고 코드를 짜야하나.. 
//     -> 굉장히 논리적으로나 성능적으로나 번거롭기 그지없으므로, 부모노드를 보는 대신 자신의 값을 찍는거로 대체
void displayPreOrder(treeNode* t) {
    if (t) {
        // 원칙적으로는 부모노드를 타고 올라가라고 지정해야 하나.. 루트부터 시작시 어차피 자기자신의 값을 찍어도 같음
        //  : 루트 -> 루트 부모 null -> 루트 왼쪽 노드(r_left) -> r_left의 부모노드 = 루트값 출력
        //  : 루트값 출력 -> 루트 왼쪽 노드(r_left) 값 출력 -> ....
        printf("%d ", t->value);    // 참고로 값의 출력은 printf를 통한 자기자신이 아니라, 메서드를 통해 고도화시켜도 상관없음
        displayPreOrder(t->left);
        displayPreOrder(t->right);
    }
}

// 해당 트리를 중위순회( [기준 노드] 왼쪽 -> 부모 -> 오른쪽 순으로 조회)하여 조회하는 메서드
//  -> 원칙적으로는 부모, 왼쪽, 오른쪽 노드가 NULL일시 그 노드의 값을 찍으라고 코드를 짜야하나.. 
//     -> 굉장히 논리적으로나 성능적으로나 번거롭기 그지없으므로, 부모노드를 보는 대신 자신의 값을 찍는거로 대체
void displayInOrder(treeNode* t) {
    if (t) {
        displayInOrder(t->left);
        printf("%d ", t->value);
        displayInOrder(t->right);
    }
}

// 해당 트리를 후위순회( [기준 노드] 왼쪽 -> 오른쪽 -> 부모 순으로 조회)하여 조회하는 메서드
//  -> 원칙적으로는 부모, 왼쪽, 오른쪽 노드가 NULL일시 그 노드의 값을 찍으라고 코드를 짜야하나.. 
//     -> 굉장히 논리적으로나 성능적으로나 번거롭기 그지없으므로, 부모노드를 보는 대신 자신의 값을 찍는거로 대체
void displayPostOrder(treeNode* t) {
    if (t) {
        displayPostOrder(t->left);
        displayPostOrder(t->right);
        printf("%d ", t->value);
    }
}

// 트리구조 해체의 순서는 노드를 모드 깔끔하게 삭제해야 하니, 부모노드를 가장 나중에 보는 후위순회로 한다
void freeTree(treeNode* t) {
    if (t) {
        freeTree(t->left);
        freeTree(t->right);
        printf("\n노드 삭제 : %d\n", t->value);
        free(t);
    }
}


int main() {

    // 해당 배열은 이진검색트리에 맞게 배열이 끝난 상태... (이에 맞도록 배열을 입력하는건 이진검색트리에서 다룸)
    int arr[] = { 6, 4, 8, 2, 5, 7, 9, 1, 3 };
    treeNode* root = setBinTreeNode(arr, 9, 0);

    printf("\n전위 순회\n");
    displayPreOrder(root);

    // 이진검색트리의 원칙으로 배열이 정렬되었으면 오름차순으로 출력
    printf("\n중위 순회\n");
    displayInOrder(root);

    printf("\n후위 순회\n");
    displayPostOrder(root);

    freeTree(root);

    return 0;
}

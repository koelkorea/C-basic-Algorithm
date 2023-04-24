// 이진검색 트리(binery search tree)
//  : 이진트리의 모든 노드의 값이 'key(왼쪽서브트리) < key(부모[루트]노드) < key(오른쪽서브트리)'의 특성으로 정렬배치 된 특수한 이진트리

//    ex)        5
//            3      7   
//          2   4  6   8
//        1              9

//   # 이진검색 트리의 특징 
//     1. 같은 값을 갖는 노드는 없음
//     2. 중위 순회를 하면 최소값 ~ 최대값의 전체수를 오름차순으로 출력할 수 있음 ( <-> 내림차순은 그 반대 오른쪽 - 부모 - 왼쪽)
//     3. 레벨과 별개로 가장 좌측에 위치하는 수가 최소값, 가장 우측에 위치하는 수가 최대값
//     4. 가급적 중위값이 가장 위에 있어야 트리 구조가 대칭에 가까워짐
//        (= 중위값이 최상단에 있어야 어떤 숫자를 검색하던 이진검색이 효율적 -> red black tree가 나온 이유)

//   # 이진검색 트리의 목적? -> 발전형인 red black tree가 나온 이유
//     : 애초에 이런 트리를 짜는 목적이 효율적인 이진검색을 위한 것..
//       -> how to? 중위값을 기준으로 크고 작음을 비교한다면, 어떤 수를 검색해도 최대 log(2)N+1 번이면 검색이 끝남을 알수 있음
//          -> 중위값을 루트로 둔 대칭구조의 이진트리라면 이를 실현가능한 극도로 효율적인 구조임 발견!
//              -> 입력되는 데이터마다 중위값이 최상단 '루트'로 가게하고, 이진트리적으로 대칭을 이루게 하도록 배치하는 방법을 모색하자 (red black tree가 나온 이유)

//   # red black tree와 이진검색트리 관계
//     : 개념적으로 이진검색트리 > red black tree인 관계 
//       (= 쉽게 설명하면, 매번 중위값이 루트가 되어 대칭을 이루도록 하는 이진트리가 red black tree)


//   # 이진 검색트리 삭제 알고리즘
//     1. 삭제하려는 노드가 리프(말단 노드)일 경우
//        : 말단 노드의 부모 노드를 찾아서 link를 끊음
//     2. 삭제하려는 노드가 하나의 왼쪽이나 오른쪽 자식을 가지고 있는 경우
//        : 노드는 삭제하고, 그 트리가 가지는 자식들인 서브 트리는 삭제된 노드의 부모 노드에 붙여줌 
//          -> 재귀적 방법으로 이를 역참조한 값에 대입해줌
//     3. 삭제하려는 노드가 두 개의 자식을 모두 가지고 있는 경우
//        : 삭제노드와 가장 근사값을 가진 노드값을 삭제할 노드위치의 값으로 대입 (= 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값)
//          -> (중요!) 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값.. 이들은 결과적으로 '리프노드'로 자식이 없음
//              -> 결과적으로 리프노드의 값을 삭제할 노드의 값으로 옮김 
//                 (= 결과적으로 삭제할 녀석은 리프노드를 의미함 -> 사실상 값을 이식 + 리프노드 삭제하는 경우1의 문제가 됨)


// 이진검색 트리(여기서는 처음에 들어온 값을 루트로 하고 이걸 영원히 바꾸지 않는 트리로 가정... red black tree가 아님)의 조회 기능 구현 코드
#include <stdio.h>
#include <stdlib.h>       //	srand(), rand() 함수 사용 가능하게 함
#include <time.h>

typedef int element;

// 트리 구현 구조체
typedef struct treeNode {
    element value;               // 값
    struct treeNode* left;       // (현재 노드기준) 왼쪽 노드의 주소값 
    struct treeNode* right;      // (현재 노드기준) 오른쪽 노드의 주소값 
}treeNode;

// 이진검색트리에 노드 추가 메서드 (= 사실상 이진트리에 노드 추가하는 메서드와 같은 기능)
//  -> 이진검색 트리는 루트가 사실상 중위값이 되어야 하는 구조로 트리가 구성되어 있어야 검색과 삭제가 가능
//     (= 애초부터 트리에 값이 들어갈 때 이진검색트리 구조를 만족시켜야 함)
treeNode* addNode(treeNode* t, element data) {

    // 파라미터로 들어간 트리구조체 포인터변수에 주소값이 없음 (= 주소값이 NULL)
    // -> 이진탐색 실패 위치가 삽입 위치 & 노드가 없을 때
    if (!t) {
        t = (treeNode*)malloc(sizeof(treeNode));
        t->value = data;
        // t->parent = NULL;
        t->left = NULL;
        t->right = NULL;
    }
    else if (data == t->value) {
        printf("\n\n\t\t%d는 이미 등록 된 값 입니다.\n", data);
    }
    else if (data < t->value) {
        t->left = addNode(t->left, data);
    }
    else /* data > t->value */ {
        t->right = addNode(t->right, data);
    }

    return t;
}

// 해당 트리를 전위순회( [기준 노드] 부모 -> 왼쪽 -> 오른쪽 순으로 조회)하여 조회하는 메서드
//  -> 원칙적으로는 부모, 왼쪽, 오른쪽 노드가 NULL일시 그 노드의 값을 찍으라고 코드를 짜야하나.. 
//     -> 굉장히 논리적으로나 성능적으로나 번거롭기 그지없으므로, 부모노드를 보는 대신 자신의 값을 찍는거로 대체
void displayPreOrder(treeNode* t) {
    if (t) {
        // 원칙적으로는 부모노드를 타고 올라가라고 지정해야 하나.. 루트부터 시작시 어차피 자기자신의 값을 찍어도 같음
        //  : 루트 -> 루트 부모 null -> 루트 왼쪽 노드(r_left) -> r_left의 부모노드 = 루트값 출력
        //  : 루트값 출력 -> 루트 왼쪽 노드(r_left) 값 출력 -> 
        printf("%d ", t->value);
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

// 트리구조 해체의 순서는 노드를 모드 깔끔하게 삭제해야 하니, 부모노드를 가장 나중에 보는 걸로 한다
void freeTree(treeNode* t) {
    if (t) {
        freeTree(t->left);
        freeTree(t->right);
        printf("\n노드 삭제 : %d\n", t->value);
        free(t);
    }
}

// 이진검색트리 구조 검색 메서드 (= 기본적으로 이진트리 구조는 재귀적 방법을 사용)
//  -> 해당 트리 검색 로직은 이진검색트리의 구조적 특성이 기반이 됨
//     -> 과정1) 루트를 기반으로 값을 검사
//        과정2) 값이 작으면 왼쪽루트로.. 크면 오른쪽 루트로
//        과정3) 이 짓을 재귀를 통해 반복... 값이 도중에 나오면 트리노드 주소값 리턴.. 아니면 null 
treeNode* searchNode(treeNode* t, element data) {

    // [최종 탐색 실패]
    // 만약 현재 트리가 존재하지 않는다면(= 아무리 뒤져봤지만, 검색할 값이 존재하지 않았음)
    //  -> NULL 리턴
    if (!t) {
        return NULL;
    }

    // [검색 성공]
    //  -> 해당 노드의 주소값 출력
    if (data == t->value) {
        return t;
    }

    // [현재 탐색 실패 = 다음 노드를 봐야함]

    // 현재 노드 data값이 작음 = 이진 트리 구조상 자신의 값보다 작은게 왼쪽에 존재하니 왼쪽으로..
    if (data < t->value) {
        return searchNode(t->left, data);
    }
    // 현재 노드 data값이 큼 = 이진 트리 구조상 자신의 값보다 큰게 오른쪽에 존재하니 오른쪽으로..
    else /* data > t->value */ {
        return searchNode(t->right, data); // 오른쪽 탐색
    }
}

// 이진검색트리 구조 삭제 메서드 (= 기본적으로 트리구조는 재귀적 방법을 사용)
//  -> 해당 트리 삭제 로직은 이진검색트리의 구조적 특성이 기반이 됨
//     -> 과정1) 루트를 기반으로 값을 검사
//        과정2) 값이 작으면 왼쪽루트로.. 크면 오른쪽 루트로
//        과정3) 이 짓을 재귀를 통해 반복... 값이 도중에 나오면.. 또 경우의 수를 따짐 아니면 null 
//        과정4) 삭제할 노드의 자식노드가 몇개냐?
//               -> 0개
//                  1개
//                  2개

//   # 이진 검색트리 삭제 알고리즘
//     1. 삭제하려는 노드가 리프(말단 노드)일 경우
//        : 말단 노드의 부모 노드를 찾아서 link를 끊음
//     2. 삭제하려는 노드가 하나의 왼쪽이나 오른쪽 자식을 가지고 있는 경우
//        : 노드는 삭제하고, 그 트리가 가지는 자식들인 서브 트리는 삭제된 노드의 부모 노드에 붙여줌 
//          -> 재귀적 방법으로 이를 역참조한 값에 대입해줌
//     3. 삭제하려는 노드가 두 개의 자식을 모두 가지고 있는 경우
//        : 삭제노드와 가장 근사값을 가진 노드값을 삭제할 노드위치의 값으로 대입 (= 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값)
//          -> (중요!) 왼쪽에서 가장 큰 값 or 오른쪽에서 가장 작은 값.. 이들은 결과적으로 '리프노드'로 자식이 없음
//              -> 결과적으로 리프노드의 값을 삭제할 노드의 값으로 옮김 
//                 (= 결과적으로 삭제할 녀석은 리프노드를 의미함 -> 사실상 값을 이식 + 리프노드 삭제하는 경우1의 문제가 됨)
treeNode* removeNode(treeNode* t, element data) {
    treeNode* temp = NULL;

    // 해당 tree노드가 위치한 주소값이 있다면?
    if (t) {

        // 삭제할 값 노드가 루트에 존재함을 확인
        //  -> 루트에 없으면, 재귀를 통해 dfs방식으로 탐색해서 진행
        if (data == t->value) {

            //노드가 리프인 경우
            if (t->left == NULL && t->right == NULL) {
                free(t);
                return NULL;
            }
            //노드가 리프가 아니라 자식을 가질수 있는 경우
            else {
                // 해당 노드의 오른쪽에만 자식만 있음
                // -> 해당 right의 주소값을 tmp에 대입하고, 해당 노드의 메모리할당을 해제후 리턴
                if (t->left == NULL) {
                    // (미완)
                    temp = t->right;
                    free(t);
                    return temp;
                }

                // 해당 노드의 왼쪽에만 자식만 있음
                // -> 해당 left의 주소값을 tmp에 대입하고, 해당 노드의 메모리할당을 해제후 리턴
                if (t->right == NULL) {
                    // (미완)
                    temp = t->left;
                    free(t);
                    return temp;
                }

                //오른쪽 & 왼쪽 모두 자식이 있어, 왼쪽 가장 큰 값 호출
                temp = findMax(t->left);

                //왼쪽 가장 큰 값을 저장
                t->value = temp->value;

                //왼쪽 가장 큰 값 삭제 재귀
                t->left = removeNode(t->left, temp->value);
            }
        }
        // 루트에 값이 없으면, 재귀를 통해 dfs방식으로 탐색해서 진행
        else {

            // 해당 노드의 값이 검색값보다 크냐? 작냐에 따라 left, right로 노드이동
            if (data < t->value) {
                t->left = removeNode(t->left, data);
            }
            else/* data > t->value */ {
                t->right = removeNode(t->right, data);
            }
        }
    }

    // 삭제를 하게되면, 삭제한 노드의 주소 리턴.. 아니면 NULL 리턴
    return t;
}




int main() {

    srand((unsigned int)time(NULL));

    // 동적배열의 위치를 받아낼 포인터
    int* array_address = NULL;
    // 동적배열의 길이값
    int array_num = 0;

    treeNode* root = NULL;

    printf("----------------------------------------------------------------------------\n");
    printf("검색기능을 수행해봅니다. 배열 크기에 해당하는 값을 입력하면,\n 배열의 값은 각 배열의 index + a(1~5) 에 대응하는 값으로 입력됩니다.");
    printf("----------------------------------------------------------------------------\n\n");

    printf("검색의 대상이 되는 배열의 크기를 입력하세요 (0이외의 값을 좀 부탁드려용~) : ");
    scanf_s("%d", &array_num);

    if (array_num == 0) {
        printf("배열의 크기가 0이므로 시스템을 종료합니다\n");
        exit(0);
    }

    // 동적할당 시행
    array_address = (int*)calloc(array_num, sizeof(int));

    // 동적할당한 메모리 각각의 값이 정렬된 효과를 낳게, 랜덤한 값이 들어갈수 있게하되, 무조건 자기 이전의 값에 추가값을 더하는 식으로 설계
    for (int i = 0; i < array_num; i++) {

        int plus_a = rand() % 3 + 1;

        if (i == 0) {
            *(array_address + i) = i + plus_a;
        }
        else {
            *(array_address + i) = *(array_address + i - 1) + plus_a;
        }

        addNode(root, *(array_address + i));

        printf("%d ", *(array_address + i));
    }

    printf("\n\n값 입력이 완료되었습니다.\n");
    printf("hint : 가장 작은 값 = %d, 가장 높은 값 = %d)\n\n", *(array_address), *(array_address + array_num - 1));


    int arr[] = { 6, 4, 8, 2, 5, 7, 9, 1, 3 };

    printf("\n전위 순회\n");
    displayPreOrder(root);

    printf("\n중위 순회\n");
    displayInOrder(root);

    printf("\n후위 순회\n");
    displayPostOrder(root);

    freeTree(root);

    return 0;
}
// 자료구조
//  : 데이터를 어떻게 관리할 것인지에 대한 내용

//	1. 데이터 = 주체(정보)
//	  -> 유형 : 정수형, 실수형, 문자형, 구조체
//	  -> 명명법 : 개체로서 명사로서 이름을 명명함

//	2. 연산 = 말 그대로 수학적 연산
//	  -> +, -, /, *, %, =, == , != , <= , >=
//	  -> 명명법 : 개체에 어떤 행위를 하는 의미로서 동사로서 이름을 명명함

//	3. 리스트 
//	  -> 스택(stack) : 후입선출(LIFO)
//	  -> 큐(queue) : 선입선출(FIFO)
//	  -> 배열(list) : 배열로 만들기
//	  -> 탐색(search) : 규칙적으로 분류(정렬)
//	  -> 그래프(graph) : 각각의 상대적 특징으로 구분
//	  -> 트리(tree)	: 자료의 상위, 하위로 구분


// 프로그램 작성 규칙
//  1. 의미 있는 상수를 대문자로 표기
//     ex) #define MAX_ELEMENT 100

//  2. 변수의 명명법 : 소문자를 사용, _(underline)을 사용해 단어간 분리

//  3. 함수 명명법 : 동사를 사용해 함수의 기능(하는 작업) 표기
//     ex) int int_add(int a, int b);

//  4. 가독성과 효율을 위한 구조체 활용(typedef 사용)
//     ex) typedef int element;

//         typedef struct ListNode {

//           element data;
//			 struct ListNode* link;
//	       } ListNode;


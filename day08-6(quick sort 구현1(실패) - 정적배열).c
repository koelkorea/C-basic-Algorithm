// 정적할당을 사용한 퀵정렬 구현
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() 함수 사용 가능하게 함
#include <time.h>
#define ARRAY_LENGTH 10
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define 매크로 영역 (형태처리 전처리 기문)			ex) A <-> : A와 B를 해당하는 타입을 빈공간으로 사용하여 교환


// [최종적 실패..] 해당 동적배열의 요소값을 순차적 출력 (for문으로 length만큼 반복) 
//  -> 패인1 : 나는 left = right가 되면, 바로 배열을 분할하려고 했음..
//     -> 그렇지만 left right커서가 정확히 같은 곳에 멈추는 곳은 '기준값'에 위치한 공간을 통과할떄 뿐이기에.. 
//        그 이외의 누가 선을 넘던 거기를 기준으로 의도대로 분할하게 되는 경우를 제대로 상정하지 못함..
//        -> 그럼에도 left = right시 배열을 분할하려고 했기에, 결국 복잡한 조건으로 이를 분해하려는 메서드가 늘어나게 되었음... 그렇지만 실패
//  -> 패인2 : 배열을 분할 후, 전 후배열 sort를 한 과정을 묶어버림 = 전배열x 후배열 sort, 전배열sort 후배열x 이런부분에서 오작동함
//     -> 정확히는 왼쪽1개 남기고 나머지 sort, 오른쪽 1개 남기고 나머지 sort의 상황... 
//        -> 하지만 각각 후배열, 전배열만 sort를 해야하는 상황에 하나를 sort안하면 나머지도 sort를 무조건 안한다는 점에서 이는 치명적
void display(int arr[], int start, int size) {

    for (int i = start; i < size; i++) {

        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

//  5. 퀵 정렬(Quick sort)
//     : 리스트 안에 존재하는 임의의 값을 기준값으로 정해두고, 
//       -> 왼쪽에서부터 데이터를 기준값과 정렬방법에 따라 크고 작은지 비교 정렬방법에 따라 조건이 안 맞으면 다음 값으로, 맞으면 오른쪽부터 데이터를 기준값과 비교해서 정반대의 경우가 존재하는지 확인
//          -> 오른쪽에도 존재가 맞는 값이 보이면? ->  왼쪽과 오른쪽의 값을 교환하고, 그 다음 왼쪽위치의 다음 값부터 똑같이 계속 진행
//       -> 왼쪽이던 오른쪽이던 포인터가 겹치게 된다면? 그 부분을 중심으로 리스트를 토막내서 다시 같은 방식으로 비교 반복
//       -> 모든 부분리스트가 더 이상 분할이 불가능한 최소 단위(1개)로 분할 될 때까지 이를 반복
void quick_sort(int arr[], int direction, int leftest, int rightest) {

    if (rightest <= 0) {

        printf("배열의 길이가 0보다 작거나 같으므로 진행X\n\n");
        return;
    }

    if (leftest >= rightest) {
        printf("배열의 시작점이 배열의 길이 %d보다 크거나 같으므로 진행X\n\n", rightest);
        return;
    }

    int left_point = leftest;
    int right_point = rightest;
    int pivot = arr[leftest];

    printf("\n---------------------[기준값 : %d, 시작부분 : %d, 끝부분 : %d]------------------------------------\n\n", pivot, leftest, rightest);

    display(arr, leftest, rightest + 1);

    // 오름차순 (큰 수를 뒤로.. )
    if (direction == ascending_order) {

        // left_point가 right_point보다 같게 될 때까지 반복 (상황이 아니라 쳐도 일단 실행해봄)
        do {


            // [문제점 1] : 아무리 디버깅 용이라지만, 조건이 복잡해서 나중에는 나도 헷갈림 (조건문은 없애자)
            if (left_point == right_point) {
                printf("\n@@@@@@@@@@@@@@@left와 right가 같은 지점 배열[%d]에 모임!@@@@@@@@@@@@@@@@@@@@\n", left_point);

                //printf("-> 기준값 %d을 가지고 있던 arr[%d]의 위치를 분기점 배열[%d]의 값과 스왑\n\n", pivot, leftest, flag);
                //printf(" ->> arr[%d] : %d <-> arr[%d] : %d!\n\n", leftest, arr[leftest], flag, arr[flag]);
                //swap(int, arr[flag], arr[leftest]);

                for (int i = leftest; i <= rightest; i++) {

                    printf("%d ", arr[i]);
                }
                printf("\n\n");

                break;
            }
            else if (left_point < right_point) {

                printf("(교환값 검색전)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

                // (중요! 중요!) <- 내가 실패한 핵심이유

                // [문제점 2] : left 커서를 옮기는 조건이 너무 복잡하다..
                //  -> 1. 내가 의도한건, left커서가 right커서를 넘어서는 안된다는거였는데.. 
                //        -> 그럴 필요가 없는게, 애초에 목표값(= 최소값 ~ 최대값)이기에.. 
                //           조건이 arr[left커서] = 최대값이라도, 그 최대값을 만나면 거기서 멈춰야 했음
                //           (= left 커서는 rightest를 넘지 못하기에, left_point < rightest 조건 필요없음)
                //  -> 2. left_point가 +1이되어 right_point가 될 걸 상정했는데.. 사실 조건 자체가 잘못됨
                //        left_point <= right_point 면, left 커서 = right커서 같을때 어디를 분할해야 할지에 대한 문제를 말끔히 해소
                //        -> 교차를 허용하면, 애초에 기준값을 바탕으로 큰값 <-> 작은값 스왑을 하는데..
                //            -> (중요!) 이 경우 left right커서가 정확히 같은 곳에 멈추는 곳은 '기준값'에 위치한 공간을 통과할떄 뿐임!
                //            -> 그 이외의 경우는 누가 선을 넘던 거기를 기준으로 의도대로 분할하게 되기에, 두 커서의 교차허용은 필연임
                while (arr[left_point] < pivot && left_point < rightest && left_point < right_point) {
                //----------------------------------------------------------------------
                // while (arr[left_point] < pivot) {
                //----------------------------------------------------------------------

                    left_point++;
                }

                if (left_point <= right_point) {
                    printf(" ->> (교환 left발견) arr[%d] : %d (arr[%d](기준값) : %d 보다 큰 값)   ----->> right값을 움직이겠음\n", left_point, arr[left_point], leftest, pivot);
                }

                // (중요! 중요!) <- 내가 실패한 핵심이유

                // [문제점 3] : right 커서를 옮기는 조건이 너무 복잡하다..
                //  -> 1. 내가 의도한건, left커서가 right커서를 넘어서는 안된다는거였는데.. 
                //        -> 그럴 필요가 없는게, 애초에 목표값(= 최소값 ~ 최대값)이기에.. 
                //           조건이 arr[left커서] = 최대값이라도, 그 최대값을 만나면 거기서 멈춰야 했음
                //           (= right 커서는 leftest를 넘지 못하기에, left_point < rightest 조건 필요없음)
                //  -> 2. right_point가 -1이되어 left_point가 될 걸 상정했는데.. 사실 조건 자체가 잘못됨
                //        left_point <= right_point 면, left 커서 = right커서 같을때 어디를 분할해야 할지에 대한 문제를 말끔히 해소
                //        -> 교차를 허용하면, 애초에 기준값을 바탕으로 큰값 <-> 작은값 스왑을 하는데..
                //            -> (중요!) 이 경우 left right커서가 정확히 같은 곳에 멈추는 곳은 '기준값'에 위치한 공간을 통과할떄 뿐임!
                //            -> 그 이외의 경우는 누가 선을 넘던 거기를 기준으로 의도대로 분할하게 되기에, 두 커서의 교차허용은 필연임

                while (arr[right_point] > pivot && right_point > leftest && left_point < right_point) {
                //----------------------------------------------------------------------
                // while (arr[right_point] > pivot) {
                //----------------------------------------------------------------------

                    right_point--;
                }

                if (left_point == right_point) {
                    printf(" ->> (right 커서 move 중단!) left = right : 현재 위치가 %d로 기준값인 %d를 검토합니다\n\n", left_point, arr[left_point]);
                }
                else if (left_point < right_point) {
                    printf(" ->> (교환 right발견) arr[%d] : %d (arr[%d](기준값) : %d 보다 작은 값)\n", right_point, arr[right_point], leftest, pivot);
                }

                printf("(교환값 검색후!)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

                if (left_point <= right_point) {
                    printf("  ->> (left - right 교환!) arr[%d] : %d <-> arr[%d] : %d \n\n", left_point, arr[left_point], right_point, arr[right_point]);
                    swap(int, arr[left_point], arr[right_point]);

                    // [문제점 4] : 값을 교환한 후 left_point, right_point를 움직이지 않았음
                    //  -> 로직상 어차피 기준값이 존재해서, 바꾼수로 인해서 문제가 되진 않음.
                    //     어차피 while문을 통해 교차될때까지 left right 커서는 상단에서 잘 움직이기 때문에 필수는 아님
                    //----------------------------------------------------------------------
                    // left_point++;
                    // right_point--;
                    //----------------------------------------------------------------------
                }
            }

            display(arr, leftest, rightest + 1);

        // [문제점 5] : [문제점 2,3]의 것과 동일..
        //  -> left_point가 +1이되어 right_point가 될 걸 상정했는데.. 사실 조건 자체가 잘못됨
        //     left_point <= right_point 면, left 커서 = right커서 같을때 어디를 분할해야 할지에 대한 문제를 말끔히 해소
        //        -> 교차를 허용하면, 애초에 기준값을 바탕으로 큰값 <-> 작은값 스왑을 하는데..
        //            -> (중요!) 이 경우 left right커서가 정확히 같은 곳에 멈추는 곳은 '기준값'에 위치한 공간을 통과할떄 뿐임!
        //            -> 그 이외의 경우는 누가 선을 넘던 거기를 기준으로 의도대로 분할하게 되기에, 두 커서의 교차허용은 필연임
        } while (left_point < right_point);

        //----------------------------------------------------------------------
        // } while (left_point <= right_point);
        //----------------------------------------------------------------------

        printf("=====================================[싸이클 end]==================================================\n\n");

        printf("leftest : %d , rightest : %d , left_point : %d , right_point : %d \n\n", leftest, rightest, left_point, right_point);

        // (중요! 중요!) <- 내가 실패한 핵심이유

        // [문제점 6] : 조건 자체는 잘 세웠지만, 이걸 and조건으로 세울시.. 
        //  -> 왼쪽에 1개, 오른쪽에 1개만 남는 상황에서, 나머지 배열을 다시 quicksort 재귀를 돌릴수가 없음
        //     -> 조건문이 2개로 분할되어 있으면, 다음의 조건이 각각 실행 <-> 이를 and조건으로 묶고 같이 실행시에는 나머지를 quicksort 돌리는게 불가능함
        //        right 커서가 왼쪽 1개에 위치한 경우 ->> 왼쪽의 1개를 놔두는거랑, 나머지를 quicksort 돌리는게 각각 실행
        //        left 커서가 오른쪽 1개에 위치한 경우 ->> 오른쪽의 1개를 놔두는거랑, 나머지를 quicksort 돌리는게 각각 실행
        if (right_point > leftest && left_point < rightest) {

            // 좌분할
            printf("<전 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", leftest, right_point);
            quick_sort(arr, direction, leftest, right_point);

            // 우분할
            printf("<후 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", left_point, rightest);
            quick_sort(arr, direction, left_point, rightest);
        }

        //----------------------------------------------------------------------
        //if (leftest < right_point) {
        //    printf("<전 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", leftest, right_point);
        //    quick_sort(arr, direction, leftest, right_point);
        //}

        //if (rightest > left_point) {
        //    printf("<후 배열> : left좌표 = %d, right좌표 = %d인 부분 배열의 quick 시작!\n\n", left_point, rightest);
        //    quick_sort(arr, direction, left_point, rightest);
        //}
        //----------------------------------------------------------------------
    }
    // 내림차순 (작은 수를 뒤로.. )
    else {

        // 배열 크기만큼 부분정렬 그룹별 싸이클 돌 수 있게 함
        for (int i = 0; i < rightest; i++) {

            if (i == rightest - 1 - i) {
                quick_sort(arr, direction, 0, i - 1);
                quick_sort(arr, direction, i + 1, rightest);
                break;
            }
            else if (i > rightest - 1 - i) {
                quick_sort(arr, direction, 0, rightest - 1 - i);
                quick_sort(arr, direction, i, rightest);
                break;
            }
            else if (i < rightest - 1 - i) {

                if (arr[i] < arr[rightest - 1 - i]) {
                    swap(int, arr[i], arr[rightest - 1 - i]);
                }
            }
        }
    }

}

int main() {

    srand((unsigned int)time(NULL));

    printf("----------------------------------------------------------------------------\n");
    printf("배열의 길이는 100이며, quick sort를 수행해봅니다.\n각 배열값은 각 배열의 이전 배열값 + a(1~5) 에 대응하는 값으로 입력됩니다.\n");
    printf("----------------------------------------------------------------------------\n\n");

    int ary_test[ARRAY_LENGTH] = { 0 };
    int input = 0;
    int direction = ascending_order;
    int array_length = ARRAY_LENGTH - 1;

    // 랜덤한 값이 들어갈수 있게 설계 (0 ~ 500)
    for (int i = 0; i < ARRAY_LENGTH; i++) {

        ary_test[i] = rand() % 501;

        printf("%d ", ary_test[i]);
    }

    printf("\n\n값 입력이 완료되었습니다. \n");

    printf("원하시는 방식의 정렬방식이 오름차순인가요? (0 : 오름차순, 그 이외 값 입력: 내림차순) : ");
    scanf_s("%d", &direction);

    // 머지 소트 실행
    quick_sort(ary_test, direction, 0, array_length);

    printf("\n[quick sort 결과] \n");

    display(ary_test, 0, ARRAY_LENGTH);

    printf("\n");

    return 0;
}
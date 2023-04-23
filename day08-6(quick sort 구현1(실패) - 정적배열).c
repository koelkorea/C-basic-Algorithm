// �����Ҵ��� ����� ������ ����
#include <stdio.h>
#include <stdlib.h>				//	srand(), rand() �Լ� ��� �����ϰ� ��
#include <time.h>
#define ARRAY_LENGTH 10
#define ascending_order  0
#define swap(type, a, b) { type temp = a; a = b; b = temp; };		// #define ��ũ�� ���� (����ó�� ��ó�� �⹮)			ex) A <-> : A�� B�� �ش��ϴ� Ÿ���� ��������� ����Ͽ� ��ȯ


// [������ ����..] �ش� �����迭�� ��Ұ��� ������ ��� (for������ length��ŭ �ݺ�) 
//  -> ����1 : ���� left = right�� �Ǹ�, �ٷ� �迭�� �����Ϸ��� ����..
//     -> �׷����� left rightĿ���� ��Ȯ�� ���� ���� ���ߴ� ���� '���ذ�'�� ��ġ�� ������ ����ҋ� ���̱⿡.. 
//        �� �̿��� ���� ���� �Ѵ� �ű⸦ �������� �ǵ���� �����ϰ� �Ǵ� ��츦 ����� �������� ����..
//        -> �׷����� left = right�� �迭�� �����Ϸ��� �߱⿡, �ᱹ ������ �������� �̸� �����Ϸ��� �޼��尡 �þ�� �Ǿ���... �׷����� ����
//  -> ����2 : �迭�� ���� ��, �� �Ĺ迭 sort�� �� ������ ������� = ���迭x �Ĺ迭 sort, ���迭sort �Ĺ迭x �̷��κп��� ���۵���
//     -> ��Ȯ���� ����1�� ����� ������ sort, ������ 1�� ����� ������ sort�� ��Ȳ... 
//        -> ������ ���� �Ĺ迭, ���迭�� sort�� �ؾ��ϴ� ��Ȳ�� �ϳ��� sort���ϸ� �������� sort�� ������ ���Ѵٴ� ������ �̴� ġ����
void display(int arr[], int start, int size) {

    for (int i = start; i < size; i++) {

        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

//  5. �� ����(Quick sort)
//     : ����Ʈ �ȿ� �����ϴ� ������ ���� ���ذ����� ���صΰ�, 
//       -> ���ʿ������� �����͸� ���ذ��� ���Ĺ���� ���� ũ�� ������ �� ���Ĺ���� ���� ������ �� ������ ���� ������, ������ �����ʺ��� �����͸� ���ذ��� ���ؼ� ���ݴ��� ��찡 �����ϴ��� Ȯ��
//          -> �����ʿ��� ���簡 �´� ���� ���̸�? ->  ���ʰ� �������� ���� ��ȯ�ϰ�, �� ���� ������ġ�� ���� ������ �Ȱ��� ��� ����
//       -> �����̴� �������̴� �����Ͱ� ��ġ�� �ȴٸ�? �� �κ��� �߽����� ����Ʈ�� �丷���� �ٽ� ���� ������� �� �ݺ�
//       -> ��� �κи���Ʈ�� �� �̻� ������ �Ұ����� �ּ� ����(1��)�� ���� �� ������ �̸� �ݺ�
void quick_sort(int arr[], int direction, int leftest, int rightest) {

    if (rightest <= 0) {

        printf("�迭�� ���̰� 0���� �۰ų� �����Ƿ� ����X\n\n");
        return;
    }

    if (leftest >= rightest) {
        printf("�迭�� �������� �迭�� ���� %d���� ũ�ų� �����Ƿ� ����X\n\n", rightest);
        return;
    }

    int left_point = leftest;
    int right_point = rightest;
    int pivot = arr[leftest];

    printf("\n---------------------[���ذ� : %d, ���ۺκ� : %d, ���κ� : %d]------------------------------------\n\n", pivot, leftest, rightest);

    display(arr, leftest, rightest + 1);

    // �������� (ū ���� �ڷ�.. )
    if (direction == ascending_order) {

        // left_point�� right_point���� ���� �� ������ �ݺ� (��Ȳ�� �ƴ϶� �ĵ� �ϴ� �����غ�)
        do {


            // [������ 1] : �ƹ��� ����� ���̶�����, ������ �����ؼ� ���߿��� ���� �򰥸� (���ǹ��� ������)
            if (left_point == right_point) {
                printf("\n@@@@@@@@@@@@@@@left�� right�� ���� ���� �迭[%d]�� ����!@@@@@@@@@@@@@@@@@@@@\n", left_point);

                //printf("-> ���ذ� %d�� ������ �ִ� arr[%d]�� ��ġ�� �б��� �迭[%d]�� ���� ����\n\n", pivot, leftest, flag);
                //printf(" ->> arr[%d] : %d <-> arr[%d] : %d!\n\n", leftest, arr[leftest], flag, arr[flag]);
                //swap(int, arr[flag], arr[leftest]);

                for (int i = leftest; i <= rightest; i++) {

                    printf("%d ", arr[i]);
                }
                printf("\n\n");

                break;
            }
            else if (left_point < right_point) {

                printf("(��ȯ�� �˻���)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

                // (�߿�! �߿�!) <- ���� ������ �ٽ�����

                // [������ 2] : left Ŀ���� �ű�� ������ �ʹ� �����ϴ�..
                //  -> 1. ���� �ǵ��Ѱ�, leftĿ���� rightĿ���� �Ѿ�� �ȵȴٴ°ſ��µ�.. 
                //        -> �׷� �ʿ䰡 ���°�, ���ʿ� ��ǥ��(= �ּҰ� ~ �ִ밪)�̱⿡.. 
                //           ������ arr[leftĿ��] = �ִ밪�̶�, �� �ִ밪�� ������ �ű⼭ ����� ����
                //           (= left Ŀ���� rightest�� ���� ���ϱ⿡, left_point < rightest ���� �ʿ����)
                //  -> 2. left_point�� +1�̵Ǿ� right_point�� �� �� �����ߴµ�.. ��� ���� ��ü�� �߸���
                //        left_point <= right_point ��, left Ŀ�� = rightĿ�� ������ ��� �����ؾ� ������ ���� ������ ������ �ؼ�
                //        -> ������ ����ϸ�, ���ʿ� ���ذ��� �������� ū�� <-> ������ ������ �ϴµ�..
                //            -> (�߿�!) �� ��� left rightĿ���� ��Ȯ�� ���� ���� ���ߴ� ���� '���ذ�'�� ��ġ�� ������ ����ҋ� ����!
                //            -> �� �̿��� ���� ���� ���� �Ѵ� �ű⸦ �������� �ǵ���� �����ϰ� �Ǳ⿡, �� Ŀ���� ��������� �ʿ���
                while (arr[left_point] < pivot && left_point < rightest && left_point < right_point) {
                //----------------------------------------------------------------------
                // while (arr[left_point] < pivot) {
                //----------------------------------------------------------------------

                    left_point++;
                }

                if (left_point <= right_point) {
                    printf(" ->> (��ȯ left�߰�) arr[%d] : %d (arr[%d](���ذ�) : %d ���� ū ��)   ----->> right���� �����̰���\n", left_point, arr[left_point], leftest, pivot);
                }

                // (�߿�! �߿�!) <- ���� ������ �ٽ�����

                // [������ 3] : right Ŀ���� �ű�� ������ �ʹ� �����ϴ�..
                //  -> 1. ���� �ǵ��Ѱ�, leftĿ���� rightĿ���� �Ѿ�� �ȵȴٴ°ſ��µ�.. 
                //        -> �׷� �ʿ䰡 ���°�, ���ʿ� ��ǥ��(= �ּҰ� ~ �ִ밪)�̱⿡.. 
                //           ������ arr[leftĿ��] = �ִ밪�̶�, �� �ִ밪�� ������ �ű⼭ ����� ����
                //           (= right Ŀ���� leftest�� ���� ���ϱ⿡, left_point < rightest ���� �ʿ����)
                //  -> 2. right_point�� -1�̵Ǿ� left_point�� �� �� �����ߴµ�.. ��� ���� ��ü�� �߸���
                //        left_point <= right_point ��, left Ŀ�� = rightĿ�� ������ ��� �����ؾ� ������ ���� ������ ������ �ؼ�
                //        -> ������ ����ϸ�, ���ʿ� ���ذ��� �������� ū�� <-> ������ ������ �ϴµ�..
                //            -> (�߿�!) �� ��� left rightĿ���� ��Ȯ�� ���� ���� ���ߴ� ���� '���ذ�'�� ��ġ�� ������ ����ҋ� ����!
                //            -> �� �̿��� ���� ���� ���� �Ѵ� �ű⸦ �������� �ǵ���� �����ϰ� �Ǳ⿡, �� Ŀ���� ��������� �ʿ���

                while (arr[right_point] > pivot && right_point > leftest && left_point < right_point) {
                //----------------------------------------------------------------------
                // while (arr[right_point] > pivot) {
                //----------------------------------------------------------------------

                    right_point--;
                }

                if (left_point == right_point) {
                    printf(" ->> (right Ŀ�� move �ߴ�!) left = right : ���� ��ġ�� %d�� ���ذ��� %d�� �����մϴ�\n\n", left_point, arr[left_point]);
                }
                else if (left_point < right_point) {
                    printf(" ->> (��ȯ right�߰�) arr[%d] : %d (arr[%d](���ذ�) : %d ���� ���� ��)\n", right_point, arr[right_point], leftest, pivot);
                }

                printf("(��ȯ�� �˻���!)  left : arr[%d] = %d , right : arr[%d] = %d \n", left_point, arr[left_point], right_point, arr[right_point]);

                if (left_point <= right_point) {
                    printf("  ->> (left - right ��ȯ!) arr[%d] : %d <-> arr[%d] : %d \n\n", left_point, arr[left_point], right_point, arr[right_point]);
                    swap(int, arr[left_point], arr[right_point]);

                    // [������ 4] : ���� ��ȯ�� �� left_point, right_point�� �������� �ʾ���
                    //  -> ������ ������ ���ذ��� �����ؼ�, �ٲۼ��� ���ؼ� ������ ���� ����.
                    //     ������ while���� ���� �����ɶ����� left right Ŀ���� ��ܿ��� �� �����̱� ������ �ʼ��� �ƴ�
                    //----------------------------------------------------------------------
                    // left_point++;
                    // right_point--;
                    //----------------------------------------------------------------------
                }
            }

            display(arr, leftest, rightest + 1);

        // [������ 5] : [������ 2,3]�� �Ͱ� ����..
        //  -> left_point�� +1�̵Ǿ� right_point�� �� �� �����ߴµ�.. ��� ���� ��ü�� �߸���
        //     left_point <= right_point ��, left Ŀ�� = rightĿ�� ������ ��� �����ؾ� ������ ���� ������ ������ �ؼ�
        //        -> ������ ����ϸ�, ���ʿ� ���ذ��� �������� ū�� <-> ������ ������ �ϴµ�..
        //            -> (�߿�!) �� ��� left rightĿ���� ��Ȯ�� ���� ���� ���ߴ� ���� '���ذ�'�� ��ġ�� ������ ����ҋ� ����!
        //            -> �� �̿��� ���� ���� ���� �Ѵ� �ű⸦ �������� �ǵ���� �����ϰ� �Ǳ⿡, �� Ŀ���� ��������� �ʿ���
        } while (left_point < right_point);

        //----------------------------------------------------------------------
        // } while (left_point <= right_point);
        //----------------------------------------------------------------------

        printf("=====================================[����Ŭ end]==================================================\n\n");

        printf("leftest : %d , rightest : %d , left_point : %d , right_point : %d \n\n", leftest, rightest, left_point, right_point);

        // (�߿�! �߿�!) <- ���� ������ �ٽ�����

        // [������ 6] : ���� ��ü�� �� ��������, �̰� and�������� �����.. 
        //  -> ���ʿ� 1��, �����ʿ� 1���� ���� ��Ȳ����, ������ �迭�� �ٽ� quicksort ��͸� �������� ����
        //     -> ���ǹ��� 2���� ���ҵǾ� ������, ������ ������ ���� ���� <-> �̸� and�������� ���� ���� ����ÿ��� �������� quicksort �����°� �Ұ�����
        //        right Ŀ���� ���� 1���� ��ġ�� ��� ->> ������ 1���� ���δ°Ŷ�, �������� quicksort �����°� ���� ����
        //        left Ŀ���� ������ 1���� ��ġ�� ��� ->> �������� 1���� ���δ°Ŷ�, �������� quicksort �����°� ���� ����
        if (right_point > leftest && left_point < rightest) {

            // �º���
            printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", leftest, right_point);
            quick_sort(arr, direction, leftest, right_point);

            // �����
            printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", left_point, rightest);
            quick_sort(arr, direction, left_point, rightest);
        }

        //----------------------------------------------------------------------
        //if (leftest < right_point) {
        //    printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", leftest, right_point);
        //    quick_sort(arr, direction, leftest, right_point);
        //}

        //if (rightest > left_point) {
        //    printf("<�� �迭> : left��ǥ = %d, right��ǥ = %d�� �κ� �迭�� quick ����!\n\n", left_point, rightest);
        //    quick_sort(arr, direction, left_point, rightest);
        //}
        //----------------------------------------------------------------------
    }
    // �������� (���� ���� �ڷ�.. )
    else {

        // �迭 ũ�⸸ŭ �κ����� �׷캰 ����Ŭ �� �� �ְ� ��
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
    printf("�迭�� ���̴� 100�̸�, quick sort�� �����غ��ϴ�.\n�� �迭���� �� �迭�� ���� �迭�� + a(1~5) �� �����ϴ� ������ �Էµ˴ϴ�.\n");
    printf("----------------------------------------------------------------------------\n\n");

    int ary_test[ARRAY_LENGTH] = { 0 };
    int input = 0;
    int direction = ascending_order;
    int array_length = ARRAY_LENGTH - 1;

    // ������ ���� ���� �ְ� ���� (0 ~ 500)
    for (int i = 0; i < ARRAY_LENGTH; i++) {

        ary_test[i] = rand() % 501;

        printf("%d ", ary_test[i]);
    }

    printf("\n\n�� �Է��� �Ϸ�Ǿ����ϴ�. \n");

    printf("���Ͻô� ����� ���Ĺ���� ���������ΰ���? (0 : ��������, �� �̿� �� �Է�: ��������) : ");
    scanf_s("%d", &direction);

    // ���� ��Ʈ ����
    quick_sort(ary_test, direction, 0, array_length);

    printf("\n[quick sort ���] \n");

    display(ary_test, 0, ARRAY_LENGTH);

    printf("\n");

    return 0;
}
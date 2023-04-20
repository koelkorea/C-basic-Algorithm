#include <stdio.h>
int interpolationSearch(int arr[], int n, int key) {

    int pos = 0, low = 0, high = (n - 1);

    while (arr[low] != arr[high] && key >= arr[low] && key <= arr[high]) {
        pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (key - arr[low]));
        if (arr[pos] == key) return pos;
        else if (arr[pos] > key) high = pos - 1;
        else low = pos + 1;

    }
    if (key == arr[low]) return low;
    else return -1;

}
int main() {

    int ary_test[] = { 1,2,4,6,7,8,9,10,15,19,21,23,24,27,28,29,30,31,35,38,39,40 }, in;

    while (1) {

        printf("찾고 싶은 숫자 1~40(범위밖 종료):");
        scanf_s("%d", &in);

        if (in <= 0 || in > 40) break;

        if (interpolationSearch(ary_test, 22, in) != -1) {
            printf("%d는 %d번째\n", in, interpolationSearch(ary_test, 22, in) + 1);
        }
        else printf("%d는 탐색 실패\n", in);
    }
    return 0;
}

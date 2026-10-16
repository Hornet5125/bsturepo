#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
void find_maxes(int arr[], int n, int result[]) {
    if (n < 4) {
        for (int i = 0; i < n; i++) {
            result[i] = arr[i];
        }
        sort(result, result + n);
        return;
    }
    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int max3 = INT_MIN;
    int max4 = INT_MIN;
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        if (num > max1) {
            max4 = max3;
            max3 = max2;
            max2 = max1;
            max1 = num;
        }
        else if (num > max2) {
            max4 = max3;
            max3 = max2;
            max2 = num;
        }
        else if (num > max3) {
            max4 = max3;
            max3 = num;
        }
        else if (num > max4) {
            max4 = num;
        }
    }
    result[0] = max1;
    result[1] = max2;
    result[2] = max3;
    result[3] = max4;
    sort(result, result + 4);
}
int main() {
    const int n=9;
    int arr[n] = {5, 2, 8, 1, 9, 3, 7, 6, 4};
    int result[4];
    find_maxes(arr, n, result);
    for (int i = 0; i < 4; i++) {
        cout << result[i] << " ";
    }
    return 0;
}
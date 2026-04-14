#include <iostream>
using namespace std;
int maxInt(const int A[], int N) {
    if (N == 1) {
        return A[0];
    }
    int prevmax = maxInt(A, N - 1);
    if (A[N - 1] > prevmax) {
        return A[N - 1];
    } else {
        return prevmax;
    }
}
void printmax(const int arr[], int size) {
    cout << maxInt(arr, size) << endl;
}
int main() {
    const int max = 10;
    int A[max], B[max], C[max];
    int NA, NB, NC;
    cin >> NA;
    for (int i = 0; i < NA; i++) {
        cin >> A[i];
    }
    cin >> NB;
    for (int i = 0; i < NB; i++) {
        cin >> B[i];
    }
    cin >> NC;
    for (int i = 0; i < NC; i++) {
        cin >> C[i];
    }
    cout << endl;
    printmax(A, NA);
    printmax(B, NB);
    printmax(C, NC);
    return 0;
}
#include <iostream> 
using namespace std;
void SwapCol(float** A,int M,int N,int K1,int K2){
    if (K1 < 1 || K1 > N || K2 < 1 || K2 > N) {
        return;
    }
    if (K1 == K2) {
        return;
    }
    for (int i = 0; i < M; i++) {
        float temp = A[i][K1-1];
        A[i][K1-1] = A[i][K2-1];
        A[i][K2-1] = temp;
    }
}
int main(){
    int M,N,K1,K2;
    cin >> M >> N >> K1 >> K2;
    float** A = new float* [M];
    for (int i = 0; i < M; i++){
        A[i] = new float[N];
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (rand() % 10000) / 100.0;
        }
    }
    for (int i = 0; i<M;i++){
        for (int j = 0; j<N;j++){
            cout << A[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
    SwapCol(A,M,N,K1,K2);
    for (int i = 0; i<M;i++){
        for (int j = 0; j<N;j++){
            cout << A[i][j] << ' ';
        }
        cout << endl;
    }
    for (int i = 0; i < M; i++) {
        delete[] A[i];
    }
    delete[] A;
}
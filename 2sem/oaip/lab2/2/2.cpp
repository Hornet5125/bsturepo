#include <iostream> 
#include <cstring>
using namespace std;
char* InvertStr(const char* S,int K,int N){
    int len = strlen(S);
    if (K > len) {
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }
    int n;
    if (K + N > len) {
        n = len - K + 1;
    } else {
        n = N;
    }
    char* invertprtstr = new char[n+1];
    for (int i = 0; i < n; i++) {
        invertprtstr[i] = S[K - 2 + n - i];
    }
    invertprtstr[n] = '\0';
    return invertprtstr;
}
int main(){
    char* S = new char[256];
    cin.getline(S,256);
    int K1, N1, K2, N2, K3, N3;
    cin >> K1 >> N1;
    cin >> K2 >> N2;
    cin >> K3 >> N3;
    cout << endl;
    char* result1 = InvertStr(S, K1, N1);
    cout << result1 << endl;
    delete[] result1;
    char* result2 = InvertStr(S, K2, N2);
    cout << result2 << endl;
    delete[] result2;
    char* result3 = InvertStr(S, K3, N3);
    cout << result3 << endl;
    delete[] result3;
    delete[] S;
    return 0;
}
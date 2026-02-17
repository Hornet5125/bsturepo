#include <iostream> // A. Выражение
int main(){
    long long a,b,c;
    long long x=0,x2=0,x3=0;
    long long num1=0,result;
    std::cin >> a >> b >> c;
    if (a == 1 || b == 1 || c == 1){
        if (a == 1){
            num1++;
            x = 1;
        }
        if (b == 1){
            num1++;
            x2 = 1;
        }
        if (c == 1){
            num1++;
            x3 = 1;
        }
        if (num1 == 3){
            result = a+b+c;
        }
        if (num1 == 2){
            result = a+b+c;
        }
        if (x == 1 && num1 == 1){
            result = (a+b)*c;
        }
        if (x2 == 1 && num1 == 1){
            if ((a+b)*c > a*(b+c)){
                result = (a+b)*c;
            }
            else result = a*(b+c);
        }
        if (x3 == 1 && num1 == 1){
            result = a*(b+c);
        }
    }
    if (a != 1 && b != 1 && c != 1) {
        if ((a+b)*c > a*(b+c)){
            result = (a+b)*c;
            if (a*(b+c) > (a+b)*c){
            result = a*(b+c);
            }
        } 
        else result = a*b*c;   
    }
    std::cout << result << std::endl;
    return 0;
}

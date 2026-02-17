#include <iostream> // Задача за 1000 "Театральная площадь"
int main(){
    int n,m,a; 
    int mult,platform_S;
    int num1,num2;
    double num;
    std::cin >> n >> m >> a;
    for (num1 = 0 ; n > 0; num1++){
        n -= a;
    }
    for (num2 = 0 ; m > 0; num2++){
        m -= a;
    }
    num = num1*num2;
    std::cout << num << std::endl;
    return 0;
}

#include <iostream> // Задача за 1000 "Театральная площадь"
int main(){
    int n,m,a; 
    int mult,platform_S;
    int num;
    std::cin >> n >> m >> a;
    platform_S = n*m;
    mult = n*m;
    for (num = 0 ; mult > 0; num++){
        mult -= platform_S;
    }
    std::cout << num << std::endl;
    return 0;
}

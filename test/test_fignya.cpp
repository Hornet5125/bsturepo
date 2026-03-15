#include <iostream> 
struct Point {
        int x;
        int y;
    } p1;
int main(){
    p1.x = 10;
    p1.y = 20; 
    std::cout << p1.x << std::endl;
    return 0; 
}
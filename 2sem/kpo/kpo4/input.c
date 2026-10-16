#include <stdio.h>
int main(){
    int n = 0; 
    if (n==0)
        printf("%d",n);
    else 
        n=5;
    while (n<10)
        n++;
    for(n=0;n<5;n++)
        if(n==3)
            break;
    return 0;
}
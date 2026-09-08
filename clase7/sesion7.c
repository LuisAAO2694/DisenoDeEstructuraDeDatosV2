#include <stdio.h>


void increment() {
    int x = 0;
    x++;
    printf("%d\n", x);
}


void incrementStatic() {
    static int x = 0;
    x++;
    printf("%d\n", x);
}
int main() 
{
    increment();
    increment();
    increment();

    incrementStatic();
    incrementStatic();
    incrementStatic();
    


    return 0;
}
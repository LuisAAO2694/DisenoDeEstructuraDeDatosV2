#include <stdio.h>

int main() {

    int a = 3;
    int b = 4;

    int* arr[4] = { &a, &b };

    int c = 5;
    arr[2] = &c;

    *arr[0] = 1;
    printf("%d\n", a);
    **arr = 2;
    printf("%d\n", a);
    
    *arr[1] = 7;
    printf("%d\n", b);
    *(*(arr + 1)) = 8;
    printf("%d\n", b);

    printf("%p, %p, %p\n", arr[0], *(arr+1), arr[2]);
    printf("%d, %d, %d\n", *arr[0], *(*(arr+1)), *arr[2]);
    
    return 0;
}

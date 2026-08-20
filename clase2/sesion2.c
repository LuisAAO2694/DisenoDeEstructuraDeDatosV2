#include <stdlib.h>
#include <stdio.h>

void duplicar(int x) {
    x *= 2;
    return;
}

int duplicar2(int x) {
    return x * 2;
}

void duplicarPorReferencia(int *x) {
    *x *= 2;
    return;
}

int main () {

    typedef struct  {
        float x;
        float y;
    } Vec2;

    Vec2 myVec = {3, 4};

    Vec2 *myVectPointer;

    myVectPointer = &myVec;

    myVec.x = 5;
    myVec.y = 6;

    printf("myVec { x: %.2f, y: %.2f}\n", myVec.x, myVec.y);

    (*myVectPointer).x = 7;
    (*myVectPointer).y = 8;

    printf("myVec { x: %.2f, y: %.2f}\n", myVec.x, myVec.y);

    myVectPointer->x = 9;
    myVectPointer->y = 10;

    printf("myVec { x: %.2f, y: %.2f}\n", myVec.x, myVec.y);

    int myInt = 2;
    duplicar(myInt);
    printf("%d\n", myInt);

    duplicar2(myInt);
    printf("%d\n", myInt);

    //Mas directo 
    duplicarPorReferencia(&myInt);
    printf("%d\n", myInt);

    //Similar al de arriba, pero con apuntador para reusarlo por cualquier cosa
    int *myIntPointer = &myInt;
    duplicarPorReferencia(myIntPointer);
    printf("%d\n", myInt);

    return 0;
}

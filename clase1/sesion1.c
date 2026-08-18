#include <stdio.h>

int main()
{
    char myChar = 'A';
    char* myCharPointer;

    myCharPointer = &myChar;

    printf("%c\n", myChar); //Valor de mi variable original
    printf("%p\n", &myChar); //Direccion de A
    printf("%p\n", myCharPointer); //Direccion de A 
    printf("%p\n", &myCharPointer); //Direccion del apuntador 

    *myCharPointer= 'B';
    printf("%c\n", myChar); //Valor de mi variable aletrado

    char myChar2 = 'C';
    printf("%c\n", myChar2);
    myCharPointer = &myChar2;

    *myCharPointer = 'D';
    printf("%c\n", myChar2);

    // printf("Size of char pointer: %d\n", sizeof());

    printf("--------------------\n");
    int myIntArray[5];
    printf("%p\n", myIntArray);

    *myIntArray = 5;
    printf("%d\n", myIntArray[0]);
    int *myArrayPointer = myIntArray;

    *myArrayPointer = 10;
    printf("myIntArray[0] = %d\n", myIntArray[0]);

    myArrayPointer++;
    *myArrayPointer=20;
    printf("myIntArray[1] = %d\n", myIntArray[1]);

    myArrayPointer++;
    *myArrayPointer=30;
    printf("myIntArray[2] = %d\n", myIntArray[2]);

    printf("myIntArray[3] = %d\n", myIntArray[3]);
    myArrayPointer+=2;
    *myArrayPointer = 60;
    printf("myIntArray[4] = %d\n", myIntArray[4]);
    return 0;
}
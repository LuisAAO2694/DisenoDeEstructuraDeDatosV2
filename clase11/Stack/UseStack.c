#include "Stack.h"
#include <stdio.h>

bool parenthesesVerifier(char s[], int N)
{
    //Creo la pila donde ire metiendo cada ( que encuentree
    Stack pila = stack_create();
    if(pila == NULL)
    {
        return false;
    }

    //Recorrer la cadena caracter por caracter
    for(int p = 0; p<N && s[p] != '\0'; p++)
    {
        //Encuentro una apertura
        if(s[p] == '(')
        {
            stack_push(pila, 1);
        }
        else if(s[p] == ')')
        {
            if(stack_isEmpty(pila))
            {
                //Aqui esta lo del cierre sin apertura
                printf("Error: ')' sin '(' en la posición %d\n", p);
                stack_destroy(pila);
                return false;
            }
            //Y aqui saco el ( que le corresponde
            stack_pop(pila);
        }
    }

    //Ya cuando termine de recorrer, la pila deberia de estar vacia tons
    bool res = stack_isEmpty(pila);
    if(!res)
    {
        printf("Error: sobra(n) %d '(' sin cerrar\n", stack_size(pila));
    }

    //Ahora ya libero la memoria de la pila 
    stack_destroy(pila);

    return res;
}


//para correrlo  gcc -Wall Stack.c UseStack.c -o UseStack && ./UseStack
int main()
{
    Stack myStack = stack_create();

    if(stack_isEmpty(myStack)) printf("newly created 'myStack' is currently empmty.\n");


    stack_push(myStack, 56);
    stack_push(myStack, 36);
    stack_push(myStack, 76);
    stack_push(myStack, 46);
    stack_push(myStack, 86);


    printf("current top %d\n", stack_top(myStack));
    printf("size %d\n", stack_size(myStack));

    printf("myStack (top -> base): ");
    stack_print(myStack);

    stack_destroy(myStack);

    char myExpression[] = "(A + B) * ((C + D)";
    if(parenthesesVerifier(myExpression, 17))
    {
        printf("%s uses parentheses correctly.\n", myExpression);
    } else {
        printf("%s dosent use parentheses correctly.\n", myExpression);
    }

    printf("\n");
    char myExpression2[] = "((A + B) * (C + D)";
    if(parenthesesVerifier(myExpression2, 18))
    {
        printf("%s uses parentheses correctly.\n", myExpression2);
    } else {
        printf("%s dosent use parentheses correctly.\n", myExpression2);
    }
    
    return 0;
}
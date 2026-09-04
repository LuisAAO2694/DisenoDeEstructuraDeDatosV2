//By LuisAcosta
#include <stdio.h>

//Creo la estructura
typedef struct {
    int day;
    int month;
    int year;
} Date;

//Aqui creo la funcion para imprimir fecha en el formato correct
//Puse el const para decir que no voy a modificar la fecha
void printShortDate(const Date* fecha)  
{
    //Lo voy a imprimir como DD/MM/YY
    //%02d asegura que siempre tenga solo 2 digitos (con cero a la izquierda)
    //El %100 es para obtener el residuo de dividir entre 100 / btw solo obtengo 2 digitos de esto
    //Uso -> para acceder a los campos a traves del pointer
    printf("%02d/%02d/%02d\n", fecha->day, fecha->month, fecha->year % 100);
}

int main() 
{
    //Pruebas 
    printf("----Prueba de mi printShortDate---- \n");

    Date fecha1 = {27, 12, 2020};
    Date fecha2 = {15, 1, 2016};
    Date fecha3 = {8, 5, 2009};

    printf("Fecha 1: ");
    //Paso la direccion de memoria con &
    printShortDate(&fecha1);
    
    printf("Fecha 2: ");
    printShortDate(&fecha2);
    
    printf("Fecha 3: ");
    printShortDate(&fecha3);
    
    return 0;
}
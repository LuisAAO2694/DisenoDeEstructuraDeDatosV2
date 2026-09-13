//By LuisAcosta
#include <stdio.h>

//Creo la estructura
typedef struct {
    int day;
    int month;
    int year;
} Date;

//tipo de funcion de comparacion
typedef int (*CompareFunc)(void*, void*);

//Funcion para compara los date
int compareDate(void* x, void* y)
{
    //Como recibimos void*, btw hay que hacer cast a Date* para poder
    //accedo a los campos, no copio nada
    //trata a esto como dateee
    Date* d1 = (Date*) x;
    Date* d2 = (Date*) y;

    //Comparo los años
    if (d1->year != d2->year)
    {
        return d1->year  - d2->year;
    }

    //Si llegue here, los años son iguales Ahora comparo los meses
    //Same logic si son distintos, la diferencia decide el orden
    if (d1->month != d2->month)
    {
        return d1->month - d2->month;
    } 

    //Si llegue aqui, año y mes son iguales
    //negativo -> d1 es antes, positivo -> d1 es despues,
    //cero -> son exactamente la misma fecha.
    return d1->day - d2->day;
}


//Mi indexOf
int indexOf(void* objects[], void* key, int N, CompareFunc compare) 
{
    //Recorro todo el arreglo desde 0 hasta N-1
    for (int i = 0; i < N; i++) 
    {
        //Si compare() devuelve 0, esto me dicee que objects[i] es igual a key.
        //no puedo comparar con == porque son void* y no se su tipo real
        if (compare(objects[i], key) == 0) 
        {
            return i;
        }
    }
    return -1;
}

//Sort de clase selection sort
void sort(void* objects[], int N, CompareFunc compare) 
{
    //Recorro cada posicion del arreglo, excepto la ultima.
    for (int a = 0; a < N - 1; a++) 
    {
        int minIndex = a;
        //Busco en el resto del arreglo
        //si hay mas elemento mas pequeño que el actual minimo
        for (int b = a + 1; b < N; b++) 
        {
            //compare(objects[b], objects[minIndex]):
            //< 0  -> objects[b] es menor que objects[minIndex]
            //== 0 -> son iguales
            //> 0  -> objects[b] es mayor
            //Si es menor, actualizo el indice del minimo
            if (compare(objects[b], objects[minIndex]) < 0) 
            {
                minIndex = b; //new minimo
            }
        }
        
        //Btwww si el minimo encontrado no es el que estaba en la posición 'a',
        //entonces hago un swap de apuntadores
        //Si minIndex == a, no hace falta hacer nada
        if (minIndex != a) 
        {
            void* tempo = objects[a];
            objects[a] = objects[minIndex];
            objects[minIndex] = tempo;
        }
    }
}


//Este solo es mi nuevo print para las fechas
void printDateArray(void* objects[], int N) 
{
    printf("[");
    for (int i = 0; i < N; i++) 
    {
        Date* d = (Date*) objects[i];
        printf("%02d/%02d/%04d", d->day, d->month, d->year);

        if (i < N - 1) printf(", ");
    }
    printf("]\n");
}


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

//Bien esta funcion solo imprime la fecha en formato largo
void printLongDate(const Date* fecha)
{
    //Defini un arreglo con los nombres de los meses 
    const char* meses[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio",
                            "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

    //Imprimo en formato: "dia de mes de año"
    //fecha->day: accede al dia (ej: 27)
    //meses[fecha->month - 1]: resta 1 al mes porquee enero=1 pero en el arreglo esta en indice 0 btw
    //fecha->year: imprime el año completo (2020)
    printf("%d de %s de %d\n", fecha->day, meses[fecha->month - 1], fecha->year);
}

//Aqui solo defino el tipo de apuntador a funcion
//Creo mi alias PrintFunction
//Recibo un apuntador constante a Date
typedef void (*PrintFunction)(const Date*);


//Esta es mi funcion para impirmir las fechas, recibo el arr con fechas, 
//el cuantas fechas voy a hacerle print y el apuntador a la funcion de print
void printDates(const Date fechas[], int N, PrintFunction impresora)
{
    printf("Imprimiendo %d fechas:\n", N);

    //Aqui uso un bucle para recorrer las N primeras fehcas del arr
    for(int i = 0; i < N; i++)
    {
        //Imprimo el numero de la fecha btw le sumo i+1 para que no empiece en 0 
        printf("Fecha %d: ", i + 1);

        //llamo a la funcion y le paso la direccion de la fecha actual
        impresora(&fechas[i]); 
    }
}

int main()
{
    // //Creo el arreglo de fechas
    // Date fechas[] = {
    //     {27, 12, 2020},
    //     {15, 1, 2016},
    //     {8, 5, 2009},
    //     {10, 12, 2003},
    //     {25, 12, 2023},
    //     {1, 1, 2024},
    //     {14, 2, 2024},
    //     {20, 6, 2024}
    // };
    
    // int totalFechas = sizeof(fechas) / sizeof(fechas[0]);
    
    // printf("----Prueba de mi printDates ---- \n");

    // //Imprimo las primeras 3 fechas en formato corto
    // printf("--- Primeras 3 fechas (formato corto) ---\n");
    // printDates(fechas, 3, printShortDate);
    // printf("\n");
    
    // //Imprimo las primeras 5 fechas en formato largo
    // printf("--- Primeras 5 fechas (formato largo) ---\n");
    // printDates(fechas, 5, printLongDate);
    // printf("\n");
    
    // //Imprimo todas las fechas en formato corto
    // printf("--- Todas las fechas (formato corto) ---\n");
    // printDates(fechas, totalFechas, printShortDate);

    //Creo varias fechas
    Date d1 = {27, 12, 2020};
    Date d2 = {15,  1, 2016};
    Date d3 = { 8,  5, 2009};
    Date d4 = {10, 12, 2003};
    Date d5 = {25, 12, 2023};
    Date d6 = { 1,  1, 2024};
    Date d7 = {14,  2, 2024};
    Date d8 = {20,  6, 2024};

    //Arreglo de apuntadores void*
    void* fechas[] = { &d1, &d2, &d3, &d4, &d5, &d6, &d7, &d8 };
    int N = 8;

    printf("Fechas originales\n");
    printDateArray(fechas, N);

    //Ordeno con sort + compareDate
    sort(fechas, N, compareDate);

    printf("\nFechas ordenadas\n");
    printDateArray(fechas, N);

    //Busco una fecha que existe
    Date key = {25, 12, 2023};
    int pos = indexOf(fechas, &key, N, compareDate);
    printf("\nBuscando 25/12/2023: indice %d\n", pos);

    //Busco una fecha que NO existe
    Date keyNo = { 1,  1, 1900};
    pos = indexOf(fechas, &keyNo, N, compareDate);
    printf("Buscando 01/01/1900 (no existe): indice %d\n", pos);
    
    return 0;
}
#include <stdlib.h>
#include "Vec3.h"
#include <math.h>
#include <stdio.h>

int main()
{
    Vec3 myVector = vec3_create(1,2,3);
    vec3_println(myVector);

    Vec3 myNormalizedVector = vec3_normalize(myVector);
    vec3_println(myVector);

    Vec3 myCopiedVector = vec3_clone(myVector);
    vec3_println(myVector);

    if(myVector == myCopiedVector){
        printf("myVector == myCopiedVector\n");
    } else {
        printf("myVector != myCopiedVector\n");
    }

    if(vec3_equals(myVector, myCopiedVector)){
        printf("myVector equals myCopiedVector\n");
    } else {
        printf("myVector is not equals myCopiedVector\n");
    }


    return 0;
}
/*
 * UseVec3.c
 *
 *  Created on: 24 sept 2026
 *      Author: diego.gilbert
 */
#include <stdio.h>
#include "Vec3.h"

int main() {

	Vec3 myVector = vec3_create(1, 2, 3);
	vec3_println(myVector);

	Vec3 myNormalizedVector = vec3_normalize(myVector);
	vec3_println(myNormalizedVector);

	Vec3 myCopiedVector = vec3_clone(myVector);
	vec3_println(myCopiedVector);

	if (myVector == myCopiedVector) {
		printf("myVector == myCopiedVector\n");
	} else {
		printf("myVector != myCopiedVector\n");
	}

	if (vec3_equals(myVector, myCopiedVector)) {
		printf("myVector equals myCopiedVector\n");
	} else {
		printf("myVector doesn't equal myCopiedVector\n");
	}

	vec3_destroy(myVector);

	return 0;
}

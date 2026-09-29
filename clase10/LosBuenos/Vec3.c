/*
 * Vec3.c
 *
 *  Created on: 24 sept 2026
 *      Author: diego.gilbert
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "Vec3.h"

struct strVec3 {
	float x, y, z;
};

Vec3 vec3_create(float x, float y, float z) {
	Vec3 v = malloc(sizeof(struct strVec3));
	v->x = x;
	v->y = y;
	v->z = z;
	return v;
}

void vec3_destroy(Vec3 v) {
	free(v);
}

void vec3_setX(Vec3 v, float x) {
	v->x = x;
}

void vec3_setY(Vec3 v, float y) {
	v->y = y;
}

void vec3_setZ(Vec3 v, float z) {
	v->z = z;
}

float vec3_getX(Vec3 v) {
	return v->x;
}

float vec3_getY(Vec3 v) {
	return v->y;
}

float vec3_getZ(Vec3 v) {
	return v->z;
}

float vec3_magnitude(Vec3 v) {
	return sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}

Vec3 vec3_normalize(Vec3 v) {
	float mag = vec3_magnitude(v);
	float x = v->x / mag;
	float y = v->y / mag;
	float z = v->z / mag;
	return vec3_create(x, y, z);
}

void vec3_print(Vec3 v) {
	printf("{ %.2f, %.2f, %.2f }", v->x, v->y, v->z);
}

void vec3_println(Vec3 v) {
	vec3_print(v);
	printf("\n");
}

Bool vec3_equals(Vec3 v1, Vec3 v2) {
	if (v1->x == v2->x && v1->y == v2->y && v1->z == v2->z) {
		return True;
	} else {
		return False;
	}
}

Vec3 vec3_clone(Vec3 v) {
	return vec3_create(v->x, v->y, v->z);
}

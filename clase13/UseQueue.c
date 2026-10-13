#include "Queue.h"
#include "Vec3.h"
#include <stdio.h>

void printChar(void* data) {
	printf("%c", *((char*) data));
}

void printVec3(void* data) {
	Vec3 v = (Vec3) data;
	printf("{ %.2f, %.2f, %.2f }", vec3_getX(v), vec3_getY(v), vec3_getZ(v));
}

int main() {

	Queue myCharQueue = queue_create(printChar);
	char myCharArr[] = "Estructuras de datos";
	for (int i = 0; i < 20; i ++) {
		queue_offer(myCharQueue, myCharArr + i);
	}
	queue_print(myCharQueue);
	for (int i = 0; i < 20; i ++) {
		printf("%c", *((char*) queue_poll(myCharQueue)));
	}
	printf("\n");

	Queue myVec3Queue = queue_create(printVec3);
	Vec3 v1 = vec3_create(1, 2, 3);
	Vec3 v2 = vec3_create(2, 3, 4);
	Vec3 v3 = vec3_create(3, 4, 5);
	queue_offer(myVec3Queue, v1);
	queue_offer(myVec3Queue, v2);
	queue_offer(myVec3Queue, v3);
	queue_print(myVec3Queue);

	return 0;
}


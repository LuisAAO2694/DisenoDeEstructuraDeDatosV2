#include <stdio.h>
#include <stdlib.h>

typedef struct strNode {
	int value;
	struct strNode* ref;
} Node;

void printAllLinkedNodes(Node n) {
	printf("{ %d } -> ", n.value);
	while(n.ref != NULL) {
		n = *(n.ref);
		printf("{ %d } -> ", n.value);
	}
	printf("NULL\n");
	/*
	if(n.ref != NULL) {
		printAllLinkedNodes(*n.ref);
	} else {
		printf("NULL\n");
	}
	*/
}

int main() {

	Node n1 = { 1, NULL };
	Node n2 = { 2, NULL };
	Node n3 = { 3, NULL };
	Node n4 = { 4, NULL };
	Node n5 = { 5, NULL };

	// { n1 } -> { n2 } -> { n3 } -> { n4 } -> { n5 }
	// { n6 }

	n1.ref = &n2;
	n2.ref = &n3;
	n3.ref = &n4;
	n4.ref = &n5;

	// [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
	// [ 1, 6, 2, 3, 4, 5, 6, 7, 8, 9 ]

	int myIntArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int i = 8; i > 0; i --) {
		myIntArray[i + 1] = myIntArray[i];
	}
	myIntArray[1] = 6;
	for (int i = 0; i < 10; i ++) {
		printf("%d ", myIntArray[i]);
	}
	printf("\n");

	Node n6 = { 6, NULL };

	n1.ref = &n6;
	n6.ref = &n2;

	printAllLinkedNodes(n1);

	int* myDynamicIntArray = malloc(2 * sizeof(int));
	myDynamicIntArray[0] = 1;
	myDynamicIntArray[1] = 2;
	myDynamicIntArray = realloc(myDynamicIntArray, 4 * sizeof(int));
	myDynamicIntArray[2] = 3;

	for (int i = 0; i < 3; i ++) {
		printf("%d ", myDynamicIntArray[i]);
	}
	printf("\n");

	Node n7 = { 7, NULL };
	n5.ref = &n7;

	printAllLinkedNodes(n1);

	return 0;
}

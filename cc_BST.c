#include <stdio.h>
#include <stdlib.h>
//Coded by Charlie C.

struct Node {
	int val;
	struct Node *left;
	struct Node *right;
};

typedef struct Node *Leaf;

//Creates a new node in memory, scans in its value, and sets its children to NULL
Leaf newLeaf() {
	Leaf temp;

	temp = (Leaf) malloc(sizeof(struct Node));

	scanf("%d", &(temp -> val));
	temp -> left = NULL;
	temp -> right = NULL;

	return temp;
}

//Calls newLeaf(), then determines the placement of the new node/leaf relative to the root node
void plantLeaf(Leaf root) {
	Leaf temp;
	int stopL, stopR;

	temp = newLeaf();

	stopL = 0;
	stopR = 0;

	while (!stopL && !stopR) {
		if (temp -> val < root -> val) {
			if (root -> left != NULL) {
				root = root -> left;
			} else {
				stopL++;
			}

		} else {
			if (root -> right != NULL) {
				root = root -> right;
			} else {
				stopR++;
			}
		}
	}

	if (stopL) {
		root -> left = temp;
	}

	if (stopR) {
		root -> right = temp;
	}
}

//Recursively goes around the tree in ascending order
void walk(Leaf leaf) {
	if (leaf != NULL) {
		walk(leaf -> left);

		printf("%d\t", leaf -> val);

		walk(leaf -> right);
	}
}

//Goes down the right children until none more exist to get the max value
void findMax(Leaf leaf) {
	if (leaf -> right != NULL) {
		findMax(leaf -> right);
	} else {
		printf("\nThe maximum leaf of this tree is %d.\n", leaf -> val);
	}
}

//Goes down the left children until none more exist to get the min value
void findMin(Leaf leaf) {
	if (leaf -> left != NULL) {
		findMin(leaf -> left);
	} else {
		printf("\nThe minimum leaf of this tree is %d.\n", leaf -> val);
	}
}

//Allows the user to explore the tree
void explore(Leaf leaf, Leaf root, int *choice) {
	if (leaf != NULL) {
		printf("\nYou are at %d.", leaf -> val);

		if (leaf == root) {
			printf(" (This is the root.)");
		}

		printf("\n[1]:\tGo left\n");
		printf("[2]:\tPeek left\n\n");
		printf("[3]:\tGo right\n");
		printf("[4]:\tPeek right\n\n");
		printf("[5]:\tStop exploring\n");

		printf("\nWhat do you want to do?\n\t--{ ");

		scanf("%d", choice);

		switch (*choice) {
			case 1: explore(leaf -> left, root, choice); break;
			case 2: {
				if (leaf -> left != NULL) {
					printf("\nTo your left, you can see a %d.\n", leaf -> left -> val);
				} else {
					printf("\nYou see nothing.\n");
				}
				explore(leaf, root, choice);
				break;
			}

			case 3: explore(leaf -> right, root, choice); break;
			case 4: {
				if (leaf -> right != NULL) {
					printf("\nTo your right, you can see a %d.\n", leaf -> right -> val);
				} else {
					printf("\nYou see nothing.\n");
				}
				explore(leaf, root, choice);
				break;
			}

			case 5: printf("Thanks for exploring this tree!\n"); break;
			default: printf("Hey! That's not a valid choice!\n");
		}
	} else {
		printf("Dead end! Better luck next time!\n");
		printf("Wanna try again? [1 = Yes, 0 = No]: ");

		scanf("%d", choice);

		if (*choice) {
			explore(root, root, choice);
		} else {
			printf("Oh well, see ya later!\n");
		}
	}
}

//Recursivly searchs the tree for the target value
void search(Leaf leaf, int target) {
	if (leaf != NULL) {
		if (target < leaf -> val) {
			search(leaf -> left, target);
		} else if (target == leaf -> val) {
			printf("\nFound it! %d is in the tree!.\n", target);
		} else {
			search(leaf -> right, target);
		}
	} else {
		printf("\nSorry, %d is not in the tree.\n", target);
	}
}

int main() {
	Leaf root, temp;
	int leaves, i;

	printf("How many leaves do you want on your Binary Search Tree?\n\t--{ ");
	scanf("%d", &leaves);

	printf("\nPlease enter the values of your leaves in any order\n\t--{ ");

	root = newLeaf();

	for (i = 1; i < leaves; i++) {
		
		plantLeaf(root);
	}

	printf("\nDone! Here's your leaves in sorted ascending order:\n");

	walk(root);
	printf("\n");

	findMin(root);
	findMax(root);

	printf("\nEnter a value to search the tree for: ");
	scanf("%d", &i);
	search(root, i);
	
	explore(root, root, &i);


	return 0;
}
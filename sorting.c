#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Coded by Charlie C.

void printArray(int *array, int arraySize) {
	int j;

	printf("Your array is: [");

	for (j = 0; j < arraySize; j++) {

		if (j + 1 < arraySize) {
			printf("%d, ", array[j]);
		} else {
			printf("%d]\n",array[j]);
		}
	}
}

int* buildArray(int *arraySize) {
	int *array;

	do {
		printf("How many spaces do you want in your array?\n--{ ");
		scanf("%d", arraySize);
	} while (*arraySize <= 0);

	array = (int*) calloc(*arraySize, sizeof(int));

	if (*arraySize == 1) {
		printf("\nPlease enter %d number.\n--{ ", *arraySize);
	} else {
		printf("\nPlease enter %d numbers, separated by spaces.\n--{ ", *arraySize);
	}
	
	int i;

	for (i = 0; i < *arraySize; i++) {

		scanf("%d", &array[i]);
	}

	return array;
}

void swap(int *g, int *h) {
	int temp = *g;
	*g = *h;
	*h = temp;
}

int min(int *array, int arraySize) {
	int resMin = array[0];
	int p;

	for (p = 0; p < arraySize; p++) {

		if (array[p] < resMin) {resMin = array[p];}
	}

	return resMin;
}

int max(int *array, int arraySize) {
	int resMax = array[0];
	int q;

	for (q = 0; q < arraySize; q++) {

		if (array[q] > resMax) {resMax = array[q];}
	}

	return resMax;
}

void randomize(int *array, int arraySize) {
	int i, j, runs, temp;

	printf("\nEnter how many times you want to randomize your array: ");
	scanf("%d", &runs);

	for (j = 0; j < runs; j++) {

		for (i = 0; i < arraySize / 2; i++) {

			do {
				temp = rand() % arraySize;
			} while (temp <= i);

			swap(&array[i], &array[temp]);
		}
	}

	printArray(array, arraySize);

}

void linSrch(int *array, int arraySize) {
	printf("Enter a number to look up in your array\n--{ ");

	int target, t, found;
	scanf("%d", &target);
	found = 0;
	for (t = 0; t < arraySize; t++) {

		if (array[t] == target) {
			found++;
			break;
		}
	}

	if (found) {
		printf("Found it! %d is in your array!\nIt was found with %d iterations of linear search.\n", target, t + 1);
	} else {
		printf("Sorry, %d is not in your array.\n", target);
	}
}

void binSrch(int *array, int arraySize) {
	int target, low, mid, high, srchSpace, partitions, counter;
	
	printf("Enter another number to look up in your array\n--{ ");
	scanf("%d", &target);
	//printf("T: %d\n", target);

	low = 0; high = arraySize - 1;
	srchSpace = arraySize;
	partitions = 0;

	while (srchSpace != 0) {
		/*printf("SS: %d\n", srchSpace); */
		srchSpace /= 2; partitions++;
	}
	//printf("P: %d\n", partitions);

	counter = 0;
	while (counter <= partitions) {

		mid = (high + low) / 2;

		//printf("L: %d | M: %d | H: %d\n", low, mid, high);
		//printf("A[M]: %d\n", array[mid]);
		
		if (array[mid] == target || low == mid && array[high] == target || high == mid && array[low] == target) {
			break;

		} else if (array[mid] < target) {
			low = mid;

		} else if (array[mid] > target) {
			high = mid;
		}

		counter++;
		//printf("C: %d\n", counter);
	}

	if (counter > partitions) {
		printf("Sorry, %d is not in your array.\n", target);
	} else {
		printf("Found it! %d is in your array!\nIt was found with %d iterations of binary search.\n", target, counter);
	}
}

void bubbleSort(int *array, int arraySize) {
	int m, n, swaps;
	printf("\nNow bubble sorting your array!\n");

	for (m = 0; m < arraySize - 1; m++) {

		swaps = 0;
		for (n = 0; n < arraySize - 1; n++) {

			if (array[n] > array[n + 1]) {
				swap(&array[n], &array[n + 1]);
				swaps++;
			}
		}

		if (!swaps) {
			if (m == 0) printf("\nHey! Your array was already sorted!\n");
			break;
		}
	}

	printf("Finished! Your array was bubble sorted!\n");
}

void insertSort(int *array, int arraySize) {
	int i, j;

	printf("\nNow insertion sorting your array!\n");

	for (j = 1; j < arraySize; j++) {

		i = j - 1;

		while (i >= 0 && array[i] > array[i + 1]) {
			swap(&array[i + 1], &array[i]);
			i--;
		}
	}

	printf("Finished! Your array was insertion sorted!\n");
}

int maxIdx(int *array, int arraySize, int firstIndex) {
	int i, max;

	max = firstIndex;

	for (i = firstIndex; i < arraySize; i++) {

		if (array[i] > array[max]) {
			max = i;
		}
	}

	return max;
}

int minIdx(int *array, int arraySize, int firstIndex) {
	int i, min;
	min = firstIndex;

	for (i = firstIndex; i < arraySize; i++) {

		if (array[i] < array[min]) {
			min = i;
		}
	}

	return min;
}

void selectSort(int *array, int arraySize) {
	int i, m;
	printf("\nNow selection sorting your array!\n");

	for (i = 1; i < arraySize; i++) {
		m = minIdx(array, arraySize, i);

		while (m >= i && array[m] < array[m - 1]) {
			swap(&array[m], &array[m - 1]);
			m--;
		}
	}
	printf("Finished! Your array was selection sorted!\n");
}

void merge(int *targ, int *a, int *b, int sizeA, int sizeB) {
	int i, j, k;

	i = 0;
	j = 0;

	for (k = 0; k < sizeA + sizeB; k++) {

		if ((i < sizeA && a[i] < b[j]) || j == sizeB) {
			targ[k] = a[i];
			i++;
		} else {
			targ[k] = b[j];
			j++;
		}		
	}
}

void mergeSort(int *array, int arraySize) {
	int *f, *g;
	int sizeF, sizeG, i, j;

	sizeF = arraySize / 2;
	sizeG = arraySize - sizeF;

	if (arraySize > 1) {

		j = 0;

		f = (int *) calloc(sizeF, sizeof(int));
		for (i = 0; i < sizeF; i++) {

			f[i] = array[j];
			j++;
		}

		g = (int *) calloc(sizeG, sizeof(int));
		for (i = 0; i < sizeG; i++) {

			g[i] = array[j];
			j++;
		}

		mergeSort(f, sizeF);
		mergeSort(g, sizeG);

		merge(array, f, g, sizeF, sizeG);
	}
}

void printHeap(int *heap, int heapSize) {
	int levels, levelSize, i, j, k;
	
	i = 1;
	levels = 0;

	while (i <= heapSize) {
		i = i * 2;
		levels++; 
	}

	levelSize = 1;
	i = 0;

	printf("\nYour heap is:\n");

	for (k = levels; k > 0; k--) {

		printf("\n");
		/*
		for (j = 1; j < k; j++) {

			printf("\t");
		}
		*/
		for (j = 0; j < levelSize; j++) {

			if (i < heapSize) {
				printf("%d\t", heap[i]);
				i++;
			}
		}

		levelSize = levelSize * 2;
	}

	printf("\n");
}

void heapify(int *array, int head, int heapSize) {
	int left, right, largest;

	left = 2 * head + 1;
	right = 2 * head + 2;
	largest = head;

	if (left < heapSize && array[left] > array[head]) {
		largest = left;
	}
	if (right < heapSize && array[right] > array[largest]) {
		largest = right;
	}

	if (largest != head) {
		swap(&array[largest], &array[head]);
	}
}

void buildHeap(int *array, int arraySize) {
	int i;

	for (i = arraySize / 2; i >= 0; i--) {

		heapify(array, i, arraySize);
	}
}

void heapSort(int *array, int arraySize) {
	int i;

	printf("\nNow heap sorting your array!\n");

	buildHeap(array, arraySize);
	printHeap(array, arraySize);

	for(i = arraySize - 1; i > 0; i--) {

		swap(&array[0], &array[i]);
		buildHeap(array, i);

		printHeap(array, i);
	}

	printf("Finished! Your array was heap sorted!\n");
}

void saveArray(int *array, int arraySize) {
	int i;
	char buffer[64];
	FILE *fOut;

	printf("Enter the base name of the file you want to save to: ");
	scanf("%s", buffer);
	strcat(buffer, ".txt");

	fOut = fopen(buffer, "w");

	fprintf(fOut, "%d\n", arraySize);
	for (i = 0; i < arraySize; i++) {
		
		fprintf(fOut, "%d ", array[i]);
	}

	fclose(fOut);
	printf("\nSaved!\n");
}

void loadArray(int **array, int *arraySize) {
	int i;
	char buffer[64];
	FILE *fIn;

	printf("Enter the base name of the file you want to load: ");
	scanf("%s", buffer);
	strcat(buffer, ".txt");

	fIn = fopen(buffer, "r");

	fscanf(fIn, "%d", arraySize);
	*array = (int*) calloc(*arraySize, sizeof(int));

	for (i = 0; i < *arraySize; i++) {
		
		fscanf(fIn, "%d", *array+i);
	}

	fclose(fIn);
	printf("\nLoaded!\n");
}

int main(){
	int size = 0;
	int *a;

	a = buildArray(&size);
	printArray(a, size);

	int done = 0;
	int choice;

	do {
		printf("\n[1]:\tEdit your array");
		printf("\n[2]:\tPrint out your array");
		printf("\n\n[3]:\tFind Min/Max");
		printf("\n[4]:\tSearch for an Element");
		printf("\n\n[5]:\tRandomize your array");
		printf("\n[6]:\tSort your array");
		printf("\n\n[0]:\tExit the program");
		printf("\n\nChoose and option: ");

		scanf("%d", &choice);

		switch (choice) {
			case 1: {
				printf("\n\t[1]:\tRe-enter your array");
				printf("\n\t[2]:\tLoad an array from a text file");
				printf("\n\t[3]:\tSave your array to a text file");
				printf("\n\nChoose and option: ");

				scanf("%d", &choice);

				switch (choice) {
					case 1: a = buildArray(&size); printArray(a, size); break;
					case 2: loadArray(&a, &size); printArray(a, size); break;
					case 3: saveArray(a, size); break;
					default: printf("\nError: Invalid Value!\n");
				}
				break;
			}
			case 2: {
				printArray(a, size);
				break;
			}
			case 3: {
				printf("\n\t[1]:\tFind the minimum element");
				printf("\n\t[2]:\tFind the maximum element");
				printf("\n\nChoose and option: ");

				scanf("%d", &choice);

				switch (choice) {
					case 1: {
						printf("\nThe minimum element is %d.", min(a, size));
						break;
					}
					case 2: {
						printf("\nThe maximum element is %d.", max(a, size));
						break;
					}
					default: printf("\nError: Invalid Value!\n");
				}

				break;
			}
			case 4: {
				printf("\n\t[1]:\tUse linear search");
				printf("\n\t[2]:\tUse binary search");
				printf("\n\nChoose and option: ");

				scanf("%d", &choice);

				switch (choice) {
					case 1: {
						linSrch(a, size);
						break;
					}
					case 2: {
						binSrch(a, size);
						break;
					}
					default: printf("\nError: Invalid Value!\n");
				}

				break;
			}
			case 5: {
				randomize(a, size);
				break;
			}
			case 6: {
				printf("\n\t[1]:\tUse Bubble Sort");
				printf("\n\t[2]:\tUse Insertion Sort");
				printf("\n\t[3]:\tUse Selection Sort");
				printf("\n\t[4]:\tUse Merge Sort");
				printf("\n\t[5]:\tUse Heap Sort");
				printf("\n\nChoose and option: ");

				scanf("%d", &choice);

				switch (choice) {
					case 1: {
						bubbleSort(a, size);
						break;
					}
					case 2: {
						insertSort(a, size);
						break;
					}
					case 3: {
						selectSort(a, size);				
						break;
					}
					case 4: {
						printf("\nNow merge sorting your array!\n");
						mergeSort(a, size);
						printf("Finished! Your array was merge sorted!\n");
						break;
					}
					case 5: {
						heapSort(a, size);
						break;
					}
					default: printf("\nError: Invalid Value!\n");
				}
				break;
			}

			case 0: done++; break;

			default: printf("\nError: Invalid Value!\n");
		}

	} while (!done);

	return 0;
}
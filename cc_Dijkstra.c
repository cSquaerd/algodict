#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Coded by Charlie C. | Started 4/16/17

int* getLine(int size, FILE *in);
int* prepareDP(int size, int x, int *a);
void printLines(int size);
void writeLines(int size, FILE *fo);
void showDAP(int size, int *d, int *a, int *p);
void writeDAP(int size, int *d, int *a, int *p, FILE *fo);
void showMap(int size, int **map);
int checkACCS(int size, int *a);
int* updateDist(int size, int node, int *d, int *p, int **m);
int getMinDist(int size, int* d, int *a);
int* getPath(int size, int *p, int *path, int node, int i);
void writePath(int size, int node, int origin, int *path, FILE *fo);

//Main function
int main(){
	//Declarations for some ints, the D.A.P. arrays, and the map matrix
	int mapSize, i, origin, node, *dist, *accs, *prev, *pathBuff, **map;
	//Char buffer for taking in the name of the input file
	char fBuffer[64];
	//File pointers for input and output
	FILE *fIn, *fOut;

	printf("Enter the name of the file containing your map: ");
	scanf("%s", fBuffer);

	fIn = fopen(fBuffer, "r");
	//Gets the number of nodes in the map,
	//which is the first entry in the input file
	fscanf(fIn, "%d", &mapSize);

	//Allocate memory for the dist array
	dist = (int*) calloc(mapSize, sizeof(int));

	//Allocate memory for the accs array
	accs = (int*) calloc(mapSize, sizeof(int));

	//Allocate memory for the prev array
	prev = (int*) calloc(mapSize, sizeof(int));

	//Allocates space for the pointers to the arrays
	//that make up the rows of the matrix
	map = (int**) calloc(mapSize, sizeof(int));

	//Iteratively read in the map data to fill the matrix
	for (i = 0; i < mapSize; i++) {

		map[i] = getLine(mapSize, fIn);
	}

	fclose(fIn);

	showMap(mapSize, map);

	printf("Map Loaded!\n");

	do {
		printf("Enter the node you want to start from:\n(Must be an integer from 0 to %d)\n(If your map is not doubly-linked, input the origin node)\n\t--{ ", mapSize - 1);
		scanf("%d", &node);

		if (node < 0 || node > mapSize - 1) {
			printf("\nError: Invalid Node.\n");
		}
	} while (node < 0 || node > mapSize - 1);

	//Set all values after the initial to -1
	prepareDP(mapSize, node, dist);

	accs[node] = 1;

	//Set all values after the initial to -1
	prepareDP(mapSize, node, prev);
	prev[node] = node;

	//Stores the origin node somewhere safe
	origin = node;

	//Show the initial D.A.P. arrays and start node
	showDAP(mapSize, dist, accs, prev);
	printf("\nNEXT NODE:\t%d\n", node);

	//We should keep going to nodes that aren't accessed
	//Thus, checking if accs is filled will be our condition
	while(checkACCS(mapSize, accs)) {
		updateDist(mapSize, node, dist, prev, map);
		i = getMinDist(mapSize, dist, accs);
		accs[i] = 1;
		node = i;

		showDAP(mapSize, dist, accs, prev);
		printf("\nNEXT NODE:\t%d\n", node);

	}

	printf("\nDone!\nEnter the base name of the output file you want for the D.A.P. arrays: ");
	scanf("%s", fBuffer);
	strcat(fBuffer, "_Solved.txt");

	fOut = fopen(fBuffer, "w");
	writeDAP(mapSize, dist, accs, prev, fOut);

	fprintf(fOut, "\n");

	pathBuff = (int*) calloc(mapSize, sizeof(int));
	prepareDP(mapSize, mapSize, pathBuff);

	for (i = 0; i < mapSize; i++) {
		if (i != origin) {
			getPath(mapSize, prev, pathBuff, i, 1);
			writePath(mapSize, i, origin, pathBuff, fOut);
			prepareDP(mapSize, mapSize, pathBuff);
		}
	}

	fclose(fOut);

	printf("\nCheck the output file for the shortest paths.");

	//showDAP(mapSize, dist, accs, prev);

	return 0;
}

//Scans a line from the input file and returns it as a pointer array
int* getLine(int size, FILE *in) {
	int i;
	int *line;

	line = (int*) calloc(size, sizeof(int));

	for (i = 0; i < size; i++) {
		fscanf(in, "%d", &line[i]);
	}

	return line;
}

//Sets all cells after the initial in an array to -1
int* prepareDP(int size, int x, int *a) {
	int i;

	if (size > 1) {

		for (i = 0; i < size; i++) {

			if (i != x) {
				a[i] = -1;
			}
		}
	}

	return a;
}

//Prints out lines when showing the contents of the D.A.P. arrays
void printLines(int size) {
	int i;

	printf("\n\t");

	for (i = 0; i < size; i++) {
		printf("------\t");
	}
}

//Writes lines when writing the contents of the D.A.P. arrays to the output file
void writeLines(int size, FILE *fo) {
	int i;

	fprintf(fo, "\n\t");

	for (i = 0; i < size; i++) {
		fprintf(fo, "------\t");
	}
}

//Shows the contents of the D.A.P. arrays
void showDAP(int size, int *d, int *a, int *p) {
	int i;

	printf("\nINDEX:\t");

	for (i = 0; i < size; i++) {

		printf("%d\t", i);
	}

	printLines(size);
	printf("\nDIST:\t");

	for (i = 0; i < size; i++) {
		
		printf("|%d\t", d[i]);
	}

	printf("|\nACCS:\t");

	for (i = 0; i < size; i++) {
		
		printf("|%d\t", a[i]);
	}

	printf("|\nPREV:\t");

	for (i = 0; i < size; i++) {
		
		printf("|%d\t", p[i]);
	}

	printf("|\n");
}

//Writes the contents of the D.A.P. arrays to the output file
void writeDAP(int size, int *d, int *a, int *p, FILE *fo) {
	int i;

	fprintf(fo, "\nINDEX:\t");

	for (i = 0; i < size; i++) {

		fprintf(fo, "%d\t", i);
	}

	writeLines(size, fo);
	fprintf(fo, "\nDIST:\t");

	for (i = 0; i < size; i++) {
		
		fprintf(fo, "|%d\t", d[i]);
	}

	fprintf(fo, "|\nACCS:\t");

	for (i = 0; i < size; i++) {
		
		fprintf(fo, "|%d\t", a[i]);
	}

	fprintf(fo, "|\nPREV:\t");

	for (i = 0; i < size; i++) {
		
		fprintf(fo, "|%d\t", p[i]);
	}

	fprintf(fo, "|\n");
}

//Shows the contents of the map matrix
void showMap(int size, int **map) {
	int i, j;

	printf("\nMAP:\n");

	for (i = 0; i < size; i++) {

		for (j = 0; j < size; j++) {

			printf("|%d\t", map[i][j]);
		}

		printf("|\n");
	}
}

//Returns a boolean value based on the accs array's state
int checkACCS(int size, int *a) {
	int i;

	for (i = 0; i < size; i++) {

		if (a[i] == 0) {
			return 1;
		}
	}

	return 0;
}

//Updates the dist and prev arrays relative to a single node
int* updateDist(int size, int node, int *d, int *p, int **m) {
	int i;

	for (i = 0; i < size; i++) {

		if (m[node][i] != -1 && (m[node][i] + d[node] < d[i] || d[i] == -1)) {
			d[i] = m[node][i] + d[node];
			p[i] = node;
		}
	}
}

//Finds the index containing the minimum unaccessed distance
int getMinDist(int size, int* d, int *a) {
	int i, min;

	min = -1;

	for (i = 0; i < size; i++) {
		//If the ith element hasn't been accessed and
		//If the distance for the ith element has been set and
		//If the ith distance is less than current min distance or
		//If the min is uninitialized
		if ((a[i] == 0 && d[i] > -1) && (d[i] < d[min] || min == -1)) {
			min = i;
		}
	}

	return min;
}

//Gets the shortest path to a node once travelling is complete.
int* getPath(int size, int *p, int *path, int node, int i) {
	if (p[node] != node) {
		getPath(size, p, path, p[node], i + 1);
		path[size - i] = node;
	}
	return path;
}

//Writes out the shortest path to the output file
void writePath(int size, int node, int origin, int *path, FILE *fo) {
	int i;

	fprintf(fo, "The shortest path to node %d from node %d is ", node, origin);

	for (i = 0; i < size; i++) {
		if (path[i] != -1) {
			fprintf(fo, "%d", path[i]);
			if (i + 1 == size) {
				fprintf(fo, ".\n");
			} else {
				fprintf(fo, ", ");
			}
		}
	}
}

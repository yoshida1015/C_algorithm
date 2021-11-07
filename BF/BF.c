/*
 * BF.c
 *
 *  Created on: 2019/07/09
 *      Author: ub301144
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define BUF_SIZE 80
int C=0;
struct node {
	double NS;	/* latitude */
	double EW;	/* longitude */
};
struct node *nodes;
double **dist;
int *visited, *path;
double mincost = INT_MAX;
void Disp(int size) {
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			if (i != j)
				printf("x%d_%d = %f;\n", i, j, dist[i][j]);
}
void Clear(int size) {
	int i;
	for (i = 0; i < size; i++) free(dist[i]);
	free(dist); free(nodes);
}
double EvaluatePath(int size) {
	int i;
	C++;
	double cost = 0;
	for (i = 1; i < size; i++) cost += dist[path[i - 1]][path[i]];
	cost += dist[path[size - 1]][path[0]];
	return cost;
}
void PrintPath(int level) {
	int i;
	for (i = 0; i < level; i++) printf("%2d ", path[i]);
	printf("%2d", path[0]);
}
void BruteForce_func(int node, int level, int size) {
	int next;
	path[level] = node;
	visited[node] = ++level;
	/* Hamiltonian path is found */
	if (level == size) {
		double cost =  EvaluatePath(size);
		if (mincost > cost) mincost = cost;
		PrintPath(level); printf("\tCost = %f\n", cost);
	}
	for (next = 0; next < size; next++)
		if (!visited[next])
			BruteForce_func(next, level, size);
	visited[node] = 0;
}
void BruteForce(int size) {
	int i, level, node;
	if ((path = malloc(sizeof(int) * size)) == NULL) {
		printf("Cannot allocate memory \n"); exit(1);
	}
	if ((visited = malloc(sizeof(int) * size)) == NULL) {
		printf("Cannot allocate memory \n"); exit(1);
	}
	for (i = 0; i < size; i++) visited[i] = 0;

	/* Brute Force Search */
	node = 0; level = 0;
	struct timeval stime, etime;
	double sec;
	gettimeofday(&stime, NULL);
	BruteForce_func(node, level, size);
	gettimeofday(&etime, NULL);
	sec = (etime.tv_sec - stime.tv_sec) +
			(etime.tv_usec - stime.tv_usec) / 1000000.0;
	printf("Elapsed Time %.4f [sec] \n", sec);
	printf("Minimum Cost = %f\n", mincost);
	printf("%d",C);
	C=0;
	free(path); free(visited);
}
int main(int argc, char *argv[]) {
	FILE *fp;
	int i, j, n;
	char buf[BUF_SIZE];
	char command;
	char fname[]="my_tsp10.txt";
	fp=fopen(fname,"r");
	/* Read the file to check the problem size */
	fgets(buf, BUF_SIZE, fp);
	sscanf(buf, "%d", &n);

	/* Memory allocation for the input data */
	if ((nodes = malloc(sizeof(struct node) * n)) == NULL) {
		printf("Cannot allocate memory \n"); exit(1);
	}
	/* Read the problem */
	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		int a; char b[16]; double c; double d;
		sscanf(buf, "%d %s %lf %lf", &a, b, &c, &d);
		nodes[a].NS = c;	/* latitude of Node-a */
		nodes[a].EW = d;	/* longitude of Node-a */
	}
	fclose(fp);

	if ((dist = malloc(sizeof(double*) * n)) == NULL) {
		printf("Cannot allocate memory \n"); exit(1);
	}
	for (i = 0; i < n; i++) {
		if ((dist[i] = malloc(sizeof(double) * n)) == NULL) {
			printf("Cannot allocate memory \n"); exit(1);
		}
		/* Distance from Node-i to Node-j */
		for (j = 0; j < n; j++) {
			if (nodes[i].NS > nodes[j].NS)
				dist[i][j] = nodes[i].NS - nodes[j].NS;
			else
				dist[i][j] = nodes[j].NS - nodes[i].NS;
			if (nodes[i].EW > nodes[j].EW)
				dist[i][j] += nodes[i].EW - nodes[j].EW;
			else
				dist[i][j] += nodes[j].EW - nodes[i].EW;
		}
	}

	printf("[d]       Display TSP Problem\n");
	printf("[b]       Brute-force (Exhaustive) Search\n");
	printf("[e]       Exit\n");
	for (;;) {
		scanf(" %c", &command);
		switch (command) {
		case 'd':	Disp(n); break;
		case 'b':	BruteForce(n); break;
		case 'e':	Clear(n); return 0;
		}
	}
	Clear(n);
	return 0;
}



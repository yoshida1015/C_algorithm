/*
 * qsort.c
 *
 *  Created on: 2019/05/07
 *      Author: ub301144
 */
#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 80
#define NAME_SIZE 32
struct student {
	int score;
	char name[NAME_SIZE];
};
struct student *table;
int my_compare(const struct student *a, const struct student *b) {
	return (a->score > b->score) ? 1 : (a->score < b->score) ? -1 : 0;
}
void Disp(int size) {
	int i;
	for (i = 0; i < size; i++)
		printf("%d\t%s\n", table[i].score, table[i].name);
}
int main(int argc, char *argv[]) {
	FILE *fp;
	int n;
	char buf[BUF_SIZE];
	char command;
	char fname[]="rand10000.txt";
	fp=fopen(fname,"r");
	/* Read the file to count the number of lines in the file */
	n = 0;
	while (fgets(buf, BUF_SIZE, fp) != NULL)
		n++;
	/* Memory allocation */
	if ((table = malloc(sizeof(struct student) * n)) == NULL) {
		printf("Cannot allocate memory \n"); exit(1);
	}
	/* Read the file again to copy the data */
	n = 0;
	fseek(fp, 0L, SEEK_SET);
	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		sscanf(buf, "%d\t%s", &table[n].score, table[n].name);
		n++;
	}
	fclose(fp);

	printf("[d]       Display Table\n");
	printf("[q]       Qsort\n");
	printf("[e]       Exit\n");
	for (;;) {
		scanf(" %c", &command);
		switch (command) {
		case 'd':	Disp(n); break;
		case 'q':	qsort(table, n, sizeof(struct student),
				(int (*)(const void *, const void *))my_compare);
				break;
		case 'e':	free(table); return 0;
		}
	}
	return 0;
}



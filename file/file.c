/*
 * file.c
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
int main(int argc, char *argv[]) {
	FILE *fp;
	int i, n;
	char buf[BUF_SIZE];
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

	/*
	 * Print data
	 */
	for (i = 0; i < n; i++)
		printf("%d\t%s\n", table[i].score, table[i].name);

	free(table);
	return 0;
}



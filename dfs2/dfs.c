/*
 * dfs.c
 *
 *  Created on: 2019/06/13
 *      Author: ub301144
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DEPTH 9
int counter_compare = 0;
int swapp_with_upper(int *board, int *next);
int swapp_with_lower(int *board, int *next);
int swapp_with_right(int *board, int *next);
int swapp_with_left(int *board, int *next);
long board2val(int *board);
void val2board(long val, int *board);
/*** Stack/Hash functions ***/
#define STACK_SIZE 1024
#define HASH_SIZE 1024
void Stack_Init();
int Stack_Size();
void Stack_Push(long val);
long Stack_Pop();
void Hash_Init();
void Hash_Insert(long val);
int Hash_Search(long val);
void Hash_Clear();
/*****************************/
int my_compare(int *board1, int *board2) {
	counter_compare++;
	return memcmp(board1, board2, sizeof(int) * 9);
}
void print_board(int *board, int depth) {
	printf("Depth: %d\n", depth);
	printf("%2d%2d%2d\n", board[0], board[1], board[2]);
	printf("%2d%2d%2d\n", board[3], board[4], board[5]);
	printf("%2d%2d%2d\n", board[6], board[7], board[8]);
}
/* Push board state to Stack */
void dfs_push(int *board, int depth) {
	Stack_Push(board2val(board));
	Stack_Push((int)depth);
}
/* Pop board state from Stack */
void dfs_pop(int *board, int *depth) {
	*depth = (int)Stack_Pop();
	long val = Stack_Pop();
	val2board(val, board);
}
int dfs_empty() {
	return Stack_Size() == 0;
}
/* Set board state as "visited" */
void set_visited(int *board) {
	Hash_Insert(board2val(board));
}
/* Is board state "visited"? */
int is_visited(int *board) {
	return Hash_Search(board2val(board));
}
void DFS(int *init, int *goal) {
	int depth = 0;
	dfs_push(init, depth);
	print_board(init, depth);
	if (!my_compare(init, goal)) {
		printf("Found!\n"); return;
	}
	while (!dfs_empty()) {
		int curr[9], next[9];
		dfs_pop(curr, &depth);
		set_visited(curr);
		depth++;
		/* Swap with upper */
		if (swapp_with_upper(curr, next) != -1) {
			if (!is_visited(next)) {
				print_board(next, depth);
				if (!my_compare(next, goal)) {
					printf("Found!\n"); return;
				}
				if (depth < MAX_DEPTH) dfs_push(next, depth);
			}
		}
		/* Swap with lower */
		if (swapp_with_lower(curr, next) != -1) {
			if (!is_visited(next)) {
				print_board(next, depth);
				if (!my_compare(next, goal)) {
					printf("Found!\n"); return;
				}
				if (depth < MAX_DEPTH) dfs_push(next, depth);
			}
		}
		/* Swap with right */
		if (swapp_with_right(curr, next) != -1) {
			if (!is_visited(next)) {
				print_board(next, depth);
				if (!my_compare(next, goal)) {
					printf("Found!\n"); return;
				}
				if (depth < MAX_DEPTH) dfs_push(next, depth);
			}
		}
		/* Swap with left */
		if (swapp_with_left(curr, next) != -1) {
			if (!is_visited(next)) {
				print_board(next, depth);
				if (!my_compare(next, goal)) {
					printf("Found!\n"); return;
				}
				if (depth < MAX_DEPTH) dfs_push(next, depth);
			}
		}
	}
	printf("Not Found...\n");
}
int main(int argc, char *argv[]) {
	FILE *fp;
	int init[9];
	int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};	/* Target board */
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]); exit(1);
	}
	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("Cannot open file (%s) \n", argv[1]); exit(1);
	}
	fscanf(fp, "%d %d %d %d %d %d %d %d %d",
		&init[0], &init[1], &init[2], &init[3],
		&init[4], &init[5], &init[6], &init[7], &init[8]);
	fclose(fp);

	counter_compare = 0;
	Stack_Init();
	Hash_Init();
	DFS(init, goal);
	printf("Compare %d\n", counter_compare);
	Hash_Clear();
	return 0;
}
/* Board state swapping functions */
int swapp_with_upper(int *board, int *next) {
	int i, pos = -1;
	for (i = 0; i < 9; i++)
		if (board[i] == 0) pos = i;
	if (pos == -1) {
		printf("Invalid board state \n"); exit(1);
	} if (pos == 0 || pos == 1 || pos == 2) {
		/* Cannot be swapped with upper */
		return -1;
	} else {
		memcpy(next, board, sizeof(int) * 9);
		next[pos] = board[pos - 3]; next[pos - 3] = board[pos];
	}
	return 0;
}
int swapp_with_lower(int *board, int *next) {
	int i, pos = -1;
	for (i = 0; i < 9; i++)
		if (board[i] == 0) pos = i;
	if (pos == -1) {
		printf("Invalid board state \n"); exit(1);
	} if (pos == 6 || pos == 7 || pos == 8) {
		/* Cannot be swapped with lower */
		return -1;
	} else {
		memcpy(next, board, sizeof(int) * 9);
		next[pos] = board[pos + 3]; next[pos + 3] = board[pos];
	}
	return 0;
}
int swapp_with_right(int *board, int *next) {
	int i, pos = -1;
	for (i = 0; i < 9; i++)
		if (board[i] == 0) pos = i;
	if (pos == -1) {
		printf("Invalid board state \n"); exit(1);
	} if (pos == 2 || pos == 5 || pos == 8) {
		/* Cannot be swapped with right */
		return -1;
	} else {
		memcpy(next, board, sizeof(int) * 9);
		next[pos] = board[pos + 1]; next[pos + 1] = board[pos];
	}
	return 0;
}
int swapp_with_left(int *board, int *next) {
	int i, pos = -1;
	for (i = 0; i < 9; i++)
		if (board[i] == 0) pos = i;
	if (pos == -1) {
		printf("Invalid board state \n"); exit(1);
	} if (pos == 0 || pos == 3 || pos == 6) {
		/* Cannot be swapped with right */
		return -1;
	} else {
		memcpy(next, board, sizeof(int) * 9);
		next[pos] = board[pos - 1]; next[pos - 1] = board[pos];
	}
	return 0;
}
/* Converter functions */
/* board[9]={1,2,3,8,0,4,7,6,5} --> val=123804765 */
long board2val(int *board) {
	int i, digit = 1;
	long val = 0;
	for (i = 0; i < 9; i++) {
		val += board[8 - i] * digit;
		digit *= 10;
	}
	return val;
}
/* val=123804765 --> board[9]={1,2,3,8,0,4,7,6,5} */
void val2board(long val, int *board) {
	int i, digit = 1;
	for (i = 0; i < 9; i++) {
		board[8 - i] = (val / digit) % 10;
		digit *= 10;
	}
}
/*** Stack functions ***/
long stack[STACK_SIZE];
int stack_ptr;
void Stack_Init() {
	stack_ptr = 0;
}
int Stack_Size() {
	return stack_ptr;
}
void Stack_Push(long val) {
	if (Stack_Size() < STACK_SIZE) {
		stack[stack_ptr++] = val;
	} else {
		printf("Stack overflow \n"); exit(1);
	}
}
long Stack_Pop() {
	if (Stack_Size() > 0) {
		return stack[--stack_ptr];
	} else {
		printf("Stack underflow \n"); exit(1);
	}
}
/*** Hash functions ***/
#define HASH(i) ((i) % HASH_SIZE)
struct hashentry {
	long val;
	struct hashentry *next;
};
struct hashentry *hashtable[HASH_SIZE];
void Hash_Init() {
	int i;
	for (i = 0; i < HASH_SIZE; i++)
		hashtable[i] = NULL;
}
void Hash_Insert(long val) {
	struct hashentry *p;
	int h = HASH(val);
	if ((p = malloc(sizeof(struct hashentry))) == NULL) {
		printf("Memory allocation error\n"); exit(1);
	}
	/* Copy val to p */
	p->val = val;
	/* Insert p to the list */
	p->next = hashtable[h]; hashtable[h] = p;
}
int Hash_Search(long val) {
	struct hashentry *p;
	int h = HASH(val);
	/* If the node exists on the list, then return 1 */
	for (p = hashtable[h]; p != NULL; p = p->next)
		if (p->val == val) return 1;
	/* Otherwise return 0 */
	return 0;
}
void Hash_Clear() {
	int i;
	struct hashentry *p;
	for (i = 0; i < HASH_SIZE; i++) {
		while (hashtable[i] != NULL) {
			p = hashtable[i];
			hashtable[i] = p->next;
			free(p);
		}
	}
}



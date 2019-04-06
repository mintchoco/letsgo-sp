/*
 ============================================================================
 Name        : sp_exploremaze.c
 Author      : bhlim
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 100

#undef DEBUG_PRINT

struct qItem {
	int rowIdx;
	int colIdx;
	int curdist;
};


int qFront = 0;
int qRear = 0;

struct qItem item[QUEUE_SIZE];


int qEmpty() {
	if(qFront == qRear) {
		return 1;
	}

	return 0;
}

int qFull() {
	int idx;

	idx = qRear + 1;
	if (idx >= QUEUE_SIZE) {
		idx = 0;
	}

	if (idx == qFront) {
		return 1;
	}

	return 0;
}

struct qItem dequeue() {
	struct qItem rsltItem;

	rsltItem = item[qFront];

#ifdef DEBUG_PRINT
	printf("Dequeue log qFront:%d (%d, %d) -%d\n", qFront, rsltItem.rowIdx, rsltItem.colIdx, rsltItem.curdist);
#endif

	qFront++;
	if (qFront >= QUEUE_SIZE) {
		qFront = 0;
	}
	return rsltItem;
}

void enqueue(struct qItem input) {

	item[qRear] = input;

#ifdef DEBUG_PRINT
	printf("Enqueue log qRear:%d (%d, %d) -%d\n", qRear, input.rowIdx, input.colIdx, input.curdist);
#endif

	qRear++;

	if (qRear >= QUEUE_SIZE) {
		qRear = 0;
	}
}


void printInputMaze(int row, int col, char* m) {
	printf("Matrix of maze\n");

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%c", m[i * col + j]);
		}
		printf("\n");
	}
}

int calcDistByBFS(int r, int c, char* m) {
	int* fVisit;

	int rowIdx = 0;
	int colIdx = 0;
	int dist = 1;
	int ret = 0;

	struct qItem pushItem;
	struct qItem popItem;

	if (m[rowIdx * c + colIdx] == '1') {
		fVisit = calloc(r*c, sizeof(int));

		pushItem.rowIdx = rowIdx;
		pushItem.colIdx = colIdx;
		pushItem.curdist = dist;

#ifdef DEBUG_PRINT
		printf("Push (%d, %d) - %d\n", pushItem.rowIdx, pushItem.colIdx, pushItem.curdist);
#endif
		enqueue(pushItem);
		fVisit[rowIdx * c + colIdx] = 1;
	}
	else {
#ifdef DEBUG_PRINT
		printf("Start point is not enable\n");
#endif
		return 0;
	}

	while (!qEmpty()) {
		popItem = dequeue();

#ifdef DEBUG_PRINT
		printf("Pop (%d, %d) - %d\n", popItem.rowIdx, popItem.colIdx, popItem.curdist);
#endif

		rowIdx = popItem.rowIdx;
		colIdx = popItem.colIdx;
		dist = popItem.curdist;

		if((rowIdx == r - 1) && (colIdx == c - 1)) {
#ifdef DEBUG_PRINT
			printf("Exit maze point is found - shortest path distance : %d\n", dist);
#endif
			ret = dist;
			break;
		}

		if(rowIdx - 1 >= 0 && (fVisit[(rowIdx-1)*c + colIdx] == 0)) {
			if(m[(rowIdx-1)*c + colIdx] == '1') {
				pushItem.rowIdx = rowIdx-1;
				pushItem.colIdx = colIdx;
				pushItem.curdist = dist+1;

#ifdef DEBUG_PRINT
				printf("Push (%d, %d) - %d\n", pushItem.rowIdx, pushItem.colIdx, pushItem.curdist);
#endif
				enqueue(pushItem);
				fVisit[(rowIdx-1) * c + colIdx] = 1;
			}
		}

		if(rowIdx + 1 < r && (fVisit[(rowIdx+1)*c + colIdx] == 0)) {
			if(m[(rowIdx+1)*c + colIdx] == '1') {
				pushItem.rowIdx = rowIdx+1;
				pushItem.colIdx = colIdx;
				pushItem.curdist = dist+1;

#ifdef DEBUG_PRINT
				printf("Push (%d, %d) - %d\n", pushItem.rowIdx, pushItem.colIdx, pushItem.curdist);
#endif
				enqueue(pushItem);
				fVisit[(rowIdx+1) * c + colIdx] = 1;
			}
		}

		if(colIdx - 1 >= 0 && (fVisit[(rowIdx)*c + colIdx-1] == 0)) {
			if(m[rowIdx*c + colIdx - 1] == '1') {
				pushItem.rowIdx = rowIdx;
				pushItem.colIdx = colIdx-1;
				pushItem.curdist = dist+1;

#ifdef DEBUG_PRINT
				printf("Push (%d, %d) - %d\n", pushItem.rowIdx, pushItem.colIdx, pushItem.curdist);
#endif
				enqueue(pushItem);
				fVisit[rowIdx * c + colIdx - 1] = 1;
			}
		}

		if(colIdx + 1 < c && (fVisit[rowIdx*c + colIdx + 1] == 0)) {
			if(m[rowIdx*c + colIdx + 1] == '1') {
				pushItem.rowIdx = rowIdx;
				pushItem.colIdx = colIdx+1;
				pushItem.curdist = dist+1;

#ifdef DEBUG_PRINT
				printf("Push (%d, %d) - %d\n", pushItem.rowIdx, pushItem.colIdx, pushItem.curdist);
#endif
				enqueue(pushItem);
				fVisit[rowIdx * c + colIdx + 1] = 1;
			}
		}

	}

	free(fVisit);

	return ret;
}

int main(void) {

	int row, column;
	char* maze;

	int shortPathCnt = 0;

	char strContent[100] = {0,};

	printf("Enter maze number of row & column:\n");

	scanf("%d %d", &row, &column);

#ifdef DEBUG_PRINT
	printf("row : %d, column : %d\n", row, column);
#endif

	maze = malloc(sizeof(char) * row * column);

	printf("Enter maze matrix:\n");

	for (int i = 0; i < row; i++) {
		scanf("%s", strContent);

		if (column != strlen(strContent)) {
			printf("Incorrect input - Please enter correct input\n");
		}

#ifdef DEBUG_PRINT
		printf("Input String: %s\n", strContent);
#endif

		for (int j = 0; j < column; j++) {
			maze[i * column + j] = strContent[j];
		}
	}

#ifdef DEBUG_PRINT
	printInputMaze(row, column, maze);
#endif

	shortPathCnt = calcDistByBFS(row, column, maze);

	printf("\nShortest Path Distance : %d\n", shortPathCnt);

	free(maze);

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define RADIX 10
#define DIGIT 2

typedef struct QNode {
	int data;
	struct QNode *link;
}QNode;

typedef struct {
	QNode *front, *rear;
} LQueueType;

LQueueType *createLinkedQueue() {
	LQueueType *LQ;
	LQ = (LQueueType *)malloc(sizeof(LQueueType));
	LQ->front = NULL;
	LQ->rear = NULL;
	return LQ;
}

int isEmpty(LQueueType *LQ) {
	if (LQ->front == NULL) return 1;
	else return 0;
}

void enQueue(LQueueType *LQ, int item) {
	QNode *newNode = (QNode *)malloc(sizeof(QNode));
	newNode->data = item;
	newNode->link = NULL;
	if (LQ->front == NULL) {
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else {
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}
int deQueue(LQueueType *LQ) {
	QNode *old = LQ->front;
	int item;
	if (isEmpty(LQ)) return 0;
	else {
		item = old->data;
		LQ->front = LQ->front->link;
		if (LQ->front == NULL) {
			LQ->rear = NULL;
		}
		free(old);
		return item;
	}
}
void radixSort(int a[], int n,int m) {
	int i, bucket, d, factor = (int)pow(10.0,(double)m);
	LQueueType *Q[RADIX];
	for (bucket = 0; bucket < RADIX; bucket++) {
		Q[bucket] = createLinkedQueue();
	}
	for (d = 0; d < 1; d++) {
		for (i = 0; i < n; i++) {
			enQueue(Q[(a[i] / factor) % 10], a[i]);
		}
		for (bucket = 0,i = 0; bucket < RADIX; bucket++) {
			while (!isEmpty(Q[bucket])) {
				a[i++] = deQueue(Q[bucket]);
			}
		}	
	}
}
int main() {
	FILE *input_fp, *output_fp;

	if ((input_fp = fopen("hw1.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw1.inp");
	}
	if ((output_fp = fopen("hw1.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw1.inp");
	}
	int length1 = 0, length2 = 0;
	char charTemp = '\0';
	int str1[100];
	int str2[100];
	while (1) {
		fscanf(input_fp, "%d%c", &str1[length1++], &charTemp);
		if (charTemp == '\n') {
			while (1) {
				fscanf(input_fp, "%d%c", &str2[length2++], &charTemp);
				if (charTemp == '\n') break;
			}
			break;
		}
	}
	int i, j,m;
	int check = 0;
	for (i = 0; i < length1; i++) {
		for (j = 0; j < length1; j++) {
			if (str1[j]/(int)pow(10.0, (double)i) != 0) {
				check=1;
			}
		}
		if (check == 0) {
			m = i;
			break;
		}
		else {
			check = 0;
		}
	}
	for (i = 0; i < m ; i++) {
		radixSort(str1, length1, i);
		for (j = 0; j < length1; j++) {
			fprintf(output_fp, "%d", str1[j]);
			if (j == (length1 - 1)) {
				fprintf(output_fp, "\n");
			}
			else {
				fprintf(output_fp, " ");
			}
		}
	}
	for (i = 0; i < length2; i++) {
		for (j = 0; j < length2; j++) {
			if (str2[j] / (int)pow(10.0, (double)i) != 0) {
				check = 1;
			}
		}
		if (check == 0) {
			m = i;
			break;
		}
		else {
			check = 0;
		}
	}
	for (i = 0; i < m; i++) {
		radixSort(str2, length2, i);
		for (j = 0; j < length2; j++) {
			fprintf(output_fp, "%d", str2[j]);
			if (j == (length2 - 1)) {
				fprintf(output_fp, "\n");
			}
			else {
				fprintf(output_fp, " ");
			}
		}
	}


	int len = length1 + length2;
	j = 0;
	for (i = length1; i < len; i++) {
		str1[i] = str2[j++];
	}

	int temp;
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			if (str1[i] < str1[j]) {
				temp = str1[i];
				str1[i] = str1[j];
				str1[j] = temp;
			}
		}
	}
	for (i = 0; i < len; i++) {
		fprintf(output_fp,"%d", str1[i]);
		if (i == (len - 1)) {
			fprintf(output_fp, "\n");
		}
		else {
			fprintf(output_fp, " ");
		}
	}
	fprintf(output_fp,"*");
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}
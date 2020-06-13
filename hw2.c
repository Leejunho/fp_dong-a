#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATASIZE 100

int compare(void * first, void * second) {
	if (*(int *)first > *(int*)second)
		return 1;
	else if (*(int *)first < *(int*)second)
		return -1;
	else
		return 0;
}
int main() {
	FILE *input_fp, *output_fp;
	if ((input_fp = fopen("hw2.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw2.inp");
	}
	if ((output_fp = fopen("hw2.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw2.inp");
	}
	
	int length = 0;
	int run = 0;
	char charTemp = '\0';
	int data[DATASIZE];
	int data2[DATASIZE];
	int fp1[DATASIZE];
	int fp2[DATASIZE];
	int fp3[DATASIZE];

	//파일 읽어오기
	while (1) {
		fscanf(input_fp, "%d%c", &data[length++], &charTemp);
		if (charTemp == '\n')
			break;
	}
	fscanf(input_fp, "%d", &run);
	int i, j, k;
	
	int len = length / run;

	//run=5일때
	if (run == 5) {
		//정렬단계
		int *arr = NULL;
		arr = (int *)malloc(sizeof(int));
		int length2 = 0;
		int fp1_len = 0;
		int fp2_len = 0;
		int fp3_len = 0;
		for (i = 1; i <= run; i++) {
			int *arr = NULL;
			arr = (int *)malloc(sizeof(int));
			if (i % 2 == 1) {
				for (j = 0; j < len; j++) {
					arr[j] = data[length2++];
				}
				qsort(arr, len, sizeof(int), compare);
				for (j = 0; j < len; j++)
					fp1[fp1_len++] = arr[j];
			}
			else {
				for (j = 0; j < len; j++) {
					arr[j] = data[length2++];
				}
				qsort(arr, len, sizeof(int), compare);
				for (j = 0; j < len; j++)
					fp2[fp2_len++] = arr[j];
			}
		}
		for (i = 0; i < fp1_len; i++) {
			fprintf(output_fp, "%d", fp1[i]);
			if ((i + 1) % len == 0 && i != (fp1_len - 1))
				fprintf(output_fp, " & ");
			else if (i == (fp1_len - 1))
				fprintf(output_fp, "\n");
			else
				fprintf(output_fp, " ");
		}
		for (i = 0; i < fp2_len; i++) {
			fprintf(output_fp, "%d", fp2[i]);
			if ((i + 1) % len == 0 && i != (fp2_len - 1))
				fprintf(output_fp, " & ");
			else if (i == (fp2_len - 1))
				fprintf(output_fp, "\n");
			else
				fprintf(output_fp, " ");
		}
		fprintf(output_fp, "\n");
		//1차 합병
		for (i = 0; i < len; i++) { arr[fp3_len++] = fp1[i]; }
		for (j = 0; j < len; j++) { arr[fp3_len++] = fp2[j]; }
		qsort(arr, fp3_len, sizeof(int), compare);
		for (k = 0; k < fp3_len; k++) { fp3[k] = arr[k]; }
		fp3_len = 0;
		for (i; i < fp2_len; i++) { arr[fp3_len++] = fp1[i]; }
		for (j; j < fp2_len; j++) { arr[fp3_len++] = fp2[j]; }
		qsort(arr, fp3_len, sizeof(int), compare);
		int arr_len = fp3_len;
		for (i; i < fp1_len; i++) {//fp1 출력
			fprintf(output_fp, "%d", fp1[i]);
			if (i != (fp1_len - 1))
				fprintf(output_fp, " ");
			else
				fprintf(output_fp, "\n");
		}
		fprintf(output_fp, "\n");//fp2 출력
		for (i = 0; i < arr_len; i++) fp3[fp3_len++] = arr[i];
		for (i = 0; i < fp3_len; i++) {//fp3 출력
			fprintf(output_fp, "%d", fp3[i]);
			if ((i + 1) % len == 0 && i != (fp3_len - 1))
				fprintf(output_fp, " & ");
			else if (i == (fp3_len - 1))
				fprintf(output_fp, "\n");
			else
				fprintf(output_fp, " ");
		}
		//2차 합병

		free(arr);
	}

	fclose(input_fp);
	fclose(output_fp);
	return 0;
}
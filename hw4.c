#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void foldingHasing(long data, long dataField[], int N, char key[],int knum[]);
void linearProbing(long data, int temp, int N, long dataField[],char key[],int knum[]);
void print_folding(FILE * output_fp, long dataField[], int N, int knum[]);
int rev(int n);
int su(int n);
int main() {
	FILE *input_fp, *output_fp;

	if ((input_fp = fopen("hw4.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw4.inp");
	}
	if ((output_fp = fopen("hw4.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw4.inp");
	}
	long data;
	long dataField[1000] = { 0, };
	int N = 0;
	char charTemp = '\0';
	fscanf(input_fp, "%d%c", &N, &charTemp);
	int knum[1000] = { 0, };
	char key[12];
	int a = 0;
	while (1) {
		fscanf(input_fp, "%s ", &key);
		if (key[0] == '*')
			break;
		data = atoi(key);
		foldingHasing(data, dataField, N, key, knum);
	}
	print_folding(output_fp, dataField, N, knum);
	fprintf(output_fp, "*");
	
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}

void foldingHasing(long data, long dataField[], int N,char key[],int knum[]) {
	int a = 0, b = 0, c = 0;
	int add = 0;
	int i;
	c = data % 10000;
	c = rev(c);
	b = (data / 10000) % 10000;
	a = data / 100000000;
	a = rev(a);
	add = a + b + c;
	if (add > 10000)
		add -= 10000;
	if (dataField[add%N] != 0) {
		linearProbing(data, add%N, N, dataField,key,knum);
	}
	else {
		dataField[add%N] = data;
		knum[add%N] = strlen(key);
	}
	return;

}
void linearProbing(long data, int temp, int N, long dataField[], char key[],int knum[]) {
	int i = 0, j = 0;
	int temp2 = 0;
	temp2 = temp;
	int i_temp = 0, j_temp = 0;
	while (1) {
		temp += 1;
		i++;
		if (temp == N - 1)
			temp = 0;
		if (dataField[temp] == 0) {
			i_temp = temp;
			break;
		}
	}
	while (1) {
		temp2 -= 1;
		j++;
		if (temp2 == 0)
			temp2 = N-1;
		if (dataField[temp2] == 0) {
			j_temp = temp2;
			break;
		}
	}
	if (i <= j) {
		dataField[i_temp] = data;
		knum[i_temp] = strlen(key);
	}
	else {
		dataField[j_temp] = data;
		knum[j_temp] = strlen(key);
	}

	return;
	

}
void print_folding(FILE * output_fp, long dataField[], int N,int knum[]) {
	int i;
	for (i = 0; i < N; i++) {
		if (dataField[i] != 0) {
			if (knum[i] == su(dataField[i]))
				fprintf(output_fp, "<%d, %ld>\n", i, dataField[i]);
			else {
				int j;
				fprintf(output_fp, "<%d, ", i);
				for (j = 0; j < knum[i] - su(dataField[i]); j++) {
					fprintf(output_fp, "0");
				}
				fprintf(output_fp, "%ld>\n", dataField[i]);
			}
		}
	}
}
int rev(int n) {
	int result = 0;
	int temp = n;
	while (n > 0) {
		result = result * 10 + n % 10;
		n /= 10;
	}
	if (temp < 1000) {
		if (temp < 100) {
			if (temp < 10)
				return result * 1000;
			return result * 100;
		}
		return result * 10;
	}
	return result;
}
int su(int n) {
	int check = 10, result = 1;
	while (n / check) {
		result++;
		check *= 10;
	}
	return result;
}
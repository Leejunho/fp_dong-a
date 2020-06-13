#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b)  ( a>b ? a:b )

typedef struct Node {
	int key;
	struct Node *left;
	struct Node *right;
}avlNode;

int high(avlNode *node) {
	int height = 0;
	if (node != NULL)
		height = 1 + MAX(high(node->left), high(node->right));
	return height;
}

int avlBF(avlNode *node) {
	int height = 0;
	if (node == NULL)
		return 0;
	else
		return high(node->left) - high(node->right);
}
avlNode *rotation_A(avlNode *parent, int bf, FILE * output_fp)
{
	avlNode *child;

	if (bf > 1)		//LL로테이션
	{
		child = parent->left;
		parent->left = child->right;
		child->right = parent;
	}
	else			//RR로테이션
	{
		child = parent->right;
		parent->right = child->left;
		child->left = parent;
	}

	return child;
}

avlNode *rotation_B(avlNode *parent, int bf, FILE * output_fp)
{
	avlNode *child;
	if (bf > 1)		//LR로테이션
	{
		child = parent->left;
		parent->left = rotation_A(child, -2,output_fp); //RR
		return rotation_A(parent, 2,output_fp); //LL

	}
	else	//RL로테이션
	{
		child = parent->right;
		parent->right = rotation_A(child, 2,output_fp); //LL
		return rotation_A(parent, -2,output_fp);	//RR
	}
}
avlNode *BF_balance(avlNode *node, FILE * output_fp)
{
	int bf = avlBF(node);

	if (bf > 1) {
		if (avlBF(node->left) > 0) {
			fprintf(output_fp, "(LL)", bf);
			return rotation_A(node, bf, output_fp);
		}
		else {
			fprintf(output_fp, "(LR)", bf);
			return rotation_B(node, bf, output_fp);
		}
	}
	else if (bf < -1) {
		if (avlBF(node->right) < 0) {
			fprintf(output_fp, "(RR)", bf);
			return rotation_A(node, bf, output_fp);
		}
		else {
			fprintf(output_fp, "(RL)", bf);
			return rotation_B(node, bf, output_fp);
		}
	}
	return node;
}
avlNode *avlInsert(avlNode *root, int key,FILE * output_fp)
{
	int bf = 0;
	
	if (root == NULL) {
		root = (avlNode*)malloc(sizeof(avlNode));
		if (root == NULL) {
			printf("메모리 할당 오류\n");
			exit(-1);
		}
		root->key = key;
		root->left = NULL;
		root->right = NULL;
	}
	else if (root->key > key) {
		root->left = avlInsert(root->left, key,output_fp);
	}

	else if (root->key < key) {
		root->right = avlInsert(root->right, key,output_fp);
	}

	fprintf(output_fp, "%d ", avlBF(root));
	return root;
	
}
avlNode *avlprint(avlNode *root, int key, FILE * output_fp)
{
	int bf = 0;
	bf = avlBF(root);
	if (root->key > key) {
		fprintf(output_fp, "%d ", bf);
		root->left = avlprint(root->left, key, output_fp);
	}
	else if (root->key < key) {
		fprintf(output_fp, "%d ", bf);
		root->right = avlprint(root->right, key,  output_fp);
	}
	else 
		fprintf(output_fp, "%d ", bf);
	return root;
}
avlNode *avlbalance(avlNode *root, int key, FILE * output_fp)
{
	int bf = 0;
	if (root == NULL) {
		root = (avlNode*)malloc(sizeof(avlNode));
		if (root == NULL) {
			printf("메모리 할당 오류\n");
			exit(-1);
		}
		root->key = key;
		root->left = NULL;
		root->right = NULL;
	}
	else if (root->key > key) {
		root->left = avlbalance(root->left, key, output_fp);
	}

	else if (root->key < key) {
		root->right = avlbalance(root->right, key, output_fp);
	}
	root = BF_balance(root, output_fp);
	return root;
}


void inorder(avlNode *root, FILE * output_fp)
{
	int bf = 0;
	if (root) {
		inorder(root->left, output_fp);
		fprintf(output_fp, "(%d:%d)", root->key, avlBF(root));
		inorder(root->right, output_fp);
	}
}


int main() {
	FILE *input_fp, *output_fp;
	avlNode *root = NULL;

	if ((input_fp = fopen("hw3.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw3.inp");
	}
	if ((output_fp = fopen("hw3.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw3.inp");
	}
	int length = 0;
	char charTemp = '\0';
	int str[100];
	while (1) {
		fscanf(input_fp, "%d%c", &str[length++], &charTemp);
		if (charTemp == '\n')
			break;
	}
	int i;
	for (i = 0; i < length; i++) {
		
		root = avlInsert(root, str[i],output_fp);

		root = avlbalance(root,str[i], output_fp);;
		fprintf(output_fp, "\n");
		
	}
	inorder(root, output_fp);
	fprintf(output_fp, "\n*");


	fclose(input_fp);
	fclose(output_fp);
	return 0;
}

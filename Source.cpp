#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

typedef struct node {
	int key = 0;
	int index = 0;
	struct node* copii[10];
}NodeT;

typedef struct node1 {
	int key;
	struct node1* left;
	struct node1* right;
}NodeB;

NodeT* newNode(int data)
{
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	p->key = data;
	p->index = 0;
	for (int i = 0; i < 4; i++) {
		p->copii[i] = NULL;
	}
	return p;
}


NodeB* binary_node(int key) {
	NodeB* p = (NodeB*)malloc(sizeof(NodeB));
	p->key = key;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void addChild(NodeT** nodul ,int data) {
	int aux = (*nodul)->index;
	(*nodul)->copii[aux] = newNode(data);
	((*nodul)->index)++;
	
}

NodeT* T1(int* arr, int n, NodeT* created[]) {
	NodeT* root = newNode(-5);
	NodeT* p;
	for (int i = 0; i < n; i++) {

		if (arr[i] == -1) {
			if (created[i] == NULL) {
				p = newNode(i);
				created[i] = p;
				root = p;
			}
			else {
				root = created[i];
			}
			continue;
		}
		
		if (created[arr[i]] == NULL) {
			p = newNode(arr[i]);
			created[arr[i]] = p;
			addChild(&created[arr[i]], i);
			int aux = created[arr[i]]->index;
			created[i] = (created[arr[i]])->copii[aux - 1];
		}

		else {
			addChild(&created[arr[i]], i);
			int aux2 = created[arr[i]]->index;
			created[i] = created[arr[i]]->copii[aux2 - 1];
		}
	} 
	return root;
}


NodeB* buildT2(NodeT* root) {
	NodeB* rootBT = binary_node(root->key);

	if (root->index != 0) {
		rootBT->left = buildT2(root->copii[0]);
	}
	NodeB* left = rootBT->left;
	for (int i = 1; i < root->index; i++) {
		left->right = buildT2(root->copii[i]);
		left = left->right;
	}
	return rootBT;
}

void printBinary(NodeB* root, int nivelul)
{
	if (root != NULL) {
		NodeB* p = root;
		while (p != NULL)
		{
			for (int i = 0; i < nivelul; i++)
				printf("   ");
			printf("%d\n", p->key);
			printBinary(p->left, nivelul + 1);
			p = p->right;
		}
	}
}

void init(NodeT* created[], int n) {
	for (int i = 0; i < n; i++) {
		created[i] = NULL;
	}
}

void printR2(NodeT* root, int space)
{
	if (root == NULL)
		return;
	for (int i = 0; i < space; i++) {
		printf(" ");
	}
	printf("%d\n\n", root->key);
	space += 5;
	for (int i = 0; i < root->index; i++) {
		printR2(root->copii[i], space);
	}
}

int main(void) {

	int n = 9;
	int p[] = { 1,6,4,1,6,6,-1,4,1};
	NodeT* created[9];
	init(created, n);
	NodeT* root = T1(p, n, created);
	NodeB* root1 = buildT2(root);
	printR2(root, 0);
	//NodeT* r = root->copii[1]->copii[1];
	//printf("%d", r->key);
	printf("\n");
	printBinary(root1, 0);

return 0;
}
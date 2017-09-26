#ifndef MY_AVLTREE
#define MY_AVLTREE
#include<iostream>
#include<cmath>
#define PRINTS(x) std::cout<<x<<std::ends

struct AvlNode;
typedef AvlNode* AvlTree;
typedef AvlNode* Position;
struct AvlNode {
	int val;
	AvlTree lTree, rTree; 
	int Height;
	AvlNode() :lTree(NULL), rTree(NULL) {}
};

AvlTree MakeEmpty(AvlTree T);
Position Find(AvlTree T,int val);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(AvlTree &T, int val);
AvlTree Delete(AvlTree &T, int val);
int Retrieve(Position p);
AvlTree SingleRotateWithLeft(AvlTree T);
AvlTree SingleRotateWithRight(AvlTree T);
AvlTree DoubleRotateWithLeft(AvlTree T);
AvlTree DoubleRotateWithRight(AvlTree T);
void Print(AvlTree T)
{

	if (T == NULL)return;
	Print(T->lTree);
	PRINTS(T->val);
	Print(T->rTree);
}
void InsAndPrint(AvlTree &T, int val)
{
	Insert(T, val);
	Print(T);
	std::cout << std::endl;
}

void DelAndPrint(AvlTree &T, int val)
{
	Delete(T, val);
	Print(T);
	std::cout << std::endl;
}

int main()
{
	AvlTree Tree=NULL;
	InsAndPrint(Tree, 1);
	InsAndPrint(Tree, 1);
	InsAndPrint(Tree, 4);
	InsAndPrint(Tree, 5);
	InsAndPrint(Tree, 1);
	InsAndPrint(Tree, 4);
	InsAndPrint(Tree, 8);
	InsAndPrint(Tree, 1);
	InsAndPrint(Tree, 0);
	InsAndPrint(Tree, 1919);
	InsAndPrint(Tree, 810);
	InsAndPrint(Tree, 114514);
	InsAndPrint(Tree, 1551);
	InsAndPrint(Tree, 6655);
	DelAndPrint(Tree, 1);
	DelAndPrint(Tree, 4);
	DelAndPrint(Tree, 1551);
	DelAndPrint(Tree, 6655);
	DelAndPrint(Tree, 114514);
	DelAndPrint(Tree, 810);
	DelAndPrint(Tree, 1919);
	DelAndPrint(Tree, 5);
	DelAndPrint(Tree, 0);
	DelAndPrint(Tree, 8);
	system("pause");
}

AvlTree MakeEmpty(AvlTree T)
{
	if (T->lTree) MakeEmpty(T->lTree);
	if (T->rTree) MakeEmpty(T->rTree);
	delete(T);
	return NULL;
}

Position Find(AvlTree T, int val)
{
	if (T == NULL)return NULL;
	if (val == T->val) return T;
	if (val < T->val)return Find(T->lTree, val);
	if (val > T->val)return Find(T->rTree, val);
}

Position FindMin(AvlTree T)
{
	if (T->lTree == NULL) return T;
	else return FindMin(T->lTree);
}

Position FindMax(AvlTree T)
{
	if (T->rTree == NULL) return T;
	else return FindMax(T->rTree);
}

int getHeight(AvlTree T)
{
	if (T == NULL) return 0;
	else return T->Height;
}

void UpdateHeight(AvlTree T)
{
	if (T == NULL)return;
	T->Height = (getHeight(T->rTree) > getHeight(T->lTree)) ? (getHeight(T->rTree) + 1) : (getHeight(T->lTree) + 1);
}

AvlTree Insert(AvlTree &T, int val)
{
	if (T == NULL)
	{
		T = new AvlNode;
		T->Height = 1;
		T->val = val;
	}
	else if (val == T->val) return T;
	else if (val < T->val) T->lTree = Insert(T->lTree, val);
	else T->rTree = Insert(T->rTree, val);
	if (abs(getHeight(T->lTree)-getHeight(T->rTree))>=2)
	{
		if (getHeight(T->lTree) > getHeight(T->rTree))
		{
			if (val > T->lTree->val) T = DoubleRotateWithLeft(T);
			else T = SingleRotateWithLeft(T);
		}
		else
		{
			if (val < T->rTree->val) T = DoubleRotateWithRight(T);
			else T = SingleRotateWithRight(T);
		}
	}
	UpdateHeight(T);
	return T;
}

AvlTree Delete(AvlTree &T, int val)
{
	if (T == NULL)return NULL;
	if (val == T->val)
	{
		AvlTree nextT;
		if (T->lTree != NULL) {
			nextT = T->lTree;
			AvlTree i;
			if (nextT->rTree == NULL) nextT->rTree = T->rTree;
			else
			{
				for (i = nextT; i->rTree->rTree; i = i->rTree);
				i->rTree = T->rTree;
			}
		}
		else nextT = T->rTree;
		delete(T);
		T = nextT;
		if (T == NULL)return NULL;
	}
	else if (val < T->val)T->lTree = Delete(T->lTree, val);
	else if (val > T->val)T->rTree = Delete(T->rTree, val);
	if (abs(getHeight(T->lTree) - getHeight(T->rTree)) >= 2)
	{
		if (getHeight(T->lTree) > getHeight(T->rTree))
		{
			if (getHeight(T->lTree->lTree) >= getHeight(T->lTree->rTree)) T = SingleRotateWithLeft(T);
			else T = DoubleRotateWithLeft(T);
		}
		else
		{
			if (getHeight(T->rTree->rTree) >= getHeight(T->rTree->lTree)) T = SingleRotateWithRight(T);
			else T = DoubleRotateWithRight(T);
		}
	}
	UpdateHeight(T);
	return T;
}

int Retrieve(Position p)
{
	return p->val;
}
 
AvlTree SingleRotateWithLeft(AvlTree T)
{
	AvlTree newT = T->lTree;
	T->lTree = newT->rTree;
	newT->rTree = T;
	return newT;
}

AvlTree SingleRotateWithRight(AvlTree T)
{
	AvlTree newT = T->rTree;
	T->rTree = newT->lTree;
	newT->lTree = T;
	return newT;
}

AvlTree DoubleRotateWithLeft(AvlTree T)
{
	T->lTree = SingleRotateWithRight(T->lTree);
	T = SingleRotateWithLeft(T);
	return T;
}

AvlTree DoubleRotateWithRight(AvlTree T)
{
	T->rTree = SingleRotateWithLeft(T->rTree);
	T = SingleRotateWithRight(T);
	return T;
}
#endif
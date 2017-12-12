#include <iostream>
#include<cstdio>
using namespace std;
struct RBNode;
typedef RBNode* RBTree;
struct RBNode
{
	bool color;//True represent red,False represent black
	RBTree L, R, P;
	int val;
	RBNode() :color(true), L(NULL), R(NULL), P(NULL), val(0) {}
};

void printTree(RBTree T)
{
	if (T == NULL)return;
	printTree(T->L);
	printf("%d ", T->val);
	printTree(T->R);
}

RBTree LeftRotate(RBTree T)
{
	RBTree newT = T->R;
	RBTree P = T->P;
	newT->P = P;
	if (P)
	{
		if (P->L == T)P->L = newT;
		else P->R = newT;
	}
	T->R = newT->L;
	if (T->R != NULL)T->R->P = T;
	newT->L = T;
	T->P = newT;
	return newT;
}

RBTree RightRotate(RBTree T)
{
	RBTree newT = T->L;
	RBTree P = T->P;
	newT->P = P;
	if (P)
	{
		if (P->L == T)P->L = newT;
		else P->R = newT;
	}
	T->L = newT->R;
	if (T->L != NULL)T->L->P = T;
	newT->R = T;
	T->P = newT;
	return newT;
}

void setColor(RBTree T, bool color)
{
	if (T != NULL)T->color = color;
}

bool getColor(RBTree T)
{
	if (T == NULL)return false;
	else return T->color;
}

void Fix(RBTree T)
{
	if (T == NULL)return;
	if (T->P == NULL)
	{
		return;
	}
	if (T->P->color == false) return;
	RBTree next = NULL;
	RBTree F = T->P, G = F->P, U = (G->L == F) ? (G->R) : (G->L);
	if (getColor(U) == true)//叔叔节点为红
	{
		setColor(F, false);
		setColor(U, false);
		setColor(G, true);
		next = G;
	}
	else if (getColor(U) == false)//叔叔节点为黑
	{
		if (F == G->L)
		{
			if (T == F->R)
			{
				next = F;
				LeftRotate(next);
			}
			else
			{
				setColor(F, false);
				setColor(G, true);
				RightRotate(G);
			}
		}
		else
		{
			if (T == F->L)
			{
				next = F;
				RightRotate(next);
			}
			else
			{
				setColor(F, false);
				setColor(G, true);
				LeftRotate(G);
			}
		}
	}
	Fix(next);
}

RBTree Insert(RBTree _T, int V)
{
	RBTree T = _T;
	if (T == NULL)
	{
		T = new RBNode;
		T->val = V;
		T->color = false;
		return T;
	}
	bool isFinished = false;
	while (!isFinished)
	{
		if (V>T->val)
		{
			if (T->R == NULL)
			{
				T->R = new RBNode;
				T->R->P = T;
				T->R->val = V;
				isFinished = true;
			}
			T = T->R;
		}
		else if (V<T->val)
		{
			if (T->L == NULL)
			{
				T->L = new RBNode;
				T->L->P = T;
				T->L->val = V;
				isFinished = true;
			}
			T = T->L;
		}
		else if (V == T->val) isFinished = true;
	}
	Fix(T);
	while (T->P != NULL)T = T->P;
	setColor(T, false);
	return T;
}

void Delete_Fix(RBTree root,RBTree F,RBTree x)
{
	//若x颜色为红：直接设成黑色
	if (getColor(x) == true)
	{
		setColor(x, false);
	}
	else
	{
		//若x颜色为黑且x不是根节点
		while ((x == NULL||getColor(x)==false) && x!=root)
		{
			RBTree v;
			if (F->L == x)//若x为父节点的左孩子
			{
				//设置兄弟节点v
				v = F->R;
				if (getColor(v) == true)//若兄弟节点为红
				{
					setColor(v, false);
					setColor(F, true);
					LeftRotate(F);
					v = F->R;
				}
				else if (getColor(v) == false)//若兄弟节点为黑
				{
					if (getColor(v->L) == false && getColor(v->R) == false)//若兄弟节点两个儿子都为黑
					{
						setColor(v, true);
						x = F;
						F = F->P;
					}
					else if (getColor(v->R) == true)//若右红
					{
						setColor(v, getColor(F));
						setColor(F, false);
						setColor(v->R, false);
						LeftRotate(F);
						x = root;
						break;
					}
					else//若左红右黑
					{
						setColor(v->L, false);
						setColor(v, true);
						RightRotate(v);
						v = F->R;
					}
				}
			}
			else
			{
				//设置兄弟节点v
				v = F->L;
				if (getColor(v) == true)//若兄弟节点为红
				{
					setColor(v, false);
					setColor(F, true);
					RightRotate(F);
					v = F->L;
				}
				else if (getColor(v) == false)//若兄弟节点为黑
				{
					if (getColor(v->L) == false && getColor(v->R) == false)//若兄弟节点两个儿子都为黑
					{
						setColor(v, true);
						x = F;
						F = F->P;
					}
					else if (getColor(v->L) == true)//若右红
					{
						setColor(v, getColor(F));
						setColor(F, false);
						setColor(v->L, false);
						LeftRotate(F);
						x = root;
						break;
					}
					else//若左红右黑
					{
						setColor(v->R, false);
						setColor(v, true);
						RightRotate(v);
						v = F->L;
					}
				}
			}
		}
		if(x)setColor(x, false);
	}
}

void Delete(RBTree& _T, int v)
{
	//若树为空则报错退出
	if (_T == NULL)
	{
		cout << "ERROR:Tree is already empty" << endl;
		return;
	}
	RBNode* curNode = _T, *fNode = NULL;
	//寻找需删除的节点
	while (true)
	{
		if (curNode == NULL)
		{
			cout << "ERROR:can't find node to delete" << endl;
			return;
		}
		if (v > curNode->val)
		{
			fNode = curNode;
			curNode = curNode->R;
		}
		else if (v < curNode->val)
		{
			fNode = curNode;
			curNode = curNode->L;
		}
		else if (v == curNode->val)break;
	}
	RBTree y = NULL, x = NULL;
	// 若被删除节点左孩子或右孩子为空，则将被删除节点赋值给y；
	if (curNode->L == NULL || curNode->R == NULL)
	{
		y = curNode;
	}
	else//否则，将被删除节点的后继节点赋值给y。
	{
		RBTree successor = curNode->R;
		if (successor->L != NULL)successor = successor->L;
		y = successor;
	}
	if (y->L != NULL)x = y->L;
	else x = y->R;
	if (x != NULL) x->P = y->P;
	if (y->P == NULL) _T = x;
	else if (y == y->P->L) y->P->L = x;
	else y->P->R = x;
	if (y != curNode) curNode->val = y->val;
	if (y->color == false) Delete_Fix(_T,y->P,x);
	delete y;
	while (_T->P != NULL)_T = _T->P;
}

int main()
{
	//插入和删除示例
	RBTree T = NULL;
	T = Insert(T, 5);
	T = Insert(T, 1);
	T = Insert(T, 4);
	T = Insert(T, 4);
	T = Insert(T, 6);
	T = Insert(T, 55);
	T = Insert(T, 214);
	T = Insert(T, 433);
	printTree(T);cout << endl;
	Delete(T, 5);
	printTree(T); cout << endl;
	Delete(T, 1);
	printTree(T); cout << endl;
	Delete(T, 6);
	printTree(T); cout << endl;
	Delete(T, 55);
	printTree(T); cout << endl;
	Delete(T, 433);
	printTree(T); cout << endl;
	Delete(T, 214);
	printTree(T); cout << endl;
	return 0;
}
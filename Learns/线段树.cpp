#include<iostream>
#include<queue>
using namespace std;
struct lineNode;
typedef lineNode* lineTree;

struct lineNode
{
	lineNode* left;
	lineNode* right;
	lineNode* father;
	int  Left, Right, val;
	lineNode() :left(NULL), right(NULL),val(0) {}
};

lineTree Build(int begin, int end,lineNode * father=NULL)
{
	lineTree root = new lineNode;
	root->Left=begin;
	root->Right = end;
	root->father = father;
	if (begin == end)
	{
		return root;
	}
	root->left = Build(begin, (begin + end) / 2, root);
	root->right = Build((begin+end)/2+1, end, root);
	return root;
}

queue<lineTree> nodes;

void printStack(queue<lineTree> nodes,int end)
{
	if (nodes.empty())return;
	cout <<"["<< nodes.front()->Left << "," << nodes.front()->Right<<","<<nodes.front()->val<<"]";
	if (nodes.front()->Right == end)
	{
		cout << endl;
	}
	if (nodes.front()->left != NULL)nodes.push(nodes.front()->left); 
	if (nodes.front()->right != NULL)nodes.push(nodes.front()->right);
	nodes.pop();
	printStack(nodes, end);
}
//更新子节点与其父节点
void UpdateTree(lineNode* node)
{
	if (node == NULL)return;//遇到头结点时退出
	lineNode* father = node->father;
	int lVal = father->left->val;
	int rVal = father->right->val;
	father->val = lVal > rVal ? lVal : rVal;
	UpdateTree(father);//递归更新父节点
}

void printTree(lineTree root)
{
	nodes.push(root);
	printStack(nodes,root->Right);
}

int main()
{
	lineTree tree = Build(1, 10);
	printTree(tree);
	//system("pause");
}
#include<iostream>
using namespace std;


struct lineNode;
typedef lineNode lineTree;

struct lineNode
{
	int left, right;
	int val;
	lineNode(int l=0, int r=0, int val=0) :left(l),
		right(r), val(val) {}
}nodeArr[800020];

void build(int pos, int l, int r, int val)
{
	nodeArr[pos] = lineNode(l, r, val);
	if (l != r)
	{
		build(pos * 2, l, (l + r) / 2, val);
		build(pos * 2 + 1, (l + r) / 2 + 1, r, val);
	}
}

void UpdateVal(int node)
{
	int fatherNode = node / 2;
	if (fatherNode == 0) { return; }
	int lVal = nodeArr[fatherNode * 2].val;
	int rVal = nodeArr[fatherNode * 2 + 1].val;
	nodeArr[fatherNode].val = lVal > rVal ? lVal : rVal;
	UpdateVal(fatherNode);
}

void UpdateNode(int node, int val)
{
	nodeArr[node].val = val;
	UpdateVal(node);
}

int findMaxValNode(int tree, int val)
{
	if (nodeArr[tree].left == nodeArr[tree].right)
	{
		UpdateNode(tree, nodeArr[tree].val - val);
		return tree;
	}
	if (val <= nodeArr[2 * tree].val)
	{
		return findMaxValNode(2 * tree, val);
	}
	else if (val <= nodeArr[2 * tree + 1].val)
	{
		return findMaxValNode(2 * tree + 1, val);
	}
	else
	{
		return 0;
	}
}

int main()
{
	int h, w, n;
	while (cin>>h>>w>>n)
	{
		if (h > 200005)h = 200005;
		build(1, 1, h, w);
		int wi;
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &wi);
			if (nodeArr[1].val < wi)printf("-1\n");
			else
			{
				int tarNode = findMaxValNode(1, wi);
				if (tarNode == 0)
				{
					printf("-1\n");
				}
				else printf("%d\n", nodeArr[tarNode].left);
			}
		}
	}
}
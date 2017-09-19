#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

struct node
{
	int to, val,rev;//去到的节点;剩余容量;nodeNet[to].rev为自身的数组编号
	node(int to, int val, int rev) :to(to), val(val), rev(rev) {}
};
int min(int a, int b)
{
	return a < b ? a : b;
}

int N, M;
vector<node> nodeNet[205];
vector<bool> passed(205,false);

//深度优先算法求当前最短路径，返回最短路径的流量
int dfs(int from,int to,int v)
{
	if (from == to)return v;
	passed[from] = true;
	for (int i = 0; i < nodeNet[from].size(); ++i)
	{
		node& tmp = nodeNet[from][i];
		if (!passed[tmp.to]&&tmp.val>0)
		{
			int d = dfs(tmp.to, to, min(v, tmp.val));
			if (d > 0)
			{
				tmp.val -= d;
				nodeNet[tmp.to][tmp.rev].val += d;
				return d;
			}
		}
	}
	return 0;
}

void addNode(int from,int to,int val)
{
	nodeNet[from].push_back(node(to,val,nodeNet[to].size()));
	nodeNet[to].push_back(node(from, 0,nodeNet[from].size()-1));
}

int getResult(int from, int to)
{
	int res = 0;
	while (true)
	{
		for (int i = 0; i < passed.size(); ++i) passed[i] = false;
		int d = dfs(from, to, 10000000);
		if (d > 0)res += d;
		else return res;
	}
}

int main()
{
	while (scanf("%d%d", &N, &M) == 2)
	{
		for (int i = 0; i <= N; ++i) nodeNet[i].clear();
		for (int i = 0; i < N; ++i)
		{
			int x, y,rate;
			scanf("%d%d%d", &x, &y,&rate);
			addNode(x, y, rate);
		}
		printf("%d\n", getResult(1, M));
	}
}
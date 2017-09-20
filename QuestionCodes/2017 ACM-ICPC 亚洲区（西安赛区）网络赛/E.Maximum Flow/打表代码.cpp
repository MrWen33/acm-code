//#include<iostream>
//#include<cstdio>
//#include<vector>
//using namespace std;
//#define LL long long
//
//struct node
//{
//	int to, val, rev;//去到的节点;剩余容量;nodeNet[to].rev为自身的数组编号
//	node(int to, int val, int rev) :to(to), val(val), rev(rev) {}
//};
//int min(int a, int b)
//{
//	return a < b ? a : b;
//}
//
//int N, M;
//vector<node> nodeNet[205];
//vector<bool> passed(205, false);
//
////深度优先算法求当前最短路径，返回最短路径的流量
//int dfs(int from, int to, int v)
//{
//	if (from == to)return v;
//	passed[from] = true;
//	for (int i = 0; i < nodeNet[from].size(); ++i)
//	{
//		node& tmp = nodeNet[from][i];
//		if (!passed[tmp.to] && tmp.val>0)
//		{
//			int d = dfs(tmp.to, to, min(v, tmp.val));
//			if (d > 0)
//			{
//				tmp.val -= d;
//				nodeNet[tmp.to][tmp.rev].val += d;
//				return d;
//			}
//		}
//	}
//	return 0;
//}
//
//void addNode(int from, int to, int val)
//{
//	nodeNet[from].push_back(node(to, val, nodeNet[to].size()));
//	nodeNet[to].push_back(node(from, 0, nodeNet[from].size() - 1));
//}
//
//int getResult(int from, int to)
//{
//	int res = 0;
//	while (true)
//	{
//		for (int i = 0; i < passed.size(); ++i) passed[i] = false;
//		int d = dfs(from, to, 10000000);
//		if (d > 0)res += d;
//		else return res;
//	}
//}
//
//int main()
//{
//	vector<int> res;
//	//while (scanf("%d", &N) == 1)
//	for(int N=2;N<51;++N)
//	{
//		for (int i = 0; i <= N; ++i) nodeNet[i].clear();
//		for (int i = 0; i < N; ++i)
//		{
//			for (int j = i+1; j < N; ++j)
//			{
//				addNode(i, j, i^j);
//			}
//		}
//		int result = getResult(0, N - 1);
//		res.push_back(result);
//		printf("%d:%d\n",N, result);
//	}
//	cout << endl;
//	for (int i = 0; i < res.size() - 1; ++i)
//	{
//		cout << i + 2 << "间隔为:" << res[i + 1] - res[i] << endl;
//	}
//	system("pause");
//}
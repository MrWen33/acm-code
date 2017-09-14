#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
double dp[1005][1001];//dp[a][b]代表通a关用b个炸弹的最大通过概率

struct level {
	int k, b;
};

double min(double a, double b)
{
	return a < b ? a : b;
}

double max(double a, double b)
{
	return a > b ? a : b;
}

double mayPoint(int k, int b, int x)
{
	return min(1, double(k*x + b) / (double)100);
}


int main()
{
	int n, m;
	scanf("%d%d",&n,&m);
	vector<level> levels(n+1);
	for (int i = 1; i <= n; ++i)
	{
		int k, b;
		scanf("%d%d", &k, &b);
		levels[i].b = b;
		levels[i].k = k;
	}
	for (int i = 0; i <= m; ++i)
	{
		dp[0][i] = 1;
	}
	for (int i = 1; i <= n; ++i)
	{
		for (int nb = 0; nb <= m; ++nb)
		{
			for (int b = nb; b <= m; ++b)
			{
				dp[i][b] = max(dp[i][b], dp[i - 1][b - nb] * mayPoint(levels[i].k, levels[i].b, nb));
			}
			if (mayPoint(levels[i].k, levels[i].b, nb) >= 1)break;
		}
	}
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= m; ++j)
		{
			cout << dp[i][j] << "\t";
		}
		cout << endl;
	}
	printf("%lf\n", dp[n][m]);
	
}
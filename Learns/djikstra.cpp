#include<iostream>
using namespace std;
#define INF 2147483647;
int val[105][105];
int N;
int S[105];
int step[105];
int previous[105];

void init()
{
	for (int i = 0; i <= N; ++i)
	{
		step[i] = INF;
	}
}

int min(int a, int b)
{
	return a < b ? a : b;
}

void djikstra(int start)
{
	step[start] = 0;
	bool hasMin = true;
	while (true)
	{
		//�ҳ�����S����·����С�ĵ�
		hasMin = false;
		int next;
		int minStep = INF;
		for (int i = 1; i <= N; ++i)
		{
			if (S[i] == false && minStep > step[i])
			{
				hasMin = true;
				minStep = step[i];
				next = i;
			}
		}
		if (!hasMin) break;
		//�������S
		S[next] = true;
		//���²���ĵ���ڽӵ�ľ���
		for (int i =1 ; i <= N; ++i)
		{
			if (val[next][i])
			{
				step[i] = min(step[i], minStep + val[next][i]);
			}
		}
	}
}

int main()
{
	cin >> N;
	int size;
	cin >> size;
	for (int i = 1; i <= size; ++i)
	{
		int a, b, v;
		cin >> a >> b >> v;
		val[a][b] = v;
		val[b][a] = v;
	}
	init();
	int start;
	cin >> start;
	djikstra(start);
	for(int i=1;i<=N;++i)
	{
		cout << step[i] << endl;
	}
	system("pause");
}
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
struct line {
	ll left, right, val;
};

ll Max(int a, int b)
{
	return a > b ? a : b;
}

int findPreV(const vector<line>& lines, int L)//找到编号为L的线段前的线段编号
{
	int i;
	for (i = L-1; i >= 0; --i)
	{
		if (lines[i].right <= lines[L].left)
		{
			break;
		}
	}
	if (i == lines.size())
	{
		return -1;
	}
	return i ;
}

int v[100005];

int main()
{
	ios::sync_with_stdio(false);
	ll n,V;
	cin >> n>>V;
	if (V == 0)
	{
		cout << n * 100 << endl;
		return 0;
	}
	vector<line> lines(n);
	for (int i = 0; i < n; ++i)
	{
		int sec;
		cin >> sec;
		lines[i].left = sec;
		lines[i].right = sec+V;
		lines[i].val = 100;
	}
	v[0] = 0;
	v[1] = lines[0].val;
	for (int i = 2; i <= n; ++i)
	{
		int lineNum = i - 1;
		int preLineNum = findPreV(lines, lineNum);
		v[i] = Max(v[i - 1], v[preLineNum + 1] + lines[lineNum].val);
	}
	cout << v[n] << endl;
	//system("pause");
}
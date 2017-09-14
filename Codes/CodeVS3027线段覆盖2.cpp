#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct line {
	int left, right, val;
};

bool lineCmp(line x, line y)
{
	return x.right < y.right;
}

int Max(int a, int b)
{
	return a > b ? a : b;
}

int findPreV(const vector<line>& lines, int L)//找到编号为L的线段前的线段编号
{
	int i;
	for (i = 0; i < lines.size(); ++i)
	{
		if (lines[i].right > lines[L].left)
		{
			break;
		}
	}
	if(i==lines.size())
	{
		return -1;
	}
	return i - 1;
}

int v[1000];

int main()
{
	int n;
	cin >> n;
	vector<line> lines(n);
	for (int i = 0; i < n; ++i)
	{
		int left, right, value;
		cin >> left >> right >> value;
		lines[i].left=left;
		lines[i].right = right;
		lines[i].val = value;
	}
	sort(lines.begin(), lines.end(), lineCmp);
	v[0] = 0;
	v[1] = lines[0].val;
	for (int i = 2; i <= n; ++i)
	{
		int lineNum = i - 1;
		int preLineNum = findPreV(lines, lineNum);
		v[i] = Max(v[i - 1], v[preLineNum + 1] + lines[lineNum].val);
	}
	cout << v[n] << endl;
}
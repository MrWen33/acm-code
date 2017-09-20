#include<iostream>
#include<cstdio>
#include<map>
#include<algorithm>
#include<cmath>
#include<vector>
#define LL long long
#define MOD 1000000007
#define MPower 65
using namespace std;
vector<pair<LL, LL> > s;


LL QPow(LL a, LL N) {
	long long r = 1, aa = a;
	while (N) {
		if (N & 1 == 1) r = (r * aa);
		N >>= 1;
		aa = (aa * aa) ;
	}
	return r;
}

int main()
{
	LL n;
	while (cin >> n)
	{
		n -= 1;
		s.push_back({ 1,0 });
		for (int i=1;;i++)
		{
			if (n >= QPow(2,i))
			{
				if (i == 1)
				{
					pair<LL, LL> p;
					p.first = QPow(2, 2*(i-1)) + 1;
					p.second = ((n - 1) / QPow(2, i -1))%MOD;
					s.push_back(p);
				}
				else
				{
					pair<LL,LL> p;
					if (i == 2)p.first = 3;
					else p.first = ( s[i-1].first*4)%MOD;
					p.second =(1+ (n-QPow(2,i))/ QPow(2, i-1 ))%MOD;

					s.push_back(p);
				}
			}
			else break;
		}
		LL result = 1;
		for (int i = 0; i < s.size(); ++i)
		{
			result += (s[i].first*s[i].second);
			result %= MOD;
		}
		cout << result << endl;
		s.clear();
	}
	//system("pause");
}
#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;
void Fact(int n, int opt, vector<int> primes, vector<int>& fact);
void addFact(int n, int opt, vector<int> primes, vector<int>& fact);
int main()
{
	int p, q, r, s;
	while (cin >> p >> q >> r >> s)
	{
		vector<int> nums(10001, 1);
		vector<int> primes(1);
		for (int i = 2; i <= 10000; ++i)
		{
			if (nums[i] == 1)
			{
				primes.push_back(i);
				for (int i1 = 1; i*i1 < 10000; ++i1)
				{
					nums[i*i1] = 0;
				}
			}
		}
		vector<int> fact(primes.size(), 0);
		addFact(p, 1, primes, fact);
		addFact(q, -1, primes, fact);
		addFact(p - q, -1, primes, fact);
		addFact(r, -1, primes, fact);
		addFact(s, 1, primes, fact);
		addFact(r - s, 1, primes, fact);
		double answer = 1;
		for (int i = 1; i < fact.size(); ++i)
		{
			if (fact[i] != 0)
			{
				answer *= pow(primes[i], fact[i]);
			}
		}
		printf("%.5lf\n", answer);
	}
	return 0;
}

void Fact(int n,int opt,vector<int> primes,vector<int>& fact)
{
	for (int i = 1; i < primes.size(); ++i)
	{
		while (!(n%primes[i]))
		{
			n = n / primes[i];
			fact[i]+=opt;
		}
		if (n == 1)
		{
			break;
		}
	}
}

void addFact(int n, int opt, vector<int> primes, vector<int>& fact)
{
	for (int i = 1; i <= n; ++i)
	{
		Fact(i, opt, primes, fact);
	}
}
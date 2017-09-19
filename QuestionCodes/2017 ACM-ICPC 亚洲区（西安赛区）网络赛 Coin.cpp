#include<iostream>
const int mod=1000000007;
using namespace std;

int power(int a, int N) {
	long long r = 1, aa = a;
	while (N) {
		if (N & 1 == 1) r = (r * aa) % mod;
		N >>= 1;
		aa = (aa * aa) % mod;
	}
	return r;
}


int gcd(int a, int b, int &x, int &y)
{
	if (b == 0) 
	{
		x = 1, y = 0;
		return a; 
	}
	int GCD=gcd(b, a%b, x, y);
	int x2 = x, y2 = y;
	x = y2;
	y = x2 - (a / b)*y2;
	return GCD;
}

int main()
{
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		int p, q, k;
		cin >> p >> q >> k;
		int a = (2 * power(p, k)) % mod;
		int x = 0, y = 0;
		gcd(a, mod, x, y);
		while (x < 0)x += mod;
		cout << (long long)(x*(long long)(power(p, k) + power(p - 2 * q, k))%mod) % mod << endl;
	}
}
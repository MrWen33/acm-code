#include<iostream>
#include<cmath>
#include<vector>
#include<cstdio>
using namespace std;
int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	vector<int> a(n+1),sum(n+1),sum2(n+1);
	for (int i = 1; i <= n; ++i)
	{
		int A;
		scanf("%d",&A);
		a[i] = A;
	}
	for (int i = 1; i <= n; ++i)
	{
		sum[i] = sum[i - 1] + a[i];
		sum2[i] = sum2[i - 1] + a[i] * a[i];
	}
	for (int i = 0; i < q; ++i)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		double ave = (double)(sum[r] - sum[l - 1]) / (r - l + 1);
		double ave2= (double)(sum2[r] - sum2[l - 1]) / (r - l + 1);
		double sigma = sqrt(ave2 - ave*ave);
		double result = -(double)75 / 70 * sigma + ave;
		printf("%lf\n", result);
	}
	//system("pause");

}
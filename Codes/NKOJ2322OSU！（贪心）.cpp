#include<iostream>
using namespace std;
#define ll long long

int main()
{
	int n,v,result=0;
	cin>>n>>v;
	ll nt=-100;
	for(int i=0;i<n;++i)
	{
		ll tempT;
		cin>>tempT;
		if(tempT-nt>=v)
		{
			nt=tempT;
			++result;
		}
	}
	cout<<result*100<<endl;
}
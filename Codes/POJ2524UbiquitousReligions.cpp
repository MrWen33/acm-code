#include <iostream>
using namespace std;
int parent[50005];
int findSource(int s)
{
    return parent[s]==s?s:findSource(parent[s]);
}
int main()
{
    ios::sync_with_stdio(false);
    int n,m,CASE=0;
    while(cin>>n>>m)
    {
        CASE++;
        if(n==0&&m==0)
        {
            return 0;
        }
        int s1,s2;
        for(int i=0;i<50005;++i)
        {
            parent[i]=i;
        }
        while(m--)
        {
            cin>>s1>>s2;
            if(findSource(s1)!=findSource(s2))
            {
                parent[findSource(s2)]=findSource(s1);
                n--;
            }
        }
        cout<<"Case "<<CASE<<": "<<n<<endl;
    }
    return 0;
}
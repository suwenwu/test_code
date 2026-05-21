#include<bits/stdc++.h>
using namespace std;
long long n,k;
int main()
{
    cin>>n>>k;
     long long tmp = n/k;
    if(k%2==1)
    {
        cout<<tmp*tmp*tmp;
    }
    long long tmp2 = (n+k/2)/k;
    if(k%2==0)
    {
        cout<<tmp*tmp*tmp + tmp2*tmp2*tmp2;
    }
    return 0;
}
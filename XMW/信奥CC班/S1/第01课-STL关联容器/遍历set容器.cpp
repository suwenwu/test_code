#include<bits/stdc++.h>
using namespace std;
set<int> s; 
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
                s.insert(x);
	}
	for(auto i:s) cout<<i<<"\n";
	return 0;
}
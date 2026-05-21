#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n;

int main()
{
    cin >> n;
    if (n & 1)
        cout << 2 * n;
    else
        cout << n;
    return 0;
}
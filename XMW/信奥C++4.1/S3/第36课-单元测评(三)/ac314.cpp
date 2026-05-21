#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a, b;
    cin >> a >> b;

    if (a.size() > b.size())
        cout << a;
    else if (a.size() < b.size())
        cout << b;
    else
        cout << max(a, b);
    return 0;
}
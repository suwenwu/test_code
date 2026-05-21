#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    if (a == 3 && b == 1 || a == 1 && b == 3 || a == 3 && b == 3 || a == 1 && b == 1)
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}
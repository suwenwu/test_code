#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n & 1)
        cout << (n / 2) * (n / 2 + 1);
    else
        cout << pow(n / 2, 2);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int a[11], cnt, idx1, idx2;

int main()
{
    int n;
    cin >> n;
    while (n)
    {
        a[++cnt] = n % 2;
        n /= 2;
    }
    for (int i = 1; i <= cnt; i++)
    {
        if (a[i] == 1)
        {
            idx1 = i;
            break;
        }
    }
    for (int i = cnt; i >= 1; i--)
    {
        if (a[i] == 1)
        {
            idx2 = i;
            break;
        }
    }
    cout << idx2 - idx1;
    return 0;
}

#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;

int n, max_num = INT_MIN, min_num = INT_MAX, num;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> num;
        if (num > max_num)
            max_num = num;
        if (num < min_num)
            min_num = num;
    }
    cout << max_num - min_num;
    return 0;
}
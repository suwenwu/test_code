#include <bits/stdc++.h>
using namespace std;
int arr[10005];
bool cmp(int x, int y)
{
    return x < y; // 升序排列
}
int main()
{
    int n, l, r;
    cin >> n >> l >> r;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    sort(arr + l, arr + r + 1, cmp);
    // l到r
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
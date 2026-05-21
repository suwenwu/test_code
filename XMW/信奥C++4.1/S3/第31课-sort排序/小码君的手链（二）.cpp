#include <bits/stdc++.h>
using namespace std;
int arr[10005];
bool cmp1(int a, int b)
{
    return a > b;
}
bool cmp2(int a, int b)
{
    return a < b;
}
int main()
{
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    sort(arr + a, arr + b + 1, cmp1);
    sort(arr + b + 1, arr + c + 1, cmp2);
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
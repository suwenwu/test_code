#include <bits/stdc++.h>
using namespace std;
char arr[10010];
bool cmp(char left, char right)
{
    return left > right;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    sort(arr + 1, arr + n + 1, cmp);
    // sort(arr+1,arr+n+1,greater<char>());
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}

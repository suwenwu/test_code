#include <bits/stdc++.h>

using namespace std;

int n, x, a[100005];

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}


int main()
{
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        a[i] = a[i] - x;
    }
    int ans = a[1];
    for (int i = 2; i <= n; i++)
        ans = gcd(ans, a[i]);
    printf("%d\n", abs(ans)); 
    return 0;
}
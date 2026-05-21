#include <bits/stdc++.h>

using namespace std;

int n, a[100005], res;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == i)
        {
            res++;
            swap(a[i], a[i + 1]);
        }
    }
    printf("%d\n", res);
    return 0;
}
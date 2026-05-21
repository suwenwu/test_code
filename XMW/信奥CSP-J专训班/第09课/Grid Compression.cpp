#include <bits/stdc++.h>

using namespace std;

int n, m;
char c[105][105];
bool col[105], row[105];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf(" %c", &c[i][j]);
            if (c[i][j] == '#')
                col[i] = row[j] = true;
        }
    for (int i = 1; i <= n; i++)
        if (col[i])
        {
            for (int j = 1; j <= m; j++)
            {
                if (row[j])
                    printf("%c", c[i][j]);
            }
            printf("\n");
        }
    return 0;
}
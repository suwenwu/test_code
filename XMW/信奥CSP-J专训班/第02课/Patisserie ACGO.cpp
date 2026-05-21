#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1005
int n, m;
ll a[N], b[N], c[N], ans, h[N];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
    for (int i = -1; i <= 1; i += 2)
        for (int j = -1; j <= 1; j += 2)
            for (int k = -1; k <= 1; k += 2)
            {
                for (int l = 1; l <= n; l++)
                    h[l] = i * a[l] + j * b[l] + k * c[l]; // 计算每一行在当前符号下的值
                sort(h + 1, h + n + 1, greater<ll>());
                ll res = 0;
                for (int l = 1; l <= m; l++)
                    res += h[l];     // 选m个值
                ans = max(res, ans); // 求最大值
            }
    printf("%lld", ans);
    return 0;
}

// 方法二
#include <bits/stdc++.h>
#define ll long long
using namespace std;

// 111 110  000 pos

/*
dp[i][j][k] : 前i种蛋糕取j中蛋糕所产生的最大价值
dp[i][j][k] = dp[i-1][j][k]
dp[i][j][k] = dp[i-1][j-1][k] + pos
111
k&1
k&2
k&4
*/

ll a[1005],b[1005],c[1005];
int n,m;
ll dp[1005][1005][8],ans = LLONG_MIN;

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);
    memset(dp,-127,sizeof(dp)); // 负无穷
    for(int i=0;i<8;i++)
        dp[0][0][i] = 0; // 初始化状态
    for(int i=1;i<=n;i++)
        for(int j=m;j>=0;j--)
            for(int k=0;k<8;k++)
                if(j)
                    dp[i][j][k] = max(dp[i-1][j][k],dp[i-1][j-1][k] + (k&1?1:-1)*a[i] + (k&2?1:-1)*b[i]+(k&4?1:-1)*c[i]);
                else
                    dp[i][j][k] = dp[i-1][j][k];
    for(int i=0;i<8;i++)
        ans = max(ans,dp[n][m][i]);
    printf("%lld",ans);
    return 0;
}

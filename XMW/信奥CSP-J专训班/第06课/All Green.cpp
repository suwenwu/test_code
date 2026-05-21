/*
 *  @date: 2026-04-10 13:24:41  星期五
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: All Green.cpp
 */
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;
int d, p[20], c[20], dp[10005]; // dp[j] 表示做了j题的最大得分
int g, ans;                     // ans 表示题目的总数
int main()
{
    scanf("%d%d", &d, &g);
    for (int i = 1; i <= d; ++i)
    {
        scanf("%d%d", &p[i], &c[i]);
        ans += p[i];
    }

    for (int i = 1; i <= d; i++)                    // 枚举每一套题目
        for (int j = ans; j >= 0; j--)              // 枚举已经做的题目数
            for (int k = min(p[i], j); k >= 0; k--) // 枚举这一套题目做的题数
                dp[j] = max(dp[j], dp[j - k] + k * i * 100 + (k == p[i] ? c[i] : 0));

    // 暴力枚举做的题目数，如果比目标值大，则输出
    for (int i = 0; i <= ans; ++i)
        if (dp[i] >= g)
        {
            printf("%d\n", i);
            break;
        }
    return 0;
}

/*
#include <bits/stdc++.h>

#define endl "\n"
#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
using namespace std;
int d, p[20], c[20]; // d表示套数，p表示每套题目的数量，c表示做完p题额外获取的分数
int g, ans;          // ans 表示题目的总数

void dfs(int x, int cnt, int sum)
{
    if (cnt > ans) // 剪枝1，如果当前已经做的题数大于答案，则返回
        return;
    if (x > d) // 如果做完d套题目，则返回
    {
        if (sum >= g)
            ans = min(ans, cnt);
        return;
    }
    for (int i = 0; i <= p[x]; ++i)
        dfs(x + 1, cnt + i, sum + i * 100 * x + (i == p[x] ? c[x] : 0)); // 做i题，得分i*100*x，如果做完p[x]题，则额外加c[x]分
}

int main()
{
    scanf("%d%d", &d, &g);
    for (int i = 1; i <= d; ++i)
        scanf("%d%d", &p[i], &c[i]), ans += p[i];
    dfs(1, 0, 0);
    printf("%d\n", ans);
    return 0;
}
*/
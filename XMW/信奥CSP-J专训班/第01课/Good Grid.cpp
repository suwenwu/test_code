#include <bits/stdc++.h>

using namespace std;

int N, C;
int d[35][35], color; // d[i][j] 是将颜色i改为颜色j所需要花费的代价
int dp[3][35]; // dp[s][k] 将(i,j)坐标(i+j)%3 = s 集合全部改成 k 的颜色所需要花费的总代价
int ans = INT_MAX;

int main()
{
	scanf("%d%d", &N, &C);
	for (int i = 1; i <= C; i++)
		for (int j = 1; j <= C; j++)
			scanf("%d", &d[i][j]);
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			scanf("%d", &color);
			int s = (i + j) % 3;
			for (int k = 1; k <= C; k++)
				dp[s][k] += d[color][k];
		}
	}
	for (int i = 1; i <= C; i++)
		for (int j = 1; j <= C; j++)
			for (int k = 1; k <= C; k++)
				if (i != j && i != k && j != k)
					ans = min(ans, dp[0][i] + dp[1][j] + dp[2][k]);
	printf("%d", ans);
	return 0;
}
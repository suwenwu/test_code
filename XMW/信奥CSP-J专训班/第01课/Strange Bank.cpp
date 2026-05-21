#include <bits/stdc++.h>

using namespace std;

int n;
int v[100005], cnt;
int dp[100005];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i *= 6)
		v[++cnt] = i;
	for (int i = 1; i <= n; i *= 9)
		v[++cnt] = i;

	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= cnt; i++)
		for (int j = v[i]; j <= n; j++)
			dp[j] = min(dp[j], dp[j - v[i]] + 1);
	printf("%d", dp[n]);
	return 0;
}
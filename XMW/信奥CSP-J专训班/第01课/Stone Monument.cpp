#include <bits/stdc++.h>

using namespace std;

int a, b, sum;

int main()
{
	scanf("%d%d", &a, &b);
	printf("%d\n", (1+b-a)*(b-a)/2 - b);
	return 0;
}
/*
 *  @date: 2026-05-03 18:59:01  星期天
 *  @description: Copyright (cpp) 2026 by Ly_boy, All Rights Reserved.
 *  @file: 左邻右舍.cpp
 */
#include <bits/stdc++.h>

#define debug freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout)
#define endl "\n"
#define N 200005
#define ll long long

using namespace std;

int n,x;

int main()
{
    scanf("%d%d",&n,&x);
    if(x == 1)
        printf("%d %d",2,n);
    else if(x == n)
        printf("%d %d",1,n-1);
    else
        printf("%d %d",x-1,x+1);
    return 0;
}
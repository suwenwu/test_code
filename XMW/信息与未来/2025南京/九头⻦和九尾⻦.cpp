#include <bits/stdc++.h>
using namespace std;
int main()
{
    int head, feet;
    cin >> head >> feet;
    int ans;
    ans = (head - (head + feet) / 10) / 8;
    cout << ans << endl;
    return 0;
}
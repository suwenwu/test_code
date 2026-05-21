#include <bits/stdc++.h>
using namespace std;
multimap<string, int> studentScores;
multimap<string, int>::iterator it;
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        char ch;
        string s;
        int x;
        cin >> ch >> s;
        if (ch == 'S')
        {
            cin >> x;
            studentScores.insert(make_pair(s, x));
        }
        else
        {
            pair<multimap<string, int>::iterator, multimap<string, int>::iterator> range;
            range = studentScores.equal_range(s); // 查找当前这个名字
            long long ans = 0;                    // 统计当前人名借书总数
            for (it = range.first; it != range.second; ++it)
            {
                ans += it->second;
            }
            cout << ans << endl;
        }
    }
    for (it = studentScores.begin(); it != studentScores.end(); ++it)
    {
        cout << it->first << " " << it->second << endl;
    }
    return 0;
}
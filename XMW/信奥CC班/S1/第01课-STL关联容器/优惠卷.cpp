#include <bits/stdc++.h>
using namespace std;
int In[110000], Out[110000];
set<int> s;
int main()
{
    int m, sum = 0;
    cin >> m;
    for (int i = 1, x; i <= m; i++)
    {
        char opt;
        cin >> opt;
        // 储存非法记录的出现时间
        if (opt == '?')
            s.insert(i);
        else
        {
            cin >> x;
            if (opt == 'I')
            {
                if (In[x])
                { // 如果当前这个人存在大楼里面
                    // 如果上次进时候比最晚未知记录还早那么不可能
                    // 在未知记录中找一下是否可以抵消当前这个人之前出来的记录
                    auto it = s.upper_bound(In[x]);
                    if (it == s.end())
                    {              // 在未知记录找不到说明是非法的
                        cout << i; // 当前这个出来的记录是非法
                        return 0;
                    }
                    s.erase(it); // 删除当前已经使用的非法记录
                }
                In[x] = i;  // 将当前这个人在i的时间内进入大楼压入
                Out[x] = 0; // 并且将当前这个人出大楼标记为空
            }
            else
            {
                // 本来就不在大楼
                if (!In[x])
                {
                    // 不在大楼，但是现在出大楼了，也是一样查看能否有非法记录抵消
                    auto it = s.upper_bound(Out[x]);
                    if (it == s.end())
                    {
                        cout << i;
                        return 0;
                    }
                    s.erase(it);
                }
                In[x] = 0;
                Out[x] = i;
            }
        }
    }
    cout << "-1" << endl;
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

string s, s1;
unordered_set<string> st;
int n;

int main()
{
    cin >> n >> s1 >> s;
    if (s == s1 || s[0] != s1[s1.size() - 1])
    {
        cout << "No\n";
        return 0;
    }
    st.insert(s);
    st.insert(s1);
    for (int i = 3; i <= n; i++)
    {
        s1 = s;
        cin >> s;
        if (st.count(s) || s[0] != s1[s1.size() - 1])
        {
            cout << "No\n";
            return 0;
        }
        st.insert(s);
    }
    cout << "Yes\n";
    return 0;
}
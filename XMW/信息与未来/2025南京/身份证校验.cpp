#include <iostream>
#include <string>
using namespace std;
int days_in_month(int y, int m)
{
    if (m == 1 || m == 3 || m == 5 || m == 7 ||
        m == 8 || m == 10 || m == 12)
        return 31;
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return 30;
    // ⼆⽉
    bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    return leap ? 29 : 28;
}
bool check_date(int y, int m, int d)
{
    if (y < 1900 || y > 2025)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > days_in_month(y, m))
        return false;
    // 上界：2025-05-10
    if (y == 2025)
    {
        if (m > 5)
            return false;
        if (m == 5 && d > 10)
            return false;
    }
    return true;
}
bool check_id(string s)
{
    int a[19];
    for (int i = 0; i < 18; i++)
    {
        if (s[i] == 'X')
            a[i + 1] = 10;
        else
            a[i + 1] = s[i] - '0';
    }
    // 校验位计算
    int sum = 0;
    int p = 1; // 2^0
    for (int i = 18; i >= 1; i--)
    {
        sum = (sum + a[i] * p) % 11;
        p = (p * 2) % 11;
    }
    if (sum != 1)
        return false;
    // 解析⽇期
    int y = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
    int m = (s[10] - '0') * 10 + (s[11] - '0');
    int d = (s[12] - '0') * 10 + (s[13] - '0');
    return check_date(y, m, d);
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string s;
        cin >> s;
        if (check_id(s))
            cout << "PASS\n";
        else
            cout << "FAIL\n";
    }
    return 0;
}
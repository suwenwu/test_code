#include <bits/stdc++.h>
#define maxn 10005
using namespace std;

int fa[maxn]; // fa[x] 表示 x 的父节点（"父亲"数组）
int n, m;     // n: 元素个数，m: 操作次数
int z, x, y;

// 查找函数：返回 x 所在集合的根节点（"代表元"）
// 使用了路径压缩优化 —— 查找过程中将沿途所有节点直接指向根
int get(int x)
{
    if (fa[x] == x) // 如果 x 就是根节点
        return x;
    return fa[x] = get(fa[x]); // 递归找根，并将 x 的父节点设为根（路径压缩）
}

// 合并函数：将 x 所在集合合并到 y 所在集合
void merge(int x, int y)
{
    int fx = get(x), fy = get(y); // 找到 x 和 y 的根节点
    if (fx != fy)                 // 如果 x 和 y 不在同一个集合中
        fa[fx] = fy;              // 将 x 的根节点指向 y 的根节点，实现合并
}

int main()
{
    scanf("%d%d", &n, &m);
    // 初始化：每个元素自成一个集合，自己的父亲就是自己
    for (int i = 1; i <= n; i++)
        fa[i] = i;

    while (m--) // 依次处理 m 个操作
    {
        scanf("%d%d%d", &z, &x, &y);                      // 读取操作类型 z 和元素 x, y
        if (z == 1)                                       // 操作 1：合并操作
            merge(x, y);                                  // 则将它们合并
        else                                              // 操作 2：查询操作
            printf("%s\n", get(x) == get(y) ? "Y" : "N"); // 如果 x 和 y 在同一集合
    }
    return 0;
}
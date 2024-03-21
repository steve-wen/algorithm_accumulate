#include <bits/stdc++.h>

using namespace std;

/**
* 树形 dp
*/

/**
*   换根 dp 模板
*   lc.no.834 : 树中距离之和
*   换根 ： 相邻节点换根
*   先考虑一个节点 0,祖先 -1，并得到 ans[0]; 然后 从 0 开始交换相邻节点, 因为 ans[相邻节点] 之间最多相差 1; reroot 换根
*   时间复杂度 O(n)
*/
vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& e) {
    vector<vector<int>> g(n);
    vector<int> sz(n,1); // sz 数组记录该节点的子树的节点总数(包含该节点)
    for (auto &e1: e) {
        int x = e1[0], y = e1[1];
        g[x].push_back(y);
        g[y].push_back(x); // 建图
    }
    vector<int> ans(n);
    function<void(int, int, int)> dfs = [&](int x, int fa, int d) {
        for (auto y: g[x])
            if (y != fa) {
                ans[0] += d; // 计数, d : 深度
                dfs(y, x, d+1);
                sz[x] += sz[y];
            }
    };
    dfs(0, -1, 1);
    function<void(int, int)> reroot = [&](int x, int fa) { // 换根
        for (auto y: g[x])
            if (y != fa) {
                ans[y] = ans[x] + n - 2*sz[y]; // 根据题目要求推公式
                reroot(y, x); // 互换根节点
            }
    };
    reroot(0, -1);
    return ans;
}

// lc.no.2858 : 可以到达每一个节点的最少边反转次数
vector<int> minEdgeReversals(int n, vector<vector<int>>& e) {
    vector<vector<pair<int,int>>> g(n);
    for (auto &e1: e) {
        int x = e1[0], y = e1[1];
        g[x].emplace_back(y,1); // 注意 emplace
        g[y].emplace_back(x,-1); // 建图
    }
    vector<int> ans(n);
    function<void(int, int)> dfs = [&](int x, int fa) {
        for (auto [y,dir]: g[x])
            if (y != fa) {
                ans[0] += dir < 0; // 计数
                dfs(y, x);
            }
    };
    dfs(0, -1);

    function<void(int, int)> reroot = [&](int x, int fa) {
        for (auto [y,dir]: g[x])
            if (y != fa) {
                ans[y] = ans[x]+dir;
                reroot(y, x); // 互换根节点
            }
    };
    reroot(0, -1);
    return ans;
}

// lc.no.2581 : 统计可能的树根数目
int rootCount(vector<vector<int>> &e, vector<vector<int>> &guesses, int k) {
    vector<vector<int>> g(e.size() + 1);
    for (auto &e1: e) {
        int x = e1[0], y = e1[1];
        g[x].push_back(y);
        g[y].push_back(x); // 建图
    }

    set<pair<int,int>> s;
    for (auto &e1: guesses) // guesses 转成哈希表
        s.insert(pair<int,int>(e1[0],e1[1]));

    int ans = 0, cnt0 = 0;
    function<void(int, int)> dfs = [&](int x, int fa) {
        for (int y: g[x])
            if (y != fa) {
                cnt0 += s.count(pair<int,int>(x,y)); // 以 0 为根时，猜对了
                dfs(y, x);
            }
    };
    dfs(0, -1);

    function<void(int, int, int)> reroot = [&](int x, int fa, int cnt) {
        ans += cnt >= k; // 此时 cnt 就是以 x 为根时的猜对次数
        for (int y: g[x])
            if (y != fa) {
                reroot(y, x, cnt- s.count(pair<int,int>(x,y)) + s.count(pair<int,int>(y,x))); // 原来是对的，现在错了 原来是错的，现在对了
                // 互换根节点
            }
    };
    reroot(0, -1, cnt0);
    return ans;
}

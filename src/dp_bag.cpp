#include <bits/stdc++.h>

using namespace std;

/**
*  背包 dp
 * 子序列 dp 的思考套路
 * 1. 0-1 背包， 选的子序列的相邻元素是无关的 [相邻无关]
 * 2. LIS(最长上升子序列) 选的子序列的相邻元素是相关的 [相邻相关]
 *
*/

/**
 * 0-1 背包 模板代码
 * c : 背包容量
 * w[i] : 第 i 个物品的体积
 * v[i] : 第 i 个物品的价值
 * 返回: 所选物品体积不超过 c 的前提下, 所能得到的最大价值和
 */

int zero_one_bag(int c, vector<int> w, vector<int> v){
    int n = w.size();
    int memo[1001][1001];
    function<int(int,int)> dfs = [&](int i, int j){
        if (i < 0) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        if (w[i] > j) {
            res = dfs(i-1,j);
        } else {
            res = max(dfs(i-1,j), dfs(i-1,j-w[i])+v[i]);
        }
        return res;
    };
    return dfs(n-1,c);
}

/**
 * 贡献法 + 二维 0-1 背包
 * 贡献法 : 考虑单个/每个元素的贡献；然后累加贡献
 * 二维 0-1 背包 ： 有两个约束条件 ： 1，背包容量 2，选取的物品数量
 * 时间复杂度: O(n^3)
 * https://leetcode.cn/problems/find-the-sum-of-the-power-of-all-subsequences/description/
 * @param a
 * @param k
 * @return
 */

const int MOD = 1'000'000'007;
const int MX = 100'000; // C(n,k) n

// 快速幂取 MOD
long long q_pow_2(long long x, int n) {
    long long res = 1;
    for (; n > 0; n /= 2) {
        if (n % 2) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

int sumOfPower(vector<int>& a, int k) {
    int n = a.size();
    long long memo[100][100][100];
    memset(memo,-1,sizeof(memo));
    // i 表示 0 - n-1；j 表示 容量为 j; l 表示选取的物品数量/数组长度 为 l
    // f[i][j][l] 表示 从 0 - n-1, 恰好选出 l 个数 且 和为 j 的方案数
    function<long long (int,int,int)> dfs = [&](int i, int j, int l){
        if (l < 0) return (long long)0;
        if (i < 0) {
            if (j == 0 && l == 0) return (long long)1;
            return (long long)0;
        }
        if (memo[i][j][l] != -1) return memo[i][j][l];
        long long& res = memo[i][j][l];
        res = 0;
        if (a[i] > j) {
            res = (res+dfs(i-1,j,l))%MOD;
        } else {
            res = (res+dfs(i-1,j,l))%MOD;
            res = (res +dfs(i-1,j-a[i],l-1))%MOD;
        }
        return res;
    };

    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        long long cnt = dfs(n-1,k,i);
        ans = (ans+ cnt * q_pow_2(2,n-i))%MOD;
    }
    return ans;
}

/**
 * 完全 背包 模板代码
 * c : 背包容量
 * w[i] : 第 i 个物品的体积
 * v[i] : 第 i 个物品的价值
 * 每种物品可以无限次重复选
 * 返回: 所选物品体积不超过 c 的前提下, 所能得到的最大价值和
 */

int unbounded_bag(int c, vector<int> w, vector<int> v){
    int n = w.size();
    int memo[1001][1001];
    function<int(int,int)> dfs = [&](int i, int j){
        if (i < 0) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        if (w[i] > j) {
            res = dfs(i-1,j);
        } else {
            res = max(dfs(i-1,j), dfs(i,j-w[i])+v[i]);
        }
        return res;
    };
    return dfs(n-1,c);
}

/**
 * 分组背包
 * t : 背包容量
 * a[i][0] : 第 i 种物品的数量
 * a[i][1] : 第 i 种物品的单价
 * 每种物品可以在数量范围内选
 * 返回: 所选物品价值恰好等于 t 的前提下, 所能得到的方案数
 * https://leetcode.cn/problems/number-of-ways-to-earn-points/description/
 * @param t
 * @param a
 * @return
 */
int waysToReachTarget(int t, vector<vector<int>>& a) {
    int n = a.size(), mod = (int)1e9 + 7;
    int memo[51][1001];
    memset(memo,-1,sizeof(memo));
    function<int(int, int)> dfs = [&](int i, int j){
        if (i < 0) {
            if (j == 0) return 1;
            else return 0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = 0;
        int a1 = a[i][0], a2 = a[i][1];
        for (int k = 0; k <= min(a1, j/a2); ++k) {
            res = (res + dfs(i-1,j-k*a2) % mod) % mod;
        }
        return res;
    };
    return dfs(n-1,t);
}

/**
 * 分组背包
 * https://leetcode.cn/problems/minimize-the-difference-between-target-and-chosen-elements/description/
 * @param a
 * @param t
 * @return
 */
int minimizeTheDifference(vector<vector<int>>& a, int t) {
    int m = a.size(), n = a[0].size();
    int mn = 0, mx = 0;
    for (int i = 0; i < m; ++i) {
        sort(a[i].begin(), a[i].end());
    }
    for (int i = 0; i < m; ++i) {
        mn += a[i][0];
        mx += a[i][n-1];
    }
    int memo[71][5000];
    memset(memo,-1, sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j) {
        if (i < 0) {
            if (j == 0) return 1;
            return 0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = 0;
        for (int k = 0; k < n; ++k) {
            if (j-a[i][k] >= 0) {
                res = max(res,dfs(i-1,j-a[i][k]));
            }
        }
        return res;
    };
    if (mx <= t) return t-mx; // 注意特判,减少部分时间
    if (mn >= t) return mn -t;
    int ans = 4900;
    for (int i = t; i >=mn; --i) {
        if (dfs(m-1,i) == 1) {
            ans = t-i;
            break;
        }
    }
    for (int i = t+1; i <= mx; ++i) {
        if (dfs(m-1,i) == 1) {
            ans = min(ans,i-t);
            break;
        }
    }
    return ans;
}

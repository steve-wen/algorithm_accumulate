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



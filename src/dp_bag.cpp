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


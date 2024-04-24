#include <bits/stdc++.h>

using namespace std;

/**
*  区间 dp
*  要解决的问题都是一段连续子数组的最多操作次数
*  子问题是 [从两侧向内缩小的] -> 区间 dp
*  dfs(i,j) = 操作 a[i] ... a[j] 这一段子数组(闭区间 [i,j]) 的最多可以进行的操作次数
*/

/**
 * dfs 外面再包一层 lambda 函数 check (技巧)
 * https://leetcode.cn/problems/maximum-number-of-operations-with-the-same-score-ii/description/
 * @param a
 * @return
 */
int maxOperations(vector<int>& a) {
    int n = a.size();
    int b1 = a[0]+a[1], b2 = a[0]+a[n-1], b3 = a[n-2]+a[n-1];

    function<int(int,int,int)> check = [&](int i1, int j1, int k) {
        int memo[(int)1e3][(int)1e3];
        memset(memo,-1,sizeof(memo));
        function<int(int,int)> dfs = [&](int i, int j){
            if (abs((j-i)) < 1 || i >= j) return 0;
            if (memo[i][j] != -1) return memo[i][j];
            int& res = memo[i][j];
            res = 0;
            if (a[i] + a[i+1] == k) {
                res = 1+dfs(i+2,j);
            }
            if (a[i] + a[j] == k) {
                res = max(res, 1+dfs(i+1,j-1));
            }
            if (a[j-1]+a[j] == k) {
                res = max(res, 1+dfs(i,j-2));
            }
            return res;
        };
        return dfs(i1,j1);
    };

    int ans = 0;
    ans = max(1+check(2,n-1,b1), max(1+check(1,n-2,b2),1+check(0,n-3,b3)));
    return ans;
}

/**
 * 朴素区间 dp + 记忆化 (O(n^2) 的写法需要转换为 dp 在遍历的时候更新状态？
 * 时间复杂度 O(n^3)
 * https://leetcode.cn/problems/stone-game-v/solutions/386111/di-gui-ji-yi-hua-by-time-limit/
 * @param a
 * @return
 */
int stoneGameV(vector<int>& a) {
    int n = a.size();
    vector<int> s(n+1);
    for (int i = 0; i < n; ++i) {
        s[i+1] += s[i]+a[i];
    }
    int memo[501][501];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i,int j){
        if (j-i <= 0) {
            return 0;
        }
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        int& res = memo[i][j];
        for (int k = i; k <= j; ++k) {
            if (s[k+1]-s[i] <= s[j+1]-s[k+1]) {
                res = max(res, dfs(i,k)+s[k+1]-s[i]);
            }
            if (s[k+1]-s[i] >= s[j+1]-s[k+1]) {
                res = max(res, dfs(k+1,j)+s[j+1]-s[k+1]);
            }
        }
        return res;
    };
    return dfs(0,n-1);
}

/**
 * 区间 dp ： 不断 缩小/压缩 区间范围
 * https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/solutions/367265/dong-tai-gui-hua-di-gui-ji-yi-hua-sou-suo-by-time-/
 * @param n
 * @param a
 * @return
 */
int minCost(int n, vector<int>& a) {
    a.emplace_back(0);
    a.emplace_back(n);
    sort(a.begin(),a.end());
    int m = a.size();
    int memo[103][103];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j){
        if (i+1 >= j) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = 1e9;
        for (int k = i+1; k < j; ++k) {
            res = min(res,dfs(i,k)+dfs(k,j)+a[j]-a[i]);
        }
        return res;
    };
    return dfs(0,m-1);
}

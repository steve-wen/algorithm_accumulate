#include <bits/stdc++.h>

using namespace std;
#define ll long long

/**
*  优化 + dp
*
*/


/**
 * 最长递增子序列 LIS + 贪心构造 g 数组 + 二分
 * 优化 + dp
 * https://leetcode.cn/problems/minimum-operations-to-make-a-subsequence/solutions/896862/gong-shui-san-xie-noxiang-xin-ke-xue-xi-oj7yu/
 * @param t
 * @param a
 * @return
 */
int minOperations(vector<int>& t, vector<int>& a) {
    int n = a.size(), m = t.size();
    vector<int> f(n), g(n+1,1e9+2);
    unordered_map<int,int> mp;
    for (int i = 0; i < m; ++i) {
        mp[t[i]] = i;
    }
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        if (!mp.count(a[i])) continue;
        int k = mp[a[i]];
        int ind = lower_bound(g.begin(),g.end(),k)-g.begin();
        f[i] = max(ind,0)+1;
        g[f[i]-1] = min(k,g[f[i]-1]);
        mx = max(mx,f[i]);
    }
    return m-mx;
}

/**
 * 本题对时间复杂度要求较高；尽量减少状态个数
 * https://leetcode.cn/problems/find-all-possible-stable-binary-arrays-i/description/
 * @param x
 * @param y
 * @param m
 * @return
 */
// int memo[202][202][202][2]; 与下列注释的赋值代码结合起来，可以减少一定的时间
int numberOfStableArrays(int x, int y, int m) {
    int mod = 1e9+7;
    int memo[y+1][m+1][x+1][2];
    memset(memo,-1,sizeof(memo));
//    for (int i = 0; i <= y; ++i) {
//        for (int j = 0; j <= m; ++j) {
//            for (int k = 0; k <= x; ++k) {
//                for (int l = 0; l <= 1; ++l) {
//                    memo[i][j][k][l] = -1;
//                }
//            }
//        }
//    }
    function<int(int,int,int,int)> dfs = [&](int i,int j,int k,int l){
        if (j > m || k > x || i > y) return 0;
        if (i == y && k == x) {
            return 1;
        }
        if (memo[i][j][k][l] != -1) return memo[i][j][k][l] ;
        int& res = memo[i][j][k][l] ;
        res = 0;
        if (l == 0) {
            res = (res%mod+dfs(i,j+1,k+1,0)%mod+dfs(i+1,1,k,1)%mod)%mod;
        } else {
            res = (res%mod+dfs(i,1,k+1,0)%mod+dfs(i+1,j+1,k,1)%mod)%mod;
        }
        return res;
    };
    int ans = (dfs(0,1,1,0)+dfs(1,1,0,1))%mod;
    return ans;
}


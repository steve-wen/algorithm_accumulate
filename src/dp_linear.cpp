#include <bits/stdc++.h>

using namespace std;

/**
*  线性 dp
 * 子序列 dp 的思考套路
 * 1. 0-1 背包， 选的子序列的相邻元素是无关的 [相邻无关]
 * 2. LIS(最长上升子序列) 选的子序列的相邻元素是相关的 [相邻相关]
 *
*/

/**
 * LCS 最长公共子序列
 * https://leetcode.cn/problems/longest-common-subsequence/description/
 * @param s1
 * @param s2
 * @return
 */
int longestCommonSubsequence(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    int memo[1001][1001];
    memset(memo, -1, sizeof(memo));
    function<int(int, int)> dfs = [&](int i, int j){
        if (i == m || j == n) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        if (s1[i] == s2[j]) {
            res = dfs(i+1,j+1) + 1;
        } else {
            res = max(dfs(i+1,j), dfs(i,j+1));
        }
        return res;
    };
    return dfs(0,0);
}

/**
 * LIS 最长递增子序列
 * 枚举选哪个 , memo 记忆
 * https://leetcode.cn/problems/longest-increasing-subsequence/description/
 * @param
 * @param
 * @return
 */
int lengthOfLIS(vector<int>& a) {
    int n = a.size(), ans = 0;
    int memo[2501];
    memset(memo, -1, sizeof(memo));
    function<int(int)> dfs = [&](int i){
        if (i == n-1) return 0;
        if (memo[i] != -1) return memo[i];
        int& res = memo[i];
        res = 0;
        for (int j = i+1; j < n; ++j) {
            if (a[j] > a[i]) {
                res = max(res, dfs(j)+1);
            }
        }
        return res;
    };
    for (int i = n-1; i >= 0; --i) { // 枚举选哪个
        ans = max(ans,dfs(i));
    }
    return ans+1;
}

int maxSelectedElements(vector<int>& a) {
    int n = 0, ans = 0;
    sort(a.begin(), a.end());
    int memo[100001][2];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j){
        if (i == n-1) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = 0;
        int k = lower_bound(a.begin()+i,a.end(),a[i]+j) - a.begin();
        if (k >= n) return 0;
        if (a[k] == a[i]+j) {
            res = dfs(k,1)+1;
        } else if (a[k] == a[i]+j+1) {
            res = dfs(k,0)+1;
        } else {
            return 0;
        }
        return res;
    };
    for (int i = n-1; i >= 0; --i) {
        ans = max(ans, max(dfs(i,0), dfs(i,1)));
    }
    return ans+1;
}

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
 * 时间复杂度 O(n^2)
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
 * 时间复杂度 O(n^2)
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

/**
 * 与最长递增子序列类似
 * 时间复杂度 O(nlogn)
 * 枚举选哪个 + 有序性 (lower_bound 二分的运用)
 * https://leetcode.cn/problems/maximize-consecutive-elements-in-an-array-after-modification/description/
 * @param a
 * @return
 */
int maxSelectedElements(vector<int>& a) {
    int n = a.size(), ans = 0;
    sort(a.begin(), a.end());
    int memo[100001][2];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j){
        if (i == n-1) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = 0;
        int k = lower_bound(a.begin()+i+1,a.end(),a[i]+j) - a.begin();
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

/**
 * LPS 最长回文子序列
 * 时间复杂度 O(n^2)
 * https://leetcode.cn/problems/longest-palindromic-subsequence/submissions/505786924/
 * @param
 * @param
 * @return
 */
int longestPalindromeSubseq(string s) {
    int n = s.size();
    int memo[1001][1001];
    memset(memo,-1,sizeof(memo));
    function<int(int, int)> dfs = [&](int i, int j){
        if (i ==j) return 1;
        if (i > j) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        if (s[i] == s[j]) {
            res = dfs(i+1,j-1)+2;
        } else {
            res = max(dfs(i+1,j), dfs(i,j-1));
        }
        return res;
    };
    return dfs(0,n-1);
}

/**
 * 朴素线性 dp
 * https://leetcode.cn/problems/dice-roll-simulation/description/
 * @param n
 * @param r
 * @return
 */
int dieSimulator(int n, vector<int>& r) {
    int mod = 1e9+7;
    int memo[n+1][7][16];
    memset(memo,-1, sizeof(memo));
    function<int(int,int,int)> dfs = [&](int i, int j, int k){
        if (i <= 0) {
            if (k <= r[j]) {
                return 1;
            }
            return 0;
        }
        if (memo[i][j][k] != -1) return memo[i][j][k];
        int& res = memo[i][j][k];
        res = 0;
        for (int l = 0; l < 6; ++l) {
            if (j != l) {
                res = (res + dfs(i-1,l,1)) % mod;
            } else {
                if (k < r[j]) {
                    res = (res + dfs(i-1,l,k+1))%mod;
                }
            }
        }
        return res;
    };
    int ans = 0;
    for (int i = 0; i < 6; ++i) {
        ans = (ans+dfs(n-1,i,1))%mod;
    }
    return ans;
}

//#include <bits/stdc++.h>
//
//using namespace std;
//
///**
// * 线性 dp + 优化
// * 时间复杂度 O(nk*n^(1/2))
// * 注意用的 dp, 不是记忆化 (平时注意结合使用，转化思维? 记忆化容易超时)
// * https://codeforces.com/problemset/problem/414/B
// * @return
// */
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    int MOD = (int)1e9+7;
//    int n,k;
//    long long ans = 0;
//    cin >> n >> k;
//    vector<int> a(n);
//    iota(a.begin(),a.end(), 1);
//    vector<vector<long long>> f(k+1,vector<long long>(n+1));
//    for (int i = 1; i <= n;++i) {
//        f[1][i] = 1;
//    }
//
//    for (int i =2; i <= k; ++i) {
//        for (int j = 1; j <= n; ++j) {
//            for (int l = 1; l <= sqrt(j); ++l) {
//                if (j % l == 0 && l != sqrt(j)) {
//                    f[i][j] = (f[i][j] + f[i-1][l] + f[i-1][j/l])%MOD;
//                } else if (j % l == 0 && l == sqrt(j)) {
//                    f[i][j] = (f[i][j] + f[i-1][l])%MOD;
//                }
//            }
//        }
//    }
//    for (int i = 1; i <= n; ++i) {
//        ans = (ans+f[k][i])%MOD;
//    }
//    cout<<ans;
//    return 0;
//}

/**
 * 前缀和, p[],f[]
 * 前缀和优化 dp
 * https://leetcode.cn/problems/first-day-where-you-have-been-in-all-the-rooms/description/?envType=daily-question&envId=2024-03-28
 * @param nextVisit
 * @return
 */
int firstDayBeenInAllRooms(vector<int>& a) {
    int mod = 1e9 + 7;
    int n = a.size();
    vector<long long> p(n+1), f(n);
    f[0] = 2;
    p[1] = 2;
    for (int i = 1; i < n; ++i) {
        f[i] = (2+p[i]-p[a[i]]+mod)%mod;
        p[i+1] = (p[i]+f[i])%mod;
    }

    return p[n-1];
}

/**
 * 离散化 + 线性 dp
 * O(n)
 * https://leetcode.cn/problems/maximum-profit-in-job-scheduling/description/
 * @param s
 * @param e
 * @param p
 * @return
 */
int jobScheduling(vector<int>& s, vector<int>& e, vector<int>& p) {
    vector<int> a;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        a.emplace_back(s[i]);
        a.emplace_back(e[i]);
    }
    ranges::sort(a);
    a.erase(unique(a.begin(),a.end()),a.end());
    int m = a.size();
    for (int i = 0; i < n; ++i) {
        s[i] = lower_bound(a.begin(),a.end(),s[i]) - a.begin();
        e[i] = lower_bound(a.begin(),a.end(),e[i]) - a.begin();
    }
    // b 记录初始位置的 各个组数
    vector<vector<pair<int,int>>> b(m+1);
    for (int i = 0; i < n; ++i) {
        b[s[i]].emplace_back(e[i],p[i]);
    }
    vector<int> f(m+1);
    for (int i = 0; i <= m; ++i) {
        if (i > 0) {
            f[i] = max(f[i],f[i-1]);
        }
        for (auto& b1 : b[i]) {
            auto [c, d] = b1;
            f[c] = max(f[c], f[i]+d);
        }
    }
    int ans = 0;
    for (int i = m; i >= 0; --i) {
        ans = max(ans,f[i]);
    }
    return ans;
}


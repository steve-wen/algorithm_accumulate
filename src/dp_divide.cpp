#include <bits/stdc++.h>

using namespace std;

/**
*  划分型 dp
*/

/**
 * 划分型 + 记忆化
 * 注意细节， 改 bug 结合调试 (仔细处)
 * lc.no.2547
 * @param a
 * @param k
 * @return
 */
int minCost(vector<int>& a, int k) {
    int n = a.size();
    vector<vector<int>> s(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        unordered_map<int,int> mp;
        for (int j = i; j < n; ++j) {
            if (mp[a[j]] == 1) {
                s[i][j] = s[i][j-1]+2;
            } else if (mp[a[j]] > 1) {
                s[i][j] = s[i][j-1]+1;
            } else if (j > 0){
                s[i][j] = s[i][j-1];
            }
            ++mp[a[j]];
        }
    }
    // int memo[n+1][n+1];
    static int memo[(int)1e3+1][(int)1e3+1];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j){
        if (i < 0) {
            if (j < 0) return 0;
            else return k + s[0][j];
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = min(k+s[i][j]+dfs(i-1,i-1),dfs(i-1,j));
        return res;
    };
    return dfs(n-1,n-1);
}

/**
 * 划分型 dp
 * lc.no.2767
 * @param s
 * @return
 */
int minimumBeautifulSubstrings(string s) {
    int n = s.size();
    auto check = [&](string s1) {
        if (s1 == "1" || s1 == "101" || s1 == "11001" || s1== "1111101" || s1 == "1001110001" || s1=="110000110101" || s1=="11110100001001") {
            return true;
        } else return false;
    };
    vector<vector<int>> memo(20,vector<int>(20,-1));

    function<int(int,int)> dfs = [&](int i, int j) {
        if (i < 0) {
            if(j < 0) return 0;
            else {
                if (check(s.substr(0,j+1))) return 1;
                else return 20;
            }
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = dfs(i-1,j);
        if (check(s.substr(i,j-i+1))) {
            res = min(1+dfs(i-1,i-1), res);
        }
        return res;
    };
    auto ans = dfs(n-1,n-1);
    return  ans >= 20 ? -1 : ans;
}

/**
 * 划分型 dp
 * 结合真因子 + 题目规则 + 预处理
 * 边界条件处注意细节
 * lc.no.2911
 */
// 预处理每个数的真因子，时间复杂度 O(MX*logMX) (较快的时间复杂度)
// 自然数 n 平均有 O(log(n)) 个因子
const int MX = 201;
vector<vector<int>> divisors(MX);
int init_1 = [] {
    for (int i = 1; i < MX; i++) {
        for (int j = i * 2; j < MX; j += i) {
            divisors[j].push_back(i);
        }
    }
    return 0;
}();

class Solution {
    // 关键， 题目规则
    int get_modify(string s) {
        int n = s.length();
        int res = n;
        for (int d: divisors[n]) { // O(log(n))
            int cnt = 0;
            // O(n) (按规则遍历字符串)
            for (int i0 = 0; i0 < d; i0++) { // 半回文规则
                for (int i = i0, j = n - d + i0; i < j; i += d, j -= d) {
                    cnt += s[i] != s[j];
                }
            }
            res = min(res, cnt);
        }
        return res;
    }

public:
    int minimumChanges(string s, int k) {
        int n = s.length();
        vector<vector<int>> modify(n, vector<int>(n,n+1));
        // O(n^3 * log(n))
        for (int left = 0; left < n - 1; left++) { // 预处理
            for (int right = left + 1; right < n; right++) {
                modify[left][right] = get_modify(s.substr(left, right - left + 1));
            }
        }
        int memo[101][201][201];
        memset(memo,-1,sizeof(memo));
        // O(n^3)
        function<int(int, int, int)> dfs = [&](int t, int i, int j) -> int {
            // 边界条件
            if (i < 0) {
                if (t >= 0) return n+1; // 注意细节条件
                else return 0;
            }
            if (t == 0) {
                return modify[0][j];
            }
            int &res = memo[t][i][j]; // 注意这里是引用
            if (res != -1) { // 之前计算过
                return res;
            }
            res = dfs(t,i-1,j);
            if (i < j) {
                res = min(res, dfs(t-1,i - 1, i-1) + modify[i][j]);
            }
            return res;
        };
        return dfs(k - 1,n-1, n - 1);
    }
};

/**
 * 划分型 dp
 * f[i][j]: 表示 第 i 次划分，以 j 结尾的子数组(子区间) 的最大和;
 * 时间复杂度(O(n*k))
 * 注意 f[i][j] 遍历的顺序， 注意递推式的变形, 边遍历边维护 w (mx),减少时间复杂度
 * https://leetcode.cn/problems/maximum-strength-of-k-disjoint-subarrays/description/
 * @param a
 * @param k
 * @return
 */
long long maximumStrength(vector<int>& a, int k) {
    int n = a.size();
    vector<long long> s(n+1);
    for(int i =0; i < n; ++i) {
        s[i+1] = s[i]+a[i];
    }
    vector<vector<long long>> f(k+1,vector<long long>(n+1));
    for (int i = 1; i <= k; ++i) {
        long long w = LLONG_MIN;
        for (int j = i; j <= n; ++j) {
            w = max(w,f[i-1][j-1]+(long long)(k-i+1)*(s[j-1])*(long long)(i%2 == 0 ? 1 : -1));
            f[i][j] = (long long)(k-i+1)*s[j]*(long long)(i%2 == 0 ? -1 : 1) + w;
        }
    }
    long long ans = LLONG_MIN;
    for (int i = k; i <= n; ++i) {
        ans = max(ans,f[k][i]);
    }
    return ans;
}

/**
 * 中心扩展法 + 划分型 dp
 * 中心扩展法 -> 统计回文字符串; 时间复杂度 O(n^2)
 * @param s
 * @param k
 * @return
 */
int maxPalindromes(string s, int k) {
    int n = s.size();
    if (k == 1) return n;
    vector<vector<bool>> b(n,vector<bool>(n));
    // 中心扩展法 时间复杂度 O(n^2); 统计回文字符串
    // 长度为奇数时的中心扩展
    for (int i = 0; i < n; ++i) {
        b[i][i] = true;
        int j = i -1, l = i+1;
        while(j >= 0 && l < n && s[j] == s[l]) {
            b[j][l] = true;
            --j;
            ++l;
        }
    }
    // 长度为偶数时的中心扩展
    for (int i = 0; i < n-1; ++i) {
        if (s[i] == s[i+1]) {
            b[i][i+1] = true;
            int j = i-1, l = i+2;
            while(j >= 0 && l < n && s[j] == s[l]) {
                b[j][l] = true;
                --j;
                ++l;
            }
        }
    }
    // 划分型 dp
    int memo[100+1][100+1];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j) {
        if (i < 0) return 0;
        if(memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        if (j-i+1 >= k && b[i][j]) {
            res = max(dfs(i-1,j), dfs(i-1,i-1)+1);
        } else {
            res = max(dfs(i-1,i-1),dfs(i-1,j));
        }
        return res;
    };
    return dfs(n-1,n-1);
}

//int minHeightShelves(vector<vector<int>>& b, int d) {
//    int n = b.size();
//    vector<int> s(n+1);
//    for(int i =0; i < n; ++i) {
//        s[i+1] = s[i]+b[i][0];
//    }
//    vector<vector<int>> f(n+1,vector<int>(n+1,1e6));
//    for (int i = 1; i <= n; ++i) {
//        int w = b[i][1];
//        for (int j = i+1; j <= n && s[j] - s[i-1] <= d; ++j) {
//            if (b[j][1])
//            f[i][j] = (long long)(k-i+1)*s[j]*(long long)(i%2 == 0 ? -1 : 1) + w;
//        }
//    }
//    long long ans = LLONG_MIN;
//    for (int i = k; i <= n; ++i) {
//        ans = max(ans,f[k][i]);
//    }
//    return ans;
//
//}


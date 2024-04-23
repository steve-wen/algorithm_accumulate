#include <bits/stdc++.h>

using namespace std;

/**
*  预处理 + dp
*
*/
#define ll long long

/**
 * set 二分预处理下标 + dp
 * https://leetcode.cn/problems/odd-even-jump/description/
 * @param a
 * @return
 */
int oddEvenJumps(vector<int>& a) {
    set<pair<int,int>> st;
    int n = a.size();
    for (int i = 0;i < n; ++i) {
        st.emplace(a[i],i);
    }
    vector<int> ind1(n), ind2(n);
    for (int i = 0; i < n; ++i) {
        st.erase(pair<int,int>(a[i],i));
        int j = n,k = n;
        if (st.lower_bound(pair<int,int>(a[i],i)) != st.end()) {
            j = (*st.lower_bound(pair<int,int>(a[i],i))).second;
        }
        if (st.lower_bound(pair<int,int>(a[i],i)) != st.begin()) {
            auto l = st.lower_bound(pair<int,int>(a[i],i));
            if (l->first == a[i]) {
                k = l->second;
            } else {
                --l;
                int m = l->first;
                auto l1 = st.lower_bound(pair<int,int>(m,0));
                k = l1->second;
            }
        } else if(st.begin()->first == a[i]) {
            k = st.begin()->second;
        }
        ind1[i] = j;
        ind2[i] = k;
    }
    int memo[(int)2e4+2][3];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j){
        if (i == n-1) {
            return 1;
        }
        if (i > n-1) {
            return 0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        if (j % 2) {
            res = dfs(ind1[i],j-1);
        } else {
            res = dfs(ind2[i],j+1);
        }
        return res;
    };
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += dfs(i,1);
    }
    return ans;
}

/**
 * 求 s[i: ] 与 s[j: ] 的最长公共前缀 lcp; 时间复杂度 O(n)
 * @param s
 * @return
 */
vector<int> z_func(string s) {
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        } else {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

/**
 * 预处理 + dp
 * z 函数预处理求 s[i: ] 与 s[j: ] 的最长公共前缀 lcp; + dp
 * 注意 s.substr 的时间复杂度为 O(n)
 * 时间复杂度 O(n^2)
 * https://leetcode.cn/problems/maximum-deletions-on-a-string/solutions/1864049/xian-xing-dppythonjavacgo-by-endlesschen-gpx9/
 * @param s
 * @return
 */
int deleteString(string s) {
    int n = s.size();
    vector<vector<int>> lcp(n,vector<int>(n,0));
    for (int i = 0; i < n; ++i) {
        auto z = z_func(s.substr(i,n-i));
        for (int j = i; j < n; ++j) {
            lcp[i][j] = z[j-i];
        }
    }
    vector<int> f(n,1);
    for (int i = n-2; i >= 0; --i) {
        for (int j = i+1;j< n; ++j) {
            if (lcp[i][j] >= j-i) {
                f[i] = max(f[i],f[j]+1);
            }
        }
    }
    return f[0];
}

/**
 * 预处理 + dp
 * 拆项： 拆除绝对值符号; 分类讨论; 前后缀分解分别存储目前下标的 max 值
 * https://leetcode.cn/problems/maximum-number-of-points-with-cost/solutions/882211/dp-you-hua-ji-qiao-chai-xiang-qian-hou-z-5vvc/
 * @param g
 * @return
 */
long long maxPoints(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    long long f[m][n];
    long long h1[m][n],h2[m][n];
    memset(f,0,sizeof(f));
    memset(h1,0,sizeof(h1));
    memset(h2,0,sizeof(h2));
    for (int i = 0; i < n; ++i) {
        f[0][i] = g[0][i];
    }
    for (int i = 1; i < m; ++i) {
        ll mx1 = -1e6, mx2 = -1e6;
        for (int j = 0; j < n; ++j) {
            mx1 = max(mx1,f[i-1][j]+j);
            h1[i][j] = mx1;
        }
        for (int j = n-1; j >= 0; --j) {
            mx2 = max(mx2,f[i-1][j]-j);
            h2[i][j] = mx2;
        }
        for (int j = 0; j < n; ++j) {
            f[i][j] = max(g[i][j]+j+h2[i][j],g[i][j]-j+h1[i][j]);
        }
    }
    ll mx = 0;
    for (int i = 0; i < n; ++i) {
        mx = max(mx,f[m-1][i]);
    }
    return mx;
}

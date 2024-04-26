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

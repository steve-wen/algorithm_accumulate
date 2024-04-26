#include <bits/stdc++.h>

using namespace std;
#define ll long long

/**
*  off_line
*/

/**
 * 离线 + 滑动窗口
 * https://leetcode.cn/problems/count-zero-request-servers/solutions/2320098/chi-xian-hua-dong-chuang-kou-pythonjavac-b573/
 * @param n
 * @param a
 * @param x
 * @param q
 * @return
 */
vector<int> countServers(int n, vector<vector<int>>& a, int x, vector<int>& q) {
    vector<int> cnt(n+1);
    int m = q.size();
    vector<int> ans(m);
    vector<int> ind(m);
    iota(ind.begin(),ind.end(),0);
    sort(ind.begin(),ind.end(),[&](int i, int j){return q[i] < q[j];});
    // lambda 表达式的入参传引用会快很多(特别针对高维 vector)
    sort(a.begin(),a.end(),[&](vector<int>& b, vector<int>& c){return b[1] < c[1];});
    int res = n,l = 0, r = 0;
    for (auto& i : ind) {
        while (r < a.size() && a[r][1] <= q[i]) {
            if (cnt[a[r++][0]]++ == 0) {
                --res;
            }
        }
        while (l < a.size() && a[l][1] < q[i]-x) {
            if (--cnt[a[l++][0]] == 0) {
                ++res;
            }
        }
        ans[i] = res;
    }
    return ans;
}

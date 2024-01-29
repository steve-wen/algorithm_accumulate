#include <bits/stdc++.h>

using namespace std;

/**
*  图论
*/

/**
 * Floyd
 * dfs, 时间复杂度 : O(n^3)
 * https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/
 */

int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
    vector<vector<int>> w(n, vector<int>(n, 1e6)); // 防止加法溢出
    for (auto &e: edges) {
        int x = e[0], y = e[1], wt = e[2];
        w[x][y] = w[y][x] = wt;
    }

    int memo[101][101][101];
    memset(memo, -1, sizeof(memo)); // 除了 0, -1 的其他特殊值用 vector 初始化
    function<int(int, int, int)> dfs = [&](int k, int i, int j) -> int {
        if (k < 0) { // 递归边界
            return w[i][j];
        }
        auto &res = memo[k][i][j]; // 注意这里是引用
        if (res != -1) { // 之前计算过
            return res;
        }
        return res = min(dfs(k - 1, i, j), dfs(k - 1, i, k) + dfs(k - 1, k, j));
    };

    int ans = 0;
    int min_cnt = n;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (j != i && dfs(n - 1, i, j) <= distanceThreshold) {
                cnt++;
            }
        }
        if (cnt <= min_cnt) { // 相等时取最大的 i
            min_cnt = cnt;
            ans = i;
        }
    }
    return ans;
}

/**
 * Floyd, O(n^3)
 * https://leetcode.cn/problems/minimum-cost-to-convert-string-i/description/
 * @param s
 * @param t
 * @param o
 * @param ch
 * @param co
 * @return
 */
long long minimumCost(string s, string t, vector<char>& o, vector<char>& ch, vector<int>& co) {
    int n = s.size();
    long long ans = 0;
    vector<vector<long long>> w(27, vector<long long>(27, 1e8)); // 防止加法溢出
    for (int i = 0; i < o.size(); ++i) {
        int x = o[i]-'a', y = ch[i]-'a', wt = co[i];
        w[x][y] = min((long long)wt, w[x][y]);
    }

    long long memo[27][27][27];
    memset(memo, -1, sizeof(memo)); // 除了 0, -1 的其他特殊值用 vector 初始化
    function<long long(int, int, int)> dfs = [&](int k, int i, int j) -> int {
        if (k < 0) { // 递归边界
            return w[i][j];
        }
        auto &res = memo[k][i][j]; // 注意这里是引用
        if (res != -1) { // 之前计算过
            return res;
        }
        return res = min(dfs(k - 1, i, j), dfs(k - 1, i, k) + dfs(k - 1, k, j));
    };

    for (int i = 0; i < n; i++) {
        if (s[i] == t[i]) continue;
        auto cnt = dfs(26,s[i]-'a',t[i]-'a');
        if (cnt >= 1e8) return -1;
        ans += cnt;
    }
    return ans;
}


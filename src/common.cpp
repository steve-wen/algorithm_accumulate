#include <bits/stdc++.h>

using namespace std;

/**
* 基础算法
*/

/**
* 不定长滑动窗口 (求子数组个数)
*/
// 滑窗,统计合法子数组数目 lc.no.2962
long long countSubarrays(vector<int>& a, int k) {
    long long ans = 0, n = a.size();
    int mx = *max_element(a.begin(),a.end());
    long long cnt = 0;
    for (long long l = 0, r = 0; r < n; ++r) {
        if (a[r] == mx) ++cnt;
        while (cnt == k) {
            ans += n-r;
            if (a[l] == mx) --cnt;
            ++l;
        }
    }
    return ans;
}

/**
 * 合并区间
 * lc.no.2963
 */
const int MOD = 1'000'000'007;

// 快速幂取 MOD
long long q_pow1(long long x, int n) {
    long long res = 1;
    for (; n > 0; n /= 2) {
        if (n % 2) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

int numberOfGoodPartitions(vector<int> &a) {
    long long ans = 0, n = a.size(), len = n;
    unordered_map<int, pair<int, int>> mp;
    for (int i = 0; i < n; ++i) {
        if (mp.count(a[i])) {
            mp[a[i]].second = i;

        } else {
            mp[a[i]].first = i;
            mp[a[i]].second = i;
        }
    }

    int mn = n + 1, mx = 0, tmp = 0;
    for (int i = 0; i < n; ++i) {
        if (mp[a[i]].first > mx || i == n - 1) {
            len -= tmp;
            mn = mp[a[i]].first;
            mx = mp[a[i]].second;
        } else {
            mn = min(mn, mp[a[i]].first);
            mx = max(mx, mp[a[i]].second);
        }
        tmp = mx - mn;
    }
    ans = q_pow1(2,len-1);// c(n,0)+...+c(n,n) == 2^n
    return ans;
}

/**
 * 差分
 */

/**
 * 差分数组 + 分类讨论 + 数学不等式思维
 * https://leetcode.cn/problems/count-the-number-of-houses-at-a-certain-distance-ii/description/
 * @param n
 * @param x
 * @param y
 * @return
 */
vector<long long> countOfPairs(int n, int x, int y) {
    // 确保 x <= y
    if (x > y) {
        swap(x, y);
    }
    vector<long long> ans(n);
    if (x + 1 >= y) {
        for (int i = 1; i < n; i++) {
            ans[i - 1] = (n - i) * 2;
        }
        return ans;
    }

    vector<int> diff(n + 1, 0);

    auto add = [&](int l, int r) {
        diff[l]++;
        diff[r + 1]--;
    };

    for (int i = 1; i < n; i++) {
        if (i <= x) {
            int k = (x + y + 1) / 2;
            add(1, k - i);
            add(x - i + 2, x - i + y - k);
            add(x - i + 1, x - i + 1 + n - y);
        } else if (i <= (x + y - 1) / 2) {
            int k = i + (y - x + 1) / 2;
            add(1, k - i);
            add(i - x + 2, i - x + y - k);
            add(i - x + 1, i - x + 1 + n - y);
        } else {
            add(1, n - i);
        }
    }

    long long sum_d = 0;
    for (int i = 0; i < n; i++) {
        sum_d += diff[i + 1];
        ans[i] = sum_d * 2;
    }
    return ans;
}

/**
 * 差分数组 + 分类讨论 + 数学不等式思维
 * https://leetcode.cn/problems/count-the-number-of-houses-at-a-certain-distance-ii/description/
 * @param n
 * @param x
 * @param y
 * @return
 */
vector<long long> diff_template(int n, int x, int y) {
    // 确保 x <= y
    if (x > y) {
        swap(x, y);
    }
    vector<long long> ans(n);
    // 特殊情况
    if (x + 1 >= y) {
        for (int i = 1; i < n; i++) {
            ans[i - 1] = (n - i) * 2;
        }
        return ans;
    }
    // 初始化差分数组
    vector<int> diff(n + 1, 0);
    // add
    auto add = [&](int l, int r) {
        diff[l]++;
        diff[r + 1]--;
    };

    for (int i = 1; i < n; i++) {
        if (i <= x) {
            int k = (x + y + 1) / 2;
            add(1, k - i);
            add(x - i + 2, x - i + y - k);
            add(x - i + 1, x - i + 1 + n - y);
        } else if (i <= (x + y - 1) / 2) {
            int k = i + (y - x + 1) / 2;
            add(1, k - i);
            add(i - x + 2, i - x + y - k);
            add(i - x + 1, i - x + 1 + n - y);
        } else {
            add(1, n - i);
        }
    }

    // 求和得到 ans
    long long sum_d = 0;
    for (int i = 0; i < n; i++) {
        sum_d += diff[i + 1];
        ans[i] = sum_d * 2;
    }
    return ans;
}

/**
 * 离散化 + 二维差分
 * @param f
 * @return
 */
int fieldOfGreatestBlessing(vector<vector<int>>& f) {
    int ans = 0;
    vector<long> x,y;
    for (auto& f1 : f) {
        // 为离散化做准备
        x.emplace_back((long)f1[0] * 2 + (long)f1[2]);
        x.emplace_back((long)f1[0] * 2 - (long)f1[2]);
        y.emplace_back((long)f1[1] * 2 + (long)f1[2]);
        y.emplace_back((long)f1[1] * 2 - (long)f1[2]);
    }
    // 为离散化做准备，有序性
    ranges::sort(x);
    x.erase(unique(x.begin(),x.end()),x.end());
    ranges::sort(y);
    y.erase(unique(y.begin(),y.end()),y.end());
    int n = x.size();
    vector<vector<int>> diff(n + 2, vector<int>(n + 2));
    for (auto& f1 : f) {
        // 离散化（以下标顺序作为参数）
        int x1 = lower_bound(x.begin(),x.end(), (long)f1[0] * 2 - (long)f1[2]) - x.begin(); // 下标做差
        int x2 = lower_bound(x.begin(),x.end(), (long)f1[0] * 2 + (long)f1[2]) - x.begin();
        int y1 = lower_bound(y.begin(), y.end(), (long)f1[1] * 2 - (long)f1[2]) - y.begin();
        int y2 = lower_bound(y.begin(), y.end(), (long)f1[1] * 2 + (long)f1[2]) - y.begin();
        // 二维差分
        ++diff[1 + x1][1 + y1];
        --diff[2 + x2][1 + y1];
        --diff[1 + x1][2 + y2];
        ++diff[2 + x2][2 + y2];
    }
    // 二维差分
    int sum_d = 0;
    for (int i = 1; i < n + 2; ++i) {
        for (int j = 1; j < n + 2; ++j) {
            sum_d = (diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1] + diff[i][j]);
            diff[i][j] = sum_d; // 需要更新 diff[i][j]
            ans = max(ans, sum_d);
        }
    }
    return ans;
}

/**
 * 离散化 + 一维差分
 * https://leetcode.cn/problems/number-of-flowers-in-full-bloom/description/
 * @param f
 * @return
 */
vector<int> fullBloomFlowers(vector<vector<int>>& f, vector<int>& p) {
    vector<int> x;
    for (auto f1 : f) {
        x.emplace_back(f1[0]);
        x.emplace_back(f1[1]);
    }
    // 为离散化做准备，有序性
    ranges::sort(x);
    x.erase(unique(x.begin(),x.end()),x.end());
    int n = x.size();
    // 差分数组
    vector<int> diff(n + 1);
    // mn 记录需要减少的值/量
    vector<int> mn(n + 1);
    for (auto& f1 : f) {
        // 离散化（以下标顺序作为参数）
        int x1 = lower_bound(x.begin(),x.end(), f1[0]) - x.begin(); // 下标做差
        int x2 = lower_bound(x.begin(),x.end(), f1[1]) - x.begin();
        // 二维差分
        ++diff[x1];
        --diff[1 + x2]; // 右闭区间
        --mn[1 + x2];
    }
    int sum = 0;
    vector<int> d(n+1);
    // 差分累加
    for (int i = 0; i < n+1; ++i) {
        sum += diff[i];
        d[i] = sum;
    }
    vector<int> ans;
    for (auto p1 : p) {
        if (p1 < x[0] || p1 >x[n-1]) {
            ans.emplace_back(0);
        } else {
            int ind = upper_bound(x.begin(),x.end(), p1) - x.begin()-1;
            if (p1 > x[ind]) {
                ans.emplace_back(d[ind]+mn[ind+1]);
            } else {
                ans.emplace_back(d[ind]);
            }
        }
    }
    return ans;
}

/**
 * 二维前缀和模板
 * @param g
 * @param k
 * @return
 */
int countSubmatrices(vector<vector<int>>& g, int k) {
    int m = g.size(), n = g[0].size(), ans = 0;
    vector<vector<int>> pre(m+2,vector<int>(n+2));
    for (int i = 1; i < m + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            pre[i][j] = ( pre[i - 1][j] +  pre[i][j - 1] -  pre[i - 1][j - 1] +  g[i-1][j-1]);
            ans += pre[i][j] <= k;
        }
    }
    return ans;
}

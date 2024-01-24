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

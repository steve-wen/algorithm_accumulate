#include <bits/stdc++.h>

using namespace std;
#define ll long long

/**
*  二分算法
*/

/**
 * 二分/枚举 + 贪心策略（在 last[idx] 时考试，消耗；其他情况 ++cnt）
 * // https://leetcode.cn/problems/earliest-second-to-mark-indices-i/description/
 * @param nums
 * @param changeIndices
 * @return
 */
int earliestSecondToMarkIndices(vector<int> &nums, vector<int> &changeIndices) {
    int n = nums.size(), m = changeIndices.size(), ans = m + 1;
    if (n > m) return -1;

    auto check = [&](int mx) {
        vector<int> last_t(n, -1);
        for (int t = 0; t < mx; t++) {
            last_t[changeIndices[t] - 1] = t;
        }
        if (ranges::find(last_t, -1) != last_t.end()) { // 有课程没有考试时间
            return false;
        }

        int cnt = 0;
        for (int i = 0; i < mx; i++) {
            int idx = changeIndices[i] - 1;
            if (i == last_t[idx]) { // 考试
                if (nums[idx] > cnt) { // 没时间复习
                    return false;
                }
                cnt -= nums[idx]; // 复习这门课程
            } else {
                cnt++; // 留着后面用
            }
        }
        return true;
    };

    int left = 0, right = m;
    while (left  <= right) {
        int mid = (left + right) / 2;
         if (check(mid)) {
             right = mid - 1;
             ans = min(ans, mid);
         } else {
             left = mid + 1;
         }
    }
    return ans > m ? -1 : ans;
}

/**
 * 二分,注意 long long 和取模
 * https://leetcode.cn/problems/sell-diminishing-valued-colored-balls/description/
 * @param a
 * @param b
 * @return
 */
int maxProfit(vector<int>& a, int b) {
    int mod = 1e9+7;
    int n = a.size();
    long long mx = *max_element(a.begin(),a.end());
    long long ans = 0, cnt = 1e9+1, val = 0;

    auto check = [&](long long mx, long long& tmp, long long& cnt1) -> bool {
        for (auto a1 : a) {
            cnt1 += (long long)max(0LL,a1-mx);
            if (a1 > mx) {
                tmp = (tmp+(long long)(a1+mx+1)*(a1-mx)/2%mod)%mod;
            }
        }
        if (cnt1 >= b) {
            return true;
        }
        return false;
    };

    int left = 0, right = mx;
    while (left  <= right) {
        long long mid = (left + right) / 2, tmp = 0,cnt1 = 0;
        if (check(mid,tmp,cnt1)) {
            left = mid + 1;
            if (mid >= val) {
                val = mid;
                ans = tmp;
                cnt = cnt1;
            }
        } else {
            right = mid - 1;
        }
    }
    // 注意负数取模
    ans = ((ans-(long long)(cnt-b)*(val+1)%mod)%mod+mod)%mod;
    return ans;
}

/**
 * 二分 + 容斥
 * https://leetcode.cn/problems/minimize-the-maximum-of-two-arrays/solutions/2031827/er-fen-da-an-by-endlesscheng-y8fp/
 * @param d1
 * @param d2
 * @param a1
 * @param a2
 * @return
 */
int minimizeSet(int d1, int d2, int a1, int a2) {
    ll d = (ll)lcm((ll)d1,(ll)d2);
    auto check = [&](ll x){
        ll cnt = x;
        ll tmp = x/d;
        cnt -= tmp;
        ll cnt1 = cnt - x/d1 + tmp;
        if (cnt1 < (ll)a1) return false;
        ll res = min((ll)a1,x/d2-x/d);
        ll cnt2 = cnt - a1;
        cnt2 = cnt2 - x/d2 +tmp+res;
        if (cnt2 < a2) return false;
        return true;
    };
    ll l = 0, r = 1e10, ans = 1e10;
    while (l  <= r) {
        ll mid = (l + r) / 2;
        if (check(mid)) {
            r = mid - 1;
            ans = min(ans, mid);
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

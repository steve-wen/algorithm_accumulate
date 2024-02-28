#include <bits/stdc++.h>

using namespace std;

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

    auto check = [&](int mx) -> bool {
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


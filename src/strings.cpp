#include <bits/stdc++.h>

using namespace std;

/**
*  strings
*/

/**
 * kmp
 * 时间复杂度 O(n)
 * @param pattern
 * @return
 */

/**
 * 计算模式串每个下标的真前缀/后缀 匹配长度
 * @param pattern
 * @return
 */
vector<int> calculateMaxMatchLengths(const string& pattern) {
    vector<int> maxMatchLengths(pattern.length());
    int maxLength = 0;
    for (int i = 1; i < pattern.length(); i++) {
        while (maxLength > 0 && pattern[maxLength] != pattern[i]) {
            maxLength = maxMatchLengths[maxLength - 1]; // ①
        }
        if (pattern[maxLength] == pattern[i]) {
            maxLength++; // ②
        }
        maxMatchLengths[i] = maxLength;
    }
    return maxMatchLengths;
}

/**
 * 在文本串中匹配模式串，匹配失败时，总是能够让模式串回退到某个位置，使文本不用回退。
 * @param pattern
 * @return
 */
vector<int> kmp_search(const string& text, const string& pattern) {
    vector<int> positions;
    vector<int> maxMatchLengths = calculateMaxMatchLengths(pattern);
    int count = 0;
    for (int i = 0; i < text.length(); i++) {
        while (count > 0 && pattern[count] != text[i]) {
            count = maxMatchLengths[count - 1];
        }
        if (pattern[count] == text[i]) {
            count++;
        }
        if (count == pattern.length()) {
            positions.emplace_back(i - pattern.length() + 1);
            count = maxMatchLengths[count - 1];
        }
    }
    return positions;
}

/**
 * kmp 经典模板题 (+ 双指针(while, 合并两个数组/字符串))
 * 时间复杂度 O(n)
 * https://leetcode.cn/problems/find-beautiful-indices-in-the-given-array-ii/description/
 * @param pattern
 * @return
 */
vector<int> beautifulIndices(string s, string a, string b, int k) {
    int n = s.size(), m1 = a.size(), m2 = b.size();
    vector<int> veci,vecj,ans;
    veci = kmp_search(s,a);
    vecj = kmp_search(s,b);
    int l1 = 0,l2 = 0, n1 = veci.size(), n2 = vecj.size();
    while (l1 < n1 && l2 < n2) {
        if (abs(veci[l1] - vecj[l2]) <= k) {
            ans.emplace_back(veci[l1]);
            ++l1;
        } else {
            if (vecj[l2] < veci[l1]) {
                ++l2;
            } else {
                ++l1;
            }
        }
    }
    return ans;
}

/**
 * 对于长度为 n 的字符串 s。定义函数 z[i] 表示 s 和 s[i,n-1]（即以 s[i] 开头的后缀）的最长公共前缀（LCP）的长度。z 被称为 s 的 Z 函数。特别地，z[0] = 0。
    国外一般将计算该数组的算法称为 Z Algorithm，而国内则称其为 扩展 KMP。
     O(n) 时间复杂度内计算 Z 函数的算法。
 * @param s
 * @return
 */
vector<int> z_function(string s) {
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
 * z_function
 * https://leetcode.cn/problems/minimum-time-to-revert-word-to-initial-state-ii/description/
 *  O(n) 时间复杂度
 * @param w
 * @param k
 * @return
 */
int minimumTimeToInitialState(string w, int k) {
    auto z = z_function(w);
    int n = w.size(), ans = 1;
    for (int i = k; i < n; i += k) {
        if (z[i] == n-i) return ans;
        else {
            ++ans;
        }
    }
    return ans;
}

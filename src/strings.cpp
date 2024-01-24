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


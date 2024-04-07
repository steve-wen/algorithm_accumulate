#include <bits/stdc++.h>

using namespace std;

/**
 *  栈的运用
 *
*/

/**
 * 用栈 模拟过程， 注意 while 的运用
 * https://leetcode.cn/problems/replace-non-coprime-numbers-in-array/description/
 * @param nums
 * @return
 */
vector<int> replaceNonCoprimes(vector<int> &nums) {
    vector<int> s;
    for (int num : nums) {
        s.push_back(num);
        while (s.size() > 1) {
            int x = s.back(), y = s[s.size() - 2];
            int g = gcd(x, y);
            if (g == 1) break;
            s.pop_back();
            s.back() *= x / g;
        }
    }
    return s;
}

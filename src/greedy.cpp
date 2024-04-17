#include <bits/stdc++.h>

using namespace std;

/**
 *  贪心
 *
*/

/**
 * 贪心+模拟, 逆序对 ?
 * https://leetcode.cn/problems/minimum-number-of-moves-to-make-palindrome/solutions/1313466/tan-xin-zheng-ming-geng-da-shu-ju-fan-we-h57i/
 * @param s
 * @return
 */
int minMovesToMakePalindrome(string s) {
    int ans = 0;
    int n = s.size();
    for (int i = 0;i < n/2; ++i){
        auto c = s[i];
        int k = i;
        for (int j = n-1-i; j >= i; --j) {
            if (s[j] == c){
                k = j;
                break;
            }
        }
        if (k == i){
            swap(s[i],s[i+1]);
            ++ans;
            --i;
        } else {
            for (int j = k; j < n-1-i; ++j){
                swap(s[j],s[j+1]);
                ++ans;
            }
        }
    }
    return ans;
}

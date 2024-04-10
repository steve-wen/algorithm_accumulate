#include <bits/stdc++.h>

using namespace std;

/**
*  位运算的运用
*  __builtin_popcount(x) : 统计二进制形式的 x 中的 1 的个数
*/

// 结合 bitset 与灵神的位运算文章结合
/**
 *
 * 位运算
 * @param vec
 * @param k
 * @return
 */
int maxSum(vector<int>& vec, int k) {
    long long mod = 1e9+7;
    long ans = 0;
    unordered_map<int,int> mp;
    for (auto a : vec){
        auto s = bitset<30>(a).to_string();
        // 注意首尾下标
        for (int i = 0, j = 29-i; j >= 0; ++i,--j) {
            if (s[j] == '1') {
                mp[i]++;
            }
        }
    }
    while (k) {
        long tmp = 0;
        for (int i = 0; i <= 29; ++i) {
            if (mp[i] > 0) {
                tmp += (long)pow(2,i);
                --mp[i];
            }
        }
        ans += tmp * tmp;
        ans = ans % mod;
        --k;
    }
    return ans;
}

/**
 * bitset 运用，整数转 bitset 转 string, 调用 string find 功能
 * @param s
 * @param n
 * @return
 */

bool queryString(string s, int n) {
    for (int i = 1; i <= n; ++i) {
        auto bin = bitset<30>(i).to_string();
        bin = bin.substr(bin.find('1'));
        if (s.find(bin) == string::npos) return false;
    }
    return true;
}

/**
 * bitset 运用 .count(), 计算二进制里 1 的个数
 * @param nums
 * @param k
 * @return
 */

int sumIndicesWithKSetBits(vector<int>& nums, int k) {
    int ans = 0, n = nums.size();
    for (int i = 0; i < n; ++i) {
        if (__builtin_popcount(i) == k) {
            ans += nums[i];
        }
        // count() 二进制里 1 的个数
//        if (bitset<10>(i).count() == k) {
//            ans += nums[i];
//        }
    }
    return ans;
}

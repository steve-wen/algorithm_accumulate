#include <bits/stdc++.h>

using namespace std;
#define ll long long

/**
* 组合数学
*/

/**
 * 组合数学 逆元
 */
const int MOD = 1'000'000'007;
const int MX = 500'000; // C(n,k) n

// 快速幂取 MOD
long long q_pow(long long x, int n) {
    long long res = 1;
    for (; n > 0; n /= 2) {
        if (n % 2) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

// 组合数模板， 逆元
// fac : 阶乘 ,inv_a : 个数 a[i] 的逆元, inv_a[i]/inv[i]
long long fac[MX], inv_fac[MX], inv_a[MX];

auto init_inv = [] {
    fac[0] = 1;
    for (int i = 1; i < MX; i++) {
        fac[i] = fac[i - 1] * i % MOD; // for (int i = 1; i <= n; ++i) s[i] = s[i - 1] * a[i] % p;
    }
    inv_fac[MX - 1] = q_pow(fac[MX - 1], MOD - 2); // x === a^(b-2) (mod b)
    for (int i = MX - 1; i > 0; i--) {
        inv_fac[i - 1] = inv_fac[i] * i % MOD; // for (int i = n; i >= 1; --i) sv[i - 1] = sv[i] * a[i] % p;
    }
    for (int i = 1; i <= MX - 1; ++i) inv_a[i] = inv_fac[i] * fac[i - 1] % MOD; // for (int i = 1; i <= n; ++i) inv[i] = sv[i] * s[i - 1] % p;
    // 求出每个数 a[i] 的逆元, inv[i]
    return 0;
}();

// 组合
long long comb(int n, int k) {
    return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD;
}
// 排列
long long arra(int n, int k) {
    return fac[n] * inv_fac[n - k] % MOD;
}

class Solution_inv {
public:
    int numberOfSequence(int n, vector<int> &a) {
        int m = a.size();
        int total = n - m;
        long long ans = comb(total, a[0]) * comb(total - a[0], n - a.back() - 1) % MOD;
        total -= a[0] + n - a.back() - 1;
        int e = 0;
        for (int i = 0; i < m - 1; i++) {
            int k = a[i + 1] - a[i] - 1;
            if (k) {
                e += k - 1;
                ans = ans * comb(total, k) % MOD;
                total -= k;
            }
        }
        return ans * q_pow(2, e) % MOD;
    }

    int countAnagrams(string s) {
        long long ans = 1;
        int n = s.size(), ind = 0;
        vector<int> cnt(26);
        for (int i = 0; i < n; ++i){
            if (s[i] != ' ' && i != n-1) {
                cnt[s[i]-'a']++;
            } else {
                if (i == n-1) {
                    cnt[s[i]-'a']++;
                    ++i;
                }
                long long l = i-ind;
                ind = i+1;
                long long tmp = arra(l,l);
                for (int i = 0; i < 26; ++i) {
                    if (cnt[i] > 1) {
                        tmp = tmp*inv_fac[cnt[i]]% MOD;
                    }
                }
                ans = ans * tmp %MOD;
                for(auto& cnt1 : cnt){
                    cnt1 = 0;
                }
            }
        }
        return ans;
    }
};

/**
 * 容斥原理
 *
 * 集合 A:
 * 集合 B:
 * 集合 C:
 *
 * 集合 A∩B:
 * 集合 A∩C:
 * 集合 B∩C:
 *
 * 集合 A∩B∩C:
 *
 * ∣A∪B∪C∣= |A| + |B| + |C| -(|A∩B|+|A∩C|+|B∩C|) + |A∩B∩C|
 * 数量更多的集合有类似规律；具有一般性
 */

/**
 * 朴素选择
 * lc.no.2930
 * @param n
 * @return
 */
//int stringCount(int n) {
//    if (n < 4) return 0;
//    long long tmp = (q_pow(25,n) * 3 % MOD + (long long)n * q_pow(25,n-1) % MOD - (q_pow(24,n) * 3 % MOD + (long long)n * q_pow(24,n-1) * 2 % MOD - q_pow(23,n) - (long long)n * q_pow(23,n-1) % MOD)) % MOD;
//    long long ans = (q_pow(26,n) - tmp) % MOD;
//    return (ans + MOD) % MOD;
//}

/**
 *  隔板法，板和球一起计总数
 *
 * lc.no.2929
 */
long long distributeCandies(int n, int l) {
    if (l * 3 + 1 <= n) return 0;
    long long tmp1 = (long long)(n+2)*(n+1)/2, tmp2 = 0;
    if (n-(l+1) >= 0) {
        tmp2 += (long long)(n-(l+1)+2)*(n-(l+1)+1)/2*3;
    }
    if (n-2*(l+1) >= 0) {
        tmp2 -= (long long)(n- 2*(l+1)+2)*(n- 2*(l+1) +1)/2*3;
    }
    return tmp1 - tmp2;
}

/**
 * __int128 的合理运用
 * https://leetcode.cn/problems/kth-smallest-instructions/description/
 * @param n
 * @param k
 * @return
 */
// 组合
__int128 comb_1(__int128 n, __int128 k) {
    __int128 tmp1 = 1, tmp2 = 1;
    for (int i = 0; i < k; ++i){
        tmp1 *= (__int128)(n-i);
        tmp2 *= (__int128)(i+1);
    }
    return tmp1/tmp2;
}

string kthSmallestPath(vector<int>& d, int k) {
    int m = d[0], n = d[1];
    int l = m+n;
    string s(l,'H');
    // cnt1:v  cnt2:h
    int cnt1 = 0, cnt2 = 0;
    // 枚举最大
    while (1){
        long long tmp = 0;
        for (int i = m-1-cnt1; i < l; ++i) {
            tmp += comb_1(i,i-m+1+cnt1);
            if (tmp > k) {
                s[l-1-i] = 'V';
                k -= (tmp-comb_1(i,i-m+1+cnt1));
                ++cnt1;
                break;
            } else if (tmp == k){
                for (int j = l-1-i; j < l-1-i+m-cnt1; ++j){
                    s[j] = 'V';
                }
                return s;
            }
        }
    }
    return s;
}

/**
 * 容斥原理 + 二分； 通用模板
 * https://leetcode.cn/problems/ugly-number-iii/solutions/586670/cer-fen-jie-fa-zhe-dao-ti-shi-zen-yao-be-b7r9/
 * @param c
 * @param k
 * @return
 */
long long findKthSmallest(vector<int>& c, int k) {
    int n = c.size();
    vector<int> path;
    vector<vector<vector<int>>> a(n+1);
    function<void(int)> dfs = [&](int i) {
        if (i == n) {
            a[path.size()].emplace_back(path);
            return;
        }
        dfs(i + 1);
        path.emplace_back(c[i]);
        dfs(i + 1);
        path.pop_back();
    };
    dfs(0);
    vector<vector<ll>> f(n+1);
    for (int i = 1; i <=n; ++i) {
        for(auto& b : a[i]) {
            ll d = 1;
            for (auto& b1 : b) {
                d = lcm(d,(ll)b1);
            }
            f[i].emplace_back(d);
        }
    }

    ll labc = f[n][0];
    ll mn = *min_element(c.begin(),c.end());
    // 这里用 lambda 捕获计算好的最小公倍数，避免重复计算
    const auto countLessEqual = [&] (long long x) -> long long {
        ll sum = 0;
        for (int i = 1; i <= n; ++i) {
            for (auto & f1 : f[i]) {
                sum += (i%2 ? 1 : (-1)) * (x/f1);
            }
        }
        return sum;
    };
    // 和 878 题一样，这里可以对 a、b、c 的最小公倍数做除法并取余数来优化算法的效率，
    // 简单来说就是每 lcm(a,b,c) 个连续整数中，
    // 就有 f(lcm(a,b,c)) 个丑数，具有周期性
    const long long m = countLessEqual(labc);
    const long long q = k / m, r = k % m;
    long long hi = min(labc, r * mn);
    long long lo = 0,ans = hi;
    while (lo <= hi) {
        const long long mi = (lo + hi) / 2;
        if (countLessEqual(mi) < r) {
            lo = mi + 1;
        } else {
            ans = min(ans,mi);
            hi = mi-1;
        }
    }
    return lo + q * labc;
}

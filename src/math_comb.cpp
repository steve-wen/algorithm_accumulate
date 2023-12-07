#include <bits/stdc++.h>

using namespace std;

/**
* 组合数学
*/

/**
 * 组合数学 逆元
 */
const int MOD = 1'000'000'007;
const int MX = 100'000; // C(n,k) n

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

long long comb(int n, int k) {
    return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD;
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
 * |A| + |B| + |C| -(|A∩B|+|A∩C|+|B∩C|) + |A∩B∩C|
 */

/**
 * 朴素选择
 * lc.no.2930
 * @param n
 * @return
 */
int stringCount(int n) {
    if (n < 4) return 0;
    long long tmp = (q_pow(25,n) * 3 % MOD + (long long)n * q_pow(25,n-1) % MOD - (q_pow(24,n) * 3 % MOD + (long long)n * q_pow(24,n-1) * 2 % MOD - q_pow(23,n) - (long long)n * q_pow(23,n-1) % MOD)) % MOD;
    long long ans = (q_pow(26,n) - tmp) % MOD;
    return (ans + MOD) % MOD;
}

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

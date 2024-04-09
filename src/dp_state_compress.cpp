#include <bits/stdc++.h>

using namespace std;

/**
*  状压 dp
*  状态压缩
*  数据范围很小 -> 暗示可以用状压之类的算法
*  结合位运算
*/

/**
 * 子集状压 dp , 结合位运算
 * 数据范围很小 -> 暗示可以用状压之类的算法
 * 集合长度转换为 位数， 位 1 表示取，0 表示不取
 * i : 分成 i 个子序列， j : i 个子序列形成的集合
 * f[i][j] : 集合 j 分成 i 个子序列时， 最大子序列的最小值 ： f[i+1][j] = min(f[i+1][j], max(f[i][j^s],sum[s]))
 * lc.no.2305 公平分发饼干
 * @param c
 * @param k
 * @return
 */
int distributeCookies(vector<int> &c, int k) {
    int n = c.size();
    vector<int> sum(1<<n);
    for (int i = 0; i < (1<<n); ++i) {
        for (int j =0; j <  n; ++j) {
            if ((i>>j)&1) sum[i] += c[j];
        }
    }

    vector<vector<int>> f(k, vector<int>(1<<n));
    f[0] = sum;
    for (int i = 0; i < k-1;++i) {
        for (int j = 0; j < (1<<n); ++j) {
            f[i+1][j] = 1e6;
            for (int s= j; s > 0; s = ((s-1)&j)) {
                f[i+1][j] = min(f[i+1][j], max(f[i][j^s],sum[s]));
            }
        }
    }
    return f[k-1][(1<<n)-1];
}

/**
 * f[i] : 集合 i 通过商品调配之后，所有元素均为 0, 最少需要几次商品调配
 * 枚举 i 的子集 j 和补集 i^j, 如果 sum[j] == 0, 则可以转移
 * f[i] = min(f[i],f[j]+f[i^j])
 * 时间复杂度 O(3^n)
 * https://leetcode.cn/contest/zj-future2022/problems/NBCXIp/
 * @param d
 * @return
 */
int minTransfers(vector<vector<int>> &d) {
    const int n = 12, m = 1 << n;
    vector<int> cnt(n);
    for (auto &d1: d) {
        cnt[d1[0]] -= d1[2];
        cnt[d1[1]] += d1[2];
    }
    vector<int> f(m);
    for (int i = 1; i < m; ++i) {
        int sum = 0;
        for (int j = 0; j < n; ++j)
            if (i >> j & 1) sum += cnt[j];
        if (sum) f[i] = 20; // 非法情况
        else {
            f[i] = __builtin_popcount(i) - 1; // 默认最大初值
            for (int j = i; j > 0; j = (j - 1) & i) // j = (i - 1) & i (只遍历真子集); j = i, 遍历包含集合本身
                f[i] = min(f[i], f[j] + f[i ^ j]);
        }
    }
    return f[m - 1];
}

/**
 * 子集状压 dp
 * lc.no.2572
 */
class Solution {
    static constexpr int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}; // 质数
    static constexpr int MOD = 1e9 + 7, MX = 30, N_PRIMES = 10, M = 1 << N_PRIMES;
public:
    int squareFreeSubsets(vector<int> &nums) {
        int sf2mask[MX + 1]{}; // sf2mask[i] 为 i 的质因子集合（用二进制表示）
        for (int i = 2; i <= MX; ++i)
            for (int j = 0; j < N_PRIMES; ++j) {
                int p = PRIMES[j];
                if (i % p == 0) {
                    if (i % (p * p) == 0) { // 有平方因子
                        sf2mask[i] = 0;
                        break;
                    }
                    sf2mask[i] |= 1 << j; // 把 j 加到集合中
                }
            }

        int cnt[MX + 1]{}, pow2 = 1;
        for (int x : nums)
            if (x == 1) pow2 = pow2 * 2 % MOD; // 1, 取或者不取
            else ++cnt[x];

        long f[M]{pow2}; // f[j] 表示 `恰好组成` 质数集合 j 的方案数，其中用 1 组成空质数集合的方案数为 pow2
        for (int x = 2; x <= MX; ++x) {
            int mask = sf2mask[x], c = cnt[x];
            if (mask && c) {
                int other = (M - 1) ^ mask, j = other; // mask 的补集 other
                do { // 枚举 other 的子集 j
                    f[j | mask] = (f[j | mask] + f[j] * cnt[x]) % MOD; // 不选 mask + 选 mask
                    j = (j - 1) & other;
                } while (j != other);
            }
        }
        return accumulate(f, f + M, -1L) % MOD; // -1 表示去掉空集（nums 的空子集）
    }
};

/**
 *  记忆化搜索 + 状压
 *  lc.no.2741
 *  思想转换 : 排列 -> 遍历枚举集合里的合适元素
 *  dfs(i,j) 表示当前可以选的下标集合为 i, 上一个数的下标是 j
 * @param a
 * @return
 */
int specialPerm(vector<int>& a) {
    int MOD = 1e9+7, n = a.size();
    int m = (1<<n) - 1;
    //long memo[m+1][n+1];
    long memo[17000][20];
    memset(memo,-1,sizeof(memo));
    function<long(int,int)> dfs = [&](int i, int j){
        if (i == 0) return 1L;
        if (memo[i][j] != -1) return memo[i][j];
        long& res = memo[i][j];
        res = 0;
        for (int k = 0; k < n; ++k) {
            if ((i >> k & 1) && (a[k] % a[j] == 0 || a[j] % a[k] == 0)) {
                res += dfs(i ^ 1 << k,k);
            }
        }
        return res;
    };
    long ans = 0;
    for (int k = 0; k < n; ++k) {
        ans += dfs(m^ 1<<k, k);
    }
    return ans%MOD;
}

/**
 *  记忆化搜索 + 状压
 *  思想转换 : 排列 -> 遍历枚举集合里的合适元素
 *  dfs(i,j,l) 表示当前可以选的下标集合为 i, 上一个数的下标是 j, 本次是第 l 次选
 *  https://leetcode.cn/problems/maximize-score-after-n-operations/description/
 * @param a
 * @return
 */
int maxScore(vector<int>& a) {
    int n = a.size();
    int m = (1<<n) - 1;
//    long long memo[m+1][n+1][n+2];
    long long memo[17000][20][20];
    memset(memo,-1,sizeof(memo));
    function<long long (int,int,int)> dfs = [&](int i, int j,int l){
        if (i == 0) return 0LL;
        if (memo[i][j][l] != -1) return memo[i][j][l];
        auto& res = memo[i][j][l];
        res = 0;
        for (int k = 0; k < n; ++k) {
            if (i >> k & 1 ) {
                if (l %2 == 0) {
                    res = max(res,gcd(a[k],a[j]) *(l/2)+dfs(i ^ 1 << k,k,l+1));
                } else {
                    res = max(res,dfs(i ^ 1 << k,k,l+1));
                }
            }
        }
        return res;
    };
    long long ans = 0;
    for (int k = 0; k < n; ++k) {
        ans = max(ans,dfs(m^ 1<<k, k,2));
    }
    return ans;
}

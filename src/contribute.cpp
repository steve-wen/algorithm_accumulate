#include <bits/stdc++.h>

using namespace std;

/**
*  贡献法
*/

/**
 * 贡献法 + 增量法(结合理解)
 * 求最大/最小与顺序无关 -> 排序 (有序是很好的性质)
 * 手玩，从枚举开始推公式(单个贡献, 规律增量)
 * lc.no.2681
 * @param a
 * @return
 */
int sumOfPower(vector<int>& a) {
    long long MOD = 1e9+7;
    long long ans = 0, s = 0;
    int n = a.size();
    sort(a.begin(),a.end());
    for (int i =0; i < n; ++i) {
        ans = (ans+((long long)a[i]*(long long)a[i]%MOD)*((long long)a[i]+s))%MOD;
        s = (s*2 + (long long)a[i])%MOD;
    }
    return ans;
}

/**
 * 贡献法 + 二维 0-1 背包
 * 贡献法 : 考虑单个/每个元素的贡献；然后累加贡献
 * 二维 0-1 背包 ： 有两个约束条件 ： 1，背包容量 2，选取的物品数量
 * 时间复杂度: O(n^3)
 * https://leetcode.cn/problems/find-the-sum-of-the-power-of-all-subsequences/description/
 * @param a
 * @param k
 * @return
 */

const int MOD = 1'000'000'007;
const int MX = 100'000; // C(n,k) n

// 快速幂取 MOD
long long q_pow_1(long long x, int n) {
    long long res = 1;
    for (; n > 0; n /= 2) {
        if (n % 2) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

int sumOfPower_1(vector<int>& a, int k) {
    int n = a.size();
    long long memo[100][100][100];
    memset(memo,-1,sizeof(memo));
    // i 表示 0 - n-1；j 表示 容量为 j; l 表示选取的物品数量/数组长度 为 l
    // f[i][j][l] 表示 从 0 - n-1, 恰好选出 l 个数 且 和为 j 的方案数
    function<long long (int,int,int)> dfs = [&](int i, int j, int l){
        if (l < 0) return (long long)0;
        if (i < 0) {
            if (j == 0 && l == 0) return (long long)1;
            return (long long)0;
        }
        if (memo[i][j][l] != -1) return memo[i][j][l];
        long long& res = memo[i][j][l];
        res = 0;
        if (a[i] > j) {
            res = (res+dfs(i-1,j,l))%MOD;
        } else {
            res = (res+dfs(i-1,j,l))%MOD;
            res = (res +dfs(i-1,j-a[i],l-1))%MOD;
        }
        return res;
    };

    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        long long cnt = dfs(n-1,k,i);
        ans = (ans+ cnt * q_pow_1(2,n-i))%MOD;
    }
    return ans;
}

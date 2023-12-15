#include <bits/stdc++.h>

using namespace std;

/**
*  状压 dp
*  状态压缩
*/

/**
 * 子集状压 dp , 结合位运算
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

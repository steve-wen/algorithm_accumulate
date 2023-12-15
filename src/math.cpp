#include <bits/stdc++.h>

using namespace std;

/**
* 数论
*/

/**
 * 欧拉筛(线性筛) O(n)
 * MX ：数的大小  primes : 质数数组
 * lc.no.2523
 */
const int MX = 1e6;
vector<int> primes;

int init = []() {
    bool np[MX + 1]{};
    for (int i = 2; i <= MX; ++i) {
        if (!np[i]) primes.push_back(i);
        for (int p: primes) {
            if (i * p > MX) break;
            np[i * p] = true;
            if (i % p == 0) break;
        }
    }
    primes.push_back(MX + 1);
    primes.push_back(MX + 1); // 保证下面下标不会越界
    return 0;
}();

class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        int p = -1, q = -1;
        int i = lower_bound(primes.begin(), primes.end(), left) - primes.begin();
        for (; primes[i + 1] <= right; ++i)
            if (p < 0 || primes[i + 1] - primes[i] < q - p) {
                p = primes[i];
                q = primes[i + 1];
            }
        return {p, q};
    }
};

/**
 * 分解质因数
 * oi-wiki, 分解质因数
 * 最简单的算法即为从 [2, N^(1/2)] 进行遍历, O(N^(1/2))。
 */
vector<int> breakdown(int N) {
    vector<int> result;
    for (int i = 2; i * i <= N; i++) {
        if (N % i == 0) {  // 如果 i 能够整除 N，说明 i 为 N 的一个质因子。
            while (N % i == 0) N /= i;
            result.push_back(i);
        }
    }
    if (N != 1) {  // 说明再经过操作之后 N 留下了一个素数
        result.push_back(N);
    }
    return result;
}

/**
 * gcd 最大公约数
 * 欧几里得算法
 * y >= x 时， gcd(x,y) = gcd(x,y mod x)
 * 更相减损术
 * y >= x 时，有 ：
 * gcd(x,y) = gcd(x,y-x)
 * gcd(x,x+y) = gcd(x,y)
 * Stein 算法的优化
 * 若 x/2 且 y/2 , gcd(x,y) = 2gcd(x/2, y/2)
 * 否则若 x/2 (或 y/2), gcd(x,y) = gcd(x/2, y)
 * lc.no. 2543
 */

bool isReachable(int x, int y) {
    return (gcd(x,y) & gcd(x,y)-1) == 0;
}

/**
* gcd, 多个数的最大公约数, 最小公倍数同理
*/
int gcdVector(vector<int> nums){
    int gcd_all = 0;
    for (auto& x : nums){
        gcd_all = gcd(gcd_all,x);
    }
    return gcd_all;
}

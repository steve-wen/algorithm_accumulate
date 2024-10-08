#include <bits/stdc++.h>

using namespace std;
#define ll long long

/**
*  背包 dp
 *  可直接用递推式写出 f[i][j],此类型少用 记忆化
 * 子序列 dp 的思考套路
 * 1. 0-1 背包， 选的子序列的相邻元素是无关的 [相邻无关]
 * 2. LIS(最长上升子序列) 选的子序列的相邻元素是相关的 [相邻相关]
 *
*/

/**
 * 0-1 背包 模板代码
 * c : 背包容量
 * w[i] : 第 i 个物品的体积
 * v[i] : 第 i 个物品的价值
 * 每种物品最多只能选一次
 * 返回: 所选物品体积不超过 c 的前提下, 所能得到的最大价值和
 */

int zero_one_bag(int c, vector<int> w, vector<int> v){
    int n = w.size();
    int memo[1001][1001];
    function<int(int,int)> dfs = [&](int i, int j){
        if (i < 0) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        if (w[i] > j) {
            res = dfs(i-1,j);
        } else {
            res = max(dfs(i-1,j), dfs(i-1,j-w[i])+v[i]);
        }
        return res;
    };
    return dfs(n-1,c);
}

/**
 * 贡献法 + 二维 0-1 背包
 * 贡献法 : 考虑单个/每个元素的贡献；然后累加贡献
 * 恰好选取长度为 l 且 和为 k
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
long long q_pow_2(long long x, int n) {
    long long res = 1;
    for (; n > 0; n /= 2) {
        if (n % 2) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

int sumOfPower(vector<int>& a, int k) {
    int n = a.size();
    int f[n][n+1][k+1];
    memset(f,0,sizeof(f));
    f[0][0][0] = 1;
    if (a[0] <= k){
        f[0][1][a[0]] = 1;
    }
    for (int i =1; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for(int l = 0; l <= k; ++l) {
                f[i][j][l] = (f[i][j][l]+f[i-1][j][l])%MOD;
                if (l >= a[i] && j >= 1) {
                    f[i][j][l] = (f[i][j][l]+f[i-1][j-1][l-a[i]])%MOD;
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        long long cnt = f[n-1][i][k];
        ans = (ans+ cnt * q_pow_2(2,n-i))%MOD;
    }
    return ans;
}

/**
 * 逆向思维 : +二维 0-1 背包; 考虑第 i 个物品 选/不选
 * f[i][j] 从 0 - i 为止的 sum 为 j 的方案数
 * https://leetcode.cn/problems/number-of-great-partitions/solutions/2032009/ni-xiang-si-wei-01-bei-bao-fang-an-shu-p-v47x/
 * @param a
 * @param k
 * @return
 */
int countPartitions(vector<int>& a, int k) {
    ll sum = accumulate(a.begin(),a.end(),0LL);
    if (sum < k*2) return 0;
    ll n = a.size();
    vector<vector<ll>> f(n,vector<ll>(k+1));
    f[0][0] = 1;
    if (a[0] < k) {
        f[0][a[0]] = 1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            f[i][j] = (f[i][j]+f[i-1][j])%MOD;
            if (j >= a[i]) {
                f[i][j] = (f[i][j]+f[i-1][j-a[i]])%MOD;
            }
        }
    }
    ll tmp = 0;
    for (int i = 0; i < k; ++i) {
        tmp = (tmp+f[n-1][i])%MOD;
    }
    ll ans = ((q_pow_2(2,n)-tmp*2)%MOD+MOD)%MOD;
    return ans;
}

/**
 * 0-1 背包；考虑第 i 个选/不选；此种遍历方式包含（恰好和小于等于）
 * https://leetcode.cn/problems/ones-and-zeroes/description/
 * @param s
 * @param m
 * @param n
 * @return
 */
int findMaxForm(vector<string>& s, int m, int n) {
    int l = s.size();
    int f[l][m+1][n+1];
    memset(f,0,sizeof(f));
    vector<int> cnt0(l),cnt1(l);
    for (int i = 0; i < l; ++i) {
        cnt0[i] = count(s[i].begin(),s[i].end(),'0');
        cnt1[i] = count(s[i].begin(),s[i].end(),'1');
    }
    if(cnt0[0] <= m && cnt1[0] <= n) {
        f[0][cnt0[0]][cnt1[0]] = 1;
    }
    for (int i = 1; i < l; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= n; ++k) {
                f[i][j][k] = f[i-1][j][k];
                if (j >= cnt0[i] && k >= cnt1[i]) {
                    f[i][j][k] = max(f[i-1][j-cnt0[i]][k-cnt1[i]]+1,f[i][j][k]);
                }
            }
        }
    }
    int mx = 0;
    for (int j = 0; j <= m; ++j) {
        for (int k = 0; k <= n; ++k) {
            mx = max(mx,f[l-1][j][k]);
        }
    }
    return mx;
}

/**
 * 定义 f[i][j][k] 为考虑前 i 件物品，使用人数不超过 j，所得利润至少/至多/恰好为 k 的方案数
 * 学会做这三类变形题
 * https://leetcode.cn/problems/profitable-schemes/solutions/820111/gong-shui-san-xie-te-shu-duo-wei-fei-yon-7su9/
 * @param m
 * @param c
 * @param g
 * @param p
 * @return
 */
int profitableSchemes(int m, int c, vector<int>& g, vector<int>& p) {
    int n = g.size(), mod = 1e9+7;
    vector<vector<vector<int>>> f(n,vector<vector<int>>(m+1,vector<int>(c+1)));
    f[0][0][c] = 1;
    if (g[0] <= m ) {
        f[0][g[0]][max(c-p[0],0)] = 1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 0; k <= c; ++k) {
                f[i][j][k] = (f[i][j][k]+f[i-1][j][k])%mod;
                if (j >= g[i]) { // 改
                    if (k == 0) {
                        for (int l = 0; l <= min(p[i],c); ++l){
                            f[i][j][k] = (f[i][j][k]+f[i-1][j-g[i]][l])%mod;
                        }
                    } else if(k+p[i] <= c) {
                        f[i][j][k] = (f[i][j][k]+f[i-1][j-g[i]][k+p[i]])%mod;
                    }
                }
            }
        }
    }
    ll sum = 0;
    for (int j = 0; j <= m; ++j) {
        sum = (sum+f[n-1][j][0])%mod;
    }
    return sum%mod;
}

/**
 * 二维 0-1 背包;
 * 注意 用 unordered_map<int,int> mp[51][51]; map 数组记忆化 针对大的数值
 * 注意这种灵活的记忆化方式
 * 注意 枚举以哪个下标为终点/起点
 * i : 当前下标， j : 剩余的次数，长度,  v : 当前最小能量值
 * mp[i][j][v]: 在 i 坐标时，剩余次数为 j , 当前最小能量值为 v 的情况下的能量和
 * https://leetcode.cn/problems/find-the-sum-of-subsequence-powers/description/
 * @param a
 * @param k
 * @return
 */
int sumOfPowers(vector<int>& a, int k) {
    int n = a.size();
    sort(a.begin(),a.end());
    // map 数组记忆化
    unordered_map<int,int> mp[51][51];
    int mod = 1e9+7;

    function<int(int,int,int)> dfs = [&](int i,int j, int v) {
        if (j == 0) {
            if (i >= 0) {
                return v;
            } else {
                return 0;
            }
        }
        if (mp[i][j].count(v)) {
            return mp[i][j][v];
        }
        int& res = mp[i][j][v];
        for (int l = i-1; l >= max(j-1,0); --l) {
            res = (res+ dfs(l,j-1,min(v,abs(a[i]-a[l])))%mod)%mod;
        }
        return res;
    };

    long long ans = 0;

    // 枚举终点
    for (int i = n-1; i >=k-1; --i) {
        ans = (ans + dfs(i,k-1,1e9)%mod)%mod;
    }
    return ans;
}



/**
 * 完全 背包 模板代码
 * c : 背包容量
 * w[i] : 第 i 个物品的体积
 * v[i] : 第 i 个物品的价值
 * 每种物品可以无限次重复选
 * 返回: 所选物品体积不超过 c 的前提下, 所能得到的最大价值和
 */

int unbounded_bag(int c, vector<int> w, vector<int> v){
    int n = w.size();
    int memo[1001][1001];
    function<int(int,int)> dfs = [&](int i, int j){
        if (i < 0) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        if (w[i] > j) {
            res = dfs(i-1,j);
        } else {
            res = max(dfs(i-1,j), dfs(i,j-w[i])+v[i]);
        }
        return res;
    };
    return dfs(n-1,c);
}

/**
 * 完全背包的 递推
 * https://leetcode.cn/problems/form-largest-integer-with-digits-that-add-up-to-target/solutions/824611/gong-shui-san-xie-fen-liang-bu-kao-lu-we-uy4y/
 * @param a
 * @param t
 * @return
 */
string largestNumber(vector<int>& a, int t) {
    vector<string> f(t+1);
    unordered_map<int,int> mp;
    for (int i = 0; i < 9; ++i) {
        if (a[i] <= t) {
            int k = i+1;
            f[a[i]] = to_string(k);
            mp[a[i]] = i;
        }
    }
    for (int i = 1; i <= t; ++i) {
        for (auto& p : mp) {
            auto j = p.second;
            if (a[j] <= i && (!f[i-a[j]].empty() || i-a[j] == 0)) {
                string s = f[i-a[j]] + f[a[j]];
                if (s.size() > f[i].size()) {
                    f[i] = s;
                } else if (s.size() == f[i].size()) {
                    sort(s.rbegin(),s.rend());
                    if (s > f[i])
                        f[i] = s;
                }
            }
        }
    }
    return f[t].empty() ? "0" : f[t];
}

/**
 * 多重背包
 * t : 背包容量
 * a[i][0] : 第 i 种物品的数量
 * a[i][1] : 第 i 种物品的单价
 * 每种物品可以在数量范围内重复选
 * 返回: 所选物品价值恰好等于 t 的前提下, 所能得到的方案数
 * https://leetcode.cn/problems/number-of-ways-to-earn-points/description/
 * @param t
 * @param a
 * @return
 */
int waysToReachTarget(int t, vector<vector<int>>& a) {
    int n = a.size(), mod = (int)1e9 + 7;
    int memo[51][1001];
    memset(memo,-1,sizeof(memo));
    function<int(int, int)> dfs = [&](int i, int j){
        if (i < 0) {
            if (j == 0) return 1;
            else return 0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = 0;
        int a1 = a[i][0], a2 = a[i][1];
        for (int k = 0; k <= min(a1, j/a2); ++k) {
            res = (res + dfs(i-1,j-k*a2) % mod) % mod;
        }
        return res;
    };
    return dfs(n-1,t);
}

/**
 * 分组背包
 * 同一组内的物品至多/恰好选一个。
 * 可以返回 1: 所选物品价值恰好等于 t 的前提下, 是否有成功的方案，成功返回 1, 否则返回 0
 *         2: 所选物品价值恰好等于 t 的前提下, 能选的方案数总和
 * 时间复杂度： O(k * m * n), m = a.size(), n = a[0].size()
 * https://leetcode.cn/problems/minimize-the-difference-between-target-and-chosen-elements/description/
 * @param a
 * @param t
 * @return
 */
int minimizeTheDifference(vector<vector<int>>& a, int t) {
    int m = a.size(), n = a[0].size();
    int mn = 0, mx = 0;
    for (int i = 0; i < m; ++i) {
        sort(a[i].begin(), a[i].end());
    }
    for (int i = 0; i < m; ++i) {
        mn += a[i][0];
        mx += a[i][n-1];
    }
    int memo[71][5000];
    memset(memo,-1, sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j) {
        if (i < 0) {
            if (j == 0) return 1;
            return 0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = 0;
        for (int k = 0; k < n; ++k) {
            if (j-a[i][k] >= 0) {
                res = max(res,dfs(i-1,j-a[i][k]));
            }
        }
        return res;
    };
    if (mx <= t) return t-mx; // 注意特判,减少部分时间
    if (mn >= t) return mn -t;
    int ans = 4900;
    for (int i = t; i >=mn; --i) {
        if (dfs(m-1,i) == 1) {
            ans = t-i;
            break;
        }
    }
    for (int i = t+1; i <= mx; ++i) {
        if (dfs(m-1,i) == 1) {
            ans = min(ans,i-t);
            break;
        }
    }
    return ans;
}

/**
 * 分组背包
 * 同一组内的物品可以选数量范围内的任意个。
 * 可以返回 1: 所选物品数量等于 k 的前提下， 物品的最大和/最大价值
 * 时间复杂度： O(k * m * n), m = p.size(), n = p[0].size()
 * https://leetcode.cn/problems/maximum-value-of-k-coins-from-piles/description/
 * @param a
 * @param t
 * @return
 */
int maxValueOfCoins(vector<vector<int>>& p, int k) {
    int n = p.size();
    int memo[11][11];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j) {
        if (j == 0 || i < 0) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = dfs(i-1,j);
        int pre = 0;
        for (int l = 0; l < min(j,(int)p[i].size()); ++l) {
            pre += p[i][l];
            res = max(res,dfs(i-1,j-l-1)+pre);
        }
        return res;
    };
    return dfs(n-1,k);
}

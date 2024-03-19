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

/**
 * 贡献法 + 线段树 (返回 距离 val 最近的 大于/小于 val 的数的下标 index)
 * 前缀和的前缀和; 且需要理解思想, 每个 strength[i] 作为所在数组最小值时的贡献
 * 巫师的总力量和
 * https://leetcode.cn/problems/sum-of-total-strength-of-wizards/description/
 */
class Solution_segment_contribute {
public:
    vector<int> mx;

    // 维护
    void maintain(int o) {
        mx[o] = min(mx[o * 2],mx[o * 2 + 1]);
    }
    // 初始化 o 从 1 开始
    void build(vector<int> &a, int o, int l, int r) {
        // 边界条件
        if (l == r) {
            mx[o] = a[l - 1];
            return;
        }
        int m = (l + r) / 2;
        // 左儿子节点编号 o*2, 右儿子节点编号 o*2+1
        build(a, o * 2, l, m);
        build(a, o * 2 + 1, m + 1, r);
        // 维护
        maintain(o);
    }

    // 线段树上二分 获取下标 ind, L是左边界
    int index_1(int o, int l, int r, int L, int R, int val) {
        if (mx[o] > val || L > R) return 1e5+2;
        if (l == r) return l;
        int mid = (l+r)/2;
        if (L <= mid && mx[o*2] <= val && R >= mid) {
            auto ind = index_1(o*2, l, mid,L,R, val);
            if (ind != (int)1e5+2) return ind;
        }
        return index_1(o*2+1, mid+1, r, L,R,val);
    }

    int index_2(int o, int l, int r, int L, int R, int val) {
        if (mx[o] >= val || L > R) return 1e5+2;
        if (l == r) return l;
        int mid = (l+r)/2;
        if (L <= mid && mx[o*2+1] < val && R >= mid) {
            auto ind = index_2(o*2+1, mid+1, r,L,R, val);
            if (ind != (int)1e5+2) return ind;
        }
        return index_2(o*2, l, mid, L,R,val);
    }

    int totalStrength(vector<int> &strength) {
        const int mod = 1e9 + 7;

        int n = strength.size();
        mx.resize(n*4);
        vector<int> left(n, -1); // left[i] 为左侧严格小于 strength[i] 的最近元素位置（不存在时为 -1）
        vector<int> right(n, n); // right[i] 为右侧小于等于 strength[i] 的最近元素位置（不存在时为 n）
        // 可用单调栈求下标
//        stack<int> st;
//        for (int i = 0; i < n; ++i) {
//            while (!st.empty() && strength[st.top()] >= strength[i]) {
//                right[st.top()] = i;
//                st.pop();
//            }
//            if (!st.empty()) left[i] = st.top();
//            st.push(i);
//        }
        build(strength,1,1,n);
        for (int i = 0; i < n; ++i) {
            auto ind1 = index_1(1,1,n,i+2,n,strength[i]);
            auto ind2 = index_2(1,1,n,1,i,strength[i]);
            right[i] = ind1 == 1e5+2 ? n : ind1-1;
            left[i] = ind2 == 1e5+2 ? -1 : ind2-1;
        }

        long s = 0L; // 前缀和
        vector<int> ss(n + 2); // 前缀和的前缀和
        for (int i = 1; i <= n; ++i) {
            s += strength[i - 1];
            ss[i + 1] = (ss[i] + s) % mod; // 注意取模后，下面计算两个 ss 相减，结果可能为负
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            long l = left[i] + 1, r = right[i] - 1; // [l,r] 左闭右闭
            long tot = ((i - l + 1) * (ss[r + 2] - ss[i + 1]) - (r - i + 1) * (ss[i + 1] - ss[l])) % mod;
            ans = (ans + strength[i] * tot) % mod; // 累加贡献
        }
        return (ans + mod) % mod; // 防止算出负数
    }
};


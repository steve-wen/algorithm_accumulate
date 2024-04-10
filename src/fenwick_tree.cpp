#include <bits/stdc++.h>

using namespace std;

/**
*  树状数组
*/

/**
 * 树状数组 (动态前缀和)
 * 解决问题 : 1.求数组中大于/小于某个数的个数,(且该数组在动态更新) : 离散化排序 + 树状数组 (只能全局查询)
            2. 求数组的前缀和/区间和 (与下标有关)：初始化树状数组(for 循环 update) + 树状数组
   与线段树区别 : 线段树 : 一个数组， 更新一个子数组的值（都加上一个数，把子数组内的元素取反，...）
               查询一个子数组的值（求和，求最大值）

   下标从 1 开始
 * https://leetcode.cn/problems/distribute-elements-into-two-arrays-ii/description/
 * @param a
 * @return
 */
class Fenwick {
    vector<int> tree;

public:
    Fenwick(int n) : tree(n) {}

    // 把下标为 i 的元素增加 1 (动态更新 +1)，下标从 1 开始
    // 每次 O(logn)
    void add(int i) {
        while (i < tree.size()) {
            tree[i] += 1;
            i += i & -i;
        }
    }

    void update(int i, int j) {
        while (i < tree.size()) {
            tree[i] += j;
            i += i & -i;
        }
    }

    // 返回下标在 [1,i] 的元素个数之和
    // 每次 O(logn)
    int pre(int i) {
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i &= i - 1;
        }
        return res;
    }
};

class Solution_Fenwick {
public:
    vector<int> resultArray(vector<int> &nums) {
        // 离散化 (以下标作为比较对象)
        auto sorted = nums;
        ranges::sort(sorted);
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        int m = sorted.size();

        vector<int> a{nums[0]}, b{nums[1]};
        // 树状数组
        Fenwick t1(m + 1), t2(m + 1);
        t1.add(ranges::lower_bound(sorted, nums[0]) - sorted.begin() + 1);
        t2.add(ranges::lower_bound(sorted, nums[1]) - sorted.begin() + 1);
        for (int i = 2; i < nums.size(); i++) {
            int x = nums[i];
            int v = ranges::lower_bound(sorted, x) - sorted.begin() + 1;
            int gc1 = a.size() - t1.pre(v); // greaterCount(a, v)
            int gc2 = b.size() - t2.pre(v); // greaterCount(b, v)
            if (gc1 > gc2 || gc1 == gc2 && a.size() <= b.size()) {
                a.push_back(x);
                t1.add(v);
            } else {
                b.push_back(x);
                t2.add(v);
            }
        }
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
};

/**
 * 树状数组
 * https://leetcode.cn/problems/range-sum-query-mutable/description/
 * @param a
 * @return
 */
class NumArray {
public:
    vector<int> tree;
    vector<int> tmp;
    // 初始化 O(nlogn)
    NumArray(vector<int>& nums) {
        int n = nums.size();
        tmp.resize(n,0);
        tree.resize(n+1);
        for (int i = 0; i < n; ++i) {
            update(i, nums[i]);
        }
    }

    // update/add O(logn)
    void update(int i, int v) {
        auto cnt = v-tmp[i];
        tmp[i] = v;
        ++i;
        while (i < tree.size()) {
            tree[i] += cnt;
            i += i & -i;
        }
    }
    // pre/query O(logn)
    int sumRange(int l, int r) {
        ++r;
        int res1 = 0, res2 = 0;
        while (l > 0) {
            res1 += tree[l];
            l &= l - 1;
        }
        while (r > 0) {
            res2 += tree[r];
            r &= r - 1;
        }
        return res2-res1;
    }
};

/**
 * 树状数组
 * https://leetcode.cn/problems/count-of-smaller-numbers-after-self/description/
 */
class Fenwick_1 {
    vector<int> tree;

public:
    Fenwick_1(int n) : tree(n) {}

    // 把下标为 i 的元素增加 1
    // 每次 O(logn)
    void add(int i) {
        while (i < tree.size()) {
            tree[i] += 1;
            i += i & -i;
        }
    }

    // 返回下标在 [1,i] 的元素之和
    // 每次 O(logn)
    int pre(int i) {
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i &= i - 1;
        }
        return res;
    }
};

vector<int> countSmaller(vector<int>& a) {
    int n = a.size();
    vector<int> ans(n);
    reverse(a.begin(),a.end());
    // 离散化, 处理下标
    auto b = a;
    ranges::sort(b);
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();

    // 树状数组
    Fenwick_1 t1(m + 1);
    for (int i = 0; i < n; ++i) {
        t1.add(ranges::lower_bound(b, a[i]) - b.begin() + 1);
        int x = a[i];
        int v = ranges::lower_bound(b, x) - b.begin();
        ans[i] = t1.pre(v);
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

/**
 * 树状数组
 * 注意 lower_bound, upper_bound 是否 +1 的合理运用
 * https://leetcode.cn/problems/number-of-pairs-satisfying-inequality/description/
 */
class Fenwick_2 {
    vector<int> tree;

public:
    Fenwick_2(int n) : tree(n) {}

    // 把下标为 i 的元素增加 1
    // 每次 O(logn)
    void add(int i) {
        while (i < tree.size()) {
            tree[i] += 1;
            i += i & -i;
        }
    }

    // 返回下标在 [1,i] 的元素个数之和
    // 每次 O(logn)
    int pre(int i) {
        int res = 0;
        while (i > 0) {
            res += tree[i];
            i &= i - 1;
        }
        return res;
    }
};

long long numberOfPairs(vector<int>& a1, vector<int>& a2, int d) {
    long long ans = 0;
    int n = a1.size();
    vector<int> a(n);
    for (int i =0; i < n; ++i) {
        a[i] = a1[i]-a2[i];
    }
    auto b = a;
    ranges::sort(b);
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();

    // 树状数组
    Fenwick_2 t1(m + 2);
    for (int i = 0; i < n; ++i) {
        int x = a[i]+d;
        int v = ranges::upper_bound(b, x) - b.begin();
        ans += (long long)t1.pre(v);
        t1.add(ranges::lower_bound(b, a[i]) - b.begin() + 1);
    }
    return ans;
}

/**
 * 差分树状数组
 * 支持区间修改, 区间查询
 * O(logn)
 */
class Fenwick_Diff {

public:
    vector<vector<int>> tree;
    Fenwick_Diff(int n) : tree(n+1,vector<int>(2)) {}

    // _add
    void _add(int i, int val) {
        int iv = i*val;
        while (i < tree.size()) {
            tree[i][0] += val;
            tree[i][1] += iv;
            i += i & -i;
        }
    }

    // a[l] 到 a[r] 增加 val
    // 1<=l<=r<=n
    void add(int l, int r, int val) {
        _add(l,val);
        _add(r+1,-val);
    }

    // 求前缀和 a[1] + ... + a[i]
    // 1<=i<=n
    int pre(int i) {
        int s0 = 0, s1 = 0, i0 =i;
        while (i > 0) {
            s0 += tree[i][0];
            s1 += tree[i][1];
            i &= i - 1;
        }
        return (i0+1)*s0 - s1;
    }

    // 求区间和 a[l] + ... + a[r]
    // 1<=l<=r<=n
    int query(int l, int r) {
        return pre(r)-pre(l-1);
    }
};

void test_Fenwick_Diff(vector<int>& a, int l, int r, int val, int& ans){
    int n = a.size();
    Fenwick_Diff t(n+1);
    t.add(l+1,r+1,val);
    ans = t.query(l+1,r+1);
}

/**
 * 差分树状数组
 * 支持单点修改, 区间查询最值
 * 可与 用单调队列,单调栈 有同样效果
 * https://leetcode.cn/problems/sliding-window-maximum/description/
 * O(log^2 (n))
 */
class Fenwick_Max {

public:
    vector<long long> tree;
    vector<long long> a;
    Fenwick_Max(long long n) : tree(n+1),a(n+1) {}

    // _add,update, 此时的 update 可以使得 a[i] 加上一个数值,变大或变小
    void update(long long i, long long val) {
        a[i] += val;
        while (i < tree.size()) {
            // 枚举受影响的区间
            tree[i] = a[i];
            for (long long j = 1; j < (i & -i); j *= 2) {
                tree[i] = max(tree[i], tree[i - j]);
            }
            i += i & -i;
        }
    }

    // 求区间和 a[l] + ... + a[r]
    // 1<=l<=r<=n
    long long getmax(long long l, long long r) {
        long long ans = -1e5; // 初始值，可根据题目设置
        while (r >= l) {
            ans = max(ans, a[r]);
            --r;
            for (; r - (r & -r) >= l; r -= (r & -r)) {
                // 注意，循环条件不要写成 r - lowbit(r) + 1 >= l
                // 否则 l = 1 时，r 跳到 0 会死循环
                ans = max(ans, tree[r]);
            }
        }
        return ans;
    }
};

vector<long long> mostFrequentIDs(vector<int>& b, vector<int>& f) {
    long long n = 1e5+2, m = b.size();
    vector<long long> ans(m);
    Fenwick_Max t(n);
    long long mx = 0;
    for (long long i = 0; i < m; ++i) {
        mx = max(mx,(long long)b[i]);
        // 注意 update
        t.update((long long)(b[i]+1),f[i]);
        ans[i] = t.getmax(1,mx+1);
    }
    return ans;
}

/**
 * 树状数组 getmax 优化 dp
 * https://leetcode.cn/problems/constrained-subsequence-sum/description/
 * @param b
 * @param k
 * @return
 */
int constrainedSubsetSum(vector<int>& b, int k) {
    int n = b.size();
    vector<int> f(n);
    f[0] = b[0];
    Fenwick_Max t(n);
    t.update(1,f[0]);
    for (int i =1; i <n; ++i) {
        if (i-k-1 >= 0) {
            t.update(i-k,-f[i-k-1]);
        }
        auto tmp = t.getmax(max(i-k,0)+1,i);
        tmp = max(0,(int)tmp);
        f[i] = tmp+b[i];
        t.update(i+1,f[i]);
    }
    int ans = f[0];
    for (int i = 0; i < n; ++i) {
        ans = max(ans,f[i]);
    }
    return ans;
}

int mx(vector<int> &nums) {
    int n = nums.size();

    // 树状数组
    Fenwick_Max t(n);
    t.a.resize(n+1);
    for (int i =0; i < n; ++i) {
        t.update(i+1,nums[i]);
    }
    int ans = 0;
    ans = t.getmax(5,7);
    return ans;
}

vector<int> maxSlidingWindow_1(vector<int>& nums, int k) {
    int n = nums.size();
    Fenwick_Max t(n);
    t.a.resize(n+1);
    for (int i =0; i < n; ++i) {
        t.update(i+1,nums[i]);
    }
    vector<int> ans(n-k+1);
    for (int i =0; i <= n-k; ++i) {
        ans[i] = t.getmax(i+1,i+k);
    }
    return ans;
}

/**
 * 树状数组，求 kth 小
 * 只能求全局 k 小值 且 静态
 * 时间复杂度 O(logn)
 */
// kth 小, 已正确；注意归纳
class Fenwick_kth {
    vector<int> tree;

public:
    Fenwick_kth(int n) : tree(n) {}

    // 把下标为 i 的元素增加 1 (动态更新 +1)
    // 若不离散化，即把元素本身 + 1, 此时 1. 元素不能有负数, 2. 数据范围不能过大；否则，进行离散化
    // 每次 O(logn)
    void add(int i, int val) {
        while (i < tree.size()) {
            tree[i] += val;
            i += i & -i;
        }
    }

    // 权值树状数组查询第 k 小， 返回的是相应的 i 值
    int kth(int k) {
        int sum = 0, x = 0;
        for (int i = log2(tree.size()); ~i; --i) {
            x += 1 << i;                    // 尝试扩展
            if (x >= tree.size() || sum + tree[x] >= k)  // 如果扩展失败
                x -= 1 << i;
            else
                sum += tree[x];
        }
        return x + 1;
    }
};

vector<int> kth(vector<int> &nums, int k) {
    // 离散化 (以下标作为比较对象)
    int n = nums.size();
    auto sorted = nums;
    ranges::sort(sorted);
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    int m = sorted.size();

    // 树状数组
    Fenwick_kth t(m + 1);
    vector<int> ans(n);
    for (int i =0; i < n; ++i) {
        auto a1 = nums[i];
        auto ind = ranges::lower_bound(sorted, a1) - sorted.begin()+1;
        t.add(ind,1);
        if (k > i+1) {
            ans[i] = -1;
        } else {
            ans[i] = sorted[t.kth(k)-1]; // 因为传入的 ind+1, 所以此处 t.kth(k)-1; sorted 是排序且去重后的数组
        }
    }

    return ans;
}



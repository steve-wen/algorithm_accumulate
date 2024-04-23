#include <bits/stdc++.h>

using namespace std;

/**
* segmentTree 线段树
*/

/**
 * lazy segment tree : lazy 线段树  (本质是递归) (区间更新 + 区间查询)
 *  0. 解决问题 ：1. 一个数组， 更新一个子数组的值（都加上一个数，把子数组内的元素取反，...）
 *              2. 查询一个子数组的值（求和，求最大值）
 *              3. index 二分; 查询 [L,R] 内第一个大于 val 的数的下标
 *  1. 两大思想：
 *      1.1 挑选 O(n) 个特殊区间，使得任意一个区间可以拆分为 O(log n) 个特殊区间 (用最近公共祖先思考)
 *          O(n) <= 4n, 分治思想， 满二叉树， 递归
 *      挑选 O(n) 个特殊区间， build
 *  2. lazy更新 / 延迟更新
 *     lazy tag : 用一个数组维护每个区间需要更新的值
 *     如果这个值 = 0 表示不需要更新
 *     如果这个值 != 0 表示更新操作在这个区间停住了， 不继续递归更新子区间了
 *
 *     如果后面又来了一个更新，破坏了有 lazy tag 的区间，那么这个区间就得继续递归更新了
 *
 *  3. 下标从 1 开始
 *
 *  to_do 作用理解？
 *
 */
// lc.no.2916
class Solution {
    vector<long> cnt1, to_do; // cnt1 区间段的数

    // 维护区间的增量
    void maintain(int o) {
        cnt1[o] = cnt1[o * 2] + cnt1[o * 2 + 1];
    }

    // 执行区间反转
    void do_(int o, int l, int r, int add) {
        cnt1[o] += (long)add * (r - l + 1) ;
        to_do[o] += add;
    }

    // 初始化线段树   o,l,r=1,1,n (节点编号，左端点，右端点)  (起点从 1 开始， 1 - n)  O(n)
    void build(vector<int> &a, int o, int l, int r) {
        // 边界条件
        if (l == r) {
            cnt1[o] = 0;
            return;
        }
        int m = (l + r) / 2;
        // 左儿子节点编号 o*2, 右儿子节点编号 o*2+1
        build(a, o * 2, l, m);
        build(a, o * 2 + 1, m + 1, r);
        // 维护
        maintain(o);
    }

    // 查询的同时做本次更新操作 （对指定区间加 1）
    long long query_and_add1(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            long long res = cnt1[o];
            do_(o, l, r, 1);
            return res;
        }

        int m = (l + r) / 2;
        int add = to_do[o];
        if (add != 0) {
            do_(o * 2, l, m, add);
            do_(o * 2 + 1, m + 1, r, add);
            to_do[o] = 0;
        }

        long long res = 0;
        if (L <= m) res += query_and_add1(o * 2, l, m, L, R);
        if (m < R)  res += query_and_add1(o * 2 + 1, m + 1, r, L, R);
        maintain(o);
        return res;
    }

    // 更新区间 [L,R], 更新 [L,R], [L,R]是常量   o,l,r=1,1,n  O(log n)， 此处 update 为 对选定区间 +1
    void update(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            do_(o, l, r,1);
            return;
        }
        int m = (l + r) / 2;
        int add = to_do[o];
        if (add != 0) {
            do_(o * 2, l, m, add);
            do_(o * 2 + 1, m + 1, r, add);
            to_do[o] = 0;
        }
        if (m >= L) update(o * 2, l, m, L, R);
        if (m < R) update(o * 2 + 1, m + 1, r, L, R);
        maintain(o);
    }

    // 查询区间 [L,R] 的和 / max 值 （查询的同时注意更新子区间）
    long query(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return cnt1[o];
        }
        int m = (l + r) / 2;
        int add = to_do[o];
        if (add != 0) {
            do_(o * 2, l, m, add);
            do_(o * 2 + 1, m + 1, r, add);
            to_do[o] = 0;
        }
        long res = 0;
        if (L <= m) res += query(o * 2, l, m, L, R);
        if (m < R)  res += query(o * 2 + 1, m + 1, r, L, R);
        maintain(o);
        return res;
    }

public:
    int sumCounts(vector<int> &a) {
        int mod = 1e9+7;
        int n = a.size();
        cnt1.resize(n * 4);
        to_do.resize(n * 4);

        long ans = 0, s = 0;
        unordered_map<int, int> mp;
        build(a,1,1,n);
        for (int i = 1; i <= n; i++) {
            int x = a[i - 1];
            int j = mp.count(x) ? mp[x] : 0;
//            s += query_and_add1(1, 1, n, j + 1, i) * 2 + (long)i - (long)j;
            s += query(1, 1, n, j + 1, i) * 2 + (long)i - (long)j;
            update(1, 1, n, j + 1, i);
            ans = (ans + s) % mod;
            mp[x] = i;
        }
        return ans;
    }
};

/*
 * lazy segment tree : lazy 线段树
 * lc.no.2569
 */

class LazySegmentTree1 {
    vector<int> cnt1, flip;

    // 维护区间 1 的个数
    void maintain(int o) {
        cnt1[o] = cnt1[o * 2] + cnt1[o * 2 + 1];
    }

    // 执行区间反转
    void do_(int o, int l, int r) {
        cnt1[o] = r - l + 1 - cnt1[o];
        flip[o] = !flip[o];
    }

    // 初始化线段树   o,l,r=1,1,n (节点编号，左端点，右端点)  (起点从 1 开始， 1 - n)  O(n)
    void build(vector<int> &a, int o, int l, int r) {
        // 边界条件
        if (l == r) {
            cnt1[o] = a[l - 1];
            return;
        }
        int m = (l + r) / 2;
        // 左儿子节点编号 o*2, 右儿子节点编号 o*2+1
        build(a, o * 2, l, m);
        build(a, o * 2 + 1, m + 1, r);
        // 维护
        maintain(o);
    }

    // 反转区间 [L,R], 更新 [L,R], [L,R]是常量   o,l,r=1,1,n  O(log n)
    void update(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            do_(o, l, r);
            return;
        }
        int m = (l + r) / 2;
        if (flip[o]) {
            do_(o * 2, l, m);
            do_(o * 2 + 1, m + 1, r);
            flip[o] = false;
        }
        if (m >= L) update(o * 2, l, m, L, R);
        if (m < R) update(o * 2 + 1, m + 1, r, L, R);
        maintain(o);
    }

public:
    vector<long long> handleQuery(vector<int> &nums1, vector<int> &nums2, vector<vector<int>> &queries) {
        int n = nums1.size();
        cnt1.resize(n * 4);
        flip.resize(n * 4);
        build(nums1, 1, 1, n);
        vector<long long> ans;
        long long sum = accumulate(nums2.begin(), nums2.end(), 0LL); // O(n)
        for (auto &q : queries) {
            if (q[0] == 1) update(1, 1, n, q[1] + 1, q[2] + 1);  // O(q log n)
            else if (q[0] == 2) sum += 1LL * q[1] * cnt1[1];
            else ans.push_back(sum);
        }
        return ans;
    }
};

/**
 * 线段树， segment tree (单点更新 + 区间查询)
 * lc.no.2286
 */
class BookMyShow {
public:
    vector<long> sum;
    vector<int> mn;
    int m,n;

    void maintain(int o) {
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
        mn[o] = min(mn[o * 2],mn[o * 2 + 1]);
    }

    void add(int o, int l, int r, int idx, int val) {
        if (l == r) {
            sum[o] += (long)val;
            mn[o] += val;
            return;
        }
        int mid = (l+r)/2;
        if (idx <= mid) add(o*2, l, mid, idx, val);
        else add(o*2 +1,mid+1, r, idx, val);
        maintain(o);
    }

    long query(int o, int l, int r, int L, int R) {
        if (L <=l && r <= R) {
            return sum[o];
        }
        int mid = (l+r)/2;
        long sum1 = 0;
        if (L <= mid) sum1 += query(o*2, l, mid, L, R);
        if (mid < R) sum1 += query(o*2+1, mid+1, r, L, R);
        return sum1;
    }

    int index(int o, int l, int r, int R, int val) {
        if (mn[o] > m-val) return 0;
        if (l == r) return l;
        int mid = (l+r)/2;
        if (mn[o*2] <= m-val) return index(o*2, l, mid, R, val);
        if (R > mid) return index(o*2+1, mid+1, r, R, val);
        return 0;
    }

    BookMyShow(int n1, int m1) {
        m = m1, n = n1;
        sum.resize(n * 4);
        mn.resize(n*4);

    }

    vector<int> gather(int k, int R) {
        auto i = index(1,1,n,R+1,k);
        if (i == 0) return {};
        add(1,1,n,i,k);
        auto seat = query(1,1,n,i,i);
        return vector<int>({i-1,(int)seat-k});

    }

    bool scatter(int k, int R) {
        auto left_seat = (long)(R+1) * (long)m - query(1,1,n,1,R+1);
        if (left_seat < k) return false;
        auto i = index(1,1,n,R+1,1);
        while (1) {
            if ((long)m - query(1,1,n,i,i) >= (long)k) {
                add(1,1,n,i,k);
                return true;
            } else {
                k -= (long)m - query(1,1,n,i,i);
                add(1,1,n,i,(long)m - query(1,1,n,i,i));
                ++i;
            }
        }
        return true;
    }
};

// segment tree 线段树 lc.no.2940
class Solution_segment {
public:
    vector<int> mx;

    // 维护; 注意是取 max 还是 min
    void maintain(int o) {
        mx[o] = max(mx[o * 2],mx[o * 2 + 1]);
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
    // 线段树二分获取最近下标的方法(val 的右边离 val 最近的下标
    // 注意是 max 还是 min
    int index1(int o, int l, int r, int L, int R, int val) {
        if (mx[o] < val || L > R) return 2e5+2; // 此处对 L，R 进行判断，处理一些边界情况
        if (l == r) return l;
        int mid = (l+r)/2;
        if (L <= mid && mx[o*2] >= val && R >= mid) {
            auto ind = index1(o*2, l, mid,L,R, val);
            if (ind != (int)2e5+2) return ind;
        }
        return index1(o*2+1, mid+1, r, L,R,val);
    }

    // 线段树上二分 获取下标 ind, L是左边界
    // 线段树二分获取最近下标的方法(val 的左边离 val 最近的下标)
    int index2(int o, int l, int r, int L, int R, int val) {
        if (mx[o] < val || L > R) return 2e5+2;
        if (l == r) return l;
        int mid = (l+r)/2;
        if (L <= mid && mx[o*2+1] >= val && R > mid) {
            auto ind = index2(o*2+1, mid+1, r, L,R,val);
            if (ind != (int)2e5+2) return ind;
        }
        return index2(o*2, l, mid,L,R, val);
    }
};
//vector<int> canSeePersonsCount(vector<int>& a) {
//    int n = a.size();
//    mx.resize(n*4);
//    build(a,1,1,n);
//    vector<int> ans(n);
//    vector<int> d(n),s(n+1);
//    for (int i = n-1; i >= 0; --i) {
//        auto ind2 = index2(1,1,n,1,i,a[i]);
//        if (ind2 != 2e5+2) {
//            d[ind2-1]++;
//        }
//    }
//    for (int i = 0; i < n; ++i) {
//        s[i+1] = s[i]+d[i];
//    }
//    for (int i = 0; i < n; ++i) {
//        auto ind1 = index1(1,1,n,i+2,n,a[i]); // k+2 代指实际下标 k+1 因为 o 从 1 开始
//        if (ind1 == 2e5+2) ind1 = n;
//        ans[i] = ind1-1-i-(s[ind1-1]-s[i+1]);
//    }
//    return ans;
//}

//vector<int> closestRoom(vector<vector<int>>& r, vector<vector<int>>& q) {
//    sort(r.begin(),r.end());
//    int n = r.size();
//    vector<int> a,b;
//    for (auto& r1 : r) {
//        a.emplace_back(r1[1]);
//        b.emplace_back(r1[0]);
//    }
//    mx.resize(n*4);
//    build(a,1,1,n);
//    vector<int> ans;
//    for(auto& q1 : q){
//        auto i = lower_bound(b.begin(),b.end(),q1[0])-b.begin();
//        auto ind1 = index1(1,1,n,i+1,n,q1[1]); // k+2 代指实际下标 k+1 因为 o 从 1 开始
//        auto ind2 = index2(1,1,n,1,i,q1[1]);
//        if (ind1 == 2e5+2 && ind2 == 2e5+2) {
//            ans.emplace_back(-1);
//        } else {
//            if (ind1 == 2e5+2) {
//                ans.emplace_back(b[ind2-1]);
//            } else if (ind2 == 2e5+2) {
//                ans.emplace_back(b[ind1-1]);
//            } else {
//                auto ind = abs(q1[0]-b[ind2-1]) <= abs(q1[0]-b[ind1-1]) ? b[ind2-1] : b[ind1-1];
//                ans.emplace_back(ind);
//            }
//        }
//
//    }
//    return ans;
//}
//
//int maxSumMinProduct(vector<int>& a) {
//    int n = a.size(), mod = 1e9+7;
//    vector<long long> s(n+1);
//    for (int i = 0; i < n; ++i) {
//        s[i+1] = s[i]+a[i];
//    }
//    mx.resize(n*4);
//    long long ans = 1;
//    build(a,1,1,n);
//    for (int i = 0; i < n; ++i) {
//        auto ind1 = index1(1,1,n,i+2,n,a[i]); // k+2 代指实际下标 k+1 因为 o 从 1 开始
//        auto ind2 = index2(1,1,n,1,i,a[i]);
//        if (ind1 == 2e5+2) ind1 = n+1;
//        if (ind2 == 2e5+2) ind2 = 0;
//        ans = max(ans,(s[ind1-1]-s[ind2])*(long long)a[i]);
//    }
//    return ans%mod;
//}

// segment tree + dp : 线段树 + 动态规划  lc.no.2407
class Solution4 {
    vector<int> mx;

    // 维护
    void maintain(int o) {
        mx[o] = max(mx[o * 2],mx[o * 2 + 1]);
    }

    void update(int o, int l, int r, int i, int val) {
        if (l == r) {
            mx[o] = val;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) update(o * 2, l, m, i, val);
        else update(o * 2 + 1, m + 1, r, i, val);
        maintain(o);
    }

    // 返回区间 [L,R] 内的最大值
    int query(int o, int l, int r, int L, int R) { // L 和 R 在整个递归过程中均不变，将其大写，视作常量
        if (L <= l && r <= R) return mx[o];
        int res = 0;
        int m = (l + r) / 2;
        if (L <= m) res = query(o * 2, l, m, L, R);
        if (R > m) res = max(res, query(o * 2 + 1, m + 1, r, L, R)); // 右边与左边取 max
        return res;
    }

public:
    int lengthOfLIS(vector<int> &nums, int k) {
        int u = *max_element(nums.begin(), nums.end());
        mx.resize(u * 4);
        for (int x: nums) {
            if (x == 1) {
                update(1, 1, u, 1, 1);
            } else {
                int res = 1 + query(1, 1, u, max(x - k, 1), x - 1);
                update(1, 1, u, x, res);
            }
        }
        return mx[1];
    }
};

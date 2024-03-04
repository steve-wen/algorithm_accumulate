#include <bits/stdc++.h>

using namespace std;

/**
*  树状数组
*/

/**
 * 树状数组 (动态前缀和)
 * 解决问题 : 1.求数组中大于/小于某个数的个数,(且该数组在动态更新) : 离散化排序 + 树状数组
            2. 求数组的前缀和/区间和 (与下标有关)：初始化树状数组(for 循环 update) + 树状数组
 * https://leetcode.cn/problems/distribute-elements-into-two-arrays-ii/description/
 * @param a
 * @return
 */
class Fenwick {
    vector<int> tree;

public:
    Fenwick(int n) : tree(n) {}

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

long long numberOfPairs(vector<int>& a1, vector<int>& a2, int d) {


}

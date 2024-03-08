#include <bits/stdc++.h>

using namespace std;

/**
*  并查集
*/

/**
 * https://leetcode.cn/problems/subarray-with-elements-greater-than-varying-threshold/description/
 * no.2334
 */

struct dsu {
    vector<size_t> fa, size;

    explicit dsu(size_t size_) : fa(size_), size(size_, 0) {
        iota(fa.begin(), fa.end(), 0);
    }

    size_t find(size_t x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    void unite(size_t x, size_t y) {
        x = find(x), y = find(y);
        fa[y] = x;
        size[x] += size[y]+1;
    }
};

class Solution {
public:
    int validSubarraySize(vector<int> &nums, int threshold) {
        int n = nums.size();

        dsu ds(n+1);
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int i, int j) { return nums[i] > nums[j]; });
        for (int i : ids) {
            ds.unite(i+1,i);
            if (nums[i] > threshold / ds.size[ds.find(i+1)]) return ds.size[ds.find(i+1)];
        }
        return -1;
    }
};

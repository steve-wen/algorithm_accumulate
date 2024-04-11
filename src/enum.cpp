#include <bits/stdc++.h>

using namespace std;

/**
 *  暴力枚举 (可适当剪枝)
 *  子集，组合，排列问题
*/

/**
 * 子集 ： 选/不选 以数组下标 ind 为例 ： 0，1，2 ... n-1
 * @param n
 * @return
 */
vector<vector<int>> func0(int n) {
    vector<int> ind(n);
    iota(ind.begin(), ind.end(), 0);
    vector<int> path;
    vector<vector<int>> ans;
    function<void(int)> dfs = [&](int i) {
        if (i == n) {
            ans.emplace_back(path);
            return;
        }
        dfs(i + 1);
        path.emplace_back(ind[i]);
        dfs(i + 1);
        path.pop_back();
    };
    dfs(0);
    return ans;
}

/**
 * 组合 : 1. 用 选/不选 做，以数组下标 ind 为例 ： 0，1，2 ... n-1
 * 组合长度为 k + 剪枝
 * @param n
 * @param k
 * @return
 */
vector<vector<int>> func1(int n, int k) {
    vector<int> ind(n);
    iota(ind.begin(), ind.end(), 0);
    vector<int> path;
    vector<vector<int>> ans;
    function<void(int)> dfs = [&](int i) {
        if (i == n) {
            if (path.size() == k) {
                ans.emplace_back(path);
            }
            return;
        }
        // 剪枝
        if(path.size()+n-i < k || path.size() > k) {
            return ;
        }
        dfs(i + 1);
        path.emplace_back(ind[i]);
        dfs(i + 1);
        path.pop_back();
    };
    dfs(0);
    return ans;
}

/**
 * 组合 : 2. 用 顺序循环遍历 做，以数组下标 ind 为例 ： 0，1，2 ... n-1
 * 组合长度为 k
 * @param n
 * @param k
 * @return
 */
vector<vector<int>> func2(int n, int k) {
    vector<int> ind(n);
    iota(ind.begin(), ind.end(), 0);
    vector<int> path;
    vector<vector<int>> ans;
    function<void(int)> dfs = [&](int i) {
        if (path.size() == k) {
            ans.emplace_back(path);
            return;
        }
        // 剪枝
        if(path.size()+n-i < k || path.size() > k) {
            return ;
        }
        for (int j = i; j < n; ++j) {
            path.emplace_back(ind[j]);
            dfs(j + 1);
            path.pop_back();
        }
    };
    dfs(0);
    return ans;
}

/**
 * 排列 :  用 顺序循环遍历 做，以数组下标 ind 为例 ： 0，1，2 ... n-1
 * 第 k 个排列 ( 按数字从小到大顺序 ）
 * @param n
 * @param k
 * @return
 */
vector<int> func3(int n, int k) {
    vector<int> ind(n);
    iota(ind.begin(), ind.end(), 0);
    vector<int> mark(n);
    vector<int> path;
    vector<vector<int>> ans;
    function<void(int)> dfs = [&](int i) {
        if (i == n) {
            ans.emplace_back(path);
            return;
        }
        for (int j = 0; j < n; ++j) {
            if (!mark[j]) {
                path.emplace_back(ind[j]);
                mark[j] = 1;
                dfs(i + 1);
                mark[j] = 0;
                path.pop_back();
            }
        }
    };
    dfs(0);
    return ans[k];
}

/**
 * 全排列 :  用 顺序循环遍历 做，以数组下标 ind 为例 ： 0，1，2 ... n-1
 * 第 k 个排列 ( 按数字从小到大顺序 )  (调 next_permutation 公式)；注意是升序排列，对字符串也有效（按字典序升序）
 * @param n
 * @param k
 * @return
 */
vector<int> func4(int n, int k) {
    vector<int> ind(n);
    iota(ind.begin(), ind.end(), 0);
    vector<vector<int>> ans;
    ans.emplace_back(ind);
    for (int i = 0; i < k; ++i) {
        next_permutation(ind.begin(), ind.end());
        ans.emplace_back(ind);
    }
    return ans[k];
}

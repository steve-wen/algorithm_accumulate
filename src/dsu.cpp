#include <bits/stdc++.h>

using namespace std;

/**
*  并查集
*/

/**
 * https://leetcode.cn/problems/subarray-with-elements-greater-than-varying-threshold/description/
 * 每次操作平均时间复杂度 O(1)? O(logn)?
 * no.2334
 */

struct dsu {
    // fa 记录 x 所在树/集合 的根节点; size 记录根节点所在树的元素个数
    vector<size_t> fa, size;
    // x 的初始 fa 是 x 本身; 注意 size 的初始化值 和 size 的合并方式; 此处与后面的统计方式有差异
    explicit dsu(size_t size_) : fa(size_), size(size_, 0) {
        iota(fa.begin(), fa.end(), 0);
    }

    size_t find(size_t x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    //合并
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

/**
 * 并查集 注意 连通, 较为典型的运用
 * https://leetcode.cn/problems/find-all-people-with-secret/description/
 * @param n
 * @param m
 * @param f
 * @return
 */

struct dsu_1 {
    vector<size_t> fa, size;

    explicit dsu_1(size_t size_) : fa(size_), size(size_, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    // 平均时间复杂度 O(1)， 找根节点
    size_t find(size_t x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    // 平均时间复杂度 O(1), 合并两棵树， fa[x] 作为新的根节点
    void unite(size_t x, size_t y) {
        x = find(x), y = find(y);
        if (x == y) return;
        fa[y] = x;
        size[x] += size[y];
    }

    // 平均时间复杂度 O(1)
    // 要删除一个叶子节点，我们可以将其父亲设为自己。
    void erase(size_t x) {
        --size[find(x)];
        fa[x] = x;
    }

    // 将 x节点 移动到 y 节点所在的树
    void move(size_t x, size_t y) {
        auto fx = find(x), fy = find(y);
        if (fx == fy) return;
        fa[x] = fy;
        --size[fx], ++size[fy];
    }
};

vector<int> findAllPeople(int n, vector<vector<int>>& m, int f) {
    sort(m.begin(),m.end(),[&](vector<int> a, vector<int> b){return a[2] < b[2];});
    unordered_set<int> st;
    st.emplace(0);
    st.emplace(f);
    dsu_1 ds(n+1);
    ds.unite(0,f);
    int n1 = m.size();
    for (int i = 0; i < n1; ++i) {
        vector<int> a{m[i][0], m[i][1]};
        while(i <n1-1 && m[i+1][2] == m[i][2]) {
            ++i;
            a.emplace_back(m[i][0]);
            a.emplace_back(m[i][1]);
        }
        int fa = -1;
        for (int j = 0; j < a.size(); j+=2) {
            ds.unite(a[j],a[j+1]);
        }
        for (int j = 0; j < a.size(); j+=2) {
            if (st.count(a[j]) || st.count(a[j+1])) {
                fa = ds.find(a[j]);
            }
        }
        for (int j = 0; j < a.size(); j+=2) {
            if (ds.find(a[j]) == fa) {
                st.emplace(a[j]);
                st.emplace(a[j+1]);
            } else {
                ds.erase(a[j]);
                ds.erase(a[j+1]);
            }
        }
    }
    vector<int> ans(st.begin(),st.end());
    return ans;
}
/**
 * https://leetcode.cn/problems/similar-string-groups/description/
 * @param s
 * @return
 */
int numSimilarGroups(vector<string>& s) {
    int n = s.size();
    dsu_1 ds(n+1);
    auto check = [&](string& s1, string& s2) {
        int m = s1.size(), cnt = 0;
        for (int i = 0; i < m; ++i) {
            if (s1[i] != s2[i]) {
                ++cnt;
            }
        }
        return cnt == 0 || cnt == 2;
    };
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (check(s[i],s[j])) {
                ds.unite(i,j);
            }
        }
    }
    int ans = 0;
    unordered_set<int> t;
    for (int i = 0; i <n; ++i) {
        t.emplace(ds.find(i));
    }
    return t.size();
}

/**
 * 并查集 + 离线思想 (离线注意)
 * 离线：对 query 进行排序等（同时记录下标）， 按照想要的顺序进行遍历
 */
struct dsu_2 {
    vector<size_t> fa, size;

    explicit dsu_2(size_t size_) : fa(size_), size(size_, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    // 平均时间复杂度 O(1)， 找根节点
    size_t find(size_t x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    // 平均时间复杂度 O(1), 合并两棵树， fa[x] 作为新的根节点
    void unite(size_t x, size_t y) {
        x = find(x), y = find(y);
        if (x == y) return;
        fa[y] = x;
        size[x] += size[y];
    }

    // 平均时间复杂度 O(1)
    // 要删除一个叶子节点，我们可以将其父亲设为自己。
    void erase(size_t x) {
        --size[find(x)];
        fa[x] = x;
    }

    // 将 x节点 移动到 y 节点所在的树
    void move(size_t x, size_t y) {
        auto fx = find(x), fy = find(y);
        if (fx == fy) return;
        fa[x] = fy;
        --size[fx], ++size[fy];
    }
};

class Solution_1 {
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
public:
    vector<int> maxPoints(vector<vector<int>> &grid, vector<int> &queries) {
        int m = grid.size(), n = grid[0].size(), mn = m * n;

        dsu_2 ds(mn+1);
        // 矩阵元素从小到大排序，方便离线
        vector<vector<int>> a(mn, vector<int>(3));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                a[i * n + j] = {grid[i][j], i, j};
        sort(a.begin(), a.end());

        // 查询的下标按照查询值从小到大排序，方便离线
        int k = queries.size();
        vector<int> id (k);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](int i, int j) { return queries[i] < queries[j]; });

        vector<int> ans(k);
        int j = 0;
        for (int i : id) {
            int q = queries[i];
            for (; j < mn && a[j][0] < q; ++j) {
                int x = a[j][1], y = a[j][2];
                // 枚举周围四个格子，值小于 q 才可以合并
                for (auto &d : dirs) {
                    int x2 = x + d[0], y2 = y + d[1];
                    if (0 <= x2 && x2 < m && 0 <= y2 && y2 < n && grid[x2][y2] < q)
                        ds.unite(x * n + y, x2 * n + y2); // 把坐标压缩成一维的编号
                }
            }
            if (grid[0][0] < q)
                ans[i] = ds.size[ds.find(0)]; // 左上角的连通块的大小
        }
        return ans;
    }
};


//https://codeforces.com/problemset/problem/28/B
//#include <bits/stdc++.h>
//
//using namespace std;
//#define endl "\n"
//
//struct dsu {
//    vector<size_t> fa, size;
//
//    explicit dsu(size_t size_) : fa(size_), size(size_, 0) {
//        iota(fa.begin(), fa.end(), 0);
//    }
//
//    size_t find(size_t x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
//
//    void unite(size_t x, size_t y) {
//        x = find(x), y = find(y);
//        fa[y] = x;
//        size[x] += size[y]+1;
//    }
//};
//
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    int n;
//    cin >> n;
//
//    vector<int> a(n);
//    for (int i =0; i < n; ++i) {
//        cin>> a[i];
//    }
//    vector<int> d(n);
//    for (int i =0; i < n; ++i) {
//        cin>> d[i];
//    }
//    unordered_set<int> st[n+1];
//    dsu ds(n+1);
//    for (int i =0; i <n; ++i) {
//        if (i-d[i] >= 0) {
//            ds.unite(i,i-d[i]);
//        }
//        if (i+d[i] < n){
//            ds.unite(i,i+d[i]);
//        }
//    }
//    for (int i =0; i <n; ++i) {
//        st[ds.find(i)].emplace(i+1);
//    }
//    for (int i =0; i <n; ++i) {
//        if(st[ds.find(i)].count(a[i]) == 0){
//            cout <<"NO";
//            return 0;
//        }
//    }
//    cout << "YES";
//    return 0;
//}

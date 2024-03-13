#include <bits/stdc++.h>

using namespace std;

/**
* hjt_segmentTree 主席树
*/

/**
 * 主席树：静态区间 kth
 * 离线 O(logn)
 */
class Hjt_Segment_Tree {
    static const int maxn = 2e5 + 5;
    int a[maxn];
    vector<int> v;

    inline int getid(int x) { return lower_bound(v.begin(), v.end(), x) - v.begin() + 1; }

    struct Node {
        int l, r, sum;
    } hjt[maxn * 40];
    int cnt, root[maxn];

    void insert(int l, int r, int pre, int &now, int p) {
        hjt[++cnt] = hjt[pre];
        now = cnt;
        hjt[now].sum++;
        if (l == r) return;
        int m = (l + r) >> 1;       //>>1    =     /2
        if (p <= m) insert(l, m, hjt[pre].l, hjt[now].l, p);
        else insert(m + 1, r, hjt[pre].r, hjt[now].r, p);
    }

    int query(int l, int r, int L, int R, int k) {
        if (l == r) return l;
        int m = (l + r) >> 1;
        int tmp = hjt[hjt[R].l].sum - hjt[hjt[L].l].sum;
        if (k <= tmp) return query(l, m, hjt[L].l, hjt[R].l, k);
        else return query(m + 1, r, hjt[L].r, hjt[R].r, k - tmp);
    }

    vector<int> range_kth(vector<int> &vec, vector<vector<int>> &q) {
        int n = vec.size(), m = q.size();
        vector<int> ans(m);
        for (int i = 1; i <= n; i++)
            v.push_back(a[i] = vec[i - 1]);
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        for (int i = 1; i <= n; i++)
            insert(1, n, root[i - 1], root[i], getid(a[i]));

        for (int i = 0; i < m; ++i) {
            // 此处 l,r 的范围是 1 <= l <= r <= n; 注意与 下标的对应关系
            auto l = q[i][0], r = q[i][1], k = q[i][2];
            ans[i] = v[query(1, n, root[l - 1], root[r], k) - 1];
        }
        return ans;
    }
};

/**
 * 动态区间主席树
 * 支持动态单点修改 + 区间查询 kth
 * O(logn) * O(nlogn) == O(nlog^2n)
 */
class Dynamic_Hjt_tree{
    static const int MAX = 10005;
    struct segment_tree {
        int v;
        int ls, rs;
    } t[MAX * 400];//线段树开nlogn大小
    struct operation {
        bool b;
        int l, r, k;
        int pos, t;
    } q[MAX];//因为要离散花所以要把所有数据输进来离线搞
    int n, m, a[MAX], o[MAX << 1], rt[MAX], len, tot, temp[2][20], cnt[2];
    char opt;

    void Modify(int &now, int l, int r, int pos, int val) {
        if (!now) now = ++tot;
        t[now].v += val;
        if (l == r) return;
        int mid = l + r >> 1;
        if (pos <= mid) Modify(t[now].ls, l, mid, pos, val);
        else Modify(t[now].rs, mid + 1, r, pos, val);
    }

    void prepare_Modify(int x, int val) {
        int k = lower_bound(o + 1, o + len + 1, a[x]) - o;
        for (int i = x; i <= n; i += i & -i) Modify(rt[i], 1, len, k, val);//处理出需要修改哪log棵主席树
    }

    int Query(int l, int r, int k) {
        if (l == r) return l;
        int mid = l + r >> 1, sum = 0;
        for (int i = 1; i <= cnt[1]; i++) sum += t[t[temp[1][i]].ls].v;
        for (int i = 1; i <= cnt[0]; i++) sum -= t[t[temp[0][i]].ls].v;
        if (k <= sum) {
            for (int i = 1; i <= cnt[1]; i++) temp[1][i] = t[temp[1][i]].ls;
            for (int i = 1; i <= cnt[0]; i++) temp[0][i] = t[temp[0][i]].ls;
            return Query(l, mid, k);
        } else {
            for (int i = 1; i <= cnt[1]; i++) temp[1][i] = t[temp[1][i]].rs;
            for (int i = 1; i <= cnt[0]; i++) temp[0][i] = t[temp[0][i]].rs;
            return Query(mid + 1, r, k - sum);
        }
    }

    int prepare_Query(int l, int r, int k) {
        memset(temp, 0, sizeof(temp));//同修改，处理出需要进行相减操作的是哪log棵主席树
        cnt[0] = cnt[1] = 0;
        for (int i = r; i; i -= i & -i) temp[1][++cnt[1]] = rt[i];
        for (int i = l - 1; i; i -= i & -i) temp[0][++cnt[0]] = rt[i];
        return Query(1, len, k);
    }

    vector<int> dynamic_range_kth(vector<int> &vec, vector<vector<int>> que) {
        n = vec.size(), m = que.size();
        vector<int> ans;
        // a[i],o[i] 存的数字
        for (int i = 1; i <= n; i++) {
            a[i] = vec[i-1];
            o[++len] = a[i];
        }
        for (int i = 1; i <= m; i++) {
            auto q1 = que[i-1];
            q[i].b = q1[0]; // q1[0] == 1 表示查询， == 0 表示修改
            if (q[i].b) { // 查询
                q[i].l = q1[1];
                q[i].r = q1[2];
                q[i].k = q1[3];
            } else { // 修改
                q[i].pos = q1[1];
                q[i].t = q1[2];
                o[++len] = q[i].t;
            }
        }
        sort(o + 1, o + len + 1);
        len = unique(o + 1, o + len + 1) - o - 1;//离散 —— 排序 + 去重
        for (int i = 1; i <= n; i++) prepare_Modify(i, 1); // 初始化
        for (int i = 1; i <= m; i++) {
            if (q[i].b) ans.emplace_back(o[prepare_Query(q[i].l, q[i].r, q[i].k)]);
            else {
                prepare_Modify(q[i].pos, -1);
                a[q[i].pos] = q[i].t; // a[q[i].pos] 重新赋值
                prepare_Modify(q[i].pos, 1); // 维护
            }
        }
        return ans;
    }
};

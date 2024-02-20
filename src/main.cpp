#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define rep(i, from, to) for(ll i = from;i<to;i++)
#define rrep(i, from, to) for(ll i = from;i>=to;i--)
#define se second
#define fi first
#define tostring(a) (ostringstream() << a).str()
#define endl "/n"

typedef pair<int,int> pii;
typedef pair<long,long> pll;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * n! n 的阶乘
 * @param n
 * @return
 */
long long fact(int n) {
    long long cnt = 1;
    while(n) {
        cnt *= n;
        --n;
    }
    return cnt;
}

/**
 * 类 string
 */
class String {
public:
    //通用构造函数
    String(const char *str = nullptr) {
        // 获取 str 长度的方法
        string strtmp(str);
        size_t len = strtmp.size();
        if (str == nullptr) {
            return;
        } else {
            // 获取 str 长度的方法
            m_data = new char[strlen(str)];
            for (size_t i = 0; i < strlen(str); ++i) { // 可用 strcpy(m_data, str) 代替
                m_data[i] = str[i];
            }
        }
    };
    //拷贝构造函数
    String(const String &another) {
        m_data = new char [strlen(another.m_data)];
        for (size_t i = 0; i < strlen(another.m_data); ++i) {
            m_data[i] = another.m_data[i];
        }
    };
    //析构函数
    ~String() {
        delete[] m_data;
        m_data = nullptr;
    };
    //赋值函数
    String &operator=(const String &rhs) {
        // 检查自赋值
        if (this == &rhs) {
            return *this;
        } else {
            delete[] m_data;
            m_data = new char[strlen(rhs.m_data)];
            for (size_t i = 0; i < strlen(rhs.m_data); ++i) {
                m_data[i] = rhs.m_data[i];
            }
            return *this;
        }
    };
    //取下标函数
    char &operator[](int i) {
        return m_data[i];
    };
private:
    char *m_data;//用于保存字符串
};

/**
 * 旋转图像
 * @param g
 */
void rotate(vector<vector<int>>& g) {
    int n = g.size();
    for (int i = 0; i < n/2; ++i) {
        for (int j = i; j < n-1-i; ++j) {
            int tmp = g[i][j];
            g[i][j] = g[n-1-j][i];
            g[n-1-j][i]  = g[n-1-i][n-1-j];
            g[n-1-i][n-1-j] = g[j][n-1-i];
            g[j][n-1-i] = tmp;
        }
    }
    return;
}

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
 * 组合长度为 k
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
 * 第 k 个排列 ( 按数字从小到大顺序 )  (调 next_permutation 公式)
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

/**
 * map lower_bound 用法， map 升序， lower_bound 大于等于， map 降序， lower_bound 小于等于
 * 1、改 map 顺序
 * 2、用 upper_bound (--it), 考虑 it 为 begin() 的情况
 */
class SnapshotArray {
public:
    unordered_map<int,map<int,int,greater<>>> mp;
    int cnt = 0;
    SnapshotArray(int len) {

    }

    void set(int ind, int val) {
        mp[ind][cnt] = val;
    }

    int snap() {
        ++cnt;
        return cnt-1;

    }

    int get(int ind, int id) {
        if (mp.count(ind) == 0) {
            return 0;
        }
        auto it = mp[ind].lower_bound(id);
        return it->second;
    }
};

class SnapshotArray1 {
public:
    unordered_map<int,map<int,int>> mp;
    int cnt = 0;
    SnapshotArray1(int len) {

    }

    void set(int ind, int val) {
        mp[ind][cnt] = val;
    }

    int snap() {
        ++cnt;
        return cnt-1;

    }

    int get(int ind, int id) {
        if (mp.count(ind) == 0) {
            return 0;
        }
        auto it = mp[ind].upper_bound(id);
        return it==mp[ind].begin() ? 0 : (--it)->second;
    }
};

/**
 * 环形数组求子数组最大和（环不含重复元素） 考虑： 原数组扩充一倍，后面部分为环的部分
 * 用非环子数组最大和 (mx1), 和带环 前缀和 + 后缀和 mx2, 求 max(mx1, mx2)
 * @param nums
 * @return
 */
int maxSubarraySumCircular(vector<int>& nums) {
    int n = nums.size(), mx = nums[0];
    // 子数组最大和
    for (int i = 0; i<n; ++i) {
        if (nums[i] > mx) {
            mx = nums[i];
        }
        int tmp = 0;
        while (i < n) {
            tmp += nums[i];
            if (tmp <= 0) {
                break;
            }
            mx = max(mx,tmp);
            ++i;
        }
    }
    // 以下标 <= i 的前缀和的最大值
    vector<int> pre(n);
    int mx1 = 0, tmp1 = 0;
    for (int i = 0; i < n; ++i) {
        tmp1 += nums[i];
        if (tmp1 > 0) {
            mx1 += tmp1;
            tmp1 = 0;
        }
        pre[i] = mx1;
    }
    // 后缀和
    vector<int> suf(n);
    suf[0] = accumulate(nums.begin(),nums.end(),0);
    for (int i = 0; i < n-1; ++i) {
        suf[i+1] = suf[i]-nums[i];
    }
    int mx2 = nums[0];
    for (int i = 1; i < n; ++i) {
        mx2 = max(mx2, suf[i]+pre[i-1]);
    }
    return max(mx, mx2);
}

/**
 * 滑动窗口 : 子数组和 >= target 的长度最小值
 * @param nums
 * @param target
 * @return
 */
int func21(vector<int> &nums, int target) {
    int n = (int) nums.size();
    int ans = n + 1, cnt = 0, sum = 0;
    for (int l = 0, r = 0; r < n; ++r) {
        sum += nums[r];
        ++cnt;
        while (sum >= target) {
            ans = min(ans, cnt);
            sum -= nums[l];
            --cnt;
            ++l;
        }
    }
    return ans == n + 1 ? 0 : ans;
}

/**
 * 深度优先搜索 / 遍历, 暴力遍历
 * 部分代码， 非完整代码，(遍历 map)
 * @param
 * @param
 * @return
 */
vector<string> getInheritanceOrder() {
    unordered_map<string, vector<string>> mp;
    vector<string> ans;
    ans.emplace_back("king");
    function<void(string)> dfs = [&](string s){
        if (mp.count(s) == 0) {
            return;
        }
        for (int j = 0; j < mp[s].size(); ++j) {
            ans.emplace_back(mp[s][j]);
            dfs(mp[s][j]);
        }
    };
    dfs("king");
    return ans;
}

/**
 * 完全连通分量： 建图，dfs
 * @param n
 * @param e
 * @return
 */
int countCompleteComponents(int n, vector<vector<int>>& e) {
    int m = e.size(), ans  = 0;
    // 建图
    unordered_map<int,vector<int>> mp;
    for (auto& e1 : e) {
        mp[e1[0]].emplace_back(e1[1]);
        mp[e1[1]].emplace_back(e1[0]);
    }
    // 标记
    vector<int> mark(n);
    // 遍历 dfs
    function<void(int i,unordered_set<int>& st)> dfs = [&](int i, unordered_set<int>& st){
        for(int j = 0; j < mp[i].size(); ++j) {
            if(!mark[mp[i][j]]) {
                st.emplace(mp[i][j]);
                mark[mp[i][j]] = 1;
                dfs(mp[i][j],st);
            }
        }
    };
    // 根据题目处理
    for (int i = 0; i < n; ++i) {
        if (!mark[i]){
            unordered_set<int> st{i};
            mark[i] = 1;
            dfs(i,st);
            int cnt = 0;
            for (auto& e1 : e) {
                if (st.count(e1[0])) {
                    ++cnt;
                }
            }
            if ((st.size()-1+1)*(st.size()-1)/2 == cnt) {
                ++ans;
            }
        }
    }
    return ans;
}

/**
 * dfs : 连通分量(On) + 分别排序
 * @param s
 * @param e
 * @return
 */
string smallestStringWithSwaps(string s, vector<vector<int>>& e) {

    int m = e.size(), n  = s.size();
    // 建图
    unordered_map<int,vector<int>> mp;
    for (auto& e1 : e) {
        mp[e1[0]].emplace_back(e1[1]);
        mp[e1[1]].emplace_back(e1[0]);
    }
    // 标记
    vector<int> mark(n);
    // 遍历 dfs
    function<void(int i,vector<int>&)> dfs = [&](int i, vector<int>& ind){
        for(int j = 0; j < mp[i].size(); ++j) {
            if(!mark[mp[i][j]]) {
                ind.emplace_back(mp[i][j]);
                mark[mp[i][j]] = 1;
                dfs(mp[i][j],ind);
            }
        }
    };
    // 根据题目处理
    for (int i = 0; i < n; ++i) {
        if (!mark[i]){
            vector<int> ind{i};
            mark[i] = 1;
            dfs(i,ind);
            int l = ind.size();
            string str(l,'0');
            for (int j = 0; j < l; ++j) {
                str[j] = s[ind[j]];
            }
            sort(ind.begin(),ind.end());
            sort(str.begin(),str.end());
            for (int j = 0; j < l; ++j) {
                s[ind[j]] = str[j];
            }
        }
    }
    return s;
}

/**
 * 无向图： dfs 的返回值为 bool 类型的情况
 * @param n
 * @param d
 * @return
 */
bool possibleBipartition(int n, vector<vector<int>>& d) {
    unordered_map<int,vector<int>> g;
    // 建图 无向图
    for (auto& d1 : d){
        g[d1[0]].emplace_back(d1[1]);
        g[d1[1]].emplace_back(d1[0]);
    }

    vector<int> vec(n+1);

    // 返回值为 bool 类型的 dfs
    function<bool(int i)> dfs = [&](int i){
        for (auto &v : g[i]) {
            if (vec[v] == 0) {
                vec[v] = 3-vec[i];
                if (!dfs(v)) return false;
            } else {
                if (vec[v] == vec[i]) return false;
            }
        }
        return true;
    };

    for (int i =1; i <= n; ++i) {
        if (!vec[i]) {
            vec[i] = 1;
            if (!dfs(i)) return false;
        }
    }
    return true;
}

/**
 * 0-1 BFS 1. 建图 3 x n 列的表格图，边权为 1 或者 0
 *         2. 双端队列 deque, d 放在队首， d+1 放在队尾
 *         队列中只含 d 和 d+1 , BFS 的两段性
 *         3. 初始化 dis数组 较大值， 需要 vis 数组 或者其他方式 标记已访问过的点
 * @param o
 * @return
 */
int minSideJumps(vector<int>& o) {
    int n = o.size();
    vector<vector<int>> dis(3, vector<int>(n,n));
    dis[1][0] = 0;
    deque<pair<int, int>> q;
    q.emplace_back(1,0);
    while(1){
        auto[i,j] = q.front();
        q.pop_front();
        int d = dis[i][j];
        if (j == n-1) {
            return d;
        }
        if (o[j+1] != i+1 && d < dis[i][j+1]) {
            dis[i][j+1] = d;
            q.emplace_front(i,j+1);
        }
        for (auto k : {(i+1) % 3, (i+2) % 3}) {
            if (o[j] != k+1 && d+1 < dis[k][j]) {
                dis[k][j] = d+1;
                q.emplace_back(k,j);
            }
        }
    }
}

/**
 * bfs : 有向图， 最短路径 （一次遍历，时间复杂度 O(n), 比 dfs 快）
 * queue q, 更新距离 d (层序遍历)
 * @param n
 * @param r
 * @param b
 * @return
 */
vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& r, vector<vector<int>>& b) {
    vector<int> ans(n, -1);
    // 建图
    unordered_map<int,vector<int>> mp[2];
    for (auto& r1 : r) {
        mp[0][r1[0]].emplace_back(r1[1]);
    }
    for (auto& b1 : b) {
        mp[1][b1[0]].emplace_back(b1[1]);
    }
    // 标记
    vector<vector<int>> mark(2, vector<int>(n));
    // 遍历 bfs
    queue<pair<int,int>> q;
    q.emplace(0,0);
    q.emplace(0,1);
    int d = 0;
    while (!q.empty()){
        for (int i = q.size(); i; --i){
            auto [j, k] = q.front();
            q.pop();
            k ^= 1;
            if (ans[j] == -1) ans[j] = d;
            for (int l = 0; l < mp[k][j].size(); ++l) {
                if (!mark[k][mp[k][j][l]]) {
                    q.emplace(mp[k][j][l],k);
                    mark[k][mp[k][j][l]] = 1;
                }
            }

        }
        ++d;
    }
    return ans;
}

/**
 * 多源 bfs, 模板
 * @param w
 * @return
 */
vector<vector<int>> highestPeak(vector<vector<int>>& w) {
    int m = w.size(), n = w[0].size();
    // 遍历方向准备
    vector<vector<int>> vec{{-1,0},{1,0},{0,-1},{0,1}};
    // 标记
    vector<vector<int>> mark(m, vector<int>(n));
    // 初始化 起始点，mark, 距离 d
    queue<pair<int,int>> q;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (w[i][j]) {
                q.emplace(i,j);
                w[i][j] = 0;
                mark[i][j] = 1;
            }
        }
    }
    int d = 1;
    // 遍历 bfs
    while (!q.empty()){
        for (int i = q.size(); i; --i){
            auto [j, k] = q.front();
            q.pop();
            for (auto& vec1:vec) {
                auto j1 = j+vec1[0], k1 = k+vec1[1];
                if (j1 >= 0 && j1 < m && k1 >= 0 && k1 < n && !mark[j1][k1]) {
                    q.emplace(j1,k1);
                    w[j1][k1] = d;
                    mark[j1][k1] = 1;
                }
            }

        }
        ++d;
    }
    return w;
}

/**
 * bfs : 一次遍历， 拓扑排序， 注意 q 是 quiet 数组， q1 是队列
 * @param r
 * @param q
 * @return
 */
vector<int> loudAndRich(vector<vector<int>>& r, vector<int>& q) {
    int n = q.size();
    vector<int> ans(n, n);

    unordered_map<int,int> mp1;
    for (int i = 0; i< n; ++i) {
        mp1[q[i]] = i;
    }

    // 建图
    unordered_map<int,vector<int>> mp;
    for (auto &r1 : r) {
        mp[r1[1]].emplace_back(r1[0]);
    }

    // 遍历 bfs
    for (int i = 0; i < n; ++i) {
        // 标记
        vector<int> mark(n);
        queue<int> q1;
        q1.emplace(i);
        ans[i] = min(ans[i], q[i]);
        while (!q1.empty()){
            for (int k = q1.size(); k; --k){
                auto j = q1.front();
                ans[i] = min(ans[i], q[j]);
                q1.pop();
                for (int l = 0; l < mp[j].size(); ++l) {
                    if (!mark[mp[j][l]]) {
                        q1.emplace(mp[j][l]);
                        mark[mp[j][l]] = 1;
                    }
                }

            }
        }
    }
    for (auto& a : ans) {
        a = mp1[a];
    }
    return ans;
}

/**
 * bfs : 拓扑， 按题意模拟
 * @param n
 * @param e
 * @return
 */
vector<vector<int>> getAncestors(int n, vector<vector<int>>& e) {
    vector<vector<int>> vec(n);
    unordered_map<int, vector<int>> g;
    for (auto & e1 : e) {
        g[e1[1]].emplace_back(e1[0]);
    }

    for (int i = 0; i < n; ++i) {
        vector<int> mark(n);
        set<int> s;
        queue<int> q;
        q.emplace(i);
        while (!q.empty()){
            for (int k = q.size(); k; --k) {
                auto q1 = q.front();
                q.pop();
                for (auto& j : g[q1]) {
                    if (!mark[j]) {
                        mark[j] = 1;
                        s.emplace(j);
                        q.emplace(j);
                    }
                }
            }
        }
        vec[i].assign(s.begin(),s.end());
    }
    return vec;
}

/**
 * 最短环 ： bfs + 记录父节点（pre)
 * @param n
 * @param e
 * @return
 */
int findShortestCycle(int n, vector<vector<int>>& e) {
    int ans = 1e4;

    unordered_map<int, vector<int>> g;
    for (auto & e1 : e) {
        g[e1[1]].emplace_back(e1[0]);
        g[e1[0]].emplace_back(e1[1]);
    }

    for (int i = 0; i < n; ++i) {
        int tmp = 1e4;
        // dis 数组记录距离 且 < 1 时未访问过，有 mark/vis 的作用
        vector<int> dis(n,-1);
        // 初始化
        dis[i] = 0;
        queue<pair<int,int>> q;
        q.emplace(i,-1);
        while (!q.empty()){
            // 找到环
            if (tmp != 1e4) break;
            for (int k = q.size(); k; --k) {
                auto q1 = q.front();
                q.pop();
                // b 为父节点
                auto&[a,b] = q1;
                for (auto& j : g[a]) {
                    if (dis[j] < 0) { // j 未访问过
                        dis[j] = dis[a]+1;
                        q.emplace(j,a);
                    } else if (j != b) { // j 访问过且不是 a 的父节点，找到环
                        tmp = dis[a]+dis[j]+1;
                        break;
                    }
                }
            }
        }
        ans = min(ans,tmp);
    }
    return ans == 1e4 ? -1 : ans;
}

/**
 * 快速幂 ： 与位运算结合，累乘，手画
 * @param x
 * @param n
 * @return
 */
double myPow(double x, int n) {
    int a = abs(n);
    vector<int> b(32);
    for (int i = 0;i < 32; ++i) {
        b[i] = ((a >> i) & 1);
    }
    double ans = 1;
    if (n < 0) x = 1/x;
    for (int i = 0; i < 32; ++i) {
        if (b[i]) ans *= x;
        x *= x;
    }
    return ans;
}

// 结合 bitset 与灵神的位运算文章结合
/**
 *
 * 位运算
 * @param vec
 * @param k
 * @return
 */
int maxSum(vector<int>& vec, int k) {
    ll mod = 1e9+7;
    long ans = 0;
    unordered_map<int,int> mp;
    for (auto a : vec){
        auto s = bitset<30>(a).to_string();
        // 注意首尾下标
        for (int i = 0, j = 29-i; j >= 0; ++i,--j) {
            if (s[j] == '1') {
                mp[i]++;
            }
        }
    }
    while (k) {
        long tmp = 0;
        for (int i = 0; i <= 29; ++i) {
            if (mp[i] > 0) {
                tmp += (long)pow(2,i);
                --mp[i];
            }
        }
        ans += tmp * tmp;
        ans = ans % mod;
        --k;
    }
    return ans;
}

/**
 * bitset 运用，整数转 bitset 转 string, 调用 string find 功能
 * @param s
 * @param n
 * @return
 */

bool queryString(string s, int n) {
    for (int i = 1; i <= n; ++i) {
        auto bin = bitset<30>(i).to_string();
        bin = bin.substr(bin.find('1'));
        if (s.find(bin) == string::npos) return false;
    }
    return true;
}

/**
 * bitset 运用 .count(), 计算二进制里 1 的个数
 * @param nums
 * @param k
 * @return
 */

int sumIndicesWithKSetBits(vector<int>& nums, int k) {
    int ans = 0, n = nums.size();
    for (int i = 0; i < n; ++i) {
//        if (__builtin_popcount(i) == k) {
//            ans += nums[i];
//        }
        // count() 二进制里 1 的个数
        if (bitset<10>(i).count() == k) {
            ans += nums[i];
        }
    }
    return ans;
}

/**
 * 二分： 下限：l, 上限： r,  mid = (r+l)/2, 更新 ans = max/min (ans, mid);
 * @param n
 * @param k
 * @param b
 * @param c1
 * @param s
 * @param c2
 * @return
 */
int maxNumberOfAlloys(int n, int k, int b, vector<vector<int>>& c1, vector<int>& s, vector<int>& c2) {
    int ans = 0;
    // 二分函数
    auto f = [&](vector<int>& c) {
        int l = 0, r = 2e8;
        // 二分 while 闭区间
        while (l <= r) {
            // mid
            int mid = (l+r)/2;
            // 根据题目需要：
            long tmp = 0;
            for (int i = 0; i < n; ++i) {
                tmp += ((long)mid*c[i]-(long)s[i] >0 ? ((long)mid*c[i]-(long)s[i])*c2[i] : 0);
            }
            // 根据题目需要。

            // 更新 l, r, ans
            if ((long)b - tmp >= 0) {
                ans = max(ans,mid);
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
    };
    // 外层调用二分函数
    for (auto &c : c1) {
        f(c);
    }
    return ans;
}

/**
 *  链表， 用到了反转链表
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution_L {
public:
    static ListNode* removeNodes(ListNode* h) {
        // 反转链表
        ListNode* h1 = nullptr;
        while(h != nullptr){
            ListNode* tmp = h;
            h = h->next;
            tmp->next = h1;
            h1 = tmp;
        }
        ListNode* h3 = h1;
        ListNode* h2 = h1;
        int tmp1 = h1->val;
        while (h1->next != nullptr) {
            h1 = h1->next;
            ListNode* tmp = h1;
            if (h1->val >= tmp1) {
                tmp1 = h1->val;
                h2->next = tmp;
                h2 = h2->next;
            }
        }
        h2->next = nullptr;
        // 反转链表
        ListNode* h4 = nullptr;
        while(h3 != nullptr){
            ListNode* tmp = h3;
            h3 = h3->next;
            tmp->next = h4;
            h4 = tmp;
        }
        return h4;
    }
};

/**
 * ListNode 链表的处理， 对地址的处理
 */
class Solution3 {
public:
    ListNode* removeZeroSumSublists(ListNode* h) {
        auto* h3 = new ListNode(0);
        auto* h4 = h3;
        h3->next = h;
        while(h3 != nullptr) {
            int sum = 0;
            ListNode* h2 = h3->next;
            while(h2) {
                sum += h2->val;
                if (sum == 0) {
                    h3->next = h2->next;
                }
                h2 = h2->next;
            }
            if (h3 == nullptr) break;
            h3 = h3->next;
        }
        return h4->next;

    }
};

/**
 * 动态规划： 1. 线性 dp； 理解题意，线性推状态
 *          2. 分类讨论， 前 1， 7， 30 天的情况
 *          3. 定状态： 当天能正常旅游的目前最小花费
 * @param d
 * @param c
 * @return
 */
int mincostTickets(vector<int>& d, vector<int>& c) {
    vector<int> f(366);
    unordered_set<int> st(d.begin(),d.end());
    for (int i = 1; i < 366; ++i) {
        if (!st.count(i)) {
            f[i] = f[i-1];
        } else {
            f[i] = min((f[max(i-1,0)]+c[0]), min(f[max(i-7,0)]+c[1], f[max(i-30,0)]+c[2]));
        }
    }
    return f[d.back()];
}


/**
 * 动态规划
 * 最长回文子序列： 变形题， 等价于 求最长回文子序列。
 *              递归思想推公式； 用动态规划写出来。
 *              确定初值，边界值
 * @param s
 * @return
 */
int minInsertions(string s) {
    int ans = 0, n = s.size();
    vector<vector<int>> f(n,vector<int>(n));
    // 倒序遍历 i
    for (int i = n-1; i >= 0; --i) {
        f[i][i] = 1;
        // 正序遍历 j 因为 f[i][j] = f[i+1][j-1]
        for (int j = i+1; j < n; ++j) {
            if (s[j] == s[i]) {
                f[i][j] = f[i+1][j-1]+2;
            } else {
                f[i][j] = max(f[i+1][j], f[i][j-1]);
            }
        }
    }
    ans = n-f[0][n-1];
    return ans;
}

/**
 * 动态规划
 * 最长公共子序列： 1、先用 dfs 递归推公式，理解思想
 *               2、根据递推式确定循环的方向（顺序， 倒序），分别确定 i, j 的循环方向
 * @param s
 * @param t
 * @return
 */
int longestCommonSubsequence(string s, string t) {
    int m = s.size(), n = t.size();
    vector<vector<int>> f(m+1,vector<int>(n+1));
    for (int i = m-1; i >= 0; --i) {
        for (int j = n-1; j >= 0; --j) {
            if (s[i] == t[j]) {
                f[i][j] = f[i+1][j+1]+1;
            } else {
                f[i][j] = max(f[i+1][j], f[i][j+1]);
            }
        }
    }
    return f[0][0];
}

/**
 * 动态规划： 考虑以 i 结尾时的最少操作次数，
 *          根据 s[i] 是 'a' 或者 'b' 分类讨论，正向递推
 * @param s
 * @return
 */
int minimumDeletions(string s) {
    int n = s.size();
    vector<int> f(n+1);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') {
            f[i+1] = min(cnt,f[i]+1);
        } else {
            f[i+1] = f[i];
            ++cnt;
        }
    }
    return f[n];
}

/**
 * 记忆化搜索转动态规划 ： 目的： 获取路径数组 pre
 * @param n
 * @param w
 * @param g
 * @return
 */
vector<string> getWordsInLongestSubsequence(int n, vector<string>& w, vector<int>& g) {
    vector<string> ans;

    auto check = [&](string a, string b){
        int cnt = 0;
        if (a.size() == b.size()) {
            for (int i = 0; i < a.size(); ++i) {
                if (a[i] != b[i]) ++cnt;
            }
            if (cnt == 1) return true;
        }
        return false;
    };
    // pre数组,记录 i 的前一个下标 j, 根据条件更新
    vector<int> pre(n+1,-1), f(n,1);
    // now 记录倒序遍历的起点，即最值时的 i
    int now = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j){
            if (g[j] != g[i] && check(w[j],w[i]) && f[j]+1 > f[i]) {
                f[i] = f[j]+1;
                pre[i] = j;
            }
        }
        if (f[i] > f[now]) now = i;
    }
    while (now != -1) {
        ans.emplace_back(w[now]);
        now = pre[now];
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

/**
 * 动态规划： 较为复杂， 动态规划(遍历时，根据条件同时处理两个动态规划数组)
 * @param b
 * @return
 */
vector<int> pathsWithMaxScore(vector<string>& b) {
    int mod = 1e9+7;
    auto check = [&](char c){
        if (c == 'E' || c == 'S') return 0;
        else return c-'0';
    };
    int n = b.size();
    int f[n+2][n+2],g[n+2][n+2];
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    g[n-1][n-1] = 1;
    for (int i = n-1; i >= 0; --i) {
        for (int j = n-1; j >= 0; --j){
            if(b[i][j] == 'X') {
                f[i][j] = (int)-1e6;
                continue;
            }
            if (i+1 < n) {
                f[i][j] = f[i+1][j] + check(b[i][j]);
                g[i][j] = g[i+1][j] ;
            }
            if (j+1 < n){
                if (f[i][j+1] + check(b[i][j]) > f[i][j]) {
                    f[i][j] = f[i][j+1] + check(b[i][j]);
                    g[i][j] = g[i][j+1];
                } else if (f[i][j+1] + check(b[i][j]) == f[i][j]){
                    g[i][j] = (g[i][j+1]+g[i][j]) % mod;
                }
            }
            if (i+1 < n && j+1 <n) {
                if (f[i+1][j+1] + check(b[i][j]) > f[i][j]) {
                    f[i][j] = f[i+1][j+1] + check(b[i][j]);
                    g[i][j] = g[i+1][j+1];
                } else if (f[i+1][j+1] + check(b[i][j]) == f[i][j]){
                    g[i][j] = (g[i+1][j+1] + g[i][j])%mod;
                }
            }
        }
    }
    vector<int> ans{f[0][0],g[0][0]};
    if (ans[0] < 0 || ans[1] == 0) return{0,0};
    return ans;
}

/**
 * 记忆化搜索 ： 1. 递归的思想：寻找/求解 子问题
 *             2. 用记忆化数组缓存 ： memo 数组 (维度与 dfs 维度匹配) (注意引用的运用， 即 int& res = memo[i]);
 *             (可结合 memset 使用， 如 int memo[n][m][k]; memset(memo,-1,sizeof(memo)))  注意 sizeof(memo)
 *             3. 从后往前思考， dfs 逆向思考 提出子问题
 * @param s1
 * @param s2
 * @param x
 * @return
 */
int minOperations1(string s1, string s2, int x) {
    int n = s1.size();
    vector<int> ind;
    for (int i = 0; i < n; ++i) {
        if (s1[i] != s2[i]) {
            ind.emplace_back(i);
        }
    }
    int m = ind.size();
    if (m%2) return -1;
    if (!m) return 0;
    vector<int> memo(m,-1);
    function<int(int)> dfs = [&](int i){
        if (i == -1) return 0;
        if (i == -2) return (int)1e6;
        if (memo[i] != -1) return memo[i];
//        return memo[i] = min(dfs(i-1)+x, i > 0 ? dfs(i-2)+(ind[i]-ind[i-1])*2 : (int)1e6);
        int& res = memo[i]; // 注意此处是引用， res 直接修改 memo
        res = min(dfs(i-1)+x, i > 0 ? dfs(i-2)+(ind[i]-ind[i-1])*2 : (int)1e6);
        return res;
    };
    return dfs(m-1)/2;
}

int minOperations(string s1, string s2, int x) {
    int n = s1.size();
    if ((count(s1.begin(), s1.end(), '1') - count(s2.begin(), s2.end(), '1')) % 2) return -1;
//    int memo[n][n + 1][2];
    int memo[100][100][2];
    memset(memo, -1, sizeof(memo)); // -1 表示没有计算过
    function<int(int,int,bool)> dfs = [&](int i, int j, bool pre){
        if (i < 0) {
            if (j > 0 || pre) {
                return (int)1e6;
            }
            return 0;
        }
        int& res = memo[i][j][pre]; // 注意此处是引用， res 直接修改 memo
        if (res != -1) {
            return res;
        }
        if ((s1[i] == s2[i]) == (!pre)) {
            res = dfs(i - 1, j, false);
            return res;
        }
        auto res1 = dfs(i-1,j+1,false)+x;
        auto res2 = dfs(i-1,j,true)+1;
        res = min(res1,res2);
        if (j > 0) {
            auto res3 = dfs(i-1,j-1,false);
            res = min(res,res3);
        }
        return res;
    };
    return dfs(n-1,0,false);
}

/**
 * 记忆化搜索： 打家劫舍
 * @param a
 * @return
 */
int rob1(vector<int>& a) {
    int n = a.size();
    int memo[n][2];
    memset(memo,-1,sizeof(memo));
    function<int(int, bool)> dfs = [&](int i, bool pre){
        if (i< 0) return 0;
        int& res = memo[i][pre];
        if (res != -1) return res;
        if (pre) {
            res = dfs(i-1,false);
            return res;
        }
        res = max(dfs(i-1,true)+a[i], dfs(i-1,false));
        return res;
    };
    return dfs(n-1,false);
}

// 简化思路 dfs(i-1) dfs(i-2)
int rob(vector<int>& a) {
    int n = a.size();
    vector<int> memo(n,-1);
    function<int(int)> dfs = [&](int i){
        if (i< 0) return 0;
        int& res = memo[i];
        if (res != -1) return res;
        res = max(dfs(i-1), dfs(i-2)+a[i]);
        return res;
    };
    return dfs(n-1);
}

/**
 * 记忆化搜索： 最长回文子序列
 * @param s
 * @return
 */
int longestPalindromeSubseq(string s) {
    int n = s.size();
//    int memo[n][n];
    int memo[100][100];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i,int j){
        if (i == j) return 1;
        if (i > j) return 0;
        int& res = memo[i][j];
        if (res != -1) return res;
        if (s[i] == s[j]) {
            res = dfs(i+1,j-1)+2;
            return res;
        }
        res = max(dfs(i+1,j),dfs(i,j-1));
        return res;
    };
    return dfs(0,n-1);
}

/**
 * 记忆化搜索： memo数组， + dfs 时，取模 mod
 * @param s
 * @param l
 * @return
 */
int numWays(int s, int l) {
    int mod = 1e9+7;
    int memo[100+5][100+5];
    memset(memo,-1,sizeof(memo));
    function<int(int i, int j)> dfs = [&](int i,int j){
        if (j == 0) {
            if (i == 0) {
                return 1;
            } else return 0;
        }
        if (i < 0 || i >= l) {
            return 0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = ((dfs(i,j-1)%mod+dfs(i-1,j-1)%mod)%mod+dfs(i+1,j-1)%mod)%mod;
        return res;
    };
    return dfs(0,s);
}

/**
 * 区间划分型 dp : 划分 k 个区间，端点 0 - n-1, dfs(k-1,n-1)
 * 用记忆化搜索 dfs 求解
 */
vector<vector<int>> divi(202);

int init1 = [](){
    for (int i = 1; i < 101; ++i) {
        for (int j = i *2; j < 202; j += i) {
            divi[j].emplace_back(i);
        }
    }
    return 0;
}();

auto check_1 = [](string s){
    int n = s.size();
    int cnt = 101;
    for (auto& d : divi[n]) {
        int tmp = 0;
        for (int i = 0; i < d; ++i) {
            string t;
            for (int j = i; j < n; j += d) {
                t += s[j];
            }
            for (int k = 0; k < t.size()/2 ; ++k) {
                tmp += t[k] != t[t.size()-1-k];
            }
        }
        cnt = min(cnt,tmp);
    }
    return cnt;
};

// memset int 类型时 value 只能为 0 或 1， 否则会出错（与预期不一致）
auto minimumChanges = [](string s, int k) {
    int n = s.size();
    int mody[202][202];
    memset(mody,0,sizeof(mody));
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            mody[i][j] = check_1(s.substr(i,j-i+1));
        }
    }

    int memo[202][202];
    memset(memo,-1,sizeof(memo));

    function<int(int,int)> dfs = [&](int i, int j){
        if (i == 0) {
            return mody[0][j];
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        for (int l = 2*i; l <= j-1; ++l) {
            res = res == -1 ? dfs(i-1,l-1)+mody[l][j] : min(res, dfs(i-1,l-1)+mody[l][j]);
        }
        return res;
    };

    return dfs(k-1,n-1);

};

// 记忆化搜索，线性， t3
long long minIncrementOperations(vector<int>& a, int k) {
    long n = a.size();
    long b = (long)k;
    long memo[n+10][3];
    memset(memo,-1,sizeof(memo));
    function<long(long, long)> dfs = [&](long i, long j){
        if (i < 0) {
            return (long)0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        long& res = memo[i][j];
        if (j < 2) {
            // b-a[i] < 0 ? 0 : b-a[i] 简化写法 ： max(b-a[i], (long)0)
            res = min(dfs(i-1,0)+max(b-a[i], (long)0), dfs(i-1,j+1));
        } else {
            res = dfs(i-1,0)+max(b-a[i], (long)0);
        }
        return res;
    };
    return dfs(n-1,0);
}

/**
 * 树形 dp, 记忆化搜索（也可用 chatgpt 转成 python 加 @cache）
 * 自顶向下
 * @param e
 * @param c
 * @param k
 * @return
 */
int maximumPoints(vector<vector<int>>& e, vector<int>& c, int k) {
    int n = c.size();
    // 建图， 建树， 无向边
    vector<vector<int>> g(n);
    for (auto& e1 : e) {
        g[e1[0]].emplace_back(e1[1]);
        g[e1[1]].emplace_back(e1[0]);
    }
    // memo 数组注意不要爆内存
    int memo[n+2][18];
    memset(memo,-1,sizeof(memo));
    function<int(int,int,int)> dfs = [&](int i, int j, int fa){
        // 边界， 右移 14 位后，都变为0(0 > 负数)
        if (j >= 14) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        int res1 = (c[i]>>j)-k, res2 = c[i]>>(j+1);
        for (auto& i1 : g[i]) {
            if (i1 != fa) {
                res1 += dfs(i1,j,i);
                res2 += dfs(i1,j+1,i);
            }
        }
        return max(res1,res2);
    };
    return dfs(0,0,0);
}

// 可用 chatgpt 转成 python 加 @cache, copy 代码时，用 copy code 按钮，保留 python 格式
//def maximumPoints(e, c, k):
//n = len(c)
//g = [[] for _ in range(n)]
//for e1 in e:
//g[e1[0]].append(e1[1])
//g[e1[1]].append(e1[0])
//
//@cache
//    def dfs(i, j, fa):
//if j >= 14:
//return 0
//res1 = (c[i] >> j) - k
//res2 = c[i] >> (j + 1)
//for i1 in g[i]:
//if i1 != fa:
//res1 += dfs(i1, j, i)
//res2 += dfs(i1, j + 1, i)
//return max(res1, res2)
//
//return dfs(0, 0, 0)

// 考虑记忆化搜索 dfs 树形dp, 记忆化搜索
long long maximumScoreAfterOperations(vector<vector<int>>& e, vector<int>& v) {
    long n = v.size(), ans = 0;
    // 建图， 建树
    vector<vector<int>> g(n);
    for (auto &e1: e) {
        g[e1[1]].emplace_back(e1[0]);
        g[e1[0]].emplace_back(e1[1]);
    }
    // memo 数组注意不要爆内存
    long memo[n+2][2];
    memset(memo,-1,sizeof(memo));
    function<long(int,int,int)> dfs = [&](int i, int j, int fa){
        // 边界， 判断叶子节点
        if (g[i].size() == 1 && g[i][0] == fa) {  // g[i].size() == 1 && i != 0
            return 0L;
        }
        if (memo[i][j] != -1) return memo[i][j];
        long& res = memo[i][j];
        res = 0;
        for (auto& i1 : g[i]) {
            if (i1 != fa) { // 不往上递归
                if (j ==1) {
                    res += dfs(i1,1,i)+(long)v[i1];
                } else {
                    if (g[i1].size() == 1 && g[i1][0] == i) {
                        res += dfs(i1,1,i);
                    } else {
                        res += max(dfs(i1,1,i), dfs(i1,0,i)+(long)v[i1]);
                    }
                }
            }
        }
        return res;
    };
    return max(dfs(0,0,0)+(long)v[0], dfs(0,1,0));
}

// 二叉树的直径， 找拐点，分成两条链 no.534
int diameterOfBinaryTree(TreeNode* root) {
    int ans = 0;
    function<int(TreeNode*)> dfs = [&](TreeNode* r){
        if (r == nullptr) return -1;
        int L = dfs(r->left), R = dfs(r->right); // 用 L，R 记录 dfs, 类似 memo 数组记忆化
        ans = max(ans, L+R+2);
        return max(L,R)+1;
    };
    dfs(root);
    return ans;
}

// 二叉树的最大路径和 no.124
int maxPathSum(TreeNode* root) {
    int ans = -1e3;
    function<int(TreeNode*)> dfs = [&](TreeNode* r){
        if (r == nullptr) return 0;
        int L = max(0,dfs(r->left)), R = max(0,dfs(r->right)); // 用 L，R 记录 dfs, 类似 memo 数组记忆化
        ans = max(ans, L+R+r->val);
        return max(L,R)+r->val;
    };
    dfs(root);
    return ans;
}

// 相邻字符不同的最长路径 no.2246
int longestPath(vector<int>& p, string s) {
    // 建树
    int n = p.size();
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        g[p[i]].emplace_back(i);
    }

    int ans = 1;
    function<int(int)> dfs = [&](int i) {
        int i_len = 0;
        for (auto j : g[i]) {
            // 递归儿子
            int j_len = dfs(j)+1;
            if (s[j] != s[i]){ // 不满足条件则不更新答案
                ans = max(ans, i_len+j_len+1);
                i_len = max(i_len,j_len);
            }
        }
        return i_len;
    };
    dfs(0);
    return ans;
}

// no.337 打家劫舍 3
int rob(TreeNode* root) {
    // 记忆化， memo map
    map<pair<TreeNode*,int>,int> memo;
    function<int(TreeNode*,int)> dfs = [&](TreeNode* r, int j){
        if (r == nullptr) return 0;
        if(memo.count(pair(r,j))) return memo[pair(r,j)];
        int& res = memo[pair(r,j)];
        int l0 = dfs(r->left,0), l1 = dfs(r->left,1);
        int r0 = dfs(r->right,0), r1 = dfs(r->right,1);
        if (j == 1) {
            res = l0+ r0+r->val;
        } else {
            res = max(l0,l1) + max(r0,r1);
        }
        return res;
    };
    return max(dfs(root,0),dfs(root,1));
}

// no.968 监控二叉树
int minCameraCover(TreeNode* root) {
    // 记忆化， memo map
    map<pair<TreeNode*,int>,int> memo;
    function<int(TreeNode*,int)> dfs = [&](TreeNode* r, int j){
        if (r == nullptr) {
            return j == 0 ? (int)1e3 : 0;
        }
        if(memo.count(pair(r,j))) return memo[pair(r,j)];
        int& res = memo[pair(r,j)];
        int l0 = dfs(r->left,0), l1 = dfs(r->left,1), l2 = dfs(r->left,2);
        int r0 = dfs(r->right,0), r1 = dfs(r->right,1), r2 = dfs(r->right,2);
        if (j == 0) {
            res = min(min(l0,l1),l2) + min(min(r0,r1),r2) + 1;
        } else if (j ==1) {
            res = min(l0,l2)+min(r0,r2);
        } else {
            res = min(min(l0+r0,l0+r2),l2+r0);
        }
        return res;
    };
    return min(dfs(root,0),dfs(root,2));

}

/**
 * 单调队列，双端队列 ： 参照单调栈，但动态更新
 * 前缀和
 * @param a
 * @param k
 * @return
 */

int shortestSubarray(vector<int>& a, int k) {
    int n = a.size(), ans = n+1;
    // 前缀和
    vector<long> pre(n+1);
    for (int i = 0; i < n; ++i) {
        pre[i+1] = pre[i]+(long)a[i];
    }
    // 双端队列
    deque<int> q;
    q.emplace_back(0);
    // 数形结合， 单调性跟图像结合
    for (int i = 1; i <= n; ++i) {
        // pop 左边无用的点
        while(!q.empty() && pre[i]-pre[q.front()] >= k ) {
            ans = min(ans, i-q.front());
            q.pop_front();
        }
        // pop 右边无用的点
        while(!q.empty() && pre[q.back()] >= pre[i]) {
            q.pop_back();
        }
        // emplace 当前点
        q.emplace_back(i);
    }
    return ans == n+1 ? -1 : ans;
}

// 单调队列，参照单调栈，但动态更新
vector<int> maxSlidingWindow(vector<int>& a, int k) {
    int n = a.size();
    vector<int> b;
    deque<int> q;
    for (int i = 0; i < n; ++i) {
        // pop 左边无用的点
        while(!q.empty() && (a[q.front()] <= a[i] || q.front() <= i-k)) {
            q.pop_front();
        }
        // pop 右边无用的点
        while (!q.empty() && a[q.back()] <= a[i]) {
            q.pop_back();
        }
        // 更新当前点
        q.emplace_back(i);
        if (i >= k-1) {
            b.emplace_back(a[q.front()]);
        }
    }
    return b;
}

int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
    unordered_map<int, vector<int>> mp;
    int m = mat.size(), n = mat[0].size(), cnt = 0;
    vector<int> vecC(n, m);
    vector<int> vecR(m, n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            mp[mat[i][j]] = vector<int>({i, j});
        }
    }
    vector<vector<int>> vec(m, vector<int>(n));
    for (auto& num : arr) {
        ++vec[mp[num][0]][mp[num][1]];
        --vecC[mp[num][1]];
        --vecR[mp[num][0]];
        if (!vecC[mp[num][1]] || !vecR[mp[num][0]]) {
            return cnt;
        }

        ++cnt;
    }
    return cnt;
}


double maxAverageRatio(vector<vector<int>>& cl, int ex) {
    priority_queue<tuple<double, double, double>,vector<tuple<double, double, double>>, less<>> q;
    vector<vector<double>> vec(cl.size(), vector<double>(2));
    for (int i = 0; i < cl.size(); ++i) {
        for(int j = 0; j < 2; ++j) {
            vec[i][j] = (double)(cl[i][j]);
        }
    }
    double sum = 0;
    for (int i = 0; i < cl.size(); ++i) {
        sum += (vec[i][0]) / (vec[i][1]);
        q.push({(vec[i][0] + 1) / (vec[i][1] + 1) - (vec[i][0]) / (vec[i][1]), vec[i][0], vec[i][1]});
    }
    while(ex--) {
        auto [a, b, c] = q.top();
        sum += a;
        q.pop();
        ++b;
        ++c;
        q.push({(b + 1) / (c + 1) - (b) / (c), b, c});
    }
    return sum / (double)(cl.size());

}

int punish(int n) {
    int ans = 0, sum = 0;

    function<void(int, int, int, string, string)> dfs = [&](int i, int j, int num, string s, string str) {
        if (i == j) {
            if (j == 1) {
                sum = stoi(str);
            }
            if (sum == num) {
                ans += sum * sum;
                sum = (int)(-1e9);
            }
            return;
        }
        sum += stoi(str);
        string tmp = str;
        str = s[i];
        if (i + 1 == j) sum += stoi(str);
        dfs(i + 1, j, num, s, str);
        if (i + 1 == j) sum -= stoi(str);
        sum -= stoi(tmp);
        str = tmp;
        str += s[i];
        if (i + 1 == j) sum += stoi(str);
        dfs(i + 1, j, num, s, str);
        if (i + 1 == j) sum -= stoi(str);

    };

    for (int j = 1; j <= n; ++j) {
        string s = to_string(j * j);
        string str{s[0]};
        sum = 0;
        dfs(1, s.size(), j, s, str);

    }
    return ans;
}


int PRE_SUM[1001];

int punishmentNumber(int n) {
    return PRE_SUM[n];
}

bool isRev(int l, int r, string s) {
    string str = s.substr(l, r - l + 1);
    string tmp = str;
    reverse(str.begin(), str.end());
    return tmp == str;
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> ans;
    vector<string> path;
    int n = s.size();
    function<void(int, int)> dfs = [&](int i, int start){
        if (i == n) {
            ans.emplace_back(path);
            return;
        }
        if (i < n - 1) {
            dfs(i + 1, start);
        }
        if (isRev(start, i, s)) {
            path.emplace_back(s.substr(start, i - start + 1));
            dfs(i + 1, i + 1);
            path.pop_back();
        }
    };
    dfs(0,0);
    return ans;
}

int semiOrderedPermutation(vector<int>& nums) {
    int n = nums.size(), ind1 = 0, ind2 = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        if (nums[i] == n) ind2 = i;
        if (nums[i] == 1) ind1 = i;
    }
    if (ind2 < ind1) {
        ans = n - 1 - ind2 + ind1 - 1;
    } else {
        ans = n - 1 - ind2 + ind1;
    }
    return ans;
}

long long matrixSumQueries(int n, vector<vector<int>>& que) { //倒序
    long ans = 0;
    unordered_set<int> st[2];
    for (int i = que.size() - 1; i >= 0; --i) {
        int type = que[i][0], ind = que[i][1], val = que[i][2];
        if (!st[type].count(ind)) {
            ans += (n - st[type ^ 1].size()) * val;
            st[type].insert(ind);
        }
    }
    return ans;

}

bool canChange(string s, string t) {
    int n = s.size();
    int i = 0, j = 0;
    for (; i < n && j < n;) {
        if (s[i] == '_') {
            ++i;
        }
        if (t[j] == '_') {
            ++j;
        }
        if ((s[i] == 'L' || s[i] == 'R') && (t[j] == 'L' || t[j] == 'R')) {
            if (s[i] == t[j]) {
                if (s[i] == 'L' && i >= j) {
                    ++i;
                    ++j;
                } else if (s[i] == 'R' && i <= j) {
                    ++i;
                    ++j;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    }
    if (i == n) {
        for (;j < n; ++j) {
            if (t[j] == 'L' || t[j] == 'R') return false;
        }
    } else if (j == n) {
        for (;i < n; ++i) {
            if (s[i] == 'L' || s[i] == 'R') return false;
        }
    }
    return true;
}


int latestTimeCatchTheBus(vector<int>& b, vector<int>& p, int cap) {
    int m = b.size(), n = p.size(), ans = 0;
    sort(b.begin(), b.end());
    sort(p.begin(), p.end());
    int cnt = 0;
    int i = 0, j = 0;
    bool flag = false;
    for (; i < m && j < n;) {
        if (p[j] <= b[i] && cnt < cap) {
            ++cnt;
            ++j;
        } else {
            if (i == m - 1 && cnt < cap) {
                flag = true;
            }
            cnt = 0;
            ++i;
        }
    }
    map<int, int> mp;
    for (auto& num : p) {
        mp[num] = 1;
    }
    if ((j == n && (i < m - 1 || cnt < cap)) || flag) {
        for (int k = b.back(); k > 0; --k) {
            if (!mp[k]) {
                ans = k;
                break;
            }
        }
    } else {
        int tmp = j - 1 >= 0 ? j - 1 : 0;
        for (int k = p[tmp]; k > 0; --k) {
            if (!mp[k]) {
                ans = k;
                break;
            }
        }
    }
    return ans;
}

int countGoodStrings(int low, int high, int zero, int one) {
    int MOD = (int)(1e9 + 7);
    int ans = 0;
    int m = min(zero, one), n = max(zero, one);
    vector<int> f(high + 1);
    f[0] = 1;
    for (int i = m; i <= high; ++i) {
        f[i] = ((i - n >= 0 ? f[i - n] : 0) % MOD + f[i - m] % MOD) % MOD;
    }
    for (int i = low; i <= high; ++i) {
        ans = ((ans % MOD) + f[i]) % MOD;
    }
    return ans;

}

int maxProfit1(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> f(n + 1, vector<int>(2));
    f[0][0] = 0;
    f[0][1] = (int)(-1e5);
    for (int i = 0; i < n; ++i) {
        f[i + 1][0] = max(f[i][0], f[i][1] + prices[i]);
        f[i + 1][1] = max(f[i][0] - prices[i], f[i][1]);
    }
    return f[n][0];
}

int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    int inf = (int) 1e5;
    vector<vector<vector<int>>> f(n + 1, vector<vector<int>>(k + 2, vector<int>(2, -inf) ));
    for (int i = 0; i <= k + 1; ++i) {
        f[0][i][0] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k + 1; ++j) {
            f[i + 1][j + 1][0] = max(f[i][j][1] + prices[i], f[i][j + 1][0]);
            f[i + 1][j + 1][1] = max(f[i][j + 1][0] - prices[i], f[i][j + 1][1]);
        }
    }
    return f[n][k + 1][0];
}

bool validPartition(vector<int>& nums) {
    int n = nums.size();
    auto isValid = [&](int i, int j){
        if (j == 2) {
            if (nums[i] == nums[i + 1]) return true;
            else return false;
        } else if (j == 3) {
            if ((nums[i] == nums[i + 1] && nums[i] == nums[i + 2]) || (nums[i + 1] - nums[i] == 1 && nums[i + 2] - nums[i + 1] == 1)) return true;
            else return false;
        } else{
            return false;
        }
    };

    vector<int> f(n + 1);
    f[2] = isValid(0, 2);
    if (n >= 3) {
        f[3] = isValid(0, 3);
    }
    if (n >= 4) {
        for (int i = 4; i <= n; ++i) {
            f[i] = (f[i - 2] && isValid(i - 2, 2)) || (f[i - 3] && isValid(i - 3, 3));
        }
    }
    return f[n];
}

int longestPalindromeSubseq1(string s) {
    int n = s.size();
    vector<vector<int>> f(n + 1, vector<int>(n + 1));
    for (int i = 0; i <= n; ++i) {
        f[i][i] = 1;
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            if (s[i] == s[j]) {
                f[i][j] = f[i + 1][j - 1] + 2;
            } else {
                f[i][j] = max(f[i + 1][j], f[i][j - 1]);
            }
        }
    }
    return f[0][n - 1];

}

int minScoreTriangulation(vector<int>& val) {
    int n = val.size();
    vector<vector<int>> f(n, vector<int>(n));
    for (int i = n - 3; i >= 0; --i) {
        for (int j = i + 2; j < n; ++j) {
            int res = (int)1e9;
            for (int k = i + 1; k < j; ++k) {
                res = min(res, f[i][k] + f[k][j] + val[i] * val[j] * val[k]);
            }
            f[i][j] = res;
        }
    }
    return f[0][n - 1];
}

int longestAlternatingSubarray(vector<int>& nums, int t) {
    int n = nums.size(), ans = 0;
    int tmp = 0;
    for (int i = 0, j = 0; i < n; ++i) {
        if (!tmp) {
            if (nums[i] % 2 == 0 && nums[i] <= t) {
                ++tmp;
            } else {
                ++j;
            }
        } else {
            if ((nums[i] % 2 != nums[i - 1] % 2) && nums[i] <= t) {
                ++tmp;
            } else {
                ans = max(ans, tmp);
                j = i;
                if (nums[i] % 2 == 0 && nums[i] <= t) tmp = 1;
                else tmp = 0;
            }
        }
    }
    ans = max(ans, tmp);
    return ans;
}

long long continuousSubarrays(vector<int>& nums) {
    int n = nums.size();
    long long ans = 0;
    multiset<int> s;
    for (int l = 0,r = 0; r < n; ++r) {
        s.insert(nums[r]);
        while (*s.rbegin() - *s.begin() > 2) {
            s.erase(s.find(nums[l++]));
        }
        ans += r - l + 1;
    }
    return ans;
}

int countBeautifulPairs(vector<int>& nums) {
    int ans = 0, n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            string tmp = to_string(nums[i]);
            int a = tmp[0] - '0';
            if (gcd(a, nums[j] % 10) == 1) ++ans;
        }
    }
    return ans;

}

int numberOfGoodSubarraySplits(vector<int>& nums) {
    int MOD = 1e9 + 7;
    long ans = 1, tmp = 1;
    int n = nums.size();
    bool fir1 = true;
    for (int i = 0; i < n; ++i) {
        if (nums[i] == 0) {
            ++tmp;
        } else {
            if (fir1) {
                tmp = 1;
                fir1 = false;
            } else {
                ans = ans * tmp % MOD;
                tmp = 1;
            }
        }
    }
    if (*max_element(nums.begin(), nums.end()) == 0) return 0;
    return ans;
}

bool checkArray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> diff(n);
    long dSum = 0;

    for (int i = 0; i < n; ++i) {
        dSum += diff[i];
        nums[i] += dSum;
        if (i > n - k && nums[i] > 0) {
            return false;
        }
        if (nums[i] < 0) return false;
        diff[i] = -nums[i];
        if (i + k < n) {
            diff[i + k] = nums[i];
        }
        dSum += diff[i];
    }
    return true;
}


int maximumJumps(vector<int>& nums, int t) {
    int INF = -1e3;
    int n = nums.size();
    vector<int> f(n, INF);
    f[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (abs(nums[i] - nums[j]) <= t) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }
    return f[n- 1] < 0 ? -1 : f[n - 1];

}


int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
    int ans = 1, n = nums1.size();
    vector<vector<int>> f(n + 1, vector<int>(2));
    f[0][0] = 1;
    f[0][1] = 1;
    for (int i = 0; i < n - 1; ++i) {
        if (nums1[i + 1] >= nums1[i]) {
            f[i + 1][0] = f[i][0] + 1;
        }
        if (nums1[i + 1] >= nums2[i]) {
            f[i + 1][0] = max(f[i + 1][0], f[i][1] + 1);
        }
        if (nums1[i + 1] < nums1[i] && nums1[i + 1] < nums2[i]) {
            f[i + 1][0] = 1;
        }
        if (nums2[i + 1] >= nums1[i]) {
            f[i + 1][1] = f[i][0] + 1;
        }
        if (nums2[i + 1] >= nums2[i]) {
            f[i + 1][1] = max(f[i + 1][1], f[i][1] + 1);
        }
        if (nums2[i + 1] < nums1[i] && nums2[i + 1] < nums2[i]) {
            f[i + 1][1] = 1;
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            ans = max(ans, f[i][j]);
        }
    }
    return ans;
}

string shiftingLetters(string s, vector<vector<int>>& vec) {
    int n = s.size(), dSum = 0;
    vector<int> diff(n + 1);
    for (auto& v : vec) {
        if (v[2] == 0) {
            --diff[v[0]];
            ++diff[v[1] + 1];
        } else {
            ++diff[v[0]];
            --diff[v[1] + 1];
        }
    }
    for (int i = 0; i < n; ++i) {
        dSum += diff[i];
        int tmp = abs(dSum) % 26;
        if (dSum > 0) {
            s[i] = (s[i] - 'a' + tmp) % 26 + 'a';
        } else if (dSum < 0) {
            int tmp1 = s[i] - 'a' - tmp;
            if (tmp1 >= 0) {
                s[i] = 'a' + tmp1;
            } else {
                s[i] = 26 + 'a' + tmp1;
            }
        }
    }
    return s;
}

// tle
int paintWalls1(vector<int>& cost, vector<int>& time) {
    int n = cost.size();
    int ans = 1e9;

    vector<int> ind(n);
    iota(ind.begin(), ind.end(), 0);
    vector<vector<int>> res;
    vector<int> path;
    function<void(int)> dfs = [&](int i){
        if (i == n) {
            res.emplace_back(path);
            return;
        }
        dfs(i + 1);
        path.emplace_back(i);
        dfs(i + 1);
        path.pop_back();
    };
    dfs(0);
    for (auto& vec : res) {
        int timeSum = 0, costSum = 0;
        for (int i = 0; i < vec.size(); ++i) {
            timeSum += time[vec[i]];
        }
        if(timeSum >= n - vec.size()) {
            for (int i = 0; i < vec.size(); ++i) {
                costSum += cost[vec[i]];
            }
            ans = min(ans, costSum);
        }
    }
    return ans;
}

int paintWalls(vector<int>& cost, vector<int>& time) {
    int n = cost.size();
    int inf = 1e9;
    vector<vector<int>> f(n, vector<int>(n + 1, inf));
    for (int i = 0; i < n; ++i) {
        f[i][0] = 0;
    }
    for (int j = 0; j <= n; ++j) {
        if (j <= time[0] + 1)
            f[0][j] = cost[0];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j - time[i] - 1 <= 0) {
                f[i][j] = min(cost[i], f[i - 1][j]);
            } else {
                f[i][j] = min(f[i-1][j - time[i] - 1] + cost[i], f[i - 1][j]);
            }
        }
    }
    return f[n - 1][n];
}

int longestValidSubstring(string wo, vector<string>& fb) {
    int n = wo.size(), ans = 0;
//    unordered_set<string> st(fb.begin(), fb.end());
    unordered_map<string, int> mp;
    for (auto& str: fb) {
        ++mp[str];
    }
    for (int l = 0, r = 0; r < n; ++r) {
        for (int i = r; i >= l && i > r - 10; --i) {
            if (mp[wo.substr(i, r - i + 1)]) {
                l = i + 1;
            }
        }
        ans = max(ans, r - l + 1);
    }
    return ans;
}

int longestIdealString(string s, int k) {
    int n = s.size();
    vector<int> f(26, 0);
    for (auto c : s) {
        int tmp = c - 'a';
        f[tmp] = *max_element(&f[0] + max(tmp - k, 0), &f[0] + min(tmp + k + 1, 26)) + 1;
    }
    return *max_element(f.begin(),f.end());

}

int peopleAwareOfSecret(int n, int de, int fo) {
    int MOD = 1e9 + 7;
    vector<int> f(n);
    f[0] = 1;
    int cnt_b = 0;
    for (int i = 0; i < n; ++i ) {
         if (i + de > n - 1) {
             cnt_b = (cnt_b % MOD + f[i] % MOD) % MOD;
         }
         for (int j = i + de; j < min(n, i + fo); ++j) {
             f[j] = (f[j] % MOD + f[i] % MOD) % MOD;
         }
    }
    return (f[n - 1] + cnt_b) % MOD;
}


long long mostPoints(vector<vector<int>>& que) {
    int n = que.size();
    vector<long> f(n);
    f[n - 1] = que[n-1][0];
    for (int i = n -2; i >= 0; --i) {
        f[i] = max(f[i + 1], (long)que[i][0] + (i + que[i][1] + 1 > n - 1 ? 0 : f[i + que[i][1] + 1]));
    }
    return f[0];
}

//dp

int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size(), ans = 0, ans1 = 0, ans2 = 0;
    int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
    int sum2 = accumulate(nums2.begin(), nums2.end(), 0);
    vector<int> f1(n),f2(n);
    f1[0] = nums2[0] - nums1[0];
    f2[0] = -f1[0];
    ans1 = max(ans1, f1[0]);
    ans2 = max(ans2, f2[0]);
    for (int i = 1; i < n; ++i) {
        f1[i] = max(f1[i - 1] + nums2[i] - nums1[i], nums2[i] - nums1[i]);
        f2[i] = max(f2[i - 1] + nums1[i] - nums2[i], nums1[i] - nums2[i]);
        ans1 = max(ans1, f1[i]);
        ans2 = max(ans2, f2[i]);
    }
    return max(sum1 + ans1, sum2 + ans2);
}

// 思维

int countCollisions(string d) {
    int ans = 0;
    int n = d.size();
    int cntR = 0;
    for (int i = 1; i < n; ++i) {
        if (d[i - 1] == 'L') {
            continue;
        } else if (d[i - 1] == 'S') {
            if (d[i] == 'L') {
                ++ans;
                d[i] = 'S';
            } else {
                continue;
            }
        } else {
            if (d[i] == 'L') {
                ans += cntR;
                ++ans;
                ++ans;
                d[i] = 'S';
                cntR = 0;
            } else if (d[i] == 'S') {
                ans += cntR;
                ++ans;
                cntR = 0;
            } else {
                ++cntR;
                continue;
            }
        }
    }
    return ans;
}

int maximumXOR(vector<int>& nums) {
    int ans = 0, cnt = 0;
    map<int, int> mp;
    for (auto num : nums) {
        while(num > 0) {
            if (num % 2) {
                if (!mp[cnt]) {
                    ans += (int)pow(2, (double)cnt);
                    ++mp[cnt];
                }
            }
            ++cnt;
            num /= 2;
        }
        cnt = 0;
    }
    return ans;
}

int maxIncreasingGroups(vector<int>& u) {
    long sum = 0, ans = 0;
    sort(u.begin(), u.end());
    for (auto v:u) {
        sum += (long)v;
        if (sum >= (ans+2) * (ans + 1) / 2) {
            ++ans;
        }
    }
    return ans;
}

// no.2262 字符串的总引力
long long appealSum(string s) {
    long ans = 0, tmp = 0;
    int n = s.size();
    unordered_map<char, int> mp;
    for (int i = 0; i < n; ++i) {
        tmp += (i - mp[i] + 1);
        ans += tmp;
        mp[s[i]] = i + 1;
    }
    return ans;
}

long long countSubarrays(vector<int>& nums, long long k) {
    long long ans = 0, sum = 0;
    int n = nums.size();
    for (int l = 0, r = 0; r < n && l < n;++r ) {
        sum += (long)nums[r];
        if (sum * (long)(r - l + 1) < k) {
            ans += (long)(r - l + 1);
        } else {
            while (sum * (long)(r - l + 1) >= k) {
                sum -= (long)nums[l];
                ++l;
            }
            ans += (long)(r - l + 1);
        }

    }
    return ans;

}

int maximumWhiteTiles(vector<vector<int>>& t, int c) {
    sort(t.begin(), t.end(), [](auto& a, auto& b) {return a[0] < b[0];});
    int ans = 0,cover = 0, n = t.size();
    for(int l = 0, r = 0; r < n; ++r) {
        cover += t[r][1] - t[r][0] + 1;
        while (t[l][1] + c - 1 < t[r][1]) {
            cover -= t[l][1] - t[l][0] + 1;
            ++l;
        }
        ans = max(ans, cover - max(t[r][1] - c + 1 - t[l][0], 0));
    }
    return ans;

}


int longestSubsequence(string s, int k) {
    int n = s.size(), ans = 0, cnt = 0, sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '1') {
            if (n- 1 - i  >= 30) break;
            sum += (int)pow(2, n - 1 - i);
            if (sum <= k) {
                ++cnt;
            } else {
                break;
            }
        }
    }

    return cnt + count(s.begin(), s.end(), '0');
}

int numberOfPaths(vector<vector<int>>& grid, int k) {
    int m = grid.size(), n = grid.front().size();
    int MOD = 1e9 + 7;
    vector<vector<vector<int>>> f(m + 1, vector<vector<int>>(n + 1, vector<int>(k)));
    f[0][1][0] = 1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int v = 0; v < k; ++v) {
                f[i+1][j+1][(v+grid[i][j]) % k] = (f[i + 1][j][v] + f[i][j+1][v]) %MOD;
            }
        }
    }
    return f[m][n][0];
}

vector<int> goodIndices(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> cnt1(n), cnt2(n);
    cnt1.front() = 1, cnt2.back() = 1;
    for (int i = 1; i < n ; ++i) {
        if (nums[i] <= nums[i-1]) {
            cnt1[i] = cnt1[i-1] + 1;
        } else {
            cnt1[i] = 1;
        }
    }
    for (int i = n - 2; i >= 0 ; --i) {
        if (nums[i] <= nums[i+1]) {
            cnt2[i] = cnt2[i+1] + 1;
        } else {
            cnt2[i] = 1;
        }
    }
    vector<int> ans;
    for (int i = k;i < n - k; ++i) {
        if (cnt1[i - 1] >= k && cnt2[i + 1] >= k) {
            ans.emplace_back(i);
        }
    }
    return ans;
}


bool isGood(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    if (n == 1) return false;
    for (int i = 0; i < n; ++i) {
        if (i == n - 1) {
            if (nums[i] != n -1)
                return false;
        } else {
            if (nums[i] != i + 1) {
                return false;
            }
        }
    }
    return true;
}

string sortVowels(string s) {
    int n = s.size();
    vector<char> vec;
    for(int i = 0; i < n; ++i) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'A'
                                                                                       || s[i] == 'E' || s[i] == 'I' || s[i] == 'O'
                                                                                                                        || s[i] == 'U' ) {
            vec.emplace_back(s[i]);
        }

    }
    sort(vec.begin(), vec.end());
    for(int i = 0, j = 0; i < n; ++i) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'A'
            || s[i] == 'E' || s[i] == 'I' || s[i] == 'O'
            || s[i] == 'U' ) {
            s[i] = vec[j];
            ++j;
        }

    }
    return s;
}

long long maxScore(vector<int>& nums, int x) {
    int n = nums.size();
    long INF = -1e9;
    long ans = nums[0];

    vector<vector<long>> f(n, vector<long>(2, INF));
    if (nums[0] % 2) {
        f[0][1] = nums[0];
    } else {
        f[0][0] = nums[0];
    }
    for (int i = 1; i < n; ++i) {
        if (nums[i] % 2) {
            f[i][1] = max(f[i-1][1] + (long)nums[i], f[i-1][0] + (long)nums[i] - (long)x);
            f[i][0] = f[i - 1][0];
            ans = max(ans,max(f[i][1], f[i][0]));
        } else {
            f[i][1] = f[i-1][1];
            f[i][0] = max(f[i-1][0] + (long)nums[i], f[i-1][1] + (long)nums[i] - (long)x);
            ans = max(ans,max(f[i][1], f[i][0]));
        }
    }
    return ans;
}

string minimumString(string a, string b, string c) {
    string ans = "";
    auto merge = [](string s, string t) {
        if (s.find(t) != string::npos)
            return s;
        if (t.find(s) != string::npos)
            return t;
        for (int i = 0; i < s.size(); ++i) {
            if (t[0] != s[i]) continue;
            else {
                if (s.substr(i, s.size() - i) == t.substr(0, s.size() - i)) {
                    s += t.substr(s.size() - i, t.size() - (s.size() - i));
                    return s;
                }
            }
        }
        s += t;
        return s;
    };
    vector<string> vec{a,b,c};


    do {
        string str = merge(merge(vec[0],vec[1]), vec[2]);

        if (ans == "" || str.size() < ans.size() || (str.size() == ans.size() && str < ans)) {
            ans = str;
        }
    }
    while(next_permutation(vec.begin(), vec.end())) ;
    return ans;

}

vector<int> permu(int n, int k) {
    vector<int> vec(n);
    iota(vec.begin(), vec.end(), 1);
    for (int i = 1; i < k; ++i) {
        next_permutation(vec.begin(), vec.end());
    }
    return vec;
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> ans;
    int n = nums.size(), cnt = 1;
    cnt = fact(n);
    for (int i = 0; i < cnt; ++i) {
        ans.emplace_back(nums);
        next_permutation(nums.begin(),nums.end());
    }
    return ans;
}

int countCompleteSubarrays(vector<int>& nums) {
    int ans = 0, n = nums.size();
    unordered_set st(nums.begin(), nums.end());
    int m = st.size();
    unordered_map<int, int> mp;
    for (int l = 0, r = 0; l < n && r < n; ++r) {
        ++mp[nums[r]];
        while (mp.size() >= m) {
            ans += n - r;
            --mp[nums[l]];
            if (mp[nums[l]] == 0) mp.erase(nums[l]);
            ++l;
        }
    }
    return ans;
}

string smallestString(string s) {
    int n = s.size();
    if (*max_element(s.begin(), s.end()) == 'a'){
        s.back() = 'z';
        return s;
    }
    for (int i = 0, j = 0; i < n; ++i) {
        if (s[i] != 'a') {
            for (j = i; j < n; ++j) {
                if (s[j] == 'a') break;
                s[j] = s[j] - 1;
            }
            break;
        }
    }
    return s;

}

long long minCost1(vector<int>& nums, int x) {
    vector<long> num(nums.begin(), nums.end());
    long y = x;
    int n = nums.size();
    vector<vector<long>> f1(n, vector<long>(n));
    for (int i = 0; i < n; ++i) {
        long minTmp = num[i];
        for (int j = 0; j < n; ++j) {
            f1[i][j] = min(minTmp, num[(i + j) % n]);
            minTmp = f1[i][j];
        }
    }
    long ans = accumulate(num.begin(), num.end(), (long)0);
    for (int j = 0; j < n; ++j) {
        long tmp = y * (long)j;
        for (int i = 0; i < n; ++i) {
            tmp += f1[i][j];
        }
        ans = min(ans, tmp);
    }
    return ans;
}

int longestSemiRepetitiveSubstring(string s) {
    int ans = 1, n = s.size();
    for (int i = 0; i < n; ++i) {
        int tmp = 1, cnt = 0;
        for (int j = i + 1; j < n; ++j) {
            if (s[j] == s[j - 1]) {
                ++cnt;
                if (cnt > 1) break;
            }
            ++tmp;
        }
        ans = max(ans, tmp);
    }
    return ans;

}

vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid.front().size();
    vector<vector<int>> ans(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            unordered_set<int> st1, st2;
            for (int p = i + 1, q = j + 1; p < m && q < n; ++p, ++q) {
                st1.insert(grid[p][q]);
            }
            for (int p = i - 1, q = j - 1; p >= 0 && q >= 0; --p, --q) {
                st2.insert(grid[p][q]);
            }
            ans[i][j] = abs((int)st1.size() - (int)st2.size());
        }
    }
    return ans;
}

long long minimumCost(string s) {
    long ans = 0;
    long n = s.size();
    char tmp1 = s.front(), tmp2 = s.back();
    for (long i = 1; i <= n/2; ++i) {
        if (s[i] != tmp1) {
            ans += i;
            tmp1 = s[i];
        }
    }
    for (long i = n - 2; i >= n/2; --i) {
        if (s[i] != tmp2) {
            ans += (n - 1 - i);
            tmp2 = s[i];
        }
    }
    return ans;

}

int minExtraChar(string s, vector<string>& dictionary) {
    int n = s.size();
    unordered_map<string, int> mp;
    for(auto & str : dictionary) {
        ++mp[str];
    }
    vector<int> f(n + 1);
    for (int i = 0; i < n; ++i) {
        f[i+1] = f[i] + 1;
        for(int j = 0; j <= i; ++j) {
            if (mp[s.substr(j, i-j+1)]) {
                f[i+1] = min(f[i+1], f[j]);
            }
        }
    }
    return f[n];
}

long long maxStrength(vector<int>& nums) {
    int n = nums.size(), cnt1 = 0, cnt2 = 0;
    vector<int> vec;
    for (auto & num : nums) {
        if (num == 0) ++cnt1;
        if (num < 0) {
            ++cnt2;
            vec.emplace_back(num);
        }
    }
    if (cnt1 == n || (cnt1 == n- 1 && cnt2 == 1 && cnt1 != 0)) return 0;
    if (cnt2 == 1 && n == 1) return nums[0];
    long ans = 1;
    for (auto & num : nums) {
        if (num != 0) {
            ans *= (long)num;
        }
    }
    if(cnt2 % 2 == 1) {
        sort(vec.rbegin(), vec.rend());
        ans /= (long)vec[0];
    }
    return ans;
}


long long findMaximumElegance(vector<vector<int>>& items, int k) {
    long ans = 0, sum = 0;
    int n = items.size();
    unordered_map<int, int> mp;
    stack<int> st;
    sort(items.begin(), items.end(), [&](auto& vec1, auto& vec2){return vec1[0] > vec2[0];});
    for (int i = 0; i < k; ++i) {
        sum += (long)items[i][0];
        if (!mp[items[i][1]]) {
            ++mp[items[i][1]];
        } else {
            st.push(items[i][0]);
        }
    }
    sum += (long)mp.size() * mp.size();
    ans = sum;
    for (int i = k; i < n; ++i) {
        if (!mp[items[i][1]] && !st.empty()) {
            ++mp[items[i][1]];
            sum += ((long)mp.size() * mp.size() - (long)(mp.size() - 1) * (mp.size() -1));
            sum += (long)(items[i][0] - st.top());
            st.pop();
            ans = max(ans, sum);
        } else if (st.empty()) {
            break;
        }
    }
    return ans;
}


bool doesValidArrayExist(vector<int>& d) {
    int n = d.size();
    if (n == 1) {
        if(d[0]) return false;
        else return true;
    }
    vector<int> vec(n);
    for (int i = 0; i < n -1; ++i) {
        if (d[i] == 1) {
            vec[i+1] = abs(vec[i] -1);
        } else {
            vec[i+1] = vec[i];
        }
    }
    if(d.back() == 1) {
        if (vec.front() != vec.back()) return true;
        else return false;
    } else {
        if (vec.front() != vec.back()) return false;
        else return true;
    }
    return true;
}


int maxMoves(vector<vector<int>>& grid) {
    int ans = 0, m = grid.size(), n = grid[0].size();
    vector<vector<int>> f(m + 1,vector<int>(n+1,0));
    for (int j = n -2; j >= 0; --j) {
        for(int i = 0; i < m; ++i) {
            for (int k = max(i - 1, 0); k <= min(i + 1, m-1); ++k) {
                if (grid[i][j] < grid[k][j+1]) {
                    f[i][j] = max(f[i][j], f[k][j+1] + 1);
                }
            }
        }
    }
    for (int i = 0; i < m;++i) {
        ans = max(ans, f[i][0]);
    }
    return ans;

}

int matrixSum(vector<vector<int>>& nums) {
    int ans = 0, m = nums.size(), n = nums[0].size();
    for (auto& vec: nums) {
        sort(vec.rbegin(), vec.rend());
    }
    for (int j = 0; j < n; ++j) {
        int tmp = 0;
        for(int i = 0; i < m; ++i) {
            tmp = max(tmp, nums[i][j]);
        }
        ans += tmp;
    }
    return ans;

}

long long maximumOr(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long> vec(nums.begin(), nums.end()), suf(n + 1), pre(n+1);
    for (int i = n-1; i >= 0; --i) {
        suf[i] = suf[i+1] | vec[i];
    }
    for (int i = 0; i < n; ++i) {
        pre[i+1] = pre[i] | vec[i];
    }
    long ans = 0, tmp = 0;
    for (int i = 0; i < n; ++i) {
        tmp = pre[i] | suf[i+1] | (vec[i] << k);
        ans = max(ans, tmp);
    }
    return ans;
}


class FrequencyTracker {
    unordered_map<int,int> mp1, mp2;
public:
    FrequencyTracker() {

    }

    void add(int number) {
        mp1[number]++;
        mp2[mp1[number]]++;
        mp2[mp1[number]-1]--;
    }

    void deleteOne(int number) {
        if(mp1[number]) {
            mp1[number]--;
            mp2[mp1[number]]++;
            mp2[mp1[number]+1]--;
        }

    }

    bool hasFrequency(int frequency) {
        return mp2[frequency];
    }
};

vector<int> colorTheArray(int n, vector<vector<int>>& que) {
    int m = que.size(), pre = 0;
    vector<int> ans(m), vec(n);
    for (int i = 0; i < m; ++i) {
        int ind = que[i][0], num = que[i][1];
        if (ind - 1 >= 0) {
            if (vec[ind -1] != 0 && vec[ind -1] == vec[ind]) {
                --pre;
            }
        }
        if (ind + 1 <= n-1) {
            if (vec[ind +1] != 0 && vec[ind +1] == vec[ind]) {
                --pre;
            }
        }
        vec[ind] = num;
        if (ind - 1 >= 0) {
            if (vec[ind -1] != 0 && vec[ind -1] == vec[ind]) {
                ++pre;
            }
        }
        if (ind + 1 <= n-1) {
            if (vec[ind +1] != 0 && vec[ind +1] == vec[ind]) {
                ++pre;
            }
        }
        ans[i] = pre;
    }
    return ans;

}



vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
    int n = A.size();
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j <= i; ++j) {
            cnt += count(A.begin(),A.begin() + i + 1, B[j]);
        }
        ans[i] = cnt;
    }
    return ans;

}


// 网格图模板
int findMaxFish(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size(), ans = 0;
    vector<vector<int>> list = {{-1,0},{1,0},{0,-1},{0,1}};
    vector<vector<int>> vis(m, vector<int>(n));
    function<int(int,int,vector<int>&)> dfs = [&](int i, int j, vector<int>& vec){
        if (grid[i][j] == 0) {
            return 0;
        }
        int sum = grid[i][j];
        vis[i][j] = 1;
        for (auto& v: list) {
            if (i + v[0] < m && i + v[0] >= 0 && j +v[1]>= 0 && j +v[1] < n && vis[i+v[0]][j +v[1]] == 0){
                sum += dfs(i+v[0], j +v[1],vec);
            }
        }
        return sum;
    };
    for (int i = 0; i <m;++i) {
        for(int j = 0; j < n; ++j) {
            vector<int> vec;
            ans = max(ans, dfs(i,j,vec));
        }
    }
    return ans;
}

int numIslands(vector<vector<char>>& grid) {
    int m = grid.size(), n =grid[0].size(), ans = 0;
    vector<vector<int>> list = {{-1,0},{1,0},{0,-1},{0,1}};
    vector<vector<int>> vis(m, vector<int>(n));
    function<int(int,int)> dfs = [&](int i, int j){
        if (grid[i][j] == '0' || vis[i][j]) {
            return 0;
        }
        int sum = 1;
        vis[i][j] = 1;
        for (auto& v: list) {
            if (i + v[0] < m && i + v[0] >= 0 && j +v[1]>= 0 && j +v[1] < n && vis[i+v[0]][j +v[1]] == 0){
                dfs(i+v[0], j +v[1]);
            }
        }
        return sum;
    };
    for (int i = 0; i <m;++i) {
        for(int j = 0; j < n; ++j) {
            ans += dfs(i,j) ;
        }
    }
    return ans;
}

void solve(vector<vector<char>>& board) {
    int m = board.size(), n =board[0].size(), ans = 0;
    vector<vector<int>> list = {{-1,0},{1,0},{0,-1},{0,1}};
    vector<vector<int>> vis(m, vector<int>(n));
    vector<vector<int>> flag(m, vector<int>(n));
    function<void(int,int)> dfs = [&](int i, int j){
        if (board[i][j] == 'X') {
            return ;
        }
        vis[i][j] = 1;
        flag[i][j] = 1;
        for (auto& v: list) {
            if (i + v[0] < m && i + v[0] >= 0 && j +v[1]>= 0 && j +v[1] < n && vis[i+v[0]][j +v[1]] == 0){
                dfs(i+v[0], j +v[1]);
            }
        }
        return ;
    };
    for (int i = 0; i < m; ++i) {
        if (board[i][0] == 'O' && !vis[i][0])
        dfs(i,0);
    }
    for (int i = 0; i < m; ++i) {
        if (board[i][n-1] == 'O' && !vis[i][n-1])
        dfs(i,n-1);
    }
    for (int j = 0; j < n; ++j) {
        if (board[0][j] == 'O' && !vis[0][j])
        dfs(0,j);
    }
    for (int j = 0; j < n; ++j) {
        if (board[m-1][j] == 'O' && !vis[m-1][j])
        dfs(m-1,j);
    }
    for (int i = 0; i <m;++i) {
        for(int j = 0; j < n; ++j) {
            if (!flag[i][j]) {
                board[i][j] = 'X';
            }
        }
    }

    return;
}
// 岛屿最大面积
int maxAreaOfIsland(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size(), ans = 0;
    vector<vector<int>> list = {{-1,0},{1,0},{0,-1},{0,1}};
    vector<vector<int>> vis(m, vector<int>(n));
    function<int(int,int)> dfs = [&](int i, int j){
        if (grid[i][j] == 0) {
            return 0;
        }
        int sum = grid[i][j];
        vis[i][j] = 1;
        for (auto& v: list) {
            if (i + v[0] < m && i + v[0] >= 0 && j +v[1]>= 0 && j +v[1] < n && vis[i+v[0]][j +v[1]] == 0){
                sum += dfs(i+v[0], j +v[1]);
            }
        }
        return sum;
    };
    for (int i = 0; i <m;++i) {
        for(int j = 0; j < n; ++j) {
            if (grid[i][j] && !vis[i][j])
            ans = max(ans, dfs(i,j));
        }
    }
    return ans;
}

int sumOfMultiples(int n) {
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
            ans += i;
        }
    }
    return ans;
}

vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
    vector<int> ans, cnt(101);
    int n = nums.size();
    for (auto& num : nums) {
        num += 50;
    }
    for (int i =0; i < k; ++i) {
        ++cnt[nums[i]];
    }
    int sum = 0;
    for (int i = 0; i <= 100; ++i) {
        sum += cnt[i];
        if (sum >= x) {
            if (i < 50)
                ans.emplace_back(i-50);
            else
                ans.emplace_back(0);
            break;
        }
    }
    for (int i = 0; i <= n-k-1; ++i) {
        --cnt[nums[i]];
        ++cnt[nums[i + k]];
        sum = 0;
        for (int j = 0; j <= 100; ++j) {
            sum += cnt[j];
            if (sum >= x) {
                if (j < 50)
                    ans.emplace_back(j - 50);
                else
                    ans.emplace_back(0);
                break;
            }

        }
    }
    return ans;
}


int maxDivScore(vector<int>& nums, vector<int>& div) {
    sort(div.begin(),div.end());
    int ans = div[0], sum = 0;
    unordered_map<int, int> mp;
    for (auto d : div) {
        if(!mp[d]) {
            for(auto num:nums) {
                if (num % d == 0) {
                    ++mp[d];
                }
            }
            if (mp[d] > sum) {
                sum = mp[d];
                ans = d;
            }
        }
    }
    return ans;
}

int addMinimum(string w) {
    int ans = 0, n = w.size();
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        if (w[i] == 'a') {
            if (i+1 < n) {
                if (w[i+1] == 'b') {
                    ++cnt;
                    if(i+2 < n) {
                        if (w[i+2] == 'c') {
                            ++cnt;
                        } else {
                            ++ans;
                        }
                    } else {
                        ++ans;
                    }
                } else if (w[i+1] == 'c') {
                    ++cnt;
                    ++ans;
                } else {
                    ans +=2;
                }
            } else {
                ans += 2;
            }
        } else if (w[i] == 'b') {
            if (i+1 < n) {
                if (w[i+1] == 'c') {
                    ++cnt;
                    ++ans;
                } else {
                    ans +=2;
                }
            } else {
                ans += 2;
            }
        } else {
            ans +=2;
        }
        i += cnt;
    }
    return ans;
}

vector<long long> findPrefixScore(vector<int>& nums) {
    int n = nums.size();
    vector<long long> ans(n);
    long ma = 0, presum = 0;
    for (int i = 0; i < n; ++i) {
        ma = max(ma, (long)nums[i]);
        presum+= ((long)nums[i]+ma);
        ans[i] = presum;
    }
    return ans;

}

vector<long long> distance(vector<int>& nums) {
    int n = nums.size();
    vector<long long> ans(n);
    unordered_map<long, long> cnt, cnt1, sum, sum1;
    for (long i = 0; i < n; ++i) {
        sum[nums[i]] += i;
        cnt[nums[i]]++;
    }
    for (long i = 0; i < n; ++i) {
        sum1[nums[i]] += i;
        cnt1[nums[i]]++;
        ans[i] = (sum[nums[i]] - sum1[nums[i]])-(i*(cnt[nums[i]]-cnt1[nums[i]]))+ i * (cnt1[nums[i]] -1) - (sum1[nums[i]]-i);
    }
    return ans;
}

int minimizeMax(vector<int>& nums, int p) {

    sort(nums.begin(), nums.end());
    int n = nums.size(), ans = nums.back()-nums[0];
    auto check = [&](int mx){
        int i = 0, cnt = 0;
        while(i < n-1) {
            if (nums[i+1] - nums[i] <= mx) {
                ++cnt;
                i+=2;
            } else {
                ++i;
            }
        }
        return cnt >= p;
    };

    int l = 0, r = nums.back()-nums[0];
    while(l <= r){
        int mid = (l+r)/2;
        if(check(mid)) {
            ans = min(ans,mid);
            r = mid-1;
        } else {
            l = mid+1;
        }
    }
    return ans;

}

int diagonalPrime(vector<vector<int>>& nums) {
    auto check = [&](int num){
        if (num == 1) return false;
        for (int i = 2; i <= sqrt(num);++i) {
            if (num % i == 0) return false;
        }
        return true;
    };
    int ans = 0;
    int m = nums.size(), n = nums[0].size();
    for(int i = 0; i < m; ++i) {
        if(check(nums[i][i])) {
            ans = max(ans,nums[i][i]);
        }
        if (check(nums[i][n-1-i])){
            ans = max(ans, nums[i][n-1-i]);
        }
    }
    return ans;
}

int minEatingSpeed(vector<int>& p, int h) {
    sort(p.begin(), p.end());
    int n = p.size();
    auto check = [&](int mx){
        int cnt = 0;
        for (auto num : p) {
            cnt += (num / mx + (num % mx == 0 ? 0 : 1));
            if (cnt > h) return false;
        }
        return cnt <= h;
    };
    int l = 1,r = p.back(), ans = r;
    while(l<=r){
        int mid = (l+r)/2;
        if(check(mid)){
            ans = min(ans, mid);
            r = mid-1;
        }else {
            l = mid+1;
        }
    }
    return ans;
}

int minimizeArrayValue(vector<int>& nums) {
    vector<long> vec(nums.begin(), nums.end());
    long n = nums.size(), ans = 1e9;
    auto check = [&](long a){
        long tmp = 0;
        for (int i = n-1; i >= 1; --i) {
            if (vec[i] + tmp > a) {
                tmp = vec[i] + tmp - a;
            } else {
                tmp = 0;
            }
        }
        if(vec[0] + tmp > a) return false;
        else return true;
    };
    long l = vec[0], r = *max_element(vec.begin(),vec.end());
    while (l <= r){
        auto mid = (l+r)/2;
        if(check(mid)) {
            ans = min(ans, mid);
            r = mid -1;
        } else {
            l =mid+1;
        }
    }
    return ans;
}


int maxDistance(vector<int>& p, int m) {
    int n = p.size(), ans = 1;
    sort(p.begin(), p.end());
    auto check = [&](int mx){
        int cnt = 1;
        int tmp = p[0];
        for (int i = 1; i < n; ++i) {
            if (p[i] - tmp>=mx) {
                ++cnt;
                tmp = p[i];
            }
        }
        return cnt >= m;
    };
    int l = 1, r = p.back() - p.front();
    while (l <= r){
        int mid = (l+r)/2;
        if(check(mid)) {
            ans = max (ans, mid);
            l = mid +1;
        } else {
            r = mid-1;
        }
    }
    return ans;
}

vector<vector<int>> findMatrix(vector<int>& nums) {
    int n = nums.size(), mx = 0;
    unordered_map<int, int> mp;
    vector<vector<int>> ans;
    for (auto & num:nums){
        mp[num]++;
        mx = max(mp[num], mx);
    }
    while (mx > 0) {
        vector<int> vec;
        for (int i = 1; i <= n; ++i) {
            if(mp[i]) {
                vec.emplace_back(i);
                --mp[i];
            }
        }
        ans.emplace_back(vec);
        --mx;
    }
    return ans;
}

int miceAndCheese(vector<int>& r1, vector<int>& r2, int k) {
    int n = r1.size(), ans = 0;
    vector<int> r3(n);
    for(int i = 0; i < n; ++i) {
        r3[i] = r1[i] - r2[i];
    }
    vector<int> ind(n);
    iota(ind.begin(), ind.end(), 0);
    sort(ind.begin(),ind.end(),[&](int i, int j){return r3[i] > r3[j];});
    unordered_map<int, int> mp;
    for (int i = 0; i < k;++i) {
        mp[ind[i]]++;
    }
    for (int i = 0; i < n;++i) {
        if(mp[ind[i]]) {
            ans += r1[ind[i]];
        } else{
            ans += r2[ind[i]];
        }
    }
    return ans;
}

int maximumCostSubstring(string s, string chars, vector<int>& val) {
    unordered_map<char, int> mp;
    for (int i = 0; i < 26; ++i) {
        mp['a' + i] = i+1;
    }
    int m = val.size(), n = s.size();
    for (int i = 0; i < m; ++i){
        mp[chars[i]] = val[i];
    }
    vector<int> f(n+1);
    for (int i = 0; i < n; ++i) {
        f[i+1] = max(mp[s[i]], f[i]+mp[s[i]]);
    }
    int mx = 0;
    for (auto & a : f){
        mx = max(mx,a);
    }
    return mx;
}

long long makeSubKSumEqual(vector<int>& arr, int k) {
    int n = arr.size();
    k = gcd(n,k);
    long ans = 0;
    for (int i = 0; i < k;++i) {
        vector<int> vec;
        for (int j = i; j < n; j=j+k) {
            vec.emplace_back(arr[j]);
        }
        sort(vec.begin(),vec.end());
        for (auto& a : vec) {
            ans += (long)abs(a-(long)vec[vec.size()/2]);
        }
    }
    return ans;
}

bool primeSubOperation(vector<int>& nums) {
    int n = nums.size();
    auto check = [&](int a){
        for (int i = 2; i <= sqrt(a); ++i){
            if (a % i == 0) return false;
        }
        return true;
    };
    for (int j = nums[0]-1; j>= 2; --j) {
        if (check(j)) {
            nums[0] -= j;
            break;
        }
    }
    for (int i = 1; i < n; ++i) {
        if (nums[i] <= nums[i-1]) return false;
        for (int j = nums[i]-nums[i-1]-1; j>= 2; --j) {
            if (check(j)) {
                nums[i] -= j;
                break;
            }
        }

    }
    return true;
}

vector<long long> minOperations1(vector<int>& nums, vector<int>& q) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<long> sum(n+2);
    for (int i = 0; i < n; ++i) {
        sum[1] += (long)(nums[i]-nums[0]);
    }
    long len = 0;
    for (int i = 1; i < n; ++i) {
        sum[i+1] = sum[i] -(long)(n-i)*(nums[i]-nums[i-1]) + (long)(i)*(nums[i]-nums[i-1]);
    }
    vector<long long> ans;
    for(auto& k : q) {
        auto ind = lower_bound(nums.begin(),nums.end(),k) - nums.begin();
        if (ind == 0) {
            ans.emplace_back(sum[1] + (long)n * (nums[0]-k));
        } else if (ind == n) {
            ans.emplace_back(sum[n] + (long)n * (k-nums[n-1]));
        } else {
            ans.emplace_back(sum[ind+1] + (long)(n-ind) * (nums[ind]-k) - (long)ind *(nums[ind]-k));
        }
    }
    return ans;
}

bool checkValidGrid(vector<vector<int>>& grid) {
    if (grid[0][0] != 0) return false;
    int n = grid.size(), m = n * n;
    int i = 0, j = 0;
    for (int k = 0; k< m -1; ++k) {
        if (i+2< n && j+ 1 < n) {
            if (grid[i+2][j+ 1] == (grid[i][j] + 1)) {
                i = i+2;
                j = j +1;
                continue;
            }
        }
        if (i+2<n && j-1 >=0 ) {
            if (grid[i+2][j- 1] == (grid[i][j] + 1)) {
                i = i+2;
                j = j -1;
                continue;
            }
        }
        if(i+1<n && j-2 >=0 ) {
            if (grid[i+1][j- 2] == (grid[i][j] + 1)) {
                i = i+1;
                j = j -2;
                continue;
            }
        }
        if (i+1< n && j+ 2 < n) {
            if (grid[i+1][j+ 2] == (grid[i][j] + 1)) {
                i = i+1;
                j = j +2;
                continue;
            }
        }
        if (i-2>=0 && j+ 1 < n) {
            if (grid[i-2][j+ 1] == (grid[i][j] + 1)) {
                i = i-2;
                j = j +1;
                continue;
            }
        }
        if (i-2>= 0 && j- 1 >=0) {
            if (grid[i-2][j- 1] == (grid[i][j] + 1)) {
                i = i-2;
                j = j -1;
                continue;
            }
        }
        if (i-1>=0 && j+ 2 < n) {
            if (grid[i-1][j+ 2] == (grid[i][j] + 1)) {
                i = i-1;
                j = j +2;
                continue;
            }
        }
        if (i-1>=0 && j- 2 >=0) {
            if (grid[i-1][j-2] == (grid[i][j] + 1)) {
                i = i-1;
                j = j -2;
                continue;
            }
        }
        return false;
    }
    return true;

}

int beautifulSubsets(vector<int>& nums, int k) {
    int ans= -1, n = nums.size();
    unordered_map<int,int> mp;
    function<void(int)> dfs = [&](int i){
        if (i == n) {
            ++ans;
            return;
        }
        dfs(i+1);
        if(mp[nums[i]+k] == 0 && mp[nums[i]-k] == 0){
            mp[nums[i]]++;
            dfs(i+1);
            mp[nums[i]]--;
        }
    };
    dfs(0);
    return ans;
}

int maximizeGreatness(vector<int>& nums) {
    int ans = 0, n = nums.size();
    sort(nums.rbegin(), nums.rend());
    vector<int> vec = nums;
    for (int i = 1, j = 0; i < n; ++i) {
        if (vec[j] > nums[i]) {
            ++j;
            ++ans;
        }
    }

    return ans;
}

long long findScore(vector<int>& nums) {
    long long ans = 0;
    int n = nums.size();
    vector<int> ind(n);
    iota(ind.begin(),ind.end(), 0);
    sort(ind.begin(), ind.end(), [&](int i, int j){return nums[i] ==  nums[j] ? i < j : nums[i] < nums[j];});
    vector<int> vec(n,1);
    for (int i = 0; i < n; ++i) {
        if (vec[ind[i]] >= 1) {
            ans += (long)nums[ind[i]];
            --vec[ind[i]];
            if (ind[i]-1 >= 0) {
                --vec[ind[i]-1];
            }
            if (ind[i]+1 < n){
                --vec[ind[i]+1];
            }
        }
    }
    return ans;
}


int maxScore(vector<int>& nums) {
    int ans = 0, n = nums.size();
    long sum = 0;
    sort(nums.rbegin(),nums.rend());
    for (int i = 0; i < n; ++i) {
        sum += (long)nums[i];
        if (sum > 0) ans++;
    }
    return ans;
}


long long beautifulSubarrays(vector<int>& nums) {
    long long ans = 0;
    int n = nums.size();
    vector<int> vec(n+1);
    vec[0] = 0;
    if (n == 1 && nums[0] == 0) return 1;
    for (int i = 1; i <= n; ++i) {
        vec[i] = vec[i-1] ^ nums[i-1];
    }
    unordered_map<int,int> mp;
    for (auto num: vec){
        ++mp[num];
        ans += (long)(mp[num]-1);
    }
    return ans;
}


int countWays(vector<vector<int>>& r) {
    int MOD = 1e9+7,cnt = 1, n = r.size();
    long ans = 1;
    sort(r.begin(),r.end(),[&](vector<int>& i, vector<int>& j){return i[0] < j[0];});
    for (int i = 1; i < n;++i){
        if (r[i][0] <= r[i-1][1]) {
            r[i][0] = r[i-1][0];
            r[i][1] = max(r[i][1],r[i-1][1]);
        } else {
            cnt++;
        }
    }
    for (int i = 1; i <= cnt; ++i) {
        ans = (ans * (long)2) % MOD;
    }
    return ans;
}


vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& q) {
    unordered_map<int, vector<int>> mp;
    int n = s.size();
    for(int l = 0; l < n;++l) {
        int x = 0;
        for (int r = l; r < min(l+30, n); ++r){
            x = x << 1 | (s[r]-'0');
            if (mp.find(x) == mp.end() ) {
                mp[x].emplace_back(l);
                mp[x].emplace_back(r);
            } else if ((mp[x][1]-mp[x][0])>(r-l)) {
                mp[x][0] = l;
                mp[x][1] = r;
            }
        }
    }
    vector<vector<int>> ans;
    for (auto& q1:q) {
        int tmp = q1[0] ^ q1[1];
        if(mp.find(tmp) != mp.end()) {
            ans.emplace_back(vector{mp[tmp][0],mp[tmp][1]});
        } else {
            ans.emplace_back(vector{-1,-1});
        }
    }
    return ans;
}


vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& q) {
    vector<vector<int>> d(n+2,vector<int>(n+2));
    for (auto & q1 : q) {
        ++d[q1[0]+1][q1[1]+1];
        ++d[q1[2]+1+1][q1[3]+1+1];
        --d[q1[0]+1][q1[3]+1+1];
        --d[q1[2]+1+1][q1[1]+1];
    }
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < n+1; ++j) {
            d[i][j] += (d[i-1][j]+d[i][j-1]-d[i-1][j-1]);
            ans[i-1][j-1] = d[i][j];
        }
    }
    return ans;
}


int maxStarSum(vector<int>& v, vector<vector<int>>& e, int k) {
    int n = e.size();
    int m = v.size();
    unordered_map<int, priority_queue<int>> mp;
    for (auto & e1 : e) {
        mp[e1[0]].emplace(v[e1[1]]);
        mp[e1[1]].emplace(v[e1[0]]);
    }
    int ans = -1e4, sum = 0;
    for (int i = 0 ; i < m; ++i) {
        sum += v[i];
        if (mp.count(i)) {
            int tmp = k;
            while (!mp[i].empty() && tmp) {
                if(mp[i].top() > 0) {
                    sum += mp[i].top();
                    mp[i].pop();
                    --tmp;
                } else {
                    break;
                }

            }
        }
        ans = max (ans, sum);
        sum = 0;
    }
    return ans;
}

int minScore(int n, vector<vector<int>>& r) {
    vector<unordered_map<int, int>> g(n+1);
    for (auto& r1 : r) {
        g[r1[0]][r1[1]] = r1[2];
        g[r1[1]][r1[0]] = r1[2];
    }
    vector<int> vis(n+1);
    int ans = 1e4;
    function<void(int)> dfs = [&](int i) {
        vis[i] = 1;
        for (auto& it : g[i]) {
            ans = min(ans, it.second);
            if (!vis[it.first]) {
                dfs(it.first);
            }
        }
    };
    for (int j = 1; j <= n; ++j) {
        if (!vis[j]) {
            dfs(j);
        }
    }

    return ans;
}


int bestClosingTime(string c) {
    int n = c.size();
    vector<int> suf(n+1);
    int sum1 = 0;
    for (int i = n-1; i>= 0; --i) {
        if (c[i] == 'Y') {
            ++sum1;
        }
        suf[i] = sum1;
    }
    int sum = n+1, ans = 0, sum2 = 0;
    for (int i = 0; i <=n; ++i) {
        if(i>=1) {
            sum2 += c[i-1] == 'N' ? 1 : 0;
        }
        if (sum2 + suf[i] < sum) {
            sum = sum2 + suf[i];
            ans = i;
        }
    }
    return ans;
}

int longestEqualSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, vector<int>> mp1;
    unordered_map<int, int> mp2;
    for(int i = 0; i < n; ++i) {
        mp1[nums[i]].emplace_back(i);
    }
    int cnt = 0, ans = 1;
    for (auto &it: mp1) {
        vector<int> vec = it.second;
        for (int r = 1, l = 0; r < vec.size(); ++r) {
            cnt += (vec[r]-vec[r-1]-1);
            while (cnt > k) {
                ++l;
                cnt -= (vec[l]-vec[l-1]-1);
            }
            ans = max(ans, r-l+1);
        }
        cnt = 0;
    }
    return ans;
}

int maximizeTheProfit(int m, vector<vector<int>>& o) {
    int n = o.size(), ans = 0;
    vector<int> f(m+1);
    sort(o.begin(),o.end(),[&](vector<int>& a, vector<int>& b){
        return a[1] < b[1];
    });
    f[o[0][1]] = o[0][2];
    for (int i = 1; i <n; ++i) {
        for (int j = o[i-1][1]+1; j < o[i][1];j++) {
            f[j] = f[o[i-1][1]];
        }
        int tmp = f[o[i-1][1]];
        f[o[i][1]] = o[i][2] + (o[i][0]-1 < 0 ? 0 : f[o[i][0]-1]);
        f[o[i][1]] = max(f[o[i][1]], tmp);
    }
    for (int i = 0; i <n; ++i) {
        ans = max(ans, f[o[i][1]]);
    }
    return ans;
}

long long maxTaxiEarnings(int n, vector<vector<int>>& r) {
    int m = r.size();
    long ans = 0;
    vector<long> f(n+1);
    sort(r.begin(),r.end(),[&](vector<int>& a, vector<int>& b){return a[1] < b[1];});
    f[r[0][1]] = r[0][1]-r[0][0]+r[0][2];
    for (int i = 1; i <m; ++i) {
        for (int j = r[i-1][1]+1; j < r[i][1];j++) {
            f[j] = f[r[i-1][1]];
        }
        long tmp = f[r[i-1][1]];
        f[r[i][1]] = (long)(r[i][2]+r[i][1]-r[i][0]) + f[r[i][0]];
        f[r[i][1]] = max(f[r[i][1]], tmp);
    }
    for (int i = 0; i <m; ++i) {
        ans = max(ans, f[r[i][1]]);
    }
    return ans;

}

void minimumFuelCost(vector<vector<int>>& r) {
    int n = r.size()+1;
    unordered_map<int,vector<int>> mp1;
    unordered_map<int,int> mp2;
    for (auto & r1 : r) {
        mp1[r1[0]].emplace_back(r1[1]);
        mp1[r1[1]].emplace_back(r1[0]);
    }
    vector<int> vis(n);
    int cnt = 0;
    function<void(int)> dfs = [&](int i){
        vis[i] = 1;
        mp2[i] = cnt;
        for (auto& it : mp1[i]) {
            if (!vis[it]) {
                ++cnt;
                dfs(it);
                --cnt;
            }
        }
    };
    dfs(0);
    return;
}

long long minimumFuelCost(vector<vector<int>>& r, int s) {
    int n = r.size()+1;
    long ans = 0;
    unordered_map<int,vector<int>> mp1;
    for (auto & r1 : r) {
        mp1[r1[0]].emplace_back(r1[1]);
        mp1[r1[1]].emplace_back(r1[0]);
    }
    vector<int> vis(n);
    function<int(int)> dfs = [&](int i){
        int size = 1;
        vis[i] = 1;
        for (auto& it : mp1[i]) {
            if (!vis[it]) {
               size += dfs(it);
            }
        }
        if (i) {
            ans += (long)((size+s-1) / s);
        }
        return size;
    };
    dfs(0);

    return ans;
}

// 环



class Solution1 {
public:
    int minimumOperations(TreeNode* root) {
        int ans = 0;
        queue<TreeNode*> q;
        q.emplace(root);
        while (!q.empty()) {
            int sz = q.size();
            int cnt = 0;
            vector<int> vec1, vec2;
            unordered_map<int, int> mp;
            for (int i = 0; i < sz; ++i) {
                auto& q1 = q.front();
                vec1.emplace_back(q1->val);
                if (q1->left) {
                    q.emplace(q1->left);
                }
                if (q1->right) {
                    q.emplace(q1->right);
                }
                q.pop();
            }
            vec2 = vec1;
            sort(vec2.begin(), vec2.end());
            for (int i = 0; i < sz; ++i) {
                mp[vec2[i]] = i;
            }
            vector<int> vis(sz);
            for (int i = 0; i < sz; ++i) {
                if (!vis[i]) {
                    int tmp = i;
                    while (!vis[tmp]) {
                        vis[tmp] = 1;
                        tmp = mp[vec1[tmp]];
                    }
                    ++cnt;
                }
            }
            ans += (sz - cnt);

        }
        return ans;
    }
};

int mostProfitablePath(vector<vector<int>>& e, int b, vector<int>& a) {
    int n = e.size();
    unordered_map<int, vector<int>> mp;
    for (auto & e1 : e) {
        mp[e1[0]].emplace_back(e1[1]);
        mp[e1[1]].emplace_back(e1[0]);
    }
    vector<int> path;
    vector<vector<int>> vec;
    vector<int> vis(n+1);
    function<void(int)> dfs1 = [&](int i) {
        if (i == 0) {
            vec.emplace_back(path);
            return;
        }
        for (auto& j : mp[i]) {
            if (!vis[j]) {
                path.emplace_back(j);
                vis[j] = 1;
                dfs1(j);
                path.pop_back();
            }
        }
    };
    path.emplace_back(b);
    vis[b] = 1;
    dfs1(b);
    vector<int> p = vec[0];
    unordered_map<int, int> mp1;
    int m = p.size();
    for (int i = 0; i < m; ++i) {
        mp1[p[i]] = i;
    }
    int ans = a[0];
    int ans1 = -1e9;
    int cnt = 1;
    vector<int> vis1(n+1);
    vis1[0] =1;

    function<void(int)> dfs2 = [&](int i) {
        for (auto& j : mp[i]) {

            if (i && mp[i].size() == 1) {
                ans1 = max(ans, ans1);
            }
            if (!vis1[j]) {
                vis1[j] = 1;
                if (mp1.count(j)) {
                    if (cnt == mp1[j]) {
                        ans += a[j]/2;
                        ++cnt;
                        dfs2(j);
                        --cnt;
                        ans -= a[j]/2;
                    } else if (cnt > mp1[j]) {
                        ans += 0;
                        ++cnt;
                        dfs2(j);
                        --cnt;
                        ans -= 0;
                    } else {
                        ans += a[j];
                        ++cnt;
                        dfs2(j);
                        --cnt;
                        ans -= a[j];
                    }
                } else {
                    ans += a[j];
                    ++cnt;
                    dfs2(j);
                    --cnt;
                    ans -= a[j];
                }
            }
        }

    };

    dfs2(0);
    return ans1;
}


long long totalCost(vector<int>& c, int k, int t) {
    long ans = 0;
    int n = c.size();
    priority_queue<int, vector<int>, greater<>> q1, q2;
    for (int i = 0, j = n-1; i < t; ++i, --j) {
        q1.emplace(c[i]);
        q2.emplace(c[j]);
    }
    int cnt1 = 0, cnt2 = 0;
    if (t * 2 >= n) {
        sort(c.begin(),c.end());
        for (int i = 0; i < k; ++i) {
            ans += (long)c[i];
        }
        return ans;
    }
    for (int i = 0; i <k; ++i) {
        if (t-1+cnt1 < n-t-cnt2-1) {
            if (q1.top() <= q2.top()) {
                ans += (long)q1.top();
                q1.pop();
                ++cnt1;
                q1.emplace(c[t-1+cnt1]);
            } else {
                ans += (long)q2.top();
                q2.pop();
                ++cnt2;
                q2.emplace(c[n-t-cnt2]);
            }
        } else {
            if (!q1.empty() && !q2.empty()) {
                if (q1.top() <= q2.top()) {
                    ans += (long)q1.top();
                    q1.pop();
                } else {
                    ans += (long)q2.top();
                    q2.pop();
                }
            } else if (!q1.empty()) {
                ans += (long)q1.top();
                q1.pop();
            } else {
                ans += (long)q2.top();
                q2.pop();
            }

        }
    }
    return ans;
}

long long makeIntegerBeautiful(long long n, int t) {
    long long x = 0;
    vector<int> vec;
    while(n) {
        vec.emplace_back(n%10);
        n /= 10;
    }
    int m = vec.size();
    int tmp = accumulate(vec.begin(), vec.end(), 0);
    if (tmp <= t) return 0;
    vec.emplace_back(0);
    for (int i = 0; i < m; ++i) {
        x += (long)(10 - vec[i]) * (long)pow((long)10,(long)i);
        vec[i] = 0;
        ++vec[i+1];
        while (vec[i+1] == 10){
            vec[i+1] = 0;
            ++i;
            ++vec[i+1];
        }
        int sum = accumulate(vec.begin(), vec.end(), 0);
        if (sum <= t) return x;
    }
    return x;

}

int destroyTargets(vector<int>& nums, int s) {
    int ans = 0, n = nums.size();
    sort(nums.begin(),nums.end());
    vector<int> vec(nums.begin(),nums.end());
    for (auto& a : vec) {
        a = (a%s);
    }
    unordered_map<int,int> mp, mp2;
    for(int i = 0; i < n;++i) {
        if (!mp2[vec[i]]) {
            mp2[vec[i]] = i+1;
        }
    }
    int cnt = 0, tmp = 0, ind = 0;
    for (auto& a : vec) {
        ++mp[a];
        if (mp[a] > cnt || (mp[a] == cnt && mp2[a] < ind)) {
            cnt = mp[a];
            ind = mp2[a];
            tmp = a;
        }
    }
    for (auto& a : nums) {
        if (a % s == tmp) return a;
    }
    return 1;
}


int minOperations(vector<int>& nums, int t) {
    int ans = 0;
    if (accumulate(nums.begin(),nums.end(),(long)0)<(long)t) return -1;
    unordered_map<int, long> mp;
    sort(nums.begin(),nums.end());
    int n = nums.size();
    auto conv = [&](int i){
        int cnt = 0;
        while(i > 1) {
            ++cnt;
            i /= 2;
        }
        return cnt;
    };
    for (int i = 0; i < n; ++i){
        if(nums[i] == 0) continue;
        mp[conv(nums[i])]++;
    }

    vector<int> vec;
    while(t){
        vec.emplace_back(t%2);
        t /= 2;
    }
    //reverse(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        mp[i] -= vec[i];
    }
    int l = 0, r = 0;
    for (int i = 0; i < 32; ++i) {
        if(mp[i] < 0) {
            l = i;
            while (mp[i] <= 0) {
                ++i;
            }
            --mp[i];
            mp[i+1] += mp[i]/2;
            ans += i-l;
        } else if (mp[i] > 0) {
            mp[i+1] += mp[i]/2;
        }
    }
    return ans;
}

bool sumOfNumberAndReverse(int num) {
    auto rev = [&](int a){
        int b = 0;
        while(a) {
            b *= 10;
            b += (a%10);
            a /= 10;
        }
        return b;
    };

    for (int i = 0; i <= num; ++i) {
        if (i + rev(i) == num) return true;
    }
    return false;

}


string robotWithString(string s) {
    string ans;
    unordered_map<char, int> mp;
    char mn = 'a';
    for (auto c:s){
        ++mp[c];
    }
    stack<char> st;
    for (auto& c : s) {
        --mp[c];
        st.emplace(c);
        while(mn < 'z' && mp[mn]==0){
            ++mn;
        }
        while(!st.empty() && st.top() <= mn){
            ans += st.top();
            st.pop();
        }
    }
    return ans;
}


int minimizeXor(int num1, int num2) {
    int ans = 0,cnt1 = 0, cnt2 = 0;
    auto conv = [&](int a) {
        vector<int> vec;
        while(a) {
            vec.emplace_back(a%2);
            a /= 2;
        }
        return vec;
    };
    vector<int> vec1 = conv(num1);
    vector<int> vec2 = conv(num2);
    for(auto a: vec1) {
        if(a) ++cnt1;
    }
    for(auto a: vec2) {
        if(a) ++cnt2;
    }
    if (cnt2 == cnt1) return num1;
    else if (cnt2 < cnt1){
        ans = num1;
        reverse(vec1.begin(),vec1.end());
        for (int i = 0; i < vec1.size(); ++i) {
            if(vec1[i]) {
                if (cnt2){
                    --cnt2;
                } else {
                    ans -= (int)pow(2,vec1.size()-1-i);
                }
            }
        }
        return ans;
    } else {
        int n = vec1.size();
        cnt2 -= cnt1;
        ans = num1;
        for (int i = 0; i < n; ++i) {
            if (!vec1[i]) {
                if (cnt2) {
                    --cnt2;
                    ans += (int)pow(2,i);
                } else {
                    return ans;
                }
            }
        }
        for (int i = 0; i < cnt2;++i) {
            ans += (int)pow(2,n+i);
        }
        return ans;
    }
    return ans;

}

int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    int sum1 = 0;
    for (auto a : nums2) {
        sum1 ^= a;
    }
    if (m % 2 == 0) {
        sum1 = 0;
    }
    if (n % 2) {
        for (auto a : nums1) {
            sum1 ^= a;
        }
    }
    return sum1;
}


class Solution1_1 {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        unordered_map<int,vector<int>> mp;
        int cnt = 0;
        queue<TreeNode*> q;
        if(root) {
            q.emplace(root);
        }

        while (!q.empty()) {
            int sz = q.size();
            while(sz) {
                if (cnt % 2) {
                    mp[cnt].emplace_back(q.front()->val);
                }
                if (q.front()->left) {
                    q.emplace(q.front()->left);
                }
                if (q.front()->right) {
                    q.emplace(q.front()->right);
                }
                q.pop();
                --sz;
            }
            ++cnt;
        }
        for (int i = 1; i <= cnt; ++i) {
            if(i % 2) {
                reverse(mp[i].begin(),mp[i].end());
            }
        }
        if(root) {
            q.emplace(root);
        }
        cnt = 0;
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i <sz; ++i){
                if (cnt % 2) {
                    q.front()->val = mp[cnt][i];
                }
                if (q.front()->left) {
                    q.emplace(q.front()->left);
                }
                if (q.front()->right) {
                    q.emplace(q.front()->right);
                }
                q.pop();
            }
            ++cnt;
        }
        return root;
    }
};

// 前缀位和， 整数按位转化处理；
vector<int> smallestSubarrays(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    vector<vector<int>> vec1(n, vector<int>(31)), vec2(n, vector<int>(31)),vec3(n, vector<int>(31));
    auto conv = [&](int a, int j){
        int i = 0;
        while(a) {
            vec1[j][i] += a%2;
            vec2[j][i] += a%2;
            vec3[j][i] += a%2;
            a /= 2;
            ++i;
        }
        return;
    };
    for (int j=0; j < n; ++j) {
        conv(nums[j],j);
    }
    for(int i = 1; i < n; ++i) {
        for (int j = 0;  j < 31; ++j) {
            vec1[i][j] += vec1[i-1][j];
        }
    }
    for(int i = n-2; i >= 0; --i) {
        for (int j = 0;  j < 31; ++j) {
            vec2[i][j] += vec2[i+1][j];
        }
    }
    int tmp = n-1;
    for (int i = 0; i < n-1; ++i){
        bool flag = true;
        for (int j = 0; j < 31; ++j) {
            if (vec1[i][j]==0 && vec2[i+1][j] > 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            tmp = i;
            break;
        }
    }
    ans[0] = tmp+1;
    auto check = [&](const vector<int>& a, vector<int> b, vector<int>& c) {
        for (int j = 0; j < 31; ++j){
            b[j] -= a[j];
        }
        for (int j = 0; j < 31; ++j){
            if (b[j] <= 0 && c[j] > 0) return true;
        }
        return false;
    };
    for (int l = 0, r = tmp; l < n-1 && r < n; ++l) {
        r = max(r, l+1);
        while(r < n-1 && check(vec1[l],vec1[r],vec2[r+1])) {
            ++r;
        }
        ans[l+1] = r-l;
    }
    return ans;
}

int minGroups(vector<vector<int>>& vec) {
    int ans = 1;
    vector<int> diff(1e6+3);
    for(auto & a : vec) {
        diff[a[0]+1]++;
        diff[a[1]+1+1]--;
    }
    int dSum = 0;
    for (int i = 1; i<= 1e6+2; ++i) {
        dSum += diff[i-1];
        ans = max(ans,dSum);
    }
    return ans;
}

int longestNiceSubarray(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> vec1(n+1, vector<int>(31)), vec2(n, vector<int>(31));
    auto conv = [&](int a, int j){
        int i = 0;
        while(a) {
            vec1[j+1][i] += a%2;
            vec2[j][i] += a%2;
            a /= 2;
            ++i;
        }
        return;
    };
    for (int j=0; j < n; ++j) {
        conv(nums[j],j);
    }
    for(int i = 1; i < n; ++i) {
        for (int j = 0;  j < 31; ++j) {
            vec1[i][j] += vec1[i-1][j];
            vec2[i][j] += vec2[i-1][j];
        }
    }

    auto check = [&](const vector<int>& a, vector<int> b) {
        for (int j = 0; j < 31; ++j){
            b[j] -= a[j];
        }
        for (int j = 0; j < 31; ++j){
            if (b[j] > 1) return false;
        }
        return true;
    };
    int ans = 1;
    for (int l = 0, r = 0; l < n && r < n; ++l) {
        while(r <= n-1 && check(vec1[l],vec2[r])) {
            ++r;
        }
        ans = max(r-l,ans);
    }
    return ans;
}

// 选/不选 暴力枚举
int maximumRows(vector<vector<int>>& vec, int col) {
    int m = vec.size(), n = vec[0].size(), ans = 0;
    vector<unordered_set<int>> vs(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (vec[i][j]) {
                vs[i].emplace(j);
            }
        }
    }

    auto check = [&](unordered_set<int> s1){
        int cnt = 0;
        for (auto & st: vs){
            for (auto num : st) {
                if (!s1.count(num)) {
                    --cnt;
                    break;
                }
            }
            ++cnt;
        }
        return cnt;
    };
    unordered_set<int> s2;
    function<void(int)> dfs = [&](int i){
        if (i == n) {
            if (s2.size() == col) {
                ans = max(ans, check(s2));
            }
            return;
        }
        dfs(i+1);
        s2.emplace(i);
        dfs(i+1);
        s2.erase(i);
    };
    dfs(0);
    return ans;
}

int garbageCollection(vector<string>& g, vector<int>& t) {
    int ans = 0, t1 = 0, t2 = 0, t3 = 0,cnt1 = 0,cnt2 = 0, cnt3 = 0, n = g.size();
    for (auto& g1 : g) {
        cnt1 += count(g1.begin(),g1.end(),'G');
        cnt2 += count(g1.begin(),g1.end(),'M');
        cnt3 += count(g1.begin(),g1.end(),'P');
    }
    for (int i = 0; i < n; ++i) {
        if (i>=1) {
            if (cnt1) t1 += t[i-1];
            if (cnt2) t2 += t[i-1];
            if (cnt3) t3 += t[i-1];
        }
        cnt1 -= count(g[i].begin(),g[i].end(),'G');
        t1 += count(g[i].begin(),g[i].end(),'G');
        cnt2 -= count(g[i].begin(),g[i].end(),'M');
        t2 += count(g[i].begin(),g[i].end(),'M');
        cnt3 -= count(g[i].begin(),g[i].end(),'P');
        t3 += count(g[i].begin(),g[i].end(),'P');
    }
    return t1+t2+t3;
}

string smallestNumber(string p) {
    string s;
    int n = p.size();
    char tmp = '1';
    auto cntD = [&](int i){
        int cnt = 0;
        for (int j = i; j < n; ++j) {
            if (p[j] == 'D') {
                ++cnt;
            } else break;
        }
        return cnt;
    };

    auto cntI = [&](int i){
        int cnt = 0;
        for (int j = i; j < n; ++j) {
            if (p[j] == 'I') {
                ++cnt;
            } else break;
        }
        return cnt;
    };

    if(p[0] == 'I') {
        s += '1';
        tmp = '1';
        int cnt = 0;
        char mx = tmp;
        for (int i = 0; i <n; ++i){
            cnt = 0;
            if (p[i] == 'I') {
                cnt = cntD(i+1);
                s += (mx+cnt+1);
                mx += cnt+1;
                tmp = mx;
            } else {
                s += (tmp-1);
                tmp -= 1;
            }
        }
    } else {
        int cnt = cntD(0);
        tmp = '1'+cnt;
        s += tmp;
        char mx = tmp;
        for(int i = 0; i < n; ++i) {
            cnt = 0;
            if (p[i] == 'I') {
                cnt = cntD(i+1);
                s += (mx+cnt+1);
                mx += cnt+1;
                tmp = mx;
            } else {
                s += (tmp-1);
                tmp -= 1;
            }
        }
    }
    return s;
}

long long countInterestingSubarrays(vector<int>& nums, int m, int k) {
    int n = nums.size();
    for (auto & a : nums) {
        a = (a % m == k);
    }
    vector<int> pre(n+1);
    for (int i = 0; i <n; ++i) {
        pre[i+1] += (pre[i]+nums[i]);
    }
    unordered_map<long,long> mp;
    long long ans = 0;
    for (int i = 0; i <= n; ++i) {
        if (mp[(pre[i]%m+m-k)%m]) {
            ans += mp[(pre[i]%m+m-k)%m];
        }
        ++mp[pre[i]%m];
    }
    return ans;
}

long long taskSchedulerII(vector<int>& t, int s) {
    long ans = 0;
    int n = t.size();
    unordered_map<long , long> mp;
    for (int i =0; i < n; ++i){
        ++ans;
        if (mp[t[i]]) {
            ans = max(ans, mp[t[i]]+(long)s+1);
        }
        mp[t[i]] = ans;
    }
    return ans;
}


// 自定义 cmp 算子, 结合 decltype
auto cmp_1 = [](pair<string, int> p1 ,pair<string, int> p2  ){
    return (p1.second>p2.second || (p1.second==p2.second && p1.first < p2.first));
};

class FoodRatings {
public:

    unordered_map<string, string> mp1;
    unordered_map<string, int> mp3;
    unordered_map<string, set<pair<string,int>, decltype(cmp_1)>> mp2;
    FoodRatings(vector<string>& f, vector<string>& c, vector<int>& r) {
        int n = f.size();
        for (int i = 0; i <n; ++i){
            mp1[f[i]] = c[i];
            mp3[f[i]] = r[i];
            mp2[c[i]].emplace(f[i],r[i]);
        }

    }

    void changeRating(string f1, int r1) {
        string c = mp1[f1];
        int r = mp3[f1];
        mp3[f1] = r1;
        mp2[c].erase(pair<string, int>(f1,r));
        mp2[c].emplace(f1,r1);
    }

    string highestRated(string c1) {
        return (*(mp2[c1].begin())).first;
    }
};

class NumberContainers {
public:
    unordered_map<int,int> mp1;
    unordered_map<int, set<int>> mp2;
    NumberContainers() {

    }

    void change(int i, int num) {
        int tmp = mp1[i];
        mp1[i] = num;
        if (tmp) {
            mp2[tmp].erase(i);
        }
        mp2[num].emplace(i);
    }

    int find(int num) {
        if (mp2[num].empty()) return -1;
        else return *mp2[num].begin();
    }
};

vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& q) {
    int m = nums.size(), n = q.size(), l = nums[0].size();
    vector<int> ans(n);
    int ind = 0;
    string s;
    for (int i = 0; i <n; ++i) {
        int k = q[i][0], t = q[i][1];
        vector<pair<string,int>> vec(m);
        for (int j = 0; j < m; ++j) {
            vec[j] = pair<string,int>(nums[j].substr(l-t,t),j);
        }
        sort(vec.begin(),vec.end());
        ans[i] = vec[k-1].second;
    }
    return ans;
}

long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
    long long ans = 0;
    int n = nums1.size();
    long k = k1+k2;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        vec[i] = abs(nums1[i]-nums2[i]);
    }
    sort(vec.rbegin(),vec.rend());
    vec.emplace_back(0);
    vector<long> pre(n+1);
    pre[0] = vec[0];
    for (int i = 1; i <= n; ++i) {
        pre[i] += (long)vec[i]+pre[i-1];
    }
    long tmp = 0, m = 0;
    if (pre[n] <= k) return 0;
    if (pre[0] - vec[1] >= k) {
        vec[0] -= k;
    } else {
        for (int i = n-1; i >= 0; --i) {
            if (pre[i] - (long)(i+1)*vec[i+1] <= k) {
                tmp = (pre[i+1]-k)/(i+2);
                m = (pre[i+1]-k)%(i+2);
                for (int j = 0; j <= i+1; ++j) {
                    vec[j] = tmp;
                    vec[j] += (m>0);
                    --m;
                }
                break;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        ans += (long)vec[i] * (long)vec[i];
    }
    return ans;
}

int numberOfWays(int s, int e, int k) {
    int MOD = 1e9+7;
    s += 1000;
    e += 1000;
    vector<vector<int>> f (1002,vector<int>(3002));
    f[0][s] = 1;
    for (int i = 1; i <= k; ++i) {
        for (int j = s-i; j <= s+i; ++j) {
            f[i][j] = (f[i-1][j-1] + f[i-1][j+1]) % MOD;
        }
    }
    return f[k][e];
}

class Bitset {
public:
    vector<int> vec;
    int cnt = 0;
    int f = 0,sum = 0;
    int n = 0;

    Bitset(int size) {
        n = size;
        vec.resize(n);
    }

    void fix(int i) {
        if (f == vec[i]) {
            vec[i] ^= 1;
            ++sum;
        }
    }

    void unfix(int i) {
        if (vec[i] != f) {
            vec[i] ^= 1;
            --sum;
        }
    }

    void flip() {
         f ^= 1;
        sum = n - sum;
    }

    bool all() {
        return sum == n;
    }

    bool one() {
        return sum;
    }

    int count() {
        return sum;
    }
    string toString() {
        string s;
        for (int i = 0; i < n; ++i) {
            int tmp = vec[i] ^ f;
            s += '0'+(tmp-0);
        }
        return s;
    }
};

int minAreaRect(vector<vector<int>>& p) {
    int ans = 2e9;
    map<int, map<int,int>> mp;
    for (auto &p1 : p) {
        mp[p1[0]][p1[1]]++;
    }
    int l = 4e4+1, w = 4e4+1;
    auto f = [&](map<int,int> mp1, map<int,int> mp2){
        int t1 = -1;
        for (auto it = mp1.begin(); it != mp1.end(); ++it){
            if (mp2[it->first]) {
                if (t1 != -1) {
                    l = min(l, it->first-t1);
                    t1 = it->first;
                } else {
                    t1 = it->first;
                }
            }
        }
        return l;
    };
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        for (auto j = next(it,1); j != mp.end(); ++j){
            w = j->first - it->first;
            l = 4e4+1;
            l = f(mp[it->first], mp[j->first]);
            if(l != 4e4+1){
                ans = min(ans, l * w);
            }
        }
    }
    return ans == 2e9 ? 0 : ans;

}

int longestArithSeqLength(vector<int>& nums) {
    int n = nums.size(), ans = 0;
    unordered_map<int,int> f[n];
    for(int i = n-2; i >= 0; --i){
        for (int j = i+1; j < n; ++j){
            int d = nums[j]-nums[i];
            if (!f[i].count(d)) {
                f[i][d] = f[j][d] == 0 ? 2 : f[j][d]+1;
                ans = max(ans,f[i][d]);
            }
        }
    }
    return ans;
}

string decodeCiphertext(string e, int row) {
    int n = e.size(), col = n/row;
    if (n == 0) return "";
    string s;
    vector<vector<char>> vec(row, vector<char>(col));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            vec[i][j] = e[col*i+j];
        }
    }
    for (int j = 0; j< col; ++j) {
        for (int i = 0; i < row; ++i) {
            if (j+i >= col) break;
            s += vec[i][j+i];
        }
    }
    int k = s.find_last_not_of(' ');
    return s.substr(0,k+1);
}

int maxSumDivThree(vector<int>& nums) {
    int n = nums.size(), ans = 0;
    vector<int> vec1,vec2;
    for (auto &a : nums) {
        if (a % 3 == 0) ans += a;
        else if (a % 3 == 1) {
            vec1.emplace_back(a);
        } else {
            vec2.emplace_back(a);
        }
    }
    sort(vec1.rbegin(),vec1.rend());
    sort(vec2.rbegin(), vec2.rend());
    int m1 = vec1.size(), m2 = vec2.size();
    if (m1 <= m2) {
        ans += accumulate(vec1.begin(),vec1.end(),0);
        ans += accumulate(vec2.begin(),vec2.end(),0);
        int t = (m2 -m1)%3;
        if (t == 1) {
            int tmp = min(vec2[m2-1],m1 >= 2 ? vec1[m1-1]+vec1[m1-2] : (int)1e4+1);
            ans -= tmp;
        } else if(t == 2){
            int tmp = min(vec2[m2-1]+vec2[m2-2],m1 >= 1? vec1[m1-1] : (int)2e4+1);
            ans -= tmp;
        }
        return ans;
    } else {
        ans += accumulate(vec1.begin(), vec1.end(), 0);
        ans += accumulate(vec2.begin(), vec2.end(), 0);
        int t = (m1 - m2) % 3;
        if (t == 1) {
            int tmp = min(vec1[m1 - 1], m2 >= 2 ? vec2[m2 - 1] + vec2[m2 - 2] : (int)1e4+1);
            ans -= tmp;
        } else if (t == 2) {
            int tmp = min(vec1[m1 - 1] + vec1[m1 - 2], (m2 >= 1 ? vec2[m2 - 1] : (int)2e4+1));
            ans -= tmp;
        }
        return ans;
    }
    return ans;
}

int bagOfTokensScore(vector<int>& t, int p) {
    int ans = 0, n = t.size();
    sort(t.begin(),t.end());
    for (int i = 0,j =n-1; i <= j;) {
        if (p >= t[i]) {
            p -= t[i];
            ++ans;
            ++i;
        } else {
            if (i==j) return ans;
            if (ans <= 0) return 0;
            else {
                --ans;
                p += t[j];
                --j;
            }
        }
    }
    return ans;
}

vector<int> findBall(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    vector<int> ans(n);
    for (int j = 0; j < n; ++j) {
        int k = j;
        for (int i = 0; i< m; ++i) {
            if (g[i][k] == 1) {
                if (k == n-1) {
                    ans[j] = -1;
                    break;
                } else if (g[i][k+1] == -1) {
                    ans[j] = -1;
                    break;
                } else {
                    ++k;
                }
            } else {
                if (k == 0) {
                    ans[j] = -1;
                    break;
                } else if (g[i][k-1] == 1) {
                    ans[j] = -1;
                    break;
                } else {
                    --k;
                }
            }
        }
        ans[j] = ans[j] == -1 ? -1 : k;
    }
    return ans;
}

vector<vector<int>> rotateGrid(vector<vector<int>>& g, int k) {
    int m = g.size(), n = g[0].size();
    vector<vector<int>> vec(m,vector<int>(n));
    auto f = [&](int i, int j, int l, int w,int k1) {
        int i1 = i, j1 = j;
        while(k1 > 0) {
            if ((m-l)/2 < i && i < m/2+l/2-1) {
                if (j == (n-w)/2) {
                    ++i;
                    --k1;
                    continue;
                } else {
                    --i;
                    --k1;
                    continue;
                }
            } else {
                if (i == (m-l)/2) {
                    if (j == (n-w)/2) {
                        ++i;
                        --k1;
                        continue;
                    } else {
                        --j;
                        --k1;
                        continue;
                    }
                } else {
                    if (j == (n+w)/2-1) {
                        --i;
                        --k1;
                        continue;
                    } else {
                        ++j;
                        --k1;
                        continue;
                    }
                }
            }
        }
        vec[i][j] = g[i1][j1];
    };

    for (int i =0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int tmp = min(min(i,m-1-i),min(j,n-1-j));
            int l = m - tmp*2;
            int w = n - tmp*2;
            int k1 = k %((l+w-2)*2);
            f(i,j,l,w,k1);
        }
    }
    return vec;
}

class ThroneInheritance {
public:
    unordered_map<string,vector<string>> mp;
    unordered_map<string,int> mp1;
    string k1;
    ThroneInheritance(string k) {
        k1 = k;

    }

    void birth(string p, string c) {
        mp[p].emplace_back(c);
    }

    void death(string name) {
        mp1[name] = 1;
    }

    vector<string> getInheritanceOrder() {
        vector<string> ans;
        if (!mp1[k1]) ans.emplace_back(k1);
        function<void(string)> dfs = [&](string s){
            if (mp.count(s) == 0) {
                return;
            }
            for (int j = 0; j < mp[s].size(); ++j) {
                if (!mp1[mp[s][j]]) {
                    ans.emplace_back(mp[s][j]);
                }
                dfs(mp[s][j]);
            }
        };
        dfs(k1);
        return ans;
    }
};

vector<int> circularPermutation(int n, int s) {
    vector<int> vec((int)(pow(2,n)));
    vec[0] = s;
    unordered_map<int,int> mp;
    mp[s]++;
    for (int i =1 ; i < vec.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            if (!mp[vec[i-1] ^ (int)pow(2,j)]) {
                mp[vec[i-1] ^ (int)pow(2,j)]++;
                vec[i] = vec[i-1] ^ (int)pow(2,j);
                break;
            }
        }
    }
    return vec;
}

int minSideJumps1(vector<int>& o) {
    int ans = 0, n = o.size();
    vector<vector<int>> vec(3);
    for (int i = 0; i < n; ++i) {
        if (o[i]) {
            vec[o[i]-1].emplace_back(i);
        }
    }
    int ind = 1;
    for (int i =0; i<n-1; ++i) {
        if (o[i+1]-1 == ind) {
            if (ind == 0) {
                if (o[i]-1 == 1) {
                    ++ans;
                    ind = 2;
                } else if (o[i]-1 == 2) {
                    ++ans;
                    ind = 1;
                } else {
                    auto it1 = lower_bound(vec[1].begin(),vec[1].end(),i);
                    auto it2 = lower_bound(vec[2].begin(),vec[2].end(),i);
                    if (it1 == vec[1].end() || (it2 != vec[2].end() && *it1 > *it2)) {
                        ++ans;
                        ind = 1;
                    } else {
                        ++ans;
                        ind = 2;
                    }
                }
            } else if (ind == 1) {
                if (o[i]-1 == 0) {
                    ++ans;
                    ind = 2;
                } else if (o[i]-1 == 2) {
                    ++ans;
                    ind = 0;
                } else {
                    auto it1 = lower_bound(vec[0].begin(),vec[0].end(),i);
                    auto it2 = lower_bound(vec[2].begin(),vec[2].end(),i);
                    if (it1 == vec[0].end() || (it2 != vec[2].end() && *it1 > *it2)) {
                        ++ans;
                        ind = 0;
                    } else {
                        ++ans;
                        ind = 2;
                    }
                }
            } else {
                if (o[i]-1 == 1) {
                    ++ans;
                    ind = 0;
                } else if (o[i]-1 == 0) {
                    ++ans;
                    ind = 1;
                } else {
                    auto it1 = lower_bound(vec[0].begin(),vec[0].end(),i);
                    auto it2 = lower_bound(vec[1].begin(),vec[1].end(),i);
                    if (it1 == vec[0].end() || (it2 != vec[1].end() && *it1 > *it2)) {
                        ++ans;
                        ind = 0;
                    } else {
                        ++ans;
                        ind = 1;
                    }
                }
            }
        }
    }
    return ans;
}

vector<int> findDiagonalOrder(vector<vector<int>>& vec) {
    vector<int> ans;
    int mx = 0;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j){
            mx = max(mx, i+j);
        }
    }
    vector<vector<int>> vec1(mx+1);
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j){
            vec1[i+j].emplace_back(vec[i][j]);
        }
    }
    for (auto& vec2 : vec1) {
        reverse(vec2.begin(),vec2.end());
    }
    for (auto& vec2 : vec1) {
        for (auto & a : vec2) {
            ans.emplace_back(a);
        }
    }
    return ans;
}

long long maxAlternatingSum(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    long long ans = 0;
    vector<vector<int>> vec(2);
    int k = 0, n = nums.size();
    for (int i = 0; i < n-1; ++i) {
        if (!k) {
            if (nums[i] > nums[i+1]) {
                vec[k].emplace_back(nums[i]);
                k ^= 1;
            } else if (i == n-2) {
                vec[k].emplace_back(nums[n-1]);
            }
        } else {
            if (nums[i] < nums[i+1]) {
                vec[k].emplace_back(nums[i]);
                k ^= 1;
                if (i+1 == n-1) {
                    vec[k].emplace_back(nums[n-1]);
                }
            }
        }
    }
    ans = accumulate(vec[0].begin(),vec[0].end(),(long)0) - accumulate(vec[1].begin(),vec[1].end(),(long)0);
    return ans;
}

bool canArrange(vector<int>& a, int k) {
    int n = a.size();
    unordered_map<int,int> mp;
    for (auto& a1 : a) {
        // 统一余数可能为负的情况，变为正数
        a1 = (a1 % k+k)%k;
        ++mp[a1];
    }
    for (auto& a1 : a) {
        if (a1 == (k-a1)%k){
            if (mp[a1] % 2) return false;
        } else {
            if (mp[a1] != mp[k-a1]) return false;
        }
    }
    return true;
}

int maxRepOpt1(string s) {
    int ans = 1, n = s.size();
    unordered_map<int,vector<int>> mp;
    for (int i = 0; i < n; ++i) {
        mp[s[i]].emplace_back(i);
    }
    for (auto & mp1 : mp){
        auto vec = mp1.second;
        int mx = 1, tmp = 0, cnt1 = 0,cnt2 = 0;
        bool flag = false;
        for (int i = 0; i < vec.size()-1; ++i){
            if (vec[i+1] - vec[i] == 1) {
                ++mx;
                if (cnt2 >= 1 || cnt1 >= 2) {
                    ans = max(ans, mx+tmp+1);
                } else {
                    ans = max(ans, mx+tmp);
                }
            } else if (vec[i+1] - vec[i] == 2) {
                ++cnt1;
                ans = max(ans, mx+tmp+1);
                tmp = mx;
                mx = 1;
                if (cnt2 >= 1 || cnt1 >= 2) {
                    ans = max(ans, mx+tmp+1);
                }
            } else {
                ++cnt2;
                ans = max(ans, mx+tmp+1);
                mx = 1;
                tmp = 0;
            }
        }
    }
    return ans;
}

int maxChunksToSorted(vector<int>& a) {
    int n = a.size(), ans = 0;
    vector<int> vec(n,-1);
    vec[0] = a[0];
    for (int i = 1; i < n; ++i) {
        auto b = a[i];
        bool flag = false;
        for (int j = 0; j < n; ++j) {
            if (b < vec[j] && !flag) {
                vec[j] = *max_element(vec.begin()+j,vec.end());
                flag = true;
                continue;
            } else {
                if (!flag) {
                    if (vec[j] == -1) {
                        vec[j] = b;
                        break;
                    }
                }
            }
            if (flag) {
                vec[j] = -1;
            }
        }
    }
    for (auto& c : vec) {
        if (c != -1) {
            ++ans;
        }
    }
    return ans;
}

vector<vector<int>> getAncestors1(int n, vector<vector<int>>& e) {
    vector<vector<int>> vec(n);
    unordered_map<int, vector<int>> g;
    for (auto & e1 : e) {
        g[e1[1]].emplace_back(e1[0]);
    }

    function<void(set<int>& v, int i,vector<int> & mark)> dfs = [&](set<int>& v, int i,vector<int> & mark){
        if (g[i].empty()) {
            return;
        }
        for (auto &a : g[i]) {
            if (!mark[a]) {
                mark[a] = 1;
                v.emplace(a);
                dfs(v,a,mark);
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        vector<int> mark(n);
        set<int> s;
        dfs(s,i,mark);
        vec[i].assign(s.begin(),s.end());
    }
    return vec;
}

/**
 * 逆向思维： 从结果出发
 * @param g
 * @return
 */
int maxEqualRowsAfterFlips(vector<vector<int>>& g) {
    int ans = 0, n = g[0].size();
    unordered_map<bitset<300>, int> mp;
    for (auto & g1 : g) {
        bitset<300> b;
        for (int i = 0; i < n; ++i) {
            b[i] = g1[i] ^ g1[0];
        }
        ans = max(ans,++mp[b]);
    }
    return ans;
}

struct myComparator
{
    int operator()( const tuple<int, int,
        int>& i,
                    const tuple<int, int,
                       int>& j) const
    {
        auto [i1,j1,k1] = i;
        auto [i2,j2,k2] = j;
        if (j1 < j2) {
            return true;
        } else if (j1 == j2 && k1 < k2) {
            return true;
        } else {
            return false;
        }
    }
};

vector<int> getOrder(vector<vector<int>>& t) {
    int n = t.size();
    vector<int> ans;
    vector<tuple<int,int,int>> vec(n);
    for (int i = 0; i < n; ++i) {
        vec[i] = tuple<int,int,int>(t[i][0], t[i][1], i);
    }


    auto cmp2  = [](const tuple<int,int,int>& i, const tuple<int,int,int>& j) {
        auto [i1,j1,k1] = i;
        auto [i2,j2,k2] = j;
        if (j1 < j2) {
            return false;
        } else if (j1 == j2 && k1 < k2) {
            return false;
        } else {
            return true;
        }
    };

    auto cmp1 = [](const tuple<int,int,int>& i, const tuple<int,int,int>& j) {
        auto [i1,j1,k1] = i;
        auto [i2,j2,k2] = j;
        if (i1 < i2) {
            return true;
        } else if (i1 == i2 && j1 < j2) {
            return true;
        } else if (i1 == i2 && j1 == j2 && k1 < k2){
            return true;
        } else {
            return false;
        }
    };

    sort(vec.begin(),vec.end(),cmp1);
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>, decltype(cmp2)> st;
    st.emplace(vec[0]);
    long ind = 1, tmp = get<0>(vec[0]);
    while (1) {
        auto [i,j,k] = st.top();
        tmp = max(tmp,(long)i);
        tmp += (long)j;
        st.pop();
        ans.emplace_back(k);
        if (ans.size() == n) return ans;
        while (ind < n) {
            auto[i1,j1,k1] = vec[ind];
            if (i1 <= tmp) {
                st.emplace(vec[ind]);
                ++ind;
            } else {
                break;
            }
        }
        if (st.empty() && ind < n) {
            st.emplace(vec[ind]);
            ++ind;
        }
    }
}

int minProcessingTime(vector<int>& p, vector<int>& t) {
    int ans = 0;
    sort(p.begin(),p.end());
    sort(t.rbegin(),t.rend());
    for (int i = 0; i < p.size(); ++i) {
        for (int j = i *4; j < (i+1)*4; ++j) {
            ans = max(ans, p[i]+t[j]);
        }
    }
    return ans;
}

int minOperations(vector<int> &nums1, vector<int> &nums2) {
    int ans = 0, n1 = nums1.size(), n2 = nums2.size();
    int nMi = min(n1, n2), nMa = max(n1, n2);
    if (nMi * 6 < nMa) return -1;
    int sum1 = accumulate(nums1.begin(), nums1.end(), 0), sum2 = accumulate(nums2.begin(), nums2.end(), 0);
    int dSum = abs(sum1 - sum2);
    if (dSum == 0) return 0;

    vector<int> d1(n1);
    for (int i = 0; i < n1; ++i) {
        d1[i] = sum1 > sum2 ? nums1[i] - 1 : 6 - nums1[i];
    }
    vector<int> d2(n2);
    for (int i = 0; i < n2; ++i) {
        d2[i] = sum1 > sum2 ? 6 - nums2[i] : nums2[i] - 1;
    }
    vector<int> d(n1 + n2);
    for (int i = 0; i < n1 + n2; ++i) {
        if (i < n1) {
            d[i] = d1[i];
        } else {
            d[i] = d2[i - n1];
        }
    }
    sort(d.rbegin(), d.rend());
    for (int i = 0; i < n1 + n2; ++i) {
        dSum -= d[i];
        if (dSum <= 0) return i + 1;
    }
    return ans;
}

vector<vector<int>> constructProductMatrix(vector<vector<int>>& g) {
    int mod = 12345;
    int m = g.size(), n = g[0].size();
    vector<vector<int>> ans(m,vector<int>(n)), pre(m,vector<int>(n)),suf(m,vector<int>(n));
    pre[0][0] = 1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j==0) continue;
            if (j == 0){
                pre[i][j] = (pre[i-1][n-1]%mod)*(g[i-1][n-1]%mod)%mod;
            } else {
                pre[i][j] = (pre[i][j-1]%mod)*(g[i][j-1]%mod)%mod;
            }
        }
    }
    suf[m-1][n-1] = 1;
    for (int i = m-1; i >= 0; --i) {
        for (int j = n-1; j >= 0; --j) {
            if (i == m-1 && j==n-1) continue;
            if (j == n-1){
                suf[i][j] = (suf[i+1][0]%mod)*(g[i+1][0]%mod)%mod;
            } else {
                suf[i][j] = (suf[i][j+1]%mod)*(g[i][j+1]%mod)%mod;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            ans[i][j] = (pre[i][j]*suf[i][j])%mod;
        }
    }
    return ans;
}

// 滑窗 + 动态规划
int minSumOfLengths(vector<int>& a, int t) {
    int n = a.size();
    vector<pii> vec;
    int tmp = 0;
    for (int r = 0,l = 0; r < n; ++r ){
        tmp += a[r];
        while (tmp >= t) {
            if (tmp ==t) {
                vec.emplace_back(l,r);
            }
            tmp -= a[l];
            ++l;
        }
    }
    sort(vec.begin(),vec.end());
    int m = vec.size();
    if (m < 2) return -1;
    int ans = 1e6;
    vector<int> f(n+1);
    f[vec[m-1].fi] = vec[m-1].se-vec[m-1].fi+1;
    for (int j = vec[m-1].se; j > vec[m-1].fi; --j) {
        f[j] = 1e6;
    }
    for (int i = m-2; i >= 0; --i) {
        if (vec[i].se < vec[i+1].fi) {
            f[vec[i].se+1] = f[vec[i+1].fi];
            for (int j = vec[i].se; j > vec[i].fi; --j){
                f[j] = f[j+1];
            }
            f[vec[i].fi] = min(f[vec[i].fi+1], vec[i].se-vec[i].fi+1);
        } else {
            for (int j = vec[i+1].fi-1; j > vec[i].fi; --j){
                f[j] = f[j+1];
            }
            f[vec[i].fi] = min(f[vec[i].fi+1], vec[i].se-vec[i].fi+1);
        }
        ans = min(ans, vec[i].se-vec[i].fi+1+f[vec[i].se+1]);
    }
    return ans == 1e6 ? -1 : ans;
}

// 前缀和 + 哈希记录 (pre[i] - target)
int maxNonOverlapping(vector<int>& nums, int t) {
    int n = nums.size(), ans = 0;
    vector<int> pre(n);
    pre[0] = nums[0];
    for (int i = 1; i < n; ++i){
        pre[i] = pre[i-1]+nums[i];
    }
    unordered_set<int> st;
    st.emplace(0);
    for (int i = 0; i < n; ++i) {
        if (st.count(pre[i]-t)){
            ++ans;
            st.clear();
            st.emplace(pre[i]);
        } else {
            st.emplace(pre[i]);
        }
    }
    return ans;
}

int sumCounts1(vector<int>& a) {
    int mod = 1e9+7;
    int ans = 0, n = a.size();
    for (int i = 0; i < n; ++i) {
        unordered_set<int> st;
        for (int j = i; j < n; ++j) {
            st.emplace(a[j]);
            ans = (ans + st.size()*st.size())%mod;
        }
    }
    return ans;

}

int minChanges(string s) {
    int ans = 0, n = s.size();
    for (int i = 0;i < n; i += 2) {
        if (s[i] != s[i+1]) ++ans;
    }
    return ans;
}

int lengthOfLongestSubsequence(vector<int>& a, int t) {
    int ans = 0, n = a.size();
    int memo[(int)(1e3+2)][(int)(1e3+2)];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j) {
        if (j < 0) return -(n+1);
        if (i < 0) {
            if (j > 0) return -(n+1);
            return 0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        return res = max(dfs(i-1,j-a[i])+1, dfs(i-1,j));
    };
    ans = dfs(n-1,t);
    return ans < 0? -1 : ans;
}

//int lengthOfLIS(vector<int>& a) {
//    int n = a.size();
//    int memo[n+1][n+2];
//    memset(memo, -1, sizeof(memo));
//    function<int(int,int)> dfs = [&](int i, int j){
//        if (i < 0) return 0;
//        if (memo[i][j] != -1) return memo[i][j];
//        int& res = memo[i][j];
//        if (j == 0 || a[i] < a[j]) {
//            res = max(dfs(i-1,i)+1,dfs(i-1,j));
//        } else {
//            res = dfs(i-1,j);
//        }
//        return res;
//    };
//    return dfs(n-1,0);
//}

int maximumXorProduct(long long a, long long b, int n) {
    long mod = 1e9+7;
    long a1 = max(a,b), b1 = min(a,b);
    auto s1 = bitset<51>(a1).to_string();
    auto s2 = bitset<51>(b1).to_string();
    long cnt = 51;
    // 注意首尾下标
    for (long i = 0; i <= 50; ++i) {
        if(s1[i] == '1') {
            cnt = i;
            break;
        }
    }
    cnt = 50 - cnt;
    bool flag = false;
    for (long i = 0; i < 51-n; ++i) {
        if (s1[i] != s2[i]) {
            flag = true;
            break;
        }
    }
    for (long i = 51-n; i <= 50; ++i) {
        if (s1[i] =='0' && s2[i] =='0') {
            s1[i] = '1', s2[i] = '1';
        }
        if (s1[i] == '1' && s2[i] == '0') {
            if (!flag) {
                flag = true;
            } else {
                s1[i] ='0', s2[i] = '1';
            }
        }
    }
    long ans1 = 0, ans2 = 0;
    for (long i = 50; i >= 0; --i) {
        if (s1[i] == '1') {
            ans1 += pow(2,50-i);
        }
        if (s2[i] == '1') ans2 += pow(2,50-i);
    }
    return (ans1%mod) * (ans2%mod) % mod;
}

// 小顶堆
vector<int> leftmostBuildingQueries1(vector<int>& h, vector<vector<int>>& q) {
    int n = h.size(), m = q.size();
    vector<int> ans(m,-1);
    vector<vector<pair<int,int>>> vec(n); // 记录高度和编号
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq; // 小顶堆
    for (int i = 0; i < m; ++i) {
        int j = min(q[i][0],q[i][1]), k =  max(q[i][0],q[i][1]);
        if (j == k || h[j] < h[k]) ans[i] = k;
        else {
            vec[k].emplace_back(h[j],i);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (auto& p : vec[i]){
            pq.emplace(p);
        }
        while (!pq.empty() && h[i] > pq.top().first) {
            ans[pq.top().second] = i;
            pq.pop();
        }
    }
    return ans;
}

// 异或哈希表 no.2935
int maximumStrongPairXor(vector<int>& a) {
    // 排序
    sort(a.begin(),a.end());
    int mx = a.back();
//    int high_bit = mx ? 31 - __builtin_clz(mx) : -1;
    int high_bit = -1;
    for (int i = 31; i >= 0; --i){
        if(mx >> i) {
            high_bit = i;
            break;
        }
    }

    int ans = 0, mask = 0, n = a.size();
    unordered_map<int,int> mp;
    for (int i = high_bit; i >= 0; i--) { // 从最高位开始枚举
        mp.clear();
        mask |= 1 << i;
        int new_ans = ans | (1 << i); // 这个比特位可以是 1 吗？
        for (int i = 0; i < n; ++i) {
            auto x = a[i];
            x &= mask; // 低于 i 的比特位置为 0
            if (mp.count(new_ans ^ x) && a[i]-a[mp[new_ans ^ x]]*2 <= 0) {
                ans = new_ans; // 这个比特位可以是 1
                break;
            }
            mp[x] = i;
        }
    }
    return ans;
}

// 异或哈希表 no.421
int findMaximumXOR(vector<int> &a) {
    int mx = *max_element(a.begin(), a.end());
//    int high_bit = mx ? 31 - __builtin_clz(mx) : -1;
    int high_bit = -1;
    for (int i = 31; i >= 0; --i){
        if(mx >> i) {
            high_bit = i;
            break;
        }
    }

    int ans = 0, mask = 0;
    unordered_set<int> seen;
    for (int i = high_bit; i >= 0; i--) { // 从最高位开始枚举
        seen.clear();
        mask |= 1 << i;
        int new_ans = ans | (1 << i); // 这个比特位可以是 1 吗？
        for (int x: a) {
            x &= mask; // 低于 i 的比特位置为 0
            if (seen.count(new_ans ^ x)) {
                ans = new_ans; // 这个比特位可以是 1
                break;
            }
            seen.emplace(x);
        }
    }
    return ans;
}

bool areSimilar(vector<vector<int>>& g, int k) {
    int m = g.size(), n = g[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i % 2) {
                if (g[i][(j+k)%n] != g[i][j]) return false;
            }
            else {
                if (g[i][((j-k)%n+n)%n] != g[i][j]) return false;
            }
        }
    }
    return true;
}

int beautifulSubstrings1(string s, int k) {
    auto check = [&](char c){
        if (c == 'a' || c == 'e' || c == 'i'||c == 'o'||c=='u') return true;
        else return false;
    };
    int ans = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = i; j < n; ++j) {
            if (check(s[j])) ++cnt;
            if (cnt == j+1-cnt-i && cnt *(j+1-cnt-i) % k == 0) ++ans;
        }
    }
    return ans;
}

vector<int> lexicographicallySmallestArray(vector<int>& a, int l) {
    int n = a.size();
    vector<int> ans(n);
    multiset<int> s1[n],s2[n];
    vector<int> ind(n);
    iota(ind.begin(),ind.end(),0);
    sort(ind.begin(),ind.end(),[&](int i, int j){return a[i] < a[j];});
    sort(a.begin(),a.end());
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || a[i]-a[i-1] <= l) {
            s1[j].emplace(a[i]);
            s2[j].emplace(ind[i]);
        } else {
            ++j;
            s1[j].emplace(a[i]);
            s2[j].emplace(ind[i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!s1[i].empty()){
            vector<int> vec1(s1[i].begin(),s1[i].end());
            vector<int> vec2(s2[i].begin(),s2[i].end());
            for (int k = 0; k < vec1.size(); ++k) {
                ans[vec2[k]] = vec1[k];
            }
        }
    }
    return ans;
}



/**
 * 子数组统计套路 : 前缀和 + 哈希表  no.2949
 *                数学： 余数化简，处理， 同余定理
 * @param s
 * @param k
 * @return
 */
long long beautifulSubstrings(string s, int k) {
    auto check = [&](char c){
        if (c == 'a' || c == 'e' || c == 'i'||c == 'o'||c=='u') return true;
        else return false;
    };
    int d = 1;
    for (;d <= 2*k; ++d) {
        if (d*d % (4 *k) == 0) {
            break;
        }
    }
    long ans = 0, n = s.size();
    vector<int> pre(n+1);
    for (int i = 0; i < n; ++i) {
        pre[i+1] += (pre[i] + (check(s[i]) ? 1 : -1));
    }
    map<pair<int,int>,long> mp;
//    mp[pair<int,int>(pre[0],0)] = 1;
    for (int i = 0; i <=n; ++i) {
        ans += mp[pair<int,int>(pre[i],i%d)];
        ++mp[pair<int,int>(pre[i],i%d)];
    }
    return ans;
}

//int minimumCoins1(vector<int>& a) {
//    int n = a.size();
//    int memo[n+1][n+1];
//    memset(memo,-1,sizeof(memo));
//    function<int(int,int)> dfs = [&](int i, int j){
//        if (i == n-1) {
//            if (j > 0) return 0;
//            else return a[i];
//        }
//        if (memo[i][j] != -1) return memo[i][j];
//        int &res = memo[i][j];
//        if (j > 0) {
//            res = min(dfs(i+1,j-1),dfs(i+1,i+1)+a[i]);
//        } else res = dfs(i+1,i+1)+a[i];
//        return res;
//    };
//    return dfs(0,0);
//}

int minimumCoins(vector<int>& a) {
    int n = a.size();
    vector<int> f(n+1);
    deque<int> q;
    for (int i = n; i >= 1;--i) {
        while (!q.empty() && q.back() > i*2+1){
            q.pop_back();
        }
        if (i*2 >= n) {
            f[i] = a[i-1];
        } else {
            f[i] = f[q.back()]+a[i-1];
        }
        while (!q.empty() && f[q.front()] >= f[i]) {
            q.pop_front();
        }
        q.emplace_front(i);
    }
    return f[1];
}

/**
 * 单调队列优化 DP : no.2945
 * @param a
 * @return
 */
int findMaximumLength(vector<int> &a) {
    int n = a.size();
    vector<long long> s(n + 1), last(n + 1);
    vector<int> f(n + 1), q(n + 1); // 数组模拟队列
    int front = 0, rear = 0; // 手写双端队列
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i - 1]; // 前缀和

        // 1. 去掉队首无用数据（计算转移时，直接取队首）
        while (front < rear && s[q[front + 1]] + last[q[front + 1]] <= s[i]) {
            front++;
        }

        // 2. 计算转移
        f[i] = f[q[front]] + 1;
        last[i] = s[i] - s[q[front]];

        // 3. 去掉队尾无用数据
        while (rear >= front && s[q[rear]] + last[q[rear]] >= s[i] + last[i]) {
            rear--;
        }
        q[++rear] = i;
    }
    return f[n];
}

vector<int> findPeaks(vector<int>& a) {
    int n = a.size();
    vector<int> ans;
    for (int i = 1; i < n-1; ++i) {
        if (a[i] > a[i-1] && a[i] > a[i+1]) ans.emplace_back(i);
    }
    return ans;
}

int minimumAddedCoins(vector<int>& a, int t) {
    int n = a.size(), ans = 0;
    sort(a.begin(),a.end());
    int tmp = 0;
    for (int i = 0; i < n;) {
        if (tmp >= t) return ans;
        if (a[i] > tmp+1) {
            ++ans;
            tmp += tmp+1;
        } else {
            tmp += a[i];
            ++i;
        }
    }
    for (int i = tmp+1; i <= t;) {
        if (tmp >= t) return ans;
        if (i > tmp) {
            ++ans;
            tmp += tmp+1;
            i = tmp+1;
        }
    }
    return ans;
}

int countCompleteSubstrings(string w, int k) {
    auto f = [&](string s, int k) {
        int res = 0;
        for (int m = 1; m <= 26 && k * m <= s.length(); m++) {
            unordered_map<char,int> mp;
            auto check = [&]() {
                for (auto p : mp) {
                    if (p.second != 0 && p.second != k) return;
                }
                res++;
            };
            for (int r = 0; r < s.length(); r++) {
                mp[s[r]]++;
                int l = r + 1 - k * m;
                if (l >= 0) {
                    check();
                    mp[s[l]]--;
                }
            }
        }
        return res;
    };

    int n = w.length();
    int ans = 0;
    // 分组循环
    for (int i = 0; i < n;) {
        int st = i;
        for (i++; i < n && abs(int(w[i]) - int(w[i - 1])) <= 2; i++);
        ans += f(w.substr(st, i - st), k);
    }
    return ans;
}

bool hasTrailingZeros(vector<int>& a) {
    int cnt = 0, n = a.size();
    for (auto a1 : a) {
        if (a1%2 == 0) ++cnt;
    }
    if (cnt >= 2) return true;
    return false;
}

int maximumLength1(string s) {
    map<pair<char,int>,int> mp;
    int n = s.size();
    auto check1 = [&](string s1) {
        for (int i = 1; i < s1.size(); ++i) {
            if (s1[i] != s1[i-1]) return false;
        }
        return true;
    };
    for (int i = 0; i < n; ++i) {
        string str{s[i]};
        mp[pair<char,int>(s[i],1)]++;
        for (int j = i+1; j < n; ++j) {
            str += s[j];
            if (check1(str)) {
                mp[pair<char,int>(s[j],str.size())]++;
            } else break;
        }
    }
    int ans = -1;
    for (char c = 'a'; c <= 'z'; ++c) {
        for (int i = 1; i < 50; ++i) {
            if (mp[pair<char,int>(c,i)] >= 3) {
                ans = max(ans, i);
            } else break;
        }
    }
    return ans;
}

int maximumLength(string s) {
    map<pair<char,int>,int> mp;
    map<char,int> mp1;
    int n = s.size();
    string str{s[0]};
    for (int i = 1; i < n; ++i) {
        if (s[i] != s[i-1]) {
            int l = str.size();
            for (int j = 1; j <= l; ++j) {
                if (mp[pair<char,int>(s[i-1],l+2-j)] < 3) {
                    mp[pair<char,int>(s[i-1],l+1-j)] += j;
                    if (mp[pair<char,int>(s[i-1],l+1-j)] >= 3)
                        mp1[s[i-1]] = max(mp1[s[i-1]], l+1-j);
                } else {
                    mp1[s[i-1]] = max(mp1[s[i-1]], l+2-j);
                    break;
                }
            }
            str = s[i];
        } else {
            str += s[i];
        }
    }
    int l = str.size();
    for (int j = 1; j <= l; ++j) {
        if (mp[pair<char,int>(s[n-1],l+2-j)] < 3) {
            mp[pair<char,int>(s[n-1],l+1-j)] += j;
            if (mp[pair<char,int>(s[n-1],l+1-j)] >= 3)
                mp1[s[n-1]] = max(mp1[s[n-1]], l+1-j);
        } else {
            mp1[s[n-1]] = max(mp1[s[n-1]], l+2-j);
            break;
        }
    }
    int ans = -1;
    for (char c = 'a'; c <= 'z'; ++c) {
        ans = max(ans,mp1[c]);
    }
    return ans == 0 ? -1 : ans;
}

int areaOfMaxDiagonal(vector<vector<int>>& d) {
    double mx1 = 0, mx2 = 0;
    for (auto& d1 : d) {
        double x = sqrt((double)d1[0]*(double)d1[0] + (double)d1[1]*(double)d1[1]);
        if (x > mx1) {
            mx1 = x;
            mx2 = (double)d1[0]*(double)d1[1];
        } else if (x == mx1){
            mx2 = max(mx2,(double)d1[0]*(double)d1[1]);
        }
    }
    return (int)mx2;

}

int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
    a= a-1,b=b-1,c=c-1,d=d-1,e=e-1,f=f-1;
    if (e == a) {
        if (!(c == a && ((b < d && d < f) || (b > d && d > f)))) return 1;
    }
    if (b == f) {
        if (!(d == b && ((a < c && c < e) || (a > c && c > e)))) return 1;
    }
    if (abs(e-c) == abs(d-f)) {
        if (! (abs(a-c) == abs(d-b) && (c-e)*(c-a) > 0 && (d-f)*(d-b) > 0 && (abs(c-a) < abs(c-e)))) return 1;
    }
    return 2;
}

int maximumSetSize(vector<int>& a, vector<int>& b) {
    int n = a.size();
    map<int,int> mp1,mp2;
    set<int> st1(a.begin(),a.end()), st2(b.begin(),b.end());
    for (auto &a1 : a) {
        mp1[a1]++;
    }
    for (auto &b1 : b) {
        mp2[b1]++;
    }
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    for (auto &a1 : st1) {
        cnt1 += (mp1[a1]-1 );
        if (mp1[a1] >0 && mp2[a1] >0) ++cnt3;
    }
    for (auto &b1 : st2) {
        cnt2 += (mp2[b1]-1 );
    }
    if (cnt1 >= n/2) {
        if (cnt2+cnt3 >= n/2) {
            return st1.size()+st2.size()-cnt3;
        } else {
            return st1.size()+st2.size()-cnt3-(n/2-cnt2-cnt3);
        }
    }
    if (cnt2 >= n/2) {
        if (cnt1+cnt3 >= n/2) {
            return st1.size()+st2.size()-cnt3;
        } else {
            return st1.size()+st2.size()-cnt3-(n/2-cnt1-cnt3);
        }
    }
    if (cnt1+cnt3+cnt2 >= n) {
        return st1.size()+st2.size()-cnt3;
    } else {
        return st1.size()+st2.size()-cnt3-(n-cnt1-cnt3-cnt2);
    }
    return st1.size()+st2.size()-cnt3;
}

int maxFrequencyElements(vector<int>& a) {
    int n = a.size(), ans = 0;
    map<int,int> mp;
    for(auto& a1 : a) {
        mp[a1]++;
    }
    multimap<int,int,greater<>> mp1;
    for(auto& p : mp) {
        mp1.emplace(p.second,p.first);
    }
    int mx = 0;
    for(auto& a1 : a) {
        mx = max(mx,mp[a1]);
    }
    for (auto& p : mp1) {
        if(p.first == mx) {
            ans += mx;
        }
    }
    return ans;
}

vector<int> beautifulIndices_1(string s, string a, string b, int k) {
    int n = s.size(), m1 = a.size(), m2 = b.size();
    vector<int> veci,vecj,ans;
    for (int i = 0; i < n; ++i) {
        if (i <= n-m1) {
            if (s.substr(i,m1) == a) {
                veci.emplace_back(i);
            }
        }
        if (i <= n-m2) {
            if (s.substr(i,m2) == b) {
                vecj.emplace_back(i);
            }
        }
    }
    int l1 = 0,l2 = 0, n1 = veci.size(), n2 = vecj.size();
    while (l1 < n1 && l2 < n2) {
        if (abs(veci[l1] - vecj[l2]) <= k) {
            ans.emplace_back(veci[l1]);
            ++l1;
        } else {
            if (vecj[l2] < veci[l1]) {
                ++l2;
            } else {
                ++l1;
            }
        }
    }
    return ans;
}

int minimumPushes_1(string w) {
    int n = w.size();
    if (n <= 8) return n;
    if (8 < n && n <= 16) {
        return 8 + (n-8)*2;
    }
    if (16 < n && n <= 24) {
        return 24+(n-16)*3;
    }
    if (n > 24) {
        return 48 + (n-24)*4;
    }
    return n;
}

int minimumPushes(string w) {
    int n = w.size(), ans = 0;
    map<char, int> mp;
    for(auto c : w) {
        mp[c]++;
    }
    int m = mp.size();
    vector<int> vec;
    for (auto& p : mp) {
        auto[a,b] = p;
        vec.emplace_back(b);
    }
    sort(vec.begin(),vec.end(),[&](int i, int j){return i > j;});
    for (int i = 0 ; i < m; ++i) {
        if (i <= 7) ans += vec[i];
        if (7 < i && i <= 15) {
            ans += vec[i] * 2;
        }
        if (15 < i && i <= 23) {
            ans += vec[i] * 3;
        }
        if (i > 23) {
            ans += vec[i] * 4;
        }

    }
    return ans;
}

vector<int> countOfPairs_1(int n, int x, int y) {
    vector<int> ans(n);
    map<int,int> mp;
    if (abs(x-y) <= 1) {
        for (int i = 0; i < n; ++i) {
            ans[i] = (n-i-1)*2;
        }
        return ans;
    } else {
        int x1 = min(x,y), y1 = max(x,y);
        x1 -= 1, y1 -= 1;
        ans[0] = n*2;
        for (int i = 0; i < n-1; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (y1 <= i || x1 >= j) {
                    mp[j-i]++;
                } else {
                    int dis = min(j-i,abs(i-x1)+abs(j-y1)+1);
                    mp[dis]++;
                }
            }
        }
        for (auto p : mp) {
            auto [a,b] = p;
            ans[a-1] = b*2;
        }
        return ans;
    }
    return ans;
}

int countKeyChanges(string s) {
    int ans = 0, n = s.size();
    for (int i = 1; i < n; ++i) {
        if (!(abs(s[i]-s[i-1]) == 32 || abs(s[i]-s[i-1]) == 0)) {
            ++ans;
        }
    }
    return ans;
}

int maximumLength(vector<int>& a) {
    int n = a.size(), ans = 1;
    vector<int> b;
    unordered_map<int,int> mp;
    for (auto a1 : a) {
        mp[a1]++;
        if (mp[a1] == 2) {
            b.emplace_back(a1);
        }
    }
    sort(b.begin(),b.end());
    unordered_map<int,int> mp1;
    set<long long> st1(a.begin(),a.end());
    set<long long> st2(b.begin(),b.end());
    for (int i = 0; i < b.size(); ++i) {
        if (!mp1[b[i]]) {
            int cnt = 1;
            mp1[b[i]] = 1;
            long long tmp = (long long)b[i]*b[i];
            while(st2.count(tmp) && !mp1[tmp]) {
                ++cnt;
                mp1[tmp] = 1;
                tmp *= tmp;
            }
            cnt *= 2;
            if (st1.count(tmp) && !mp1[tmp]) {
                ++cnt;
            } else {
                --cnt;
            }
            ans = max(ans,cnt);
        }
    }
    int cnt1 = count(a.begin(),a.end(),1);
    if (cnt1 % 2 == 0) cnt1--;
    ans = max(cnt1,ans);
    return ans;
}

long long flowerGame(int n, int m) {
    long long ans = 0;
    long long n1 = n/2 + (n%2);
    long long n2 = n/2 ;
    long long m1 = m/2 + (m%2);
    long long m2 = m/2 ;
    ans = n1 * m2 + n2 * m1;
    return ans;
}

/**
 * 排序 + 枚举 (技巧)
 * https://leetcode.cn/problems/find-the-number-of-ways-to-place-people-ii/description/
 * @param p
 * @return
 */
int numberOfPairs(vector<vector<int>>& p) {
    int n = p.size();
    int ans = 0;
    sort(p.begin(), p.end(),[&](auto p1, auto p2){return p1[0] < p2[0] || (p1[0] == p2[0] && p1[1] > p2[1]);});

    for (int i = 0; i < n-1; ++i) {
        int mx = -(1e9+1);
        int a1 = p[i][0], a2 = p[i][1];
        for (int j = i+1; j < n; ++j) {
            int b1 = p[j][0], b2 = p[j][1];
            if (b2 <= a2 && b2 > mx) {
                ++ans;
                mx = b2;
            }
        }
    }
    return ans;
}

int main() {

    return 0;
}

/**
 * luogu
 */
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    int n;
//    cin >> n;
//    vector<int> r(n+1);
//    vector<int> a(n+1); // 找根
//    vector<vector<int>> g(n+1);
//    for (int i = 0; i < n; ++i) {
//        int b;
//        cin >> b >> r[b];
//        int m;
//        cin >> m;
//        for (int j = 0; j < m; ++j) {
//            int k;
//            cin >> k;
//            g[b].emplace_back(k);
//            a[k] = 1;// 找根
//        }
//
//    }
//
//    int root = 0;
//    for (int i = 1; i <= n; ++i) {
//        if (!a[i]) root = i; // 找根
//    }
//
//    int memo[n+1][3];
//    memset(memo,-1,sizeof(memo));
//    // 需特殊处理叶子节点
//    function<int(int,int)> dfs = [&](int i, int j){
//        if (g[i].size() == 0 && j == 2) return (int)2e7; // 处理叶子为 red
//        if(memo[i][j] != -1) return memo[i][j];
//        int& res = memo[i][j];
//        res = 0;
//        int tmp = (int)2e7;
//        if (j == 0) {
//            res += r[i];
//        }
//        for (auto k : g[i]) {
//            int k0 = dfs(k,0), k1 = dfs(k,1), k2 = dfs(k,2);
//            if (j == 0) {
//                res += min(k0,k1);
//            } else if (j == 1){
//                if (g[k].size() == 0) {
//                    res += k0;
//                } else {
//                    res += min(k0,k2);
//                }
//            } else {
//                if (g[k].size() == 0) {
//                    res += k0;
//                    tmp = 0;
//                } else {
//                    res += min(k0,k2);
//                }
//                tmp = min(tmp,k0-k2);
//            }
//        }
//        if (j == 2) {
//            res += max(0, tmp);
//        }
//        return res;
//    };
//    int ans = min(dfs(root,0),dfs(root,2));
//    cout<<ans;
//    return 0;
//}

/**
 * codeforces
 */
//#include <bits/stdc++.h>
//
//using namespace std;
//
//void solve() {
//    int n,k;
//    cin >> n >> k;
//    vector<int> a(n);
//    for (int i = 0; i < n; ++i) {
//        cin >> a[i];
//    }
//    int ans = 5;
//    if (k == 3) {
//        for (auto& b : a) {
//            ans = min(ans, 3- (b%3 == 0 ? 3 : b%3));
//        }
//
//    } else if (k == 5) {
//        for (auto& b : a) {
//            ans = min(ans, 5- (b%5 == 0 ? 5 : b%5));
//        }
//
//    } else if(k == 2){
//        for (auto& b : a) {
//            ans = min(ans, 2- (b%2 == 0 ? 2 : b%2));
//        }
//    }else {
//        int cnt = 0;
//        for (auto& b : a) {
//            cnt += (b % 2 == 0 ? 1 : 0);
//        }
//        for (auto& b : a) {
//            ans = min(ans, 4- (b%4 == 0 ? 4 : b%4));
//        }
//        if (n >= 2) {
//            ans = min(ans, 2-cnt >= 0 ? 2-cnt : 0);
//        }
//
//    }
//    cout << ans << endl;
//
//}
//
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    int t;
//    cin >> t;
//    while (t--) {
//        solve();
//    }
//}

/**
 * impl list :
 * 7.5 dijkstra/floyd (两种)
 * 7.6 贡献法
 * 7.8 巫师的力量总和
 * 8. 莫队算法
 * 1. 370 周赛第 3，4 题
 * 4. 2200 难度题
 * 5. 灵神 总结/归纳 的周赛题单（附难度分和知识点）-> 对应练习
 * 6. no.887 鸡蛋掉落
 * 9. 按灵神 github 模板， 整理算法结构
 * 10. 往届周赛 t4
 */

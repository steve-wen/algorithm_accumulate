#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define rep(i, from, to) for(ll i = from;i<to;i++)
#define rrep(i, from, to) for(ll i = from;i>=to;i--)
#define se second
#define fi first
#define tostring(a) (ostringstream() << a).str()
//#define endl "/n"

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
 * 树形 dp, 记忆化搜索（也可用 chatgpt 转成 python 加 @cache）
 * fa 不用记忆
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

//int main() {
//    return 0;
//}


/**
 * luogu/nowcoder/codeforces
 */
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    unordered_map<string,int> mp1,mp2;
    vector<int> b(n);
    vector<string> str(n);
    for (int i =0; i < n ; ++i) {
        int a = 0;
        string s;
        cin >> s >> a;
        b[i] = a;
        str[i] = s;
        mp1[s] += a;
    }
    int mx = 0;
    for (auto p : mp1) {
        mx = max(mx,p.second);
    }
    unordered_set<string> st;
    for (auto p : mp1) {
        if(mx == p.second){
            st.emplace(p.first);
        }
    }
    if (st.size() == 1) {
        cout << *st.begin();
        return 0;
    }

    for (int i =0; i <n; ++i) {
        mp2[str[i]] += b[i];
        if (mp2[str[i]] >= mx) {
            cout << str[i];
            return 0;
        }
    }
    return 0;
}

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
 * CF 的经典题, 注意练习
 * 1. 1.2 练习对应分数的题目，包括速度 (注意速度) (注意对应分数)
 * 1.3 贡献法 巫师的力量总和 (熟悉此种思想和用法)
 * 2. 注意 cf 题单，套路等
 * 3. 练习 CF 题单等; 多类型比赛并行打
 * 4. 2200 难度题
 * 5. 灵神 总结/归纳 的周赛题单（附难度分和知识点）-> 对应练习
 * 6. no.887 鸡蛋掉落
 * 9. 按灵神 github 模板， 整理算法结构
 * 10. 往届周赛 t4
 */

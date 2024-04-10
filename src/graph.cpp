#include <bits/stdc++.h>

using namespace std;

/**
*  图论
*/

/**
 * Floyd
 * dfs, 时间复杂度 : O(n^3)
 * https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/
 */

int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
    vector<vector<int>> w(n, vector<int>(n, 1e6)); // 防止加法溢出
    for (auto &e: edges) {
        int x = e[0], y = e[1], wt = e[2];
        w[x][y] = w[y][x] = wt;
    }

    int memo[101][101][101];
    memset(memo, -1, sizeof(memo)); // 除了 0, -1 的其他特殊值用 vector 初始化
    function<int(int, int, int)> dfs = [&](int k, int i, int j) -> int {
        if (k < 0) { // 递归边界
            return w[i][j];
        }
        auto &res = memo[k][i][j]; // 注意这里是引用
        if (res != -1) { // 之前计算过
            return res;
        }
        return res = min(dfs(k - 1, i, j), dfs(k - 1, i, k) + dfs(k - 1, k, j));
    };

    int ans = 0;
    int min_cnt = n;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (j != i && dfs(n - 1, i, j) <= distanceThreshold) {
                cnt++;
            }
        }
        if (cnt <= min_cnt) { // 相等时取最大的 i
            min_cnt = cnt;
            ans = i;
        }
    }
    return ans;
}

/**
 * 枚举子集 + floyd
 * 时间复杂度 O(2^n * m^3)
 * https://leetcode.cn/problems/number-of-possible-sets-of-closing-branches/description/
 * @param n
 * @param d
 * @param r
 * @return
 */
int numberOfSets(int n, int d, vector<vector<int>>& r) {
    int m = r.size();
    for (auto& r1 : r) {
        if (r1[0] > r1[1]) {
            swap(r1[0],r1[1]);
        }
    }
    sort(r.begin(),r.end());
    map<pair<int,int>,int> g;
    if (m > 0) {
        g[pair<int,int>(r[0][0],r[0][1])] = r[0][2];
    }
    for (int i = 1; i < m; ++i) {
        if (r[i][0] == r[i-1][0] && r[i][1] == r[i-1][1]) {
            continue;
        } else {
            g[pair<int,int>(r[i][0],r[i][1])] = r[i][2];
        }
    }
    vector<int> path;
    vector<vector<int>> ans;
    function<void(int)> dfs = [&](int i) {
        if (i == n) {
            ans.emplace_back(path);
            return;
        }
        dfs(i + 1);
        path.emplace_back(i);
        dfs(i + 1);
        path.pop_back();
    };
    dfs(0);
    int res = ans.size();
    auto check = [&](int& res, vector<int>& ind) {
        vector<vector<int>> w(n, vector<int>(n, 1e5+1)); // 防止加法溢出
        int l = ind.size();
        sort(ind.begin(),ind.end());
        for (int i = 0; i < l-1; ++i) {
            for (int j = i+1; j <l; ++j){
                if (g.count(pair<int,int>(ind[i],ind[j]))) {
                    w[ind[i]][ind[j]] = g[pair<int,int>(ind[i],ind[j])];
                    w[ind[j]][ind[i]] = g[pair<int,int>(ind[i],ind[j])];
                }
            }
        }

        int memo[11][11][11];
        memset(memo, -1, sizeof(memo)); // 除了 0, -1 的其他特殊值用 vector 初始化
        function<int(int, int, int)> dfs = [&](int k, int i, int j) -> int {
            if (k < 0) { // 递归边界
                return w[ind[i]][ind[j]];
            }
            auto &res = memo[k][i][j]; // 注意这里是引用
            if (res != -1) { // 之前计算过
                return res;
            }
            return res = min(dfs(k - 1, i, j), dfs(k - 1, i, k) + dfs(k - 1, k, j));
        };

        for (int i = 0; i < l; i++) {
            for (int j = 0; j < l; j++) {
                if (j != i && dfs(l - 1, i, j) > d) {
                    --res;
                    return;
                }
            }
        }
    };
    for (auto& ind : ans){
        check(res,ind);
    }
    return res;
}

/**
 * Floyd, O(n^3)
 * https://leetcode.cn/problems/minimum-cost-to-convert-string-i/description/
 * @param s
 * @param t
 * @param o
 * @param ch
 * @param co
 * @return
 */
long long minimumCost(string s, string t, vector<char>& o, vector<char>& ch, vector<int>& co) {
    int n = s.size();
    long long ans = 0;
    vector<vector<long long>> w(27, vector<long long>(27, 1e8)); // 防止加法溢出
    for (int i = 0; i < o.size(); ++i) {
        int x = o[i]-'a', y = ch[i]-'a', wt = co[i];
        w[x][y] = min((long long)wt, w[x][y]);
    }

    long long memo[27][27][27];
    memset(memo, -1, sizeof(memo)); // 除了 0, -1 的其他特殊值用 vector 初始化
    function<long long(int, int, int)> dfs = [&](int k, int i, int j) -> int {
        if (k < 0) { // 递归边界
            return w[i][j];
        }
        auto &res = memo[k][i][j]; // 注意这里是引用
        if (res != -1) { // 之前计算过
            return res;
        }
        return res = min(dfs(k - 1, i, j), dfs(k - 1, i, k) + dfs(k - 1, k, j));
    };

    for (int i = 0; i < n; i++) {
        if (s[i] == t[i]) continue;
        auto cnt = dfs(26,s[i]-'a',t[i]-'a');
        if (cnt >= 1e8) return -1;
        ans += cnt;
    }
    return ans;
}

/**
 * dijkstra : 解决没有负边权的单源最短路， 时间复杂度（ElogN)
 * @param g
 * @return
 */
int minimumTime(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    // 特判
    if (g[0][1] > 1 && g[1][0] > 1) return -1;

    // 准备方向数组 vec
    vector<vector<int>> vec{{-1,0},{1,0},{0,-1},{0,1}};

    // 初始化 dis 数组
    vector<vector<int>> dis(m,vector<int>(n, 1e6));
    dis[0][0] = 0;

    // 小顶堆， 起点（0，0，0） 入堆
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<>> q;
    q.emplace(0,0,0);

    while(true) {
        auto[d,i,j] = q.top();
        q.pop();
        if (i == m-1 && j == n-1) {
            return d;
        }
        // 此时的 d 不是最小值， 说明之前已更新过， continue
        if (d > dis[i][j]) continue;
        // 遍历上下左右
        for (auto& vec1 : vec) {
            int i1 = i + vec1[0], j1 = j + vec1[1];
            if (i1 >= 0 && i1 < m && j1 >= 0 && j1 < n) {
                // 根据题目处理
                int nd = max(d+1, g[i1][j1]);
                nd += (abs(nd - i1 - j1) % 2);
                // 更新点
                if (nd < dis[i1][j1]) {
                    dis[i1][j1] = nd;
                    q.emplace(nd,i1,j1);
                }
            }
        }
    }
}

/**
 * dijkstra : 解决没有负边权的单源最短路， 时间复杂度（ElogN)
 * 本质上是 dijkstra, 到一个点的转向次数最少(记为 d)，单源最短路
 * https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/
 * @param g
 * @return
 */
int minCost(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();

    // 准备方向数组 vec
    vector<vector<int>> vec{{0,0},{0,1},{0,-1},{1,0},{-1,0}};

    // 初始化 dis 数组
    vector<vector<int>> dis(m,vector<int>(n, 1e6));
    dis[0][0] = 0;

    // 小顶堆， 起点（0，0，0） 入堆
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<>> q;
    q.emplace(0,0,0);

    while(true) {
        auto[d,i,j] = q.top();
        q.pop();
        if (i == m-1 && j == n-1) {
            return d;
        }
        // 此时的 d 不是最小值， 说明之前已更新过， continue; 类似 vis 的作用
        if (d > dis[i][j]) continue;
        // 遍历上下左右
        for (int k = 1; k <= 4; ++k) {
            auto vec1 = vec[k];
            int i1 = i + vec1[0], j1 = j + vec1[1];
            if (i1 >= 0 && i1 < m && j1 >= 0 && j1 < n) {
                // 根据题目处理
                int nd = d + (g[i][j] != k);
                // 更新点
                if (nd < dis[i1][j1]) {
                    dis[i1][j1] = nd;
                    q.emplace(nd,i1,j1);
                }
            }
        }
    }
}

/**
 * dijkstra : dijkstra 结合最多经过 k + 1 条边； 非负边权单源最短路 + 限定经过边数；
 *            用 dis 和 cnt 数组剪枝
 * @param n
 * @param f
 * @param s
 * @param des
 * @param k
 * @return
 */
int findCheapestPrice(int n, vector<vector<int>>& f, int s, int des, int k) {
    int ans  = 1e7;
    // 建图
    unordered_map<int,vector<pair<int,int>>> mp;
    for (auto& f1 : f) {
        mp[f1[0]].emplace_back(f1[1],f1[2]);
    }

    // 初始化 dis 数组, cnt 记录 cnt[i], 即 到达 i 时已经过边数； 便于后续剪枝
    vector<int> dis(n, 1e7);
    vector<int> cnt(n, k+2);
    dis[s] = 0;
    cnt[s] = 0;
    // 小顶堆， 起点（0，0，0） 入堆
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<>> q;
    q.emplace(0,s,0);

    while(!q.empty()) {
        auto[d,i,j] = q.top();
        q.pop();
        if (i == des && j <= k+1) {
            return d;
        }

        // 遍历邻居
        for (auto& p : mp[i]) {
            int i1 = p.first, j1 = j + 1;
            // 根据题目处理
            int nd = d + p.second;
            // 更新点
            if (j1 <= k+1 ) {
                // 剪枝
                if (j1 < cnt[i1] || nd < dis[i1]) {
                    q.emplace(nd,i1,j1);
                    dis[i1] = nd;
                    cnt[i1] = j1;
                }
            }
        }
    }
    return -1;
}

struct TreeNode {
         int val;
         TreeNode *left;
         TreeNode *right;
         TreeNode() : val(0), left(nullptr), right(nullptr) {}
         TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
         TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
     };

/**
 * dfs 记录 父节点 +  bfs 记录来源节点和方向
 * 注意理解灵神题解
 * @param r0
 * @param st
 * @param des
 * @return
 */
string getDirections(TreeNode* r0, int st, int des) {
    vector<vector<pair<int,char>>> g(1e5+1);
    string s;
    function<void(TreeNode*)> dfs = [&](TreeNode* r){
        if (r == nullptr) return;
        if (r->left) {
            g[r->val].emplace_back(r->left->val,'L');
            g[r->left->val].emplace_back(r->val,'U');
            dfs(r->left);
        }
        if (r->right) {
            g[r->val].emplace_back(r->right->val,'R');
            g[r->right->val].emplace_back(r->val,'U');
            dfs(r->right);
        }
    };
    dfs(r0);

    // dis 数组记录距离 且 < 1 时未访问过，有 mark/vis 的作用
    vector<int> dis(1e5+1,-1);
    // 初始化
    dis[st] = 0;

    unordered_map<int,pair<int,char>> mp;
    queue<pair<int,char>> q;
    q.emplace(st,'a');
    bool flag = false;
    while (!q.empty()) {
        if (flag) break;
        for (int i = q.size(); i > 0; --i) {
            auto q1 = q.front();
            q.pop();

            // b 为父节点
            auto&[a,b] = q1;

            if (a == des) {
                flag = true;
                break;
            }
            for (auto& [j,k] : g[a]) {
                if (dis[j] < 0) { // j 未访问过
                    dis[j] = dis[a]+1;
                    q.emplace(j,k);
                    mp[j] = pair<int,char>(a,k);
                }
            }
        }
    }
    int a = des;
    while (a != st) {
        s += mp[a].second;
        a = mp[a].first;
    }
    reverse(s.begin(),s.end());
    return s;
}

/**
 * dijktra: 套 dijkstra 模板
 */
class Graph {
public:
    // 建图
    unordered_map<int,vector<pair<int,int>>> mp;
    int n = 0;

    Graph(int n1, vector<vector<int>>& e) {
        n = n1;
        for (auto& e1 : e) {
            mp[e1[0]].emplace_back(e1[1],e1[2]);
        }
    }

    void addEdge(vector<int> e) {
        mp[e[0]].emplace_back(e[1],e[2]);
    }

    int shortestPath(int s, int end) {
        vector<int> dis(n, 1e9);
        dis[s] = 0;
        // 小顶堆， 起点（0，0，0） 入堆
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
        q.emplace(0,s);
        while(!q.empty()) {
            auto[d,i] = q.top();
            q.pop();
            if (i == end) {
                return d;
            }

            // 遍历邻居
            for (auto& p : mp[i]) {
                int i1 = p.first;
                // 根据题目处理
                int nd = d + p.second;
                // 更新点, 剪枝
                if (nd < dis[i1]) {
                    q.emplace(nd,i1);
                    dis[i1] = nd;
                }
            }
        }
        return -1;
    }
};

/**
 * dijkstra: dijkstra 运用
 * @param s
 * @param t
 * @param r
 * @return
 */
int minimumCost(vector<int>& s, vector<int>& t, vector<vector<int>>& r) {

    // 初始化 dis 数组便于后续剪枝
    map<pair<int,int>,int> dis;
    dis[pair<int,int>(t[0],t[1])] = 2e5;
    for (auto& r1 : r) {
        dis[pair<int,int>(r1[2],r1[3])] = 2e5;
    }

    // 小顶堆， 起点（0，0，0） 入堆
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<>> q;
    q.emplace(0,s[0],s[1]);
    while(true) {
        auto[d,i,j] = q.top();
        q.pop();
        // 边界返回
        if (i == t[0] && j == t[1]) {
            return d;
        }
        // 根据题目更新
        if (d+t[0]-i+t[1]-j < dis[pair<int,int>(t[0],t[1])]) {
            q.emplace(d+t[0]-i+t[1]-j,t[0],t[1]);
        }

        // 遍历邻居
        for (auto& r1 : r) {
            // 更新点, 剪枝
            int nd = d+abs(r1[0]-i)+abs(r1[1]-j)+r1[4];
            if (nd < dis[pair<int,int>(r1[2],r1[3])]) {
                dis[pair<int,int>(r1[2],r1[3])] = nd;
                q.emplace(nd,r1[2],r1[3]);
            }
        }
    }
}

/**
 * dijkstra(+ 多源 ) : dijkstra + for 循环
 * @param n
 * @param e
 * @param d
 * @return
 */
// 带边权，注意
int findTheCity_1(int n, vector<vector<int>>& e, int d) {
    // 建图
    unordered_map<int, vector<pair<int,int>>> g;
    for (auto & e1 : e) {
        g[e1[1]].emplace_back(e1[0],e1[2]);
        g[e1[0]].emplace_back(e1[1],e1[2]);
    }
    // 待更新结果
    int mi = 100, ans = 0;

    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        // 初始化 dis 数组
        vector<int> dis(n, 1e6);
        dis[i] = 0;
        // 小顶堆， 起点（0，0，0） 入堆
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
        q.emplace(0,i);

        while(!q.empty()) {
            auto[d,i] = q.top();
            q.pop();

            // 遍历邻居
            for (auto &p: g[i]) {
                int i1 = p.first;
                // 根据题目处理
                int nd = d + p.second;
                // 更新点
                // 剪枝
                if (nd < dis[i1]) {
                    q.emplace(nd, i1);
                    dis[i1] = nd;
                }
            }
        }
        for (auto & a : dis){
            if (a != 0 && a <= d){
                ++cnt;
            }
        }
        if (cnt <= mi) {
            mi = cnt;
            ans = i;
        }
    }
    return ans;
}

/**
 * 网格图: 循环遍历 + 记忆化搜索(dfs)
 * 时间复杂度 O(m*n)
 * https://leetcode.cn/problems/number-of-increasing-paths-in-a-grid/description/
 * @param g
 * @return
 */
int countPaths(vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size(), mod = (int)1e9 +7;
    // 遍历方向准备
    vector<vector<int>> vec{{-1,0},{1,0},{0,-1},{0,1}};
    int cnt = m*n;

    vector<vector<int>> mark(m, vector<int>(n));

    int memo[101][101];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j){
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = 0;
        for (auto &vec1: vec) {
            auto i1 = i + vec1[0], j1 = j + vec1[1];
            if (i1 >= 0 && i1 < m && j1 >= 0 && j1 < n && !mark[i1][j1] && g[i1][j1] > g[i][j]) {
                mark[i1][j1] = 1;
                res = (res +(dfs(i1,j1)+1)) % mod;
                mark[i1][j1] = 0;
            }
        }
        return res;
    };
    for (int i = 0; i < m;++i) {
        for (int j = 0; j < n; ++j) {
            mark[i][j] = 1;
            cnt = (cnt + dfs(i,j))%mod;
            mark[i][j] = 0;
        }
    }
    return cnt;
}

/**
 * 多源 bfs, 模板
 * 每一层 q, 距离+1(d)
 * 时间复杂度 O(m*n)
 * https://leetcode.cn/problems/map-of-highest-peak/description/
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
 * 最短环 ： bfs + 记录父节点（pre)
 * 时间复杂度 (On^3)
 * 注意用 vector 代替 unordered_map 建图, 可缩短时间
 * https://leetcode.cn/problems/shortest-cycle-in-a-graph/description/
 * @param n
 * @param e
 * @return
 */
int findShortestCycle(int n, vector<vector<int>>& e) {
    int ans = 1e4;

    vector<vector<int>> g(n+1);
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
                        ans = min(ans,tmp);
//                        break; // break 可剪枝
                    }
                }
            }
        }
    }
    return ans == 1e4 ? -1 : ans;
}

/**
 * 找环，同时统计出入度数
 * bfs
 * https://leetcode.cn/problems/minimum-degree-of-a-connected-trio-in-a-graph/description/
 * 时间复杂度 (On^3)
 * 注意用 vector 代替 unordered_map 建图, 可缩短时间
 * @param n
 * @param e
 * @return
 */
int minTrioDegree(int n, vector<vector<int>>& e) {
    int ans = 1e4;
    vector<vector<int>> g(n+1);
    for (auto & e1 : e) {
        g[e1[1]].emplace_back(e1[0]);
        g[e1[0]].emplace_back(e1[1]);
    }

    for (int i = 1; i <= n; ++i) {
        int tmp = 1e4, cnt = 0;
        // dis 数组记录距离 且 < 1 时未访问过，有 mark/vis 的作用
        vector<int> dis(n+1,-1);
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
                        cnt = g[a].size()-2+g[b].size()-2+g[j].size()-2;
                        if (tmp == 3) {
                            ans = min(ans,cnt);
                        }
                    }
                }
            }
        }
    }
    return ans == 1e4 ? -1 : ans;
}

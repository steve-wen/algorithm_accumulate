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


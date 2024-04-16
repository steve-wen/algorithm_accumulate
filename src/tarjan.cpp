#include <bits/stdc++.h>

using namespace std;

/**
 *  tarjan 算法
 *  强连通分量
 *
*/

/**
 * tarjan 算法：解决强连通分量问题（环？）
 * 时间复杂度 O(n)
 * 难度较高，偏竞赛
 * https://leetcode.cn/problems/critical-connections-in-a-network/description/
 * @param n
 * @param c
 * @return
 */
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& c) {
    vector<int> dfn(n);
    vector<int> low(n);
    vector<bool> visit(n);
    vector<vector<int>> ret;
    int times = 0;
    vector<vector<int>> g(n);
    for (auto& c1 : c){
        g[c1[0]].emplace_back(c1[1]);
        g[c1[1]].emplace_back(c1[0]);
    }
    function<void(int,int)> tarjan = [&](int i, int fa){
        times++;
        dfn[i] = times;
        low[i] = times;
        visit[i] = true;
        for (auto e : g[i]){
            if (e == fa) continue;
            if (!visit[e]){
                tarjan(e, i);
                low[i] = min(low[e], low[i]);
                if(low[e] > dfn[i]){
                    ret.push_back({i, e});
                }
            }else{
                low[i] = min(low[i], dfn[e]);
            }
        }
    };
    tarjan(0,-1);
    return ret;
}

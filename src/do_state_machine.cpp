#include <bits/stdc++.h>

using namespace std;

/**
*  状态机 dp
*
*/

/**
 * 状态机 dp
 * dfs(i,j,l) 表示第 i 天结束时 是(l==1)否(l == 0) 持有; 且剩余交易次数为 j
 * https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/description/
 * @param k
 * @param p
 * @return
 */
int maxProfit(int k, vector<int>& p) {
    int n = p.size();
    int memo[11][11][2];
    memset(memo,-1,sizeof(memo));
    function<int(int,int,int)> dfs = [&](int i, int j, int l) {
        if (i < 0) {
            if (j >= 0 && l == 0) return 0;
            else return (int)-1e8;
        }
        if(memo[i][j][l] != -1) return memo[i][j][l];
        int& res = memo[i][j][l];
        res = 0;
        if (l == 1 && j >=0) {
            res = max(dfs(i-1,j,1), dfs(i-1,j,0)-p[i]);
        } else if (l == 0 && j > 0) {
            res = max(dfs(i-1,j,0), dfs(i-1,j-1,1)+p[i]);
        }
        return res;
    };
    return dfs(n-1,k,0);
}

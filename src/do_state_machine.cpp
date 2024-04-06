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

/**
 *  状态机 dp
 *  dfs(i,j,k) 状态定义：本次在下标 i 处, 剩余 j 次，最大值 是 k 时的最小难度总和
 *  注意遍历的过程中，维护最大值
 *  时间复杂度(O(n^2*d))
 *  https://leetcode.cn/problems/minimum-difficulty-of-a-job-schedule/description/
 * @param a
 * @param d
 * @return
 */
int minDifficulty(vector<int>& a, int d) {
    int n = a.size();
    int memo[301][11][1001];
    memset(memo,-1,sizeof(memo));
    function<int(int,int,int)> dfs = [&](int i, int j, int k) {
        if (i <= 0) {
            if (j == 0) {
                return k;
            } else {
                return (int)1e6;
            }
        }
        if (j == 0) {
            if (i == 0) {
                return k;
            } else {
                return (int)1e6;
            }
        }
        if (memo[i][j][k] != -1) return memo[i][j][k];
        int& res = memo[i][j][k];
        res = (int)1e6;
        int mx = 0;
        for (int l = i-1; l >= max(0,j-1); --l) {
            mx = max(mx,a[l]);
            res = min(res, dfs(l,j-1,mx)+k);
        }
        return res;
    };
    return dfs(n,d,0) >= 1e6 ? -1 : dfs(n,d,0);
}
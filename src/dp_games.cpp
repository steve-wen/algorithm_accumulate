#include <bits/stdc++.h>

using namespace std;

/**
*  博弈 dp
 * 考虑当前/本次 先手获胜，最优的情况，无需考虑是哪个选手
 * 用 sum - dfs(i,j)
*/

/**
 * 博弈 dp
 * dfs(i,j) ： 先手情况时，可以从 i 选到 min(i+j*2-1,n-1) 堆石头，能获得的最大值
 * https://leetcode.cn/problems/stone-game-ii/description/
 * @param a
 * @return
 */
int stoneGameII(vector<int>& a) {
    int n = a.size();
    int sum = accumulate(a.begin(),a.end(),0);
    vector<int> s(n+1);
    for (int i = 0; i <n; ++i){
        s[i+1] = s[i] + a[i];
    }
    int memo[101][101];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j){
        if (i >= n) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        for (int k = i; k <= min(i+j*2-1,n-1); ++k) {
            res = max(res,sum-s[i]-dfs(k+1,max(j,k-i+1)));
        }
        return res;
    };
    return dfs(0,1);
}


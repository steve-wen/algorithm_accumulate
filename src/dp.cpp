#include <bits/stdc++.h>

using namespace std;

/**
* dp 动态规划
*/

/**
 * 数位 dp, 记忆化搜索
 * 数位 dp 模板
 * lc.no.2376
 * 说明 dfs 每个参数的作用，及整体逻辑
 * 逻辑 ： 按 n 的长度，横向遍历，获取有效个数
 * 参数 ： i : 目前在的数位位置（从 0 开始计算）
 *        j : mask, 用位运算来记录是否含重复数字
 *        k : is_lim, 之前的数位是否是上限
 *        l : is_num, 之前的数位是否全是 0
 * 注：第二个参数 j 灵活可变
 * 时间复杂度：
 * @param n
 * @return
 */
int countSpecialNumbers(int n) {
    string s(to_string(n));
    int memo[10][1024][2][2];
    memset(memo,-1,sizeof(memo));
    function<int(int,int,int,int)> dfs = [&](int i, int j, int k, int l){
        if (i == s.size()) {
            return l;
        }
        if (memo[i][j][k][l] != -1) return memo[i][j][k][l];
        int& res = memo[i][j][k][l];
        res = 0;
        if (!l) {
            res += dfs(i+1,j,0,0);
        }
        int up = k ? s[i]-'0' : 9;
        for (int m = 1-l; m <= up; ++m) {
            if ((j >> m & 1) == 0) {
                res += dfs(i+1,j | 1 << m,k && m == up,1);
            }
        }
        return res;
    };
    return dfs(0,0,1,0);
}

// lc.no.902
int atMostNGivenDigitSet(vector<string>& d, int n) {
    string s(to_string(n));
    unordered_set<int> st;
    for (auto d1 : d) {
        st.emplace(d1[0]-'0');
    }
    int memo[10][2][2];
    memset(memo,-1,sizeof(memo));
    function<int(int,int,int)> dfs = [&](int i, int k, int l){
        if (i == s.size()) {
            return l;
        }
        if (memo[i][k][l] != -1) return memo[i][k][l];
        int& res = memo[i][k][l];
        res = 0;
        if (!l) {
            res += dfs(i+1,0,0);
        }
        int up = k ? s[i]-'0' : 9;
        for (int m = 1-l; m <= up; ++m) {
            if (st.count(m)) {
                res += dfs(i+1,k && m == up,1);
            }
        }
        return res;
    };
    return dfs(0,1,0);
}

// lc.no.233
int countDigitOne(int n) {
    string s(to_string(n));
    int memo[10][10][2][2];
    memset(memo,-1,sizeof(memo));
    function<int(int,int,int,int)> dfs = [&](int i, int j, int k, int l){
        if (i == s.size()) {
            return j;
        }
        if (memo[i][j][k][l] != -1) return memo[i][j][k][l];
        int& res = memo[i][j][k][l];
        res = 0;
        if (!l) {
            res += dfs(i+1,j,0,0);
        }
        int up = k ? s[i]-'0' : 9;
        for (int m = 1-l; m <= up; ++m) {
            if (m == 1) {
                res += dfs(i+1,j+1,k && m == up,1);
            } else {
                res += dfs(i+1,j,k && m == up,1);
            }
        }
        return res;
    };
    return dfs(0,0,1,0);
}

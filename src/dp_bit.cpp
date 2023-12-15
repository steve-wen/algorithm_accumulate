#include <bits/stdc++.h>

using namespace std;

/**
*  数位 dp
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
// j 记录 1 的个数
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

// lc.no.2719
// j 记录数位之和
int count(string s1, string s2, int a, int b) {
    int MOD = 1e9+7;

    int memo1[23][500][2][2];
    memset(memo1,-1,sizeof(memo1));
    function<int(int,int,int,int)> dfs1 = [&](int i, int j, int k, int l){
        if (i == s1.size()) {
            if (a <= j && j <= b && !k)
                return 1;
            else return 0;
        }
        if (memo1[i][j][k][l] != -1) return memo1[i][j][k][l];
        int& res = memo1[i][j][k][l];
        res = 0;
        if (j > b) return 0;
        if (!l) {
            res = (res +dfs1(i+1,j,0,0)) % MOD;
        }
        int up = k ? s1[i]-'0' : 9;
        for (int m = 1 - l; m <= up; ++m) {
            res = (res + dfs1(i + 1, j+m, k && m == up, 1)) % MOD;
        }
        return res;
    };
    int cnt1 = dfs1(0,0,1,0);

    int memo2[23][500][2][2];
    memset(memo2,-1,sizeof(memo2));
    function<int(int,int,int,int)> dfs2 = [&](int i, int j, int k, int l){
        if (i == s2.size()) {
            if (a <= j && j <= b)
                return 1;
            else return 0;
        }
        if (memo2[i][j][k][l] != -1) return memo2[i][j][k][l];
        int& res = memo2[i][j][k][l];
        res = 0;
        if (j > b) return 0;
        if (!l) {
            res = (res +dfs2(i+1,j,0,0)) % MOD;
        }
        int up = k ? s2[i]-'0' : 9;
        for (int m = 1 - l; m <= up; ++m) {
            res = (res + dfs2(i + 1, j+m, k && m == up, 1)) % MOD;
        }
        return res;
    };
    int cnt2 = dfs2(0,0,1,0);
    return (cnt2-cnt1+MOD)%MOD;
}

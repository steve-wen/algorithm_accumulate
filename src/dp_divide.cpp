#include <bits/stdc++.h>

using namespace std;

/**
*  划分型 dp
*/

/**
 * 划分型 + 记忆化
 * 注意细节， 改 bug 结合调试 (仔细处)
 * lc.no.2547
 * @param a
 * @param k
 * @return
 */
int minCost(vector<int>& a, int k) {
    int n = a.size();
    vector<vector<int>> s(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        unordered_map<int,int> mp;
        for (int j = i; j < n; ++j) {
            if (mp[a[j]] == 1) {
                s[i][j] = s[i][j-1]+2;
            } else if (mp[a[j]] > 1) {
                s[i][j] = s[i][j-1]+1;
            } else if (j > 0){
                s[i][j] = s[i][j-1];
            }
            ++mp[a[j]];
        }
    }
    // int memo[n+1][n+1];
    static int memo[(int)1e3+1][(int)1e3+1];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j){
        if (i < 0) {
            if (j < 0) return 0;
            else return k + s[0][j];
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = min(k+s[i][j]+dfs(i-1,i-1),dfs(i-1,j));
        return res;
    };
    return dfs(n-1,n-1);
}

/**
 * 划分型 dp
 * lc.no.2767
 * @param s
 * @return
 */
int minimumBeautifulSubstrings(string s) {
    int n = s.size();
    auto check = [&](string s1) {
        if (s1 == "1" || s1 == "101" || s1 == "11001" || s1== "1111101" || s1 == "1001110001" || s1=="110000110101" || s1=="11110100001001") {
            return true;
        } else return false;
    };
    vector<vector<int>> memo(20,vector<int>(20,-1));

    function<int(int,int)> dfs = [&](int i, int j) {
        if (i < 0) {
            if(j < 0) return 0;
            else {
                if (check(s.substr(0,j+1))) return 1;
                else return 20;
            }
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        res = dfs(i-1,j);
        if (check(s.substr(i,j-i+1))) {
            res = min(1+dfs(i-1,i-1), res);
        }
        return res;
    };
    auto ans = dfs(n-1,n-1);
    return  ans >= 20 ? -1 : ans;
}

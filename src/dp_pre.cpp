#include <bits/stdc++.h>

using namespace std;

/**
*  预处理 + dp
*
*/

/**
 * set 二分预处理下标 + dp
 * https://leetcode.cn/problems/odd-even-jump/description/
 * @param a
 * @return
 */
int oddEvenJumps(vector<int>& a) {
    set<pair<int,int>> st;
    int n = a.size();
    for (int i = 0;i < n; ++i) {
        st.emplace(a[i],i);
    }
    vector<int> ind1(n), ind2(n);
    for (int i = 0; i < n; ++i) {
        st.erase(pair<int,int>(a[i],i));
        int j = n,k = n;
        if (st.lower_bound(pair<int,int>(a[i],i)) != st.end()) {
            j = (*st.lower_bound(pair<int,int>(a[i],i))).second;
        }
        if (st.lower_bound(pair<int,int>(a[i],i)) != st.begin()) {
            auto l = st.lower_bound(pair<int,int>(a[i],i));
            if (l->first == a[i]) {
                k = l->second;
            } else {
                --l;
                int m = l->first;
                auto l1 = st.lower_bound(pair<int,int>(m,0));
                k = l1->second;
            }
        } else if(st.begin()->first == a[i]) {
            k = st.begin()->second;
        }
        ind1[i] = j;
        ind2[i] = k;
    }
    int memo[(int)2e4+2][3];
    memset(memo,-1,sizeof(memo));
    function<int(int,int)> dfs = [&](int i, int j){
        if (i == n-1) {
            return 1;
        }
        if (i > n-1) {
            return 0;
        }
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        if (j % 2) {
            res = dfs(ind1[i],j-1);
        } else {
            res = dfs(ind2[i],j+1);
        }
        return res;
    };
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += dfs(i,1);
    }
    return ans;
}


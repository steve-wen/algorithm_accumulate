#include <bits/stdc++.h>

using namespace std;

/**
*  中位数贪心
*/

#define ll long long
/**
 * 中位数贪心 + 找中位数(遍历)
 * https://leetcode.cn/problems/minimum-cost-to-make-array-equalindromic/submissions/526708032/
 * @param nums
 * @return
 */
long long minimumCost(vector<int>& a) {
    int n = a.size();
    sort(a.begin(),a.end());
    ll ans = 0;
    auto check = [&](string s){
        string s1 = s;
        reverse(s.begin(),s.end());
        if (s1 == s) {
            return true;
        }
        return false;
    };
    ll b = a[n/2];
    ll mx = b;
    for (;mx < b+1e5; ++mx) {
        if (check(to_string(mx))) {
            break;
        }
    }
    ll mn = b;
    for (;mn > b-1e5; --mn) {
        if (check(to_string(mn))) {
            break;
        }
    }
    ll ans1 = 0,ans2 = 0;
    for (auto& a1 : a) {
        ans1 += (ll)(abs(a1-mx));
        ans2 += (ll)(abs(a1-mn));
    }
    ans = min(ans1,ans2);
    return ans;
}

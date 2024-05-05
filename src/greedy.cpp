#include <bits/stdc++.h>

using namespace std;

/**
 *  贪心
 *
*/

#define ll long long

/**
 * 贪心+模拟, 逆序对 ?
 * https://leetcode.cn/problems/minimum-number-of-moves-to-make-palindrome/solutions/1313466/tan-xin-zheng-ming-geng-da-shu-ju-fan-we-h57i/
 * @param s
 * @return
 */
int minMovesToMakePalindrome(string s) {
    int ans = 0;
    int n = s.size();
    for (int i = 0;i < n/2; ++i){
        auto c = s[i];
        int k = i;
        for (int j = n-1-i; j >= i; --j) {
            if (s[j] == c){
                k = j;
                break;
            }
        }
        if (k == i){
            swap(s[i],s[i+1]);
            ++ans;
            --i;
        } else {
            for (int j = k; j < n-1-i; ++j){
                swap(s[j],s[j+1]);
                ++ans;
            }
        }
    }
    return ans;
}

/**
 * 排序 + 贪心 + 遍历
 * https://leetcode.cn/problems/maximum-performance-of-a-team/description/
 * @param n
 * @param a
 * @param b
 * @param k
 * @return
 */
int maxPerformance(int n, vector<int>& a, vector<int>& b, int k) {
    vector<pair<ll,ll>> p;
    ll mod = 1e9+7;
    for (int i = 0; i < n; i++){
        p.emplace_back(b[i],a[i]);
    }
    sort(p.rbegin(),p.rend());
    priority_queue<ll,vector<ll>,greater<>> q;
    ll sum = 0, ans = 0;
    for (int i = 0; i < k; ++i) {
        sum += p[i].second;
        ans = max(ans,sum*p[i].first);
        q.emplace(p[i].second);
    }
    ans = max(ans,sum*p[k-1].first);
    for (int i = k; i < n; ++i) {
        ll c = q.top();
        q.pop();
        sum -= c;
        q.emplace(p[i].second);
        sum += p[i].second;
        ans = max(ans,sum*p[i].first);
    }
    return ans%mod;
}

/**
 * 贪心+分类讨论+枚举
 * https://leetcode.cn/problems/minimum-cost-to-equalize-array/solutions/2766600/fen-lei-tao-lun-on-zuo-fa-pythonjavacgo-9bsb4/
 * @param a
 * @param t1
 * @param t2
 * @return
 */
int minCostToEqualizeArray(vector<int>& a, int t1, int t2) {
    int mod = 1e9+7;
    sort(a.rbegin(),a.rend());
    int n = a.size();
    ll mx = a[0];
    ll sum1 = 0;
    for (auto& a1 : a) {
        sum1 += (ll)(mx-a1);
    }
    ll ans1 = 1e17;
    for (ll k = mx; k <= min((ll)2e6,mx*2); ++k) {
        ll ans = 0;
        ll sum = (ll)(k-mx)*(ll)n+sum1;
        if (t2 >= 2*t1) {
            return sum*t1%mod;
        }
        ll d1 = k-a.back();
        ll sum1 = sum-d1;
        if (sum1 >= d1) {
            if (sum%2) {
                ans = ((sum/2)*(ll)t2+(ll)t1);
            } else {
                ans = (sum/2)*(ll)t2;
            }
        } else {
            ans = ((sum1)*(ll)t2+(d1-sum1)*t1);
        }
        ans1 = min(ans1,ans);
    }
    return ans1%mod;
}

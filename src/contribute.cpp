#include <bits/stdc++.h>

using namespace std;

/**
*  贡献法
*/

/**
 * 贡献法 + 增量法(结合理解)
 * 求最大/最小与顺序无关 -> 排序 (有序是很好的性质)
 * 手玩，从枚举开始推公式(单个贡献, 规律增量)
 * lc.no.2681
 * @param a
 * @return
 */
int sumOfPower(vector<int>& a) {
    long long MOD = 1e9+7;
    long long ans = 0, s = 0;
    int n = a.size();
    sort(a.begin(),a.end());
    for (int i =0; i < n; ++i) {
        ans = (ans+((long long)a[i]*(long long)a[i]%MOD)*((long long)a[i]+s))%MOD;
        s = (s*2 + (long long)a[i])%MOD;
    }
    return ans;
}

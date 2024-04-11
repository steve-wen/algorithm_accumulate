#include <bits/stdc++.h>

using namespace std;

/**
*  rb_tree 的库的调用
*/

#include <ext/pb_ds/assoc_container.hpp>  // 因为tree定义在这里 所以需要包含这个头文件
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

/**
 * rb_tree 类似于 set 但是功能更强大：（不用离散化）
 * 如果要实现 map 则 null_type 参数对应于 map 的第二个参数
 * 1. order_of_key(x) 返回集合中严格小于输入参数 x 的元素个数；不用离散化
 * 2. *find_by_order(k) 返回第 k 小的元素（从 0 开始计数）
 * 注意：当有重复元素时，使用 pair<int, int>， p.second 表示插入的时间，以此来支持 multi
 * https://leetcode.cn/problems/distribute-elements-into-two-arrays-ii/description/
 */
// 不支持 multi (重复元素)
// 使用 pair<int,int> , p.second 表示插入的时间，以此来支持 multi
__gnu_pbds::tree<pair<int, int>, __gnu_pbds::null_type, less<pair<int, int> >,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update> t1, t2;

vector<int> resultArray_1(vector<int> &a) {
    int n = a.size();
    vector<int> v1, v2;
    v1.push_back(a[0]);
    v2.push_back(a[1]);
    t1.insert({a[0], 1});
    t2.insert({a[1], 2});
    for (int i = 2; i < n; i++) {
        int g1 = v1.size() - t1.order_of_key({a[i] + 1, 0}); // order_of_key(x) 返回集合中严格小于输入参数 x 的元素个数；不用离散化
        int g2 = v2.size() - t2.order_of_key({a[i] + 1, 0});
        // cout<<a[i]<<" "<<g1<<" "<<g2<<endl;
        if (g1 > g2 || (g1 == g2 && v1.size() <= v2.size())) {
            t1.insert({a[i], i + 1});
            v1.push_back(a[i]);
        } else {
            t2.insert({a[i], i + 1});
            v2.push_back(a[i]);
        }
    }
    auto x1 = *t1.find_by_order(0); // *find_by_order(k) 返回第 k 小的元素（从 0 开始计数）
    auto x2 = *t2.find_by_order(0);
    for (int x: v2) v1.push_back(x);
    return v1;
}

/**
 * https://leetcode.cn/problems/number-of-excellent-pairs/description/
 * @param a2
 * @param k
 * @return
 */
long long countExcellentPairs(vector<int>& a2, int k) {
    unordered_set<int> st(a2.begin(),a2.end());
    vector<int> a(st.begin(),st.end());
    vector<int> b;
    int n = a.size();
    for (auto& a1 : a) {
        b.emplace_back(__builtin_popcount(a1));
    }
    __gnu_pbds::tree<pair<int, int>, __gnu_pbds::null_type, less<pair<int, int> >,
        __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update> t;
    for (int i = 0; i < n; ++i){
        t.insert({b[i],i});
    }
    long long ans = 0;
    for (int i = 0; i < n-1; ++i) {
        t.erase({b[i],i});
        int v = k-b[i];
        if (v >= 34) continue;
        long long cnt = n-1-i - t.order_of_key({v,0});
        ans += cnt*2;
    }
    for (auto& b1 : b){
        if (b1 * 2 >= k) {
            ++ans;
        }
    }
    return ans;
}

/**
 * rb_tree 的灵活运用
 * https://leetcode.cn/problems/ways-to-split-array-into-three-subarrays/description/
 * @param a
 * @return
 */
int waysToSplit(vector<int>& a) {
    int mod = 1e9+7, n = a.size();
    vector<int> s(n+1);
    for (int i = 0; i < n; ++i) {
        s[i+1] = s[i]+a[i];
    }
    int ans = 0;
    __gnu_pbds::tree<pair<int, int>, __gnu_pbds::null_type, less<pair<int, int> >,
        __gnu_pbds::rb_tree_tag,
        __gnu_pbds::tree_order_statistics_node_update> t;
    for (int i = 1; i <= n; ++i){
        t.insert({s[i],i});
    }
    for (int i = 0; i < n-2; ++i) {
        int s1 = s[i+1];
        int cnt1 = t.order_of_key({s1*2,0});
        cnt1 = max(cnt1,i+1);
        int cnt2 = t.order_of_key({(s[n]-s1)/2+s1+1,0});
        cnt2 = min(cnt2,n-1);
        ans = (ans +max(cnt2-cnt1,0)) % mod;
    }
    return ans;
}

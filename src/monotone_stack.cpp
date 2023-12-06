#include <bits/stdc++.h>

using namespace std;

/**
*  单调栈
*/

/**
 * 单调栈：下一个更大的元素 (1)
 *        1. 原数组无序， 要找到下一个更大元素
 *        2. 单调栈存值
 * lc.no.496
 * @param nums1
 * @param nums2
 * @return
 */
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    int n = nums2.size(), m = nums1.size();
    vector<int> vec(n);
    stack<int> s;
    for(int i = n-1; i >= 0; --i){
        while (!s.empty() && s.top() < nums2[i]) {
            s.pop();
        }
        vec[i] = s.empty() ? -1:s.top();
        s.emplace(nums2[i]);
    }
    unordered_map<int,int> mp;
    for (int i = 0; i < n; ++i) {
        mp[nums2[i]] = i;
    }
    vector<int> ans(m);
    for (int i = 0; i < m; ++i){
        ans[i] = vec[mp[nums1[i]]];
    }
    return ans;
}

/**
 * 单调栈 + 前后缀和：从右向左单调减 ： 正序，下一个更小的元素； 从左向右单调增： 倒序， 下一个更大的元素
 * 单调栈存下标
 * lc.no.2866 美丽塔 2
 * @param h
 * @return
 */
long long maximumSumOfHeights(vector<int>& h) {
    int n  = h.size();
    // 单调栈
    stack<int> s1;
    // 记录下标
    vector<int> ind1(n);
    // 从右向左单调减 ： 正序，下一个更小的元素
    for (int i = 0; i < n; ++i) {
        // pop 大于的元素
        while (!s1.empty() && h[s1.top()] > h[i]) {
            s1.pop();
        }
        // -1 标记
        ind1[i] = s1.empty() ? -1 : s1.top();
        s1.emplace(i);
    }
    // 前缀和
    vector<long> pre(n);
    for (int i = 0; i < n; ++i) {
        if (ind1[i] == -1) {
            pre[i] = (long)h[i] * (i+1);
        } else {
            pre[i] = pre[ind1[i]] + (long)(i-ind1[i]) * h[i];
        }
    }

    stack<int> s2;
    vector<int> ind2(n);
    // 从左向右单调减 ： 倒序，下一个更小的元素
    for (int i = n-1; i >= 0; --i) {
        while (!s2.empty() && h[s2.top()] > h[i]) {
            s2.pop();
        }
        ind2[i] = s2.empty() ? -1 : s2.top();
        s2.emplace(i);
    }
    vector<long> suf(n);
    for (int i = n-1; i >= 0; --i) {
        if (ind2[i] == -1) {
            suf[i] = (long)h[i] * (n-i);
        } else {
            suf[i] = suf[ind2[i]] + (long)(ind2[i]-i) * h[i];
        }
    }
    long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, pre[i]+suf[i]-(long)h[i]);
    }
    return ans;
}

/**
 * 经典单调栈， 数形结合
 * @param h
 * @return
 */
int longestWPI(vector<int>& h) {
    int n = h.size(), ans = 0;
    vector<int> pre(n+1);
    stack<int> st;
    st.emplace(0);
    for (int i = 0; i < n; ++i) {
        pre[i+1] = pre[i]+ (h[i] > 8 ? 1 : -1);
        if (pre[st.top()] > pre[i+1]) {
            st.emplace(i+1);
        }
    }
    for (int i = n; i >= 0; --i) {
        while (!st.empty() && pre[i] - pre[st.top()] > 0) {
            ans = max(ans, i-st.top());
            st.pop();
        }
    }
    return ans;
}

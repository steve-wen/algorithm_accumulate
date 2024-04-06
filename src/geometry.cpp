#include <bits/stdc++.h>

using namespace std;

/**
*  计算几何
*/

/**
 * 曼哈顿距离 max 值
 * https://leetcode.cn/problems/minimize-manhattan-distances/description/
 * @param p
 * @return
 */
int minimumDistance(vector<vector<int>>& p) {
    int n = p.size();
    int ans = 1e9;
    vector<pair<int,int>> v1;
    vector<pair<int,int>> v2;
    for (int i = 0; i < n; ++i) {
        v1.emplace_back(p[i][0]+p[i][1],i);
        v2.emplace_back(p[i][0]-p[i][1],i);
    }
    sort(v1.rbegin(),v1.rend());
    sort(v2.rbegin(),v2.rend());
    auto j1 = v1.begin()->second;
    if (p[j1][0] - p[j1][1] == v2.begin()->first) {
        ans = min(ans, max((v1.begin()+1)->first-v1.rbegin()->first, (v2.begin()+1)->first-v2.rbegin()->first));
    } else if (p[j1][0] - p[j1][1] == v2.rbegin()->first){
        ans = min(ans, max((v1.begin()+1)->first-v1.rbegin()->first, (v2.begin())->first-(v2.rbegin()+1)->first));
    } else {
        ans = min(ans, max((v1.begin()+1)->first-v1.rbegin()->first, (v2.begin())->first-(v2.rbegin())->first));
    }

    auto j2 = v1.rbegin()->second;
    if (p[j2][0] - p[j2][1] == v2.begin()->first) {
        ans = min(ans, max((v1.begin())->first-(v1.rbegin()+1)->first, (v2.begin()+1)->first-v2.rbegin()->first));
    } else if (p[j2][0] - p[j2][1] == v2.rbegin()->first){
        ans = min(ans, max((v1.begin())->first-(v1.rbegin()+1)->first, (v2.begin())->first-(v2.rbegin()+1)->first));
    } else {
        ans = min(ans, max((v1.begin())->first-(v1.rbegin()+1)->first, (v2.begin())->first-(v2.rbegin())->first));
    }

    auto j3 = v2.begin()->second;
    if (p[j3][0] + p[j3][1] == v1.begin()->first) {
        ans = min(ans, max((v1.begin()+1)->first-v1.rbegin()->first, (v2.begin()+1)->first-v2.rbegin()->first));
    } else if (p[j3][0] + p[j3][1] == v1.rbegin()->first){
        ans = min(ans, max((v1.begin())->first-(v1.rbegin()+1)->first, (v2.begin()+1)->first-v2.rbegin()->first));
    } else {
        ans = min(ans, max((v1.begin())->first-v1.rbegin()->first, (v2.begin()+1)->first-v2.rbegin()->first));
    }

    auto j4 = v2.rbegin()->second;
    if (p[j4][0] + p[j4][1] == v1.begin()->first) {
        ans = min(ans, max((v1.begin()+1)->first-v1.rbegin()->first, (v2.begin())->first-(v2.rbegin()+1)->first));
    } else if (p[j4][0] + p[j4][1] == v1.rbegin()->first){
        ans = min(ans, max((v1.begin())->first-(v1.rbegin()+1)->first, (v2.begin())->first-(v2.rbegin()+1)->first));
    } else {
        ans = min(ans, max((v1.begin())->first-v1.rbegin()->first, (v2.begin())->first-(v2.rbegin()+1)->first));
    }
    return ans;
}

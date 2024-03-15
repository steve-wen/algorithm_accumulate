#include <bits/stdc++.h>

using namespace std;

/**
*  莫队算法
*/

/**
 * 普通莫队算法
 * P2709 小B的询问
 * https://www.luogu.com.cn/problem/P2709
 * 时间复杂度 O(n*n^(1/2)) (n 根号 n)
 */
class Modui_Common{
    static const int maxn = 5e4 + 5;
    int a[maxn],pos[maxn],cnt[maxn]; // a[] 记录输入的 vec, cnt[] 记录 a[] 的次数
    long long ans[maxn]; // ans[] 存放每次询问的结果
    long long res; // 当前询问的结果，会动态变化
    struct Q
    {
        int l,r,k;
    }q[maxn]; // l,r 对应询问区间范围， k 记录是哪一次询问
    // Add, Sub 是对于不同的题，需要修改的地方，其他是模板
    void Add(int n) { cnt[a[n]]++; res+=cnt[a[n]]*cnt[a[n]]-(cnt[a[n]]-1)*(cnt[a[n]]-1); } // 统计区间数字出现次数的平方和 (用现在的 - 之前的 == 新增的)
    void Sub(int n) { cnt[a[n]]--; res-=(cnt[a[n]]+1)*(cnt[a[n]]+1)-cnt[a[n]]*cnt[a[n]]; } // 同上

    vector<long long> modui_common(vector<int>& vec, vector<vector<int>>& que, int k) {
        int n = vec.size(),m = que.size();
        int siz = sqrt(n); // 分块?
        for(int i=1;i<=n;i++)
        {
            a[i] = vec[i-1];
            pos[i]=i/siz;
        }
        for(int i=0;i<m;i++)
        {
            q[i].l = que[i][0];
            q[i].r = que[i][1];
            q[i].k=i;
        }
        std::sort(q,q+m,[&](Q x,Q y){
            return pos[x.l]==pos[y.l]?x.r<y.r:pos[x.l]<pos[y.l];
        });
        int l=1,r=0;
        for(int i=0;i<m;i++)
        {
            while(q[i].l<l) Add(--l);
            while(q[i].r>r) Add(++r);
            while(q[i].l>l) Sub(l++);
            while(q[i].r<r) Sub(r--);
            ans[q[i].k]=res;
        }
        vector<long long> result(ans,ans+m);
        return result;
    }
};

/**
 * 普通莫队
 * 小 Z 的袜子，已解决
 * https://www.luogu.com.cn/problem/P1494
 * 时间复杂度 O(n*n^(1/2)) (n 根号 n)
 */
class Modui_Common_1{
    static const int maxn = 5e4 + 5;
    int a[maxn],pos[maxn],cnt[maxn];
    long long ans[maxn];
    long long res;
    struct Q
    {
        int l,r,k;
    }q[maxn];
    // 统计区间数字出现次数的可选取其中两个的方法数，即 C(2 n) (用现在的 - 之前的 == 新增的)
    void Add(int n) { cnt[a[n]]++; res+=(cnt[a[n]]*(cnt[a[n]]-1))/2-((cnt[a[n]]-1)*(cnt[a[n]]-2))/2; }
    void Sub(int n) { cnt[a[n]]--; res-=(cnt[a[n]]+1)*(cnt[a[n]])/2-(cnt[a[n]]*(cnt[a[n]]-1))/2; }

    vector<long long> modui_common(vector<int>& vec, vector<vector<int>>& que) {
        int n = vec.size(),m = que.size();
        int siz = sqrt(n);
        for(int i=1;i<=n;i++)
        {
            a[i] = vec[i-1];
            pos[i]=i/siz;
        }
        for(int i=0;i<m;i++)
        {
            q[i].l = que[i][0];
            q[i].r = que[i][1];
            q[i].k=i;
        }
        std::sort(q,q+m,[&](Q x,Q y){
            return pos[x.l]==pos[y.l]?x.r<y.r:pos[x.l]<pos[y.l];
        });
        int l=1,r=0;
        for(int i=0;i<m;i++)
        {
            while(q[i].l<l) Add(--l);
            while(q[i].r>r) Add(++r);
            while(q[i].l>l) Sub(l++);
            while(q[i].r<r) Sub(r--);
            ans[q[i].k]=res;
        }
        vector<long long> result(ans,ans+m);
        return result;
    }
};

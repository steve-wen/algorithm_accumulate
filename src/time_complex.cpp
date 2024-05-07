#include <bits/stdc++.h>

using namespace std;
#define ll long long

/**
*  time_complex
*/

/**
 * 一般ACM或者笔试题的时间限制是1秒或2秒。
    在这种情况下，C++代码中的操作次数控制在 10^7 为最佳。
    下面给出在不同数据范围下，代码的时间复杂度和算法该如何选择：
    n≤30 => 指数级别, dfs+剪枝，状态压缩dp
    n≤10^2 => O(n^3)，floyd，dp
    n≤1000 => O(n2)，O(n^2logn)，dp，二分
    n≤10^4 => O（n*sqrt(n)），块状链表，质数，莫队
    n≤10^5 => O(nlogn)，各种sort，前缀和+哈希表(套路)、枚举小写字母/位运算 + 遍历、线段树、树状数组、贪心+枚举、set/map、heap、dijkstra+heap、拓扑排序、spfa、求凸包、求半平面交、二分、组合数学、容斥原理
    n≤10^6 => O(n)， 以及常数较小的 O(nlogn)算法， hash、双指针扫描、并查集、kmp、AC自动机，常数比较小的 O(nlogn) 的做法：sort、树状数组、heap、dijkstra、spfa
    n≤10^7 => O(n)，双指针扫描、kmp、AC自动机、线性筛素数
    n≤10^9 => O（sqrt(n)），判断质数 ；O(logn)，二分
    n≤10^18 => O(logn)，最大公约数，快速幂，二分
 */

/**
 * 测试程序用时，单位 ms
 */
//    clock_t s,e;
//    s = clock();
//    auto ans = func1(25,18);
//    e = clock();
//    cout << double(e-s);


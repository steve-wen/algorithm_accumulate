#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, from, to) for(ll i = from;i<to;i++)
#define rrep(i, from, to) for(ll i = from;i>=to;i--)
#define se second
#define fi first
#define tostring(a) (ostringstream() << a).str()

typedef pair<int,int> pii;
typedef pair<long,long> pll;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * n! n 的阶乘
 * @param n
 * @return
 */
long long fact(int n) {
    long long cnt = 1;
    while(n) {
        cnt *= n;
        --n;
    }
    return cnt;
}

/**
 * 类 string
 */
class String {
public:
    //通用构造函数
    String(const char *str = nullptr) {
        // 获取 str 长度的方法
        string strtmp(str);
        size_t len = strtmp.size();
        if (str == nullptr) {
            return;
        } else {
            // 获取 str 长度的方法
            m_data = new char[strlen(str)];
            for (size_t i = 0; i < strlen(str); ++i) { // 可用 strcpy(m_data, str) 代替
                m_data[i] = str[i];
            }
        }
    };
    //拷贝构造函数
    String(const String &another) {
        m_data = new char [strlen(another.m_data)];
        for (size_t i = 0; i < strlen(another.m_data); ++i) {
            m_data[i] = another.m_data[i];
        }
    };
    //析构函数
    ~String() {
        delete[] m_data;
        m_data = nullptr;
    };
    //赋值函数
    String &operator=(const String &rhs) {
        // 检查自赋值
        if (this == &rhs) {
            return *this;
        } else {
            delete[] m_data;
            m_data = new char[strlen(rhs.m_data)];
            for (size_t i = 0; i < strlen(rhs.m_data); ++i) {
                m_data[i] = rhs.m_data[i];
            }
            return *this;
        }
    };
    //取下标函数
    char &operator[](int i) {
        return m_data[i];
    };
private:
    char *m_data;//用于保存字符串
};


/**
 * 树形 dp, 记忆化搜索（也可用 chatgpt 转成 python 加 @cache）
 * fa 不用记忆
 * 自顶向下
 * @param e
 * @param c
 * @param k
 * @return
 */
int maximumPoints(vector<vector<int>>& e, vector<int>& c, int k) {
    int n = c.size();
    // 建图， 建树， 无向边
    vector<vector<int>> g(n);
    for (auto& e1 : e) {
        g[e1[0]].emplace_back(e1[1]);
        g[e1[1]].emplace_back(e1[0]);
    }
    // memo 数组注意不要爆内存
    int memo[n+2][18];
    memset(memo,-1,sizeof(memo));
    function<int(int,int,int)> dfs = [&](int i, int j, int fa){
        // 边界， 右移 14 位后，都变为0(0 > 负数)
        if (j >= 14) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        int& res = memo[i][j];
        int res1 = (c[i]>>j)-k, res2 = c[i]>>(j+1);
        for (auto& i1 : g[i]) {
            if (i1 != fa) {
                res1 += dfs(i1,j,i);
                res2 += dfs(i1,j+1,i);
            }
        }
        return max(res1,res2);
    };
    return dfs(0,0,0);
}

// 考虑记忆化搜索 dfs 树形dp, 记忆化搜索
long long maximumScoreAfterOperations(vector<vector<int>>& e, vector<int>& v) {
    long n = v.size(), ans = 0;
    // 建图， 建树
    vector<vector<int>> g(n);
    for (auto &e1: e) {
        g[e1[1]].emplace_back(e1[0]);
        g[e1[0]].emplace_back(e1[1]);
    }
    // memo 数组注意不要爆内存
    long memo[n+2][2];
    memset(memo,-1,sizeof(memo));
    function<long(int,int,int)> dfs = [&](int i, int j, int fa){
        // 边界， 判断叶子节点
        if (g[i].size() == 1 && g[i][0] == fa) {  // g[i].size() == 1 && i != 0
            return 0L;
        }
        if (memo[i][j] != -1) return memo[i][j];
        long& res = memo[i][j];
        res = 0;
        for (auto& i1 : g[i]) {
            if (i1 != fa) { // 不往上递归
                if (j ==1) {
                    res += dfs(i1,1,i)+(long)v[i1];
                } else {
                    if (g[i1].size() == 1 && g[i1][0] == i) {
                        res += dfs(i1,1,i);
                    } else {
                        res += max(dfs(i1,1,i), dfs(i1,0,i)+(long)v[i1]);
                    }
                }
            }
        }
        return res;
    };
    return max(dfs(0,0,0)+(long)v[0], dfs(0,1,0));
}

// 二叉树的直径， 找拐点，分成两条链 no.534
int diameterOfBinaryTree(TreeNode* root) {
    int ans = 0;
    function<int(TreeNode*)> dfs = [&](TreeNode* r){
        if (r == nullptr) return -1;
        int L = dfs(r->left), R = dfs(r->right); // 用 L，R 记录 dfs, 类似 memo 数组记忆化
        ans = max(ans, L+R+2);
        return max(L,R)+1;
    };
    dfs(root);
    return ans;
}

// 二叉树的最大路径和 no.124
int maxPathSum(TreeNode* root) {
    int ans = -10;
    function<int(TreeNode*)> dfs = [&](TreeNode* r){
        if (r == nullptr) return 0;
        int L = max(0,dfs(r->left)), R = max(0,dfs(r->right)); // 用 L，R 记录 dfs, 类似 memo 数组记忆化
        ans = max(ans, L+R+r->val);
        return max(L,R)+r->val;
    };
    dfs(root);
    return ans;
}

// no.968 监控二叉树
int minCameraCover(TreeNode* root) {
    // 记忆化， memo map
    map<pair<TreeNode*,int>,int> memo;
    function<int(TreeNode*,int)> dfs = [&](TreeNode* r, int j){
        if (r == nullptr) {
            return j == 0 ? (int)10 : 0;
        }
        if(memo.count(pair(r,j))) return memo[pair(r,j)];
        int& res = memo[pair(r,j)];
        int l0 = dfs(r->left,0), l1 = dfs(r->left,1), l2 = dfs(r->left,2);
        int r0 = dfs(r->right,0), r1 = dfs(r->right,1), r2 = dfs(r->right,2);
        if (j == 0) {
            res = min(min(l0,l1),l2) + min(min(r0,r1),r2) + 1;
        } else if (j ==1) {
            res = min(l0,l2)+min(r0,r2);
        } else {
            res = min(min(l0+r0,l0+r2),l2+r0);
        }
        return res;
    };
    return min(dfs(root,0),dfs(root,2));
}



int main(){
    return 0;
}

/**
 * luogu/nowcoder/codeforces
 * "\n" 比 endl 快很多
 */

//#include <bits/stdc++.h>
//
//using namespace std;
//#define endl "\n"
//int MOD = 1e9+7;
//
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    int n,x;
//    cin >> n>>x;
//    vector<int> a(n);
//    for (int i =0; i <n; ++i) {
//        cin >> a[i];
//    }
//    sort(a.begin(),a.end());
//    int n1 = lower_bound(a.begin(),a.end(),x) - a.begin();
//    int n2 = upper_bound(a.begin(),a.end(),x) -a.begin()-1;
//    int n3 = (n-1)/2;
//    if (n1 <= n3 && n2 >= n3) {
//        cout << 0;
//    } else if (n1 > n3) {
//        cout<< (n1-n3)*2-((n+1)%2);
//    } else if (n2 < n3) {
//        cout<< (n3-n2)*2-((n)%2);
//    }
//    return 0;
//}

/**
 * codeforces
 */
//#include <bits/stdc++.h>
//
//using namespace std;
//
//void solve() {
//    int n,k;
//    cin >> n >> k;
//    vector<int> a(n);
//    for (int i = 0; i < n; ++i) {
//        cin >> a[i];
//    }
//    int ans = 5;
//    if (k == 3) {
//        for (auto& b : a) {
//            ans = min(ans, 3- (b%3 == 0 ? 3 : b%3));
//        }
//
//    } else if (k == 5) {
//        for (auto& b : a) {
//            ans = min(ans, 5- (b%5 == 0 ? 5 : b%5));
//        }
//
//    } else if(k == 2){
//        for (auto& b : a) {
//            ans = min(ans, 2- (b%2 == 0 ? 2 : b%2));
//        }
//    }else {
//        int cnt = 0;
//        for (auto& b : a) {
//            cnt += (b % 2 == 0 ? 1 : 0);
//        }
//        for (auto& b : a) {
//            ans = min(ans, 4- (b%4 == 0 ? 4 : b%4));
//        }
//        if (n >= 2) {
//            ans = min(ans, 2-cnt >= 0 ? 2-cnt : 0);
//        }
//
//    }
//    cout << ans << endl;
//
//}
//
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//
//    int t;
//    cin >> t;
//    while (t--) {
//        solve();
//    }
//}

/**
 * impl list :
 * CF 的经典题, 注意练习
 * 0.9 中位数贪心
 * 1.0 tarjan 算法的理解和积累
 * 1.1 每日灵茶; 可根据灵神的视频总结模板等; 手机上看题目，然后口胡/看题解思路
 * 1. 1.2 练习对应分数的题目，包括速度 (注意速度) (注意对应分数)
 * 2. 注意 cf 题单，套路等
 * 3. 练习 CF 题单等; 多类型比赛并行打
 * 4. 2200 难度题
 * 5. 灵神 总结/归纳 的周赛题单（附难度分和知识点）-> 对应练习
 * 6. no.887 鸡蛋掉落
 * 9. 按灵神 github 模板， 整理算法结构
 * 10. 往届周赛 t4
 */

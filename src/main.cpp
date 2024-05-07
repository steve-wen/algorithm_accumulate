#include <bits/stdc++.h>
#include <ctime>

using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<long,long>
#define tiii tuple<int,int,int>

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


int main(){
    return 0;
}

#define ll long long
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
 * 0.5 刷灵神的 dp 题单 (注意分类刷灵神题单，从式酱思路得来)；注意何时用 dp 何时用记忆化；
 * 0.9 中位数贪心; 树上倍增/树上 lca 模板积累 https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/solutions/2305895/mo-ban-jiang-jie-shu-shang-bei-zeng-suan-v3rw/
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

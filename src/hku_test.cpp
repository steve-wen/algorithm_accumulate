#include <bits/stdc++.h>

using namespace std;
/**
 * 求平方根
 */

double func_square(double s) {
    if (s <= 0) return -1;
    double res = sqrt(s);
    double dif = 0.001;
    double x = s/2;
    while(abs(x-res) > dif) {
        x = (x+s/x)/2;
    }
    return x;
}

/**
 * 十进制转二进制
 */

string func_transf(int a) {
    string s = bitset<33>(a).to_string();
    string s1;
    for (int i = 0; i < 33; ++i) {
        if (s[i] == '1') {
            s1 = s.substr(i,33-i);
            return s1;
        }
    }
    return "0";
}

/**
 * x,x+2 是否是质数
 */

//string func_is_special(int a) {
//    for (int i = 1; i <= sqrt(a); ++i) {
//        if (a % i == 0 && is_prime(i)) {
//            if (a%(i+2) == 0 && is_prime(i+2)) {
//                return "YES";
//            }
//        }
//    }
//    return "NO";
//}

/**
 * a^2+b^3
 */

string func_is_spec(int x) {
    for (int i = 0; i <= sqrt(x); ++i) {
        for (int j = 0; j <= pow(x,1/3);++j){
            if (i*i + j*j*j == x) {
                return "YES";
            }
        }
    }
    return "NO";
}

/**
 * 统计频率
 */

//int main(){
//    unordered_map<int,int> mp;
//    int a;
//    while(cin>>a){
//        mp[a]++;
//    }
//    for(auto& p : mp) {
//        cout<<p.first<<":"<<p.second<<endl;
//    }
//    return 0;
//}

/**
 * 猜数字
 */

//int main(){
//    cout << "please input limit n"<<endl;
//    int n;
//    cin >> n;
//    if (n < 1) {
//        cout << "invalid input, try again"<<endl;
//        cin >> n;
//    }
//    int l = 1, r = n, ans = n;
//    while (l <= r) {
//        int mid = (l+r)/2;
//        cout<< "is" << mid <<"<"<< "the number? please input y or n"<<endl;
//        char s;
//        cin >> s;
//        if (s == 'y') {
//            l = mid+1;
//        } else {
//            ans = min(ans,mid);
//            r = mid-1;
//        }
//    }
//    cout <<"the number is " << ans;
//    return 0;
//}

/**
 * 最长公共子串
 */

string find_str(string a, string b){
    int m = a.size(), n = b.size(),len = 0;
    string ans;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i] == b[j]) {
                int k = i, l = j;
                while(k<m && l < n && a[k]==b[l]) {
                    if (k-i+1 > len) {
                        ans = a.substr(i,k-i+1);
                    }
                    ++k;
                    ++l;
                }
                len = max(len,(int)ans.size());
            }
        }
    }
    return ans;
}

/**
 * 取最值
 */

vector<int> find_max(vector<int> a) {
    if (a.empty()) return {0};
    else {
        return {*max_element(a.begin(),a.end()),*min_element(a.begin(),a.end())};
    }
}

/**
 * dfs
 * 暴力枚举，选哪一个
 */

//int main(){
//    int n;
//    cin >> n;
//    vector<vector<int>> ans;
//    vector<int> path;
//    function<void(int)> dfs = [&](int i){
//        if (i < 0) return;
//        if (i == 0) {
//            ans.emplace_back(path);
//            return;
//        }
//        path.emplace_back(1);
//        dfs(i-1);
//        path.pop_back();
//        path.emplace_back(2);
//        dfs(i-2);
//        path.pop_back();
//        path.emplace_back(3);
//        dfs(i-3);
//        path.pop_back();
//    };
//    dfs(n);
//    for (auto& a: ans){
//        for (auto& b : a) {
//            cout << b;
//        }
//        cout<<endl;
//    }
//    return 0;
//}

/**
 * dfs
 * 暴力枚举，选哪一个
 */

vector<vector<int>> func_enum(int n) {
    vector<vector<int>> ans;
    vector<int> path;
    function<void(int)> dfs = [&](int i){
        if (i < 0) return;
        if (i == 0) {
            ans.emplace_back(path);
            return;
        }
        path.emplace_back(1);
        dfs(i-1);
        path.pop_back();
        path.emplace_back(3);
        dfs(i-3);
        path.pop_back();
    };
    dfs(n);
    return ans;
}

/**
 * 单峰数列
 */

int is_peak(vector<int>& a) {
    auto it = max_element(a.begin(),a.end());
    auto ind = it - a.begin();
    int n = a.size();
    if (0<ind && ind<n-1) {
        for (int i =0; i < ind; ++i) {
            if (a[i] >= a[i+1]) return 0;
        }
        for (int i = ind; i < n-1; ++i) {
            if (a[i] <= a[i+1]) return 0;
        }
        return 1;
    }
    return 0;
}

/**
 * to_string
 */

bool is_correct_num(int a) {
    auto s = to_string(a);
    if (s.size() == 7 && s[3] == '0') return true;
    return false;
}

/**
 * 频率最高的数
 */

int find_freq(vector<int>& a) {
    unordered_map<int,int> mp;
    for(auto& a1:a) {
        mp[a1]++;
    }
    int mx = 0, ans = 0;
    for (auto& p : mp){
        if (p.second > mx) {
            ans = p.first;
            mx = p.second;
        }
    }
    return ans;
}

/**
 * 找出乘积最大的两个整数
 */

vector<int> find_num(vector<int>& a){
    int n = a.size();
    sort(a.begin(),a.end());
    if (a[0]*a[1] > a[n-1]*a[n-2]) {
        return {a[0],a[1]};
    } else {
        return {a[n-2],a[n-1]};
    }
}

/**
 * 容斥，遍历
 */

vector<int> light(int n, int k){
    vector<int> cnt(n+1);
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j % i == 0) {
                cnt[j]++;
            }
        }
    }
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (cnt[i] % 2 == 1) {
            ans.emplace_back(i);
        }
    }
    return ans;
}

/**
 * 跳台阶
 */

int sum_step(int n) {
    vector<int> f(n+1);
    f[0] = 1, f[1] = 1, f[2] = 2;
    for (int i = 3; i <= n; ++i) {
        f[i] = f[i-1]+f[i-2];
    }
    return f[n];
}

/**
 * perfect number
 */

//int main(){
//    int k;
//    cin >> k;
//    int cnt = 0;
//    for (int i = 2; i < 1e9; ++i) { // 注意从 2 开始，1 不是完美数
//        int sum =0;
//        for (int j = 1; j <= sqrt(i); ++j) {
//            if (i % j == 0) {
//                sum += j;
//                if (j != sqrt(i) && j != 1) {
//                    sum += (i/j);
//                }
//            }
//        }
//        if (sum == i) ++cnt;
//        if (cnt == k) {
//            cout << i;
//            return 0;
//        }
//    }
//    return 0;
//}

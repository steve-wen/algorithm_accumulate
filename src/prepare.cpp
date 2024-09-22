#include  <bits/stdc++.h>

using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<long,long>
#define tiii tuple<int,int,int>

/**
* prepare
*/

/**
 * 手动实现字符串hash
 * 注意随机化
 * https://oi-wiki.org/string/hash/
 * https://leetcode.cn/problems/find-beautiful-indices-in-the-given-array-ii/solutions/2603683/ha-xi-kmp-er-fen-by-tsreaper-mliq/
 */

vector<int> beautifulIndices(string s, string a, string b, int K) {
    // 随机哈希基数和模数，防止被 hack
    srand(time(0));
    int BASE = 37 + rand() % 107;
    int MOD = 998244353 + rand() % 10007;
    // 求字符串 s 的哈希
    // x*b^2 + y*b + z
    int n = s.size();
    long long P[n + 1];
    P[0] = 1;
    for (int i = 1; i <= n; i++) P[i] = P[i - 1] * BASE % MOD;
    long long h[n + 1];
    h[0] = 0;
    for (int i = 1; i <= n; i++) h[i] = (h[i - 1] * BASE + s[i - 1] - 'a') % MOD;

    // 求子串 s[L..R] 的哈希值
    auto calc = [&](int L, int R) {
        return (h[R] - h[L - 1] * P[R - L + 1] % MOD + MOD) % MOD;
    };

    // 用哈希找出 b 在 s 里出现的所有下标
    vector<int> vec;
    long long HB = 0;
    for (char c: b) HB = (HB * BASE + c - 'a') % MOD;
    for (int i = 1, j = b.size(); j <= n; i++, j++) if (calc(i, j) == HB) vec.push_back(i);

    vector<int> ans;
    // 用哈希找出 a 在 s 里出现的所有下标
    long long HA = 0;
    for (char c: a) HA = (HA * BASE + c - 'a') % MOD;
    for (int i = 1, j = a.size(); j <= n; i++, j++)
        if (calc(i, j) == HA) {
            // 在 vec 里二分，看是否存在范围内的数
            int idx = lower_bound(vec.begin(), vec.end(), i - K) - vec.begin();
            if (idx < vec.size() && vec[idx] <= i + K) ans.push_back(i - 1);
        }
    return ans;
}

/**
 * 手动实现 shared_ptr
 */
class Count {
private:
    int cnt;
public:
    Count() :cnt(1) {}
    ~Count() = default;
    void addcount() { ++cnt; }
    int getcount() { return cnt; }
    int reducecount() { return --cnt; }
};

template <typename T>
class Shared_ptr {
private:
    T* ptr;
    Count* cnt;
public:
    //构造函数
    Shared_ptr(T* pt = nullptr) : ptr(pt) {
        if (pt)
            cnt = new Count();
    }

    //析构函数
    ~Shared_ptr() {
        if (ptr && !cnt -> reducecount()) {
            delete ptr;
            delete cnt;
            ptr = nullptr;
            cnt = nullptr;
        }
    }

    //拷贝构造函数
    Shared_ptr(Shared_ptr<T>& sptr) {
        ptr = sptr.ptr;
        if (ptr) {
            cnt = sptr.cnt;
            cnt -> addcount();
        }
    }

    //移动构造函数
    Shared_ptr(Shared_ptr<T>&& sptr) {
        ptr = sptr.ptr;
        if (ptr) {
            cnt = sptr.cnt;
            sptr.ptr = nullptr;
            sptr.cnt = nullptr;
        }
    }

    //拷贝构造运算符
    Shared_ptr& operator=(Shared_ptr& sptr) {
        ptr = sptr.ptr;
        if (ptr) {
            cnt = sptr.cnt;
            cnt -> addcount();
        }
        return *this;
    }

    Shared_ptr& operator=(Shared_ptr<T>&& sptr) {
        ptr = sptr.ptr;
        if (ptr) {
            cnt = sptr.cnt;
            sptr.ptr = nullptr;
            sptr.cnt = nullptr;
        }
        return *this;
    }

    long use_count() {
        if (ptr)
            return cnt -> getcount();
        return 0;
    }
};

/**
 * 手动实现 unique_ptr
 */
template <typename T>
class Uptr {
public:
    //构造函数
    Uptr(T* pIn = nullptr)
        :ptr(pIn)
    {}
    //析构函数
    ~Uptr() {
        if (nullptr != ptr)
            del();
    }
    //拷贝构造函数
    Uptr(const Uptr&) = delete;
    //拷贝赋值运算符
    Uptr& operator=(const Uptr&) = delete;
    //移动构造函数
    Uptr(Uptr &&pIn)
        : ptr(pIn.release()) {
    }
    //移动赋值运算符
    Uptr& operator=(Uptr&& uIn) {
        if (this != &uIn) {
            del();
            ptr = uIn.release();
        }
        return *this;
    }

    //reset
    void reset(T* pIn = nullptr) {
        del();
        ptr = pIn;
    }
    //release
    T* release() {
        T* ret = ptr;
        ptr = nullptr;
        return ret;
    }
    //get
    T* get() {
        return ptr;
    }
    //swap
    void swap(Uptr& uIn) {
        swap(*this, uIn);
    }
    //*
    T& operator*() {
        return *ptr;
    }
    //->
    T* operator->() {
        return ptr;
    }
private:
    T* ptr;
    //析构调用
    void del() {
        delete ptr;
        ptr = nullptr;
    }
};

/**
 * LRU
 */
class LRUCache {
public:
    vector<int> vec;
    queue<int> q;
    unordered_map<int,int> mp;
    int cnt = 0;
    int cap = 0;
    LRUCache(int c) {
        cap = c;
        vec.resize(1e4+2,-1);
    }

    int get(int k) {
        if (vec[k] == -1) return -1;
        q.emplace(k);
        mp[k]++;
        return vec[k];
    }

    void put(int k, int v) {
        if (vec[k] == -1) {
            if (cnt == cap) {
                q.emplace(k);
                vec[k] = v;
                mp[k]++;
                while(!q.empty()) {
                    auto q1 = q.front();
                    q.pop();
                    mp[q1]--;
                    if (!mp[q1]) {
                        vec[q1] = -1;
                        return;
                    }
                }
            } else {
                q.emplace(k);
                vec[k] = v;
                mp[k]++;
                ++cnt;
            }
        } else {
            q.emplace(k);
            vec[k] = v;
            mp[k]++;
        }
    }
};

class Node {
public:
    int key, value;
    Node *prev, *next;

    Node(int k = 0, int v = 0) : key(k), value(v) {}
};

class LRUCache_1 {
private:
    int capacity;
    Node *dummy; // 哨兵节点
    unordered_map<int, Node*> key_to_node;

    // 删除一个节点（抽出一本书）
    void remove(Node *x) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

    // 在链表头添加一个节点（把一本书放在最上面）
    void push_front(Node *x) {
        x->prev = dummy;
        x->next = dummy->next;
        x->prev->next = x;
        x->next->prev = x;
    }

    Node *get_node(int key) {
        auto it = key_to_node.find(key);
        if (it == key_to_node.end()) // 没有这本书
            return nullptr;
        auto node = it->second; // 有这本书
        remove(node); // 把这本书抽出来
        push_front(node); // 放在最上面
        return node;
    }

public:
    LRUCache_1(int capacity) : capacity(capacity), dummy(new Node()) {
        dummy->prev = dummy;
        dummy->next = dummy;
    }

    int get(int key) {
        auto node = get_node(key);
        return node ? node->value : -1;
    }

    void put(int key, int value) {
        auto node = get_node(key);
        if (node) { // 有这本书
            node->value = value; // 更新 value
            return;
        }
        key_to_node[key] = node = new Node(key, value); // 新书
        push_front(node); // 放在最上面
        if (key_to_node.size() > capacity) { // 书太多了
            auto back_node = dummy->prev;
            key_to_node.erase(back_node->key);
            remove(back_node); // 去掉最后一本书
            delete back_node; // 释放内存
        }
    }
};

vector<vector<int>> threeSum(vector<int>& a) {
    int n = a.size();
    sort(a.begin(), a.end());
    vector<vector<int>> ans;
    for (int i = 0; i < n-2; ++i) {
        int x = a[i];
        if (i && a[i-1] == a[i]) continue;
        if (x+a[n-1]+a[n-2] < 0) continue;
        if (x+a[i+1]+a[i+2] > 0) break;
        int j = i+1, k = n-1;
        while (j < k) {
            if (x+a[j]+a[k] > 0) --k;
            else if (x+a[j]+a[k] < 0) ++j;
            else {
                ans.emplace_back(vector<int>{x,a[j],a[k]});
                ++j;
                --k;
                for(;j< k; ++j) {
                    if (a[j] != a[j-1]) break;
                }
                for(;j< k; --k) {
                    if (a[k] != a[k+1]) break;
                }
            }
        }
    }
    return ans;
}

int lengthOfLongestSubstring(string s) {
    int n = s.size(), ans = 0;
    unordered_map<char,int> mp;
    for (int l = 0, r= 0; r < n; ++r) {
        ++mp[s[r]];
        while(mp[s[r]] >= 2) {
            --mp[s[l]];
            ++l;
        }
        ans = max(r-l+1,ans);
    }
    return ans;
}

int maxSubArray(vector<int>& a) {
    int ans = a[0], n = a.size();
    vector<int> f(n);
    f[0] = a[0];
    int l = 0, r = 0;
    vector<pii> ind(n);
    for (int i = 1; i < n; ++i) {
        if (f[i-1] > 0) {
            ind[i].first = ind[i-1].first;
            ind[i].second = i;
            f[i] = f[i-1]+a[i];
        } else {
            ind[i].first = i;
            ind[i].second = i;
            f[i] = a[i];
        }
        if (f[i] > ans) {
            ans = f[i];
            l = ind[i].first;
            r = ind[i].second;
        }
    }
    vector<int> res; // 如果求返回子数组
    for (int i = l; i <=r; ++i) {
        res.emplace_back(a[i]);
    }
    return ans;
}

int Paritition(vector<int>& A, int low, int high) {
    int pivot = A[low];
    while (low < high) {
        while (low < high && pivot <= A[high]) --high;
        A[low] = A[high];
        while (low < high && A[low] <= pivot) ++low;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}
void QuickSort(vector<int>& A, int low, int high) {
    if (low < high) {
        int pivot = Paritition(A, low, high);
        QuickSort(A, low, pivot - 1);
        QuickSort(A, pivot + 1, high);
    }
}

void QuickSort(vector<int>& A, int len) {
    QuickSort(A, 0, len - 1);
}


/**
 * 三路快速排序
 * https://oi-wiki.org/basic/quick-sort/
 * @tparam T
 * @param arr
 * @param len
 */
// 模板的 T 参数表示元素的类型，此类型需要定义小于（<）运算
template <typename T>
// arr 为需要被排序的数组，len 为数组长度
void quick_sort(T arr[], const int len) {
    if (len <= 1) return;
    // 随机选择基准（pivot）
    const T pivot = arr[rand() % len];
    // i：当前操作的元素下标
    // arr[0, j)：存储小于 pivot 的元素
    // arr[k, len)：存储大于 pivot 的元素
    int i = 0, j = 0, k = len;
    // 完成一趟三路快排，将序列分为：
    // 小于 pivot 的元素 | 等于 pivot 的元素 | 大于 pivot 的元素
    while (i < k) {
        if (arr[i] < pivot)
            swap(arr[i++], arr[j++]);
        else if (pivot < arr[i])
            swap(arr[i], arr[--k]);
        else
            i++;
    }
    // 递归完成对于两个子序列的快速排序
    quick_sort(arr, j);
    quick_sort(arr + k, len - k);
}

vector<int> sortArray(vector<int>& a) {
    int n = a.size();
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = a[i];
    }
    quick_sort<int>(arr, n);
    for (int i = 0; i < n; ++i) {
        a[i] = arr[i];
    }
    return a;
}

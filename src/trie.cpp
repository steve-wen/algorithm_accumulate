#include <bits/stdc++.h>

using namespace std;

/**
* 前缀树/字典树/单词查找树
*/

/**
 * 实现 trie no.208
 * 字典树, 小写字母朴素用法
 */

class Node {
public:
    array<Node*, 26> children{};
};

class Trie {
public:
    unordered_map<string,int> mp;
    Node *root = new Node();
    Trie() {

    }

    void insert(string w) {
        ++mp[w];
        Node *cur = root;
        for (auto c : w) {
            if (cur->children[c-'a'] == nullptr) {
                cur->children[c-'a'] = new Node();
            }
            cur = cur->children[c-'a'];
        }
    }

    bool search(string w) {
        return mp[w];
    }

    bool startsWith(string p) {
        Node *cur = root;
        for (auto c : p) {
            if (cur->children[c-'a'] == nullptr) {
                return false;
            }
            cur = cur->children[c-'a'];
        }
        return true;
    }
};

/**
 * 前缀分数和
 * lc.no.2416
 */
class Node1 {
public:
    array<Node1*, 26> children{};
    int cnt = 0;
};

class Trie1 {
public:
    Node1 *root = new Node1();

    void insert(string w) {
        Node1 *cur = root;
        for (auto c : w) {
            if (cur->children[c-'a'] == nullptr) {
                cur->children[c-'a'] = new Node1();
            }
            cur = cur->children[c-'a'];
            cur->cnt++;
        }
    }

    int query(string p) { // dfs
        Node1 *cur = root;
        int tmp = 0;
        for (auto c : p) {
            if (cur->children[c-'a'] == nullptr) {
                return tmp;
            }
            cur = cur->children[c-'a'];
            tmp += cur->cnt;
        }
        return tmp;
    }
};

class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& w) {
        Trie1 t{};
        vector<int> ans;
        for (auto& s : w) {
            t.insert(s);
        }
        for (auto& s : w) {
            ans.emplace_back(t.query(s));
        }
        return ans;
    }
};

/**
 * 字典树 + z_function
 * https://leetcode.cn/problems/count-prefix-and-suffix-pairs-ii/description/
 */

vector<int> z_function_1(string s) {
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        } else {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

class Node_1 {
public:
    array<Node_1*, 26> children{};
    int cnt = 0;
};

class Trie_1 {
public:
    Node_1 *root = new Node_1();

    void insert(string w) {
        auto z = z_function_1(w);
        int n = w.size();
        z[0] = n;
        Node_1 *cur = root;
        for (int i = 0; i < n; ++i) {
            auto c = w[i];
            if (cur->children[c-'a'] == nullptr) {
                cur->children[c-'a'] = new Node_1();
            }
            cur = cur->children[c-'a'];
            if (z[n-i-1] == i+1) { // 此处注意 ？
                cur->cnt++;
            }
        }
    }

    int query(string p) { // dfs
        Node_1 *cur = root;
        int tmp = 0;
        for (int i = 0; i < p.size(); ++i) {
            auto c = p[i];
            if (cur->children[c-'a'] == nullptr) {
                return tmp;
            }
            cur = cur->children[c-'a'];
            if (i == p.size()-1) {
                return cur->cnt;
            }
        }
        return tmp;
    }
};

long long countPrefixSuffixPairs(vector<string> &w) {
    Trie_1 t{};
    long long ans = 0;
    int n = w.size();
    for (int i = n - 1; i >= 0; --i) {
        ans += (long long) t.query(w[i]);
        t.insert(w[i]);
    }
    return ans;
}


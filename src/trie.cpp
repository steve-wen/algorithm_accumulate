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

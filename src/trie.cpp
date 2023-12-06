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


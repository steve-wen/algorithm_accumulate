#include <bits/stdc++.h>

using namespace std;

/**
* 0-1 trie
*/

/**
 * 0-1 Trie ，0-1 字典树
 * no.2935
 */
class Node {
public:
    array<Node*, 2> children{};
    int cnt = 0; // 子树大小
};

class Trie {
    static const int HIGH_BIT = 19;
public:
    Node *root = new Node();

    // 添加 val, insert 时，建树
    void insert(int val) {
        Node *cur = root;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (cur->children[bit] == nullptr) {
                cur->children[bit] = new Node();
            }
            cur = cur->children[bit];
            cur->cnt++; // 维护子树大小
        }
    }

    // 删除 val，但不删除节点
    // 要求 val 必须在 trie 中
    void remove(int val) {
        Node *cur = root;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            cur = cur->children[bit];
            cur->cnt--; // 维护子树大小
        }
    }

    // 返回 val 与 trie 中一个元素的最大异或和
    // 要求 trie 不能为空
    int max_xor(int val) {
        Node *cur = root;
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            // 如果 cur.children[bit^1].cnt == 0，视作空节点
            if (cur->children[bit ^ 1] && cur->children[bit ^ 1]->cnt) {
                ans |= 1 << i;
                cur = cur->children[bit ^ 1];
            } else { // 必然存在其中一边节点不为空
                cur = cur->children[bit];
            }
        }
        return ans;
    }
};

class Solution {
public:
    int maximumStrongPairXor(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        Trie t{};
        int ans = 0, left = 0;
        for (int y: nums) {
            t.insert(y);
            while (nums[left] * 2 < y) {
                t.remove(nums[left++]);
            }
            ans = max(ans, t.max_xor(y));
        }
        return ans;
    }
};


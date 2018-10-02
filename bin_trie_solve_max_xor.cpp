#include <iostream>
#include <stdio.h>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <queue>
//详情见算法竞赛进阶指南
using namespace  std;
typedef long long ll;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 10;
const int MAXE = 2 * MAXN;
const int NIL = -1;
const ll INF = 0x3f3f3f3f;


struct TNode {
    int c[2];
    int size;

};

struct Trie {
    int cnt, root;
    TNode buf[MAXN];
    enum {height = 31};
    Trie() {
        cnt = 0;
        root = newNode();
    }



    void init() {
        cnt = 0;
        root = newNode();
    }
    int newNode() {
        buf[cnt].c[0] = buf[cnt].c[1] = NIL;
        buf[cnt].size = 0;
        return cnt++;
    }
    void ins(int x) {
        int p = root;
        ++buf[p].size;
        for (int i = height; i >= 0; --i) {
            int b = (x >> i) & 1;
            if (buf[p].c[b] == NIL)
                buf[p].c[b] = newNode();
            p = buf[p].c[b];
            ++buf[p].size;
        }
    }
    bool exist(int x) {
        int p = root;
        for (int i = height; i >= 0; --i) {
            int b = (x >> i) & 1;
            if (buf[p].c[b] == NIL)
                return false;
            p = buf[p].c[b];
        }
        return true;
    }
    void del(int x) {
        int p = root;
        --buf[p].size;
        for (int i = height; i >= 0; --i) {
            int b = (x >> i) & 1;
            p = buf[p].c[b];
            --buf[p].size;
        }
    }
    int maxXor(int x) {
        int p = root;

        for (int i = height; i >= 0; --i) {
            int b = (x >> i) & 1;

            if (b) {
                if (buf[p].c[0] && buf[buf[p].c[0]].size)
                    p = buf[p].c[0];
                else
                    p = buf[p].c[1], x ^= (1 << i);
            } else {
                if (buf[p].c[1] && buf[buf[p].c[1]].size)
                    p = buf[p].c[1], x ^= (1 << i);
                else
                    p = buf[p].c[0];
            }

        }
        return x;
    }
};


int a[1005];
Trie trie;
int main()
{

    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        trie.init();
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            trie.ins(a[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            trie.del(a[i]);
            for (int j = i + 1; j < n; ++j) {
                trie.del(a[j]);
                ans = max(ans, trie.maxXor(a[i] + a[j]));
                trie.ins(a[j]);
            }
            trie.ins(a[i]);
        }
        printf("%d\n", ans);

    }
    return 0;
}



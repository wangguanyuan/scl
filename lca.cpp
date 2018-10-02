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
const int MAXN = 200000 + 10;
const int MAXE = 2 * MAXN;
const int NIL = -1;
const ll INF = 0x3f3f3f3f;

struct Node {
    int to, w, next;
    void set(int tt, int ww, int nn) {
        to = tt;
        w = ww;
        next = nn;
    }
} edge[MAXE];

int head[MAXN], CNT;

void init() {
    CNT = 0;
    memset(head, NIL, sizeof(int) * MAXN);
}

void add(int u, int v, int w) {
    edge[CNT].set(v, w, head[u]);
    head[u] = CNT++;
}

int d[MAXN];    //深度
int dist[MAXN]; //距离
int f[MAXN][20];    //2k祖先
int maxHeight;
void bfs()      //求以1为根的节点深度
{
    memset(d, 0, sizeof(d));
    d[1] = 1;
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; ~i; i = edge[i].next) {
            int v = edge[i].to;
            int w = edge[i].w;
            if (d[v])
                continue;
            d[v] = d[u] + 1;
            dist[v] = dist[u] + w;
            f[v][0] = u;    //直接祖先
            for (int j = 1; j <= maxHeight; ++j) {
                f[v][j] = f[f[v][j - 1]][j - 1];
            }
            q.push(v);
        }
    }
}

int lca(int x, int y) {
    if (d[x] > d[y])
        swap(x, y);
    for (int i = maxHeight; i >= 0; --i) {
        if (d[f[y][i]] >= d[x])
            y = f[y][i];
    }
    if (x == y)
        return x;
    for (int i = maxHeight; i >= 0; --i) {
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}


int main()
{
    int T, n, m, u, v, w;

    init();
    scanf("%d", &n);
    maxHeight = (int)(log(n) / log(2)) + 1;
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &u, &v);
        add(u, v, 1);
        add(v, u, 1);
    }
    bfs();
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + i; j <= n; j += i) {
            ans += dist[i] + dist[j] - 2 * dist[lca(i, j)] + 1;
            //printf("%d->%d:%d, ", i, j, dist[i] + dist[j] - 2 * dist[lca(i, j)] + 1);
        }
    }

    printf("%lld\n", ans);

    return 0;
}



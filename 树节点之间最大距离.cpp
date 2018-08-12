
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


int dp[MAXN][2];    //dp[i][0]表示i到它的叶子的最长距离，dp[i][1]表示i到它的叶子的次长距离
int maxid[MAXN];    //maxid[i]的值为i的子树中最长距离经过的孩子

void dfs1(int u, int fa) {
    dp[u][0] = 0;
    dp[u][1] = NIL;
    maxid[u] = u;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        int w = edge[i].w;
        if (v == fa)
            continue;
        dfs1(v, u);
        if (dp[v][0] + w > dp[u][0]) {  //子节点到叶子结点的距离加上子节点边的长度
            dp[u][1] = dp[u][0];
            dp[u][0] = dp[v][0] + w;
            maxid[u] = v;
        } else if (dp[v][0] + w > dp[u][1]) {
            dp[u][1] = dp[v][0] + w;    //次短
        }
    }
}

int dist[MAXN];
void dfs2(int u, int fa, int len) { //len为不在u节点的子树里的节点到u的最远距离
    dist[u] = max(dp[u][0], len);
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        int w = edge[i].w;
        if (v == fa)
            continue;
        if (v == maxid[u])
            dfs2(v, u, max(dp[u][1], len) + w);
        else
            dfs2(v, u, dist[u] + w);
    }
}
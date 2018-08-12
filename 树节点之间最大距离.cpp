
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


int dp[MAXN][2];    //dp[i][0]��ʾi������Ҷ�ӵ�����룬dp[i][1]��ʾi������Ҷ�ӵĴγ�����
int maxid[MAXN];    //maxid[i]��ֵΪi������������뾭���ĺ���

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
        if (dp[v][0] + w > dp[u][0]) {  //�ӽڵ㵽Ҷ�ӽ��ľ�������ӽڵ�ߵĳ���
            dp[u][1] = dp[u][0];
            dp[u][0] = dp[v][0] + w;
            maxid[u] = v;
        } else if (dp[v][0] + w > dp[u][1]) {
            dp[u][1] = dp[v][0] + w;    //�ζ�
        }
    }
}

int dist[MAXN];
void dfs2(int u, int fa, int len) { //lenΪ����u�ڵ��������Ľڵ㵽u����Զ����
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
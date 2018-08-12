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

int dist[MAXN];
bool inque[MAXN];
void spfa(int s) {
    queue<int> q;
    memset(dist, 0x3f, sizeof(int) * MAXN);
    dist[s] = 0;
    inque[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inque[u] = false;
        for (int i = head[u]; ~i; i = edge[i].next) {
            int v = edge[i].to;
            int w = edge[i].w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!inque[v]) {
                    inque[v] = true;
                    q.push(v);
                }
            }
        }
    }
}
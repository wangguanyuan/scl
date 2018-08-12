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

int a[MAXN], b[MAXN];

int LIS(int n) {
    int len = 0;
    b[len++] = a[0];
    for (int i = 1; i < n; ++i) {
        if (b[len - 1] < a[i])
            b[len++] = a[i];
        else
            *lower_bound(b, b + len, a[i]) = a[i];
    }
    return len;
}

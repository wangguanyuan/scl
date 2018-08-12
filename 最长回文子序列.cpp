两种写法 第一种是根据递推顺序来 第二种是枚举长度

int dp[MAXN][MAXN];
int LPS(int a[], int len) {
    for (int i = len - 1; i >= 0; --i) {
        dp[i][i] = 1;

        for (int j = i + 1; j < len; ++j) {
            dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            if (a[i] == a[j])
                dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 2);
        }
    }
}

int LPS(int a[], int n) {
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= n; ++i)
        dp[i][i] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            if (a[i] == a[j])
                dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 2);
        }
    }
    return dp[0][n - 1];
}
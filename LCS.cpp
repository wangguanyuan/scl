int flag[MAXN][MAXN];
int dp[MAXN][MAXN];
int LCS(char a[], char b[]) {
    int lena = strlen(a);
    int lenb = strlen(b);
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < lena; ++i)
        flag[i][0] = 1;
    for (int j = 0; j < lenb; ++j)
        flag[0][j] = -1;
    for (int i = 1; i <= lena; ++i) {
        for (int j = 1; j <= lenb; ++j) {
            if (a[i - 1] == b[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
                flag[i][j] = 0;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                flag[i][j] = 1;
            } else {
                dp[i][j] = dp[i][j - 1];
                flag[i][j] = -1;
            }
        }
    }
    return dp[lena][lenb];
}

void print(char a[], char b[], int i, int j) {
    if (i < 1 && j < 1)
        return;
    if (flag[i][j] == 0) {
        print(a, b, i - 1, j - 1);
        printf("%c", a[i - 1]);
        return;
    }
    if (flag[i][j] == 1) {
        print(a, b, i - 1, j);
        printf("%c", a[i - 1]);
        return;
    }
    print(a, b, i, j - 1);
    printf("%c", b[j - 1]);
}
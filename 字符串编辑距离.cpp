#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <cstdio>
#include <cmath>
#include <string>
#include <sstream>
#include <stack>
#define MAXN 105
#define INF 0x3f3f3f3f
#define NIL -1
using namespace std;
typedef long long ll;
#define DEL 1
#define REP 2
#define INS 3

char a[MAXN], b[MAXN];
int lena, lenb;
int dp[MAXN][MAXN], flag[MAXN][MAXN];
bool vis[MAXN][MAXN];
int editDist(int i, int j) {
    if (vis[i][j])
        return dp[i][j];
    vis[i][j] = true;
    if (j == lenb) {
        int ret = 0;
        int k = i;          //这里不能直接改变i的值 下面的j也一样
        while (k < lena) {  //删除a串中多余的字符
            flag[k][j] = DEL;
            ++ret;
            ++k;
        }
        return dp[i][j] = ret;
    }
    if (i == lena) {        //在a串尾部插入字符
        int ret = 0;
        int k = j;
        while (k < lenb) {
            flag[i][k] = INS;
            ++ret;
            ++k;
        }
        return dp[i][j] = ret;
    }
    if (a[i] == b[j])
        return dp[i][j] = editDist(i + 1, j + 1);
    int del = editDist(i + 1, j);
    int rep = editDist(i + 1, j + 1);
    int ins = editDist(i, j + 1);
    int mi = min(del, min(rep, ins));
    if (mi == del)
        flag[i][j] = DEL;
    else if (mi == rep)
        flag[i][j] = REP;
    else
        flag[i][j] = INS;
    return dp[i][j] = mi + 1;
}

void out(int i, int j, int ord) {
    if (i == lena && j == lenb)
        return;
    if (a[i] == b[j])
        out(i + 1, j + 1, ord);
    else if (flag[i][j] == DEL) {
        printf("%d Delete %d\n", ord, j + 1);
        out(i + 1, j, ord + 1);
    } else if (flag[i][j] == REP) {
        printf("%d Replace %d,%c\n", ord, j + 1, b[j]);
        out(i + 1, j + 1, ord + 1);
    } else {
        printf("%d Insert %d,%c\n", ord, j + 1, b[j]);
        out(i, j + 1, ord + 1);
    }
}

int main() {
    while (scanf("%s %s", a, b) != EOF) {
        memset(vis, 0, sizeof(vis));
        lena = strlen(a);
        lenb = strlen(b);
        printf("%d\n", editDist(0, 0));
        out(0, 0, 1);
    }

    return 0;
}

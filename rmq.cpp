
class RMQ {
public:
    int log2[MAXN];
    int dp1[MAXN][20];  //�������ֵ dp[i][j] ��1��ʼ����Ϊ2^j������
    int dp2[MAXN][20];  //������Сֵ
    RMQ() {
        log2[0] = NIL;
        for (int i = 1; i < MAXN; ++i) {
            log2[i] = (i & (i - 1)) ? log2[i - 1] : log2[i - 1] + 1;
        }
    }
    void init(int a[], int n) {     //�±��1��ʼ
        for (int i = 1; i <= n; ++i) {
            dp1[i][0] = dp2[i][0] = a[i];
        }
        for (int j = 1; j <= log2[n]; ++j) {
            int len = (1 << j);
            int half = 1 << (j - 1);
            for (int i = 1; i + len - 1 <= n; ++i) {
                dp1[i][j] = max(dp1[i][j - 1], dp1[i + half][j - 1]);
                dp2[i][j] = min(dp2[i][j - 1], dp2[i + half][j - 1]);
            }
        }
    }
    int rmq(int l, int r) {
        int k = log2[r - l + 1];
        return max(dp1[l][k], dp1[r - (1 << k) + 1][k]) - min(dp2[l][k], dp2[r - (1 << k) + 1][k]);	//���ﷵ�ص�����Сֵ�����ֵ�Ĳ�ֵ
    }
};
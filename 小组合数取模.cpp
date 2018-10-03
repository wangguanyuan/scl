ll f[MAXN];
ll qpow(ll a, ll b, ll c) {
    ll ans = 1;
    a = a % c;
    while (b>0) {
        if (b % 2 == 1)
            ans = (ans * a) % c;
        b = b / 2;
        a = (a * a) % c;
    }
    return ans;
}
void init(){//先打出阶乘，节省时间
    f[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        f[i] = f[i - 1] * i%MOD;
    }
}
ll C(ll n, ll m)
{
    return f[n] * qpow(f[m] * f[n - m] % MOD, MOD - 2, MOD) % MOD;
}

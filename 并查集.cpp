int p[MAXN];
inline void init(int n)
{
	for (int i = 0; i <= n; ++i)
		p[i] = i;
}
int find_p(int x)
{
	if (x == p[x])
		return x;
	
	int root = find_p(p[x]);


	return p[x] = root;
}

inline void merge(int x, int y)
{
	int px = find_p(x);
	int py = find_p(y);
	if (px == py)
		return;

	p[px] = py;
}

#include <bits/stdc++.h>

using namespace std;

int MOD;

struct matrix{
	int a, b, c, d;
	matrix() {}
	matrix(int a1, int b1, int c1, int d1) {
		a = a1;
		b = b1;
		c = c1;
		d = d1;
	}
	matrix operator *(const matrix &b) {
		matrix a = *this;
		matrix result = matrix(a.a * b.a + a.b * b.c, a.a * b.b + a.b * b.d,
		 a.c * b.a + a.d * b.c, a.c * b.b + a.d * b.d);
		result.a %= MOD;
		result.b %= MOD;
		result.c %= MOD;
		result.d %= MOD;
		return result;
	}
};

const int N = 2e5 + 10;

matrix t[4 * N];
matrix a[N];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v] = a[tl];
	} else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		t[v] = t[2 * v] * t[2 * v + 1];
	}
}

matrix neutral = matrix(1, 0, 0, 1);

matrix get_prod(int v, int tl, int tr, int l, int r) {
	if (l > r) {
		return neutral;
	}
	if (tl == l && tr == r) {
		return t[v];
	} else {
		int tm = (tl + tr) / 2;
		matrix a = get_prod(2 * v, tl, tm, l, min(r, tm));
		matrix b = get_prod(2 * v + 1, tm + 1, tr, max(tm + 1, l), r);
		return a * b;
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif   // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> MOD >> n >> m;
	for (int i = 0; i < n; i++) {
		int m1, m2, m3, m4;
		cin >> m1 >> m2 >> m3 >> m4;
		a[i] = matrix(m1, m2, m3, m4);
	}
	build(1, 0, n - 1);
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		matrix res = get_prod(1, 0, n - 1, l, r);
		cout << res.a << ' ' << res.b << '\n' << res.c << ' ' << res.d << "\n\n";
	}
	return 0;
}

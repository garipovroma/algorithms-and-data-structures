#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 5e5 + 229;

long long t[4 * N];
int a[N];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v] = a[tl];
	} else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		t[v] = t[2 * v] + t[2 * v + 1];
	}
}

void modify(int v, int tl, int tr, int x, int y) {
	if (tl == tr) {
		a[tl] = y;
		t[v] = y;
	} else {
		int tm = (tl + tr) / 2;
		if (x <= tm)
			modify(2 * v, tl, tm, x, y);
		else
			modify(2 * v + 1, tm + 1, tr, x, y);
		t[v] = t[2 * v] + t[2 * v + 1];
	}
}

long long get_sum(int v, int tl, int tr, int l, int r) {
	if (l > r) return 0;
	if (tl == l && tr == r) {
		return t[v];
	} else {
		int tm = (tl + tr) / 2;
		ll s1 = get_sum(2 * v, tl, tm, l, min(tm, r));
		ll s2 = get_sum(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
		return s1 + s2;
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	build(1, 0, n - 1);
	string s;
	while (cin >> s) {
		int a, b;
		cin >> a >> b;
		if (s == "sum") {
			cout << get_sum(1, 0, n - 1, a - 1, b - 1) << "\n";
		} else {
			modify(1, 0, n - 1, a - 1, b);
		}
	}
	return 0;
}
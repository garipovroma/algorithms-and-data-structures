#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 100000;

const ll INF = 1000002000000000000ll;

ll a[N];
ll p_set[4 * N];
ll p_plus[4 * N];
ll t[4 * N];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v] = a[tl];
	} else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		t[v] = min(t[2 * v], t[2 * v + 1]);
	}
}

void push(int v) {
	if (p_set[v] != -INF) {
		t[2 * v] = p_set[v];
		t[2 * v + 1] = p_set[v];
		p_set[2 * v] = p_set[v];
		p_set[2 * v + 1] = p_set[v];
		p_set[v] = -INF;
		p_plus[2 * v] = 0;
		p_plus[2 * v + 1] = 0;
	}
	t[2 * v] += p_plus[v];
	t[2 * v + 1] += p_plus[v];
	p_plus[2 * v] += p_plus[v];
	p_plus[2 * v + 1] += p_plus[v];
	p_plus[v] = 0;
}

void add_on_seg(int v, int tl, int tr, int l, int r, ll dx) {
	if (l > r) return;
	if (tl == l && tr == r) {
		t[v] += dx;
		if (p_set[v] != -INF) {
			p_set[v] += dx;
		} else {
			p_plus[v] += dx;
		}
	} else {
		push(v);
		int tm = (tl + tr) / 2;
		add_on_seg(2 * v, tl, tm, l, min(r, tm), dx);
		add_on_seg(2 * v + 1, tm + 1, tr, max(tm + 1, l), r, dx);
		t[v] = min(t[2 * v], t[2 * v + 1]);
	}
}

void set_on_seg(int v, int tl, int tr, int l, int r, ll dx) {
	if (l > r) return;
	if (tl == l && tr == r) {
		t[v] = dx;
		p_set[v] = dx;
		p_plus[v] = 0;
	} else {
		push(v);
		int tm = (tl + tr) / 2;
		set_on_seg(2 * v, tl, tm, l, min(r, tm), dx);
		set_on_seg(2 * v + 1, tm + 1, tr, max(tm + 1, l), r, dx);
		t[v] = min(t[2 * v], t[2 * v + 1]);
	}
}

ll get_min(int v, int tl, int tr, int l, int r) {
	if (l > r) return INF;
	if (tl == l && tr == r) {
		return t[v];
	} else {
		push(v);
		int tm = (tl + tr) / 2;
		ll s1 = get_min(2 * v, tl, tm, l, min(tm, r));
		ll s2 = get_min(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
		return min(s1, s2);
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for (int i = 0; i < 4 * N; i++) {
		p_set[i] = -INF;
	}
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	build(1, 0, n - 1);
	string s;
	while (cin >> s) {
		if (s == "min") {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			ll cur = get_min(1, 0, n - 1, l, r);
			cout << cur << "\n";
		} else if (s == "add") {
			int l, r;
			ll x;
			cin >> l >> r >> x;
			l--;
			r--;
			add_on_seg(1, 0, n - 1, l, r, x);
		} else {
			int l, r;
			ll x;
			cin >> l >> r >> x;
			l--;
			r--;
			set_on_seg(1, 0, n - 1, l, r, x);
		}
	}
	return 0;
}


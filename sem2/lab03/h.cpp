#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5 + 10;

int leftest[4 * N];
int a[N];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		leftest[v] = tl;
		a[tl] = 0;
	} else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		leftest[v] = min(leftest[2 * v], leftest[2 * v + 1]);
	}
}

int get(int v, int tl, int tr, int l, int r) {
	if (l > r) return 1e9;
	if (tl == l && tr == r) {
		return leftest[v];
	} else {
		int tm = (tl + tr) / 2;
		int x = get(2 * v, tl, tm, l, min(tm, r));
		int y = get(2 * v + 1, tm + 1, tr, max(tm + 1, l), r);
		return min(x, y);
	}
}

void setv(int v, int tl, int tr, int x, int y) {
	if (tl == tr) {
		a[x] = y;
		if (a[x] == 0) {
			leftest[v] = x;
		} else {
			leftest[v] = 1e9;
		}
	} else {
		int tm = (tl + tr) / 2;
		if (x <= tm) {
			setv(2 * v, tl, tm, x, y);
		} else {
			setv(2 * v + 1, tm + 1, tr, x, y);
		}
		leftest[v] = min(leftest[2 * v], leftest[2 * v + 1]);
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	build(1, 0, n - 1);
	string s;
	int pos;
	for (int i = 0; i < m; i++) {
		cin >> s >> pos;
		pos--;
		if (s == "enter") {
			if (a[pos] == 0) {
				setv(1, 0, n - 1, pos, 1);
				cout << pos + 1 << "\n";
			} else {
				int kek = get(1, 0, n - 1, pos + 1, n - 1);
				if (kek == 1e9) {
					int lol = get(1, 0, n - 1, 0, pos - 1);
					setv(1, 0, n - 1, lol, 1);
					cout << lol + 1 << "\n";
				} else {
					setv(1, 0, n - 1, kek, 1);
					cout << kek + 1 << "\n";
				}
			}
		} else {
			setv(1, 0, n - 1, pos, 0);
		}
	}
	return 0;
}

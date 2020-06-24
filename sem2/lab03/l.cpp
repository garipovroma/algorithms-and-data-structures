#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

const int N = (1 << 17);

vector <vector<int>> t;
int a[N];
vector <int> buf;

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v] = vector<int>(1, a[tl]);
	} else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm  + 1, tr);
		buf.clear();
		buf.resize(len(t[2 * v]) + len(t[2 * v + 1]));
		merge(t[2 * v].begin(), t[2 * v].end(), t[2 * v + 1].begin(), t[2 * v + 1].end(), buf.begin());
		t[v] = buf;
	}
}

int query(int v, int tl, int tr, int l, int r, int x, int y) {
	if (l > r) {
		return 0;
	}
	if (tl == l && tr == r) {
		int le = lower_bound(all(t[v]), x) - t[v].begin();
		int ri = upper_bound(all(t[v]), y) - t[v].begin();
		return (ri - le);
	} else {
		int tm = (tl + tr) / 2;
		int x1 = query(2 * v, tl, tm, l, min(tm, r), x, y);
		int x2 = query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, x, y);
		return (x1 + x2);
	}
}

unsigned int a_, b_;
unsigned int cur_ = 0;

unsigned int nextRand17() {
	cur_ = cur_ * a_ + b_;
	return cur_ >> 15;
}

unsigned int nextRand24() {
	cur_ = cur_ * a_ + b_;
	return cur_ >> 8;
}

void gen() {
	for (int i = 0; i < (1 << 17); i++) {
		a[i] = nextRand24();
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> q >> a_ >> b_;
	t.resize(4 * N);
	gen();
	build(1, 0, N - 1);
	unsigned int sum = 0;
	for (int i = 0; i < q; i++) {
		int l = nextRand17();
		int r = nextRand17();
		if (l > r) {
			swap(l, r);
		}
		int x = nextRand24();
		int y = nextRand24();
		if (x > y) {
			swap(x, y);
		}
		unsigned int cur = query(1, 0, N - 1, l, r, x, y);
		b_ += cur;
		sum += cur;
	}
	cout << sum;
	return 0;
}

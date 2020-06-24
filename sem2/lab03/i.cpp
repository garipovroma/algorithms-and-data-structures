#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

const int MAX_VAL = 1e6 + 10;

ll cnt[MAX_VAL];

long long cur_sum = 0;

void add(ll x) {
	if (cnt[x] == 0) {
		cur_sum += x;
		cnt[x]++;
	} else {
		cnt[x] += 2;
		cur_sum += cnt[x] * x;
	}
}

void del(ll x) {
	if (cnt[x] == 1) {
		cur_sum -= x;
		cnt[x] -= 1;
	} else {
		cur_sum -= cnt[x] * x;
		cnt[x] -= 2;
	}
}

struct seg {
	int l, r, id;
	seg() {}
	seg(int a, int b, int c) {
		l = a;
		r = b;
		id = c;
	}
};

const int K = 448;

bool cmp(const seg &a, const seg &b) {
	return (a.l / K == b.l / K ? a.r < b.r : a.l / K < b.l / K);
}

const int N = 2e5 + 10;

ll a[N];
seg q[N];
ll query[N];

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif   // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		q[i] = seg(l - 1, r - 1, i);
	}
	sort(q, q + m, cmp);
	int L = q[0].l;
	int R = q[0].r;
	for (int i = L; i <= R; i++) {
		add(a[i]);
	}
	query[q[0].id] = cur_sum;
	for (int i = 1; i < m; i++) {
		if (q[i].l > L) {
			for (int j = L; j < q[i].l; j++) {
				del(a[j]);
			}
		} else if (q[i].l < L) {
			for (int j = L - 1; j >= q[i].l; j--) {
				add(a[j]);
			}
		}
		L = q[i].l;
		if (q[i].r > R) {
			for (int j = R + 1; j <= q[i].r; j++) {
				add(a[j]);
			}
		} else if (q[i].r < R) {
			for (int j = q[i].r + 1; j <= R; j++) {
				del(a[j]);
			}
		}
		R = q[i].r;
		query[q[i].id] = cur_sum;
	}
	for (int i = 0; i < m; i++) {
		cout << query[i] << "\n";
	}
	return 0;
}

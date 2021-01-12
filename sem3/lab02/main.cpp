#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")

#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("btr-bb-exclusive")

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int MAXN = 1e5;

struct DSU {
	int p[MAXN], sz[MAXN];
	DSU() {
		for (int i = 0; i < MAXN; i++) {
			p[i] = i;
			sz[i] = 1;
		}
	}
	int get_p(int v) {
		if (v == p[v]) {
			return v;
		} else {
			return p[v] = get_p(p[v]);
		}
	}

	bool un(int a, int b) {
		a = get_p(a);
		b = get_p(b);
		if (a == b) {
			return false;
		}
		if (sz[a] > sz[b]) {   // a < b
			swap(a, b);
		}
		sz[b] += sz[a];
		p[a] = b;
		return true;
	}
};

vector <pair<long long, pair<int, int>>> edges;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <pair<int, int>> pts;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		pts.push_back({a, b});
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			double x = pts[i].first - pts[j].first;
			double y = pts[i].second - pts[j].second;
			long long xx = (ll(x * x + y * y));
			edges.push_back({xx, {i, j}});
		}
	}
	sort(all(edges));
	double ans = 0;
	DSU d;
	int x = 0;
	for (int i = 0; i < len(edges); i++) {
		int a = edges[i].second.first;
		int b = edges[i].second.second;
		if (d.un(a, b)) {
			double kek = double(edges[i].first);
			kek = sqrt(kek);
			ans += kek;
			x++;
			if (x == n - 1) {
				break;
			}
		}
	}
	cout.precision(15);
	cout << fixed;
	cout << ans;
	return 0;
}

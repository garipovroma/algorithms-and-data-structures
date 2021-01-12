#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int MAXN = 1e3 + 1;

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

int status = -1;

int get_min_spanning_tree(int n, vector<pair<int, pair<int, int>>> edges) {
	int mx = (int) -2e9 - 228, mn = (int) 2e9 + 228;
	DSU d;
	for (int i = 0; i < len(edges); i++) {
		int a = edges[i].second.first;
		int b = edges[i].second.second;
		if (d.un(a, b)) {
			mx = max(edges[i].first, mx);
			mn = min(edges[i].first, mn);
		}
		if (d.sz[d.get_p(0)] == n) {
			break;
		}
	}
	if (status == -1) {
		status = (d.sz[d.get_p(0)] == n ? 1 : 0);
	}
	return (d.sz[d.get_p(0)] == n ? mx - mn : int(2e9 + 228));
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
	vector <pair<int, pair<int, int>>> edges;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		edges.push_back({c, {a, b}});
	}
	sort(all(edges));
	int mn = (int) 2e9 + 228;
	for (auto it = edges.begin(); it != edges.end(); it++) {
		mn = min(mn, get_min_spanning_tree(n, vector<pair<int, pair<int, int>>>(it, edges.end())));
	}
	if (status == 1 || n <= 1) {
		if (n <= 1) {
			mn = 0;
		}
		cout << "YES\n";
		cout << mn;
	} else {
		cout << "NO";
	}
	return 0;
}

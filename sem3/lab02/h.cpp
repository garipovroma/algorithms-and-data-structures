#include <bits/stdc++.h>

using namespace std;

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

vector <pair<int, pair<int, int>>> edges;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		edges.push_back({c, {a, b}});
	}
	sort(all(edges));
	long long ans = 0;
	DSU d;
	for (int i = 0; i < len(edges); i++) {
		int a = edges[i].second.first;
		int b = edges[i].second.second;
		if (d.un(a, b)) {
			ans += edges[i].first;
		}
	}
	cout << ans;
	return 0;
}

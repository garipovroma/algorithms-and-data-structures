#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 2e3 + 10;
const ll INF = 2000000000000000002;

struct edge {
	int from, to;
	ll cost;
	edge() {}
	edge(int a, int b, ll c) {
		from = a;
		to = b;
		cost = c;
	}
};

vector <pair<int, ll>> g[N];
vector <edge> edges;

bool ford_bellman(int s, int n, vector <ll> &d, vector <edge> &edges,
	unordered_set <int> &on_cycle) {
	d[s] = 0;
	for (int i = 0; i < n; i++) {
		for (auto e : edges) {
			int v = e.from;
			int u = e.to;
			ll w = e.cost;
			if (d[v] < INF && d[v] + w < d[u]) {
				d[u] = max(-INF, d[v] + w);
				if (i >= n - 1) {
					on_cycle.insert(u);
					on_cycle.insert(v);
				}
			}
		}
	}
	return (!on_cycle.empty());
}

vector <bool> used;

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i.first]) {
			dfs(i.first);
		}
	}
}

void mark_vertexes_on_negative_cycle(int n, unordered_set <int> on_cycle) {
	used.assign(n, false);
	for (auto i : on_cycle) {
		if (!used[i]) {
			dfs(i);
		}
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m, s;
	cin >> n >> m >> s;
	s--;
	for (int i = 0; i < m; i++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--;
		b--;
		g[a].push_back({b, c});
		edges.push_back(edge(a, b, c));
	}
	vector <ll> d(n, INF);
	unordered_set <int> on_cycle;
	bool negative_cycle = ford_bellman(s, n, d, edges, on_cycle);
	if (negative_cycle) {
		mark_vertexes_on_negative_cycle(n, on_cycle);
	}
	for (int i = 0; i < n; i++) {
		if (d[i] == INF) {
			cout << "*\n";
		} else if (negative_cycle && used[i]) {
			cout << "-\n";
		} else {
			cout << d[i] << "\n";
		}
	}
	return 0;
}

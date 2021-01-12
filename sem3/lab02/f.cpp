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

bool ford_bellman(int s, int n, vector <ll> &d, vector <int> &p, vector <edge> &edges,
	unordered_set <int> &on_cycle) {
	d[s] = 0;
	int last;
	for (int i = 0; i < n; i++) {
		last = -1;
		for (auto e : edges) {
			int v = e.from;
			int u = e.to;
			ll w = e.cost;
			if (d[v] < INF && d[v] + w < d[u]) {
				d[u] = max(-INF, d[v] + w);
				p[u] = v;
				if (i >= n - 1) {
					last = u;
				}
			}
		}
	}
	if (last != -1) {
		on_cycle.insert(last);
	}
	return (!on_cycle.empty());
}

void get_cycle(int s, vector <int> &p, vector <int> &way) {
	int cur = s;
	int k = 0;
	vector <bool> used(len(p), false);
	while (cur != s || k == 0) {
		if (used[cur]) {
			break;
		}
		used[cur] = true;
		k++;
		way.push_back(cur);
		cur = p[cur];
	}
	way.push_back(cur);
	reverse(all(way));
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

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ll x;
			cin >> x;
			if (x == (int)1e9) {
				continue;
			}
			edges.push_back(edge(i, j, x));
		}
	}
	vector <ll> d(n, 0);
	vector <int> p(n, -1);
	unordered_set <int> on_cycle;
	bool negative_cycle = ford_bellman(0, n, d, p, edges, on_cycle);
	if (negative_cycle) {
		vector <int> way;
		int start = *on_cycle.begin();
		for (int i = 0; i < n; i++) {
			start = p[start];
		}
		get_cycle(start, p, way);
		cout << "YES\n" << len(way) << "\n";
		for (auto i : way) {
			cout << i + 1 << ' ';
		}
	} else {
		cout << "NO\n";
	}

	return 0;
}

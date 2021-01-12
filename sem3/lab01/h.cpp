#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 2e4 + 100;

vector <int> tin;
vector <int> g[N];
vector <int> fup;

unordered_map<long long, int> edges_map;
int edges_counter = 1;

ll get_edge_hash(int v, int u) {
	ll hash = v * ((ll) (1e9 + 7)) + u;
	return hash;
}

void add_edge(int v, int u) {
	ll hash = get_edge_hash(u, v);
	edges_map[hash] = edges_counter;
	hash = get_edge_hash(v, u);
	edges_map[hash] = edges_counter++;
}

int get_edge_num(int v, int u) {
	ll hash = get_edge_hash(v, u);
	return edges_map[hash];
}

set <int> bridges;

int timer = 0;

void dfs(int v, int p = -1) {
	fup[v] = tin[v] = ++timer;
	for (int i : g[v]) {
		if (tin[i] != -1 && i != p) {
			fup[v] = min(fup[v], tin[i]);
		} else if (tin[i] == -1) {
			dfs(i, v);
			fup[v] = min(fup[v], fup[i]);
			if (fup[i] > tin[v]) {
				bridges.insert(get_edge_num(v, i));
			}
		}
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
		add_edge(a, b);
	}
	fup.resize(n, 1e9);
	tin.resize(n, -1);
	dfs(0);
	cout << len(bridges) << "\n";
	for (auto i : bridges) {
		cout << i << ' ';
	}
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 2e5 + 10;
const int K = 21;

vector <int> g[N];
vector <int> cost[N];
int dp[N][K];
int mn[N][K];
int tin[N];
int tout[N];
int parent[N];
int parent_edge_cost[N];
int timer = 1;

void dfs(int v, int p, int cur_edge_cost) {
	tin[v] = timer++;
	parent[v] = p;
	parent_edge_cost[v] = cur_edge_cost;

	dp[v][0] = p;
	mn[v][0] = cur_edge_cost;
	for (int i = 1; i < K; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
		int e1 = mn[v][i - 1];
		int vert = dp[v][i - 1];
		int e2 = mn[vert][i - 1];
		mn[v][i] = min(e1, e2);
	}

	for (int i = 0; i < len(g[v]); i++) {
		int u = g[v][i];
		int edge_cost = cost[v][i];
		if (u != p) {
			dfs(u, v, edge_cost);
		}
	}
	tout[v] = timer++;
}

int check_ancestor(int v, int u) {   // v - anc of u
	return (tin[v] <= tin[u] && tout[u] <= tout[v]);
}

int mega_jump(int v, int u) {
	if (check_ancestor(v, u)) {
		swap(v, u);
	}
	int jmp_cost = 1e9;
	for (int i = K - 1; i >= 0; i--) {
		int cur = dp[v][i];
		int cur_cost = mn[v][i];
		if (!check_ancestor(cur, u)) {
			v = cur;
			jmp_cost = min(jmp_cost, cur_cost);
		}
	}
	jmp_cost = min(jmp_cost, parent_edge_cost[v]);
	return jmp_cost;
}

int get_lca(int v, int u) {
	return min(mega_jump(v, u), mega_jump(u, v));
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif   //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n - 1; i++) {
		/*cin >> x >> y >> c;
		x--;
		y--;*/
		int anc, c;
		cin >> anc >> c;
		int x = i;
		int y = anc;
		y--;
		g[x].push_back(y);
		cost[x].push_back(c);
		g[y].push_back(x);
		cost[y].push_back(c);
	}
	dfs(1, 1, 1e9);
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		int x = get_lca(a, b);
		cout << x << "\n";
	}
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 100;

vector <int> g[N];
vector <int> used;

bool f = true;

void dfs(int v, int col) {
	used[v] = col;
	for (int i : g[v]) {
		if (used[i] == -1) {
			dfs(i, 1 - col);
		} else if (used[i] == col) {
			f = false;
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
	int n, m;
	cin >> n >> m;
	used.resize(n, -1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for (int i = 0; i < n; i++) {
		if (used[i] == -1) {
			dfs(i, 1);
		}
	}
	if (f) {
		cout << "YES";
	} else {
		cout << "NO";
	}
	return 0;
}

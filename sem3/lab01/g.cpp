#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5 + 10;

vector <int> g[N];
vector <int> used;
int col = 1;

void dfs(int v) {
	used[v] = col;
	for (int i : g[v]) {
		if (used[i] == 0) {
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
	int n, m;
	cin >> n >> m;
	used.resize(n, 0);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			dfs(i);
			col++;
		}
	}
	cout << col - 1 << "\n";
	for (int i = 0; i < n; i++)
		cout << used[i] << ' ';
	return 0;
}

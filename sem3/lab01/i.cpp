#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 2e4 + 100;

vector <int> tin;
vector <int> g[N];
vector <int> fup;
set <int> cutpoint;

int timer = 0;

void dfs(int v, int p = -1) {
	fup[v] = tin[v] = ++timer;
	int count = 0;
	for (int i : g[v]) {
		if (tin[i] != -1 && i != p) {
			fup[v] = min(fup[v], tin[i]);
		} else if (tin[i] == -1) {
			dfs(i, v);
			fup[v] = min(fup[v], fup[i]);
			if (p != -1 && fup[i] >= tin[v]) {
				cutpoint.insert(v);
			}
			count++;
		}
	}
	if (count >= 2 && p == -1) {
		cutpoint.insert(v);
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
	}
	fup.resize(n, 1e9);
	tin.resize(n, -1);
	for (int i = 0; i < n; i++) {
		if (tin[i] == -1) {
			dfs(i);
		}
	}
	cout << len(cutpoint) << "\n";
	for (auto i : cutpoint) {
		cout << i + 1 << "\n";
	}
	return 0;
}

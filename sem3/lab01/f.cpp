#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5 + 10;

vector <int> g[N];
vector <int> used;
vector <int> ord;
set <pair<int, int>> sg[N];

void tops(int v) {
	used[v] = 1;
	for (int i : g[v]) {
		if (used[i] == 0) {
			tops(i);
		}
	}
	ord.push_back(v);
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
	}
	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			tops(i);
		}
	}
	reverse(all(ord));
	vector <int> num(n, -1);
	for (int i = 0; i < n; i++) {
		num[ord[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		for (int j : g[i]) {
			sg[i].insert({num[j], j});
		}
	}
	vector <int> to(n, -1);
	for (int i = 0; i < n; i++) {
		if (!sg[i].empty()) {
			auto x = *sg[i].begin();
			to[i] = x.second;
		}
	}
	int cnt = 1;
	int cur = ord[0];
	while (to[cur] != -1) {
		cur = to[cur];
		cnt++;
	}
	if (cnt == n) {
		cout << "YES";
	} else {
		cout << "NO";
	}
	return 0;
}

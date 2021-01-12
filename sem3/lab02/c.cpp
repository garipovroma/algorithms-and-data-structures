#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 201;
const int INF = 1000000000;

vector <pair<int, int>> g[N];

void dijkstra(int n, vector <int> &d) {
	set <pair<int, int>> ds;
	for (int i = 0; i < n; i++) {
		ds.insert({d[i], i});
	}
	while (!ds.empty()) {
		pair <int, int> cur = *ds.begin();
		ds.erase(ds.begin());
		for (auto i : g[cur.second]) {
			int v = i.first;
			int w = i.second;
			if (w + d[cur.second] < d[v]) {
				ds.erase({d[v], v});
				d[v] = w + d[cur.second];
				ds.insert({d[v], v});
			}
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
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		g[a].push_back({b, c});
	}
	for (int i = 0; i < n; i++) {
		vector <int> d(n, INF);
		d[i] = 0;
		dijkstra(n, d);
		for (int j = 0; j < n; j++) {
			cout << d[j] << ' ';
		}
		cout << "\n";
	}
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

vector <int> a;
vector <int> first, last;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	a.resize(m);
	for (int i = 0; i < m; i++) {
		cin >> a[i];
		a[i]--;
	}

	first.resize(n, -1);
	last.resize(n, -1);

	for (int i = 0; i < m; i++) {
		if (first[a[i]] == -1) {
			first[a[i]] = i;
		}
		last[a[i]] = i;
	}
	set <pair<int, int>> g;
	for (int i = 0; i < m; i++) {
		if (i == first[a[i]]) {
			int id = -1;
			for (int j = i + 1; j < m; j++) {
				if (a[j] == a[i]) {
					id = j;
					break;
				}
			}
			if (id == -1) {
				continue;
			}
			for (int j = i + 1; j < id; j++) {
				if (a[j] >= a[i + 1]) {
					g.insert({a[i], a[j]});
				}
			}
			first[a[i]] = id;
		}
	}

	cout << len(g) << "\n";
	for (auto i : g) {
		cout << i.first + 1 << ' ' << i.second + 1 << "\n";
	}
	return 0;
}

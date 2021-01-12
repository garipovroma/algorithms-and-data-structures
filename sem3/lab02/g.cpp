#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 5e3 + 228;
const int INF = (1 << 30);

pair <int, int> pts[N];

int get_cost(int x, int y) {
	return ((pts[x].first - pts[y].first) * (pts[x].first - pts[y].first)
	 + (pts[x].second - pts[y].second) * (pts[x].second - pts[y].second));
}

double get_double_cost(int x, int y) {
	return sqrt(1.0 * get_cost(x, y));
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
		cin >> pts[i].first >> pts[i].second;
	}
	vector <int> mn(n, -1);
	vector <double> mn_cost(n, 1e18);
	vector <bool> used(n, false);
	double sum = 0;
	for (int i = 0; i < n; i++) {
		int v = -1;
		for (int j = 0; j < n; j++) {
			if (!used[j] && (v == -1 || mn_cost[j] < mn_cost[v])) {
				v = j;
			}
		}
		if (mn[v] != -1) {
			sum += get_double_cost(v, mn[v]);
			//  cout << v << ' ' << mn[v] << "\n";
		}
		used[v] = true;
		for (int j = 0; j < n; j++) {
			double cur_cost = get_double_cost(v, j);
			if (cur_cost < mn_cost[j]) {
				mn[j] = v;
				mn_cost[j] = cur_cost;
			}
		}
	}
	cout.precision(15);
	cout << fixed;
	cout << sum;
	return 0;
}

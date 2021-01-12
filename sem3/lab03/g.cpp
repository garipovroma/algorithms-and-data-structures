#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1010;

struct euler_graph {
	int n;
	multiset<pair<int, int>> g;
	vector <int> deg;
	euler_graph() {}
	euler_graph(int n_, multiset<pair<int, int>> &g_) {
		n = n_;
		g = g_;
	}
	void read_graph(bool directed) {
		cin >> n;
		deg.resize(n, 0);
		for (int i = 0; i < n; i++) {
			int k;
			cin >> k;
			for (int j = 0; j < k; j++) {
				int x;
				cin >> x;
				x--;
				if (i > x && !directed) {
				    continue;
				}
				g.insert({i, x});
				deg[i]++;
				if (!directed) {
				    g.insert({x, i});
				    deg[x]++;
				}
			}
		}
	}
	int dfs(int v, multiset<pair<int, int>> &g, vector <bool> &used) {
		used[v] = true;
		int res = 1;
		for (int i = 0; i < n; i++) {
		    if (g.find(make_pair(v, i)) == g.end()) {
		        continue;
		    }
			if (!used[i]) {
				res += dfs(i, g, used);
			}
		}
		return res;
	}
	bool check_euler_path() {
		vector <bool> used(n, false);
		int total_cnt = 0, cnt = 0;
		for (int i = 0; i < n; i++) {
			if (!used[i]) {
				int cur_size = dfs(i, g, used);
				if (cur_size == 1) {
					cnt++;
				}
				total_cnt++;
			}
		}
		int odd = 0;
		for (int i = 0; i < n; i++) {
			if (deg[i] % 2 == 1) {
				odd++;
				break;
			}
		}
		return (cnt <= 1 && odd <= 1);
	}
	void get_euler_path(vector <int> &res) {
		int odd = -1;
		for (int i = 0; i < n; i++) {
			if (deg[i] % 2 == 1) {
				odd = i;
				break;
			}
		}
		if (odd == -1) {
			odd++;
		}
		find_path(odd, res);
	}
	void find_path(int v, vector <int> &res) {
        for (int i = 0; i < n; i++) {
            if (g.find(make_pair(v, i)) == g.end()) {
                continue;
            }
            g.erase(g.find({v, i}));
            g.erase(g.find({i, v}));
            find_path(i, res);
        }
		res.push_back(v);
	}
};

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	euler_graph g;
	g.read_graph(false);
	if (!g.check_euler_path()) {
	    cout << -1;
	    return 0;
	}
	vector <int> ans;
	g.get_euler_path(ans);
	cout << len(ans) - 1 << "\n";
	for (auto i : ans) {
		cout << i + 1 << ' ';
	}
	return 0;
}

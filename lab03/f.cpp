#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

struct DSU {
	vector <int> p, sz, mn, mx;
	DSU(int n) {
		p.resize(n);
		sz.resize(n);
		for (int i = 0; i < n; i++) {
			p[i] = i;
			sz[i] = 1;
		}
	}
    int get_p(int v) {
    	return ((v == p[v]) ? v : (p[v] = get_p(p[v])));
    }
    bool un(int x, int y) {
    	x = get_p(x);
    	y = get_p(y);
    	if (x == y) return false;
    	if (sz[x] > sz[y]) swap(x, y);  //   sz[x] < sz[y]
    	p[x] = y;
    	sz[y] += sz[x];
    	return true;
    }
};

const int N = 50001;

vector <int> g[N];


int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	vector <pair<string, pair <int, int>> > v;
	for (int i = 0; i < k; i++) {
		string a;
		int b, c;
		cin >> a >> b >> c;
		b--;
		c--;
		v.push_back({a, {b, c}});
	}
	reverse(all(v));
	int num = 0;
	for (auto i : v)
		if (i.first == "ask") num++;
	vector <int> ans(num);
	DSU d(n);
	for (auto x : v) {
		string a = x.first;
		int b = x.second.first;
		int c = x.second.second;
		if (a == "cut") {
			d.un(b, c);
		} else {
			ans[--num] = (d.get_p(b) == d.get_p(c));
		}
	}
	for (auto i : ans)
		if (i == 1)
			cout << "YES\n";
		else
			cout << "NO\n";
	return 0;
}

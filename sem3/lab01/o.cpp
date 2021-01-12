#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1e5 + 228;

int n;

vector <int> g[N];
vector <int> tg[N];
vector <int> used, fs, ls, colors, plate;
int color = 1;

int get_negate(int x, int pos) {
	if (fs[x] == pos) {
		return ls[x];
	} else {
		return fs[x];
	}
}

void add_edge(int pos1, int pos2, int n1, int n2) {
	int x = plate[pos1];
	int y = plate[pos2];
	if (n1 == 1) {
		pos1 = get_negate(x, pos1);
	}
	if (n2 == 1) {
		pos2 = get_negate(y, pos2);
	}
	//  cout << "pos " << pos1 << ' ' << pos2 << "\n";
	int kek1 = get_negate(x, pos1);
	int kek2 = get_negate(y, pos2);
	g[pos1].push_back(kek2);
	g[pos2].push_back(kek1);
	tg[kek2].push_back(pos1);
	tg[kek1].push_back(pos2);
	//  cout << pos1 << " --> " << kek2 << "\n";
	//  cout << pos2 << " --> " << kek1 << "\n";
}

void process(int i, int j) {
	int x = colors[plate[i]];
	int y = colors[plate[j]];
	if (x == y) {
		if (i == fs[plate[i]] && j == fs[plate[j]]) {
			add_edge(i, j, 0, 0);
		} else if (i != fs[plate[i]] && j == fs[plate[j]]) {
			add_edge(i, j, 0, 0);
		} else if (i == fs[plate[i]] && j != fs[plate[j]]) {
			add_edge(i, j, 0, 0);
		} else {
			add_edge(i, j, 0, 0);
		}
	}
}

vector <int> ord;

void tops(int v) {
	used[v] = 1;
	for (int i : g[v]) {
		if (used[i] == -1) {
			tops(i);
		}
	}
	ord.push_back(v);
}

void colorize(int v) {
	used[v] = color;
	for (int i : tg[v]) {
		if (used[i] == -1) {
			colorize(i);
		}
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	fs.resize(n, -1);
	ls.resize(n);
	plate.resize(2 * n);
	colors.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> colors[i];
	}
	for (int i = 0; i < 2 * n; i++) {
		cin >> plate[i];
		plate[i]--;
		if (fs[plate[i]] == -1) {
			fs[plate[i]] = i;
		}
		ls[plate[i]] = i;
	}

	for (int i = 0; i + 1 < 2 * n; i++) {
		process(i, i + 1);
	}
	process(2 * n - 1, 0);
	process(0, 2 * n - 1);

	used.resize(2 * n, -1);
	for (int i = 0; i < 2 * n; i++) {
		if (used[i] == -1) {
			tops(i);
		}
	}
	reverse(all(ord));
	used.clear();
	used.resize(2 * n, -1);
	for (int i : ord) {
		if (used[i] == -1) {
			colorize(i);
			color++;
		}
	}
	for (int i = 0; i < n; i++) {
		if (used[fs[i]] == used[ls[i]]) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES\n";
	for (int i = 0; i < n; i++) {
		if (used[fs[i]] > used[ls[i]]) {
			cout << fs[i] + 1 << ' ';
		} else {
			cout << ls[i] + 1 << ' ';
		}
	}
	return 0;
}

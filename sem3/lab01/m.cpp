#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 26;

vector <string> strs;

vector <int> g[N], used, ord, incoming, num;

void tops(int v) {
	used[v] = 1;
	for (int i : g[v]) {
		if (used[i] == -1) {
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
	int n;
	cin >> n;
	strs.resize(n);
	incoming.resize(N, 0);
	num.resize(N, 0);
	for (int i = 0; i < n; i++) {
		cin >> strs[i];
	}
	for (int i = 0; i < n - 1; i++) {
		if (strs[i] == strs[i + 1]) {
			cout << "No";
			return 0;
		}
		if (len(strs[i]) > len(strs[i + 1])) {
			cout << "No";
			return 0;
		}
		if (len(strs[i]) != len(strs[i + 1])) {
			continue;
		}
		for (int j = 0; j < len(strs[i]); j++) {
			int x = strs[i][j] - 'a';
			int y = strs[i + 1][j] - 'a';
			if (x != y) {
				g[x].push_back(y);
				incoming[y]++;
				break;
			}
		}
	}

	used.resize(N, -1);
	for (int i = N - 1; i >= 0; i--) {
		if (used[i] == -1) {
			tops(i);
		}
	}
	reverse(all(ord));
	for (int i = 0; i < N; i++) {
		num[ord[i]] = i;
	}
	for (int i = 0; i < N; i++) {
		for (int j : g[i]) {
			int x = num[i];
			int y = num[j];
			if (x > y) {
				cout << "No";
				return 0;
			}
		}
	}
	unordered_set <int> cant_be_first;
	for (int i = 0; i < n; i++) {
		if (len(strs[i]) == 1) {
			continue;
		}
		cant_be_first.insert(int(strs[i][0] - 'a'));
	}
	for (int i = 0; i < N; i++) {
		if (incoming[i] != 0) {
			cant_be_first.insert(i);
		}
	}
	int first_letter = -1;
	vector <int> cols(N, -1);
	int col = 0;
	for (int i = 0; i < N; i++) {
		if (cant_be_first.find(i) == cant_be_first.end()) {
			first_letter = i;
			cols[i] = col++;
			break;
		}
	}
	for (int i = 0; i < N; i++) {
		if (cols[ord[i]] == -1) {
			cols[ord[i]] = col++;
		}
	}
	if (first_letter == -1) {
		cout << "No";
		return 0;
	}

	cout << "Yes\n";
	for (auto i : cols) {
		cout << i << ' ';
	}
	return 0;
}

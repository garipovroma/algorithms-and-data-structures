#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())

bool check(vector <int> &a) {
	int n = len(a);
	for (int i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1])
			return false;
	}
	return true;
}

bool srt(vector <int> a, vector <vector<pair<int, int>>> s) {
	for (int i = 0; i < len(s); i++) {
		for (int j = 0; j < len(s[i]); j++) {
			int x = a[s[i][j].first];
			int y = a[s[i][j].second];
			a[s[i][j].first] = min(x, y);
			a[s[i][j].second] = max(x, y);
		}
	}
	return check(a);
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector <vector<pair<int, int>>> s(k);
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		while (x > 0) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			if (a > b) {
				swap(a, b);
			}
			s[i].push_back({a, b});
			x--;
		}
	}
	int ss = 0;
	for (int i = 0; i < (1 << n); i++) {
		vector <int> a;
		for (int j = 0; j < n; j++) {
			int b = (i >> j) & 1;
			a.push_back(b);
		}
		if (srt(a, s))
			ss++;
	}
	if (ss == (1 << n))
		cout << "Yes";
	else
		cout << "No";
	return 0;
}

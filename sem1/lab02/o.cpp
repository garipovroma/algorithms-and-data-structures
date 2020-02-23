#include <bits/stdc++.h>

using namespace std;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	while (cin >> n) {
		if (n == 0) return 0;
		vector <int> a(n);
		int m = 0;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			if (a[i] == 1) {
				m++;
			}
		}
		vector <pair <int, int>> ans;
		int id = -1;
		for (int i = 0; i < n; i++) {
			if (a[i] == 1) {
				id = i;
				break;
			}
		}

		bool kek = false;
		for (int i = 0; i < n - 1; i++) {
			if (a[i] > a[i + 1]) kek = true;
		}
		if (!kek) {
			cout << "-1\n";
			continue;
		}

		//  1

		for (int i = 0; i < n; i++) {
			if (i != id && a[i] == 1) {
				ans.push_back({id, i});
			}
		}

		//  2
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (i == id || j == id) continue;
				ans.push_back({i, j});
			}
		}

		//  3
		for (int i = id; i < n - m - 1; i++) {
			ans.push_back({i, i + 1});
		}
		for (int i = n - m - 1; i >= 1; i--) {
			ans.push_back({i, i - 1});
		}
		cout << (int)ans.size() << "\n";

		for (auto i : ans) {
			cout << i.first + 1 << ' ' << i.second + 1 << "\n";
		}
	}
	return 0;
}

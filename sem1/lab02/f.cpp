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
	cin >> n;
	vector <int> a(n);
	a[0] = 1;
	for (int i = 1; i < n; i++) {
		a[i] = i + 1;
		swap(a[i], a[i / 2]);
	}
	for (int i : a) {
		cout << i << ' ';
	}
	return 0;
}

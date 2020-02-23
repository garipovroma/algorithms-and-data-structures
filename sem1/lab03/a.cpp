#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <int> a(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	bool ok = true;
	for (int i = 1; i <= n; i++) {
		if (2 * i <= n && a[i] > a[2 * i])
			ok = false;
		if (2 * i + 1 <= n && a[i] > a[2 * i + 1])
			ok = false;
		if (!ok) break;
	}
	if (ok)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}

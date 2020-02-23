#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef long long ll;

vector <int> get_next(vector <int> a) {
	int n = len(a);
	vector <pair<int, int>> cnt(n + 1, {0, 0});
	for (int i : a) {
		cnt[i].first++;
		cnt[i].second++;
	}
	int mn = 1e9;
	int id = -1;
	for (int i = n - 1; i >= 0; i--) {
		//cout << i << endl;
		if (mn != 1e9 && mn >= a[i]) {
			for (int j = a[i] + 1; j <= n; j++) {
			    if (cnt[j].first < cnt[j].second) {
			        mn = j;
			        break;
			    }
			}
			cnt[a[i]].first--;
			cnt[mn].first++;
			a[i] = mn;
			id = i + 1;
			break;
		}
		cnt[a[i]].first--;
		if (cnt[a[i]].second > cnt[a[i]].first) {
			if (mn == 1e9 || mn < a[i]) {
			    mn = a[i];
			}
		}
	}
	/*for (int i = 1; i <= n; i++)
		cout << cnt[i].first << ' ' << cnt[i].second << endl;
	cout << endl;*/
	vector <int> mas;
	for (int i = 1; i <= n; i++) {
		for (int j = cnt[i].second - cnt[i].first; j >= 1; j--) {
			mas.push_back(i);
		}
	}
	int pos = 0;
	for (int i = id; i < n; i++) {
		a[i] = mas[pos++];
	}
	return a;
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("nextmultiperm.in", "rt", stdin);
	freopen("nextmultiperm.out", "wt", stdout);
	#endif // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector <int> mas = get_next(a);
	for (int i : mas)
		cout << i << ' ';
	return 0;
}

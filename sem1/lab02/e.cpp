#include <bits/stdc++.h>

using namespace std;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif   //  HOME
	int n, m, k;
	cin >> n >> m >> k;
	vector <string> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector <int> ord(n);
	for (int i = 0; i < n; i++)
		ord[i] = i;
	for (int t = 0; t < k; t++) {
		int cnt[26];
		int head[26];
		for (int i = 0; i < 26; i++) {
			cnt[i] = 0;
		}
		for (int i : ord)
			cnt[a[i][m - t - 1] - 'a']++;
		head[0] = 0;
		for (int i = 1; i < 26; i++)
			head[i] = head[i - 1] + cnt[i - 1];
		vector <int> nword(n);
		for (int i : ord) {
			nword[head[a[i][m - t - 1] - 'a']++] = i;
		}
		nword.swap(ord);
	}
	for (int i = 0; i < n; i++)
		cout << a[ord[i]] << "\n";
	return 0;
}

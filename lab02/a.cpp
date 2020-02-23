#include <bits/stdc++.h>

using namespace std;

#define len(x) int(x.size())
#define all(x) x.begin(), x.end()

int myrand() {
	return (((rand()) >> 16) + rand());
}

int partition(vector <int> &a, int l, int r) {
	int i = l, j = r;
	int val = a[l + myrand() % (r - l + 1)];
	// int m = (l + r) / 2;
	// int val = a[m];
	while(true) {
		while (a[j] > val) {
			j--;
		}
		while (a[i] < val) {
			i++;
		}
		if (i < j) {
			swap(a[i], a[j]);
			i++;
			j--;
		} else {
			break;
		}
	}
	return j;
}

void qsort(vector <int> &a, int l, int r) {
	if (l >= r) return;
	int ind = partition(a, l, r);
	qsort(a, l, ind);
	qsort(a, ind + 1, r);
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	srand(time(nullptr));
	int n;
	cin >> n;
	vector <int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	qsort(a, 0, n - 1);
	for (int i : a)
		cout << i << ' ';
	return 0;
}

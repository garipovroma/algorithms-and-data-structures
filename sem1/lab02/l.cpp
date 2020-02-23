#include <bits/stdc++.h>

using namespace std;

struct kek{
	int v, w;
	int id;
	kek() {}
	kek(int vv, int ww, int dd) {
		v = vv;
		w = ww;
		id = dd;
	}
};

double x;

bool cmp(kek i, kek j) {
	return (- i.v + i.w * x + j.v - j.w * x < 0);
}

int k;
int n;

const int N = 1e5 + 1;

kek s[N];

bool check() {
	sort(s, s + n, cmp);
	double sum = 0;
	for (int i = 0; i < k; i++) {
		sum += s[i].v - s[i].w * x;
	}
	return (sum >= 0);
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> s[i].v >> s[i].w;
		s[i].id = i + 1;
	}
	double l = 0, r = 0;
	for (int i = 0; i < n; i++) {
		r += s[i].v;
	}
	while(r > 1e-6 + l) {
		double m = (l + r) / 2.0;
		x = m;
		if (check()) {
			l = m;
		} else {
			r = m;
		}
	}
	x = l;
	sort(s, s + n, cmp);
	for (int i = 0; i < k; i++)
		cout << s[i].id << " ";
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

typedef unsigned int iint;

iint get_hash(string &s) {
	iint res = 0;
	int n = len(s);
	for (int i = 0; i < n; i++) {
		res = res * 31 + s[i];
	}
	return res;
}

void gen() {
	vector <char> v;
	for (char i = 'a'; i <= 'z'; i++) {
		v.push_back(i);
	}
	for (char i = 'A'; i <= 'Z'; i++) {
		v.push_back(i);
	}
	while(true) {
		string s, t;
		for (int i = 0; i < 4; i++) {
			int x = rand() % len(v);
			int y = rand() % len(v);
			s.push_back(v[x]);
			t.push_back(v[y]);
		}
		if (get_hash(s) == get_hash(t)) {
			cout << s << ' ' << t << endl;
			return;
		}
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif   //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	srand(time(nullptr));
	gen();
	int k;
	cin >> k;
	int deg = 0;
	while ((1 << deg) < k) {
		deg++;
	}

	vector <string> ans;
	for (int i = 0; i < (1 << deg); i++) {
		string cur;
		for (int j = 0; j < deg; j++) {
			int b = (i >> j) & 1;
			if (b == 0) {
				string a = "VrZD";
				cur.push_back('V');
				cur.push_back('r');
				cur.push_back('Z');
				cur.push_back('D');
			} else {
				string b = "VqyD";
				cur.push_back('V');
				cur.push_back('q');
				cur.push_back('y');
				cur.push_back('D');
			}
		}
		ans.push_back(cur);
	}
	int x = 0;
	for (auto i : ans) {
		if (x == k) {
			return 0;
		}
		cout << i << "\n";
		x++;
	}
	return 0;
}

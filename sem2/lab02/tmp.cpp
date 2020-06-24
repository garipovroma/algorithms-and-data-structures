#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 1000;
const int LEN = 3;

const unsigned int P = 31;

unsigned int deg[N];

void calc() {
	deg[0] = 1;
	for (int i = 1; i < N; i++) {
		deg[i] = deg[i - 1] * P;
	}
}

unsigned int get_hash(string s) {
	unsigned int res = 0;
	int n = len(s);
	for (int i = 0; i < n; i++) {
		unsigned int x = s[i];
		res += x * deg[n - i - 1];
	}
	return res;
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	calc();
	vector <char> pull;
	for (int k = 0; k < 1; k++) {
		for (char i = 'a'; i <= 'z'; i++) {
			pull.push_back(i);
		}
		for (char i = 'A'; i <= 'Z'; i++) {
			pull.push_back(i);
		}
	}
	int ans = 0;
	map<int, unordered_set<string>> v;
	for (int i = 0; i < len(pull); i++) {
		for (int j = 0; j < len(pull); j++) {
			for (int k = 0; k < len(pull); k++) {
				for (int h = 0; h < len(pull); h++) {
					string s;
					s.push_back(pull[i]);
					s.push_back(pull[j]);
					s.push_back(pull[k]);
					s.push_back(pull[h]);
					v[get_hash(s)].insert(s);
				}
			}
		}
	}
	int mx = 0;
	int hash = 0;
	for (auto i : v) {
		int was = 0;
		was = mx;
		mx = max(mx, len(i.second));
		if (mx != was) {
			hash = i.first;
		}
	}
	cout << mx << endl;
	for (auto i : v[hash])
		cout << i << ' ';
	int x;
	cin >> x;
	/*
	map <unsigned int, unordered_set<string>> v;
	int mx = 0;
	int hash = -1;
	do {
		random_shuffle(all(pull));
		string cur = "";
		for (int i = 0; i < LEN; i++) {
			cur.push_back(pull[i]);
		}
		int cur_hash = get_hash(cur);
		if ((size(v[cur_hash]) != 0 && v[cur_hash].find(cur) == v[cur_hash].end()) || (len(v[cur_hash]) == 0)) {
			v[cur_hash].insert(cur);
		}
		if (len(v[cur_hash]) > mx) {
			mx = len(v[cur_hash]);
			hash = cur_hash;
		}
		if (mx == 2) {
			for (auto i : v[hash]) {
				cout << i << ' ' << get_hash(i) << "\n";
			}
			break;
		}
	} while(true);*/
	return 0;
}
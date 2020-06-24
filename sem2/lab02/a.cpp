#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

template <typename T> struct hash_table {  //  use this hash_table only with ints and strings
	const unsigned int P = 59;
	static const unsigned int M = 3e6 + 1;
	vector <vector<T>> mas = vector<vector<T>>(M);
	unsigned int get_hash(string s) {
		unsigned int res = 0;
		for (int i = 0; i < len(s); i++) {
			res = res * P + s[i];
			res %= M;
		}
		return res;
	}
	unsigned int get_hash(int x) {
		return x % M;
	}
	bool contains(T val) {
		unsigned int h = get_hash(val);
		for (auto i : mas[h]) {
			if (i == val) {
				return true;
			}
		}
		return false;
	}
	bool insert(T val) {
		if (contains(val)) {
			return false;
		}
		unsigned int h = get_hash(val);
		mas[h].push_back(val);
		return true;
	}
	bool erase(T val) {
		if (!contains(val)) {
			return false;
		}
		unsigned int h = get_hash(val);
		auto it = mas[h].begin();
		while (*it != val) {
			it++;
		}
		mas[h].erase(it);
		return true;
	}
};

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#else
	freopen("set.in", "rt", stdin);
	freopen("set.out", "wt", stdout);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	hash_table <int> v;
	while (cin >> s) {
		int x;
		cin >> x;
		if (s == "insert") {
			v.insert(x);
		} else if (s == "exists") {
			bool f = v.contains(x);
			if (f) {
				cout << "true\n";
			} else {
				cout << "false\n";
			}
		} else if (s == "delete") {
			v.erase(x);
		}
	}
	return 0;
}

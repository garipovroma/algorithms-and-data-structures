#include <iostream>

using namespace std;

template<typename T> struct vector228 {
	T *mas;
	int sz = 0;
	int capacity = 1;
	vector228() {
		mas = (T*)malloc(sizeof(T));
	}
	void push_back(T x) {
		if (sz == 0) {
			mas[0] = x;
			sz++;
			return;
		}
		if (sz < capacity) {
			mas[sz] = x;
			sz++;
		} else {
			capacity *= 2;
			T *nw = (T*)malloc(capacity * sizeof(T));
			for (int i = 0; i < sz; i++) {
				nw[i] = mas[i];
			}
			free(mas);
			mas = nw;
			mas[sz] = x;
			sz++;
		}
	}
	T pop_back() {
		sz--;
		T v = mas[sz];
		if (4 * sz == capacity) {
			capacity /= 2;
			T *nw = (T*)malloc(capacity * sizeof(T));
			for (int i = 0; i < sz; i++) {
				nw[i] = mas[i];
			}
			free(mas);
			mas = nw;
		}
		return v;
	}
	T back() {
		return mas[sz - 1];
	}
	int size() {
		return sz;
	}
	T operator[](int x) {
		return mas[x];
	}
};

template<typename T> struct stack228 {
	vector228 <T> mas;
	void push(T x) {
		mas.push_back(x);
	}
	T top() {
		return mas[mas.size() - 1];
	}
	int size() {
		return mas.size();
	}
	T pop_back() {
		return mas.pop_back();
	}
};

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string t;
	while(cin >> t) {
		stack228 <char> s;
		int n = int(t.length());
		s.push(t[0]);
		for (int i = 1; i < n; i++) {
			if (s.size() > 0) {
				if (t[i] == ')' && s.top() == '(') {
					s.pop_back();
				} else if (t[i] == ']' && s.top() == '[') {
					s.pop_back();
				} else {
					s.push(t[i]);
				}
			} else {
				s.push(t[i]);
			}
		}
		bool ok;
		if (s.size() == 0) {
			ok = true;
		} else {
			ok = false;
		}
		if (ok)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}

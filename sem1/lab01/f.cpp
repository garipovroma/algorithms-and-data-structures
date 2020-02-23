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
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	stack228 <int> s;
	string t;
	int res = 0;
	while (cin >> t) {
		if (t[0] == '*') {
			int x = s.pop_back();
			int y = s.pop_back();
			x = x * y;
			s.push(x);
		} else if (t[0] == '+') {
			int x = s.pop_back();
			int y = s.pop_back();
			x = x + y;
			s.push(x);
		} else if (t[0] == '-') {
			int x = s.pop_back();
			int y = s.pop_back();
			x = y - x;
			s.push(x);
		} else {
			int x = 0;
			for (int i = 0; i < int(t.length()); i++) {
				x = x * 10 + (t[i] - '0');
			}
			s.push(x);
		}
	}
	res = s.pop_back();
	cout << res;
	return 0;
}

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
		return mas[sz];
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
	stack228 <int> s;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char t;
		cin >> t;
		if (t == '-') {
			cout << s.pop_back() << "\n";
		} else {
			int x;
			cin >> x;
			s.push(x);
		}
	}
	return 0;
}

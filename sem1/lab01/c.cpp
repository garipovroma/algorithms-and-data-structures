#include <iostream>

using namespace std;

template<typename T> struct queue228 {
	T *mas;
	int sz = 0;
	int capacity = 1;
	int l = 0;
	queue228() {
		mas = (T*)malloc(sizeof(T));
	}
	void push_back(T x) {
		if (sz - l < capacity) {
			if (sz < capacity)
				mas[sz] = x;
			else
				mas[sz - capacity] = x;
			sz++;
		} else {
			capacity *= 2;
			T *nw = (T*)malloc(capacity * sizeof(T));
			for (int i = 0; i < sz - l; i++) {
				if (l + i < capacity /  2)
					nw[i] = mas[l + i];
				else
					nw[i] = mas[(l + i) - (capacity / 2)];
			}
			free(mas);
			mas = nw;
			sz -= l;
			mas[sz] = x;
			sz++;
			l = 0;
		}
		if (l > capacity && sz > capacity) {
			sz -= capacity;
			l -= capacity;
		}
	}
	T pop_back() {
		sz--;
		T v;
		if (sz > capacity)
			v = mas[sz - capacity];
		else
			v = mas[sz];
		if (4 * (sz - l)  == capacity) {
			capacity /= 2;
			T *nw = (T*)malloc(capacity * sizeof(T));
			for (int i = 0; i < sz - l; i++) {
				if (l + i < capacity * 2)
					nw[i] = mas[l + i];
				else
					nw[i] = mas[(l + i) - (capacity * 2)];
			}
			free(mas);
			mas = nw;
			sz -= l;
			l = 0;
		}
		if (l > capacity && sz > capacity) {
			sz -= capacity;
			l -= capacity;
		}
		return v;
	}
	T pop_front() {
		int v = mas[l % capacity];
		l++;
		if (4 * (sz - l)  == capacity) {
			capacity /= 2;
			T *nw = (T*)malloc(capacity * sizeof(T));
			for (int i = 0; i < sz - l; i++) {
				if (l + i < capacity * 2)
					nw[i] = mas[l + i];
				else
					nw[i] = mas[(l + i) - capacity * 2];
			}
			free(mas);
			mas = nw;
			sz -= l;
			l = 0;
		}
		if (l > capacity && sz > capacity) {
			sz -= capacity;
			l -= capacity;
		}
		return v;
	}
	T back() {
		if (sz - 1 < capacity)
			return mas[sz - 1];
		else
			return mas[(sz - 1) - capacity];
	}
	int size() {
		return sz - l;
	}
	T operator[](int x) {
		if (x + l >= capacity)
			return mas[(x + l) % capacity];
		else
			return mas[x + l];
	}
	T front() {
		if (l >= capacity)
			return mas[l - capacity];
		else
			return mas[l];
	}
	T get_from_back(int x) {
		if (sz - x < capacity)
			return mas[sz - x];
		else
			return mas[(sz - x - capacity)];
	}
};


int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //  HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	queue228 <int> q;
	for (int i = 0; i < n; i++) {
		char t;
		cin >> t;
		if (t == '+') {
			int x;
			cin >> x;
			q.push_back(x);
		} else {
			cout << q.pop_front() << "\n";
		}
	}
	return 0;
}

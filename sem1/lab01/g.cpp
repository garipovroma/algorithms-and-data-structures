#include <bits/stdc++.h>

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

int get_mn(queue228 <int> &mn) {
	int res = mn.front();
	return res;
}

void add(queue228 <int> &q, int x) {
	while (q.size() > 0 && q.back() > x) {
		q.pop_back();
	}
	q.push_back(x);
}

void erase(queue228 <int> &q, int x) {
	if (q.size() > 0 && q.front() == x)
		q.pop_front();
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	int a, b, c;
	cin >> a >> b >> c;
	queue228 <int> mas;
	queue228 <int> mn;
	if (m > k) {
		for (int i = 0; i < k; i++) {
			int x;
			cin >> x;
			add(mn, x);
			mas.push_back(x);
		}
		long long ans = 0;
		for (int i = 0; i < m - k; i++) {
			int x = a * mas.get_from_back(2) + b * mas.get_from_back(1) + c;
			add(mn, x);
			mas.push_back(x);
		}
		for (int i = 0; i < n - m; i++) {
			int x = a * mas.get_from_back(2) + b * mas.get_from_back(1) + c;
			ans += get_mn(mn);
			erase(mn, mas.front());
			mas.pop_front();
			add(mn, x);
			mas.push_back(x);
		}
		ans += get_mn(mn);
		cout << ans;
	} else {   // m < k
		for (int i = 0; i < m; i++) {
			int x;
			cin >> x;
			add(mn, x);
			mas.push_back(x);
		}
		long long ans = 0;
		for (int i = 0; i < k - m; i++) {
			ans += get_mn(mn);
			erase(mn, mas.front());
			mas.pop_front();
			int x;
			cin >> x;
			mas.push_back(x);
			add(mn, x);
		}
		for (int i = 0; i < n - k; i++) {
			ans += get_mn(mn);
			erase(mn, mas.front());
			mas.pop_front();
			int x = a * mas.get_from_back(2) + b * mas.get_from_back(1) + c;
			mas.push_back(x);
			add(mn, x);
		}
		ans += get_mn(mn);
		cout << ans;
	}
	return 0;
}

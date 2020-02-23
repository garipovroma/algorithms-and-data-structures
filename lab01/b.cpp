#include <iostream>

using namespace std;

template<typename T> struct Node {
	Node *prv = nullptr;
	T val;
	Node(T y) {
		val = y;
	}
};


template<typename T> struct list228 {
	Node <T> *end = nullptr;
	void push(T x) {
		if (end == nullptr) {
			end = new Node<T>(x);
		} else {
			Node <T> *nw = new Node<T>(x);
			nw->prv = end;
			end = nw;
		}
	}
	T top() {
		return end->val;
	}
	T pop_back() {
		Node <T> *x = end;
		T val = end->val;
		end = end->prv;
		delete x;
		return val;
	}
};

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	list228 <int> s;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char t;
		cin >> t;
		if (t == '+') {
			int x;
			cin >> x;
			s.push(x);
		} else {
			cout << s.pop_back() << "\n";
		}
	}
	return 0;
}

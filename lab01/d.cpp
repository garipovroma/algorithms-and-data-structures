#include <iostream>

using namespace std;

template<typename T> struct Node {
	Node *prv = nullptr;
	Node *nxt = nullptr;
	T val;
	Node(T y) {
		val = y;
	}
};


template<typename T> struct queue228 {
	Node <T> *end = nullptr;
	Node <T> *begin = nullptr;
	void push_back(T x) {
		if (end == nullptr) {
			begin = end = new Node<T>(x);
		} else {
			Node <T> *nw = new Node<T>(x);
			end->nxt = nw;
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
	T pop_front() {
		Node <T> *x = begin;
		T val = begin->val;
		begin = begin->nxt;
		if (begin == nullptr) {
			end = nullptr;
		}
		delete x;
		return val;
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

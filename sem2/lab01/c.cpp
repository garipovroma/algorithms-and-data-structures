#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

int getRand() {
	return (rand() >> 16) + rand();
}

struct Node {
	Node *l, *r;
	int sz;
	int x, y;
	Node() {
		l = r = nullptr;
	}
	Node(int a) {
		x = a;
		y = getRand();
		l = r = nullptr;
		sz = 1;
	}
};

const int N = 1e6 + 228;

Node nodes[N];
int curPos = 0;

Node *nwNode(int x) {
	nodes[curPos] = Node(x);
	curPos++;
	return &nodes[curPos - 1];
}

int get_sz(Node *v) {
	if (v == nullptr) {
		return 0;
	}
	return v->sz;
}

void upd_sz(Node *v) {
	if (v == nullptr) {
		return;
	}
	v->sz = get_sz(v->l) + 1 + get_sz(v->r);
}

pair <Node*, Node*> split(Node *v, int k) {
	if (v == nullptr) {
		return {nullptr, nullptr};
	}
	int sz = get_sz(v->l);
	if (k <= sz) {
		pair <Node*, Node*> t = split(v->l, k);
		v->l = t.second;
		upd_sz(v->l);
		return {t.first, v};
	} else {
		pair <Node*, Node*> t = split(v->r, k - sz - 1);
		v->r = t.first;
		upd_sz(v->r);
		return {v, t.second};
	}
}

Node* merge(Node *vl, Node *vr) {
	if (vl == nullptr) {
		return vr;
	}
	if (vr == nullptr) {
		return vl;
	}
	if (vl->y > vr->y) {
		vl->r = merge(vl->r, vr);
		upd_sz(vl->r);
		return vl;
	} else {
		vr->l = merge(vl, vr->l);
		upd_sz(vr->l);
		return vr;
	}
}

Node *root = nullptr;

void push_back(int val) {
	root = merge(root, nwNode(val));
}

void move_segment(int l, int r) {
	pair <Node*, Node*> t1 = split(root, r);
	pair <Node*, Node*> t2 = split(t1.first, l - 1);
	root = merge(merge(t2.second, t2.first), t1.second);
}

void print(Node *v) {
	if (v == nullptr) {
		return;
	}
	print(v->l);
	cout << v->x << ' ';
	print(v->r);
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif   // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	srand(time(nullptr));    //   change me
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		push_back(i + 1);
	}
	/*pair <Node*, Node*> kek = split(root, );
	print(kek.first);
	cout << "\n-----------\n";
	print(kek.second);
	cout << "\n-----------\n";*/
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		move_segment(l, r);
	}
	print(root);
	return 0;
}

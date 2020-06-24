#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;


int myRand() {
    return ((rand() >> 16) + rand());
}

struct Node {
    int x, y, sz;
    Node *l, *r;
    int num;
    Node() {
        l = r = nullptr;
        sz = 1;
        y = myRand();
    }
    Node(int a, int numm) {
        x = a;
        y = myRand();
        num = numm;
        sz = 1;
        l = r = nullptr;
    }
};

const int N = 1e6 + 228;
Node v[N];
int curPos = 0;

Node *nwNode(int x, int numm) {
    v[curPos] = Node(x, numm);
    curPos++;
    return &v[curPos - 1];
}

int get_sz(Node *v) {
    if (v == nullptr)
        return 0;
    else
        return v->sz;
}

void upd_sz(Node *v) {
    if (v == nullptr) {
        return;
    }
    v->sz = get_sz(v->l) + get_sz(v->r) + 1;
}

pair <Node*, Node*> split(Node *v, int k) {  // < k
    if (v == nullptr) {
        return {nullptr, nullptr};
    }
    if (k <= v->x) {
        pair <Node*, Node*> t = split(v->l, k);
        v->l = t.second;
        upd_sz(v->l);
        return {t.first, v};
    } else {
        pair <Node*, Node*> t = split(v->r, k);
        v->r = t.first;
        upd_sz(v->r);
        return {v, t.second};
    }
}

Node *merge(Node *vl, Node *vr) {
    if (vl == nullptr) {
        return vr;
    }
    if (vr == nullptr) {
        return vl;
    }
    if (vl->y < vr->y) {
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

void print(Node *v, string s) {
    if (v == nullptr) {
        return;
    }
    print(v->l, s + "## ");
    cout << s << v->x << endl;
    print(v->r, s + "## ");
}

vector <pair<pair<int, int>, int>> ans;
vector <int> parent;

int get_num(Node *v) {
	if (v == nullptr) {
		return -1;
	}
	return v->num;
}

void gfs(Node *v, Node *p) {
	if (v == nullptr) {
		return;
	}
	gfs(v->l, v);
	ans[v->num] = {{get_num(v->l), get_num(v->r)}, get_num(p)};
	gfs(v->r, v);
}

bool cmp(Node *a, Node *b) {
	return (a->x < b->x);
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif    //   HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <Node*> v(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		v[i] = nwNode(x, i);
		v[i]->y = y;
	}
	sort(all(v), cmp);
	deque <Node*> d;
	for (int i = 0; i < n; i++) {
		Node *vert = v[i];
		d.push_back(vert);
	}
	int len = 1;
	while (d.size() > 1) {
		deque <Node*> nw_d;
		while (d.size() >= 2) {
			Node *v1 = d.front();
			d.pop_front();
			Node *v2 = d.front();
			d.pop_front();
			Node *x = merge(v1, v2);
			nw_d.push_back(x);
		}
		if (d.size() == 1) {
			Node *v1 = d.front();
			d.pop_front();
			nw_d.push_back(v1);
		}
		len *= 2;
		d.swap(nw_d);
	}
	/*
	for (auto i : d) {
		cout << i->x << ' ';
	}
	*/
	cout << "YES\n";
	ans.resize(n);
	parent.resize(n);
	root = d.front();
	gfs(root, nullptr);
	for (auto i : ans) {
		cout << i.second + 1 << ' ' << i.first.first + 1 << ' ' << i.first.second + 1 << "\n";
	}
	return 0;
}

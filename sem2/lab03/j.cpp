#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

struct rect {
	int l, r, d, u;
	rect() {}
	rect(int a, int b, int c, int dd) {
		l = a;
		r = b;
		d = c;
		u = dd;
	}
};

struct event {
	int x, t, id;
	event() {}
	event(int a, int b, int c) {
		x = a;
		t = b;
		id = c;
	}
};

bool cmp(const event &a, const event &b) {
	if (a.x == b.x) {
		return (a.t < b.t);
	} else {
		return (a.x < b.x);
	}
}


const int N = 2e6 + 10;

int t[4 * N];
int p[4 * N];
int mx_pos[4 * N];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		mx_pos[v] = tl;
		t[v] = 0;
	} else {
		int tm = (tl + tr) / 2;
		build(2 * v, tl, tm);
		build(2 * v + 1, tm + 1, tr);
		mx_pos[v] = min(mx_pos[2 * v], mx_pos[2 * v + 1]);
		t[v] = 0;
	}
}

void push(int v) {
	if (p[v] == 0) return;
	t[2 * v] += p[v];
	p[2 * v] += p[v];
	t[2 * v + 1] += p[v];
	p[2 * v + 1] += p[v];
	p[v] = 0;
}

void add(int v, int tl, int tr, int l, int r, int val) {
	if (l > r) {
		return;
	}
	if (tl == l && tr == r) {
		t[v] += val;
		p[v] += val;
	} else {
		push(v);
		int tm = (tl + tr) / 2;
		add(2 * v, tl, tm, l, min(r, tm), val);
		add(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
		if (t[2 * v] > t[2 * v + 1]) {
			mx_pos[v] = mx_pos[2 * v];
		} else {
			mx_pos[v] = mx_pos[2 * v + 1];
		}
		t[v] = max(t[2 * v], t[2 * v + 1]);
	}
}


int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif  // HOME
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <rect> rects;
	vector <event> events;
	for (int i = 0; i < n; i++) {
		int l, d, r, u;
		cin >> l >> d >> r >> u;
		d += 1000000;
		u += 1000000;
		rects.push_back(rect(l, r, d, u));
		events.push_back(event(l, -1, i));
		events.push_back(event(r, 1, i));
	}
	sort(all(events), cmp);
	build(1, 0, N);
	int mx = -1e9;
	int mx_x = -1;
	int mx_y = -1;
	for (auto cur_event : events) {
		int x = cur_event.x;
		int type = cur_event.t;
		int id = cur_event.id;
		int l = rects[id].d;
		int r = rects[id].u;
		if (type == -1) {
			add(1, 0, N, l, r, 1);
		} else {
			int cur_mx = t[1];
			if (cur_mx > mx) {
				mx = cur_mx;
				mx_x = x;
				mx_y = mx_pos[1];
			}
			add(1, 0, N, l, r, -1);
		}
	}
	cout << mx << "\n" << mx_x << ' ' << mx_y - 1000000;
	return 0;
}

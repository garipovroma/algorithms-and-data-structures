#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int chr = -1, N = 4e5 + 10;

long long a[N], a_[N], col[N], col_[N], ord[N], head[N], cnt[N], lcp[N];

template <typename T1, typename T2, typename T3>
struct triple {
    T1 first;
    T2 second;
    T3 third;
    triple(T1 t1, T2 t2, T3 t3) {
        first = t1;
        second = t2;
        third = t3;
    }
};

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector <int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    s.push_back(chr);
    n++;
    for (int i = 0; i < n; i++) {
        col[i] = s[i] - chr;
        cnt[col[i]]++;
    }
    head[0] = 0;
    for (int i = 1; i < 30; i++) {
        head[i] = head[i - 1] + cnt[i - 1];
    }
    for (int i = 0; i < n; i++) {
        a[head[col[i]]++] = i;
    }
    head[0] = 0;
    for (int i = 1; i < 30; i++)
        head[i] = head[i - 1] + cnt[i - 1];
    int l = 1;
    while (l < n) {
        for (int i = 0; i < n; i++) {
            int j = ((int) a[i] + n - l) % n;
            a_[head[col[j]]++] = j;
        }
        int k = 0;
        for (int i = 0; i < n; i++) {
            a[i] = a_[i];
            if (i == 0 || col[a[i]] != col[a[i - 1]] || col[(a[i] + l) % n] != col[(a[i - 1] + l) % n])
                head[k++] = i;
            col_[a[i]] = k - 1;
        }
        for (int i = 0; i < n; i++)
            col[i] = col_[i];
        l *= 2;
    }
    for (int i = 0; i < n; i++) {
        ord[a[i]] = i;
    }
    int x = 0;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        x = max(x - 1, 0);
        if (ord[i] == n - 1)
            x = 0;
        else
            while (s[i + x] == s[(int) a[ord[i] + 1] + x])
                x++;
        lcp[ord[i]] = x;
        sum += 1ll * x;
    }
    stack<pair<ll, ll>> stack;
    vector <ll> left(n, -1);
    vector <ll> right(n, n + 1);
    for (int i = 0; i < n; i++) {
        while (!stack.empty() && stack.top().first >= lcp[i]) {
            stack.pop();
        }
        if (!stack.empty()) {
            left[i] = stack.top().second;
        }
        stack.push({lcp[i], (ll) i});
    }
    while (!stack.empty()) {
        stack.pop();
    }
    for (int i = n - 1; i >= 0; i--) {
        while (!stack.empty() && stack.top().first >= lcp[i]) {
            stack.pop();
        }
        if (!stack.empty()) {
            right[i] = stack.top().second;
        }
        stack.push({lcp[i], (ll) i});
    }
    ll ans = 0;
    ll id = -1;
    for (int i = 0; i < n; i++) {
        ll xx = lcp[i];
        ll left_id = left[i];
        ll right_id = right[i];
        ll kek = (right_id - left_id);
        ll val = xx;
        ll cur = val * kek;
        if (ans < cur) {
            ans = cur;
            id = i;
        }
    }
    ll mx = 0;
    ll mn = 1000000000;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] > mx) {
            mx = s[i];
        }
        mn = min(mn, (ll) s[i]);
    }
    ll kek = ll(1ll * mn * (n - 1));
    if (ans < mx && mx > kek) {
        cout << mx << "\n" << 1 << "\n" << mx;
        return 0;
    } else if (ans < kek) {
        cout << ll(1ll * mn * (n - 1)) << "\n" << n - 1 << "\n";
        for (int i = 0; i < n - 1; i++) {
            cout << s[i] << ' ';
        }
        return 0;
    }
    cout << ans << "\n" << lcp[id] << "\n";
    for (int i = 0; i < lcp[id]; i++) {
        cout << s[(int) a[id] + i] << ' ';
    }
    cout << "\n";
    return 0;
} 

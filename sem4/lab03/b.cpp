#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif // HOME
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    int n = len(s);
    unordered_map<string, int> map[2];
    for (int msk = 0; msk < (1 << (n / 2)); msk++) {
        vector <int> a, b;
        for (int i = 0; i < n / 2; i++) {
            int bit = (msk >> i) & 1;
            if (bit == 1) {
                a.push_back(i);
            } else {
                b.push_back(i);
            }
        }
        int sz = min(len(a), len(b));
        bool ok = true;
        for (int i = 0; i < sz; i++) {
            if (s[a[i]] != s[b[i]]) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }
        string remainder = "";
        vector <int> c;
        if (len(a) > len(b)) {
            c = a;
        } else {
            c = b;
        }
        for (int i = sz; i < len(c); i++) {
            remainder.push_back(s[c[i]]);
        }
        if (len(a) > len(b)) {
            map[1][remainder] += 1;
        } else {
            map[0][remainder] += 1;
        }
    }
    ll ans = 0;
    for (int msk = 0; msk < (1 << (n / 2)); msk++) {
        vector <int> a, b;
        for (int i = 0; i < n / 2; i++) {
            int bit = (msk >> i) & 1;
            if (bit == 1) {
                a.push_back(n - i - 1);
            } else {
                b.push_back(n - i - 1);
            }
        }
        int sz = min(len(a), len(b));
        bool ok = true;
        for (int i = 0; i < sz; i++) {
            if (s[a[i]] != s[b[i]]) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }
        string remainder = "";
        vector <int> c;
        if (len(a) > len(b)) {
            c = a;
        } else {
            c = b;
        }
        for (int i = sz; i < len(c); i++) {
            remainder.push_back(s[c[i]]);
        }
        reverse(all(remainder));
        if (len(a) > len(b)) {
            ans += map[1][remainder];
        } else {
            ans += map[0][remainder];
        }
    }
    cout << ans;
    return 0;
}
 

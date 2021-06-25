#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

vector<int> calc_pref(string &s) {
    int n = len(s);
    vector <int> pref(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pref[i - 1];
        while (j > 0 && s[j] != s[i]) {
            j = pref[j - 1];
        }
        if (s[j] == s[i]) {
            j++;
        }
        pref[i] = j;
    }
    return pref;
}

vector<int> calc_z_function_from_prefix(vector<int> &pref) {
    int n = len(pref);
    vector<int> z(n, 0);
    z[0] = n;
    for (int i = 1; i < n; i++) {
        if (pref[i] > 0) {
            z[i - pref[i] + 1] = pref[i];
        }
    }
    int ind = -1;
    for (int i = 1; i < n; i++) {
        if (z[i] == 0) {
            if (ind >= i) {
                z[i] = min(z[i + pref[ind] - 1 - ind], ind - i + 1);
            } else {
                ind = -1;
            }
        } else {
            ind = i + z[i] - 1;
        }
    }
    return z;
}

vector <ll> get_distinct_substrings_count(string &s) {
    int n = len(s);
    vector <ll> res(n);
    string cur_str = "";
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        cur_str += s[i];
        reverse(all(cur_str));
        vector <int> pref = calc_pref(cur_str);
        vector <int> z = calc_z_function_from_prefix(pref);
        reverse(all(cur_str));
        int mx = 0;
        for (int j = 1; j <= i; j++) {
            mx = max(mx, z[j]);
        }
        ll val = i - mx + 1;
        cur += val;
        res[i] = cur;
    }
    return res;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    string s;
    cin >> s;
    vector <ll> ans = get_distinct_substrings_count(s);
    for (ll i : ans) {
        cout << i << "\n";
    }
    return 0;
}


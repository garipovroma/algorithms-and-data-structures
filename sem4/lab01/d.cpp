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

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    string s;
    cin >> s;
    vector <int> pref = calc_pref(s);
    vector <int> z = calc_z_function_from_prefix(pref);
    z.erase(z.begin());
    for (int i : z) {
        cout << i << ' ';
    }
    return 0;
} 

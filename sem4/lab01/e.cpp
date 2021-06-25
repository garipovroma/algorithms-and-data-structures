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

vector <int> calc_z_function(string &s) {
    vector <int> pref = calc_pref(s);
    vector <int> z = calc_z_function_from_prefix(pref);
    return z;
}

int main(){
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif    // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s, t;
    cin >> s >> t;

    string rev_s = s;
    reverse(all(rev_s));
    string rev_t = t;
    reverse(all(rev_t));

    string text = s + "#" + t;
    string rev_text = rev_s + "#" + rev_t;

    vector <int> z = calc_z_function(text);
    vector <int> rev_z = calc_z_function(rev_text);
    vector <int> ans;
    //    cout << len(rev_text) << "\n";
    //    cout << text << "\n";
    //    cout << rev_text << "\n";
    for (int i = len(s) + 1; i + len(s) - 1 < len(text); i++) {
        int x = i;
        int y = len(rev_text) - i + 1;
        //  cout << x << ' ' << y << ' ' << text[x] << ' ' << rev_text[y] << ' ' << z[x] + rev_z[y] << "\n";
        if (z[x] + rev_z[y] >= len(s) - 1) {
            ans.push_back(i - len(s));
        }
    }
    cout << len(ans) << "\n";
    for (int i : ans) {
        cout << i << ' ';
    }
    return 0;
}
 

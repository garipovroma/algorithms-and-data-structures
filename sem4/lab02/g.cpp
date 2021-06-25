#include <bits/stdc++.h>

using namespace std;

const int chr = 'a' - 2, N = 4e5 + 10;

long long a[N], a_[N], col[N], col_[N], ord[N], head[N], cnt[N], lcp[N];

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s, t, s_;
    cin >> s >> t;
    s_ = s;
    s_.push_back(chr);
    s_ += t;
    s_.push_back(chr + 1);
    int n = s.length();
    int k = s_.length();
    for (int i = 0; i < k; i++) {
        col[i] = s_[i] - chr;
        cnt[col[i]]++;
    }
    head[0] = 0;
    for (int i = 1; i < 30; i++) {
        head[i] = head[i - 1] + cnt[i - 1];
    }
    for (int i = 0; i < k; i++) {
        a[head[col[i]]++] = i;
    }
    head[0] = 0;
    for (int i = 1; i < 30; i++)
        head[i] = head[i - 1] + cnt[i - 1];
    int l = 1;
    while (l < k) {
        for (int i = 0; i < k; i++) {
            int j = ((int) a[i] + k - l) % k;
            a_[head[col[j]]++] = j;
        }
        int kk = 0;
        for (int i = 0; i < k; i++) {
            a[i] = a_[i];
            if (i == 0 || col[a[i]] != col[a[i - 1]] || col[(a[i] + l) % k] != col[(a[i - 1] + l) % k])
                head[kk++] = i;
            col_[a[i]] = kk - 1;
        }
        for (int i = 0; i < k; i++)
            col[i] = col_[i];
        l *= 2;
    }
    for (int i = 0; i < k; i++) {
        ord[a[i]] = i;
    }
    int x = 0;
    long long sum = 0;
    for (int i = 0; i < k; i++) {
        x = max(x - 1, 0);
        if (ord[i] == k - 1)
            x = 0;
        else
            while (s_[i + x] == s_[(int) a[ord[i] + 1] + x])
                x++;
        lcp[ord[i]] = x;
        sum += 1ll * x;
    }
    vector <int> num(k, 0);
    for (int i = 0; i < k; i++) {
        num[i] = (a[i] <= n ? 0 : 1);

        /*cout << a[i] << ' ' << lcp[i] << ' ' << num[i] << ' ';
        for (int j = a[i]; j < k; j++) {
            cout << s_[j];
        }
        cout << "\n";*/

    }
    int mx = -1000000000;
    int id = -1;
    int r = 0;
    int mn;
    for (int l = 1; l < k; l++) {
        mn = (int) lcp[l];
        int idd = l;
        r = l;
        while(r < k && num[l] == num[r]) {
            if (lcp[r] < mn) {
                mn = (int) lcp[r];
                idd = r;
            }
            r++;
        }
        if (mn > mx) {
            mx = mn;
            id = idd;
        }
        l = max(r - 2, l);
    }
    //   cout << mx << "\n";
    for (int i = 0; i < mx; i++) {
        cout << s_[(int) a[id] + i];
    }
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int chr = 'a' - 1, N = 4e5 + 10;

long long a[N], a_[N], col[N], col_[N], ord[N], head[N], cnt[N], lcp[N];

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    s.push_back(chr);
    int n = s.length();
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
    for (int i = 1; i < n; i++) {
        cout << a[i] + 1 << ' ';
    }
    cout << "\n";
    for (int i = 1; i < n - 1; i++) {
        cout << lcp[i] << ' ';
    }
    return 0;
}

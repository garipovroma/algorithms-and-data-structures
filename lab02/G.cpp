#include <bits/stdc++.h>

using namespace std;

const int N = 3e6 + 10;
const unsigned int K = 31622;

typedef long long ll;

unsigned int a[N];
int v[N][2];
int cnt[N];
int head[N];
int ord[N];
int nword[N];

void bucketsort(int n) {
    for (int i = 0; i < n; i++) {
        v[i][1] = a[i] % K;
        v[i][0] = a[i] / K;
        ord[i] = i;
        nword[i] = i;
    }
    for (int t = 1; t >= 0; t--) {
        int mx = -1;
        for (int i = 0; i < n; i++)
            mx = max(mx, v[i][t]);
        for (int i = 0; i <= mx; i++) {
            cnt[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            cnt[v[i][t]]++;
        }
        head[0] = 0;
        for (int i = 1; i <= mx; i++) {
            head[i] = head[i - 1] + cnt[i - 1];
        }
        for (int i = 0; i < n; i++) {
            nword[head[v[ord[i]][t]]] = ord[i];
            head[v[ord[i]][t]]++;
        }
        for (int i = 0; i < n; i++) {
            ord[i] = nword[i];
        }
    }
}

unsigned int cur = 0;
unsigned int kekx, keky;
unsigned int nextRand24() {
    cur = cur * kekx + keky;
    return (cur >> 8);
}

unsigned int nextRand32() {
    unsigned int a = nextRand24(), b = nextRand24();
    return ((a << 8) ^ b);
}

signed main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif  //  HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t, n;
    cin >> t >> n;
    for (int tt = 0; tt < t; tt++) {
        unsigned long long sum = 0;
        cin >> kekx >> keky;
        for (int j = 0; j < n; j++) {
            a[j] = nextRand32();
        }
        bucketsort(n);
        for (int i = 0; i < n; i++)
            sum += 1ll * a[ord[i]] * (1ll * i + 1ll);
        cout << sum << "\n";
    }
    return 0;
}

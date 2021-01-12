#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define len(x) int(x.size())

typedef long long ll;

const int N = 501;
const int INF = 2000000000;

int n, m, s, t;

struct edge {
    int from, to, capacity, flow, id;
    edge() {}
    edge(int a, int b, int c, int d) {
        from = a;
        to = b;
        capacity = c;
        flow = d;
    }
    edge(int a, int b, int c, int d, int _id) {
        from = a;
        to = b;
        capacity = c;
        flow = d;
        id = _id;
    }
};

vector<vector<int>> get_flow_decomposition();

vector <int> g[N];
vector <edge> edges;

void add_edge(int a, int b, int c, int id = -1) {
    g[a].push_back(len(edges));
    edges.emplace_back(a, b, c, 0, id);
    g[b].push_back(len(edges));
    edges.emplace_back(b, a, 0, 0, id);
}

vector <int> dist;
vector <int> pos;

bool bfs() {
    queue <int> q;
    dist.assign(n + 2, -1);
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        if (dist[t] != -1) {
            break;
        }
        int v = q.front();
        q.pop();
        for (auto ind : g[v]) {
            edge cur_edge = edges[ind];
            int to = cur_edge.to;
            int f = cur_edge.flow;
            int c = cur_edge.capacity;
            if (dist[to] == -1 && f < c) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return (dist[t] != -1);
}

ll dfs(int v, ll flow) {
    if (flow == 0 || v == t) {
        return flow;
    }
    for (int i = pos[v], id = g[v][i]; pos[v] < len(g[v]); pos[v]++, i++, id = g[v][i]) {
        int to = edges[id].to;
        if (dist[v] + 1 == dist[to]) {
            int res = (int) dfs(to, min(flow, (ll) edges[id].capacity - edges[id].flow));
            if (res > 0) {
                edges[id].flow += res;
                edges[id ^ 1].flow -= res;
                return res;
            }
        }
    }
    return 0;
}

ll dinic_find_max_flow() {
    ll max_flow = 0;
    while (true) {
        bool current_bfs_result = bfs();
        if (!current_bfs_result) {
            break;
        }
        pos.assign(n + 2, 0);
        while (true) {
            ll cur_flow_push = dfs(s, INF);
            if (cur_flow_push == 0) {
                break;
            }
            max_flow += cur_flow_push;
        }
    }
    return max_flow;
}

struct edges_set {
    const ll P = 1000000007;

    unordered_set<ll> edges;
    deque <edge> edges_deque;

    ll get_edge_hash(edge e) {
        ll hash = e.from + e.to * P;
        return hash;
    }

    void add_edge(edge e) {
        if (!find(e)) {
            edges.insert(get_edge_hash(e));
            edges_deque.push_back(e);
        }
    }

    bool find(edge e) {
        return edges.find(get_edge_hash(e)) != edges.end();
    }

    void pop_front() {
        edges.erase(get_edge_hash(edges_deque.front()));
        edges_deque.pop_front();
    }

    deque <edge> get_edges() {
        return edges_deque;
    }
};

int __cur_flow;

vector<edge> get_decomposition_part(int begin_vertex) {
    edges_set edges_set;
    unordered_set <int> vertexes_set;
    int cur_vertex = begin_vertex;
    while (vertexes_set.find(cur_vertex) == vertexes_set.end()) {
        if (cur_vertex == t) {
            break;
        }
        edge found_edge(-1, -1, -1, -1);
        for (int ind : g[cur_vertex]) {
            edge cur_edge = edges[ind];
            if (cur_edge.flow > 0) {
                found_edge = cur_edge;
                break;
            }
        }
        if (found_edge.from == -1 && found_edge.to == -1) {
            return vector<edge>();
        }
        edges_set.add_edge(found_edge);
        vertexes_set.insert(cur_vertex);
        cur_vertex = found_edge.to;
    }
    if (vertexes_set.find(cur_vertex) != vertexes_set.end()) {
        while (edges_set.get_edges().front().from != cur_vertex) {
            edges_set.pop_front();
        }
    }
    __cur_flow = 0;
    int mn_flow = INF;
    vector <edge> edges_vector;
    for (edge cur_edge : edges_set.get_edges()) {
        if (cur_edge.from == s) {
            __cur_flow += cur_edge.flow;
        }
        mn_flow = min(mn_flow, cur_edge.flow);
        edges_vector.push_back(cur_edge);
    }
    for (edge cur_edge : edges_set.get_edges()) {
        edges[cur_edge.id * 2].flow -= mn_flow;
    }
    __cur_flow = mn_flow;
    return edges_vector;
}

pair<vector<int>, vector<vector<edge>>> build_decomposition() {
    vector <edge> cur_part = get_decomposition_part(s);
    vector <int> flows_values;
    vector <vector<edge>> decomposition;
    while (!cur_part.empty()) {
        decomposition.push_back(cur_part);
        flows_values.push_back(__cur_flow);
        cur_part = get_decomposition_part(s);
    }
    for (int i = 0; i < n; i++) {
        cur_part = get_decomposition_part(i);
        while (!cur_part.empty()) {
            decomposition.push_back(cur_part);
            flows_values.push_back(__cur_flow);
            cur_part = get_decomposition_part(i);
        }
    }
    return {flows_values, decomposition};
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif   // HOME
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    s = 0;
    t = n - 1;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        add_edge(a, b, c, i);
    }
    dinic_find_max_flow();
    pair<vector<int>, vector<vector<edge>>> result = build_decomposition();
    vector <int> flows_values = result.first;
    vector <vector<edge>> decomposition = result.second;
    cout << len(decomposition) << "\n";
    for (int i = 0; i < len(decomposition); i++) {
        cout << flows_values[i] << ' ' << len(decomposition[i]) << ' ';
        for (edge cur_edge : decomposition[i]) {
            cout << cur_edge.id + 1 << ' ';
        }
        cout << "\n";
    }
    return 0;
}

struct Query {
    int l;
    int r;
    int id;
};

const int S = 700;

bool cmp(Query A, Query B) {
    if (A.l / S != B.l / S) return A.l / S < B.l / S;
    return A.r > B.r;
}

int nc3(int n) {
    return (n * (n - 1) * (n - 2)) / 6;
}

int ans = 0;
int a[N + 1];
int freq[N + 1];

void add(int x) {
    ans -= nc3(freq[x]);
    freq[x]++;
    ans += nc3(freq[x]);
}

void remove(int x) {
    ans -= nc3(freq[x]);
    freq[x]--;
    ans += nc3(freq[x]);
}

void harshit() {
    int n, q; cin >> n >> q;
    // V<int> a(n);
    // cin >> a;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end(), cmp);
    vector<int> result(q);

    for (int i = 0, L = 1, R = 0; i < q; ++i) {
        while (R < queries[i].r) add(a[++R]);
        while (L > queries[i].l) add(a[--L]);
        while (R > queries[i].r) remove(a[R--]);
        while (L < queries[i].l) remove(a[L++]);
        result[queries[i].id] = ans;
    }

    for (int i = 0; i < q; ++i) {
        cout << result[i] << endl;
    }
}

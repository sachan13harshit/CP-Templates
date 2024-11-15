vector<int> F;

void Pre() {
    const int N = 1e6 + 5;
    vector<bool> P(N, true);
    P[0] = false;
    P[1] = false;

    for (int i = 2; i * i <= N; i++) {
        if (P[i]) {
            for (int j = i * i; j < N; j += i) {
                P[j] = false;
            }
        }
    }
    for (int i = 2; i < N; i++) {
        if (P[i]) {
            F.push_back(i);
        }
    }
}

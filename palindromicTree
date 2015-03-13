struct PalTree {
    const static int maxn = 111111;

    const static int alphabet = 8;

    int len[maxn];
    int suffLink[maxn];
    int to[maxn][alphabet];
    long long cnt[maxn];
    int numV;
    char str[maxn];

    int v;

    void addLetter(int n) {
        while (str[n - len[v] - 1] != str[n])
            v = suffLink[v];
        int u = suffLink[v];
        while (str[n - len[u] - 1] != str[n])
            u = suffLink[u];
        int u_ = to[u][str[n] - 'a'];
        int v_ = to[v][str[n] - 'a'];
        if (v_ == -1) {
            v_ = to[v][str[n] - 'a'] = numV;
            len[numV++] = len[v] + 2;
            suffLink[v_] = u_;
        }
        v = v_;
        cnt[v]++;
    }

    void init() {
        memset(cnt, 0, sizeof cnt);
        memset(to, -1, sizeof to);
        str[0] = '#';
        len[0] = -1;
        len[1] = 0;
        for (int i = 0; i < alphabet; ++i) {
            len[2 + i] = 1;
            suffLink[2 + i] = 1;
            to[0][i] = 2 + i;
        }
        len[2] = len[3] = 1;
        suffLink[1] = 0;
        suffLink[0] = 0;
        numV = 2 + alphabet;
    }
};

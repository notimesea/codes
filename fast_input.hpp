#include <bits/stdc++.h>

namespace Scanner {
    const static int BUF_SIZE = 65536;
    static char input[BUF_SIZE];
    const static size_t MAGIC = 256;
    size_t pos = BUF_SIZE;
    
    inline void ensureCapacity() {
        if (pos == BUF_SIZE) {
            memmove(input, input + pos, sizeof(char) * (BUF_SIZE - pos));
            fread(input + BUF_SIZE - pos, sizeof(char), sizeof(char) * pos, stdin);
            pos = 0;
        }
    }

    int nextInt() {
        ensureCapacity();
        while (isspace(input[pos])) {
            ++pos;
        }
        bool sign = false;
        if (input[pos] == '-') {
            sign = true;
            ++pos;
        }
        int res = 0;
        while (isdigit(input[pos])) {
            res = res * 10 + input[pos] - '0';
            ++pos;
        }
        return sign ? -res : res;
    }

    char nextChar() {
        ensureCapacity();
        while (isspace(input[pos])) {
            ++pos;
        }
        return input[pos++];
    }
};

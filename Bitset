struct Bitset
{
    ull * data;
    int n;
    Bitset(const int _n)
    {
        n = (_n + 63) >> 6;
        data = new ull[n];
        memset(data, 0, n << 3);
    }

    Bitset & operator=(const Bitset & r)
    {
        if (this == &r)
            return *this;
        n = r.n;
        memcpy(data, r.data, n << 3);
        return *this;
    }

    void set(int pos)
    {
        if (pos >= 0 && (pos >> 6) < n)
            data[pos >> 6] |= 1ull << (pos & 63);
    }

    void reset() {
        memset(data, 0, n << 3);
    }
    void reset(int pos)
    {
        if (pos >= 0 && (pos >> 6) < n)
            data[pos >> 6] &= ~(1ull << (pos & 63));
    }

    bool test(int pos)
    {
        if (pos >= 0 && (pos >> 6) < n)
            return (data[pos >> 6] >> (pos & 63)) & 1ull;
        else
            return false;
    }

    void operator|=(const Bitset & r)
    {
        for(int i = 0; i < n; ++i)
            data[i] |= r.data[i];
    }
    void operator&=(const Bitset & r)
    {
        for(int i = 0; i < n; ++i)
            data[i] &= r.data[i];
    }
    void operator^=(const Bitset & r)
    {
        for(int i = 0; i < n; ++i)
            data[i] ^= r.data[i];
    }

    void shr(int shift, const Bitset &r) {
        int delta = shift >> 6;
        if (delta >= n) {
            return;
        }
        shift &= 63;
        if (shift == 0) {
            for (int i = 0, j = delta; j < n; ++i, ++j) {
                data[j] |= r.data[i];
            }
            return;
        }
        int rs = 64 - shift;
        for(int j = 0, k = j + delta + 1; k < n; ++j, ++k)
            data[k] |= (r.data[j + 1] << shift) | (r.data[j] >> rs);

        data[delta] |= r.data[0] << shift;
    }

    void operator<<=(int shift)
    {
        int delta = shift >> 6;
        if (delta >= n)
        {
            memset(data, 0, n << 3);
            return;
        }
        shift &= 63;
        if (shift == 0)
        {
            memmove(data + delta, data, (n - delta) << 3);
            memset(data, 0, delta << 3);
            return;
        }
        for(int i = n - 1; i >= delta + 1; --i)
            data[i] = (data[i - delta] << shift) | (data[i - delta - 1] >> (64 - shift));

        data[delta] = data[0] << shift;
        memset(data, 0, delta << 3);
    }
    void operator>>=(int shift)
    {
        int delta = shift >> 6;
        if (delta >= n)
        {
            memset(data, 0, n << 3);
            return;
        }
        shift &= 63;
        if (shift == 0)
        {
            memmove(data, data + delta, (n - delta) << 3);
            memset(data + n - delta, 0, delta << 3);
            return;
        }
        for(int i = 0; i < n - delta - 1; ++i)
            data[i] = (data[i + delta] >> shift) | (data[i + delta + 1] << (64 - shift));

        data[n - delta - 1] = data[n - 1] >> shift;
        memset(data + n - delta, 0, delta << 3);
    }

    int set_of_bits(int * res) const
    {
        int size = 0;
        for(int i = 0; i < n; ++i)
        {
            if (!data[i])
                continue;
            ull temp = data[i];
            while(temp)
            {
                int pos = __builtin_ctzll(temp);
                res[size++] = pos + (i << 6);
                temp ^= 1ull << pos;
            }
        }
        return size;
    }
    inline void print()
    {
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < 64; ++j)
                cout << ((data[i] >> j) & 1ull);
        }
        cout << endl;
    }
    ~Bitset() {
        delete data;
    }
};

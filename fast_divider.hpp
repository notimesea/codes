#include <bits/stdc++.h>

struct divider_32 {
    uint32_t value;
    uint32_t magic;
    uint8_t more;

    static inline uint32_t div_32_to_32(uint32_t u1, uint32_t u0, uint32_t v, uint32_t *r) {
        uint64_t n = ((uint64_t)u1 << 32) | u0;
        auto result = (uint32_t)(n / v);
        *r = (uint32_t)(n - result * (uint64_t)v);
        return result;
    }

    static inline uint32_t mullhi_u32(uint32_t x, uint32_t y) {
        uint64_t xl = x, yl = y;
        uint64_t rl = xl * yl;
        return (uint32_t) (rl >> 32u);
    }

    divider_32(uint32_t d) : value(d) {
        assert(d != 0);

        uint32_t floor_log_2_d = 31 - __builtin_clz(d);

        if ((d & (d - 1)) == 0) {
            magic = 0;
            more = (uint8_t) (floor_log_2_d);
        } else {
            uint32_t rem, proposed_m;
            proposed_m = div_32_to_32(1U << floor_log_2_d, 0, d, &rem);
            const uint32_t e = d - rem;
            proposed_m += proposed_m;
            const uint32_t twice_rem = rem + rem;
            if (twice_rem >= d || twice_rem < rem) proposed_m += 1;
            more = (uint8_t) (floor_log_2_d | 0x40);
            magic = 1 + proposed_m;
        }

        more &= 0x1F;
    }

    friend inline uint32_t operator/(uint32_t numer, const divider_32 &d) {
        if (!d.magic) {
            return numer >> d.more;
        }
        uint32_t q = mullhi_u32(d.magic, numer);
        uint32_t t = ((numer - q) >> 1u) + q;
        return t >> d.more;
    }

    friend inline uint32_t operator%(uint32_t numer, const divider_32 &d) {
        return numer - (numer / d) * d.value;
    }
};

struct divider_64 {
    uint64_t value;
    uint64_t magic;
    uint8_t more;

    static inline uint64_t div_64_to_64(uint64_t u1, uint64_t u0, uint64_t v, uint64_t *r) {
        const uint64_t b = (1ULL << 32); // Number base (32 bits)
        uint64_t un1, un0; // Norm. dividend LSD's
        uint64_t vn1, vn0; // Norm. divisor digits
        uint64_t q1, q0; // Quotient digits
        uint64_t un64, un21, un10; // Dividend digit pairs
        uint64_t rhat; // A remainder
        int s; // Shift amount for norm

        // If overflow, set rem. to an impossible value,
        // and return the largest possible quotient
        if (__builtin_expect(u1 >= v, 0)) {
            if (r != NULL)
                *r = (uint64_t) -1;
            return (uint64_t) -1;
        }

        // count leading zeros
        s = __builtin_clzll(v);
        if (__builtin_expect(s > 0, 1)) {
            // Normalize divisor
            v = v << s;
            un64 = (u1 << s) | ((u0 >> (64 - s)) & (-s >> 31));
            un10 = u0 << s; // Shift dividend left
        } else {
            // Avoid undefined behavior
            un64 = u1 | u0;
            un10 = u0;
        }

        // Break divisor up into two 32-bit digits
        vn1 = v >> 32;
        vn0 = v & 0xFFFFFFFF;

        // Break right half of dividend into two digits
        un1 = un10 >> 32;
        un0 = un10 & 0xFFFFFFFF;

        // Compute the first quotient digit, q1
        q1 = un64 / vn1;
        rhat = un64 - q1 * vn1;

        while (q1 >= b || q1 * vn0 > b * rhat + un1) {
            q1 = q1 - 1;
            rhat = rhat + vn1;
            if (rhat >= b)
                break;
        }

        // Multiply and subtract
        un21 = un64 * b + un1 - q1 * v;

        // Compute the second quotient digit
        q0 = un21 / vn1;
        rhat = un21 - q0 * vn1;

        while (q0 >= b || q0 * vn0 > b * rhat + un0) {
            q0 = q0 - 1;
            rhat = rhat + vn1;
            if (rhat >= b)
                break;
        }

        // If remainder is wanted, return it
        if (r != NULL)
            *r = (un21 * b + un0 - q0 * v) >> s;

        return q1 * b + q0;
    }


    static inline uint64_t mullhi_u64(uint64_t x, uint64_t y) {
#ifdef __SIZEOF_INT128__
        __uint128_t xl = x;
        __uint128_t rl = xl * y;

        return (rl >> 64);
#else
        uint64_t u0, u1, v0, v1, k, t;
    uint64_t w1, w2;
    uint64_t whi;

    u1 = x >> 32; u0 = x & 0xFFFFFFFF;
    v1 = y >> 32; v0 = y & 0xFFFFFFFF;

    t = u0*v0;
    k = t >> 32;

    t = u1*v0 + k;
    w1 = t & 0xFFFFFFFF;
    w2 = t >> 32;

    t = u0*v1 + w1;
    k = t >> 32;

    whi = u1*v1 + w2 + k;

    return whi;
#endif
    }

    divider_64(uint64_t d) : value(d) {
        assert(d != 0);

        uint32_t floor_log_2_d = 63 - __builtin_clzll(d);

        // Power of 2
        if ((d & (d - 1)) == 0) {
            magic = 0;
            more = (uint8_t) (floor_log_2_d);
        } else {
            uint64_t rem;
            auto proposed_m = div_64_to_64(1ULL << floor_log_2_d, 0, d, &rem);
            const auto e = d - rem;
            proposed_m += proposed_m;
            const uint64_t twice_rem = rem + rem;
            if (twice_rem >= d || twice_rem < rem) proposed_m += 1;
            more = (uint8_t) (floor_log_2_d | 0x40);
            magic = 1 + proposed_m;
        }
        more &= 0x3f;
    }

    friend inline uint64_t operator/(uint64_t numer, const divider_64 &d) {
        if (!d.magic) {
            return numer >> d.more;
        }
        auto q = mullhi_u64(d.magic, numer);
        auto t = ((numer - q) >> 1u) + q;
        return t >> d.more;
    }

    friend inline uint64_t operator%(uint64_t numer, const divider_64 &d) {
        return numer - (numer / d) * d.value;
    }
};

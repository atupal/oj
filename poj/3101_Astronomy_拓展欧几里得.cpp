#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long p[3];

unsigned long long* gcdEx(unsigned long long a, unsigned long long b, unsigned long long *p) {
    if (b == 0) {
        p[0] = 1, p[1] = 0, p[2] = a;
        return p;
    } else {
        p = gcdEx(b, b%a, p);
        unsigned long long t = p[0];
        p[0] = p[1];
        p[1] = t - a/b*p[1];
        return p;
    }
}

void swap(unsigned long long &a, unsigned long long &b) {
    if (a != b) {
        a ^= b ^= a ^= b;
    }
}

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    if (a == 0 || b == 0) return 0;
    while (a && b) b%=a^=b^=a^=b;
    return a+b;
}

void solve() {
    unsigned long long n;

    scanf("%llu", &n);

    // ans  = ans1 / ans2;
    unsigned long long ans1, ans2;

    unsigned long long a, b;

    scanf("%llu", &a);
    scanf("%llu", &b);
    if (a > b) {
        swap(a, b);
    }
    ans1 = a * b;
    ans2 = 2 * (b - a);
    unsigned long long g = gcd(ans1, ans2);
    if (g != 0) {
        ans1 /= g;
        ans2 /= g;
    } else {
        ans1 = 0;
        ans2 = 1;
    }


    for (unsigned long long i = 2; i < n; ++ i) {
        scanf("%llu", &b);

        if (a > b) {
            swap(a, b);
        }
        unsigned long long newans1, newans2;
        newans1 = a * b;
        newans2 = 2 * (b - a);

        unsigned long long g = gcd(newans1, newans2);
        if (g != 0) {
            newans1 /= g;
            newans2 /= g;
        } else {
            continue;
        }

        if (ans1 == 0) {
            ans1 = newans1;
            ans2 = newans2;
            continue;
        }

        g = gcd(ans1 * newans2, newans1 * ans2);
        ans1 *= newans1 * ans2 / g;
        g = gcd(ans1, ans2);
        ans1 /= g;
        ans2 /= g;
    }

    printf("%llu %llu", ans1, ans2);
}

void test() {
    gcdEx(8, 5, p);
    printf("%llu %llu %llu\n", p[0], p[1], p[2]);
}

int main() {
    solve();

    return 0;
}

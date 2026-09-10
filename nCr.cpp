#include <bits/stdc++.h>
using namespace std;

// n * n - 1 * ... (n - r + 1)
// r * (r - 1) *... 1
int MOD = 1e9 + 7;
long long power(long long base, long long exp, long long mod)
{
    long long res = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long nCr(long long n, long long r, long long mod = 0)
{
    if (r < 0 || r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;
    if (r > n / 2)
        r = n - r;

    // Case 1: Modulo calculation
    if (mod > 0)
    {
        long long num = 1, den = 1;
        for (int i = 0; i < r; i++)
        {
            num = (num * (n - i)) % mod;
            den = (den * (i + 1)) % mod;
        }
        return (num * power(den, mod - 2, mod)) % mod;
    }

    // Case 2: Non-modulo calculation
    else
    {
        long long ans = 1;
        for (int i = 1; i <= r; i++)
        {
            ans = ans * (n - i + 1) / i;
        }
        return ans;
    }
}

int main()
{
    cout << nCr(5, 3) << endl; // 10
    cout << nCr(4, 3) << endl; // 4
    cout << nCr(6, 2) << endl; // 15
}

// For use of modl with diff, follow this pattern:
// ```
// (v1 - v2 + modl)%modl
// ```
// It will prevent negative answers
// Example: https://leetcode.com/problems/count-valid-sequences/
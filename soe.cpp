// Sieve of Eratosthenes
vector<int> primes;

void soe()
{
    int n = 1e5;
    vector<bool> p(n + 1, true);
    for (int i = 2; i * i <= n; i++)
    {
        if (p[i])
        {
            for (int j = i * i; j <= n; j++)
                p[j] = false;
        }
    }

    for (int i = 2; i <= n; i++)
    {
        if (p[i])
            prims.emplace_back(p[i]);
    }
}
// vector<int> freq(1000001, 0); 
// Assuming the maximum value of x is 1,000,000
// freq has count of divisors for each number when multiply called with divisorMapping for each number in the range.
void divisorMapping(int x, vector<int> &freq){
    for(int d = 1; d*d <= x; d++){
        if(x%d == 0){
            freq[d]++;
            if(d*d != x) freq[x/d]++;
        }
    }
}

// Example:
// vector<int> freq(mx + 1, 0);
// for(auto x : nums){
//     divisorMapping(x, freq);
// }


int countCoPrimeTo(int x) {
    // Get unique prime factors of x
    vector<int> primes;
    int temp = x;
    for (int d = 2; d * d <= temp; d++) {
        if (temp % d == 0) {
            primes.push_back(d);
            while (temp % d == 0) temp /= d;
        }
    }
    if (temp > 1) primes.push_back(temp);

    int k = primes.size();
    int total_coprime = 0;

    // Iterate over all 2^k subsets of prime factors using bitmask
    for (int mask = 0; mask < (1 << k); mask++) {
        int prod = 1;
        int bits_set = 0;
        for (int i = 0; i < k; i++) {
            if ((mask >> i) & 1) {
                prod *= primes[i];
                bits_set++;
            }
        }
        // PIE Logic: Odd bits -> Add (+), Even bits -> Subtract (-)
        // total_coprime = freq[1] (All elements) - ∑ freq[pᵢ] (Elements with 1 Prime common) + ∑ freq[pᵢpⱼ] (Add elements with 2 prime common) - …
        
        if (bits_set % 2 == 1) {
            total_coprime -= freq[prod];
        } 
        else{
            total_coprime += freq[prod];
        }
    }
    return total_coprime;
}
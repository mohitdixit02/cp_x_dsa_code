#include <bits/stdc++.h>
using namespace std;

// n * n - 1 * ... (n - r + 1)
// r * (r - 1) *... 1
long long uppr = pow(2, 50); // upper limit of nCr
long long nCr(long long n, long long r){
    if(r == 0 || r == n) return 1;
    if(r < 0 || r > n) return 0;
    if(r > n/2) r = n - r;
    long long rt = 1;
    long long nt = n;
    long long ans = 1;
    while(nt > (n - r)){
        if(ans > uppr) return uppr;
        ans *= nt;
        while(rt <= r && ans%rt == 0){
            ans /= rt;
            rt++;
        }
        nt--;
    }
    return ans;
}

int main(){
    cout << nCr(5, 3) << endl; // 10
    cout << nCr(4, 3) << endl; // 4
    cout << nCr(6, 2) << endl; // 15
}
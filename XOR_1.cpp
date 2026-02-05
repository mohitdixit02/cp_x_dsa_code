// Given MEX and XOR ( a and b ) find the minimum array length

#include <bits/stdc++.h>
#include <numeric>
using namespace std;

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        int xor_val = 0;
        int rem = (a - 1)%4;
        if(rem == 0){
            xor_val = a - 1;
        } 
        else if(rem == 1){
            xor_val = 1;
        }
        else if(rem == 2){
            xor_val = a;
        }
        else{
            xor_val = 0;
        }
        if(xor_val == b){
            cout << a << endl;
        }
        else{
            int num2 = xor_val ^ b;
            cout << (num2 == a ? a + 2 : a + 1) << endl; 
        }
    }
}

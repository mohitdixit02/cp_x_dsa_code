#include <bits/stdc++.h>
using namespace std;

long long LIS(vector <long long>&a){
    vector <long long> x;
    for(auto i : a){
        if(x.size() == 0 || i > x.back()){
            x.emplace_back(i);
        }
        else{
            long long index = lower_bound(x.begin(), x.end(), i) - x.begin();
            x[index] = i;
        }
    }
    return x.size();
}

int main(){
    vector<long long> a = { 10, 22, 9, 33, 21, 50, 41, 60 };
    cout << LIS(a) << endl;
    return 0;
}
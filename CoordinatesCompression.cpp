#include <bits/stdc++.h>
using namespace std;

vector<int> coordinatesCompression(vector <int> a){
    int n = a.size();
    vector<int> res(a.begin(), a.end());
    sort(res.begin(), res.end());
    map<int,int> m;
    int ind = 0;
    for(int i = 0; i < n; i++){
        if(!m.count(res[i])){
            m[res[i]] = ind;
            ind++;
        }
    }
    for(int i = 0; i < n; i++) a[i] = m[a[i]];
    return a;
}


int main(){
    int n = 6;
    vector<int> arr = {2,11,0,14,30,7};
    vector <int> res = coordinatesCompression(arr);
    for(auto i : res) cout << i << " ";
    return 0;
}
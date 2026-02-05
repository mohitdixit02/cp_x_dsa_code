#include <bits/stdc++.h>
using namespace std;
// Fenwick Tree implementation
// Problem - Given an array find the sum of elements for a given range in the query

class FenwickTree{
    private:
        vector <int> a; int n;
        int solveQuery(int i){
            int ans = 0;
            while(i > 0){
                ans += a[i];
                i -= (i & -i);
            }
            return ans;
        };
        void updateTree(int i, int val){
            while(i <= n){
                a[i] += val;
                i += (i & -i);
            }
        }
    public:
        FenwickTree(int x){
            n = x;
            a.assign(x + 1, 0);
        }
        int query(int l, int r){
            return solveQuery(r + 1) - solveQuery(l);
        }
        void build(vector <int> &arr){
            int n = arr.size();
            for(int i = 0; i < n; i++) updateTree(i + 1, arr[i]);
        }
        void update(int i, int val, vector<int> &arr){
            updateTree(i + 1, val - arr[i]);
        }
};

vector<int> solve(int n, vector<int>& arr, vector<vector<int>> &queries){
    int q = queries.size();
    vector<int> res(q, -1);
    FenwickTree ft(n);
    ft.build(arr);
    for(int i = 0; i < q; i++){
        if(queries[i][0] == 1){
            res[i] = ft.query(queries[i][1], queries[i][2]);
        }
        else{
            ft.update(queries[i][1], queries[i][2], arr);
        }
    }
    return res;
};

int main(){
    int n = 6;
    vector<int> arr = {2,1,0,4,3,7};
    vector<vector<int>> queries; // t1 l r , t2 i val
    queries.push_back({1,2,4}); // 7
    queries.push_back({1,1,3}); // 5
    queries.push_back({2,1,5}); // update
    queries.push_back({1,0,4}); // 14
    queries.push_back({1,5,5}); // 7
    queries.push_back({2,4,2}); // update
    queries.push_back({1,1,5}); // 18
    queries.push_back({1,3,5}); // 13
    vector <int> soln = {7,5,-1,14,7,-1,18,13};
    vector <int> res = solve(n, arr, queries);
    double correct = 0;
    for(int i = 0; i < queries.size(); i++){
        if(queries[i][0] == 1){
            if(soln[i] == res[i]){
                cout << "Q:" << (i + 1) << " - passed!!" << endl;
                correct++;
            }
            else{
                cout << "Q:" << (i + 1) << " - failed X " << "Expected: " << soln[i] << " Received: " << res[i] << endl;
            }
        }
    }
    cout << "Accuracy: " << (correct/6) * 100 << "%" << endl;
    return 0;
}

// Range Update part is missing
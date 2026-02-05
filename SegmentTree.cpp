#include <bits/stdc++.h>
using namespace std;
// Segment Tree implementation
// Problem - Given an array find the minimum element for a given range in the query

class SegmentTree{
    private:
        vector <int> a; int n;
        vector <bool> isLazy; vector <int> lazyVal;
        // Store lazy value and apply on themselves
        void applyLazyVal(int i, int l, int r, int val){
            if(l != r){ // Not a leaf node
                isLazy[i] = true;
                lazyVal[i] = val;
            }
            a[i] = lazyVal[i];
        }
        // propagate lazy value
        void propagateVal(int i, int l, int r){
            if(!isLazy[i]) return;
            isLazy[i] = false;
            int m = l + (r - l)/2;
            applyLazyVal(2*i + 1, l, m, lazyVal[i]);
            applyLazyVal(2*i + 1, m + 1, r, lazyVal[i]);
        }
        // l, r for building segments, i for storing in segment tree
        void buildArray(vector <int> &arr, int l, int r, int i){
            if(l == r) {
                a[i] = arr[l];
                return;
            }
            int m = l + (r - l)/2;
            buildArray(arr, l, m, 2*i + 1);
            buildArray(arr, m + 1, r, 2*i + 2);
            a[i] = min(a[2*i + 1], a[2*i + 2]);
        }
        // l, r for current segment, x, y for query range, i for current index in segment tree to retrieve value
        // We traverse into segment tree and pick the segments which lie in the query range
        int solveQuery(int x, int y, int i, int l, int r){
            if(y < l || x > r) return INT_MAX; // No overlap
            if(x <= l && r <= y) return a[i]; // complete overlap
            int m = l + (r - l)/2;
            propagateVal(i, l, r);
            return min(
                solveQuery(x, y, 2*i + 1, l, m),
                solveQuery(x, y, 2*i + 2, m + 1, r)
            );
        }
        void updateVal(int x, int y, int val, int i, int l, int r){
            if(x <= l && r <= y){
                applyLazyVal(i, l, r, val);
                a[i] = val;
                return;
            }
            if(y < l || x > r) return;
            propagateVal(i, l, r);
            int m = l + (r - l)/2;
            updateVal(x, y, val, 2*i + 1, l, m);
            updateVal(x, y, val, 2*i + 2, m + 1, r);
            a[i] = min(a[2*i + 1], a[2*i + 2]);
        }
    public:
        SegmentTree(int x){
            n = x;
            a.assign(4*x + 10, 0);
            isLazy.assign(4*x + 10, false);
            lazyVal.assign(4*x + 10, 0);
        }
        void build(vector <int> &arr){ 
            buildArray(arr, 0, n - 1, 0);
        }
        int query(int x, int y){ 
            return solveQuery(x, y, 0, 0, n - 1);
        };
        void update(int x, int y, int val){
            updateVal(x, y, val, 0, 0, n - 1);
        }
};

vector<int> solve(int n, vector<int>& arr, vector<vector<int>> &queries){
    int q = queries.size();
    vector<int> res(q, -1);
    SegmentTree st(n);
    st.build(arr);
    for(int i = 0; i < q; i++){
        if(queries[i][0] == 1){
            res[i] = st.query(queries[i][1], queries[i][2]);
        }
        else{
            st.update(queries[i][1], queries[i][2], queries[i][3]);
        }
    }
    return res;
};

int main(){
    int n = 6;
    vector<int> arr = {2,1,0,4,3,7};
    vector<vector<int>> queries; // t1 l r , t2 l r val
    queries.push_back({1,2,4}); // 0
    queries.push_back({1,1,3}); // 0
    queries.push_back({2,1,3,5}); // update
    queries.push_back({1,0,4}); // 2
    queries.push_back({1,5,5}); // 7
    queries.push_back({2,1,4,3}); // update
    queries.push_back({1,1,5}); // 3
    queries.push_back({1,3,5}); // 3
    vector <int> soln = {0,0,-1,2,7,-1,3,3};
    vector <int> res = solve(n, arr, queries);
    double correct = 0;
    for(int i = 0; i < queries.size(); i++){
        if(queries[i][0] == 1){
            if(soln[i] == res[i]){
                cout << "Q:" << (i + 1) << " - passed!!" << endl;
                correct++;
            }
            else{
                cout << "Q:" << (i + 1) << " - failed X" << endl;
            }
        }
    }
    cout << "Accuracy: " << (correct/6) * 100 << "%" << endl;
    return 0;
}

class SegmentTree{
    private:
        vector <int> a; int n;
        void buildArray(vector <int> &arr, int l, int r, int i){
            if(l == r) {
                a[i] = arr[l];
                return;
            }
            int m = l + (r - l)/2;
            buildArray(arr, l, m, 2*i + 1);
            buildArray(arr, m + 1, r, 2*i + 2);
            a[i] = max(a[2*i + 1], a[2*i + 2]);
        }
        int solveQuery(int x, int y, int i, int l, int r){
            if(y < l || x > r) return INT_MIN; // No overlap
            if(x <= l && r <= y) return a[i]; // complete overlap
            int m = l + (r - l)/2;
            return max(
                solveQuery(x, y, 2*i + 1, l, m),
                solveQuery(x, y, 2*i + 2, m + 1, r)
            );
        }
        void updateVal(int index, int val, int i, int l, int r){
            if(l == r){
                a[i] = val;
                return;
            }
            int m = l + (r - l)/2;
            if(index <= m) updateVal(index, val, 2*i + 1, l, m);
            else updateVal(index, val, 2*i + 2, m + 1, r);
            a[i] = max(a[2*i + 1], a[2*i + 2]);
        }
    public:
        SegmentTree(int x){
            n = x;
            a.assign(4*x + 10, 0);
        }
        void build(vector <int> &arr){ 
            buildArray(arr, 0, n - 1, 0);
        }
        int query(int x, int y){ 
            return solveQuery(x, y, 0, 0, n - 1);
        };
        void update(int i, int val){
            updateVal(i, val, 0, 0, n - 1);
        }
};
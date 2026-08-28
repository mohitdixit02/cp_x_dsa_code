/*
Q: Number of pairs of elements (i, j) such that i < j and arr[i] > arr[j].
*/
int mergeSort(vector<int>&arr, int l, int r){
    if(l >= r) return 0;
    int m = l + (r - l)/2;

    int count = 0;

    // Recursively Divide into Subarrays - Standard Divide
    // Count pairs when (i,j) belong to one half
    count += mergeSort(arr, l, m); // C1
    count += mergeSort(arr, m + 1, r); // C2

    // Count pairs when i in one and j in another half (cross pair) - Two Pointers/ Binary Search
    count += solveCrossPair(arr, l, m, r); // C3

    // In all three cases (i < j) is satisfied

    // Standard Sorting & Merge
    merge(arr, l, m, r);

    return count;
}

// Using Binary Search
int solveCrossPair(vector<int>&arr, int l, int m, int r){
    int count = 0;

    // For each left half element, do BS in right half to find count
    for(int i = l; i <= m; i++){
        int lp = m + 1;
        int rp = r;
        while(lp <= rp){
            int mp = lp + (rp - lp)/2;
            if(arr[mp] >= arr[i]){
                rp = mp - 1;
            }
            else{
                lp = mp + 1;
            }
        }
        count += (lp - m - 1);
    }
    return count;
}

// Using Two Pointers
int solveCrossPair(vector<int>&arr, int l, int m, int r){
    int count = 0;

    // Compare both halves and take count on condition using Two Pointers
    int lp = l;
    int rp = m + 1;
    while(lp <= m && rp <= r){
        if(arr[lp] > arr[rp]){
            count += (m - lp + 1);
            rp++;
        }
        else lp++;
    }
    return count;
}

void merge(vector<int>&arr, int l, int m, int r){
    // Standard Merge of Two Sorted Halfs
    int lp = l;
    int rp = m + 1;

    vector<int> t;
    while(lp <= m && rp <= r){
        if(arr[lp] <= arr[rp]){
            t.emplace_back(arr[lp]);
            lp++;
        }
        else{
            t.emplace_back(arr[rp]);
            rp++;
        }
    }
    while(lp <= m){
        t.emplace_back(arr[lp]);
        lp++;
    }
    while(rp <= r){
        t.emplace_back(arr[rp]);
        rp++;
    }
    for(int i = l; i <= r; i++){
        arr[i] = t[i - l];
    }
}

int inversionCount(vector<int> &arr)
{
    int n = arr.size();
    return mergeSort(arr, 0, n - 1);
}


// ********* Direct ****************
int mergeSort(vector<int>&arr, int l, int r){
    if(l >= r) return 0;
    int m = l + (r - l)/2;

    int count = 0;
    count += mergeSort(arr, l, m); // C1
    count += mergeSort(arr, m + 1, r); // C2

    count += solveCrossPair(arr, l, m, r); // C3
    merge(arr, l, m, r);

    return count;
}

int solveCrossPair(vector<int>&arr, int l, int m, int r){
    int count = 0;
    int lp = l;
    int rp = m + 1;
    while(lp <= m && rp <= r){
        if(arr[lp] > arr[rp]){
            count += (m - lp + 1);
            rp++;
        }
        else lp++;
    }
    return count;
}

void merge(vector<int>&arr, int l, int m, int r){
    int lp = l;
    int rp = m + 1;

    vector<int> t;
    while(lp <= m && rp <= r){
        if(arr[lp] <= arr[rp]){
            t.emplace_back(arr[lp]);
            lp++;
        }
        else{
            t.emplace_back(arr[rp]);
            rp++;
        }
    }
    while(lp <= m){
        t.emplace_back(arr[lp]);
        lp++;
    }
    while(rp <= r){
        t.emplace_back(arr[rp]);
        rp++;
    }
    for(int i = l; i <= r; i++){
        arr[i] = t[i - l];
    }
}

int inversionCount(vector<int> &arr)
{
    int n = arr.size();
    return mergeSort(arr, 0, n - 1);
}
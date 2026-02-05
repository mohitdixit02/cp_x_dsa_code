// Policy Based Data Structure
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

// for int data type
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

int main(){
    ordered_set x;
    x.insert(1);
    x.insert(2);
    x.insert(3);
    x.insert(5);
    x.insert(16);
    cout<<*x.find_by_order(3)<<endl; // returns iterator to element at index 2 (0 based & sorted) => 5
    cout<<x.order_of_key(6)<<endl;  // elements strictly smaller than 5 => 3
    return 0;
}

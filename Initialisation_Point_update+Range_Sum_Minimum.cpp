#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void build_tree(vector<int>& arr, vector<int>& segTree, int low, int high, int index) {
    if (low == high) {
        segTree[index] = arr[low];
        return;
    }
    int mid = (high+low) / 2;
    build_tree(arr, segTree, low, mid, 2 * index + 1);
    build_tree(arr, segTree, mid + 1, high, 2 * index + 2);
    segTree[index] = min(segTree[2 * index + 1], segTree[2 * index + 2]);
}

void updates(vector<int>& segTree, vector<int>& arr, int i, int new_val, int low, int high, int index) {
    if (low == high) {
        arr[i] = new_val;
        segTree[index] = new_val;
        return;
    }
    int mid = (high + low) / 2;
    if (i <= mid) updates(segTree, arr, i, new_val, low, mid, 2 * index + 1);
    else updates(segTree, arr, i, new_val, mid + 1, high, 2 * index + 2);
    segTree[index] = min(segTree[2 * index + 1], segTree[2 * index + 2]); 
}


int query(vector<int>& segTree, int x, int y, int low, int high, int index) {
    if (high < x || low > y) return INT_MAX;
    if (low >= x && high <= y) return segTree[index];
    int mid =(high + low) / 2;
    return min(query(segTree, x, y, low, mid, 2 * index + 1), query(segTree, x, y, mid + 1, high, 2 * index + 2));
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (auto &it : arr) cin >> it;
    vector<int> segTree(4 * n);
    build_tree(arr, segTree, 0, n-1 , 0);
   
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        int l, r;
        cin >> l >> r;
        l--;
        if (type==1) cout << query(segTree, l, r-1, 0, n - 1, 0) << endl;
        else updates(segTree, arr, l, r, 0, n - 1, 0);
    }
    return 0;
}

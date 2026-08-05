#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<long long> array, tree;
    int n;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = array[start];
            return;
        }
        int middle = (start + end) / 2;
        build(2*node, start, middle);
        build(2*node+1, middle + 1, end);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void update(int node, int start, int end, int index, long long value) {
        if (start == end) {
            array[index] = value;
            tree[node] = value;
            return;
        }
        int middle = (start + end) / 2;
        if (index <= middle) {
            update(2*node, start, middle, index, value);
        } else {
            update(2*node+1, middle + 1, end, index, value);
        }
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    long long query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) {
            return 0;
        }
        if (left <= start && end <= right) {
            return tree[node];
        }
        int middle = (start + end) / 2;
        return query(2*node, start, middle, left, right) + query(2*node+1, middle + 1, end, left, right);
    }
    public:
    SegmentTree(vector<long long>& input) {
        array = input;
        n = array.size();
        tree.assign(4*n, 0);
        build(1, 0, n - 1);
    }

    void update(int index, long long value) {
        update(1, 0, n - 1, index, value);
    }

    long long query(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        SegmentTree st(v);

        int q; cin >> q;
        while (q--) {
            int type; cin >> type;
            if (type == 1) {
                int index;
                long long value;
                cin >> index >> value;
                st.update(index, value);
            } else {
                int left, right;
                cin >> left >> right;
                cout << st.query(left, right) << '\n';
            }
        }
    }

    return 0;
}

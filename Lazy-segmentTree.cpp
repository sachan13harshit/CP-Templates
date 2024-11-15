class SegmentTree{
    public:
    vector<int> tree;
    vector<bool> lazy;
    vector<int> lazyValues;
    int N;
    SegmentTree(int n){
        tree.resize(4*n);
        lazy.resize(4*n);
        lazyValues.resize(4*n);
        N = n;
    }

    void propogate(int tid , int tl , int tr){
        if(!lazy[tid]){
            return;
        }
        if(tl != tr){
            lazyValues[2*tid+1] += lazyValues[tid];
            lazy[2*tid+1] = true;
            lazyValues[2*tid+2] += lazyValues[tid];
            lazy[2*tid+2] = true;
        }
        tree[tid] += lazyValues[tid];
        lazyValues[tid] = 0;
        lazy[tid] = false;
    }

    void update(int l , int r , int x){
        function<void(int,int,int)> f = [&](int tid , int tl , int tr){
            propogate(tid , tl , tr);
            if(tl > r || tr < l){
                return;
            }
            if(l <= tl && tr <= r){
                lazy[tid] = true;
                lazyValues[tid] += x;
                propogate(tid , tl , tr);
                return;
            }
            int tm = (tl + tr) / 2;
            f(2*tid + 1, tl, tm);
            f(2*tid + 2, tm + 1, tr);
            tree[tid] = min(tree[2*tid + 1], tree[2*tid + 2]);
        };
        f(0, 0, N-1);
    }

    int query(int l , int r){
        function<int(int,int,int)> f = [&](int tid , int tl , int tr){
            propogate(tid , tl , tr);
            if(tl > r || tr < l){
                return INT_MAX;
            }
            if(l <= tl && tr <= r){
                return tree[tid];
            }
            int tm = (tl + tr) / 2;
            return min(f(2*tid + 1, tl, tm), f(2*tid + 2, tm + 1, tr));
        };
        return f(0, 0, N-1);
    }
};

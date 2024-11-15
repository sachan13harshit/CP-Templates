struct DECOMPOSITION{
    V<int> arr;
    int n;
    V<int> sq;
    int bs;
    DECOMPOSITION(V<int>& a){
        arr = a;
        n = arr.size();
        bs = sqrt(n) + 1;
        sq.resize(bs*bs);
        for(int i=0;i<n;i++){
            sq[i] = arr[i];
        }
        for(int i=0;i<n;i+=bs){
           int s = i;
           int e = min((int)sq.size(),i+bs);
           sort(sq.begin()+s , sq.begin()+e);
        }
    }
    void update(int idx , int val){
        arr[idx] = val;
        int blockIdx = idx / bs;
        int s = blockIdx*bs;
        int e = min((int)sq.size(),s + bs);
        for(int i=s;i<e;i++){
            sq[i] = arr[i];
        }
        sort(sq.begin() + s , sq.begin()+e);
    }
    int query(int l , int r, int x){
        int ans = 0;
        for(int i=l;i<=r;++i){
            if(i % bs != 0  or i + bs - 1 > r ){
                if(arr[i] >= x){
                    ans++;
                }
            }
            else{
                int s = i;
                int e = i+ bs-1;
                int idx = -1;
                while(s <= e){
                    int mid = (s+e)/2;
                    if(sq[mid] >=x){
                        idx  = mid;
                        e = mid - 1;
                    }
                    else{
                        s = mid+1;
                    }
                }
                if(idx != -1){
                    ans+= i+ bs - idx;
                }
                i += bs -1;
            }
            
        }
        return ans;
    }
};

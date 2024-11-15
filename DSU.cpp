
struct DSU{
    vector<int> parent , size;
    DSU(int n){
        parent.assign(n,0);
        size.assign(n,1);
        for(int i=0;i<n;i++){
            parent[i] = i;
        }
    }
    int findRoot(int x){
        if(x==parent[x]){
            return x;
        }
        return parent[x] = findRoot(parent[x]);
    }
    void unite(int x, int y){
        x = findRoot(x);
        y = findRoot(y);
        if(x==y){
            return;
        }
        if(size[x]>size[y]){
            swap(x,y);
        }
        size[x]+=size[y];
        parent[y] = x;
    }
};

vector<int> level(n+1,0);
    function<void(int,int,int)> dfs = [&](int cur , int l, int p){
        parent[cur] = p;
        level[cur] = l;
        for(int nb : adj[cur]){
            if(nb==p){
                continue;
            }
            dfs(nb , l+1,cur);
        }
    };
    dfs(1,-1,-1);
vector<vector<int>> dp(32 , vector<int>(n+1,-1));
    dp[0] = parent;

    for(int i=1;i<32;i++){
        for(int j=1;j<=n;j++){
               int halfpath = dp[i-1][j];
               if(halfpath==-1){
                    continue;
               }
               dp[i][j]  =  dp[i-1][halfpath];
        }
    }
    
    auto getAncestor = [&](int node , int k){
        for(int i=31;i>=0;i--){
            if(k&(1<<i)){
                node = dp[i][node];
                if(node==-1){
                    break;
                }
            }
        }
        return node;
    };
    auto query = [&](int a , int b){
        if(level[a] < level[b]){
            swap(a,b);
        }
        if(level[a]!=level[b]){
            a = getAncestor(a , level[a] - level[b]);
        }
        if(a==b){
            return a;
        }
        for(int i=30;i>=0;i--){
            int a_new = dp[i][a];
            int b_new = dp[i][b];
            if(a_new != b_new){
                a = a_new;
                b = b_new;
            }
        }
        return dp[0][a];
    };

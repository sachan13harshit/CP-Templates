// 1st
vector<int> adj[N];
int downAns[50010][510] , upAns[50010][510];
int n , k;

void dfs1(int cur , int parent){
    downAns[cur][0] = 1;
    for(int nb : adj[cur]){
        if(nb == parent){
            continue;
        }
        dfs1(nb , cur);
        for(int j=1;j<=k;j++){
            downAns[cur][j] += downAns[nb][j-1];
        }
    }
}

int getDown(int node , int dist){
    if(dist < 0){
        return 0;
    }
    return downAns[node][dist];
}
int getUp(int node , int dist){
    if(dist<0){
        return 0;
    }
    return upAns[node][dist];
}

void dfs2(int cur , int parent){
    if(cur!=1){
        // upAns[cur][k] = downAns[parent][k-1] - downAns[cur][k-2];
        // upAns[cur][k] = getDown(parent,k-1) - getDown(cur , k-2) + getUp(parent,k-1);
        // upAns[cur][k-1] = getDown(parent,k-2) - getDown(cur , k-3) + getUp(parent,k-2);
        for(int j=1;j<=k;j++){
            upAns[cur][j] = getDown(parent,j-1) - getDown(cur , j-2) + getUp(parent,j-1);
        }
    }

    for(int nb : adj[cur]){
        if(nb == parent){
            continue;
        }
        dfs2(nb , cur);
    }
}

void harshit()
{
    cin >> n;
    cin >> k;
    // DownAns[i][j] - > count of nodes which are aat a , distance of j from node[i[ ]]
    // which are in subtree of a   

    for(int i=1;i<n;i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(1,0);
    dfs2(1,0);
    int ans = 0;
    for(int i=1;i<=n;i++){
        ans += (downAns[i][k] + upAns[i][k]);
    }
    cout << ans/2 << endl;

}



// 2nd 


int downAns[N][2] , upAns [N];
const int MX = 0 , SMX = 1;


void dfs1(int cur , int parent){
    downAns[cur][MX]= 1;
    downAns[cur][SMX] = 0;
    for(int nb : adj[cur]){
        if(nb==parent){
            continue;
        }
        dfs1(nb , cur);
        // downAns[cur] = max(downAns[cur] , 1 + downAns[nb]);
        int curans = 1 + downAns[nb][MX];
        if(curans > downAns[cur][MX]){
            downAns[cur][SMX] = downAns[cur][MX];
            downAns[cur][MX] = curans;
        }
        else if(curans > downAns[cur][SMX]){
            downAns[cur][SMX] = curans;
        }
    }
}


void dfs2(int cur , int parent){
    if(cur!=1){
        upAns[cur] =  1+ upAns[parent];
        if(downAns[parent][MX] == 1 + downAns[cur][MX]){
            upAns[cur] = max(upAns[cur] , 1 + downAns[parent][SMX]);
        }
        else{
         upAns[cur] = max(upAns[cur] , 1 + downAns[parent][MX]);

        }

    }
    for(int nb : adj[cur]){
        if(nb == parent){
            continue;
        }
        dfs2(nb , cur);
    }
}

void harshit()
{
    int n;
    cin >> n;
    // vector<int> adj[n+1];
    for(int i=1;i<n;i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        cout << max(downAns[i][MX] , upAns[i]) - 1 << " ";
    }
    cout << endl;
}


// 3rd 

vector<int> adj[N];
int downAns[N] , upAns[N];
int Size[N];
int n;


void dfs1(int cur , int parent){
    Size[cur]++;
    for(int nb : adj[cur]){
        if(nb == parent){
            continue;
        }
        dfs1(nb , cur);
        Size[cur] += Size[nb];
        downAns[cur] += downAns[nb] + Size[nb];
    }
}

void dfs2(int cur , int parent){
    if(cur!=1){
        int parentAns = downAns[parent] + upAns[parent];
        int parentwithoutcur = parentAns - (downAns[cur] + Size[cur]);
        upAns[cur] = parentwithoutcur + n - Size[cur];
    }
    for(int nb : adj[cur]){
        if(nb==parent){
            continue;
        }
        dfs2(nb , cur);
    }
}

void harshit()
{
 
    cin >> n;
    for(int i=1;i<n;i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        cout << downAns[i] + upAns[i] << " ";
    }
    cout << endl;
}


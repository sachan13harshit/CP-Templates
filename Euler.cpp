int Tin[M] , Tout[M];
int timer  = 0 ;
vector<int> tour;
void dfs(int cur , int parent , vector<int> A[], vector<int>& B){
    Tin[cur] = timer++;
    tour.push_back(B[cur]);
    for(int nb : A[cur]){
        if(nb!=parent){
            dfs(nb , cur , A,B);
        }
    }
    tour.push_back(B[cur]);
    Tout[cur] = timer++;
}



// 2nd way


 V<int> tin(n) , tout(n) , tour , level(n);
    int timer = 0;
    function<void(int,int,int)> dfs = [&](int cur , int parent , int l){
        tin[cur] = timer++;
        tour.push_back(cur);
        level[cur] = l;
        for(int nb : A[cur]){
            if(nb!=parent){
                dfs(nb , cur , l+1);
            }
        }
        tour.push_back(B[cur]);
        tout[cur] = timer++;
    };

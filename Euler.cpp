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

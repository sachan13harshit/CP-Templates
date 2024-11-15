int power(int x , int n , int mod){
    if(n==0){
        return 1;
    }
    if(n%2==1){
        return (power(x,n-1,mod)*x) % mod;
    }
    int ans = power(x , n/2 , mod);
    return (ans*ans) % mod;
}
int modInv(int x , int mod){
    return power(x , mod -2 , mod);
}
class Hash{
    const int p1 = 31 , p2 = 37;
    int mod1 = 1e9+7 , mod2 = 1e9+9;
    vector<int> arr1 , arr2;
    vector<int> modInv1 , modInv2;
    public:
        Hash(string &s){
            int n = s.size();
            arr1.resize(n);
            arr2.resize(n);
            modInv1.resize(n);
            modInv2.resize(n);
            int pow1 = 1 , pow2 = 1;
            for(int i=0; i<n; i++){
                arr1[i] = ((s[i]-'a' + 1) * pow1) % mod1;
                arr2[i] = ((s[i]-'a' + 1) * pow2) % mod2;
                pow1 *= p1;
                pow1 %= mod1;
                pow2 *= p2;
                pow2 %= mod2;
            }
            for(int i=1; i<n; i++){
                arr1[i] += arr1[i-1];
                arr1[i] %= mod1;
                arr2[i] += arr2[i-1];
                arr2[i] %= mod2;
            }
            pow1 = modInv(p1, mod1);
            pow2 = modInv(p2, mod2);
            modInv1[0] = 1;
            modInv2[0] = 1;
            for(int i=1; i<n; i++){
                modInv1[i] = (modInv1[i-1] * pow1) % mod1;
                modInv2[i] = (modInv2[i-1] * pow2) % mod2;
            }
        }

        pair<int,int> substr(int l , int r){
            if(r >= arr1.size()){
                return {-1, -1};
            }
            int ans1 = arr1[r] - (l ? arr1[l-1] : 0);
            ans1 += mod1;
            ans1 %= mod1;
            int ans2 = arr2[r] - (l ? arr2[l-1] : 0);
            ans2 += mod2;
            ans2 %= mod2;
            ans1 *= modInv1[l];
            ans1 %= mod1;
            ans2 *= modInv2[l];
            ans2 %= mod2;
            return {ans1, ans2};
        }
};

#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=35;
int n,q;
bitset<maxn*maxn> bs[maxn][maxn],S;
int main(){
    scanf("%d%d",&n,&q);
    bs[0][0].set(0);
    for(int i=2;i<=n;i++)
        for(int j=2;j<=n;j++)
            for(int u=2;u<=i;u++)
                for(int v=2;v<=j;v++){
                    bs[i][j]|=bs[i-u][j-v]<<(u*v);
                    // for(int l=u*v;l<=n*n;l++)
                    //     if(bs[i-u][j-v][l-u*v]) bs[i][j].set(l);
                }
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)   S|=bs[i][j];
    while(q--){
        int x;scanf("%d",&x);
        puts(S[n*n-x]?"Yes":"No");
    }
}
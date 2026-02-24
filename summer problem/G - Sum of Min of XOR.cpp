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
const int maxn=2e5+10;
int n,m;
ll ans=0;
const int lgV=30;
struct Trie{
    int tot;
    int nex[maxn*lgV][2];
    void ins(int x){
        int p=0;
        for(int i=lgV;~i;i--){
            bool o=x&(1<<i);
            int &t=nex[p][o];
            if(!t)  t=++tot;
            p=t;
        }
    }
    void dfs(int d,int p,int r,int k){
        if(!~d)  return;
        int R=(1ll<<d+1)-1,RR=(1<<d)-1;
        r&=R;
        if(nex[p][0]&&(nex[p][1]||r<(1<<d))){
            if(r>=(1<<d))   dfs(d-1,nex[p][0],R,k),dfs(d-1,nex[p][1],r,k);
            else    dfs(d-1,nex[p][0],r,k);
            return;
        }
        if(!nex[p][0]){
            ans+=1ll*min(r+1,1<<d)*(1<<d)*k;
            if(r>=(1<<d)){
                if((r&RR)==(R&RR))  dfs(d-1,nex[p][1],R,k+k);
                else dfs(d-1,nex[p][1],R,k),dfs(d-1,nex[p][1],r,k);
            }
            else    dfs(d-1,nex[p][1],r,k);
            return;
        }
        if(!nex[p][1]){
            ans+=1ll*(r-(1<<d)+1)*(1<<d)*k;
            if((r&RR)==(R&RR))  dfs(d-1,nex[p][0],R,k+k);
            else dfs(d-1,nex[p][0],R,k),dfs(d-1,nex[p][0],r,k);
            return;
        }
    }
}T;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        T.ins(x);
    }
    T.dfs(lgV,0,m-1,1);
    printf("%lld\n",ans);
}
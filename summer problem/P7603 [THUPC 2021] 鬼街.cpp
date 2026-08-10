#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10;
const ll INF=1e18;
int n,q,Q;
bool ntpri[maxn];
vector<int> pri,fac[maxn],ans;
bool vis[maxn];
ll cnt[maxn],val[maxn];
int pos[maxn];
priority_queue<pli,vector<pli>,greater<pli>> pq[maxn];
void init(){
    for(int i=2;i<=n;i++){
        if(!ntpri[i])   pri.eb(i);
        for(int j:pri){
            if(1ll*i*j>n)   break;
            ntpri[i*j]=true;
            if(i%j==0)  break;
        }
    }
    for(int i=1;i<=n;i++){
        int x=i;
        for(int j:pri){
            if(1ll*j*j>x)   break;
            if(x%j==0){
                fac[i].eb(j);
                while(x%j==0)   x/=j;
            }
        }
        if(x^1) fac[i].eb(x);
    }
}
vector<int> vec;
unordered_map<int,ll> mn[maxn];
inline void chk(int x){
    if(vis[x])  return;
    ll v=val[x];int p=pos[x];
    // printf("# %d %d %d\n",x,v,p);
    for(int i:fac[p])   v-=cnt[i];
    if(v<=0)    return ans.eb(x),vis[x]=true,void();
    int siz=fac[p].size();
    for(int i:fac[p]){
        if(Q==maxn-10)  pq[i].ep((v+siz-1)/siz+cnt[i],x);
        else{
            vec.eb(i);
            if(mn[i].find(x)==mn[i].end())  mn[i][x]=(v+siz-1)/siz+cnt[i];
            else mn[i][x]=min(mn[i][x],(v+siz-1)/siz+cnt[i]);
        }
    }
}
void check(int x){
    while(!pq[x].empty()){
        ll w=pq[x].top().fi;int i=pq[x].top().se;
        if(w>cnt[x])    break;
        pq[x].pop();chk(i);
    }
}
int main(){
    scanf("%d%d",&n,&q);Q=q;
    init();
    int lst=0,tot=0;
    while(q--){
        int op,x;ll y;scanf("%d%d%lld",&op,&x,&y);
        y^=lst;
        if(!op){
            for(int i:fac[x])   cnt[i]+=y,check(i);
            for(int i:vec){
                for(auto [j,k]:mn[i])   pq[i].ep(k,j);
                mn[i].clear();
            }
            vec.clear();
            sort(ans.begin(),ans.end());
            printf("%d ",lst=ans.size());
            for(int i:ans)  printf("%d ",i);puts("");
            ans.clear();
        }
        else{
            for(int i:fac[x])   y+=cnt[i];
            pos[++tot]=x;val[tot]=y;
            chk(tot);
            for(int i:vec){
                for(auto [j,k]:mn[i])   pq[i].ep(k,j);
                mn[i].clear();
            }
            vec.clear();
        }
    }
}
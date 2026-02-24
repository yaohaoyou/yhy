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
const int maxn=510,V=500*5000,maxV=(V<<1)+10;
int n,m,k;
bool used[maxn];
pii fr[maxV];
pii a[maxn],b[maxn];
vector<pair<pii,pii>> v;
bitset<maxV> dp,tmp,bs;
void solve(){
    v.clear();
    while(m--){
        sort(a+1,a+n+1);
        int p=0;
        for(int i=1;i<=n;i++)if(a[i].fi){p=i;break;}
        if(a[p].fi>=k){a[p].fi-=k;v.eb(pii(a[p].se,k),pii(0,0));}
        else{v.eb(pii(a[p].se,a[p].fi),pii(a[n].se,k-a[p].fi));a[n].fi-=(k-a[p].fi);a[p].fi=0;}
    }
    for(auto i:v){
        printf("%d %d",i.fi.fi,i.fi.se);
        if(i.se.fi) printf(" %d %d",i.se.fi,i.se.se);
        puts("");
    }
}
void matt(){
    v.clear();
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].fi),a[i].se=i;
    while(m>n-1){
        sort(a+1,a+n+1);
        a[n].fi-=k;v.eb(pii(a[n].se,k),pii(0,0));
        m--;
    }
    for(auto i:v){
        printf("%d %d",i.fi.fi,i.fi.se);
        if(i.se.fi) printf(" %d %d",i.se.fi,i.se.se);
        puts("");
    }
    if(m==n-1)  solve();
    else{
        dp.reset();dp.set(V);
        for(int i=0;i<=V+V;i++)   fr[i].fi=0;
        for(int i=1;i<=n;i++)   a[i].fi=k-a[i].fi;
        // for(int i=1;i<=n;i++)   printf("%d ",a[i].fi);puts("");
        for(int i=1;i<=n;i++){
            if(a[i].fi<0)   bs=dp|dp>>-a[i].fi;
            else bs=dp|dp<<a[i].fi;
            tmp=dp^bs;
            for(int j=tmp._Find_first();j<=V+V;j=tmp._Find_next(j))   fr[j]=pii(j-a[i].fi,a[i].se);
            swap(bs,dp);
        }
        for(int i=1;i<=n;i++)   a[i].fi=k-a[i].fi;
        if(!dp[V+k])  puts("-1");
        else{
            vector<int> vec;vec.clear();
            int p=V+k;
            while(p^V){
                vec.eb(fr[p].se);
                p=fr[p].fi;
            }
            for(int i=1;i<=n;i++)b[i]=a[i];int N=n;n=0;
            for(int i:vec)  used[i]=true,a[++n]=b[i];
            m=n-1;solve();
            n=0;for(int i=1;i<=N;i++)if(!used[i])a[++n]=b[i];else used[i]=false;
            m=n-1;solve();
        }
    }
}
int main(){int T;scanf("%d",&T);while(T--)matt();}
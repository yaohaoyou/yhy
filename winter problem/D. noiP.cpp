#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e6+10,maxk=55;
int n,a,b,c;
pii pf[maxn],pg[maxn],ph[maxn];
bool ntp[maxn];
ll F[maxn],G[maxn];
unordered_map<ll,ll> H;
vector<int> p;
vector<pii> fac[maxn];
void seive(){
    F[1]=G[1]=H[1]=1;
    for(int i=2;i<=n;i++){
        if(!ntp[i]) p.eb(i);
        for(int j:p){
            if(1ll*i*j>n)   break;
            ntp[i*j]=true;
            if(i%j==0)  break;
        }
    }
    for(int i=2;i<=n;i++){
        // printf("F[%d] = %d\n",i,F[i]);
        for(int j:p){
            if(j>i||1ll*i*j>n)  break;
            if(i%j==0){
                int x=i,y=j;while(x%j==0)x/=j,y*=j;
                F[i*j]=F[x]*F[y];
                G[i*j]=G[x]*G[y];
                H[i*j]=H[x]*H[y];
                break;
            }
            F[i*j]=F[i]*F[j];
            G[i*j]=G[i]*G[j];
            H[i*j]=H[i]*H[j];
        }
    }
    for(int i:p)
        for(ll j=i,c=1;j<=n;j*=i,c++)
            for(int k=j,l=1;k<=n;k+=j,l++)
                if(l%i) fac[k].eb(i,c);
    // for(int i=1;i<=n;i++){
    //     printf("%d : ",i);
    //     for(auto [j,k]:fac[i])   printf("(%d,%d) ",j,k);
    //     puts("");
    // }
}
inline ll Hsqr(int x){
    ll res=1;
    for(auto [i,j]:fac[x]){
        ll c=1,t=j+j;while(t--)c*=i;
        res*=H[c];
    }
    return res;
}
vector<pli> vec;
void matt(int _cases){
    p.clear();for(int i=0;i<=n;i++)ntp[i]=F[i]=G[i]=0,fac[i].clear();H.clear();
    scanf("%d%d%d%d",&n,&a,&b,&c);
    for(int i=1;i<=a;i++){
        scanf("%d%d",&pf[i].fi,&pf[i].se);
        ll x=pf[i].fi;
        for(int j=1;j<=pf[i].se;j++){
            if(!x)  scanf("%*d");
            else scanf("%d",&F[x]);
            if(x*pf[i].fi>n)  x=0;
            x*=pf[i].fi;
        }
    }
    for(int i=1;i<=b;i++){
        scanf("%d%d",&pg[i].fi,&pg[i].se);
        ll x=pg[i].fi;
        for(int j=1;j<=pg[i].se;j++){
            if(!x)  scanf("%*d");
            else scanf("%d",&G[x]);
            if(x*pg[i].fi>n)  x=0;
            x*=pg[i].fi;
        }
    }
    for(int i=1;i<=c;i++){
        scanf("%d%d",&ph[i].fi,&ph[i].se);
        ll x=pg[i].fi;
        for(int j=1;j<=ph[i].se;j++){
            if(!x)  scanf("%*d");
            else scanf("%d",&H[x]);
            if(LL(x)*ph[i].fi>1ll*n*n)  x=0;
            x*=ph[i].fi;
        }
    }
    seive();
    ll ans=0,sum=1ll*n*n;
    for(int d=1;d<=n;d++){
        ll hd=Hsqr(d);
        if(!hd) continue;
        // printf("%d %d %d : ",d,hd,H[d*d]);
        vec.clear();
        for(int x=1;x*d<=n;x++) vec.eb(G[x*d]*H[x],x);
        // puts("");
        // sort(vec.begin(),vec.end(),greater<pli>());
        // for(int x=1;x*d<=n;x++){
        //     for(int j=0;j<vec.size();j++){
        //         ll res=vec[j].fi*F[x*d]*H[x]*hd;
        //         if(res<ans) break;
        //         if(__gcd(x,vec[j].se)==1){
        //             if(res>ans) ans=res,sum=0;
        //             if(res==ans)    sum++;
        //         }
        //     }
        // }
        for(int x=1;x*d<=n;x++){
            for(int y=1;y*d<=n;y++)if(__gcd(x,y)==1&&__gcd(x,d)==1&&__gcd(y,d)==1){
                ll res=F[x*d]*H[x]*G[y*d]*H[y]*hd;
                if(res>ans) ans=res,sum=0;
                if(res==ans)    sum++;
                if(res==432)    printf("S(%d,%d) %d %d %d\n",x*d,y*d,x,y,d);
            }
        }
    }
    printf("%lld %lld\n",ans,sum);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
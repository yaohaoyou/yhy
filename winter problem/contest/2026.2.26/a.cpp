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
const int maxn=5e5+10;
int n,q;ll k;
ll a[maxn];
mt19937 matt(202602);
namespace FHQTreap{
    int rt;
    int tot;
    ll rd[maxn],tag[maxn],val[maxn];
    int ls[maxn],rs[maxn],siz[maxn];
    inline int nd(ll x){int p=++tot;val[p]=x;rd[p]=matt();tag[p]=ls[p]=rs[p]=0;siz[p]=1;return p;}
    inline void pu(int p){siz[p]=(ls[p]?siz[ls[p]]:0)+(rs[p]?siz[rs[p]]:0)+1;}
    inline void pt(int p,ll s){tag[p]+=s;val[p]+=s;}
    inline void pd(int p){if(tag[p]){if(ls[p])pt(ls[p],tag[p]);if(rs[p])pt(rs[p],tag[p]);tag[p]=0;}}
    int merge(int x,int y){
        if(!x||!y)  return x|y;
        pd(x);pd(y);
        if(rd[x]>rd[y]) return rs[x]=merge(rs[x],y),pu(x),x;
        return ls[y]=merge(x,ls[y]),pu(y),y;
    }
    void split(int p,int v,int &x,int &y){
        if(!p)  return x=y=0,void();
        pd(p);
        if(v<=siz[ls[p]])   split(ls[p],v,x,ls[y=p]);
        else    split(rs[p],v-siz[ls[p]]-1,rs[x=p],y);
        int sz=siz[p];
        pu(p);
        // if(siz[p]!=sz)  printf("nb on %d\n",p);
    }
    void splitval(int p,ll v,int &x,int &y){
        if(!p)  return x=y=0,void();
        pd(p);
        if(v<val[p])    splitval(ls[p],v,x,ls[y=p]);
        else    splitval(rs[p],v,rs[x=p],y);
        pu(p);
    }
    inline ll getmn(){
        int x,y;
        split(rt,1,x,y);
        ll ret=val[x];
        rt=merge(x,y);
        return ret;
    }
    // void print(int p){pd(p);if(ls[p])print(ls[p]);int sz=siz[p];if(rs[p])print(rs[p]);pu(p);assert(siz[p]==sz);if(p==rt)puts("");}
    void print(int p){
        pd(p);
        printf("%d : %d %d %d\n",p,ls[p],rs[p],siz[p]);
        if(ls[p])print(ls[p]);
        int sz=siz[p];
        if(rs[p])print(rs[p]);
        pu(p);
        if(sz!=siz[p])  printf("nboj on %d\n",p);
        if(p==rt)puts("");
    }
}
using namespace FHQTreap;
int main(){
    freopen("a.in","r",stdin);freopen("a.out","w",stdout);
    scanf("%d%d%lld",&n,&q,&k);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    int p=n;while(p&&a[n]-a[p]<k) rt=merge(nd(a[p--]),rt);
    while(q--){
        char op[5];ll x;scanf("%s%lld",op,&x);
        if(op[0]=='A'){
            if(tot>=x){
                int p,q,r;
                split(rt,tot-x+1,p,r);
                split(p,tot-x,p,q);
                printf("%lld\n",val[q]);
                rt=merge(merge(p,q),r);
            }
            else    printf("%lld\n",a[n-x+1]);
        }
        else{
            while(x){
                ll t=(getmn()-a[p])/k,ct=t*tot;
                if(p&&ct<=x){
                    x-=ct;pt(rt,-t*k);
                    int a,b;splitval(rt,::a[p]+k-1,a,b);
                    if(x>=siz[b]){
                        x-=siz[b];pt(b,-k);
                        rt=merge(nd(::a[p]),merge(b,a));
                        p--;
                    }
                    else{
                        rt=merge(a,b);
                        split(rt,tot-x,a,b);
                        pt(b,-k);
                        rt=merge(b,a);x=0;
                    }
                }
                else{
                    t=x/tot;ct=x%tot;
                    pt(rt,-t*k);
                    int a,b;split(rt,tot-ct,a,b);
                    pt(b,-k);
                    rt=merge(b,a);
                    x=0;
                }
            }
        }
    }
}
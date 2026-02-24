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
int n,m,q;
int l[maxn],r[maxn],v[maxn];
ll ans[maxn];
vector<pii> Q[maxn];
struct BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ll s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return que(r)-que(l-1);}
}T;
struct odt{
    int l,r,t,v;odt(int x=0,int y=0,int z=0,int w=0){l=x;r=y;t=z;v=w;}
    inline bool operator<(odt x)const{return l<x.l;}
};
set<odt> s;
inline auto split(int p){
    auto it=s.lower_bound(odt(p));
    if(it!=s.end()&&it->l==p)   return it;
    if(it==s.begin()) return s.end();
    it--;
    if(it->r<p) return s.end();
    int l=it->l,r=it->r,t=it->t,v=it->v;
    s.erase({l,r,t,v});s.ep(l,p-1,t,v);
    return s.ep(p,r,t,v).fi;
}
inline void assign(int cl,int cr,int ct,int cv){
    auto itr=split(cr+1),itl=split(cl);
    for(auto i=itl;i!=itr;i++){
        auto [l,r,t,v]=*i;
        if(t)T.add(t,-1ll*(r-l+1)*v);
    }
    s.erase(itl,itr);
    s.ep(cl,cr,ct,cv);
    T.add(ct,1ll*(cr-cl+1)*cv);
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)   scanf("%d%d%d",&l[i],&r[i],&v[i]);
    for(int i=1;i<=q;i++){int L,R;scanf("%d%d",&L,&R);Q[R].eb(L,i);}
    s.ep(0,m+1,0,0);
    for(int i=1;i<=n;i++){
        assign(l[i],r[i],i,v[i]);
        for(auto [j,id]:Q[i])   ans[id]=T.query(j,i);
    }
    for(int i=1;i<=q;i++)   printf("%lld\n",ans[i]);
}
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
const ll INF=1e18;
int n,m;
int a[maxn],b[maxn];
ll tag;
struct node{
    int l,r;ll x;bool o;
    node(int l1=0,int r1=0,ll x1=0,bool o1=0){l=l1;r=r1;x=x1;o=o1;}
    inline bool operator<(node x)const{return l<x.l;}
};
set<node> s;
inline ll get(int x){auto it=s.upper_bound(node(x,m,INF,1));assert(it!=s.begin());it--;return (it->o?it->x+(x-it->l):it->x)+tag;}
inline set<node>::iterator split(int x){
    auto it=s.upper_bound(node(x,m,INF,1));
    assert(it!=s.begin());
    it--;
    if(x==it->r)    return it;
    int l=it->l,r=it->r;ll x1=it->x,x2=x1+(x+1-l)*it->o;bool o=it->o;
    s.erase(it);
    s.ep(x+1,r,x2,o);
    return s.ep(l,x,x1,o).fi;
}
void matt(int _cases){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    s.clear();s.ep(1,m,1,1);tag=0;
    for(int i=1;i<=n;i++){
        int l=1,r=m,p=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(get(mid)+b[i]<=a[i]) p=mid,l=mid+1;
            else r=mid-1;
        }
        tag+=b[i];
        if(p){
            auto itr=split(p);
            s.erase(s.begin(),++itr);
            s.ep(1,p,a[i]-tag,0);
        }
    }
    auto sum=[&](ll l,ll r){return (l+r)*(r-l+1)/2;};
    ll ans=0;
    for(auto [l,r,x,o]:s){
        if(!o)  ans+=(x+tag)*(r-l+1);
        else    ans+=sum(x+tag,x+tag+r-l);
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
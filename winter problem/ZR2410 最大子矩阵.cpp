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
int n;
pii a[maxn];
set<pii> s;
struct line{int k;ll b;ll get(int x){return 1ll*k*x+b;}};
inline bool cmp(line a,line b,int x){return a.get(x)<b.get(x);}
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    line tr[maxn<<2];
    void upd(setpos,line x){
        // debug("%d %d %d\n",p,l,r);
        setmid;line &v=tr[p];
        if(!cmp(x,v,mid))   swap(x,v);
        if(l==r)    return;
        if(!cmp(x,v,l)) return upd(lson,x);
        if(!cmp(x,v,r)) return upd(rson,x);
    }
    void upd(setpos,int pl,int pr,line x){if(l>=pl&&r<=pr)return upd(p,l,r,x);setmid;if(pl<=mid)upd(lson,pl,pr,x);if(pr>mid)upd(rson,pl,pr,x);}
    inline ll query(int x){ll res=0;int p=1,l=1,r=n;while(l^r){gmx(res,tr[p].get(x));setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}gmx(res,tr[p].get(x));return res;}
}T[2];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].fi),a[i].se=i;
    sort(a+1,a+n+1,greater<pii>());
    for(int i=1;i<=n;i++){
        int x=a[i].se,l=x,r=x;
        auto it=s.lower_bound(pii(x,0));
        if(it!=s.end()){
            if(it->fi==x+1) r=it->se,it=s.erase(it);
        }
        if(it!=s.begin()){
            it--;
            if(it->se==x-1) l=it->fi,s.erase(it);
        }
        s.ep(l,r);
        ll w=1ll*(r-l+1)*a[i].fi;
        T[0].upd(all,r,n,(line){0,w});T[1].upd(all,1,l,(line){0,w});
        T[0].upd(all,1,r,(line){a[i].fi,w-1ll*a[i].fi*r});T[1].upd(all,l,n,(line){-a[i].fi,w+1ll*a[i].fi*l});
    }
    for(int i=1;i<=n;i++)   printf("%lld\n",max(T[0].query(i-1),T[1].query(i+1)));
}
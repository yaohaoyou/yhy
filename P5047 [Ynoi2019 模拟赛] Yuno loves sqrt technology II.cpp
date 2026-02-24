#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10,B=512,maxB=B+10,maxnB=maxn/B+10;
int n,q,m;
int a[maxn],b[maxn];
int pref[maxn],sufg[maxn];
void discrete(){
    for(int i=1;i<=n;i++)   b[i]=a[i];
    sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+m+1,a[i])-b;
}
ll ans;
ll out[maxn],res[maxn];
inline void modifyL(int x,int t){ans+=t*sufg[x];}
inline void modifyR(int x,int t){ans+=t*pref[x];}
struct ques{int l,r,id,ans;}Q[maxn];
struct node{int l,r,id,o;};
vector<node> vf[maxn],vg[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void clear(){mems(tr,0);}
    inline void add(int x,int s){while(x<=m){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
}T;
struct BlockArray{
    int id[maxn],tag[maxnB],sum[maxn];
    inline void init(){for(int i=1;i<=m;i++)id[i]=(i-1)/B+1;}
    inline void clear(){mems(tag,0);mems(sum,0);}
    inline void upd(int l,int r,int s){
        if(l>r) return;
        int idl=id[l],idr=id[r];
        if(idl==idr){
            for(int i=l;i<=r;i++)   sum[i]+=s;
            return;
        }
        while(idl==id[l])    sum[l++]+=s;
        while(idr==id[r])    sum[r--]+=s;
        for(int i=idl+1;i<idr;i++)  tag[i]+=s;
    }
    inline int que(int x){return tag[id[x]]+sum[x];}
    inline void add(int x,int s){upd(x,m,s);}
    inline int query(int l,int r){return l<=r?que(r)-que(l-1):0;}
}Block;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    discrete();
    Block.init();
    for(int i=1;i<=n;i++){pref[i]=Block.query(a[i]+1,m);Block.add(a[i],1);}
    Block.clear();
    for(int i=n;i;i--){sufg[i]=Block.query(1,a[i]-1);Block.add(a[i],1);}
    Block.clear();
    for(int i=1;i<=q;i++){scanf("%d%d",&Q[i].l,&Q[i].r);Q[i].id=i;}
    sort(Q+1,Q+q+1,[&](ques x,ques y){return x.l/B==y.l/B?((x.l/B)&1)^(x.r>y.r):(x.l<y.l);});
    for(int i=1,l=1,r=0;i<=q;i++){
        int ql=Q[i].l,qr=Q[i].r;
        if(l>ql)    vg[r+1].eb(ql,l-1,i,-1);
        while(l>ql) modifyL(--l,1);
        if(r<qr)    vf[l-1].eb(r+1,qr,i,-1);
        while(r<qr) modifyR(++r,1);
        if(l<ql)    vg[r+1].eb(l,ql-1,i,1);
        while(l<ql) modifyL(l++,-1);
        if(r>qr)    vf[l-1].eb(qr+1,r,i,1);
        while(r>qr) modifyR(r--,-1);
        out[Q[i].id]=ans;
    }
    for(int i=1;i<=n;i++){
        Block.add(a[i],1);
        for(auto [l,r,id,o]:vf[i])
            for(int j=l;j<=r;j++)
                res[id]+=o*Block.query(a[j]+1,m);
    }
    Block.clear();
    for(int i=n;i;i--){
        Block.add(a[i],1);
        for(auto [l,r,id,o]:vg[i])
            for(int j=l;j<=r;j++)
                res[id]+=o*Block.query(1,a[j]-1);
    }
    for(int i=1;i<=q;i++){res[i]+=res[i-1];out[Q[i].id]+=res[i];}
    for(int i=1;i<=q;i++)   printf("%lld\n",out[i]);
}
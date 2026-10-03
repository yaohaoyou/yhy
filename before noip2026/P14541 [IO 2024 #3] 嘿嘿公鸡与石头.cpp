#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
bool mem1;
const int maxn=1e6+10;
const int INF=2e9;
int n,m;
pii a[maxn];
piii b[maxn];
int out[maxn];

struct SGT{
    int mx[maxn<<2],idmin[maxn<<2],lazy[maxn<<2];
    inline void pu(int p){
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
        idmin[p]=min(idmin[p<<1],idmin[p<<1|1]);
    }
    inline void pd(int p){
        if(lazy[p]){
            int v=lazy[p];
            mx[p<<1]+=v; lazy[p<<1]+=v;
            mx[p<<1|1]+=v; lazy[p<<1|1]+=v;
            lazy[p]=0;
        }
    }
    void build(int p,int l,int r){
        lazy[p]=0;
        if(l==r){
            mx[p]=a[l].fi;
            idmin[p]=a[l].se;
            return;
        }
        int mid=(l+r)>>1;
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
        pu(p);
    }
    void add(int p,int l,int r,int ql,int qr,int v){
        if(ql>r||qr<l) return;
        if(ql<=l&&r<=qr){
            mx[p]+=v;
            lazy[p]+=v;
            return;
        }
        pd(p);
        int mid=(l+r)>>1;
        if(ql<=mid) add(p<<1,l,mid,ql,qr,v);
        if(qr>mid) add(p<<1|1,mid+1,r,ql,qr,v);
        pu(p);
    }
    int QF(int p,int l,int r,int x){
        if(mx[p]<x) return n+1;
        if(l==r) return l;
        pd(p);
        int mid=(l+r)>>1;
        if(mx[p<<1]>=x) return QF(p<<1,l,mid,x);
        else return QF(p<<1|1,mid+1,r,x);
    }
    int QFG(int p,int l,int r,int x){
        if(mx[p]<=x) return n+1;
        if(l==r) return l;
        pd(p);
        int mid=(l+r)>>1;
        if(mx[p<<1]>x) return QFG(p<<1,l,mid,x);
        else return QFG(p<<1|1,mid+1,r,x);
    }
    int query_point(int p,int l,int r,int pos){
        if(l==r) return mx[p];
        pd(p);
        int mid=(l+r)>>1;
        if(pos<=mid) return query_point(p<<1,l,mid,pos);
        else return query_point(p<<1|1,mid+1,r,pos);
    }
    int QMN(int p,int l,int r,int ql,int qr){
        if(ql>r||qr<l) return INF;
        if(ql<=l&&r<=qr) return idmin[p];
        int mid=(l+r)>>1;
        return min(QMN(p<<1,l,mid,ql,qr), QMN(p<<1|1,mid+1,r,ql,qr));
    }
}T;

bool mem2;
int main(){
    freopen("bean.in","r",stdin);freopen("bean.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].fi),a[i].se=i;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)   scanf("%d%d",&b[i].fi.fi,&b[i].fi.se),b[i].se=i;
    sort(a+1,a+n+1);
    sort(b+1,b+m+1,greater<piii>());
    T.build(1,1,n);
    for(int i=1;i<=m;i++){
        int pos=b[i].fi.se;
        int idx=b[i].se;
        int pos1=T.QFG(1,1,n,pos);
        int L=pos1-1;
        int pos2=T.QF(1,1,n,pos);
        int R=pos2;
        int vL=-INF,vR=INF;
        int dL=INF,dR=INF;
        if(L>=1){
            vL=T.query_point(1,1,n,L);
            dL=pos-vL;
        }
        if(R<=n){
            vR=T.query_point(1,1,n,R);
            dR=vR-pos;
        }
        int t=min(dL,dR);
        int ans=INF;
        if(dL==t&&L>=1){
            int l=T.QF(1,1,n,vL);
            int r=T.QFG(1,1,n,vL)-1;
            ans=min(ans,T.QMN(1,1,n,l,r));
        }
        if(dR==t&&R<=n){
            int l=T.QF(1,1,n,vR);
            int r=T.QFG(1,1,n,vR)-1;
            ans=min(ans,T.QMN(1,1,n,l,r));
        }
        out[idx]=ans;
        if(t>0){
            if(L>=1) T.add(1,1,n,1,L,t);
            if(R<=n) T.add(1,1,n,R,n,-t);
        }
    }
    for(int i=1;i<=m;i++)   printf("%d\n",out[i]);
    return 0;
}
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
const int maxn=6e5+10;
bool mem1;
int n,q;
int a[maxn],nxt[maxn],ans[maxn];
int buc[maxn],qmex[maxn];
vector<pii> v[maxn],Q[maxn];
vector<piii> vq[maxn];
int nex[20][maxn<<1];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void pt(int p,int s){tag[p]=tr[p]=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s;while(p>>=1)pu(p);}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    inline int binary(int x){
        if(tr[1]<x) return n+1;
        int p=1,l=1,r=n;
        while(l^r){pd(p);setmid;(tr[ls]>=x)?(p=ls,r=mid):(p=rs,l=mid+1);}
        return l;
    }
    inline int query(int x){int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return tr[p];}
}
using namespace SegmentTree;
std::vector<int> solve(int sn, std::vector<int>& vv,int sq, std::vector<std::pair<int, int>>& queries){
    n=sn;q=sq;
    for(int i=1;i<=n;i++)   a[i]=vv[i-1];
    for(int i=0;i<q;i++){
        int l=queries[i].fi,r=queries[i].se;
        Q[l].eb(r,i+1);
    }
    fill(buc+1,buc+n+1,n+1);
    for(int i=n;i;i--){nxt[i]=buc[a[i]];buc[a[i]]=i;}
    mems(buc,0);
    for(int i=1,mex=1;i<=n;i++){
        buc[a[i]]=1;while(buc[mex])mex++;
        upd(i,mex);
        if(mex==a[1])   v[mex].eb(1,i);
    }
    for(int i=1;i<=n;i++){
        int k=max(i+1,binary(a[i])),K=k;
        v[a[i]==1?2:1].eb(i,i);
        for(auto [r,id]:Q[i])   vq[query(r)].eb(pii(i,r),id);
        if(k>n) continue;
        // printf("k = %d\n",k);
        int x=a[i]-1;
        while(k<nxt[i]){
            int qk=query(k);
            v[qk].eb(i,k);
            k=binary(qk+1);
        }
        upd(all,K,nxt[i]-1,a[i]);
        upd(i,-1e9);
    }
    for(int i=1;i<=n;i++){
        if(vq[i].empty())   continue;
        const int m=v[i].size()-1;
        for(int j=0,k=0;j<=m;j++){
            while(k<=m&&v[i][k].fi<=v[i][j].se)    k++;
            nex[0][j]=k;
        }
        nex[0][m+1]=m+1;
        for(int o=1;o<20;o++)
            for(int j=0;j<=m+1;j++)
                nex[o][j]=nex[o-1][nex[o-1][j]];
        for(auto [t,id]:vq[i]){
            int l=t.fi,r=t.se;
            int x=lower_bound(v[i].begin(),v[i].end(),pii(l,0))-v[i].begin();
            for(int o=19;~o;o--){
                if(nex[o][x]<=m&&v[i][nex[o][x]].se<=r)x=nex[o][x],ans[id]|=(1<<o);
            }
            ans[id]++;
        }
    }
    vector<int> out;
    for(int i=1;i<=q;i++)   out.eb(ans[i]);
    return out;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int n,q;
    scanf("%d%d",&n,&q);
    vector<int> v;vector<pii> qry;
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);v.eb(x);}
    for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);qry.eb(l,r);}
    v=solve(n,v,q,qry);
    for(int i:v)    printf("%d\n",i);
}
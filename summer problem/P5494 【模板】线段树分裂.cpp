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
int n,q;
int a[maxn];
namespace SegmentTree{
    #define ls(p) lc[p]
    #define rs(p) rc[p]
    #define lson ls(p),l,mid
    #define rson rs(p),mid+1,r
    #define all(x) root[x],1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int l,int r
    int tot;
    int root[maxn];
    ll tr[maxn*18];int lc[maxn*18],rc[maxn*18];
    inline void pu(int p){tr[p]=tr[ls(p)]+tr[rs(p)];}
    void split(int p,int &q,ll v){
        if(!p)  return;q=++tot;
        if(tr[ls(p)]<v) split(rs(p),rs(q),v-tr[ls(p)]);
        else swap(rs(p),rs(q));
        if(tr[ls(p)]>v) split(ls(p),ls(q),v);
        tr[q]=tr[p]-v;tr[p]=v;
    }
    int merge(int x,int y){
        if(!x||!y)  return x|y;
        tr[x]+=tr[y];
        ls(x)=merge(ls(x),ls(y));
        rs(x)=merge(rs(x),rs(y));
        tr[y]=lc[y]=rc[y]=0;
        return x;
    }
    inline void upd(setpos,int x,int s){if(!p)p=++tot;if(l==r)return tr[p]+=s,void();setmid;(x<=mid)?upd(lson,x,s):upd(rson,x,s);pu(p);}
    ll query(setpos,int pl,int pr){if(!p)return 0;if(l>=pl&&r<=pr)return tr[p];setmid;ll res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res+=query(rson,pl,pr);return res;}
    int binary(setpos,ll x){if(tr[p]<x)return -1;if(l==r)return l;setmid;return (tr[ls(p)]>=x)?binary(lson,x):binary(rson,x-tr[ls(p)]);}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);upd(all(1),i,a[i]);}
    int cur=1;
    while(q--){
        int op,p,y;ll x;scanf("%d%d%lld",&op,&p,&x);
        if(!op){
            scanf("%d",&y);++cur;root[cur]=0;
            ll xx=query(all(p),1,x-1),yy=query(all(p),x,y);int tmp=0;
            split(root[p],root[cur],xx);
            split(root[cur],tmp,yy);
            root[p]=merge(root[p],tmp);
        }
        if(op==1)   root[p]=merge(root[p],root[x]);
        if(op==2){scanf("%d",&y);upd(all(p),y,x);}
        if(op==3){scanf("%d",&y);printf("%lld\n",query(all(p),x,y));}
        if(op==4)   printf("%d\n",binary(all(p),x));
    }
}
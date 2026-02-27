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
const int maxn=1e6+10;
int n,q;
struct ques{int op,x,y;int id;};
vector<ques> Q[maxn];
int a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define pos p,l,r
    #define all 1,1,q
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct tree{int sum,premin,val,rsubl;}tr[maxn<<2];
    int L[maxn<<2],R[maxn<<2];
    int querytop(setpos,int x){
        if(!x)  return 0;
        if(tr[p].sum-tr[p].premin<=x)   return tr[p].val;
        if(l==r)    return x*a[l];
        setmid;int surv=tr[rs].sum-tr[rs].premin;
        if(surv>=x) return querytop(rson,x);
        return querytop(lson,x-tr[rs].sum)+tr[rs].val-tr[p].rsubl;
    }
    inline void pu(setpos){
        tr[p].sum=tr[ls].sum+tr[rs].sum;
        tr[p].premin=min(tr[ls].premin,tr[ls].sum+tr[rs].premin);
        if(tr[ls].sum-tr[ls].premin+tr[rs].premin<=0)    tr[p].rsubl=tr[ls].val;
        else{setmid;tr[p].rsubl= (lson,-tr[rs].premin);}
        tr[p].val=tr[ls].val+tr[rs].val-tr[p].rsubl;
    }
    inline void upd(int x,int y,int s){int p=1,l=1,r=q;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p].sum=s;tr[p].premin=min(0,s);tr[p].val=y*s;tr[p].rsubl=0;while(p>>=1)pu(p,L[p],R[p]);}
    pii query(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)return pii(tr[p].sum,tr[p].premin);
        setmid;if(pl>mid)return query(rson,pl,pr);if(pr<=mid)return query(lson,pl,pr);
        pii x=query(lson,pl,pr),y=query(rson,pl,pr);
        return pii(x.fi+y.fi,min(x.se,x.fi+y.se));
    }
    tree queryval(setpos,int pr,int x){
        if(r<=pr)return (tree){tr[p].sum,tr[p].premin,querytop(pos,x),0};
        setmid;
        if(pr<=mid) return queryval(lson,pr,x);
        tree trr=queryval(rson,pr,x),trl=tr[ls],res;
        res.sum=trl.sum+trr.sum;res.premin=min(trl.premin,trl.sum+trr.premin);
        if(trr.sum-trr.premin>=x)   res.val=trr.val;
        else    res.val=trr.val+querytop(lson,x-trr.sum)-querytop(lson,-trr.premin);
        return res;
    }
    void build(setpos){L[p]=l;R[p]=r;tr[p].sum=tr[p].premin=tr[p].val=tr[p].rsubl=0;if(l==r)return;setmid;build(lson);build(rson);}
}
using namespace SegmentTree;
int ans[maxn];
void matt(){
    scanf("%d%d",&n,&q);
    build(all);
    for(int i=1;i<=q;i++)   ans[i]=-1e9;
    for(int i=1;i<=q;i++){
        int op,l,r,x;
        scanf("%d%d%d",&op,&l,&r);
        if(op==1){scanf("%d",&x);Q[l].eb((ques){1,1,x,i});Q[r+1].eb((ques){-1,1,x,i});a[i]=x;}
        if(op==2)   Q[l].eb((ques){2,1,0,i}),Q[r+1].eb((ques){-2,1,0,i});
        if(op==3)   Q[l].eb((ques){3,r,r,i});
    }
    for(int i=1;i<=n;i++){
        for(auto [op,x,y,id]:Q[i]){
            if(op==1)   upd(id,y,x);
            if(op==-1)  upd(id,y,0);
            if(op==2)   upd(id,0,-x);
            if(op==-2)  upd(id,0,0);
            if(op==3){
                pii tmp=query(all,1,id);int siz=tmp.fi-tmp.se;
                if(x>siz){ans[id]=-1;continue;}
                x=max(x,1);y=min(y,siz);
                if(x<=y)    ans[id]=queryval(all,id,y).val-queryval(all,id,x-1).val;
            }
        }
        Q[i].clear();
    }
    Q[n+1].clear();
    for(int i=1;i<=q;i++)if(ans[i]>=-1)printf("%d\n",ans[i]);
}
int main(){int c,T;scanf("%d%d",&c,&T);while(T--)matt();}
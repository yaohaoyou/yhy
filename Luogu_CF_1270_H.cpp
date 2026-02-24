#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10,V=1e6+10;
int n,q;
int a[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,V
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int mn[(V<<2)+10],cnt[(V<<2)+10],tag[(V<<2)+10];
    inline void pushtag(int p,int s){mn[p]+=s;tag[p]+=s;}
    inline void pushup(int p){mn[p]=min(mn[ls],mn[rs]);cnt[p]=(mn[ls]==mn[p])*cnt[ls];cnt[p]+=(mn[rs]==mn[p])*cnt[rs];}
    inline void pushdown(int p){if(!tag[p])return;pushtag(ls,tag[p]);pushtag(rs,tag[p]);tag[p]=0;}
    void update(setpos,int x,int s){
        if(l==r)    return cnt[p]+=s,void();
        setmid;
        pushdown(p);
        if(x<=mid)  update(lson,x,s);
        else    update(rson,x,s);
        pushup(p);
    }
    void updateN(setpos,int pl,int pr,int s){
        if(l>=pl&&r<=pr) return pushtag(p,s);
        pushdown(p);
        setmid;
        if(pl<=mid) updateN(lson,pl,pr,s);
        if(pr>mid)  updateN(rson,pl,pr,s);
        pushup(p);
    }
    int query(setpos,int pl,int pr){
        if(l>=pl&&r<=pr)    return mn[p]==1?cnt[p]:0;
        pushdown(p);
        setmid,res=0;
        if(pl<=mid) res=query(lson,pl,pr);
        if(pr>mid)  res+=query(rson,pl,pr);
        return res;
    }
}
using namespace SegmentTree;
void modify(int x,int y,int val){
    if(x>y)   swap(x,y);
    updateN(all,x,y-1,val);
}
int main(){
    scanf("%d%d",&n,&q);
    a[0]=V;a[n+1]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        update(all,a[i],1);
    }
    for(int i=1;i<=n+1;i++)
        modify(a[i-1],a[i],1);
    while(q--){
        int i,y;
        scanf("%d%d",&i,&y);
        update(all,a[i],-1);
        modify(a[i-1],a[i],-1);
        modify(a[i],a[i+1],-1);
        a[i]=y;
        update(all,a[i],1);
        modify(a[i-1],a[i],1);
        modify(a[i],a[i+1],1);
        printf("%d\n",query(all,1,V-1));
    }
}
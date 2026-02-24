#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e5+10,inf=1e4;
int n,q;
int pt[maxn];int tp;  // 空间回收
namespace FHQTreap{
    int rt,cur;
    int siz[maxn];
    int ls[maxn],rs[maxn];
    int val[maxn];
    bool rev[maxn];int mod[maxn];  // lazy-tag
    struct node{
        int sum,pre,suf,mx;
        inline void modify(int x,int sz){sum=x*sz;pre=suf=mx=x>0?sum:x;}
        friend node operator+(node x,node y){
            node res;
            res.sum=x.sum+y.sum;
            res.pre=max(x.pre,x.sum+y.pre);
            res.suf=max(y.suf,y.sum+x.suf);
            res.mx=max({x.mx,y.mx,x.suf+y.pre});
            return res;
        }
    }tr[maxn],emp;
    int rd[maxn];
    inline int nd(int v){int p=tp?pt[tp--]:++cur;siz[p]=1;val[p]=v;rev[p]=false;mod[p]=inf;tr[p]={v,v,v,v};rd[p]=rand();return p;}
    inline void pushup(int p){tr[p]=tr[ls[p]]+(node){val[p],val[p],val[p],val[p]}+tr[rs[p]];siz[p]=siz[ls[p]]+siz[rs[p]]+1;}
    inline void pushrev(int p){rev[p]^=1;swap(tr[p].pre,tr[p].suf);}
    inline void pushmod(int p,int s){if(!p)return;mod[p]=val[p]=s;tr[p].modify(s,siz[p]);}
    inline void pushdown(int p){
        if(rev[p])pushrev(ls[p]),pushrev(rs[p]),swap(ls[p],rs[p]),rev[p]=false;
        if(mod[p]^inf)pushmod(ls[p],mod[p]),pushmod(rs[p],mod[p]),mod[p]=inf;
    }
    int merge(int p,int q){
        if(!p||!q)  return p|q;
        pushdown(p);pushdown(q);
        if(rd[p]>rd[q]){rs[p]=merge(rs[p],q);pushup(p);return p;}
        ls[q]=merge(p,ls[q]);pushup(q);return q;
    }
    void split(int p,int v,int &x,int &y){
        if(!p)  return x=y=0,void();
        pushdown(p);
        if(v<=siz[ls[p]])   split(ls[p],v,x,ls[y=p]);
        else    split(rs[p],v-siz[ls[p]]-1,rs[x=p],y);
        pushup(p);
    }
    void clear(int p){
        if(!p)return;
        clear(ls[p]);clear(rs[p]);
        tr[p]=emp;rev[p]=siz[p]=ls[p]=rs[p]=val[p]=rd[p]=0;mod[p]=inf;
        pt[++tp]=p;
    }
    inline void ins(){
        int p,tot,x,y;scanf("%d%d",&p,&tot);
        int tt=0;
        for(int i=1;i<=tot;i++){
            int k;scanf("%d",&k);
            tt=merge(tt,nd(k));
        }
        split(rt,p,x,y);
        rt=merge(merge(x,tt),y);
    }
    inline void del(){
        int p,tot,x,y,z;scanf("%d%d",&p,&tot);
        split(rt,p-1,x,y);split(y,tot,y,z);
        clear(y);
        rt=merge(x,z);
    }
    inline void modify(){
        int p,tot,c,x,y,z;scanf("%d%d%d",&p,&tot,&c);
        split(rt,p-1,x,y);split(y,tot,y,z);
        rev[y]=false;
        mod[y]=val[y]=c;tr[y].modify(c,tot);
        rt=merge(merge(x,y),z);
    }
    inline void reverse(){
        int p,tot,x,y,z;scanf("%d%d",&p,&tot);
        split(rt,p-1,x,y);split(y,tot,y,z);
        rev[y]^=1;
        rt=merge(merge(x,y),z);
    }
    inline int getsum(){
        int p,tot,x,y,z;scanf("%d%d",&p,&tot);
        split(rt,p-1,x,y);split(y,tot,y,z);
        int ret=tr[y].sum;
        rt=merge(merge(x,y),z);
        return ret;
    }
}
using namespace FHQTreap;
int main(){
    srand(547547);
    tr[0]=emp={0,-inf,-inf,-inf};
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        rt=merge(rt,nd(x));
    }
    while(q--){
        char s[20];
        scanf("%s",s);
        if(s[0]=='I')   ins();
        if(s[0]=='D')   del();
        if(s[2]=='K')   modify();
        if(s[0]=='R')   reverse();
        if(s[0]=='G')   printf("%d\n",getsum());
        if(s[2]=='X')   printf("%d\n",tr[rt].mx);
    }
}
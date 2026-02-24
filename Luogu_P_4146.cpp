#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e4+10;
int n,q;
namespace FHQTreap{
    int rt,tot;
    int siz[maxn];
    ll mx[maxn],plu[maxn],val[maxn];
    bool rev[maxn];
    int ls[maxn],rs[maxn];
    int rd[maxn];
    inline void pushup(int p){siz[p]=siz[ls[p]]+siz[rs[p]]+1;mx[p]=max({mx[ls[p]],mx[rs[p]],val[p]});}
    inline void pushplu(int p,int s){if(!p)return;val[p]+=s;mx[p]+=s;plu[p]+=s;}
    inline void pushdown(int p){if(plu[p]){pushplu(ls[p],plu[p]);pushplu(rs[p],plu[p]);plu[p]=0;}if(rev[p]){rev[ls[p]]^=1;rev[rs[p]]^=1;swap(ls[p],rs[p]);rev[p]=false;}}
    inline int nd(int v){int p=++tot;siz[p]=1;mx[p]=val[p]=v;rd[p]=rand();return p;}
    int merge(int p,int q){
        if(!p||!q)  return p|q;
        pushdown(p);pushdown(q);
        if(rd[p]>rd[q]) return rs[p]=merge(rs[p],q),pushup(p),p;
        return ls[q]=merge(p,ls[q]),pushup(q),q;
    }
    void split(int p,int v,int &x,int &y){
        if(!p)  return x=y=0,void();
        pushdown(p);
        if(v<=siz[ls[p]])   split(ls[p],v,x,ls[y=p]);
        else    split(rs[p],v-siz[ls[p]]-1,rs[x=p],y);
        pushup(p);
    }
    inline void spl(int &x,int &y,int &z){int l,r;scanf("%d%d",&l,&r);split(rt,l-1,x,y);split(y,r-l+1,y,z);}
    inline void update(){
        int x,y,z,v;spl(x,y,z);scanf("%d",&v);
        pushplu(y,v);
        rt=merge(merge(x,y),z);
    }
    inline void rever(){
        int x,y,z;spl(x,y,z);
        rev[y]^=1;
        rt=merge(merge(x,y),z);
    }
    inline void query(){
        int x,y,z;spl(x,y,z);
        printf("%lld\n",mx[y]);
        rt=merge(merge(x,y),z);
    }
}
using namespace FHQTreap;
int main(){
    mx[0]=-1e18;
    srand(time(0));
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   rt=merge(rt,nd(0));
    while(q--){
        int op;scanf("%d",&op);
        if(op==1)   update();
        else if(op==2)  rever();
        else query();
    }
}
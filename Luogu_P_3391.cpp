#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi firs[p]t
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10;
int n,q;
namespace FHQTreap{
    int tot,rt;
    int ls[maxn],rs[maxn],siz[maxn],rd[maxn],val[maxn];
    bool tag[maxn];
    inline void pushup(int p){siz[p]=siz[ls[p]]+siz[rs[p]]+1;}
    inline void pushdown(int p){if(!tag[p])return;tag[ls[p]]^=1;tag[rs[p]]^=1;swap(ls[p],rs[p]);tag[p]=0;}
    inline int nd(int x){int p=++tot;rd[p]=rand();siz[p]=1;val[p]=x;return p;}
    void split(int p,int v,int &x,int &y){
        if(!p) return x=y=0,void();
        pushdown(p);
        if(v<=siz[ls[p]])  split(ls[p],v,x,ls[y=p]);
        else    split(rs[p],v-siz[ls[p]]-1,rs[x=p],y);
        pushup(p);
    }
    int merge(int p,int q){
        if(!p||!q)  return p|q;
        pushdown(p);pushdown(q);
        if(rd[p]>rd[q]){rs[p]=merge(rs[p],q);pushup(p);return p;}
        ls[q]=merge(p,ls[q]);pushup(q);return q;
    }
    inline void modify(int l,int r){
        int x,y,z;
        split(rt,l-1,x,y);
        split(y,r-l+1,y,z);
        tag[y]^=1;
        rt=merge(merge(x,y),z);
    }
    void print(int p){if(!p)return;pushdown(p);print(ls[p]);printf("%d ",val[p]);print(rs[p]);}
}
using namespace FHQTreap;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   rt=merge(rt,nd(i));
    while(q--){int l,r;scanf("%d%d",&l,&r);modify(l,r);}
    print(rt);
}
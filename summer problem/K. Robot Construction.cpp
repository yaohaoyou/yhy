#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10;
int n,m;
pii a[maxn],b[maxn];
mt19937 matt(10121105);
int rt;
vector<piii> vec;
struct FHQTreap{
    #define ls(p) nex[p][0]
    #define rs(p) nex[p][1]
    int tot;
    int nex[maxn][2],val[maxn],rd[maxn],tag1[maxn],tag2[maxn],id[maxn],ans[maxn];
    int mem[maxn],tp;
    inline int nd(int v,int i,int j){int p=tp?mem[tp--]:++tot;val[p]=v;rd[p]=matt();id[p]=i;ans[p]=j;return p;}
    inline void era(int p){mem[++tp]=p;val[p]=id[p]=tag1[p]=tag2[p]=ans[p]=ls(p)=rs(p)=rd[p]=0;}
    inline void pushtag(int p,int s,int t){val[p]+=s;ans[p]+=t;tag1[p]+=s;tag2[p]+=t;}
    inline void pushdown(int p){if(!tag1[p]&&!tag2[p])return;pushtag(ls(p),tag1[p],tag2[p]);pushtag(rs(p),tag1[p],tag2[p]);tag1[p]=tag2[p]=0;}
    int merge(int p,int q){
        if(!p||!q)  return p|q;
        if(rd[p]>rd[q]) return pushdown(p),rs(p)=merge(rs(p),q),p;
        else    return pushdown(q),ls(q)=merge(p,ls(q)),q;
    }
    void split(int p,int v,int &x,int &y){
        if(!p)  return x=y=0,void();
        pushdown(p);
        if(v<val[p])    split(ls(p),v,x,ls(y=p));
        else    split(rs(p),v,rs(x=p),y);
    }
    void print(int p){if(!p)return;pushdown(p);print(ls(p));printf("(%d,%d,%d)\n",val[p],id[p],ans[p]);print(rs(p));}
    void get(int p){if(!p)return;pushdown(p);get(ls(p));vec.eb(val[p],pii(id[p],ans[p]));get(rs(p));}
    void clear(int p){if(!p)return;pushdown(p);clear(ls(p));clear(rs(p));era(p);}
    inline void ins(int v,int i,int j){/*printf("ins (%d,%d,%d)\n",v,i,j);*/int x,y=nd(v,i,j),z;split(rt,v,x,z);rt=merge(merge(x,y),z);}
}tr;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i].se,&a[i].fi);
    sort(a+1,a+n+1,[&](pii x,pii y){return x.fi==y.fi?x.se<y.se:x.fi>y.fi;});
    scanf("%d",&m);
    for(int i=1;i<=m;i++){scanf("%d",&b[i].fi);b[i].se=i;}
    sort(b+1,b+m+1);
    for(int i=1;i<=m;i++)   tr.ins(b[i].fi,b[i].se,0);
    for(int i=1;i<=n;i++){
        int v=a[i].se;
        int x,y,z;
        // printf("v = %d\n",v);
        tr.split(rt,v-1,x,y);
        tr.split(y,v<<1,y,z);
        tr.pushtag(z,-v,1);
        vec.clear();tr.get(y);
        tr.clear(y);
        rt=tr.merge(x,z);
        for(auto [j,k]:vec)  tr.ins(j-v,k.fi,k.se+1);
        // puts("-------------------");
    }
    vec.clear();tr.get(rt);
    sort(vec.begin(),vec.end(),[&](piii x,piii y){return x.se.fi<y.se.fi;});
    for(auto i:vec) printf("%d ",i.se.se);
}
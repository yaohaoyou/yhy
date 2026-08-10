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
const int maxn=1e6+10;
int n,m,q;
int a[maxn];
set<pii> st[maxn];
map<piii,int> id;
namespace FHQTreap{
    mt19937 matt(888);
    int cur,c;
    int siz[maxn],line[maxn],ls[maxn],rs[maxn],fa[maxn],rd[maxn];
    pii val[maxn];
    inline int nd(int x,int y,int k){int p=++cur;id[piii(pii(x,y),k)]=p;val[p]=pii(x,y);line[p]=k;rd[p]=matt();siz[p]=1;return p;}
    inline void pu(int p){siz[p]=siz[ls[p]]+siz[rs[p]]+1;(ls[p])&&(fa[ls[p]]=p);(rs[p])&&(fa[rs[p]]=p);}
    int merge(int x,int y){
        c++;assert(c<=1e6);
        if(!x||!y)  return x|y;
        if(rd[x]<rd[y]){rs[x]=merge(rs[x],y);pu(x);return x;}
        ls[y]=merge(x,ls[y]);pu(y);return y;
    }
    void split(int p,int v,int &x,int &y){
        if(!p)  return x=y=0,void();
        if(val[p].se>v)   split(ls[p],v,x,ls[y=p]);
        else    split(rs[p],v,rs[x=p],y);
        pu(p);
    }
    inline int getrt(int p){c++;while(fa[p])assert(c<=1e6),p=fa[p];return p;}
    inline int query(int p){c++;while(rs[p])assert(c<=1e6),p=rs[p];return line[p];}
}
using namespace FHQTreap;
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)   nd(0,m+1,i),st[i].ep(0,m+1);
    while(q--){
        int op,x,y;scanf("%d%d",&op,&x);
        if(op==1){
            scanf("%d",&y);
            auto it1=--st[x].lower_bound(pii(y+1,0)),it2=--st[x+1].lower_bound(pii(y+1,0));
            st[x].ep(it1->fi,y);st[x].ep(y+1,it1->se);
            st[x+1].ep(it2->fi,y);st[x+1].ep(y+1,it2->se);
            int r1=getrt(id[piii(*it1,x)]),r2=getrt(id[piii(*it2,x+1)]),x1,y1,z1,x2,y2,z2;
            // printf("id = %d %d %d\n",id[piii(*it1,x)],it1->fi,it1->se);
            // printf("r1 = %d,r2 = %d\n",r1,r2);
            c=0;split(r1,it1->se,x1,z1);int xx1=x1;
            c=0;split(xx1,it1->fi-1,x1,y1);
            c=0;split(r2,it2->se,x2,z2);int xx2=x2;
            c=0;split(xx2,it2->fi-1,x2,y2);
            r1=merge(merge(x1,nd(it1->fi,y,x)),merge(nd(y+1,it2->se,x+1),z2));
            r2=merge(merge(x2,nd(it2->fi,y,x+1)),merge(nd(y+1,it1->se,x),z1));
            fa[r1]=fa[r2]=0;
            // printf("(%d,%d) (%d,%d) %d %d\n",x1,z1,x2,z2,r1,r2);
            st[x].erase(it1);st[x+1].erase(it2);
        }
        else{
            // printf("%d %d %d\n",st[x].begin()->fi,st[x].begin()->se,id[piii(*st[x].begin(),x)]);
            printf("%d\n",query(getrt(id[piii(*st[x].begin(),x)])));
        }
    }
}
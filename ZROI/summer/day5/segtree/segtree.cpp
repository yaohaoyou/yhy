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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=4e5+10;
int n,q,tot;
pii a[maxn];
int ls[maxn],rs[maxn],fa[maxn];
void input(int u){
    if(a[u].fi==a[u].se)    return;
    int x;scanf("%d",&x);
    ls[u]=++tot;rs[u]=++tot;
    a[ls[u]]=pii(a[u].fi,x);a[rs[u]]=pii(x+1,a[u].se);
    fa[ls[u]]=fa[rs[u]]=u;
    // debug("%d %d\n",u,ls[u]);
    // debug("%d %d\n",u,rs[u]);
    input(ls[u]);input(rs[u]);
}
int ans;
vector<int> v[2],emp;
void query(int u,int l,int r){
    if(l<=a[u].fi&&a[u].se<=r){
        if(u==ls[fa[u]])    emp.eb(fa[u]<<1);
        else    emp.eb(fa[u]<<1|1);
        v[0].eb(u);ans++;
        return;
    }
    int mid=a[ls[u]].se;
    if(l<=mid)  query(ls[u],l,r);
    if(r>mid)   query(rs[u],l,r);
}
int m;
void build(int u){
    if(!ls[u]&&!rs[u])  return m++,a[u]=pii(m,m),void();
    assert(bool(ls[u])+bool(rs[u])!=1);
    fa[ls[u]]=fa[rs[u]]=u;
    build(ls[u]);build(rs[u]);
    a[u]=pii(a[ls[u]].fi,a[rs[u]].se);
}
void out_graph(){
    for(int i=1;i<=tot;i++) printf("[%d,%d] ",a[i].fi,a[i].se);puts("");
    for(int i=1;i<=tot;i++){
        if(ls[i])printf("%d %d\n",i,ls[i]);
        if(rs[i])printf("%d %d\n",i,rs[i]);
    }
    puts("");
}
int main(){
    freopen("segtree.in","r",stdin);freopen("segtree.out","w",stdout);
    scanf("%d%d",&n,&q);
    if(n>5000&&q>5000){
        while(q--){
            int l,x,r;scanf("%d%d%d",&l,&x,&r);
            puts("1 1");
        }
        return 0;
    }
    a[1]=pii(1,n);input(++tot);
    while(q--){
        v[0].clear();v[1].clear();emp.clear();
        int l,x,r;scanf("%d%d%d",&l,&x,&r);
        ans=0;query(1,l,x);printf("%d ",ans);v[1].swap(v[0]);
        ans=0;query(1,x+1,r);printf("%d\n",ans);
        {
            int i=0;
            for(int o:{0,1}){
                for(int x:v[o]){
                    if(emp[i]&1)    rs[emp[i]>>1]=x,fa[x]=emp[i]>>1;
                    else    ls[emp[i]>>1]=x,fa[x]=emp[i]>>1;
                    i++;
                }
            }
        }
        m=l-1;
        for(int o:{0,1}){
            for(int i:v[o]){
                build(i);
                while(i=fa[i]){
                    if(a[i]==pii(a[ls[i]].fi,a[rs[i]].se))  break;
                    a[i]=pii(a[ls[i]].fi,a[rs[i]].se);
                }
            }
        }
    }
}
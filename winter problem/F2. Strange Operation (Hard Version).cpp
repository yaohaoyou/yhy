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
const int maxn=3e5+10;
int n;
int a[maxn],b[maxn];
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline void gmx(int &x,int y){(x<y)&&(x=y);}
mt19937 Matt(time(0));
namespace FHQTreap{
    int tot,rt;
    int tr[maxn],val[maxn],ls[maxn],rs[maxn],siz[maxn],rnd[maxn];
    inline int nd(int x){int p=++tot;tr[p]=val[p]=x;ls[p]=rs[p]=0;siz[p]=1;rnd[p]=Matt();return p;}
    inline void pu(int p){tr[p]=val[p];if(ls[p])gmn(tr[p],tr[ls[p]]);if(rs[p])gmn(tr[p],tr[rs[p]]);siz[p]=siz[ls[p]]+siz[rs[p]]+1;}
    int merge(int p,int q){if(!p||!q)return p|q;if(rnd[p]<rnd[q])return rs[p]=merge(rs[p],q),pu(p),p;ls[q]=merge(p,ls[q]);pu(q);return q;}
    void split(int p,int v,int &x,int &y){
        if(!p)  return x=y=0,void();
        if(v<=siz[ls[p]])   split(ls[p],v,x,ls[y=p]);
        else split(rs[p],v-siz[ls[p]]-1,rs[x=p],y);
        pu(p);
    }
    inline int binary(int p,int x){
        if(tr[p]>=x) return siz[p];
        int res=0;
        while(p){
            if(rs[p]&&tr[rs[p]]<x) p=rs[p];
            else if(val[p]<x)  return res+=siz[rs[p]];
            else    res+=siz[rs[p]]+1,p=ls[p];
        }
        assert(0);
        return 888;
    }
    void dfs(int p){
        if(ls[p])dfs(ls[p]);
        b[++tot]=val[p];
        if(rs[p])dfs(rs[p]);
    }
    void clear(){tot=rt=0;}
}
using namespace FHQTreap;
void matt(int _cases){
    clear();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[a[i]]=i;
    for(int i=1;i<=n;i++){
        // if(b[i-1]>b[i]&&b[i-2]>b[i]){
        //     int p=b[i],x=b[i-1],y=b[i-2];
        //     a[p]-=2;a[x]++;a[y]++;
        //     b[a[p]]=p;b[a[x]]=x;b[a[y]]=y;
        //     i-=3;
        // }
        rt=merge(rt,nd(b[i]));
        if(i<=2)    continue;
        int s=binary(rt,b[i]);
        // printf("s = %d\n",s);
        if(!(s&1))  s--;
        if(s>1){
            int x,y,z;split(rt,i-1,y,z);split(y,i-s,x,y);
            rt=merge(x,merge(z,y));
        }
    }
    tot=0;dfs(rt);
    for(int i=1;i<=n;i++)   a[b[i]]=i;
    for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
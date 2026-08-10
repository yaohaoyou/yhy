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
const int maxn=1e6+10,B=1e4;
int n;
int a[maxn],R[maxn],ans[maxn],f[maxn];
pii b[maxn];
int buc[maxn],id[maxn],t[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x){gmx(tr[x],s);x^=lowbit(x);}}
    inline void upd(int l,int r,int s){if(l<=r)add(l,s),add(r+1,-s);}
    inline int que(int x){int res=0;while(x){gmx(res,tr[x]);x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
int main(){
    scanf("%d",&n);n<<=1;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    for(int i=n;i;i--){
        if(buc[a[i]]){
            R[i]=buc[a[i]];
            b[a[i]]=pii(i,R[i]);
        }
        buc[a[i]]=i;
    }
    n>>=1;
    sort(b+1,b+n+1,[&](pii x,pii y){return id[x.fi]==id[y.fi]?x.se<y.se:x.fi<y.fi;});
    for(int i=1;i<=n;i++)   t[a[b[i].fi]]=t[a[b[i].fi]]=i;
    int m=0;
    for(int i=1;i<=n;i++){
        if(t[i])
    }
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);puts("");
}
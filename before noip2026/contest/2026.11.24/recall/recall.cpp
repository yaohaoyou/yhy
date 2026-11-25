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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=4e5+10,inf=1e9+10;
int n,q;
int a[maxn],b[maxn],t[maxn];
piii Q[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x){gmn(tr[x],s);x^=lowbit(x);}}
    inline int que(int x){int res=inf;while(x<=n){gmn(res,tr[x]);x+=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=inf;}
}T;
int ans[maxn];
pii c[maxn];
bool mem2;
int main(){
    freopen("recall.in","r",stdin);freopen("recall.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%*d%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    T.clear();
    for(int i=1;i<=n;i++){
        if(a[i]>=i){t[i]=inf;continue;}
        if(i-a[i]>=b[i])    t[i]=b[i];
        else{
            t[i]=inf;
            // for(int j=a[i];j<i;j++) gmn(t[i],t[j]-j+a[i]);
            t[i]=T.que(a[i])+a[i];
            gmx(t[i],0);
            t[i]+=b[i];
        }
        T.add(i,t[i]-i);
    }
    for(int i=1;i<=n;i++)   c[i]=pii(t[i],i);
    T.clear();
    for(int i=1;i<=q;i++){int p,k;scanf("%d%d",&p,&k);Q[i]=piii(pii(k,p),i);}
    sort(c+1,c+n+1);sort(Q+1,Q+q+1);
    for(int i=1,j=1;i<=q;i++){
        while(j<=n&&c[j].fi<=Q[i].fi.fi){
            T.add(c[j].se,c[j].fi-c[j].se);
            j++;
        }
        ans[Q[i].se]=T.que(Q[i].fi.se)+Q[i].fi.se;
        if(ans[Q[i].se]<=Q[i].fi.fi)    gmx(ans[Q[i].se],0);
        else    ans[Q[i].se]=-1;
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
    // int ans=inf;
    // for(int i=p;i<=n;i++)if(t[i]<=k)gmn(ans,t[i]-i+p);
    // printf("%d\n",ans<=k?max(0,ans):-1);
}
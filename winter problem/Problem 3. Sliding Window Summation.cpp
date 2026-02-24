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
int n,m;
int a[maxn],x[maxn],y[maxn];
pii b[maxn];
piii c[maxn];
void matt(int _cases){
    for(int i=1;i<=n;i++)   x[i]=y[i]=c[i].fi.fi=c[i].fi.se=c[i].se=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   b[i]=pii(i,1);
    for(int i=1;i<=n-m+1;i++){
        scanf("%1d",&a[i]);
        if(i^1){
            b[i+m-1].fi=b[i-1].fi;
            b[i+m-1].se=b[i-1].se^a[i]^a[i-1];
        }
    }
    if(m==1)    return printf("%d %d\n",accumulate(a+1,a+n+1,0),accumulate(a+1,a+n+1,0)),void();
    for(int i=1;i<=n;i++)   c[b[i].fi].fi.fi+=b[i].se?1:-1,c[b[i].fi].fi.se++;
    for(int i=1;i<=m;i++)   c[i].se=c[i].fi.fi>=0,c[i].fi.fi=abs(c[i].fi.fi);
    sort(c+1,c+m+1,greater<piii>());
    for(int i=1;i<=m;i++)   x[i]=(c[i].fi.fi+c[i].fi.se)/2,y[i]=(c[i].fi.se-c[i].fi.fi)/2;
    // for(int i=1;i<=m;i++)   printf("%d,%d,%d ",c[i].fi.fi,c[i].fi.se,c[i].se);puts("");
    int mn=0,mx=0,o0=0,o1=0;
    for(int i=1;i<m;i++){mn+=y[i];mx+=x[i];o0^=!c[i].se;o1^=c[i].se;}
    if((o0^(!c[m].se))==a[1])mn+=y[m];
    else mn+=x[m];
    if((o1^c[m].se)==a[1])  mx+=x[m];
    else mx+=y[m];
    printf("%d %d\n",mn,mx);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
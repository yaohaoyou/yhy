#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define plii pair<ll,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e6+10;
int n,m,tot;
int a[2][maxn],c[maxn],pr[maxn],nx[maxn],p[maxn];
ll b[2][maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){x=max(x,y);}
void discrete(){
    for(int i=1;i<=n+m;i++)if(!c[i])c[i]=++tot;
    for(int i=1;i<=n;i++)   a[0][i]=c[a[0][i]],p[a[0][i]]=i;
    for(int i=1;i<=m;i++)   a[1][i]=c[a[1][i]];
}
int main(){
    freopen("select.in","r",stdin);freopen("select.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[0][i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[0][i]),b[0][i]+=b[0][i-1];
    for(int i=1;i<=m;i++)   scanf("%d",&a[1][i]),c[a[1][i]]=++tot;
    for(int i=1;i<=m;i++)   scanf("%d",&b[1][i]),b[1][i]+=b[1][i-1];
    discrete();
    ll ans;pii seg1,seg2;
    if(b[0][n]>=b[1][m])    ans=b[0][n],seg1=pii(1,n),seg2=pii(0,0);
    else ans=b[1][m],seg1=pii(0,0),seg2=pii(1,m);
    for(int l=1;l<=n;l++){
        plii now=plii(0,pii(0,0));
        for(int i=0;i<=m+1;i++)nx[i]=0;
        int lst=0;
        for(int i=1;i<=m;i++)
            if(p[i]>=l){pr[i]=lst;nx[lst]=i;gmx(now,plii(b[1][i-1]-b[1][lst],pii(lst+1,i-1)));lst=i;}
        pr[m+1]=lst;nx[lst]=m+1;gmx(now,plii(b[1][m]-b[1][lst],pii(lst+1,m)));
        ll mx=0;int pos;
        for(int i=n;i>=l;i--){
            if(now.fi+b[0][i]-b[0][l-1]>mx) mx=now.fi+b[0][i]-b[0][l-1],pos=i;
            if(now.fi+b[0][i]-b[0][l-1]>ans)    ans=now.fi+b[0][i]-b[0][l-1],seg1=pii(l,i),seg2=now.se;
            int x=a[0][i];
            if(x<=m){
                int pre=pr[x],nxt=nx[x];pr[nxt]=pre;nx[pre]=nxt;
                gmx(now,plii(b[1][nxt-1]-b[1][pre],pii(pre+1,nxt-1)));
            }
        }
    }
    printf("%lld\n%d %d\n%d %d\n",ans,seg1.fi,seg1.se,seg2.fi,seg2.se);
}
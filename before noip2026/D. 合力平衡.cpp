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
bool mem1;
const int maxn=1e6+10;
const ll lim=1e18;
int n;
ll a[maxn],b[maxn],c[maxn],p[maxn],ans[maxn];
queue<int> q;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);int N=n;
    for(int i=1;i<=n;i++)   scanf("%lld%lld",&a[i],&b[i]),q.ep(i);
    while(q.size()>=3){
        int u=q.front(),v,w;q.pop();v=q.front();q.pop();w=q.front();q.pop();
        bool fl=false;
        for(auto [x,y]:{pii(u,v),pii(u,w),pii(v,w)}){
            ll dx=a[x]+a[y],dy=b[x]+b[y];
            if(dx*dx+dy*dy<=lim){
                p[x]=p[y]=++n;
                c[x]=c[y]=1;
                a[n]=dx;b[n]=dy;
                if((x^u)&&(y^u))q.ep(u);if((x^v)&&(y^v))q.ep(v);if((x^w)&&(y^w))q.ep(w);
                fl=true;
                break;
            }
            dx=a[x]-a[y],dy=b[x]-b[y];
            if(dx*dx+dy*dy<=lim){
                p[x]=p[y]=++n;
                c[x]=1;c[y]=-1;
                a[n]=dx;b[n]=dy;
                if((x^u)&&(y^u))q.ep(u);if((x^v)&&(y^v))q.ep(v);if((x^w)&&(y^w))q.ep(w);
                fl=true;
                break;
            }
        }
        // debug("%d %d %d : %d\n",u,v,w,fl);
        assert(fl);
        q.ep(n);
    }
    int x=q.front(),y;q.pop();y=q.front();q.pop();
    ll dx=a[x]+a[y],dy=b[x]+b[y];
    if(dx*dx+dy*dy<=lim*2)  ans[x]=ans[y]=1;
    else    ans[x]=1,ans[y]=-1;
    for(int i=n-1;i;i--)if(!ans[i])ans[i]=c[i]*ans[p[i]];
    for(int i=1;i<=N;i++)   printf("%lld ",ans[i]);
}
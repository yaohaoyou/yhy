#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pll pair<ll,ll>
#define plli pair<pll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
const ll inf=1e13;
int n;
ll ans,tag;
ll a[maxn],b[maxn],c[maxn],d[maxn];
priority_queue<plli> q;
bool check(){for(int i=1;i<=n;i++)if(a[i]^(b[i]+tag))return false;return true;}
bool mem2;
int main(){
    // freopen("a.in","r",stdin);freopen("a.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    ll ans=0;
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%lld",&b[i]);
    if(check()) return puts("0"),0;
    int lst=0;
    for(int i=1;i<=n;i++){
        if(i==1)    lst=(b[i]-a[i]+inf*n)%n;
        else if(lst!=(b[i]-a[i]+inf*n)%n)  return puts("-1"),0;
    }
    int cnt=0;
    while(true){
        cnt+=n;if(cnt>1e8)break;
        bool flag=false;
        for(int i=1;i<=n;i++){
            if(b[i]+tag>=a[i]){
                ll w=(b[i]+tag-a[i])/(n-1);
                if(w){
                    flag=true;
                    ans+=w;tag+=w;
                    b[i]-=w*n;
                }
            }
        }
        if(!flag)break;
    }
    ll mn=0;for(int i=1;i<=n;i++)gmn(mn,b[i]-a[i]),q.ep(pll(b[i]-a[i],b[i]),i);
    for(int i=1;i<=n;i++)if(b[i]-mn>a[i]&&a[i]<n)d[a[i]]++;
    for(int i=1;i<n;i++)d[i]+=d[i-1];
    for(int i=0;i<n;i++)if(d[i]>i+1)return puts("-1"),0;
    for(int i=1;i<=n;i++)   c[i]=(b[i]-a[i]-mn)/n;
    int tim=0;
    while((++tim)<=n+n&&q.top().fi.fi+tag>0){
        int p=q.top().se;q.pop();
        c[p]--;
        if(c[p]<0||b[p]+tag<n-1)    return puts("-1"),0;
        b[p]-=n;q.ep(pll(b[p]-a[p],b[p]),p);
        tag++;
    }
    printf("%lld\n",-mn);
    // while(q.top().fi+tag>=n-1){
    //     cnt++;
    //     if(cnt%10000==0)printf("%lld %d\n",q.top().fi+tag,cnt);
    //     int p=q.top().se;q.pop();
    //     ll w=(b[p]+tag-a[p])/(n-1);
    //     if(b[p]+tag<n-1)    return puts("-1"),0;
    //     if(w){
    //         ans+=w;tag+=w;
    //         b[p]-=w*n;
    //         q.ep(b[p]-a[p],p);
    //     }
    //     else break;
    // }
    // debug("cnt = %d\n",cnt);
}
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=3e5+10;
bool mem1;
int n;
int a[maxn],b[maxn],c[maxn];
ll s[maxn];
priority_queue<pli> q;
bool mem2;
bool check(int x){
    while(!q.empty())q.pop();
    ll now=0;
    for(int i=1;i<=n;i++){
        while(!q.empty()&&q.top().fi-s[i]-c[i]>0){
            ll w=q.top().fi-s[i-1];int d=q.top().se;q.pop();
            now+=1ll*w*d;x+=d;
        }
        now+=a[i]-1ll*x*b[i];
        while(now<0&&!q.empty()){
            ll w=q.top().fi-s[i];int d=q.top().se;q.pop();
            if(w>0){
                if(now+1ll*d*w<=0)   now+=1ll*d*w,x+=d;
                else{
                    int del=(-now+w-1)/w;
                    now+=1ll*del*w;assert(del<=d&&now>=0&&now-w<0);
                    x+=del;
                    if(d^del)   q.ep(w+s[i],d-del);
                }
            }
            else break;
        }
        if(now<0)   return false;
        if(now/c[i]>=x) return true;
        int d=now/c[i];
        if(d){now-=1ll*d*c[i];x-=d;q.ep(c[i]+s[i],d);}
    }
    return !x;
}
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d%d",&a[i],&b[i],&c[i]),s[i]=s[i-1]+b[i];
    int l=1,r=1e6,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,l=mid+1;
        else    r=mid-1;
    }
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e5+10;
int n,m,v;ll V;
int a[maxn],b[maxn];
ll c[maxn];
set<pii> st[3],now;
inline void ins(int i){st[0].erase(pii(a[i],i));st[1].erase(pii(b[i],i));st[2].ep(b[i]-a[i],i);now.ep(a[i],i);}
inline void era(int i){st[0].ep(a[i],i);st[1].ep(b[i],i);st[2].erase(pii(b[i]-a[i],i));now.erase(pii(a[i],i));}
int main(){
    freopen("king.in","r",stdin);freopen("king.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%lld",&c[i]);
    sort(c+1,c+n+1,greater<ll>());for(int i=1;i<=n;i++)   c[i]+=c[i-1];
    for(int i=1;i<=m;i++)   scanf("%d%d",&a[i],&b[i]),gmx(b[i],a[i]);
    scanf("%lld",&V);v=min(V,(ll)n+m+m);
    for(int i=1;i<=m;i++)   st[0].ep(a[i],i),st[1].ep(b[i],i);
    ll ans=0,out=c[min(v,n)];
    for(int _=1;_<=m+m&&_<=v;_++){
        // printf("%d %d\n",x,i);
        int o=0;
        int mx=-1;
        if(!st[0].empty()){
            auto [x,i]=*--st[0].end();
            mx=x;
        }
        if(!now.empty()&&!st[1].empty()){
            int s=now.begin()->fi;
            auto [y,iy]=*--st[1].end();
            if(y-s>mx) o=1,mx=y-s;
        }
        if(!st[2].empty()){
            int s=(--st[2].end())->fi;
            if(s>mx) o=2;
        }
        if(!o)  ans+=(--st[0].end())->fi,ins((--st[0].end())->se);
        else if(o==1){
            ans-=now.begin()->fi;
            era(now.begin()->se);
            int y=(--st[1].end())->se;
            st[0].erase(pii(a[y],y));st[1].erase(pii(b[y],y));
            ans+=b[y];
        }
        else{
            ans+=(--st[2].end())->fi;
            int y=(--st[2].end())->se;
            st[2].erase(pii(b[y]-a[y],y));now.erase(pii(a[y],y));
        }
        gmx(out,ans+c[min(v-_,n)]);
    }
    printf("%lld\n",out);
}
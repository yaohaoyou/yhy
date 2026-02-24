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
int n,q;
int a[maxn],c[maxn],out[maxn];
pii b[maxn];
vector<pii> Q[maxn];
struct BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
}T[2];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   b[i]=pii(a[i],i);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)   c[i]=n+1-(lower_bound(b+1,b+n+1,pii(a[i],i))-b);
    for(int i=1;i<=q;i++){int x,y;scanf("%d%d",&x,&y);Q[x].eb(y,i);}
    for(int i=1;i<=n;i++){
        T[0].add(c[i],1);T[1].add(c[i],a[i]);
        for(auto [x,id]:Q[i]){
            int l=1,r=n,ans=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(T[1].que(mid)>=x)    ans=T[0].que(mid),r=mid-1;
                else    l=mid+1;
            }
            // printf("%d %d %d\n",x,id,T[1].que(n));
            out[id]=ans;
        }
    }
    for(int i=1;i<=q;i++)   printf("%d\n",out[i]);
}
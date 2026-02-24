#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=3e4+10,V=1e5+10;
int n;
int a[maxn];
struct BIT{
    int tr[V];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=V-10){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x-=lowbit(x);}return res;}
}T[2];
ll ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   T[1].add(a[i],1);
    for(int i=1;i<=n;i++){
        T[1].add(a[i],-1);
        ans+=1ll*T[0].que(a[i]-1)*(T[1].que(V)-T[1].que(a[i]));
        T[0].add(a[i],1);
    }
    printf("%lld\n",ans);
}
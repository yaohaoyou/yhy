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
const int maxn=2e5+10;
int n,q;
int a[maxn],b[maxn];ll c[maxn],ans[maxn];
vector<pii> v[maxn];
struct ques{int l,r,id;}Q[maxn];
inline ll sqr(int x){return 1ll*x*x;}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)   scanf("%lld",&c[i]);
    for(int i=1;i<=n;i++){
        int sum=v[a[i]].empty()?0:v[a[i]].back().se;
        sum+=b[i];
        v[a[i]].eb(i,sum);
    }
    for(int i=1;i<=q;i++)   scanf("%d%d",Q[i].l,Q[i].r),Q[i].id=i;
    for(int i=1;i<=q;i++){
        int l=Q[i].l,r=Q[i].r,id=Q[i].id;
        int res=-1;ll now=0;
        for(int x=1;x<=n;x++){
            int kr=lower_bound(v[x].begin(),v[x].end(),pii(r+1,0))-v[x].begin()-1,kl=lower_bound(v[x].begin(),v[x].end(),pii(l,0))-v[x].begin();
            if(kr>=0&&kl<v[x].size())now+=sqr(v[x][kr].se-(kl?v[x][kl-1].se:0));
            if(now>=c[x])   res=x;
        }
        ans[id]=res;
    }
}
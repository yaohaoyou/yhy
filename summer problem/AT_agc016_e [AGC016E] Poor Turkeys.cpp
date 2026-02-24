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
const int maxn=410,maxm=1e5+10;
int n,m;
bitset<maxn> a,bs[maxn];
pii E[maxm];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   scanf("%d%d",&E[i].fi,&E[i].se);
    for(int x=1;x<=n;x++){
        a.reset();a.set(x);
        bool flag=true;
        for(int i=m;i;i--){
            auto [u,v]=E[i];
            if(a[u]&&a[v]){flag=false;break;}
            if(a[u])    a.set(v);
            else if(a[v])    a.set(u);
        }
        if(flag)    bs[x]=a;
        else    bs[x].set();
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(!(bs[i]&bs[j]).any())    ans++;
    printf("%d\n",ans);
}
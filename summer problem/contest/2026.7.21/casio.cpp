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
const int maxn=3e5+10,V=4e7;
int q,p,n;
int ans[maxn];
pii a[maxn];
bool f[V+10],pr[V+10];
int main(){
    freopen("casio.in","r",stdin);freopen("casio.out","w",stdout);
    scanf("%d%d",&q,&p);
    for(int i=1;i<=q;i++)   scanf("%d",&a[i].fi),a[i].se=i;
    sort(a+1,a+q+1);
    for(int i=2;i<=p;i++){
        if(f[i])    continue;
        pr[i]=true;
        for(int j=i;j<=V;j+=i)f[j]=true;
    }
    int now=2;
    for(int i=1;i<=q;i++){
        now=max(now,a[i].fi);
        while(f[now]&&!pr[now])now++;
        ans[a[i].se]=now;
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}
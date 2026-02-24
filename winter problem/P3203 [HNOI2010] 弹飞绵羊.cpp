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
const int maxn=2e5+10,B=450;
int n,q;
int a[maxn];
int id[maxn],f[maxn],to[maxn],bl[maxn],br[maxn];
void build(int x){
    for(int i=br[x];i>=bl[x];i--){
        if(i+a[i]>br[x])    f[i]=1,to[i]=i+a[i];
        else    f[i]=f[i+a[i]]+1,to[i]=to[i+a[i]];
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,n),build(i);
    scanf("%d",&q);
    while(q--){
        int op,x,k;
        scanf("%d%d",&op,&x);x++;
        if(op==1){
            int ans=0;
            while(x<=n) ans+=f[x],x=to[x];
            printf("%d\n",ans);
        }
        else{
            scanf("%d",&k);
            a[x]=k,build(id[x]);
        }
    }
}
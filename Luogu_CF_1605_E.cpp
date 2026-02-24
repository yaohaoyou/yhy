#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,V=1e6+10;
int n,q;
int a[maxn],b[maxn],c[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    scanf("%d",&q);
    while(q--){
        int ans=0;
        memc(c,a);
        scanf("%d",&b[1]);
        for(int i=1;i<=n;i++){
            int d=b[i]-a[i];
            ans+=abs(d);
            printf("%d ",abs(d));
            for(int j=i;j<=n;j+=i)  a[j]+=d;
        }
        memc(a,c);
        printf("%d\n",ans);
    }
}
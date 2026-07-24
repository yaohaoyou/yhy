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
const int maxn=1e5+10;
int n,q;
int a[maxn],b[maxn];
void matt(int _cases){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    while(q--){
        int op,l,r;scanf("%d%d%d",&op,&l,&r);
        if(op==1){
            for(int i=l;i<=r;i++)   a[i]+=b[i];
        }
        else{
            int g=a[l];
            for(int i=l+1;i<=r;i++){if(a[i]%g)g=__gcd(a[i],g);if(g==1)break;}
            printf("%d\n",g);
        }
    }
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
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
int n;
int a[maxn],b[maxn],c[maxn];
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[a[i]]=i;
    for(int i=3;i<=n;i++){
        if(b[i-1]>b[i]&&b[i-2]>b[i]){
            int p=b[i],x=b[i-1],y=b[i-2];
            a[p]-=2;a[x]++;a[y]++;
            b[a[p]]=p;b[a[x]]=x;b[a[y]]=y;
            i-=3;
        }
    }
    for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
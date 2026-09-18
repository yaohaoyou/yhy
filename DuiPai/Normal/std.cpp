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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n;
int a[maxn],b[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]),b[i]=a[i];
        // if(a[i]==4) printf("i = %d\n",i);
    }
    int T=1e6;
    int ans=1e9;
    while(T--){
        // printf("! %d\n",a[43]);
        int x=max_element(a+1,a+n+1)-a;
        // printf("%d\n",a[x]);
        gmn(ans,a[x]-*min_element(a+1,a+n+1));
        // printf("%d %d\n",b[x],b[min_element(a+1,a+n+1)-a]);
        // printf("%d %d\n",a[x],*min_element(a+1,a+n+1));
        // if(ans==45) break;
        if(a[x]>=n-1){
            a[x]-=n-1;
            for(int i=1;i<=n;i++)if(i^x)a[i]++;
        }
        else break;
    }
    printf("%d\n",ans);
    // for(int i=1;i<=n;i++)   scanf("%d",&a[i]),a[i]%=n;
    // sort(a+1,a+n+1);
    // int ans=a[n]-a[1];
    // for(int i=2;i<=n;i++)   gmn(ans,a[i-1]+n-a[i]);
    // printf("%d\n",ans);
}
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
const int maxn=3510;
int n;
int a[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
inline int pos(int &x,int &y,int &z,int p){(p>=x)&&(p++);(p>=y)&&(p++);(p>=z)&&(p++);return p;}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    if(!(n&1)){
        int ans=1e9;
        for(int i=1;i<=n/2;i++) gmn(ans,a[n/2+i]-a[i]);
        printf("%d\n",ans);
        return 0;
    }
    int ans=-1;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int l=lower_bound(a+1,a+n+1,a[j]+a[j]-a[i])-a;
            if(a[l]!=a[j]+a[j]-a[i])    continue;
            int m=(n-3)/2,res=a[j]-a[i];
            if(res<=ans)    continue;
            for(int k=1;k<i&&k<=m;k++)gmn(res,a[pos(i,j,l,m+k)]-a[k]);
            for(int k=i+1;k<j&&k<=m+1;k++)gmn(res,a[pos(i,j,l,m+k-1)]-a[k]);
            for(int k=j+1;k<l&&k<=m+2;k++)gmn(res,a[pos(i,j,l,m+k-2)]-a[k]);
            for(int k=l+1;k<=n&&k<=m+3;k++)gmn(res,a[pos(i,j,l,m+k-3)]-a[k]);
            gmx(ans,res);
        }
    }
    printf("%d\n",ans);
}
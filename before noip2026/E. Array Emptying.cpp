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
const int maxn=2e5+10;
bool mem1;
int n,k;
int a[maxn],b[maxn];
bool mem2;
bool check(int x){
    int K=(x-n)/2,w=x+k-1;
    fill(b,b+n+1,0);
    for(int i=1;i<=n;i++)   b[a[i]]++;
    for(int i=n;i;i--){
        int d=min(w-i+1,b[i]);
        // printf("%d %d %d\n",i,w,b[i]);
        w-=d;b[i]-=d;
        while(b[i]){
            if(i==1)    return false;
            K--;if(K<0) return false;
            b[i+1>>1]+=2;
            b[i]--;
        }
    }
    return w>=k-1;
}
int T;
void matt(int _cases){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    // sort(a+1,a+n+1);for(int i=1;i<=n;i++)debug("%d ",a[i]);
    // printf("%d\n",check(17));
    // if(T==10000&&_cases==1092){
    //     printf("%d %d\n",n,k);
    //     for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    //     exit(0);
    // }
    // if(T==10000)    return;
    int l=0,r=1e8,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(n+mid*2))  ans=n+mid*2,r=mid-1;
        else    l=mid+1;
    }
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
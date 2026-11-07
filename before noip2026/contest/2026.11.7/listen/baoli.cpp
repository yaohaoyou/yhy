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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n,q;
int a[maxn],b[maxn];
bool A[20],B[20];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    int ans=0,mx=0;pii res;
    for(int i=0;i<(1<<n);i++){
        mems(A,0);mems(B,0);
        for(int j=1;j<=n;j++)if(i&(1<<j-1))A[a[j]]=B[b[j]]=true;else A[b[j]]=B[a[j]]=true;
        int x=0,y=0;
        while(A[x])x++;while(B[y])y++;
        // printf("%d %d\n",x,y);
        gmx(mx,min(x,y));
        if(ans<x+y) ans=x+y,res=pii(x,y);
    }
    // printf("(%d,%d) %d\n",res.fi,res.se,mx);
    printf("%d\n",ans);
}
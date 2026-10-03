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
const int maxn=1e5+10;
bool mem1;
int n;
int a[maxn],p[maxn];
bool mem2;
inline int lcm(int x,int y){return x/__gcd(x,y)*y;}
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    iota(p+1,p+n+1,1);
    int ans=0;
    do{
        int res=0;
        for(int i=1;i<n;i++)res+=lcm(a[p[i]],a[p[i+1]]);
        gmx(ans,res);
    }while(next_permutation(p+1,p+n+1));
    iota(p+1,p+n+1,1);
    do{
        int res=0;
        for(int i=1;i<n;i++)res+=lcm(a[p[i]],a[p[i+1]]);
        if(ans==res){
            for(int i=1;i<=n;i++)   printf("%d ",a[p[i]]);
            puts("");
        }
    }while(next_permutation(p+1,p+n+1));
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
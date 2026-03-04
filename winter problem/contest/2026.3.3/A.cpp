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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2e5+10;
int n;
int a[maxn],b[maxn];
int f[maxn][3];  //  0:前 i 个匹配完毕，1:上 i-1 和下 i 未匹配，2:上 i 和下 i-1 未匹配
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(~a[i])   b[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        if(~a[i]){
            if(a[i]<i-1){
                
            }
        }
    }
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
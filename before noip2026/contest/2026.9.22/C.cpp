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
const int maxn=1010;
bool mem1;
int n;
int a[maxn],b[maxn];
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%1d",&b[i]);
    int cnt=0;for(int i=1;i<=n;i++)cnt+=a[i]!=b[i];
    vector<pii> ans;
    if(cnt*2<=n){
        for(int i=1;i<=n;i++)if(a[i]!=b[i])ans.eb(i,i);
    }
    else{
        ans.eb(1,n);
        for(int i=1;i<=n;i++)if(a[i]==b[i])ans.eb(i,i);
    }
    printf("%d\n",ans.size());
    for(pii i:ans)printf("%d %d\n",i.fi,i.se);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
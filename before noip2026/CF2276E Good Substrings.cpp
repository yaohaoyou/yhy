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
#define cpy(arr1,arr2,siz) fill(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=3e5+10;
bool mem1;
int n;
char a[maxn];
inline int id(char c){if(c=='2')return 0;if(c=='0')return 1;if(c=='5')return 2;if(c=='6')return 3;return -1;}
int nx[maxn][4];
ll c[maxn],d[maxn];
bool mem2;
void matt(int _cases){
    fll(c,0,n+5);fll(d,0,n+5);
    scanf("%d%s",&n,a+1);
    mems(nx[n+1],0);
    for(int i=n;i;i--){
        memc(nx[i],nx[i+1]);
        if(id(a[i])>=0) nx[i][id(a[i])]=i;
    }
    for(int i=1;i<=n;i++){
        int p=i;p=nx[p][0];p=nx[p][1];p=nx[p][0];
        int r=n;if(nx[p][2])r=nx[p][2]-1;
        c[i]+=r-i+2;d[i]--;d[r+2]++;
        if(nx[p][2]&&nx[p][3]){
            r=max(nx[p][2],nx[p][3]);
            c[i]+=n-r+1;d[r+1]--;
        }
    }
    for(int i=1;i<=n;i++)   d[i]+=d[i-1],c[i]+=c[i-1]+d[i],printf("%lld ",c[i]);puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
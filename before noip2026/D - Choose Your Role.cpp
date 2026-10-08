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
const int maxn=210;
int n,k;
bool a[maxn][maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)a[i][i]=1;
    puts("Second");fflush(stdout);
    while(true){
        int x,y;scanf("%d%d",&x,&y);if(!x)return 0;
        vector<int> v;
        while(y--){
            for(int i=1;i<=n;i++)if(!a[x][i]){
                a[x][i]=a[i][x]=true;v.eb(i);
                break;
            }
        }
        printf("%d\n",v.size());
        for(int i:v)printf("%d ",i);puts("");fflush(stdout);
    }
}
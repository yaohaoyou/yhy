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
bool mem1;
const int maxn=1e5+10,lgV=29;
int n,m,q;
int a[maxn],b[maxn];
int sa[lgV+1][maxn],sb[lgV+1][maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    for(int j=0;j<=lgV;j++){
        for(int i=1;i<=n;i++){
            if(a[i]&(1<<j))sa[j][i]=sa[j][i-1]+1;
            else    sa[j][i]=sa[j][i-1];
        }
        for(int i=1;i<=m;i++){
            if(b[i]&(1<<j))sb[j][i]=sb[j][i-1]+1;
            else    sb[j][i]=sb[j][i-1];
        }
    }
    scanf("%d",&q);
    while(q--){
        int l,r,L,R;scanf("%d%d%d%d",&l,&r,&L,&R);
        int ans=0;
        for(int i=lgV;~i;i--)if(((sa[i][r]-sa[i][l-1])&1)&&((sb[i][R]-sb[i][L-1])&1))ans|=1<<i;
        printf("%d\n",ans);
    }
}
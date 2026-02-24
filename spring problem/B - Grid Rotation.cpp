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
const int maxn=110;
int n;
char s[maxn][maxn],t[maxn][maxn],tt[maxn][maxn];
int calc(){
    int res=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)res+=(s[i][j]!=t[i][j]);
    return res;
}
void round(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            tt[j][n-i+1]=t[i][j];
    memc(t,tt);
    // for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%c ",t[i][j]);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%s",s[i]+1);
    for(int i=1;i<=n;i++)   scanf("%s",t[i]+1);
    int ans=calc();round();
    ans=min(ans,calc()+3);round();
    ans=min(ans,calc()+2);round();
    ans=min(ans,calc()+1);
    printf("%d\n",ans);
}
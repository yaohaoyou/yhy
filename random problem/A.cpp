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
const int maxn=1010;
int n,a,b;
int mp[maxn][maxn];
bool c[maxn][maxn];
void matt(){
    scanf("%d%d%d",&n,&a,&b);swap(a,b);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)c[i][j]=false;
    for(int i=1;i<=n;i++){
        char s[maxn];scanf("%s",s+1);
        for(int j=1;j<=n;j++)   mp[i][j]=s[j]=='W'?0:((s[j]=='B')+1);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if(mp[i][j]==2){
                c[i][j]=true;
                ans++;
                // printf("%d %d\n",i,j);
                if(i<=a||j<=b||!mp[i-a][j-b])   return puts("-1"),void();
                if(!c[i-a][j-b])    c[i-a][j-b]=true,ans++;
            }
            else if(mp[i][j]==1){
                if(i<=a||j<=b||!mp[i-a][j-b])   c[i][j]=true,ans++;
                else if(mp[i-a][j-b]==1&&!c[i-a][j-b])    c[i][j]=true,ans++;
                // else    continue;
                // printf("%d %d\n",i,j);
            }
        }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}
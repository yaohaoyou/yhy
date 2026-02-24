#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=110,maxk=maxn*maxn*maxn;
int n,m;
bool mp[maxn][maxn][maxn],v1[maxn][maxn],v2[maxn][maxn],v3[maxn][maxn];
piii a[maxk];
void dfs(int x){
    if(x>m){
        mems(v1,0);mems(v2,0);mems(v3,0);
        for(int i=1;i<=m;i++){
            int xx=a[i].fi,yy=a[i].se.fi,zz=a[i].se.se;
            v1[xx][yy] = 1;v2[xx][zz] = 1;v3[yy][zz] = 1;
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(v1[i][j]!=v2[i][j]||v2[i][j]!=v3[i][j])  return;
        for(int i=1;i<=m;i++)   printf("%d %d %d\n",a[i].fi,a[i].se.fi,a[i].se.se);
        puts("");
        // while(1);
        // exit(0);
        return;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++){
                if(!mp[i][j][k]){
                    mp[i][j][k]=true;
                    a[x]=piii(i,pii(j,k));
                    dfs(x+1);
                    mp[i][j][k]=false;
                }
            }
}
namespace SubAll{
    void solve(){
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                for(int k=j+1;k<=n;k++){
                    int b[3]={i,j,k};
                    if(m<6) break;
                    printf("%d %d %d\n",b[0],b[1],b[2]);printf("%d %d %d\n",b[0],b[2],b[1]);
                    printf("%d %d %d\n",b[1],b[0],b[2]);printf("%d %d %d\n",b[1],b[2],b[0]);
                    printf("%d %d %d\n",b[2],b[0],b[1]);printf("%d %d %d\n",b[2],b[1],b[0]);
                    m-=6;
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j)    continue;
                if(m<3) break;
                int b[2]={i,j};
                printf("%d %d %d\n",b[0],b[0],b[1]);printf("%d %d %d\n",b[0],b[1],b[0]);printf("%d %d %d\n",b[1],b[0],b[0]);
                m-=3;
            }
        }
        for(int i=1;i<=n;i++){
            if(!m)  exit(0);
            printf("%d %d %d\n",i,i,i);
            m--;
        }
        exit(0);
    }
}
int main(){
    freopen("D:\\yhy\\DuiPai\\SPJ\\data.in","r",stdin);freopen("D:\\yhy\\DuiPai\\SPJ\\mine.out","w",stdout);
    scanf("%d%d",&n,&m);
    if(m<=n){
        for(int i=1;i<=m;i++)   printf("%d %d %d\n",i,i,i);
        return 0;
    }
    SubAll::solve();
    // dfs(1);
}
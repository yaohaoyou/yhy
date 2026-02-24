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
const int maxn=10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
struct DSU{
    int fa[maxn*maxn];
    void init(){iota(fa+1,fa+n*m+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int n,m,k,d,cnt;
int ans;
int a[maxn][maxn],b[maxn][maxn],s1[maxn],s2[maxn],s[2][maxn];
void dfs(int x,int y){
    if(cnt>n+m) return;
    if(x>n){
        if(cnt^(n+m))   return;
        int sum=n+m;
        for(int i=0;i<(1<<n+m);i++){
            int ss=0;
            for(int j=1;j<=n;j++)
                for(int k=1;k<=m;k++)if((i&(1<<j-1))||(i&(1<<k+n-1)))ss+=a[j][k];
            if(__builtin_popcount(i)>ss)return;
        }
        memc(s[0],s1);memc(s[1],s2);memc(b,a);
        while(true){
            bool flag=false;
            for(int i=1;i<=n;i++)if(s[0][i]==1){
                flag=true;
                s[0][i]--;
                sum--;
                for(int j=1;j<=m;j++)if(b[i][j]){b[i][j]=0;s[1][j]--;break;}
            }
            for(int i=1;i<=m;i++)if(s[1][i]==1){
                flag=true;
                s[1][i]--;
                sum--;
                for(int j=1;j<=n;j++)if(b[j][i]){b[j][i]=0;s[0][j]--;break;}
            }
            if(!flag)   break;
        }
        // for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%d ",a[i][j]);
        U.init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                
            }
        }
        // printf("sum = %d\n\n",sum);
        // if(sum%4)exit(0);
        madd(ans,qpow(2,k));
        return;
    }
    if(y>m) return dfs(x+1,1);
    if(s1[x]+1<=d&&s2[y]+1<=d){
        s1[x]++;s2[y]++;
        a[x][y]=1;
        cnt++;
        dfs(x,y+1);
        cnt--;
        s1[x]--;s2[y]--;
    }
    a[x][y]=0;
    dfs(x,y+1);
}
int main(){
    scanf("%d%d%d%d",&n,&m,&k,&d);
    dfs(1,1);
    printf("%d\n",ans);
}
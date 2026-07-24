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
const int maxn=1e3+10;
int n,m,k;
int a[maxn][maxn],b[maxn][maxn],c[maxn][maxn],out[maxn][maxn];
char s[maxn];
void dfs(int i,int j){
    if(a[i][j]>=0&&(!~out[i][j+1])) out[i][j+1]=out[i][j]^a[i][j],dfs(i,j+1);
    if(b[i][j]>=0&&(!~out[i+1][j])) out[i+1][j]=out[i][j]^b[i][j],dfs(i+1,j);
    if(a[i][j-1]>=0&&(!~out[i][j-1]))   out[i][j-1]=out[i][j]^a[i][j-1],dfs(i,j-1);
    if(b[i-1][j]>=0&&(!~out[i-1][j]))   out[i-1][j]=out[i][j]^b[i-1][j],dfs(i-1,j);
}
void matt(int _cases){
    bool flag=false;
    scanf("%d%d%d",&n,&m,&k);
    mems(a,-1);mems(b,-1);
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<m;j++)    a[i][j]=s[j]=='N';
        if(i^n){
            scanf("%s",s+1);
            for(int j=1;j<=m;j++)    b[i][j]=s[j]=='N';
        }
    }
    if(k==1){
        int c1=0,c2=0;
        for(int i=1;i<=n;i++)for(int j=1;j<m;j++)c1+=a[i][j],c2++;
        for(int i=1;i<n;i++)for(int j=1;j<=m;j++)c1+=b[i][j],c2++;
        c1=c2-c1;
        if(c1*4>=c2*3){
            puts("YES");
            for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++)printf("1 ");
        }
        else puts("NO");
        return;
    }
    if(m==2){
        flag=true;
        swap(n,m);
        int H = m, W = n;          // 交换后的 n,m 分别对应原来的 m,n，这里 H 为原高，W 为原宽
        memc(c, a); memc(out, b);  // 暂存原来的 a,b
        mems(a, -1); mems(b, -1);  // 清空 a,b
        for (int i = 1; i <= W; ++i)
            for (int j = 1; j < H; ++j)
                a[i][j] = out[j][i];   // 新水平约束来自原垂直约束
        for (int i = 1; i < W; ++i)
            for (int j = 1; j <= H; ++j)
                b[i][j] = c[j][i];     // 新垂直约束来自原水平约束
    }
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++){
            if(a[i][j]>=0&&b[i][j]>=0&&a[i+1][j]>=0&&b[i][j+1]>=0)  c[i][j]=(a[i][j]+b[i][j]+a[i+1][j]+b[i][j+1])&1;
            else c[i][j]=0;
        }
    for(int i=1;i<n;i++){
        int res=0;
        vector<int> v;v.clear();
        for(int j=1;j<m;j++)if(c[i][j])v.eb(j);
        if(v.empty())   continue;
        if(v.size()&1)  v.eb(m);
        for(int j=0;j<v.size();j+=2)    res+=v[j+1]-v[j];
        if(res<=m/2){
            for(int j=0;j<v.size();j+=2){
                int l=v[j],r=v[j+1];
                for(int x=l+1;x<=r;x++)if(b[i][x]>=0)b[i][x]^=1;
            }
            continue;
        }
        res=v[0];
        for(int j=1;j+1<v.size();j+=2)  res+=v[j+1]-v[j];
        assert(res<=m/2);
        {
            int l=0,r=v[0];
            for(int x=l+1;x<=r;x++)if(b[i][x]>=0)b[i][x]^=1;
        }
        for(int j=1;j+1<v.size();j+=2){
            int l=v[j],r=v[j+1];
            for(int x=l+1;x<=r;x++)if(b[i][x]>=0)b[i][x]^=1;
        }
        {
            int l=v.back(),r=m;
            for(int x=l+1;x<=r;x++)if(b[i][x]>=0)b[i][x]^=1;
        }
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)out[i][j]=-1;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(!~out[i][j])out[i][j]=0,dfs(i,j);
    if(flag){
        swap(n,m);
        memc(c, out);                 // 暂存已染色的转置网格
        mems(out, -1);
        for (int i = 1; i <= n; ++i)  // 此时 n 为原高，m 为原宽
            for (int j = 1; j <= m; ++j)
                out[i][j] = c[j][i];  // 转置回原方向
    }
    puts("YES");
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++)printf("%d ",out[i][j]+1);
}
int main(){int T=1;for(int i=1;i<=T;i++)matt(i);}
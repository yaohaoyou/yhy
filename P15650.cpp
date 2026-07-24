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
const int maxn=210,maxk=3010,B=70,inf=0x3f3f3f3f;
bool mem1;
int n,K;
int a[maxn],nxt[maxn],s[maxn][2],up[maxn][2],out[maxk];
int f[maxn][B][maxk][2];
struct node{int i,j,k;bool o,ch;}op[maxn][B][maxk][2];
bool mem2;
void matt(int _cases){
    mems(s,0);mems(up,0);
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    if(n==1){
        if(!a[1])   return puts("Impossible"),void();
        if(K==1)    return puts("10"),void();
    }
    for(int i=2;i<=n;i++){
        int j=nxt[i-1];
        while(j&&a[j+1]!=a[i])j=nxt[j];
        if(a[j+1]==a[i])    j++;
        nxt[i]=j;
    }
    s[0][a[1]]++;
    for(int i=1;i<=n;i++){
        memc(s[i],s[nxt[i]]);memc(up[i],up[nxt[i]]);
        if(i^n)s[i][a[i+1]]++,up[i][a[i+1]]=i;
    }
    int*dp;node *opt;
    mems(f,0x3f);
    f[0][0][0][0]=0;
    for(int k=0;k<K;k++){
        for(int i=n;~i;i--){
            for(int j=0;j<=K&&j<B;j++){
                int f0=f[i][j][k][0],f1=f[i][j][k][1];
                if(f0==inf&&f1==inf)    continue;
                {
                        int t=up[i][0],nw=0;t+=(!a[t+1]);
                        nw=s[i][0]+s[i][1]-(t==n);
                        dp=f[t][j+s[i][1]][k+j+nw];opt=op[t][j+s[i][1]][k+j+nw];
                        if(dp[t==n]>f0+1)   dp[t==n]=f0+1,opt[t==n]={i,j,k,0,0};
                        if(dp[1]>f1+1)  dp[1]=f1+1,opt[1]={i,j,k,1,0};
                    }
                    {
                        int t=up[i][1],nw=0;t+=a[t+1];
                        nw=s[i][1]-(t==n);
                        dp=f[t][j][k+j+nw];opt=op[t][j][k+j+nw];
                        if(dp[t==n]>f0+1)   dp[t==n]=f0+1,opt[t==n]={i,j,k,0,1};
                        if(dp[1]>f1+1)  dp[1]=f1+1,opt[1]={i,j,k,1,1};
                    }
            }
        }
    }
    int ans=f[0][0][0][1];node o;
    for(int i=0;i<=n;i++)for(int j=0;j<=K&&j<B;j++)if(ans>f[i][j][K][1])ans=f[i][j][K][1],o={i,j,K,1};
    if(ans==f[0][0][0][1]) return puts("Impossible"),void();
    int i=o.i,j=o.j,k=o.k,p=o.o;
    while(true){
        node x=op[i][j][k][p];
        out[f[i][j][k][p]]=x.ch;
        if(f[i][j][k][p]==1)    break;
        i=x.i;j=x.j;k=x.k;p=x.o;
    }
    for(int i=1;i<=ans;i++)printf("%d",out[i]);puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}
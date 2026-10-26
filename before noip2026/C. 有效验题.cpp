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
const int maxn=810,mod=998244353;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
int n,m;
int a[maxn],p[maxn];
mit f[maxn][maxn],g[maxn][maxn],h[maxn][maxn],s[maxn][maxn];  // f[i][j] 表示 i+1 的最前的入点在 j 的方案数
vector<int> v[maxn];
void data(){
    srand(time(0));
    n=8;m=rand()%10+1;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++)   printf("%d ",rand()%(m-1)+1);
    exit(0);
}
void dp(int c0,int c1){
    int x=v[c0].size()+1,y=v[c1].size()+1;
    for(int i=0;i<=x+1;i++)for(int j=0;j<=y+1;j++)s[i][j]=0;
    for(int j=y;j;j--)s[x][j]=s[x][j+1]+g[x][j];
    for(int j=x;j;j--)s[j][y]=s[j+1][y]+g[j][y];
    for(int jj=x-1;jj;jj--){
        int j=v[c0][jj-1];
        for(int kk=y-1;kk;kk--){
            int k=v[c1][kk-1];
            if(k>=j)g[jj][kk]+=s[jj+1][kk+1];
            s[jj][kk]=s[jj+1][kk]+s[jj][kk+1]-s[jj+1][kk+1]+g[jj][kk];
        }
    }
}
inline void rbd(int x){for(int i=1;i<=n;i++)if(a[i]==x)a[i]=-1;for(int i=0;i<v[x].size();i++)p[v[x][i]]=i+1,a[v[x][i]]=x;}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),v[a[i]].eb(i),p[i]=v[a[i]].size();
    mit ans=0;
    vector<int> VM=v[m-1];VM.insert(VM.begin(),0);
    for(int o:VM){
        mems(f,0);mems(h,0);
        v[m-1].clear();
        if(o){
            mems(g,0);
            for(int i:VM)if(i&&i<=o)v[m-1].eb(i);rbd(m-1);

            for(int i:v[0])if(i>o)g[p[o]][p[i]]=1;
            dp(m-1,0);
            for(int j:v[0])for(int k:v[m-1])if(j>k)f[m+1][j]+=g[p[k]][p[j]],h[m+1][j]+=g[p[k]][p[j]];
        }
        else    f[m+1][n+1]=1;
        v[m-1].clear();for(int i:VM)if(i>o)v[m-1].eb(i);rbd(m-1);
        for(int i=0;i<m;i++){
            int x=v[i].size()+1,y=v[i+1].size()+1,pr=i?i-1:m+1;
            for(int j=0;j<=x+1;j++)for(int k=0;k<=y+1;k++)g[j][k]=0;
            g[x][y]=f[pr][n+1];
            for(int j:v[i])g[p[j]][y]=f[pr][j];
            dp(i,i+1);
            for(int j=1;j<=x;j++)   f[i][n+1]+=g[j][y];
            for(int k:v[i+1])for(int j:v[i])if(j<=k)f[i][k]+=g[p[j]][p[k]];else break;
        }
        ans+=f[m-1][n+1];
        if(o&&!(m&1)){
            v[m-1].insert(v[m-1].begin(),o);rbd(m-1);
            for(int i=0;i<m-1;i++){
                int x=v[i].size()+1,y=v[i+1].size()+1,pr=i?i-1:m+1;
                for(int j=0;j<=x+1;j++)for(int k=0;k<=y+1;k++)g[j][k]=0;
                for(int k:v[i+1])for(int j:v[i])if(j<k)g[p[j]][p[k]]=h[pr][j];else break;
                dp(i,i+1);
                for(int k:v[i+1])for(int j:v[i])if(j<k)h[i][k]+=g[p[j]][p[k]];else break;
            }
            ans-=h[m-2][o];
        }
        v[m-1]=VM;rbd(m-1);
    }
    printf("%d\n",ans);
}
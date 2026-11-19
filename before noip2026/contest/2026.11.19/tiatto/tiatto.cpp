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
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxm=110,maxn=(1<<6)+10,mod=1e9+7;
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
// mit f[maxm][maxn];
map<vector<int>,mit> f[2];
struct DSU{
    int fa[maxm];
    void init(){iota(fa,fa+n+n+1,0);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){x=find(x);y=find(y);fa[x]=y;}
    inline int operator[](int x){return find(x);}
}U;
int b[maxn];
vector<int> calc(int s,int u0,bool flg=false){
    fll(b,-1,n+n);
    vector<int> v(n+1);
    // if(flg){
        // for(int i=0;i<n;i++)printf("%d ",U[i+(flg*n)]);puts("");
    // }
    for(int i=0;i<n;i++)if(s&(1<<i)){
        int ui=U[i+(flg*n)];
        if(!~b[ui])  b[ui]=i;
        v[i]=b[ui];
    }
    else    v[i]=n;
    if(!~b[u0])  return vector<int>();
    v[n]=b[u0];
    // for(int i:v)printf("%d ",i);puts("\n");
    return v;
}
bool mem2;
int main(){
    freopen("tiatto.in","r",stdin);freopen("tiatto.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<(1<<n);i+=2){
        U.init();
        // int s=0,j=0;while(j<n&&(i&(1<<j)))s|=1<<j,j++;
        for(int j=1;j<n;j++)if((i&(1<<j))&&(i&(1<<j-1)))U.merge(j-1,j);
        vector<int> v=calc(i,U[0]);
        if(!v.empty())  f[1][v]+=1;
    }
    for(int i=1;i<m;i++){
        // printf("i = %d\n",i);
        // for(int j=1;j<(1<<n);j++)if(f[i][j])
        for(auto [j,dp]:f[i&1]){
            // printf("f : ");for(int x:j)printf("%d ",x);printf("= %d\n",dp);
            for(int k=1;k<(1<<n);k++){
                U.init();for(int x=0;x<n;x++)if(j[x]^n)U.fa[x]=j[x];
                for(int x=0;x<n;x++)if(k&(1<<x)){
                    if(x&&(k&(1<<x-1))) U.merge(x-1+n,x+n);
                    if(j[x]^n)  U.merge(x,x+n);
                }
                // for(int x=0;x<n;x++)if((k&(1<<x))&&U[x]==U[n])s|=1<<x;
                vector<int> v=calc(k,U[j[n]],1);
                if(!v.empty())  f[(i+1)&1][v]+=dp;
            }
        }
        f[i&1].clear();
    }
    mit ans=0;
    for(auto [i,dp]:f[m&1])if(i[n-1]==i[n])ans+=dp;
    printf("%d\n",ans);
}
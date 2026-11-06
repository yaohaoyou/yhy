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
const int maxn=10,mod=998244353;
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
int a[maxn],b[maxn],c[maxn][maxn],d[maxn][maxn],s[maxn][maxn],h[maxn][maxn],ha[maxn],hb[maxn];
mit ans;
void makeC(int x,int y){
    if(x>n){
        vector<pii> v;
        int now=0,al=accumulate(ha+1,ha+n+1,0),w=0;
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(c[i][j]==2)v.eb(i,j);else if(c[i][j]==1)now++;
        mems(d,0);
        for(int i=0;i<(1<<v.size());i++)if(now+__builtin_popcount(i)<=al){
            for(int j=0;j<v.size();j++)d[v[j].fi][v[j].se]=bool(i&(1<<j));
            bool fl=true;
            for(int j=1;j<=n;j++){
                int cnt=0;
                for(int k=1;k<=m;k++)cnt+=(c[j][k]==1||d[j][k]==1);
                if(cnt<a[j]){fl=false;break;}
            }
            if(!fl) continue;
            for(int j=1;j<=m;j++){
                int cnt=0;
                for(int k=1;k<=n;k++)cnt+=(c[k][j]==1||d[k][j]==1);
                if(cnt<b[j]){fl=false;break;}
            }
            if(!fl) continue;
            if(now+__builtin_popcount(i)<al)    return;
            w++;if(w>1)return;
        }
        ans+=1;
        return;
    }
    if(y>m) return makeC(x+1,1);
    for(int i=0;i<=2;i++)if(s[x][y]&(1<<i)){
        if(i!=2&&h[x][y]!=i)    continue;
        int bef=ans;
        c[x][y]=i;
        makeC(x,y+1);
        if(bef==ans)    break;
    }
}
void makeB(int x){
    if(x>m) return makeC(1,1);
    for(int i=hb[x];~i;i--){
        int bef=ans;
        b[x]=i;
        makeB(x+1);
        if(ans==bef)    break;
    }
}
void makeA(int x){
    if(x>n) return makeB(1);
    for(int i=ha[x];~i;i--){
        int bef=ans;
        a[x]=i;
        makeA(x+1);
        if(ans==bef)    break;
    }
}
bool mem2;
int main(){
    freopen("matrix.in","r",stdin);freopen("matrix.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%*d%d%d",&n,&m);
    bool fl=true;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%1d",&s[i][j]),fl&=!(s[i][j]&4);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%1d",&h[i][j]);
    for(int i=1;i<=n;i++)   ha[i]=accumulate(h[i]+1,h[i]+m+1,0);
    for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)hb[i]+=h[j][i];
    if(!accumulate(ha+1,ha+n+1,0)){
        ans=1;
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(!(s[i][j]&1))return puts("0"),0;else if(s[i][j]&4)ans*=2;
        printf("%d\n",ans);
        return 0;
    }
    if(fl){
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(!(s[i][j]&(1<<h[i][j])))return puts("0"),0;
        ans=1;
        for(int i=1;i<=n;i++)ans*=(ha[i]+1);
        for(int i=1;i<=m;i++)ans*=(hb[i]+1);
        printf("%d\n",ans);
        return 0;
    }
    makeA(1);
    printf("%d\n",ans);
}
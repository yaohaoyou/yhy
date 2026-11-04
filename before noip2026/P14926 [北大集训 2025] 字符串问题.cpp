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
const int maxn=1e6+10,mod=998244353,inf=1e9;
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
int n;
char s[maxn];
mit f[maxn];
int sa[2][maxn],rk[2][maxn],ht[2][maxn],y[maxn],buc[maxn];
mit c[maxn];
struct ST{
    int len;
    int st[21][maxn<<1];
    void build(int *arr){
        st[0][++len]=inf;
        for(int i=2;i<=n;i++)   st[0][++len]=arr[i],st[0][++len]=inf;
        for(int i=1;i<=20;i++)for(int j=1;j<=len;j++)st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int query(int l,int r){int k=31^__builtin_clz(r-l+1);return min(st[k][l],st[k][r-(1<<k)+1]);}
}st[2];
inline int lcp(int x,int y){assert(x^y);x=(rk[0][x]<<1)-1;y=(rk[0][y]<<1)-1;if(x>y)swap(x,y);return st[0].query(x,y);}
inline int lcs(int x,int y){assert(x^y);x=n-x+1;y=n-y+1;x=(rk[1][x]<<1)-1;y=(rk[1][y]<<1)-1;if(x>y)swap(x,y);return st[1].query(x,y);}
void build_SA(bool o){
    int m='z';
    mems(buc,0);
    for(int i=1;i<=n;i++)   buc[rk[o][i]=s[i]]++;
    for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
    for(int i=n;i;i--)  sa[o][buc[rk[o][i]]--]=i;
    for(int w=1;w<=n;w<<=1){
        int p=0;
        for(int i=n-w+1;i<=n;i++)   y[++p]=i;
        for(int i=1;i<=n;i++)if(sa[o][i]>w)y[++p]=sa[o][i]-w;
        mems(buc,0);
        for(int i=1;i<=n;i++)   buc[rk[o][i]]++;
        for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
        for(int i=n;i;i--)  sa[o][buc[rk[o][y[i]]]--]=y[i];
        memc(y,rk[o]);
        rk[o][sa[o][1]]=m=1;
        for(int i=2;i<=n;i++){
            if(y[sa[o][i]]==y[sa[o][i-1]]&&(sa[o][i]+w<=n?y[sa[o][i]+w]:0)==(sa[o][i-1]+w<=n?y[sa[o][i-1]+w]:0))  rk[o][sa[o][i]]=m;
            else    rk[o][sa[o][i]]=++m;
        }
        if(n==m)    break;
    }
    for(int i=1,k=0;i<=n;i++){
        if(rk[o][i]==1)k=0;
        else{
            if(k)k--;
            int x=sa[o][rk[o][i]-1];
            while(i+k<=n&&x+k<=n&&s[i+k]==s[x+k])k++;
            ht[o][rk[o][i]]=k;
        }
    }
    st[o].build(ht[o]);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%s",&n,s+1);
    for(int i=1;i<=n;i++)   scanf("%d",&f[i]);
    for(int i=1;i<=n;i++)
        for(int j=i+i;j<=n;j+=i) f[j]-=f[i];
    build_SA(0);
    reverse(s+1,s+n+1);
    build_SA(1);
    reverse(s+1,s+n+1);
    for(int i=1;i<=n;i++)   c[i]+=f[1];
    for(int p=1;p<=n/2;p++){
        for(int x=p+p;x<=n;x+=p){
            int l=x-lcs(x,x-p)+1,r=x+lcp(x,x-p)-1;
            if(l>r||l<=x-p)continue;
            for(int k=2;(k-1)*p<=r-l+1;k++) c[l+(k-1)*p-1]+=f[k],c[r+1]-=f[k];
            x=r/p*p;
        }
    }
    for(int i=1;i<=n;i++)   c[i]+=c[i-1],printf("%d ",c[i]);puts("");
}
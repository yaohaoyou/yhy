#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e4+10,mod=998244353;
int n,q;
char s[maxn];
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
struct Matrix{
    int a[7][7];int lx,ly;
    Matrix(int x=0,int y=0){lx=x;ly=y;mems(a,0);}
    inline int* operator[](int x){return a[x];}
    inline Matrix operator*(Matrix y){
        Matrix ret(lx,y.ly);
        assert(ly==y.lx);
        for(int i=0;i<lx;i++)
            for(int j=0;j<ly;j++)
                for(int k=0;k<y.ly;k++)    madd(ret[i][k],immul(a[i][j],y[j][k]));
        return ret;
    }
    inline void print(){for(int i=0;i<lx;i++,puts(""))for(int j=0;j<ly;j++)printf("%d ",a[i][j]);puts("");}
};
Matrix base[6],base2[6];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    Matrix tr[maxn<<2];
    int f[maxn<<2][6][6],pre[maxn<<2][6],suf[maxn<<2][6],sta[maxn<<2];
    inline void pu(int p){
        tr[p]=tr[rs]*tr[ls];
        rep(i,0,5)pre[p][i]=min(pre[ls][i],sta[ls]|pre[rs][i]),suf[p][i]=min(suf[ls][i]|sta[rs],suf[rs][i]);sta[p]=sta[ls]|sta[rs];
        mems(f[p],0);
        rep(i,0,5)rep(j,0,5){
            rep(x,0,5)rep(y,0,5)if(!((suf[ls][x]|pre[rs][y])&((1<<x)|(1<<y))))madd(f[p][i][j],immul(f[ls][i][x],f[rs][y][j]));
            if(!(sta[ls]&(1<<i)))    madd(f[p][i][j],f[rs][i][j]);
            if(!(sta[rs]&(1<<j)))    madd(f[p][i][j],f[ls][i][j]);
        }
    }
    void build(setpos){tr[p]=Matrix(7,7);if(l==r)return;setmid;build(lson);build(rson);}
    inline void upd(int x){
        int p=1,l=1,r=n;
        while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        int o=s[x]-'a';
        tr[p]=base[o];rep(i,0,5)pre[p][i]=suf[p][i]=63;
        pre[p][o]=suf[p][o]=0;sta[p]=1<<o;mems(f[p],0);f[p][o][o]=1;
        while(p>>=1)pu(p);
    }
    void print(setpos){printf("%d [%d,%d]\n",p,l,r);rep(i,0,5){rep(j,0,5)printf("%d ",f[p][i][j]);puts("");}if(l==r)return;setmid;print(lson);print(rson);}
}
using namespace SegmentTree;
Matrix matt;
inline int getans(){
    int ans=0;
    Matrix res=tr[1]*matt;
    rep(i,0,5)madd(ans,res[i][0]);
    rep(i,0,5)rep(j,0,5)mdel(ans,f[1][i][j]);
    return ans;
}
int main(){
    scanf("%d%d%s",&n,&q,s+1);
    matt=Matrix(7,1);matt[6][0]=1;
    for(int i=0;i<6;i++){
        base[i]=Matrix(7,7);
        for(int j=0;j<7;j++)    base[i][i][j]=1;
        for(int j=0;j<7;j++)    base[i][j][j]=1;
    }
    build(all);
    for(int i=1;i<=n;i++)   upd(i);
    printf("%d\n",getans());
    while(q--){
        int x;char c[5];
        scanf("%d%s",&x,c);
        s[x]=c[0];
        upd(x);
        printf("%d\n",getans());
    }
}
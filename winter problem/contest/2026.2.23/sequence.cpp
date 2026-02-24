#include<bits/stdc++.h>
#define rep(i) for(int i:{0,1})
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define ptii pair<tree,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e4+10;
const ll inf=1e18;
int n,q;
int a[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char ch){if(!x)return putc(48),putc(ch),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(ch);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<ll> tr[maxn<<2][2][2];
    vector<ll> concave_merge(vector<ll> &x,vector<ll> &y){
        vector<ll> res(x.size()+y.size()-1,-inf);res.clear();
        res[0]=x[0]+y[0];
        int i=0,j=0;ll now=x[0]+y[0];
        while(i+1<x.size()&&j+1<y.size()){
            ll cx=x[i+1]-x[i],cy=y[j+1]-y[j];
            if(cx>cy)   res[i+j+1]=(now+=cx),i++;
            else    res[i+j+1]=(now+=cy),j++;
        }
        while(i+1<x.size()) res[i+j+1]=(now+=x[i+1]-x[i]),i++;
        while(j+1<y.size()) res[i+j+1]=(now+=y[j+1]-y[j]),j++;
        return res;
    }
    void build(setpos){
        if(l==r){
            tr[p][0][0].eb(0);tr[p][0][0].eb(-inf);
            tr[p][0][1].eb(-inf);tr[p][0][1].eb(-inf);
            tr[p][1][0].eb(-inf);tr[p][1][0].eb(-inf);
            tr[p][1][1].eb(-inf);tr[p][1][1].eb(a[l]);
            return;
        }
        setmid;build(lson);build(rson);
        rep(a)rep(b)tr[p][a][b]=vector<ll>(r-l+2,-inf);
        rep(a)rep(b)rep(c)rep(d){
            vector<ll> tmp=concave_merge(tr[ls][a][b],tr[rs][c][d]);
            for(int i=0;i<=r-l+1;i++){
                if(b&&c&&i) gmx(tr[p][a][d][i-1],tmp[i]);
                gmx(tr[p][a][d][i],tmp[i]);
            }
        }
    }
    vector<int> vec;
    void query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return vec.eb(p),void();setmid;if(pl<=mid)query(lson,pl,pr);if(pr>mid)query(rson,pl,pr);}
}
using namespace SegmentTree;
struct node{
    ll val[2][2],id[2][2];
    void init(){mems(val,-0x3f);mems(id,0x3f);}
    inline node mrg(node y,int k){
        node res;res.init();
        rep(a)rep(b)rep(c)rep(d){
            ll v=val[a][b]+y.val[c][d],i=id[a][b]+y.id[c][d];
            if(v>res.val[a][d]) res.val[a][d]=v,res.id[a][d]=i;
            else if(v==res.val[a][d])   gmn(res.id[a][d],i);
            if(b&&c){
                v+=k;i--;
                if(v>res.val[a][d]) res.val[a][d]=v,res.id[a][d]=i;
                else if(v==res.val[a][d])   gmn(res.id[a][d],i);
            }
        }
        return res;
    }
    inline void GMX(node x){rep(i)rep(j)if(x.val[i][j]>val[i][j])val[i][j]=x.val[i][j],id[i][j]=x.id[i][j];else if(x.val[i][j]==val[i][j])gmn(id[i][j],x.id[i][j]);}
};
inline bool cmp(int vx,int vy,int x,int y){return (vx<vy)||(vx==vy&&x<y);}
node f;
inline ll slv(int k,bool o=false){
    for(int p:vec){
        auto W=[&](int i,int j,int x){return tr[p][i][j][x]-(x?tr[p][i][j][x-1]:0);};
        node M;
        rep(i)rep(j){
            int l=1,r=tr[p][i][j].size()-1,y=0;
            while(l<=r){setmid;(W(i,j,mid)>k)?(y=mid,l=mid+1):(r=mid-1);}
            M.val[i][j]=tr[p][i][j][y]-1ll*y*k;M.id[i][j]=y;
        }
        if(p==vec.front())  f=M;
        else f=f.mrg(M,k);
    }
    ll mxv=-inf,ret;
    rep(i)rep(j)if(f.val[i][j]>mxv)mxv=f.val[i][j],ret=f.id[i][j];else if(f.val[i][j]==mxv)gmn(ret,f.id[i][j]);
    return o?mxv:ret;
}
// vector<int> res[2][2],now[2][2];
// int baoli(int l,int r,int k){
//     rep(a)rep(b)res[a][b]=vector<int>{-inf};
//     res[0][0]=vector<int>{0};
//     int len=1;
//     for(int p:vec){
//         len+=tr[p][0][0].size()-1;
//         rep(a)rep(b)now[a][b]=res[a][b],res[a][b]=vector<int>(len,-inf);
//         rep(a)rep(b)rep(c)rep(d){
//             vector<int> tmp=concave_merge(now[a][b],tr[p][c][d]);
//             for(int i=0;i<len;i++){
//                 if(b&&c&&i) gmx(res[a][d][i-1],tmp[i]);
//                 gmx(res[a][d][i],tmp[i]);
//             }
//         }
//     }
//     assert(res[0][0].size()==r-l+2);
//     int ret=-inf;
//     rep(i)rep(j)gmx(ret,res[i][j][k]);
//     return ret;
// }
int main(){
    freopen("sequence.in","r",stdin);freopen("sequence.out","w",stdout);
    read();n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    build(all);
    while(q--){
        int l=read(),r=read(),k=read();
        vec.clear();
        query(all,l,r);
        int L=-1e9,R=1e9,pp=1e9;
        while(L<=R){
            int mid=(L+R)>>1;
            int p=slv(mid);
            if(p<=k) pp=mid,R=mid-1;
            else L=mid+1;
        }
        print(slv(pp,1)+1ll*k*pp,'\n');
    }
    flush();
}
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
const int maxn=1e6+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=gc();while(c<48||c>57){if(c=='-')f=-1;c=gc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=gc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=gc();while(c<48||c>57){if(c=='-')f=-1;c=gc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=gc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::gc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
inline char getc(){char c=gc();while(c!='1'&&c!='2'&&c!='?')c=gc();return c;}
int n,m,q;
int a[maxn],b[maxn];
struct tree{
    int a[10][10];ll s;
    tree(){mems(a,0x3f);s=0;}
    int* operator[](int x){return a[x];}
    tree operator+(tree y){
        tree res;res.s=s+y.s;
        for(int i=0;i<m;i++)for(int j=0;j<m;j++)for(int k=0;k<m;k++)gmn(res[i][k],a[i][j]+y[j][k]);
        int mn=1e9;
        for(int i=0;i<m;i++)for(int j=0;j<m;j++)gmn(mn,res[i][j]);
        if(mn){
            res.s+=mn;
            for(int i=0;i<m;i++)for(int j=0;j<m;j++)res[i][j]-=mn;
        }
        return res;
    }
};
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    tree tr[2148600];int pos[maxn];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    int cnt=0;
    void build(setpos){
        if(l==r){
            gmx(cnt,p);
            pos[l]=p;
            ll mn;
            {
                int x=m-1,y=a[l]-m;
                if(x>=y)mn=0;
                else mn=1ll*(y-x+m-1)/m*b[l];
            }
            tr[p].s=mn;
            for(int i=0;i<m;i++)for(int j=0;j<m;j++){
                int x=i,y=a[l]-m+j;
                if(x>=y)tr[p][i][j]=0;
                else    tr[p][i][j]=1ll*(y-x+m-1)/m*b[l]-mn;
            }
            return;
        }
        setmid;build(lson);build(rson);pu(p);
    }
    inline void U(int X){
        int p=pos[X];
        ll mn;
        {
            int x=m-1,y=a[X]-m;
            if(x>=y)mn=0;
            else mn=1ll*(y-x+m-1)/m*b[X];
        }
        tr[p].s=mn;
        for(int i=0;i<m;i++)for(int j=0;j<m;j++){
            int x=i,y=a[X]-m+j;
            if(x>=y)tr[p][i][j]=0;
            else    tr[p][i][j]=1ll*(y-x+m-1)/m*b[X]-mn;
        }
        while(p>>=1)pu(p);
    }
    tree Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;return pr<=mid?Q(lson,pl,pr):(pl>mid?Q(rson,pl,pr):Q(lson,pl,pr)+Q(rson,pl,pr));}
}
using namespace SegmentTree;
bool mem2;
int main(){
    // freopen("travel.in","r",stdin);freopen("travel.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();q=read();m=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   b[i]=read();
    build(all);
    while(q--){
        char op=getc();int l=read(),r=read();
        if(op=='1') a[l]=r,U(l);
        else if(op=='2')    b[l]=r,U(l);
        else{
            tree w=Q(all,l,r);
            printf("%lld\n",w[0][m-1]+w.s);
        }
    }
}
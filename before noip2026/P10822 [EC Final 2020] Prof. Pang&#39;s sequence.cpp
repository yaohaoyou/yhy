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
const int maxn=5e5+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(ll x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(ll x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
struct Mat{
    ll a[3][3];bool emp;
    Mat(bool o=false){mems(a,0);emp=o;if(o)a[0][0]=a[1][1]=a[2][2]=1;}
    ll* operator[](int x){return a[x];}
    inline Mat operator+(Mat y){
        // for(int i=0;i<3;i++)for(int j=0;j<3;j++)y[i][j]+=a[i][j];
        y[0][0]+=a[0][0];y[0][1]+=a[0][1];y[0][2]+=a[0][2];
        y[1][0]+=a[1][0];y[1][1]+=a[1][1];y[1][2]+=a[1][2];
        y[2][0]+=a[2][0];y[2][1]+=a[2][1];y[2][2]+=a[2][2];
        y.emp=false;
        return y;
    }
    inline Mat operator*(Mat y){
        if(y.emp)return *this;
        Mat res;res.emp=false;
        // for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int k=0;k<3;k++)res[i][k]+=a[i][j]*y[j][k];
        res[0][0]=a[0][0]*y[0][0]+a[0][1]*y[1][0]+a[0][2]*y[2][0];
        res[0][1]=a[0][0]*y[0][1]+a[0][1]*y[1][1]+a[0][2]*y[2][1];
        res[0][2]=a[0][0]*y[0][2]+a[0][1]*y[1][2]+a[0][2]*y[2][2];
        res[1][0]=a[1][0]*y[0][0]+a[1][1]*y[1][0]+a[1][2]*y[2][0];
        res[1][1]=a[1][0]*y[0][1]+a[1][1]*y[1][1]+a[1][2]*y[2][1];
        res[1][2]=a[1][0]*y[0][2]+a[1][1]*y[1][2]+a[1][2]*y[2][2];
        res[2][0]=a[2][0]*y[0][0]+a[2][1]*y[1][0]+a[2][2]*y[2][0];
        res[2][1]=a[2][0]*y[0][1]+a[2][1]*y[1][1]+a[2][2]*y[2][1];
        res[2][2]=a[2][0]*y[0][2]+a[2][1]*y[1][2]+a[2][2]*y[2][2];
        return res;
    }
    inline void operator*=(Mat y){*this=*this*y;}
};
struct Vec{
    ll a[3];
    Vec(){mems(a,0);}
    ll& operator[](int x){return a[x];}
    inline Vec operator+(Vec y){y[0]+=a[0];y[1]+=a[1];y[2]+=a[2];return y;}
    inline Vec operator*(Mat y){
        if(y.emp)return *this;
        Vec res;
        // for(int j=0;j<3;j++)for(int k=0;k<3;k++)res[k]+=a[j]*y[j][k];
        res[0]=a[0]*y[0][0]+a[1]*y[1][0]+a[2]*y[2][0];
        res[1]=a[0]*y[0][1]+a[1]*y[1][1]+a[2]*y[2][1];
        res[2]=a[0]*y[0][2]+a[1]*y[1][2]+a[2]*y[2][2];
        return res;
    }
    inline void operator*=(Mat y){*this=*this*y;}
    // inline void operator+=(Vec y){*this=*this+y;}
};
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    Vec tr[maxn<<2];Mat tag[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p,Mat s){tr[p]*=s;tag[p]*=s;}
    inline void pd(int p){if(!tag[p].emp)pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=Mat(1);}
    void build(setpos){tag[p]=Mat(1);if(l==r)return tr[p][0]=tr[p][1]=0,tr[p][2]=1,void();setmid;build(lson);build(rson);pu(p);}
    void upd(setpos,int pl,int pr,Mat s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    int pl,pr;ll res;
    void Q(setpos){if(l>=pl&&r<=pr)return res+=tr[p][1],void();pd(p);setmid;if(pl<=mid)Q(lson);if(pr>mid)Q(rson);}
}
using namespace SegmentTree;
Mat rev,his;
int n,q;
int a[maxn],buc[maxn];
ll ans[maxn];
vector<pii> vq[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    rev[0][0]=-1;rev[1][1]=rev[2][0]=rev[2][2]=1;
    his[0][0]=his[0][1]=his[1][1]=his[2][2]=1;
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    q=read();
    for(int i=1;i<=q;i++){int l=read(),r=read();vq[r].eb(l,i);}
    build(all);
    for(int i=1;i<=n;i++){
        int p=buc[a[i]];
        upd(all,p+1,i,rev);pt(1,his);
        for(auto [l,id]:vq[i])   pl=l,pr=i,res=0,Q(all),ans[id]=res;
        buc[a[i]]=i;
    }
    for(int i=1;i<=q;i++)   print(ans[i],'\n');Flush();
}
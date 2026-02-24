#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define plii pair<ll,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e6+10;
int n,m,tot;
int a[2][maxn],c[maxn],p[maxn];
ll b[2][maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){x=max(x,y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll tr[maxn<<2],tag[maxn<<2];
    int L[maxn<<2],R[maxn<<2],mxp[maxn<<2],asl[maxn<<2],asr[maxn<<2];
    inline void pu(int p){if(tr[ls]>tr[rs])tr[p]=tr[ls],L[p]=L[ls],R[p]=R[ls],mxp[p]=mxp[ls];else tr[p]=tr[rs],L[p]=L[rs],R[p]=R[rs],mxp[p]=mxp[rs];}
    inline void pt(int p,ll s){tr[p]+=s;tag[p]+=s;}
    inline void ptl(int p,int s){L[p]=asl[p]=s;}
    inline void ptr(int p,int s){R[p]=asr[p]=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;if(asl[p])ptl(ls,asl[p]),ptl(rs,asl[p]),asl[p]=0;if(asr[p])ptr(ls,asr[p]),ptr(rs,asr[p]),asr[p]=0;}
    inline void upd(int x){int p=1,l=1,r=m;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=b[0][n];L[p]=1;R[p]=n;mxp[p]=x;while(p>>=1)pu(p);}
    void upd(setpos,int pl,int pr,ll s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    void updL(setpos,int pl,int pr,ll s,int L){if(l>=pl&&r<=pr)return pt(p,s),ptl(p,L);pd(p);setmid;if(pl<=mid)updL(lson,pl,pr,s,L);if(pr>mid)updL(rson,pl,pr,s,L);pu(p);}
    void updR(setpos,int pl,int pr,ll s,int R){if(l>=pl&&r<=pr)return pt(p,s),ptr(p,R);pd(p);setmid;if(pl<=mid)updR(lson,pl,pr,s,R);if(pr>mid)updR(rson,pl,pr,s,R);pu(p);}
    void clear(){
        memset(tr,0,((m<<2)+10)*sizeof(ll));
        memset(tag,0,((m<<2)+10)*sizeof(ll));
        memset(asl,0,((m<<2)+10)*sizeof(int));
        memset(asr,0,((m<<2)+10)*sizeof(int));
        memset(L,0,((m<<2)+10)*sizeof(int));
        memset(R,0,((m<<2)+10)*sizeof(int));
    }
}
using namespace SegmentTree;
struct node{
    ll x;pii seg1,seg2;
    inline bool operator<(const node &y)const{return x<y.x;}
};
void discrete(){
    for(int i=1;i<=n+m;i++)if(!c[i])c[i]=++tot;
    for(int i=1;i<=n;i++)   a[0][i]=c[a[0][i]],p[a[0][i]]=i;
    for(int i=1;i<=m;i++)   a[1][i]=c[a[1][i]];
}
node solve(int x){
    clear();
    stack<piii> sl,sr;
    node ret={0,pii(0,0),pii(0,0)};
    int lst=1;
    for(int i=1;i<=m;i++){
        if(p[i]==x){while(!sl.empty())sl.pop();while(!sr.empty())sr.pop();clear();lst=i+1;continue;}
        sl.ep(pii(i,i),1);sr.ep(pii(i,i),n);upd(i);
        if(p[i]){
            if(p[i]<=x){
                int L=0;
                while(!sl.empty()&&sl.top().se<=p[i]){
                    updL(all,sl.top().fi.fi,sl.top().fi.se,-b[0][p[i]]+b[0][sl.top().se-1],p[i]+1);
                    L=sl.top().fi.fi;sl.pop();
                }
                sl.ep(pii(L,i),p[i]+1);
            }
            if(p[i]>=x){
                int L=0;
                while(!sr.empty()&&sr.top().se>=p[i]){
                    updR(all,sr.top().fi.fi,sr.top().fi.se,-b[0][sr.top().se]+b[0][p[i]-1],p[i]-1);
                    L=sr.top().fi.fi;sr.pop();
                }
                sr.ep(pii(L,i),p[i]-1);
            }
        }
        upd(all,lst,i,b[1][i]-b[1][i-1]);
        ret=max(ret,{tr[1],pii(L[1],R[1]),pii(mxp[1],i)});
    }
    return ret;
}
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++)   a[0][i]=read();
    for(int i=1;i<=n;i++)   b[0][i]=read(),b[0][i]+=b[0][i-1];
    for(int i=1;i<=m;i++)   a[1][i]=read(),c[a[1][i]]=++tot;
    for(int i=1;i<=m;i++)   b[1][i]=read(),b[1][i]+=b[1][i-1];
    discrete();
    node ans;
    if(b[0][n]>=b[1][m])    ans={b[0][n],pii(1,n),pii(0,0)};
    else ans={b[1][m],pii(0,0),pii(1,m)};

    int x=1;while(x<=n&&b[0][x]*2<b[0][n])x++;
    ans=max(ans,solve(x));

    swap(a[0],a[1]);swap(b[0],b[1]);swap(n,m);tot=0;mems(c,0);mems(p,0);
    for(int i=1;i<=m;i++)   c[a[1][i]]=++tot;
    discrete();
    x=1;while(x<=n&&b[0][x]*2<b[0][n])x++;
    node tmp=solve(x);swap(tmp.seg1,tmp.seg2);
    ans=max(ans,tmp);
    printf("%lld\n%d %d\n%d %d\n",ans.x,ans.seg1.fi,ans.seg1.se,ans.seg2.fi,ans.seg2.se);
}
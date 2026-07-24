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
const int maxn=3e5+10,maxV=3e5,B=1300;
int V,V2;
int n,q,len;ll sumL;
int a[maxn],b[maxn];
struct ques{int l,r,id;}Q[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(ll x,char ch){if(!x)return putc(48),putc(ch),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(ch);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
struct Fenwcik{
    struct BIT{
        ll tr[maxV],sum;
        inline int lowbit(int x){return x&-x;}
        inline void add(int x,ll s){sum+=s;while(x<=V2){tr[x]+=s;x+=lowbit(x);}}
        inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
        inline ll query(int l,int r){return que(r)-que(l-1);}
    }t1,t2;
    inline void add(int l,int s){t1.add(l,s);t2.add(l,1ll*l*s);}
    inline ll query(int l){return (V2+1)*t1.sum-l*t1.que(l-1)-t2.sum+t2.que(l-1);}
}TL[2];
struct BIT{
    int tr[maxV],sum;
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){sum+=s;while(x<=V2){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l){return sum-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T[2];
int poi;
int c[maxn][2],cnt[maxn],en[maxn],be[maxn];pii p[maxn];
ll ans[maxn];
ll now;
void add(int x){
    const int y=a[x];ll cc=cnt[y];bool o=p[y].fi;
    if(y^en[cc]){
        swap(c[p[y].se][o],c[p[en[cc]].se][p[en[cc]].fi]);
        swap(p[y],p[en[cc]]);
        if(y==be[cc])   be[cc]=en[cc];
    }
    o=p[y].fi;
    if(cnt[c[p[y].se-(!o)][!o]]==cc) en[cc]=c[p[y].se-(!o)][!o];
    else    be[cc]=en[cc]=0;
    if(!en[cc+1])   en[cc+1]=y;
    be[cc+1]=y;
    ll L=p[y].se==1?0:T[o].que(p[y].se-1);
    now+=(len<<1|1)-cc+sumL-L;len++;cc++;cnt[y]++;
    now+=1ll*(len-1)*(V2-p[y].se)-2*TL[o].query(p[y].se+1)-T[o].query(p[y].se+1);
    T[o].add(p[y].se,1);TL[o].add(p[y].se+1,1);sumL+=V2-p[y].se;
}
void del(int x){
    const int y=a[x];ll cc=cnt[y];bool o=p[y].fi;
    if(y^be[cc]){
        swap(c[p[y].se][o],c[p[be[cc]].se][p[be[cc]].fi]);
        swap(p[y],p[be[cc]]);
        if(y==en[cc])   en[cc]=be[cc];
    }
    o=p[y].fi;
    if(cnt[c[p[y].se+o][!o]]==cc) be[cc]=c[p[y].se+o][!o];
    else    be[cc]=en[cc]=0;
    if(!be[cc-1])   be[cc-1]=y;
    en[cc-1]=y;
    ll L=p[y].se==1?0:T[o].que(p[y].se-1);
    now-=(len<<1)-cc+sumL-L;len--;cc--;cnt[y]--;
    now-=1ll*(len+1)*(V2-p[y].se)-2*TL[o].query(p[y].se+1)-T[o].query(p[y].se+1);
    T[o].add(p[y].se,-1);TL[o].add(p[y].se+1,-1);sumL-=V2-p[y].se;
}
void discrete(){
    memc(b,a);
    sort(b+1,b+n+1);V=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+V+1,a[i])-b;
}
inline int bid(int x){return (x-1)/B+1;}
inline bool cmp(ques x,ques y){
    if(bid(x.l)^bid(y.l))  return x.l<y.l;
    return x.r==y.r?false:(bid(x.l)&1)^(x.r>y.r);
}
int main(){
    freopen("color.in","r",stdin);freopen("color.out","w",stdout);
    // freopen("D:\\yhy\\down\\div1_down\\color\\color5.in","r",stdin);
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    discrete();(V&1)&&(V++);V2=V>>1;
    // debug("V = %d\n",V);
    for(int i=1;i<=q;i++)   Q[i].l=read(),Q[i].r=read(),Q[i].id=i;
    sort(Q+1,Q+q+1,cmp);
    cnt[0]=-1;
    for(int i=1;i<=V;i++)   p[i]=pii((i-1)&1,(i+1)>>1),c[p[i].se][p[i].fi]=i;
    be[0]=1;en[0]=V;
    for(int i=1,l=1,r=0;i<=q;i++){
        int ql=Q[i].l,qr=Q[i].r,id=Q[i].id;
        while(r<qr) add(++r);
        while(l>ql) add(--l);
        while(r>qr) del(r--);
        while(l<ql) del(l++);
        ans[Q[i].id]=now;
    }
    for(int i=1;i<=q;i++)   print(ans[i],'\n');
    flush();
    // debug("move = %d\n",poi);
}
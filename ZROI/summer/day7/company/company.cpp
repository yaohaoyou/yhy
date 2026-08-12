#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pll pair<ll,ll>
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=4e5+10;
int n,m,q,X,Y;
ll b[maxn];
pii a[maxn];
piii Q[maxn];
pll v[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
void discrete(){
    sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;
    for(int i=1;i<=n;i++)   a[i].se=lower_bound(b+1,b+m+1,a[i].se)-b;
    for(int i=1;i<=q;i++)   Q[i].se.se=lower_bound(b+1,b+m+1,Q[i].se.se)-b;
}
multiset<int> st;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct tree{
        ll nx,mx,ny,my;
        inline friend tree operator+(tree x,tree y){
            tree res;
            ll d=min(x.nx,y.mx);x.nx-=d;y.mx-=d;
            if(x.nx&&y.my%Y){
                int r=y.my%Y;
                y.my-=r;y.ny+=r;
                x.nx--;
            }
            if(y.my%Y){d=min(Y-y.my%Y,x.ny);x.ny-=d;y.my+=d;}
            // printf("%lld %lld %lld %lld %lld %lld %lld\n",y.emp,y.len,x.mx,x.my,y.mx,y.my,d);
            d=min(LL(x.ny),LL(y.mx)*Y);x.ny-=d;y.mx-=(d+Y-1)/Y;y.my+=d;
            // res.ny=x.ny+y.ny;res.my=x.my+y.my;
            if(x.my%Y&&y.my%Y){
                d=x.my%Y;
                if(x.my%Y+y.my%Y<=Y)    x.mx++,y.my+=d,x.my-=d;
            }
            res={x.nx+y.nx,x.mx+y.mx,x.ny+y.ny,x.my+y.my};
            // d=min(x.ny,y.my);x.ny-=d;y.my-=d;
            // res.ny=x.ny+y.ny;res.my=x.my+y.my;
            // if(res.emp>res.len){
            //     printf("%lld %lld %lld %lld %lld %lld\n",x.emp,y.emp,x.len,y.len,x.nx,y.mx);
            //     exit(0);
            // }
            // assert(res.emp<=res.mx&&res.emp<=res.len);
            return res;
        }
    }tr[maxn<<2];
    int binary(int x){
        int p=1,l=1,r=m;
        tree now={0,0,0,0};
        while(l^r){
            setmid;
            if(x>mid){now=now+tr[ls];p=rs;l=mid+1;}
            else{
                tree tmp=now+tr[ls];
                if(!tmp.nx&&!tmp.ny)    p=ls,r=mid;
                else    now=tmp,p=rs,l=mid+1;
            }
        }
        return l;
    }
    int pos[maxn];
    inline void init(int p,int l){
        ll len=b[l+1]-b[l],x=v[l].fi,y=v[l].se;
        if(len>=x){
            len-=x,x=0;
            ll d=min(len,y/Y);
            len-=d;
            if(len&&y%Y)  tr[p]={0,len-1,0,y};
            else    tr[p]={0,len,y-Y*d,d*Y};
        }
        else{
            x-=len;
            tr[p]={x,0,y,0};
        }
    }
    void build(setpos){
        if(l==r)    return init(p,l),pos[l]=p,void();
        setmid;build(lson);build(rson);tr[p]=tr[ls]+tr[rs];
    }
    inline void upd(int l){
        int p=pos[l];init(p,l);
        while(p>>=1)    tr[p]=tr[ls]+tr[rs];
    }
    tree query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;if(pl>mid)return query(rson,pl,pr);if(pr<=mid)return query(lson,pl,pr);return query(lson,pl,pr)+query(rson,pl,pr);}
    vector<int> pat;
    void qpath(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pat.eb(p),void();setmid;if(pl<=mid)qpath(lson,pl,pr);if(pr>mid)qpath(rson,pl,pr);}
}
using namespace SegmentTree;
inline void ins(int x,int s){
    st.ep(x);
    v[x].fi+=s/X;s%=X;
    if(s>=Y)    v[x].fi++;
    else    v[x].se+=s;
}
inline void era(int x,int s){
    st.erase(st.find(x));
    v[x].fi-=s/X;s%=X;
    if(s>=Y)    v[x].fi--;
    else    v[x].se-=s;
}
ll getans(){
    // b[m+1]=281501069+1;
    // build(all);
    // printf("[%d,%d]\n",b[1],b[m+1]-1);
    // printf("! %lld %lld %lld %lld\n",tr[1].nx,tr[1].ny,tr[1].mx,tr[1].my);
    // return 0;
    int mx=*(--st.end());
    ll l=mx,r=m,p=binary(mx);
    tree now=p==1?(tree){0,0,0,0}:query(all,1,p-1);
    ll yuan=b[p+1];
    l=b[p],r=b[p+1]-1;ll ans=0;
    while(l<=r){
        ll mid=(l+r)>>1;
        b[p+1]=mid+1;init(pos[p],p);
        tree tmp=now+tr[pos[p]];
        if(!tmp.nx&&!tmp.ny)    ans=mid,r=mid-1;
        else    l=mid+1;
    }
    b[p+1]=yuan;init(pos[p],p);
    return ans;
}
int main(){
    freopen("company.in","r",stdin);freopen("company.out","w",stdout);
    n=read();q=read();X=read();Y=read();gmx(X,Y);
    for(int i=1;i<=n;i++)   a[i].fi=read(),a[i].se=read(),b[++m]=a[i].se;
    for(int i=1;i<=q;i++)   Q[i].fi=read(),Q[i].se.fi=read(),Q[i].se.se=read(),b[++m]=Q[i].se.se;
    if(n==1){
        printf("%d\n",a[1].se+(a[1].fi+X-1)/X-1);
        for(int i=1;i<=q;i++){
            a[1]=Q[i].se;
            printf("%d\n",a[1].se+(a[1].fi+X-1)/X-1);
        }
        return 0;
    }
    discrete();
    b[m+1]=2e14;
    for(int i=1;i<=n;i++)   ins(a[i].se,a[i].fi);
    build(all);
    print(getans(),'\n');
    for(int i=1;i<=q;i++){
        int p=Q[i].fi,x=Q[i].se.fi,y=Q[i].se.se;
        era(a[p].se,a[p].fi);upd(a[p].se);
        a[p]=pii(x,y);
        ins(a[p].se,a[p].fi);upd(a[p].se);
        print(getans(),'\n');
    }
    flush();
}
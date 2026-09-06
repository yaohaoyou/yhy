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
const int maxn=5e5+10;
int n,m,q,rt;
int a[maxn],ans[maxn],fa[maxn],son[maxn],pre[maxn],nxt[maxn];
pii seg[maxn];
vector<pii> v[maxn];
set<int> col[maxn];
set<pii> st;
int buc[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],pos[maxn];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    void build(setpos){if(l==r)return tr[p]=pre[l],pos[l]=p,void();setmid;build(lson);build(rson);pu(p);}
    inline void upd(int x){int p=pos[x];tr[p]=pre[x];while(p>>=1)pu(p);}
    // int query(setpos,int pr){if(r<=pr)return tr[p];setmid,res=query(lson,pr);if(pr>mid)gmx(res,query(rson,pr));return res;}
    int query(int pr){
        int p=1,l=1,r=n,ret=0;
        while(l^r){
            setmid;
            if(pr<=mid) p=ls,r=mid;
            else    gmx(ret,tr[ls]),p=rs,l=mid+1;
        }
        gmx(ret,tr[p]);
        return ret;
    }
}
using namespace SegmentTree;
vector<int> vec;
void chk(int p,int tim){
    auto it=st.lower_bound(pii(p,0));if(it==st.end())return;
    int x=it->se;
    int l=seg[x].fi,r=seg[x].se;
    while(x&&query(r)<l){
        ans[x]=tim;
        st.erase(pii(r,x));
        son[fa[x]]--;if(son[fa[x]])break;
        x=fa[x];l=seg[x].fi,r=seg[x].se;
        st.ep(r,x);
    }
}
void era(int x){int pr=pre[x],nx=nxt[x];pre[nx]=pr;nxt[pr]=nx;if(nx)upd(nx),vec.eb(nx);}
bool mem2;
int main(){
    freopen("artist.in","r",stdin);freopen("artist.out","w",stdout);
    debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);
    n=read();m=read();q=read();
    for(int i=1;i<=n;i++){
        a[i]=read();col[a[i]].ep(i);
        pre[i]=buc[a[i]];nxt[pre[i]]=i;buc[a[i]]=i;
    }
    nxt[0]=0;
    build(all);
    for(int i=1;i<=m;i++){
        int l=read(),r=read();seg[i]=pii(l,r);
        v[l].eb(r,i);
    }
    for(int i=1;i<=n;i++){
        sort(v[i].begin(),v[i].end(),greater<pii>());
        for(auto [j,id]:v[i]){
            auto it=st.lower_bound(pii(j,0));
            if(it==st.end())assert(!rt),rt=id;
            else    son[fa[id]=it->se]++;
            st.ep(j,id);
        }
    }
    st.clear();
    // for(int i=1;i<=m;i++)   printf("%d ",fa[i]);puts("");
    for(int i=1;i<=m;i++)if(!son[i])st.ep(seg[i].se,i);
    for(int i=1;i<=m;i++)   ans[i]=i+m;
    for(int i=1;i<=n;i++)   chk(i,0);
    for(int i=1;i<=q;i++){
        int x=read(),y=read();
        col[a[x]].erase(x);era(x);
        a[x]=y;auto it=col[y].ep(x).fi;
        if(it!=col[y].begin()){int pr=*prev(it);nxt[pr]=x;pre[x]=pr;}
        else    pre[x]=0;
        it++;
        if(it!=col[y].end()){
            int nx=*it;nxt[x]=nx;pre[nx]=x;
            upd(nx);vec.eb(nx);
        }
        else    nxt[x]=0;
        upd(x);vec.eb(x);
        for(int k:vec)chk(k,i);
        vec.clear();
    }
    int out=0;for(int i=1;i<=m;i++)out^=ans[i];
    printf("%d\n",out);
}
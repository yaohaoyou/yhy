#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10,V=5e5,B=2048,Block=maxn,inf=1e9;
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
int n,q;
int a[maxn];
piii Q[maxn];
int ans[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
struct DSU{
    int fa[maxn];
    void init(){for(int i=0;i<=V;i++)fa[i]=i;}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
    inline int operator[](int x){return find(x);}
}U;
namespace Block_array{
    int pr[maxn],nx[maxn],c[maxn];
    int mx[Block],tag[Block];
    int id[maxn],bl[Block],br[Block];
    inline void era(int x){int pre=pr[x],nxt=nx[x];if(~pre)nx[pre]=nxt;pr[nxt]=pre;}
    inline void build(int x){
        int l=bl[x],r=br[x];tag[x]=0;
        mx[x]=l;c[l]=-l-1;pr[l]=-1;nx[l]=l+1;for(int i=l+1;i<=r;i++)c[i]=-1,pr[i]=i-1,nx[i]=i+1;
    }
    inline void ins(int x){
        int xid=id[x];
        if(x==bl[xid])  return tag[xid]++,void();tag[xid+1]++;
        int u=U[x];
        c[u]++;if(~pr[u])c[u]+=c[pr[u]],U.merge(pr[u],u),era(pr[u]);
        if(!~pr[u])  mx[xid]=u;
    }
    inline int query(){
        int s=accumulate(tag+1,tag+id[V]+1,0);
        for(int i=id[V];i;i--){
            if(s+c[mx[i]]>=0){
                int now=s;
                int cnt=0;
                for(int x=mx[i];;x=nx[x]){
                    cnt++;assert(cnt<=V);
                    now+=c[x];
                    if(!now)return x+1;
                }
            }
            else    s-=tag[i];
        }
        return 0;
    }
}
using namespace Block_array;
inline bool cmp(piii x,piii y){
    if(id[x.fi.fi]==id[y.fi.fi])    return x.fi.se<y.fi.se;
    return x.fi.fi<y.fi.fi;
}
void data(){
    n=q=1.5e5;srand(time(0));
    printf("%d %d\n",n,q);
    for(int i=1;i<=n;i++)   printf("%d ",rand()%n);
    while(q--){int l=rand()%n+1,r=rand()%n+1;if(l>r)swap(l,r);printf("%d %d\n",l,r);}
    exit(0);
}
int main(){
    freopen("sequence.in","r",stdin);freopen("sequence.out","w",stdout);
    // data();
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=q;i++)   Q[i]=piii(pii(read(),read()),i),swap(Q[i].fi.fi,Q[i].fi.se);
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    sort(Q+1,Q+q+1,cmp);
    vector<int> vec;
    for(int _=1;_<=q;_++){
        int idl=(Q[_].fi.fi-1)/B+1,ql=_,qr=_;
        while(qr<q&&(Q[qr+1].fi.fi-1)/B+1==idl) qr++;
        vec.clear();
        int L=min_element(Q+ql,Q+qr+1)->fi.fi,R=max_element(Q+ql,Q+qr+1)->fi.fi;for(int i=L;i<=R;i++)vec.eb(a[i]);
        for(int i=0;i<=V;i+=B)  vec.eb(i);vec.eb(V+1);
        sort(vec.begin(),vec.end());vec.erase(unique(vec.begin(),vec.end()),vec.end());
        for(int i=0;i+1<vec.size();i++){
            bl[i+1]=vec[i];br[i+1]=vec[i+1]-1;
            for(int j=vec[i];j<vec[i+1];j++)    id[j]=i+1;
        }
        U.init();
        for(int i=1;i<=id[V];i++)   build(i);
        for(int i=ql,l=L,r=L-1;i<=qr;i++){
            int pl=Q[i].fi.fi,pr=Q[i].fi.se,qid=Q[i].se;
            while(r<pr) ins(a[++r]);
            while(l>pl) tag[id[a[--l]]]++;
            while(l<pl) tag[id[a[l++]]]--;
            ans[qid]=query();
        }
        _=qr;
    }
    for(int i=1;i<=q;i++)   print(ans[i]),putc('\n');flush();
}
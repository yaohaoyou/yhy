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
const int maxn=3e5+10;
bool mem1;
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
int n,m,k;
int b[maxn];
vector<int> v[maxn],I[maxn*20];
vector<ll> s[maxn];
ll ans;
struct BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ll s){while(x<=m){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=m;i++)tr[i]=0;}
}T[4];
struct node{
    int l,r,pl,pr;
    node(int _l,int _r,int _pl,int _pr){l=_l;r=_r;pl=_pl;pr=_pr;}
};
vector<node> a;
bool mem2;
void discrete(){
    sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;b[++m]=1e9;
    for(int i=1;i<=k;i++)for(int &j:v[i])j=lower_bound(b+1,b+m+1,j)-b;
}
inline ll cal(int x,int i){
    int p=lower_bound(v[i].begin(),v[i].end(),x)-v[i].begin();
    ll res=0;
    if(p)   res+=1ll*p*b[x]-s[i][p-1];
    if(p<v[i].size())   res+=s[i].back()-(p?s[i][p-1]:0)-1ll*(v[i].size()-p)*b[x];
    return res;
}
void dvd(int l,int r,int pl,int pr){
    int x=(l+r)>>1;
    ll mn=1e18,p=0;
    for(int y=max(x+1,pl);y<=pr;y++){
        ll res=0;
        for(int i=1;i<=k;i++)   res+=min(cal(x,i),cal(y,i));
        if(res<mn)  mn=res,p=y;
    }
    gmn(ans,mn);
    if(l==r)    return;
    dvd(l,x,pl,p);dvd(x+1,r,p,pr);
}
void matt(int _cases){
    ans=1e18;m=0;for(int i=1;i<=k;i++)v[i].clear(),s[i].clear();a.clear();
    for(int i=0;i<4;i++)    T[i].clear();
    n=read();k=read();
    for(int i=1;i<=k;i++){
        int m=read();
        while(m--){int x=read();v[i].eb(x);b[++::m]=x;}
        sort(v[i].begin(),v[i].end());
        ll sum=0;for(int j:v[i])sum+=j,s[i].eb(sum);
    }
    discrete();
    // dvd(1,m,1,m);
    a.eb(1,m,1,m);
    while(!a.empty()){
        vector<pii> Q;
        for(auto [l,r,pl,pr]:a){
            int x=(l+r)>>1;
            for(int i=max(x+1,pl);i<=pr;i++) Q.eb(x,i);
        }
        for(int i=0;i<4;i++)    T[i].clear();
        for(int i=1;i<=k;i++){
            int l=0,r=Q.size()-1,res=Q.size();
            while(l<=r){
                int mid=(l+r)>>1;
                if(cal(Q[mid].fi,i)<=cal(Q[mid].se,i))  res=mid,r=mid-1;
                else    l=mid+1;
            }
            if(res&&(res^Q.size()))    I[res].eb(i);
            if(!res){
                for(int j:v[i]) T[0].add(j,1),T[1].add(j,b[j]);
            }
            else{
                for(int j:v[i]) T[2].add(j,1),T[3].add(j,b[j]);
            }
        }
        vector<ll> w(Q.size());
        for(int i=0;i<Q.size();i++){
            for(int j:I[i]){
                for(int x:v[j]) T[2].add(x,-1),T[3].add(x,-b[x]),T[0].add(x,1),T[1].add(x,b[x]);
            }
            I[i].clear();
            int x=Q[i].fi,y=Q[i].se;
            w[i]=T[0].que(x)*b[x]-T[1].que(x)+T[1].query(x+1,m)-T[0].query(x+1,m)*b[x]+
            T[2].que(y)*b[y]-T[3].que(y)+T[3].query(y+1,m)-T[2].query(y+1,m)*b[y];
        }
        vector<node> nw;
        int ps=0;
        for(auto [l,r,pl,pr]:a){
            int x=(l+r)>>1;
            ll mn=1e18;int p=0;
            for(int i=max(x+1,pl);i<=pr;i++,ps++){
                if(w[ps]<mn)mn=w[ps],p=i;
            }
            gmn(ans,mn);
            if(l^r)nw.eb(l,x,pl,p),nw.eb(x+1,r,p,pr);
        }
        a.swap(nw);
    }
    print(ans,'\n');
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);Flush();}
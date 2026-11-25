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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10,maxm=4e5+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
int n,m,S,T;
piii E[maxm];
namespace Graph{
    vector<piii> son[maxn];
    inline void add(int u,int v,int w,int id){son[u].eb(pii(v,w),id);}
    inline void rebuild(){
        for(int i=0;i<=n;i++)son[i].clear();
        for(int i=1;i<=m;i++)add(E[i].fi.fi,E[i].fi.se,E[i].se,i);
    }
}
using namespace Graph;
bool f[maxm];
queue<pii> q;
int ps[maxn];
bool check(int X){
    mems(f,0);mems(ps,0);while(!q.empty())q.pop();
    q.ep(S,0);
    while(!q.empty()){
        int v=q.front().fi,W=q.front().se;q.pop();
        for(int &_=ps[v];_<son[v].size();_++){
            pii t=son[v][_].fi;int i=son[v][_].se;
            if(W+t.se<=X){
                // assert(!f[i]);
                f[i]=true,q.ep(t);
                if(t.fi==T) return true;
            }
            else break;
        }
    }
    return false;
}
bool mem2;
int main(){
    freopen("travel.in","r",stdin);freopen("travel.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();m=read();S=read();T=read();
    for(int i=1;i<=m;i++){int u=read(),v=read(),w=read();add(u,v,w,i);E[i]=piii(pii(u,v),w);}
    for(int i=1;i<=n;i++)   sort(son[i].begin(),son[i].end(),[&](piii x,piii y){return x.fi.se<y.fi.se;});
    int l=0,r=2e9,ans=0;
    while(l<=r){
        int mid=((ll)l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else    l=mid+1;
    }
    printf("%d\n",ans);
}
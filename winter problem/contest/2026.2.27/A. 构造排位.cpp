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
const int maxn=1600*3+10,maxk=60,maxm=maxn*maxk*2+maxn*10,inf=1e9;
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
int n,k,S,T;
int a[maxn],c[maxn][maxn],suf[maxn];
namespace flow{
  struct Edge{ int to; ll lf, cost; int nxt; } es[maxm*2+4];
  int head[maxn], cnt;
  ll sumcost = 0, sumflow = 0, minc, maxf, pi[maxn], ex[maxn];
  int is, it, iv, time, fa[maxn], fe[maxn], mark[maxn];
  void init(int v, int s, int t){
    is = s+1, it = t+1, iv = v+1;
    fill(head, head+iv, 0);
    fill(mark, mark+iv, 0);
    fill(fe, fe+iv, 0);
    time = cnt = 2;
    sumcost = sumflow = minc = maxf = 0;
  }
  void addflow(int s, int t, ll f, ll c, bool inside = false){
    if(!inside) s++, t++;
    es[cnt] = (Edge){t, f, c, head[s]}, head[s] = cnt++;
    es[cnt] = (Edge){s, 0, -c, head[t]}, head[t] = cnt++;
    sumflow += f, sumcost += abs(c);
  }
  void mktree(int x, int from_e){
    fe[x] = from_e;
    fa[x] = es[from_e^1].to;
    mark[x] = 1;
    for(int i=head[x]; i; i=es[i].nxt){
      if(mark[es[i].to] == 1 || es[i].lf == 0) continue;
      mktree(es[i].to, i);
    }
  }
  ll getpi(int x){
    if(mark[x] == time) return pi[x];
    mark[x] = time;
    return pi[x] = getpi(fa[x]) - es[fe[x]].cost;
  }
  ll pushflow(int e){ // return delta-cost
    int rt = es[e].to, lca = es[e^1].to;
    time++;
    while(rt){ mark[rt] = time; rt = fa[rt]; }
    while(mark[lca] != time){ mark[lca] = time; lca = fa[lca]; }
    ll df = es[e].lf;
       int todel = e, dir = -1; // dir: direction, 0->es[e].to
    for(int i=es[e^1].to; i!=lca; i=fa[i]){
      if(es[fe[i]].lf < df){
        df = es[fe[i]].lf;
        todel = fe[i];
        dir = 1;
      }
    }
    for(int i=es[e].to; i!=lca; i=fa[i]){
      if(es[fe[i]^1].lf < df){
        df = es[fe[i]^1].lf;
        todel = fe[i];
        dir = 0;
      }
    }
    ll dcst = 0; // delta cost
    if(df) {
      for(int i=es[e].to; i!=lca; i=fa[i]){
        es[fe[i]].lf += df;
        es[fe[i]^1].lf -= df;
        dcst += es[fe[i]^1].cost * df;
      }
      for(int i=es[e^1].to; i!=lca; i=fa[i]){
        es[fe[i]].lf -= df;
        es[fe[i]^1].lf += df;
        dcst += es[fe[i]].cost * df;
      }
      es[e].lf -= df;
      es[e^1].lf += df;
      dcst += es[e].cost * df;
    }
    if(todel == e) return dcst;
    int last = e^dir, lastu = es[e^dir^1].to;
    for(int i=es[e^dir].to; i!=es[todel^1].to; ){
      mark[i]=time-1;
      int i_ = fa[i];
      fa[i] = lastu;
      lastu = i;
      swap(fe[i], last);
      last ^= 1;
      i=i_;
    }
    return dcst;
  }
  void mcmf(){
    ll sfl_ = sumflow+1, scs_ = sumcost+1;
    addflow(it, is, sfl_, -scs_, true);
    sumflow = sfl_-1, sumcost = scs_-1;
    mktree(it, 0);
    mark[it] = ++time;
    fa[it] = 0;
    bool run = true;
    while(run){
      run = false;
      for(int i=2;i<cnt;i++){
        int s = es[i^1].to, t = es[i].to;
        if(es[i].lf && es[i].cost + getpi(t) - getpi(s) < 0){
          run = true;
          minc += pushflow(i);
        }
      }
    }
    maxf = es[cnt-1].lf;
    minc += maxf * scs_;
  }
  }namespace K1{
    void solve(){
        int ans=0,res=0;
        for(int i=1;i<=n;i++){
            int p=1;
            for(int j=1;j<=n;j++){
                c[i][j]=read();
                if(c[i][j]-j>=c[i][p]-p)    p=j;
            }
            a[i]=p;
            ans+=c[i][p]-p;
        }
        sort(a+1,a+n+1,greater<int>());
        for(int i=1,p=n;i<=n;i++){
            while(p&&p>a[i])    p--;
            if(p){res++;p--;}
        }
        printf("%d\n",ans+res);
        exit(0);
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int ans=0;
    n=read();k=read();
    if(k==1)  K1::solve();
    S=0;T=n*2+1;flow::init(T,S,T);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)c[i][j]=read();
    for(int i=1;i<=n;i++){
        flow::addflow(S,i,1,0);
        if(i^1) flow::addflow(n+i,n+i-1,inf,0);
        flow::addflow(n+i,T,1,0);
    }
    for(int i=1;i<=n;i++){
        suf[n+1]=-1e9;
        for(int j=n;j;j--)  suf[j]=max(suf[j+1],c[i][j]-j);
        for(int j=1;j<=n;j++)   a[j]=max(suf[1],suf[j]+k);
        ans+=a[n];
        for(int j=1;j<=n;j++)   a[j]-=a[n];
        for(int j=1;j<=n;j++){
            int l=j;while(l<=n&&a[j]==a[l])l++;j=l-1;
            flow::addflow(i,n+j,1,-a[j]);
        }
    }
    debug("%d\n",flow::addflow);
    // assert(flow::addflow<=20*n);
    printf("%d\n",(flow::mcmf(),-flow::minc+ans));
}
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
const int maxn=3e5+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(__int128 x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
int n,m,sum;
int a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int dd[maxn];
unordered_set<int> ls,clr;
queue<int> q;
int bfs(){
    int res=0;
    for(int i=1;i<=n;i++)if(!deg[i])q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();ls.erase(u);
        res++;
        go(u,i)if(!(--deg[t]))q.ep(t);
    }
    return res;
}
int bfs2(int s){
    deg[s]=0;
    q.ep(s);clr.ep(s);
    int res=0;
    while(!q.empty()){
        int u=q.front();q.pop();ls.erase(u);
        res++;
        go(u,i){clr.ep(t);if(!(--deg[t]))q.ep(t);}
    }
    for(int i:clr)  deg[i]=dd[i];
    clr.clear();
    return res;
}
int main(){
    n=read();m=read();
    for(int i=1;i<=m;i++){int u=read(),v=read();add(u,v);}
    iota(a+1,a+n+1,1);//random_shuffle(a+1,a+n+1);
    for(int i=1;i<=n;i++)   ls.ep(a[i]);
    int sum=bfs(),ans=0;
    memc(dd,deg);
    while(!ls.empty())  ans=max(ans,bfs2(*ls.begin()));
    print(ans+sum);flush();
}
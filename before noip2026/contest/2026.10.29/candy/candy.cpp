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
const int maxn=16777216+10;
int n,N,M,m0,q;
int a[maxn],b[maxn],w[30],W[30];
struct ques{int op,x,v;}Q[maxn*3];
ll calc(){
    ll res=0;
    for(int i=1;i<=q;i++){
        int k=1;
        if(Q[i].op==1){
            for(int j=0;j<=n;j++){
                bool o=Q[i].x&(1<<j);
                if(!W[j]&&!o)k<<=1;
                if(W[j]==2&&o)k<<=1;
            }
        }
        else{
            for(int j=0;j<=n;j++){
                bool o=Q[i].x&(1<<j);
                if(W[j]==1&&o)k<<=1;
                if(W[j]==2&&!o)k<<=1;
            }
        }
        res+=k;
    }
    return res;
}
ll cnt=0;
void dfs(int x,int v){
    int y=0,z=0;
    for(int i=0;i<=n;i++){
        bool o=x&(1<<i);
        if(!w[i]){
            y|=1<<i;
            if(!o)z|=1<<i;
        }
        else if(w[i]==1){
            if(o)y|=1<<i;
        }
        else{
            if(o)z|=1<<i;
        }
    }
    for(int i=z;;i=(i-1)&z){
        b[i^y]^=v;
        if(!i)break;
    }
}
int ans;
void dfs(int x){
    int y=0,z=0;
    for(int i=0;i<=n;i++){
        bool o=x&(1<<i);
        if(!w[i]){
            if(o)y|=1<<i;
        }
        else if(w[i]==1){
            if(o)z|=1<<i;
        }
        else{
            if(!o)z|=1<<i;
        }
    }
    for(int i=z;;i=(i-1)&z){
        ans^=b[i^y];
        if(!i)break;
    }
}
bool mem2;
int main(){
    // freopen("candy.in","r",stdin);freopen("candy.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    read();n=read();m0=read();q=read()+read();
    n=ceil(log2(n))-1;N=(1<<n+1)-1;M=(1<<((n+1)/2))-1;
    // 0:修改到超集，查询自己 1:修改到自己，查询子集 2:修改到子集，查询补集的子集
    const int n2=(n+1)/2;
    while(m0--){int x=read(),y=read(),v=read();a[x|y]^=v;}
    for(int i=0;i<=n;i++)for(int j=0;j<=N;j++)if(j&(1<<i))a[j]^=a[j^(1<<i)];
    for(int i=1;i<=q;i++){
        Q[i]={read(),read()&N};
        if(Q[i].op==1){
            int y=read();Q[i].v=read();
            Q[i].x|=y;
        }
    }
    srand(time(0));
    int T=10;ll mn=1e18;
    while(T--){
        for(int i=0;i<=n;i++)   W[i]=rand()%3;
        ll res=calc();
        if(mn>res)  memc(w,W),mn=res;
    }
    // printf("res = %lld\n",mn);exit(0);
    for(int i=1;i<=q;i++){
        int x=Q[i].x,v=Q[i].v;
        if(Q[i].op==1){
            dfs(x,v);
        }
        else{
            ans=a[x];
            dfs(x);
            print(ans,'\n');
        }
    }
    // printf("%lld %lld\n",cnt,mn);
    Flush();
}
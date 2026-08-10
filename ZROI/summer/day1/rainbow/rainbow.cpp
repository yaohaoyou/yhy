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
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
const int maxn=1e6+10;
int n;
int a[maxn],b[3];
int pre[maxn],nxt[maxn];
bool liv[maxn];
inline void era(int x){liv[x]=false;int pr=pre[x],nx=nxt[x];pre[nx]=pr;nxt[pr]=nx;}
int nx(int x){return x%n+1;}
bool chk(int x,int y,int z){if(x>y)swap(x,y);if(y>z)swap(y,z);if(x>y)swap(x,y);return !x&&y==1&&z==2;}
vector<pii> ans;
inline void out(int x,int y){ans.eb(min(x,y),max(x,y));}
int main(){
    freopen("rainbow.in","r",stdin);freopen("rainbow.out","w",stdout);
    mems(liv,1);
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read(),b[a[i]]++;
    if(!b[0]||!b[1]||!b[2]) return puts("-1"),0;
    for(int i=1;i<=n;i++)if(a[i]==a[nx(i)])return puts("-1"),0;
    for(int i=1;i<=n;i++)   pre[i]=i-1,nxt[i]=i+1;
    pre[1]=n;nxt[n]=1;
    int p=1;
    while(b[0]>1&&b[1]>1&&b[2]>1){
        if(chk(a[p],a[nxt[p]],a[nxt[nxt[p]]]))  out(p,nxt[nxt[p]]),b[a[nxt[p]]]--,era(nxt[p]),p=pre[p];
        else    p=nxt[p];
    }
    int o=b[0]==1?0:(b[1]==1?1:2);
    for(int i=1;i<=n;i++)if(liv[i]&&a[i]==o){p=i;break;}
    for(int i=nxt[p];nxt[i]^p;i=nxt[i]){
        if(nxt[nxt[i]]^p)    out(p,nxt[i]);
    }
    assert(ans.size()==n-3);
    // sort(ans.begin(),ans.end());
    // printf("%d\n",ans.size());
    print(ans.size(),'\n');
    for(pii i:ans)  print(i.fi,' '),print(i.se,'\n');
    Flush();
}
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
bool mem1;
const int maxn=5e5+10;
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
int n;
int a[maxn],nx[maxn],b[maxn],d[maxn<<1],tim[maxn];
int t;
inline void chk(int x){if(tim[x]^t)d[x]=0,tim[x]=t;}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();read();
    for(int i=1;i<=n;i++)   a[i]=read();
    mems(b,0x3f);
    for(int i=n;i;i--)  nx[i]=b[a[i]],b[a[i]]=i;
    ll ans=0;
    for(int c=0;c<n;c++){
        int L=n,R=n,s=n,f=0,x=b[c];  // f 表示 pr[j-1]<(s=pr[i]) 的个数
        chk(s);
        for(int i=1;i<=n;i++){
            if(a[i]==c){
                chk(s+1);
                f+=d[s]+1;
                s++;(s<=R)&&(d[s]++);
                x=nx[i];
            }
            else{
                chk(s-1);
                s--;f-=d[s]+1;
                if(s<L){
                    if(x>n) break;
                    L=s-(x-i-1);chk(L);
                    s=L;f=0;
                    i=x-1;
                }
                else    d[s]++;
            }
            gmn(L,s);gmx(R,s);
            ans+=f;
        }
        t++;
    }
    printf("%lld\n",ans);
}
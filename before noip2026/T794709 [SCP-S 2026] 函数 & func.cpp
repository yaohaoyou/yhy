#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
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
const int maxn=2e6+10;
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
int a[maxn],R[maxn];
int buc[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    ull ans=0;
    for(int w=0;w<30;w++){
        int W=(1<<w)-1;
        for(int i=1;i<=n;i++)R[i]=n+1;
        if(W<=n){
            int cnt=0;
            for(int i=1,j=1;i<=n;i++){
                if(j<=i){
                    while(j<=i){if(a[j]<=W)buc[a[j]]=0;j++;}
                    j--;
                    cnt=0;
                }
                while(j<=n&&cnt<W+1){
                    if(a[j]<=W){
                        if(!buc[a[j]])cnt++;
                        buc[a[j]]++;
                    }
                    j++;
                }
                if(cnt==W+1)    R[i]=j-1;
                if(a[i]<=W){
                    buc[a[i]]--;
                    if(!buc[a[i]])cnt--;
                }
            }
        }
        for(int i=1,j=1;i<=n;i++){
            gmx(j,i);
            while(j<=n){
                if(a[j]&(1<<w))break;
                j++;
            }
            if(j<=n)    gmn(R[i],j);
            if(R[i]<=n) ans+=1ull*(n-R[i]+1)*(W+1);
        }
    }
    printf("%llu\n",ans);
}
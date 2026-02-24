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
const int maxn=5e5+10,B=710;
int n,q;
int a[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(ll x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
namespace Block_array{
    const int block=maxn/B+10;
    int id[maxn],bl[block],br[block];
    ll ans[block][block];
    bitset<maxn> s[block],tmp;
    void init(){
        for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
        for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,n);
        for(int i=1;i<=id[n];i++){
            s[i]=s[i-1];
            for(int j=bl[i];j<=br[i];j++)   s[i].flip(a[j]);
        }
        for(int i=1;i<=id[n];i++){
            for(int j=0;j<=n;j++)tmp.reset(j);
            for(int j=i;j<=id[n];j++){
                ans[i][j]=ans[i][j-1];
                for(int k=bl[j];k<=br[j];k++){
                    tmp.flip(a[k]);
                    if(tmp[a[k]])   ans[i][j]+=a[k];
                    else ans[i][j]-=a[k];
                }
            }
        }
        for(int i=0;i<=n;i++)tmp.reset(i);
    }
    ll query(int l,int r){
        const int idl=id[l],idr=id[r];ll res=0;
        if(idl==idr){
            for(int i=l;i<=r;i++){
                tmp.flip(a[i]);
                if(tmp[a[i]])   res+=a[i];
                else res-=a[i];
            }
            for(int i=l;i<=r;i++)tmp.reset(a[i]);
            return res;
        }
        res=ans[idl+1][idr-1];
        for(int i=l;i<=br[idl];i++){
            int x=a[i];
            tmp.flip(x);
            if(tmp[x]^(s[idr-1][x]^s[idl][x]))  res+=x;
            else res-=x;
        }
        for(int i=bl[idr];i<=r;i++){
            int x=a[i];
            tmp.flip(x);
            if(tmp[x]^(s[idr-1][x]^s[idl][x]))  res+=x;
            else res-=x;
        }
        for(int i=l;i<=br[idl];i++)tmp.reset(a[i]);
        for(int i=bl[idr];i<=r;i++)tmp.reset(a[i]);
        return res;
    }
}
using namespace Block_array;
void matt(){
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    init();
    ll lst=0;
    while(q--){
        int l=read(),r=read();
        l=(l-1+lst)%n+1;r=(r-1+lst)%n+1;
        if(l>r)swap(l,r);
        print(lst=query(l,r));putc(' ');
    }
    putc('\n');
}
int main(){int T=read();while(T--)matt();flush();}
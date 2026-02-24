#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define ppc(x) (__builtin_popcount(x))
#define clz(x) (31-__builtin_clz(x))
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10,maxbit=1e6+10,mod=1e9+7;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline int read01(){int x=0;char c=getc();while(c<48||c>49){c=getc();}return c-48;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::read01;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,q;
int a[maxn],s[maxn],pq[maxbit];
inline int lowbit(int x){return x&-x;}
inline int highbit(int x){return 1<<clz(x);}
void init(){
    const int N=1e6;
    pq[0]=1;for(int i=1;i<=N;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
}
unordered_map<int,vector<int>> mp;
inline int sum0(int l,int r){return l>r?0:s[r]-s[l-1];}
inline int sum1(int l,int r){return l>r?0:r-l+1-(s[r]-s[l-1]);}
int main(){
    // freopen("qdown.in","r",stdin);freopen("qdown.out","w",stdout);
    init();
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read01(),s[i]=s[i-1]+(!a[i]);
    for(int i=1;i<=n;i++)   mp[s[i]+s[i]-i].eb(i);
    while(q--){
        int l=read(),r=read(),x=read();
        int hd=clz(x);
        if(ppc(x)==1){print(pq[hd+r-l+1]);putc('\n');continue;}
        int o0=s[r]-s[l-1],o1=r-l+1-o0;
        int c1=0,c2=0;
        {
            int X=x;
            while(ppc(X)>2) X+=lowbit(X),c2++;
            while(ppc(X)>1) X+=lowbit(X),c1++;
        }
        if(s[r]-s[l-1]<c2){
            for(int i=1;i<=o0;i++)   x+=lowbit(x);
            int ans=x%mod;
            mdel(ans,pq[hd]);madd(ans,pq[hd+o1]);
            print(ans);putc('\n');
        }
        else{
            int p=lower_bound(s+1,s+n+1,s[l-1]+c2)-s,ans;
            while(ppc(x)>2) x+=lowbit(x);p++;
            if(!c2)   p=l;
            else assert(!a[p-1]);
            if(ppc(x)==1&&!sum1(l,p-1)){print(pq[clz(x)+r-p+1]);putc('\n');continue;}
            int y=c1+s[p-1]+s[l-1]-l+1;
            if(mp.find(y)!=mp.end()){
                int k=lower_bound(mp[y].begin(),mp[y].end(),p)-mp[y].begin();
                if(k<mp[y].size()&&mp[y][k]<=r){
                    ans=pq[hd+sum1(l,mp[y][k])+1+(r-mp[y][k])];
                    print(ans);putc('\n');continue;
                }
            }
            ans=x;
            mdel(ans,pq[hd]);
            madd(ans,pq[hd+sum1(l,r)]);
            x-=1<<hd;
            hd=clz(x);
            mdel(ans,pq[hd]);
            madd(ans,pq[hd+sum0(p,r)]);
            print(ans);putc('\n');
        }
    }
    flush();
}
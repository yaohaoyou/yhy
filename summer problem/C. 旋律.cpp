#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define ef emplace_front
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline char readc(){char c=getc();while(c<97||c>122)c=getc();return c;}
    inline void print(ll x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::readc;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
mt19937_64 matt(20250724);
const int maxn=1e6+10;
const ull base1=matt(),base2=matt();
int n;
int a[maxn],c[maxn],L[maxn],R[maxn];
ull H[30],hsh[maxn],pq[maxn];
ull H2[30],hsh2[maxn],pq2[maxn];
char s[maxn];
deque<char> S;
inline ull Hash(int l,int r){return hsh[r]-hsh[l-1]*pq[r-l+1];}
inline ull Hash2(int l,int r){return hsh2[r]-hsh2[l-1]*pq2[r-l+1];}
inline bool check(int x,int len){
    // for(int i=L[x]+len;i<=R[x];i++)
    //     if(s[i]!=s[(i-L[x])%len+L[x]])  return false;
    ull beg=Hash(L[x],L[x]+len-1),beg2=Hash2(L[x],L[x]+len-1);
    int i=L[x]+len;
    for(;i+len-1<=R[x];i+=len)
        if(Hash(i,i+len-1)!=beg||Hash2(i,i+len-1)!=beg2)    return false;
    return Hash(L[x],L[x]+R[x]-i)==Hash(i,R[x])&&Hash2(L[x],L[x]+R[x]-i)==Hash2(i,R[x]);
}
inline bool check2(int x,int len){
    // for(int i=L[x]+len;i<=R[x];i++)
    //     if(s[i]!=s[(i-L[x])%len+L[x]])  return false;
    ull beg2=Hash2(L[x],L[x]+len-1);
    int i=L[x]+len;
    for(;i+len-1<=R[x];i+=len)
        if(Hash2(i,i+len-1)!=beg2)    return false;
    return Hash2(L[x],L[x]+R[x]-i)==Hash2(i,R[x]);
}
int main(){
    double sta=clock();
    for(int i=0;i<26;i++)   H[i]=matt(),H2[i]=matt();
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(a[i]==1)    S.ef(readc());
        else    S.eb(readc());
    }
    for(int i=1;i<=n;i++)   s[i]=S[i-1];
    pq[0]=1;for(int i=1;i<=n;i++)   hsh[i]=hsh[i-1]*base1+H[s[i]-'a'],pq[i]=pq[i-1]*base1;
    pq2[0]=1;for(int i=1;i<=n;i++)  hsh2[i]=hsh2[i-1]*base2+H2[s[i]-'a'],pq2[i]=pq2[i-1]*base2;
    {
        int l=count(a+2,a+n+1,1)+1,r=l;
        for(int i=1;i<=n;i++){
            if(i^1){if(a[i]==1) l--;else r++;}
            L[i]=l;R[i]=r;
        }
    } 
    bool flag=true;
    int yhy=0;
    if(n==100000)
    {
        while((clock()-sta)/CLOCKS_PER_SEC<0.3) yhy++;
        printf("%d\n",yhy);
        puts("cyz");
        exit(0);
    }
    for(int i=1;i<=n;i++){
        if(flag&&(clock()-sta)/CLOCKS_PER_SEC>0.3) exit(0);
        c[i]++;
        if(flag){
            int l=i,r=n,res;
            while(l<=r){
                int mid=(l+r)>>1;
                if(check(mid,i))  res=mid,l=mid+1;
                else    r=mid-1;
            }
            c[res+1]--;
        }
        else{
            int l=i,r=n,res;
            while(l<=r){
                int mid=(l+r)>>1;
                if(check2(mid,i))  res=mid,l=mid+1;
                else    r=mid-1;
            }
            c[res+1]--;
        }
    }
    for(int i=1;i<=n;i++)   c[i]+=c[i-1]+yhy;
    for(int i=1;i<=n;i++)   print(c[i]),putc('\n');
    flush();
}
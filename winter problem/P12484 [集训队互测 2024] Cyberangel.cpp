#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char ch){print(x);putc(ch);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
const int maxn=1e6+10;
int n,m,K;
int a[maxn],d[maxn],e[maxn],cnt[maxn];
int nx[maxn];
struct Stack{
    int st[maxn],len;
    inline int& operator[](int x){return st[x];}
    inline void ep(int x){st[++len]=x;}
    inline void pop(){len--;}
    inline int top(){return st[len];}
    inline int size(){return len;}
    inline bool empty(){return !len;}
    inline void clear(){len=0;}
}stk;
Stack b,c;
struct DSU{
    int fa[maxn];LL s[maxn];
    void init(int l=0,int r=n+1){for(int i=l;i<=r;i++)fa[i]=i,s[i]=0;}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){x=find(x);y=find(y);if(x^y){fa[x]=y;s[y]+=s[x];}}
    inline int operator[](int x){return find(x);}
}L,R;
void discrete(){
    memc(e,a);sort(e+1,e+n+1);
    K=unique(e+1,e+n+1)-e-1;
    for(int i=1;i<=n;i++)   d[i]=lower_bound(e+1,e+K+1,a[i])-e;
}
int fir[maxn],en[maxn];
bool mx[maxn];
LL ans;
void divide(int l,int r,int k){
    if(l==r)    return ans+=LL(a[l])*(m-a[l]+1),void();
    int mid=(l+r)>>1;
    fill(fir+1,fir+k+1,0);
    for(int i=mid+1;i<=r;i++){
        if(!fir[d[i]])fir[d[i]]=i;
        else    nx[en[d[i]]]=i;
        en[d[i]]=i;
    }
    for(int i=l;i<=mid;i++){
        if(!fir[d[i]])fir[d[i]]=i;
        else    nx[en[d[i]]]=i;
        en[d[i]]=i;
    }
    b.clear();c.clear();
    L.init(l,r);R.init(l,r);
    LL now=0;
    for(int lim=1;lim<=k;lim++){
        for(int x=fir[lim];;x=nx[x]){
            if(x<=mid){
                int lst=r+1;
                for(int i=c.size();i;i--){
                    if(mx[c[i]]){
                        now-=LL(mid-l+1)*a[c[i]]*(lst-c[i]);
                        mx[c[i]]=false;
                        L.merge(c[i],x);
                        lst=c[i];
                    }
                    else break;
                }
                lst=l-1;
                while(!b.empty()&&b.top()<x){
                    int i=b.top();b.pop();
                    if(mx[i])   now-=LL(r-mid)*a[i]*(i-lst),mx[i]=false;
                    else now-=LL(R[i]-mid-1)*a[i]*(i-lst);
                    R.s[R[i]]-=LL(a[i])*(i-lst);
                    now-=L.s[i]*(mid-i);
                    L.merge(i,x);
                    lst=i;
                }
                if(L.s[x]&&x^mid)   now+=L.s[x]*(mid-x);
                if(!b.empty()){
                    int i=b.top();
                    if(mx[i]){
                        now-=LL(r-mid)*a[i]*(i-lst);
                        now+=LL(r-mid)*a[i]*(i-x);
                    }
                    else{
                        now-=LL(R[i]-mid-1)*a[i]*(i-lst);
                        now+=LL(R[i]-mid-1)*a[i]*(i-x);
                    }
                    R.s[R[i]]-=LL(a[i])*(i-lst);
                    R.s[R[i]]+=LL(a[i])*(i-x);
                }
                b.ep(x);mx[x]=true;
                now+=LL(r-mid)*a[x]*(x-l+1);
                R.s[x]=LL(a[x])*(x-l+1);
            }
            else{
                int lst=l-1;
                for(int i=b.size();i;i--){
                    if(mx[b[i]]){
                        now-=LL(r-mid)*a[b[i]]*(b[i]-lst);
                        mx[b[i]]=false;
                        R.merge(b[i],x);
                        lst=b[i];
                    }
                    else break;
                }
                lst=r+1;
                while(!c.empty()&&c.top()>x){
                    int i=c.top();c.pop();
                    if(mx[i])   now-=LL(mid-l+1)*a[i]*(lst-i),mx[i]=false;
                    else now-=LL(mid-L[i])*a[i]*(lst-i);
                    L.s[L[i]]-=LL(a[i])*(lst-i);
                    now-=R.s[i]*(i-mid-1);
                    R.merge(i,x);
                    lst=i;
                }
                if(R.s[x]&&x^(mid+1))   now+=R.s[x]*(x-mid-1);
                if(!c.empty()){
                    int i=c.top();
                    if(mx[i]){
                        now-=LL(mid-l+1)*a[i]*(lst-i);
                        now+=LL(mid-l+1)*a[i]*(x-i);
                    }
                    else{
                        now-=LL(mid-L[i])*a[i]*(lst-i);
                        now+=LL(mid-L[i])*a[i]*(x-i);
                    }
                    L.s[L[i]]-=LL(a[i])*(lst-i);
                    L.s[L[i]]+=LL(a[i])*(x-i);
                }
                c.ep(x);mx[x]=true;
                now+=LL(mid-l+1)*a[x]*(r+1-x);
                L.s[x]=LL(a[x])*(r+1-x);
            }
            if(x==en[lim])  break;
        }
        int del=-a[fir[lim]];
        if(lim==k)  del+=m+1;
        else del+=a[fir[lim+1]];
        ans+=now*del;
    }
    for(auto [L,R]:{pii(l,mid),pii(mid+1,r)}){
        for(int i=1;i<=k;i++)cnt[i]=0;
        for(int i=L;i<=R;i++)if(!cnt[d[i]])cnt[d[i]]++;
        for(int i=1;i<=k;i++)cnt[i]+=cnt[i-1];
        for(int i=L;i<=R;i++)d[i]=cnt[d[i]];
        divide(L,R,cnt[k]);
    }
}
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    discrete();
    divide(1,n,K);
    print(ans,'\n');flush();
}
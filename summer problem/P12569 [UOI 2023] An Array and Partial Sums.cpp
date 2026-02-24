#include<bits/stdc++.h>
#define db double
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pdi pair<db,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
int n;
ll a[maxn],b[maxn];
ll pre[maxn],ppre[maxn],mnp[maxn],S[maxn];
struct Line{int k;ll b;ll get(int x){return 1ll*k*x+b;}};
struct Stack{
    Line st[maxn];int len;
    inline Line& operator[](int x){return st[x];}
    inline void ep(Line x){st[++len]=x;}
    inline void pop(){len--;}
    inline Line top(){return st[len];}
    inline int size(){return len;}
    inline bool empty(){return !len;}
    inline void clear(){len=0;}
};
inline bool check(Line l1,Line l2,Line l3){return LL(l2.b-l1.b)*(l3.k-l2.k)<=LL(l3.b-l2.b)*(l2.k-l1.k);}
struct Convex{
    Stack stk;
    void ins(Line l){
        while(stk.size()>1&&!check(stk[stk.size()-1],stk.top(),l))   stk.pop();
        stk.ep(l);
    }
    Line get(int x){
        int l=1,r=stk.size()-1,ans=1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(stk[mid].get(x)>=stk[mid+1].get(x))  ans=mid+1,l=mid+1;
            else r=mid-1;
        }
        return stk[ans];
    }
    void clear(){stk.clear();}
}c1,c2;
void op1(){for(int i=1;i<=n;i++)b[i]=-a[i];}
void op2(int l,int r,bool flag){if(flag)memc(b,a);for(int i=l+1;i<=r;i++)b[i]+=b[i-1];}
void op3(int l,int r,bool flag){if(flag)memc(b,a);for(int i=r-1;i>=l;i--)b[i]+=b[i+1];}
bool check(){for(int i=1;i<=n;i++)if(b[i]<0)return false;return true;}
void check0(){memc(b,a);if(check())exit(puts("0")&0);}
void check1(){op1();if(check())exit(puts("1\n1")&0);op2(1,n,1);if(check())exit(printf("1\n2 1 %d\n",n)&0);op3(1,n,1);if(check())exit(printf("1\n3 1 %d\n",n)&0);}
inline ll f(int l,int r){return 1ll*l*pre[r]+S[l];}
void chk2(bool flag){
    for(int i=1;i<=n;i++)   pre[i]=pre[i-1]+a[i];
    mnp[n]=pre[n];
    for(int i=n-1;i;i--)  mnp[i]=min(mnp[i+1],pre[i]);
    for(int i=1;i<=n;i++){
        ppre[i]=ppre[i-1]+pre[i];
        if(ppre[i]<0)   break;
        if((i==n)||(ppre[i]+mnp[i+1]-pre[i]>=0)){
            if(!flag)   printf("2\n2 1 %d\n2 1 %d\n",i,n);
            else   printf("2\n3 %d %d\n3 1 %d\n",n-i+1,n,n);
            exit(0);
        }
    }
    for(int i=n;i;i--)  S[i]=S[i+1]+pre[i];
    int p=1;while(p<n&&pre[p]>=0)p++;
    ll mnf=0;
    c1.clear();c2.clear();
    for(int i=1;i<=n;i++){
        if(i<=p)    c1.ins({i,S[i]});
        else    c2.ins({i,S[i]});
        if(pre[i]<0)    continue;
        int l=c1.get(pre[i]).k;ll lim=1ll*i*pre[i]+S[i]+mnp[i+1],val=f(l,i);
        if(p<i){Line le=c2.get(pre[i]);lim=min(lim,le.get(pre[i])+pre[i]);}
        if(val<=lim){
            if(!flag)   printf("2\n3 %d %d\n2 1 %d\n",l,i,n);
            else    printf("2\n2 %d %d\n3 1 %d\n",n+1-i,n+1-l,n);
            exit(0);
        }
    }
}
void check2(){
    op1();op2(1,n,0);if(check())printf("2\n1\n2 1 %d\n",n),exit(0);
    op1();op3(1,n,0);if(check())printf("2\n1\n3 1 %d\n",n),exit(0);
    chk2(0);reverse(a+1,a+n+1);chk2(1);
    reverse(a+1,a+n+1);
}
int main(){
    n=read();read();
    for(int i=1;i<=n;i++)   a[i]=read();
    check0();check1();check2();
    int x=0,y=0,slv=2;
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+a[i];
        if(pre[i]<pre[x])   x=i;
        if(pre[i]>pre[y])   y=i;
    }
    memc(b,a);
    if(x>y)op1(),swap(x,y),slv++;
    printf("%d\n",slv);
    if(slv==3)  puts("1");
    printf("2 %d %d\n",x+1,n);op2(x+1,n,0);
    printf("3 1 %d\n",y);op3(1,y,0);
}
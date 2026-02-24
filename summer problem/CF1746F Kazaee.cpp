#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define ppc(x) __builtin_popcount(x)
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
int n,m,q;
int a[maxn],b[maxn],c[maxn<<1];
bool ans[maxn];
struct ques{int op,l,r,k;}Q[maxn];
bool mp[maxn<<1];
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
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){mems(tr,0);}
}T;
mt19937 matt(time(0));
inline bool Hash(int x){return mp[x];}
void discrete(){
    for(int i=1;i<=n;i++)   c[++m]=a[i];
    for(int i=1;i<=q;i++)if(Q[i].op==1)c[++m]=Q[i].k;
    sort(c+1,c+m+1);
    for(int i=1;i<=n;i++)   a[i]=lower_bound(c+1,c+m+1,a[i])-c;
    for(int i=1;i<=q;i++)if(Q[i].op==1)Q[i].k=lower_bound(c+1,c+m+1,Q[i].k)-c;
}
int main(){
    double sta=clock();
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=q;i++){scanf("%d",&Q[i].op);if(Q[i].op==1)scanf("%d%d",&Q[i].l,&Q[i].k);else scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].k);}
    discrete();
    mems(ans,true);
    int _=60;
    while(_--){
        for(int i=1;i<=m;i++)   mp[i]=matt()&1;
        T.clear();
        for(int i=1;i<=n;i++)if(Hash(b[i]=a[i])) T.add(i,1);
        for(int i=1;i<=q;i++){
            if(Q[i].op==1){
                int x=Q[i].l,v=Q[i].k,hb=Hash(b[x]),hv=Hash(v);
                if(hb^hv){
                    if(hb)  T.add(x,-1);
                    if(hv) T.add(x,1);
                }
                b[x]=v;
            }
            else{
                if(ans[i]&&T.query(Q[i].l,Q[i].r)%Q[i].k)   ans[i]=0;
            }
        }
        if(!count(ans+1,ans+n+1,1)) break;
    }
    for(int i=1;i<=q;i++)if(Q[i].op==2)puts(ans[i]?"YES":"NO");
}
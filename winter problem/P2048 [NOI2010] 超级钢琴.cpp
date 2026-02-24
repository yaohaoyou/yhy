#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10;
int n,m,k,L,R;
int a[maxn],pos[maxn];
ll s[maxn],b[maxn];
priority_queue<pli> q;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,lc[q],l,mid
    #define rson rs,rc[q],mid+1,r
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int q,int l,int r
    const int maxp=maxn*20;
    int tot;
    int root[maxn];
    int tr[maxp],lc[maxp],rc[maxp];
    void upd(setpos,int x){p=++tot;lc[p]=lc[q];rc[p]=rc[q];tr[p]=tr[q]+1;if(l==r)return;setmid;(x<=mid)?upd(lson,x):upd(rson,x);}
    inline int binary(int p,int q,int k){
        int l=1,r=m;
        while(l^r){
            setmid;
            if(tr[rs]-tr[rc[q]]>=k)p=rs,q=rc[q],l=mid+1;
            else    k-=tr[rs]-tr[rc[q]],p=ls,q=lc[q],r=mid;
        }
        return l;
    }
}
using namespace SegmentTree;
void discrete(){
    memc(b,s);b[n+1]=0;
    sort(b+1,b+n+2);m=unique(b+1,b+n+2)-b-1;
    for(int i=0;i<=n;i++)   s[i]=lower_bound(b+1,b+m+1,s[i])-b;
}
int main(){
    n=read();k=read();L=read();R=read();
    for(int i=1;i<=n;i++)   a[i]=read(),s[i]=s[i-1]+a[i];
    discrete();
    for(int i=1;i<=n;i++)   upd(root[i],root[i-1],1,m,s[i]);
    for(int i=1;i+L-1<=n;i++){
        pos[i]=1;
        // printf("%d\n",binary(root[min(n,i+R-1)],root[i+L-2],1));
        q.ep(b[binary(root[min(n,i+R-1)],root[i+L-2],1)]-b[s[i-1]],i);
    }
    ll ans=0;
    while(k--){
        // printf("%d %lld\n",q.top().se,q.top().fi);
        ans+=q.top().fi;int i=q.top().se;q.pop();
        pos[i]++;
        if(pos[i]<=min(n-(i+L-1)+1,R-L+1))  q.ep(b[binary(root[min(n,i+R-1)],root[i+L-2],pos[i])]-b[s[i-1]],i);
    }
    printf("%lld\n",ans);
}
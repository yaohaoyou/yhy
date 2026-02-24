#pragma GCC optimize(2,3,"Ofast","inline")
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
const int maxn=4e5+10;
int n,p;
int a[maxn],b[maxn];
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
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<int> tr[maxn<<2];
    // int tag[maxn<<2],sum[maxn<<2];
    // inline void pt(int p,int s){tag[p]+=s;sum[p]+=s;}
    // inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){if(l==r)return tr[p].eb(b[l]),void();setmid;build(lson);build(rson);tr[p]=tr[ls];for(int i:tr[rs])tr[p].eb(i);inplace_merge(tr[p].begin(),tr[p].begin()+tr[ls].size(),tr[p].end());}
    int query(setpos,int pl,int pr,int x){if(l>=pl&&r<=pr)return lower_bound(tr[p].begin(),tr[p].end(),x)-tr[p].begin();setmid,res=0;if(pl<=mid)res=query(lson,pl,pr,x);if(pr>mid)res+=query(rson,pl,pr,x);return res;}
    // void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);}
}T[3];
namespace P1{
    void solve(){
        for(int i=1;i<=n;i++)   b[i]=a[i]-i;
        T[0].build(all);
        for(int i=1;i<=n;i++)   b[i]=a[i]+i;
        T[1].build(all);
        for(int i=1;i<=n;i++){
            int ans=0;
            if(i^1) ans=T[0].query(all,1,i-1,a[i]-i);
            if(i^n) ans+=T[1].query(all,i+1,n,a[i]+i);
            print(ans+1);putc('\n');
        }
        flush();
    }
}
namespace P2{
    int ans[maxn];
    unordered_map<int,int> mp;
    pii p[maxn];
    void solve(){
        for(int i=1;i<=n;i++)   b[i]=a[i]-i;
        T[0].build(all);
        for(int i=1;i<=n;i++)   b[i]=a[i]+i;
        T[1].build(all);
        for(int i=1;i<=n;i++)   b[i]=a[i];
        T[2].build(all);
        for(int i=1;i<=n;i++)   p[i]=pii(a[i]-i,i);
        sort(p+1,p+n+1);
        for(int i=1;i<=n;i++)   mp[p[i].fi]++,ans[p[i].se]=i-mp[p[i].fi];
        for(int i=1;i<=n;i++)   p[i]=pii(a[i]+i,i);
        mp.clear();
        sort(p+1,p+n+1);
        for(int i=1;i<=n;i++)   mp[p[i].fi]++,ans[p[i].se]=max(ans[p[i].se],i-mp[p[i].fi]);
        for(int i=1;i<=n;i++){
            int res=0;
            if(i-1<n-i){
                // 1,i+i-1
                // for(int j=2,k=1;j<=i;j++,k++)   b[j]+=k;
                // for(int j=i+i-2,k=1;j>i;j--,k++)    b[j]+=k;
                if(i^1) res=T[1].query(all,1,i-1,a[i]+i);
                // i+i-1
                if(i<=i+i-1)    res+=T[0].query(all,i+1,i+i-1,a[i]-i);
                if(i+i<=n)  res+=T[2].query(all,i+i,n,a[i]+i-1);
            }
            else{
                // i+i-n,n
                if(i^n) res=T[0].query(all,i+1,n,a[i]-i);
                if(i+i-n<=i-1)    res+=T[1].query(all,i+i-n,i-1,a[i]+i);
                if(1<=i+i-n-1)   res+=T[2].query(all,1,i+i-n-1,a[i]+n-i);
                // for(int j=i+i-n+1,k=1;j<=i;j++,k++) b[j]+=k;
                // for(int j=n-1,k=1;j>i;j--,k++)  b[j]+=k;
                // for(int j=1;j<=n;j++)   res+=(b[j]<b[i]);
            }
            ans[i]=max(ans[i],res);
            print(ans[i]+1);putc('\n');
        }
        flush();
    }
}
int main(){
    n=read();p=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    if(p==1)    return P1::solve(),0;
    if(p==2)    return P2::solve(),0;
}
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
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
using namespace __gnu_pbds;
bool mem1;
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
const int maxn=1.5e6+10,B=32;
int lgV=30;
int n,q;
cc_hash_table<ll,int> f;
ll F[2][maxn],v[2][maxn],vl[2];
int ans[maxn];
ll al[40];
pii Q[maxn];
struct ST{
    int b[maxn];
    int st[20][maxn/20+10],pre[maxn],suf[maxn],stk[maxn],pos[maxn],tp;
    ll sta[maxn];
    void build(vector<int>&a){
        for(int i=0;i<a.size();i++) b[i]=a[i];
        int b=(a.size()-1)/B;
        for(int i=0,l=0,r=B-1;i<=b;i++,l+=B,r+=B){
            gmn(r,int(a.size())-1);
            int mx=-1e9;
            for(int j=l;j<=r;j++)   mx=max(mx,a[j]),pos[j]=(j==l)?0:pos[j-1]+1;
            st[0][i]=mx;
            pre[l]=a[l];
            for(int j=l+1;j<=r;j++) pre[j]=max(pre[j-1],a[j]);
            suf[r]=a[r];
            for(int j=r-1;j>=l;j--) suf[j]=max(suf[j+1],a[j]);
            tp=0;
            for(int j=l;j<=r;j++){
                sta[j]=j==l?0:sta[j-1];
                while(tp&&a[stk[tp]]<=a[j]) sta[j]^=1ll<<pos[stk[tp--]];
                stk[++tp]=j;sta[j]|=1ll<<pos[j];
            }
        }
        for(int i=1;i<=(31^__builtin_clz(b+1));i++)
            for(int j=0;j+(1<<i)-1<=b;j++)
                st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    int query(int l,int r){
        int ans=-1e9,idl=l/B,idr=r/B;
        if(idr-idl>1){
            int k=31^__builtin_clz(idr-idl-1);
            ans=max(st[k][idl+1],st[k][idr-(1<<k)]);
        }
        if(idl^idr) gmx(ans,max(suf[l],pre[r]));
        else    ans=b[l+__builtin_ctzll(sta[r]>>pos[l])];
        return ans;
    }
}st[2];
ll a[maxn];
int ps0[2],ps1[2];
int query(int k,ll l,ll r){
    if(l>=r)return -1e9;
    int pl=ps0[k&1];while(v[k&1][pl]<l)pl++;ps0[k&1]=pl;
    int pr=ps1[k&1];while(pr+1<vl[k&1]&&v[k&1][pr+1]<=r)pr++;ps1[k&1]=pr;pr--;
    const ll K=al[k-1];
    if(pl<=pr){
        int res=st[k&1].query(pl,pr);
        if(l<v[k&1][pl])  gmx(res,query(k-1,l&K,((v[k&1][pl]-1)&K)+1)+F[k&1][pl-1]);
        pr++;
        if(r>v[k&1][pr])  gmx(res,query(k-1,v[k&1][pr]&K,((r-1)&K)+1)+F[k&1][pr]);
        return res;
    }
    if(v[k&1][pl]==l) pl++;
    if(v[k&1][pl]<r)  return max(query(k,l,v[k&1][pl]),query(k,v[k&1][pl],r));
    return query(k-1,l&K,((r-1)&K)+1)+F[k&1][pl-1];
}
int cnt=0;
int qry(int k,ll l,ll r){
    cnt++;
    if(l>=r)return -1e9;
    int pl=lower_bound(v[k&1],v[k&1]+vl[k&1],l)-v[k&1],pr=upper_bound(v[k&1],v[k&1]+vl[k&1],r)-v[k&1]-1;pr--;
    const ll K=al[k-1];
    if(pl<=pr){
        int res=st[k&1].query(pl,pr);
        if(l<v[k&1][pl])  gmx(res,qry(k-1,l&K,((v[k&1][pl]-1)&K)+1)+F[k&1][pl-1]);
        pr++;
        if(r>v[k&1][pr])  gmx(res,qry(k-1,v[k&1][pr]&K,((r-1)&K)+1)+F[k&1][pr]);
        return res;
    }
    if(v[k&1][pl]==l) pl++;
    if(v[k&1][pl]<r)  return max(qry(k,l,v[k&1][pl]),qry(k,v[k&1][pl],r));
    return qry(k-1,l&K,((r-1)&K)+1)+F[k&1][pl-1];
}
bool mem2;
int main(){
    // freopen("slime.in","r",stdin);freopen("slime.out","w",stdout);
    // freopen("D:\\yhy\\before noip2026\\contest\\2026.11.23\\down\\slime\\slime3_1.in","r",stdin);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    for(int i=0;i<40;i++)  al[i]=(1ll<<i+1)-1;
    n=read();q=read();
    int sum=0;
    for(int i=1;i<=n;i++){sum+=__builtin_popcountll(a[i]=readll());if(a[i]>INT_MAX)lgV=37;}
    for(int i=1;i<=q;i++)   Q[i].fi=read(),Q[i].se=read()+1;
    for(int i=0;i<=lgV;i++){
        cc_hash_table<ll,int>().swap(f);
        f[0]=f[1ll<<i+1]=0;
        ll x=al[i];
        for(int j=1;j<=q;j++)   f[Q[j].fi&x]=f[Q[j].se&x]=0;
        for(int j=1;j<=n;j++)   f[(x-(a[j]&x)+1)&x]--;
        f[1ll<<i]+=n;
        vl[i&1]=0;
        for(auto j:f)v[i&1][vl[i&1]++]=j.fi;
        stable_sort(v[i&1],v[i&1]+vl[i&1]);
        vector<int> w;
        ll tag=0,K=al[i-1];
        mems(ps0,0);mems(ps1,0);
        for(int j=0,lst=-1;j+1<vl[i&1];j++){
            tag+=f[v[i&1][j]];F[i&1][j]=f[v[i&1][j]]=tag;
            if((v[i&1][j]&K)<lst)   mems(ps0,0),mems(ps1,0);
            w.eb((i?query(i-1,v[i&1][j]&K,((v[i&1][j+1]-1)&K)+1):0)+tag);
            lst=((v[i&1][j+1]-1)&K)+1;
            // if((v[i&1][j]&K)>=((v[i&1][j+1]-1)&K)+1)mems(ps0,0),debug("clear\n");
        }
        st[i&1].build(w);
        sum-=f[0];
    }
    for(int i=1;i<=q;i++)   print(sum+qry(lgV,Q[i].fi,Q[i].se),'\n');
    Flush();
}
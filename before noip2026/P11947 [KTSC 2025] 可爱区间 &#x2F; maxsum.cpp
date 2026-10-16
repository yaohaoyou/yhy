#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2.5e5+10;
int n,q;
int a[maxn],b[maxn];
ll pre[maxn],suf[maxn],s[maxn],f[maxn],p[maxn];
bool isL[maxn],isR[maxn];
ll ans[maxn];
vector<piii> v[maxn];
struct ques{
    int l1,r1,l2,r2,id;
    ques(int _l1=0,int _r1=0,int _l2=0,int _r2=0,int _id=0){l1=_l1;r1=_r1;l2=_l2;r2=_r2;id=_id;}
};
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(ll x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(ll x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int m;
    ll tr[maxn<<2];int tag[maxn<<2],len[maxn<<2];
    inline void pt(int p,int s){tr[p]+=1ll*s*len[p];tag[p]+=s;}
    #define pd(p) if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;
    void build(setpos){tr[p]=tag[p]=0;if(l==r)return len[p]=1,void();setmid;build(lson);build(rson);len[p]=len[ls]+len[rs];}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s),void();pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);tr[p]=tr[ls]+tr[rs];}
    ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid;ll ul=0;if(pl<=mid)ul=query(lson,pl,pr);if(pr>mid)ul+=query(rson,pl,pr);return ul;}
}
using namespace SegmentTree;
unordered_map<int,ll> mp[maxn];
void dvd1(int l,int r){
    if(l==r){
        mp[l][r]=(isL[l]&&isR[r]&&b[l]>=max(pre[l-1],suf[r+1]));
        return;
    }
    int md=(l+r)>>1;ll sum;
    sum=f[md]=p[md]=b[md];
    for(int i=md-1;i>=l;i--)    sum=max(sum,0ll)+b[i],f[i]=max(f[i+1],sum),p[i]=max(p[i+1],s[md]-s[i-1]);
    sum=f[md+1]=p[md+1]=b[md+1];
    for(int i=md+2;i<=r;i++)    sum=max(sum,0ll)+b[i],f[i]=max(f[i-1],sum),p[i]=max(p[i-1],s[i]-s[md]);
    vector<int> vec;vec.clear();
    for(int i=md+1,lst=md;i<=r;i++)if(isR[i]){
        if(s[i]>=s[lst])   lst=i,vec.eb(i);
    }
    if(!vec.empty()){m=vec.size();build(all);}
    vector<ques> vl,vr;
    int l1=l,r1=md,l2=md+1,r2=r;
    if(!vec.empty()){
        l2=lower_bound(vec.begin(),vec.end(),l2)-vec.begin()+1;
        r2=upper_bound(vec.begin(),vec.end(),r2)-vec.begin();
        if(l2>=1&&l2<=vec.size()&&r2>=1&&r2<=vec.size()&&l2<=r2){
            if(l1^l)    v[l1-1].eb(pii(l2,r2),-1);
            v[r1].eb(pii(l2,r2),1);
        }
    }
    for(int i=l;i<=md;i++){
        if(isL[i]&&s[md]>=max(0ll,p[i])+s[i-1]){
            int L=0,R=vec.size()-1,ul=-1;
            while(L<=R){
                int mid=(L+R)>>1,j=vec[mid];
                if(s[j]-s[i-1]>=max(max(pre[i-1],f[i]),suf[j+1])) ul=mid,R=mid-1;
                else    L=mid+1;
            }
            L=0,R=vec.size()-1;int ur=-1;
            while(L<=R){
                int mid=(L+R)>>1,j=vec[mid];
                if(s[j]-s[i-1]>=f[j]) ur=mid,L=mid+1;
                else    R=mid-1;
            }
            if((~ul)&&(~ur)&&ul<=ur)    upd(all,ul+1,ur+1,1);
        }
        for(auto [t,id]:v[i]){
            if(id<0)    mp[l][r]-=query(all,t.fi,t.se);
            else    mp[l][r]+=query(all,t.fi,t.se);
        }
        if(!v[i].empty())   vector<piii>().swap(v[i]);
    }
    if(l^r){
        dvd1(l,md),dvd1(md+1,r);
        mp[l][r]+=mp[l][md];mp[l][r]+=mp[md+1][r];
    }
}
void dvd(int l,int r,vector<ques> Q){
    if(Q.empty())   return;
    if(l==r){
        if(isL[l]&&isR[r]&&b[l]>=max(pre[l-1],suf[r+1])){
            for(auto i:Q)   ans[i.id]++;
        }
        return;
    }
    int md=(l+r)>>1;ll sum;
    sum=f[md]=p[md]=b[md];
    for(int i=md-1;i>=l;i--)    sum=max(sum,0ll)+b[i],f[i]=max(f[i+1],sum),p[i]=max(p[i+1],s[md]-s[i-1]);
    sum=f[md+1]=p[md+1]=b[md+1];
    for(int i=md+2;i<=r;i++)    sum=max(sum,0ll)+b[i],f[i]=max(f[i-1],sum),p[i]=max(p[i-1],s[i]-s[md]);
    vector<int> vec;vec.clear();
    for(int i=md+1,lst=md;i<=r;i++)if(isR[i]){
        if(s[i]>=s[lst])   lst=i,vec.eb(i);
    }
    if(!vec.empty()){m=vec.size();build(all);}
    vector<ques> vl,vr;
    for(auto [l1,r1,l2,r2,id]:Q){
        if(r2<=md)  vl.eb(l1,r1,l2,r2,id);
        else if(l1>md)  vr.eb(l1,r1,l2,r2,id);
        else{
            if(r1>md)   vr.eb(md+1,r1,max(md+1,l2),r2,id),r1=md;
            if(l2<=md)  vl.eb(l1,r1,l2,md,id),l2=md+1;
            if(!vec.empty()){
                l2=lower_bound(vec.begin(),vec.end(),l2)-vec.begin()+1;
                r2=upper_bound(vec.begin(),vec.end(),r2)-vec.begin();
                if(l2>=1&&l2<=vec.size()&&r2>=1&&r2<=vec.size()&&l2<=r2){
                    if(l1^l)    v[l1-1].eb(pii(l2,r2),-id);
                    v[r1].eb(pii(l2,r2),id);
                }
            }
        }
    }
    if(!vec.empty()){
        for(int i=l;i<=md;i++){
            if(isL[i]&&s[md]>=max(0ll,p[i])+s[i-1]){
                int L=0,R=vec.size()-1,ul=-1;
                while(L<=R){
                    int mid=(L+R)>>1,j=vec[mid];
                    if(s[j]-s[i-1]>=max(max(pre[i-1],f[i]),suf[j+1])) ul=mid,R=mid-1;
                    else    L=mid+1;
                }
                L=0,R=vec.size()-1;int ur=-1;
                while(L<=R){
                    int mid=(L+R)>>1,j=vec[mid];
                    if(s[j]-s[i-1]>=f[j]) ur=mid,L=mid+1;
                    else    R=mid-1;
                }
                if((~ul)&&(~ur)&&ul<=ur)    upd(all,ul+1,ur+1,1);
            }
            for(auto [t,id]:v[i]){
                if(id<0)    ans[-id]-=query(all,t.fi,t.se);
                else    ans[id]+=query(all,t.fi,t.se);
            }
            if(!v[i].empty())   vector<piii>().swap(v[i]);
        }
    }
    if(l^r)dvd(l,md,vl),dvd(md+1,r,vr);
}
vector<pii> w(int l,int r,int pl,int pr){
    if(l>=pl&&r<=pr)    return vector<pii>{pii(l,r)};
    setmid;vector<pii> ul;ul.clear();
    if(pl<=mid)ul=w(l,mid,pl,pr);
    if(pr>mid){
        auto t=w(mid+1,r,pl,pr);
        for(pii i:t)ul.eb(i);
    }
    return ul;
}
bool mem2;
vector<long long> maxsum(vector<int> A, vector<int> B, 
                         vector<int> L1, vector<int> R1,  
                         vector<int> L2, vector<int> R2){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=A.size();q=L1.size();
    for(int i=1;i<=n;i++)   a[i]=A[i-1],b[i]=B[i-1],s[i]=s[i-1]+b[i];
    pre[0]=suf[n+1]=-1e18;
    ll sum=0;
    for(int i=1;i<=n;i++){
        isL[i]=sum<=0;
        sum=max(sum,0ll)+a[i];
        pre[i]=max(pre[i-1],sum);
    }
    sum=0;
    for(int i=n;i;i--){
        isR[i]=sum<=0;
        sum=max(sum,0ll)+a[i];
        suf[i]=max(suf[i+1],sum);
    }
    dvd1(1,n);
    vector<ques> Q;
    for(int i=1;i<=q;i++){
        int l1=L1[i-1]+1,r1=R1[i-1]+1,l2=L2[i-1]+1,r2=R2[i-1]+1;
        gmn(r1,r2);gmx(l2,l1);
        if(l1>r2)   continue;
        if(r1>=l2){
            vector<pii> v=w(1,n,l2,r1);
            for(auto [l,r]:v){
                ans[i]+=mp[l][r];
                if(r^r1)    Q.eb(l,r,r+1,r1,i);
            }
            if(r1<r2)   Q.eb(l2,r1,r1+1,r2,i);
            if(l1<l2)   Q.eb(l1,l2-1,l2,r2,i);
        }
        else    Q.eb(l1,r1,l2,r2,i);
    }
    dvd(1,n,Q);
    vector<ll> ret;
    for(int i=1;i<=q;i++)   ret.eb(ans[i]);
    return ret;
}
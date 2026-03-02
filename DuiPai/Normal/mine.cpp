#include<set>
#include<map>
#include<queue>
#include<ctime>
#include<cstdio>
#include<vector>
#include<cassert>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
#define ep emplace
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char ch=getchar();int f=1,x=0;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=8e5+10,mod=998244353;
int n,q;
char S[N];
struct SGT{
    int L[N],R[N],s[N],mn[N],p[N],v[N],len[N],lim[N];pii h[N];
    pii mg(pii a,pii b){
        return {a.fi+max(0,b.fi-a.se),b.se+max(0,a.se-b.fi)};
    }
    #define ls (x<<1)
    #define rs (x<<1|1)
    int find(int x,int k){
        if(L[x]==R[x]) return L[x];
        if(mn[ls]+k<0) return find(ls,k);
        return find(rs,k+s[ls]);
    }
    void pu(int x){
        h[x]=mg(h[ls],h[rs]);
        s[x]=s[ls]+s[rs];
        mn[x]=min(mn[ls],mn[rs]+s[ls]);
        p[x]=(mn[x]==mn[rs]+s[ls]?p[rs]:p[ls]);
        v[x]=max(v[ls],v[rs]);
        if(mn[rs]+lim[ls]==0) v[x]=max(v[x],len[ls]+p[rs]-L[rs]+1);
        if(mn[rs]+lim[ls]>=0){
            lim[x]=lim[ls]+s[rs];
            len[x]=len[ls]+R[rs]-L[rs]+1;
        }
        else{
            v[x]=max(v[x],len[ls]+find(rs,lim[ls])-L[rs]);
            lim[x]=lim[rs],len[x]=len[rs];
        }
    }
    void bd(int l=1,int r=n,int x=1){
        L[x]=l,R[x]=r;
        if(l==r){
            int t=S[l]==')'?-1:1;
            s[x]=mn[x]=t;p[x]=l;
            if(t==-1){
                lim[x]=len[x]=0;
                h[x]={1,0};
            }
            else{
                lim[x]=len[x]=1;
                h[x]={0,1};
            }
            return;
        }
        int m=l+r>>1;
        bd(l,m,ls);bd(m+1,r,rs);pu(x);
    }
    vector<int> vt;
    void get(int l,int r,int x=1){
        if(L[x]>r||R[x]<l) return;
        if(l<=L[x]&&R[x]<=r){vt.eb(x);return;}
        get(l,r,ls);get(l,r,rs);
    }
    int qry(int l,int r){
        int mx=0;
        vt.clear();get(l,r);
        pii H={0,0};
        int lm=0,ln=0;
        for(int x:vt){
            H=mg(H,h[x]);
            mx=max(mx,v[x]);
            if(lm+mn[x]==0) mx=max(mx,ln+p[x]-L[x]+1);
            if(lm+mn[x]>=0){
                lm+=s[x];
                ln+=R[x]-L[x]+1;
            }
            else{
                mx=max(mx,ln+find(x,lm)-L[x]);
                lm=lim[x],ln=len[x];
            }
        }
        if(H.fi==H.se) return -1;
        for(int x:vt){
            H=mg(H,h[x]);
            mx=max(mx,v[x]);
            if(lm+mn[x]==0) mx=max(mx,ln+p[x]-L[x]+1);
            if(lm+mn[x]>=0){
                lm+=s[x];
                ln+=R[x]-L[x]+1;
            }
            else{
                mx=max(mx,ln+find(x,lm)-L[x]);
                lm=lim[x],ln=len[x];
            }
        }
        return mx;
    }
}t1,t2;
void misaka(int _ID){
    n=read(),q=read();
    scanf("%s",S+1);
    t1.bd();
    reverse(S+1,S+n+1);
    rep(i,1,n) S[i]=S[i]==')'?'(':')';
    t2.bd();
    while(q--){
        int l=read(),r=read();
        printf("%d\n",max(t1.qry(l,r),t2.qry(n-r+1,n-l+1)));
    }
}
bool __ed;
signed main(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    rep(i,1,T) misaka(i);
    return 0;
}

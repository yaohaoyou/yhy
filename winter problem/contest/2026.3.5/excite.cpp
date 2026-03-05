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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e5+10;
int n,q;
pii a[maxn];
int b[maxn],fa[17][maxn],dep[maxn];
int L[maxn],R[maxn],nx[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char ch){if(!x)return putc(48),putc(ch),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(ch);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
namespace SG2{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,lc[q],l,mid
    #define rson rs,rc[q],mid+1,r
    #define setmid int mid=(l+r)>>1
    #define setpos int &p,int q,int l,int r
    const int maxp=maxn*25;
    int tot;
    int root[maxn],tr[maxp],lc[maxp],rc[maxp];
    void upd(setpos,int x){
        p=++tot;tr[p]=tr[q]+1;
        if(l==r)    return;
        ls=lc[q];rs=rc[q];
        setmid;(x<=mid)?upd(lson,x):upd(rson,x);
    }
    int binaryL(setpos,int x){
        if(tr[p]==tr[q])    return 0;
        if(l==r)    return l;
        setmid;
        if(x<=mid)  return binaryL(lson,x);
        int res=binaryL(rson,x);
        if(res)return res;
        return binaryL(lson,x);
    }
    int binaryR(setpos,int x){
        if(tr[p]==tr[q])    return 0;
        if(l==r)    return l;
        setmid;
        if(x>mid)  return binaryR(rson,x);
        int res=binaryR(lson,x);
        if(res)return res;
        return binaryR(rson,x);
    }
    #undef ls
    #undef rs
    #undef lson
    #undef rson
    #undef setpos
}
using namespace SG2;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,q
    #define setpos int p,int l,int r
    // fr[p] 表示跳出 [l,r] 的最小起点，to[p] 表示跳到的位置（即 max[l,r]）,mx[p] 表示离开区间时的最大贡献
    int fr[maxn<<2],to[maxn<<2],mx[maxn<<2],pos[maxn];
    inline void pu(int p){
        to[p]=max(to[ls],to[rs]);
        fr[p]=to[ls]>=fr[rs]?fr[ls]:fr[rs];
        if(to[ls]>=fr[rs]&&to[ls]<=mx[rs])  mx[p]=mx[rs];
        else if(to[ls]>=fr[rs]) mx[p]=mx[ls];
        else    mx[p]=mx[rs];
    }
    void build(setpos){
        if(l==r){
            fr[p]=(b[l]<=l?l+1:l);
            if(a[l].se)mx[p]=l;to[p]=b[l];
            pos[l]=p;
            return;
        }
        setmid;build(lson);build(rson);pu(p);
    }
    inline void upd(int x,bool flag){
        int p=pos[x];
        fr[p]=b[x]<=x?x+1:x;
        if(flag)mx[p]=nx[x]-1;to[p]=b[x];
        while(p>>=1)pu(p);
    }
    pii jump(setpos,int x,int now){
        if(l==r)    return pii(max(to[p],now),now<=mx[p]?mx[p]:0);
        setmid;
        if(l>x){
            if(now>=fr[p])    return pii(max(now,to[p]),now<=mx[p]?mx[p]:0);
            if(now>=fr[ls]){pii res=jump(rson,x,max(now,to[ls]));if(now<=mx[ls])gmx(res.se,mx[ls]);return res;}
            return jump(lson,x,now);
        }
        if(x>mid)return jump(rson,x,now);
        pii tp=jump(lson,x,now);
        if(tp.fi<=mid) return tp;
        pii res=jump(rson,x,tp.fi);
        gmx(res.se,tp.se);return res;
    }
}
using namespace SegmentTree;
int cur;
int dL[maxn],dR[maxn],rk[maxn];
void dfs1(int u,int ft){dep[u]=dep[fa[0][u]=ft]+1;rk[dL[u]=++cur]=u;go(u,i)if(t^ft)dfs1(t,u);dR[u]=cur;}
pii s1[maxn],s2[maxn];
vector<int> v[maxn];
vector<pii> I[maxn];
set<int> st;
void dfs(int u,int ft){for(int i:v[u])st.ep(i);go(u,i)if(t^ft){dfs(t,u);}}
inline int jp(int x,int d){while(d){int lb=d&-d;x=fa[__lg(lb)][x];d^=lb;}return x;}
int main(){
    freopen("excite.in","r",stdin);freopen("excite.out","w",stdout);
    n=read();
    for(int i=1;i<n;i++)    adde(read(),read());
    dfs1(1,0);for(int i=1;i<17;i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
    q=read();
    for(int i=1;i<=q;i++){
        char c=getc();while(c!='s'&&c!='b')c=getc();
        a[i].fi=read();
        if(a[i].se=c=='s')   v[a[i].fi].eb(i);
    }
    for(int i=1;i<=n;i++){
        int u=rk[i];
        if(!v[u].empty()){
            upd(root[i],root[i-1],1,q,v[u].front());
            for(int j=1;j<v[u].size();j++)  upd(root[i],root[i],1,q,v[u][j]);
        }
        else root[i]=root[i-1];
    }
    nx[q+1]=q+1;
    for(int i=q;i;i--)  nx[i]=(i<q&&!a[i+1].se)?i+1:nx[i+1];
    int lst=0,nxt=1;
    for(int i=1;i<=q;i++){
        gmx(nxt,i);while(nxt<=q&&!a[nxt].se)nxt++;
        if(a[i].se){lst=i;R[i]=i+1;continue;}
        int LST=lst,NXT=nxt;nxt=a[nxt].fi;lst=a[lst].fi;
        R[i]=s1[i].se=s2[i].se=q+2;
        int u=a[i].fi;
        if(lst&&lst^u){
            s2[i].fi=LST;
            if(dL[lst]>=dL[u]&&dL[lst]<=dR[u]){
                int v=jp(lst,dep[lst]-dep[u]-1);
                if(dL[v]^1){
                    L[i]=binaryL(root[0],root[dL[v]-1],1,q,i);
                    s2[i].se=binaryR(root[0],root[dL[v]-1],1,q,i);
                    (!s2[i].se)&&(s2[i].se=q+2);
                }
                if(dR[v]^n){
                    gmx(L[i],binaryL(root[dR[v]],root[n],1,q,i));
                    gmn(s2[i].se,binaryR(root[dR[v]],root[n],1,q,i));
                }
            }
            else{
                L[i]=binaryL(root[dL[u]],root[dR[u]],1,q,i);
                s2[i].se=binaryR(root[dL[u]],root[dR[u]],1,q,i);
            }
        }
        if(nxt&&nxt^u){
            s1[i].se=NXT;
            if(dL[nxt]>=dL[u]&&dL[nxt]<=dR[u]){
                int v=jp(nxt,dep[nxt]-dep[u]-1);
                if(dL[v]^1){
                    R[i]=binaryR(root[0],root[dL[v]-1],1,q,i);
                    // if(i==4189) debug("R = %d\n",R[i]);
                    (!R[i])&&(R[i]=q+2);
                    gmx(s1[i].fi,binaryL(root[0],root[dL[v]-1],1,q,i));
                }
                if(dR[v]^n){
                    int tmp=binaryR(root[dR[v]],root[n],1,q,i);
                    if(tmp)gmn(R[i],tmp);
                    // debug("brl = %d %d\n",dR[v]+1,n,1,q,i);
                    gmx(s1[i].fi,binaryL(root[dR[v]],root[n],1,q,i));
                }
            }
            else{
                R[i]=binaryR(root[dL[u]],root[dR[u]],1,q,i);
                s1[i].fi=binaryL(root[dL[u]],root[dR[u]],1,q,i);
            }
        }
        (!s2[i].se)&&(s2[i].se=q+2);
        if(s2[i].se>q)  s2[i].fi=0;
        (!s1[i].se)&&(s1[i].se=q+2);
        if(s1[i].se>q)  s1[i].fi=0;
        (!R[i])&&(R[i]=q+2);
        int k=lower_bound(v[u].begin(),v[u].end(),i)-v[u].begin();
        if(k<v[u].size())   gmn(R[i],v[u][k]),gmn(s1[i].se,v[u][k]),gmn(s2[i].se,v[u][k]);
        k--;
        if(k>=0)   gmx(L[i],v[u][k]);
        if(s2[i].fi)    I[s2[i].fi].eb(i,s2[i].se);
        if(s1[i].fi)    I[s1[i].fi].eb(i,s1[i].se);
        if(L[i])    I[L[i]].eb(i,0);
        nxt=NXT;lst=LST;
    }
    for(int i=1;i<=q;i++)   b[i]=R[i];
    build(all);
    vector<int> ans;
    for(int i=q;i;i--){
        for(auto [p,k]:I[i]){
            gmn(b[p],k?k:nx[p]);
            upd(p,!k);
        }
        pii jp=jump(all,i,i);
        int r=a[i].se?nx[i]-1:i-1;
        gmx(r,jp.se);ans.eb(r-i+1);
    }
    reverse(ans.begin(),ans.end());
    for(int i:ans)  print(i,'\n');flush();
}
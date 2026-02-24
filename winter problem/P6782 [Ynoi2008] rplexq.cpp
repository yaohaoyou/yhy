#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,BB=100,B=450,Block=maxn/B+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
int n,q,rt;
vector<int> son[maxn];
inline void add(int u,int v){son[u].eb(v);}
inline void adde(int u,int v){add(u,v);add(v,u);}
struct ques{int l,r,id;};
vector<ques> Q[maxn],vq[maxn];
int qx[maxn],en[maxn],sum[maxn],lst[maxn];
int tot;
int dfsn[maxn],siz[maxn],rnk[maxn];
ll ans[maxn];
inline ll C2(int x){return 1ll*x*(x-1)/2;}
int id[maxn],bl[Block],br[Block];
struct Block_array{
    int pre[maxn],sum[Block];
    inline void upd(int x,int s){
        int idx=id[x];
        for(int i=x;i<=br[idx];i++) pre[i]++;
        for(int i=idx;i<=id[n];i++) sum[i]=sum[i-1]+pre[br[i]];
    }
    inline int query(int x){return pre[x]+sum[id[x]-1];}
}DS1;
struct Block_array2{
    int a[maxn],sum[Block];
    inline void upd(int x,int s){a[x]+=s;sum[id[x]]+=s;}
    inline int query(int x){
        if(id[x]<=1)    return accumulate(a+1,a+x+1,0);
        int idx=id[x],res=0;
        while(id[x]==idx)   res+=a[x--];
        for(int i=1;i<idx;i++)  res+=sum[i];
        return res;
    }
    void clear(){mems(a,0);mems(sum,0);}
}DS2;
void dfs(int u,int ft){
    for(int t:son[u])if(t^ft)dfs(t,u);
    siz[u]=1;
    for(int t:son[u])if(t^ft)siz[u]+=siz[t];
    sort(son[u].begin(),son[u].end(),[&](int x,int y){return siz[x]>siz[y];});
    if(ft)  son[u].pop_back();
}
void dfs1(int u){dfsn[u]=++tot;rnk[tot]=u;for(int t:son[u])dfs1(t);}
int pos[maxn],pr[maxn];
int vec[maxn],tmp[maxn];
int vl,vt;
void dfs2(int u){
    if(!son[u].empty()&&!Q[u].empty()){
        int t=son[u][0],l=dfsn[t],r=dfsn[t]+siz[t]-1;
        for(auto [ql,qr,id]:Q[u])   vq[l-1].eb((ques){ql,qr,-id}),vq[r].eb((ques){ql,qr,id});
        t=son[u][min(BB,(int)son[u].size())-1];l=dfsn[u];r=dfsn[t]+siz[t]-1;
        for(auto [ql,qr,id]:Q[u])   en[id]=r,sum[id]=ql<=u&&u<=qr;
    }
    if(son[u].size()>BB&&!Q[u].empty()){
        vl=0;
        sort(Q[u].begin(),Q[u].end(),[&](ques x,ques y){return x.r<y.r;});
        for(int _=BB;_<son[u].size();_++){
            vt=0;
            int t=son[u][_];
            for(int i=dfsn[t];i<=dfsn[t]+siz[t]-1;i++)  tmp[++vt]=rnk[i],vec[++vl]=rnk[i];
            sort(tmp+1,tmp+vt+1);
            int lst=0;for(int i=1;i<=vt;i++)  pr[tmp[i]]=lst,lst=tmp[i];
        }
        sort(vec+1,vec+vl+1);
        DS2.clear();
        int ss=0;
        for(int i=0,j=1;i<Q[u].size();i++){
            while(j<=vl&&vec[j]<=Q[u][i].r){
                for(int k=pr[vec[j]];k;k=pr[k])DS2.upd(k,1),ss++;
                j++;
            }
            ans[Q[u][i].id]-=ss-DS2.query(Q[u][i].l-1);
        }
    }
    for(int t:son[u])dfs2(t);
}
int main(){
    n=read();q=read();rt=read();
    for(int i=1;i<n;i++)    adde(read(),read());
    for(int i=1;i<=q;i++){int l=read(),r=read(),x=read();Q[x].eb((ques){l,r,i});qx[i]=x;}
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,n);
    dfs(rt,0);dfs1(rt);dfs2(rt);
    for(int i=1;i<=n;i++){
        DS1.upd(rnk[i],1);
        for(auto [l,r,id]:vq[i]){
            int res=DS1.query(r)-DS1.query(l-1);
            if(id<0)    sum[-id]-=res,lst[-id]=res;
            else if(id>q)    sum[id-q]+=res,ans[id-q]+=C2(sum[id-q]);
            else{
                ans[id]-=C2(res-lst[id]);lst[id]=res;
                if(en[id]^i)    vq[i+1+siz[rnk[i+1]]-1].eb((ques){l,r,id});
                else{
                    int x=qx[id];
                    if(dfsn[x]+siz[x]-1==i) sum[id]+=res,ans[id]+=C2(sum[id]);
                    else    vq[dfsn[x]+siz[x]-1].eb((ques){l,r,id+q});
                }
            }
        }
        vector<ques>().swap(vq[i]);
    }
    for(int i=1;i<=q;i++)   print(ans[i]),putc('\n');flush();
}
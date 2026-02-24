#pragma GCC optimize(2,3,"Ofast")
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
const int maxn=1e6+10;
int n,k,mod;
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
int deg[maxn];
vector<int> son[maxn];
inline void add(int u,int v){son[u].eb(v);deg[v]++;}
inline void adde(int u,int v){add(u,v);add(v,u);}
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
    inline int I(int x){return qpow(x,mod-2);}
}
using namespace FastMod;
int ans;
int dp[maxn][2],siz[maxn],pq[maxn],cc[maxn],tag[maxn],G[maxn],H[maxn],M[maxn],c[maxn];
int fac[maxn],inv[maxn];
vector<int> f[maxn];
void init(){
    fac[0]=1;for(int i=1;i<=n;i++)   fac[i]=immul(fac[i-1],i);
    inv[n]=qpow(fac[n],mod-2);
    for(int i=n-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void dfs1(int u,int ft){
    siz[u]=1;
    if(deg[u]>=k){
        f[u].resize(k);vector<int> g(k);
        for(int i=0;i<k;i++)f[u][i]=0;f[u][0]=1;
        bool flag=true;tag[u]=1;c[u]=0;
        for(int t:son[u]){
            if(t==ft)   continue;
            dfs1(t,u);
            siz[u]+=siz[t];
            if(deg[t]>=k){
                assert(flag);
                g.swap(f[u]);for(int i=0;i<k;i++)f[u][i]=0;
                for(int i=0;i<k;i++){
                    madd(f[u][i],immul(g[i],dp[t][0]));
                    if(i+1<k)madd(f[u][i+1],immul(g[i],dp[t][1]));
                }
            }
            else{
                flag=false;
                mmul(tag[u],dp[t][0]);c[u]++;
                // for(int i=k-1;~i;i--)   mmul(f[u][i],dp[t][0]);
                // for(int i=k-1;~i;i--)   f[u][i]=imadd(f[u][i],i?f[u][i-1]:0);
            }
        }
        {
            cc[0]=1;for(int i=1;i<=k;i++)    cc[i]=imadd(cc[i-1],C(c[u],i));
            G[u]=0;for(int i=0;i<k;i++)    madd(G[u],immul(f[u][i],cc[k-i-1]));
        }
        dp[u][0]=immul(G[u],tag[u]);
        if(c[u]){
            c[u]--;
            cc[0]=1;for(int i=1;i<=k;i++)   cc[i]=imadd(cc[i-1],C(c[u],i));
            H[u]=0;for(int i=0;i<k;i++)    madd(H[u],immul(f[u][i],cc[k-i-1]));
            c[u]++;
        }
        {
            c[u]++;
            cc[0]=1;for(int i=1;i<=k;i++)   cc[i]=imadd(cc[i-1],C(c[u],i));
            M[u]=0;for(int i=0;i<k;i++)    madd(M[u],immul(f[u][i],cc[k-i-1]));
            c[u]--;
        }
        // for(int i=0;i<k;i++)    mmul(f[u][i],tag[u]);
        // for(int i=k-1;~i;i--){
        //     int s=0;
        //     for(int j=0;j<=c&&j<=i;j++)   madd(s,immul(C(c,j),f[u][i-j]));
        //     f[u][i]=s;
        // }
        dp[u][1]=imdel(pq[siz[u]],dp[u][0]);
    }
    else{
        for(int t:son[u])if(t^ft)dfs1(t,u),siz[u]+=siz[t];
        dp[u][0]=dp[u][1]=pq[siz[u]-1];
    }
}
void dfs2(int u,int ft){
    if(deg[u]>=k){
        vector<int> g(k);
        if(ft){
            // printf("%d %d\n",dp[ft][0],dp[ft][1]);
            if(deg[ft]>=k){
                g.swap(f[u]);for(int i=0;i<k;i++)f[u][i]=0;
                for(int i=0;i<k;i++){
                    madd(f[u][i],immul(g[i],dp[ft][0]));
                    if(i+1<k)madd(f[u][i+1],immul(g[i],dp[ft][1]));
                }
                {
                    cc[0]=1;for(int i=1;i<=k;i++)    cc[i]=imadd(cc[i-1],C(c[u],i));
                    G[u]=0;for(int i=0;i<k;i++)    madd(G[u],immul(f[u][i],cc[k-i-1]));
                }
                dp[u][0]=immul(G[u],tag[u]);
                if(c[u]){
                    c[u]--;
                    cc[0]=1;for(int i=1;i<=k;i++)   cc[i]=imadd(cc[i-1],C(c[u],i));
                    H[u]=0;for(int i=0;i<k;i++)    madd(H[u],immul(f[u][i],cc[k-i-1]));
                    c[u]++;
                }
                {
                    c[u]++;
                    cc[0]=1;for(int i=1;i<=k;i++)   cc[i]=imadd(cc[i-1],C(c[u],i));
                    M[u]=0;for(int i=0;i<k;i++)    madd(M[u],immul(f[u][i],cc[k-i-1]));
                    c[u]--;
                }
            }
            else{
                mdel(dp[u][0],immul(G[u],tag[u]));
                mmul(tag[u],dp[ft][0]);c[u]++;H[u]=G[u];G[u]=M[u];
                madd(dp[u][0],immul(G[u],tag[u]));
            }
            dp[u][1]=imdel(pq[n],dp[u][0]);
        }
        // printf("%d : %d %d\n",u,dp[u][0],dp[u][1]);
        madd(ans,dp[u][1]);
        vector<int> F=f[u];
        for(int t:son[u]){
            if(t==ft)   continue;
            int du0=dp[u][0],du1=dp[u][1];
            if(deg[t]>=k){
                f[u]=F;
                for(int i=0;i<k;i++)   f[u][i]=immul(imdel(f[u][i],i?immul(f[u][i-1],dp[t][1]):0),I(dp[t][0]));
                cc[0]=1;for(int i=1;i<=k;i++)cc[i]=imadd(cc[i-1],C(c[u],i));
                int gu=0;
                for(int i=0;i<k;i++)    madd(gu,immul(f[u][i],cc[k-i-1]));
                dp[u][0]=immul(gu,tag[u]);
            }
            else{
                mdel(dp[u][0],immul(G[u],tag[u]));
                // printf("%d %d : %d %d\n",u,t,H[u],immul(tag[u],I(dp[t][0])));
                madd(dp[u][0],immul(H[u],immul(tag[u],I(dp[t][0]))));
            }
            dp[u][1]=imdel(pq[n-siz[t]],dp[u][0]);
            dfs2(t,u);
            dp[u][0]=du0;dp[u][1]=du1;
        }
    }
    else{
        dp[u][0]=dp[u][1]=pq[n-1];
        madd(ans,dp[u][1]);
        // printf("%d : %d %d\n",u,dp[u][0],dp[u][1]);
        for(int t:son[u])if(t^ft)dp[u][0]=dp[u][1]=pq[n-1-siz[t]],dfs2(t,u);
    }
}
int main(){
    n=read();k=read();mod=read();
    init();
    for(int i=1;i<n;i++)    adde(read(),read());
    for(int i=1;i<=n;i++)   sort(son[i].begin(),son[i].end(),[&](int x,int y){return deg[x]>deg[y];});
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    dfs1(1,0);dfs2(1,0);
    // for(int i=1;i<=n;i++){
    //     dfs1(i,0);madd(ans,dp[i][1]);
    // }
    printf("%d\n",ans);
}
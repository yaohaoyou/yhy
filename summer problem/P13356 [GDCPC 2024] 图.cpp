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
const int maxn=1e5+10,maxm=2e5+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
int n,m,k;
pii E[maxm];
struct DSU{
    vector<int> fa;
    void init(){fa.resize(n+1);for(int i=1;i<=n;i++)fa[i]=i;}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
};
vector<DSU> U;
vector<vector<int>> son[maxn];
vector<int> vec;
int cnt=0;
bool dfs(int u,int ft,int en,int o){
    cnt++;assert(cnt<=n);
    vec.eb(u);
    if(u==en){
        print(vec.size());putc(' ');
        for(int i:vec)    print(i),putc(' ');putc('\n');
        vec.clear();return true;
    }
    for(int t:son[u][o]){
        if(t==ft)   continue;
        if(dfs(t,u,en,o))return true;
    }
    vec.pop_back();
    return false;
}
void matt(){
    vector<DSU>().swap(U);
    for(int i=1;i<=n;i++)vector<vector<int>>().swap(son[i]);
    n=read();m=read();
    k=(m+n-2)/(n-1);
    for(int i=1;i<=m;i++){int u=read(),v=read();E[i]=pii(u,v);}
    U.resize(k+1);
    for(int i=1;i<=k;i++)   U[i].init();
    for(int i=1;i<=n;i++)   son[i].resize(k+1);
    for(int i=1;i<=m;i++){
        auto [u,v]=E[i];
        int l=1,r=k,p=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(U[mid].find(u)!=U[mid].find(v))  p=mid,r=mid-1;
            else    l=mid+1;
        }
        if(!p)  break;
        U[p].merge(u,v);
        son[u][p].eb(v);
        son[v][p].eb(u);
    }
    for(int o=1;o<=m;o++){
        auto [u,v]=E[o];
        if(U[k].find(u)==U[k].find(v)){
            print(u);putc(' ');print(v);putc('\n');
            for(int i=1;i<=k;i++)   vec.clear(),cnt=0,assert(dfs(u,0,v,i));
            return;
        }
    }
}
int main(){int T=read();while(T--)matt();flush();}
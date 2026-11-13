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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e5+10,maxm=maxn*12;
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
int n,q,tot;
char a[maxn][12];
int id[maxn][12],en[maxm];
int len[maxn];
int siz[maxm];
struct DSU{
    int l,r;
    int fa[maxm];
    void init(){iota(fa+1,fa+tot+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){
        x=find(x);y=find(y);
        if(x^y){
            if(x>=l&&x<=r)swap(x,y);
            fa[x]=y;siz[y]+=siz[x];
        }
    }
    inline int operator[](int x){return find(x);}
}U;
int _c;
int ans[maxn];
vector<piii> Q[30][maxn];
int f[maxn][12],s[maxn][12],bel[2][12],mx[maxn];
void dvd(int l,int r,int d){
    if(l>r) return;
    int mid=(l+r)>>1;
    if(!Q[d][mid].empty()){
        // mems(f,0);mems(s,0);mems(bel,0);mems(mx,0);
        U.l=id[mid][0];U.r=id[mid][len[mid]-1];
        for(int i=l;i<=r;i++)   mems(s[i],0),mems(f[i],0);
        for(int i=l;i<=mid;i++)for(int j=0;j<len[i];j++)U.fa[id[i][j]]=id[i][j],siz[id[i][j]]=(a[i][j]=='0');
        for(int i=1;i<len[mid];i++)if(a[mid][i]=='0'&&a[mid][i-1]=='0')U.merge(id[mid][i],id[mid][i-1]);
        mx[mid]=0;for(int i=0;i<len[mid];i++){
            if(U[id[mid][i]]==id[mid][i])gmx(mx[mid],f[mid][i]=siz[id[mid][i]]);
            s[mid][en[U[id[mid][i]]]]|=1<<i;
        }
        for(int i=mid-1;i>=l;i--){
            for(int j=1;j<len[i];j++)if(a[i][j]=='0'&&a[i][j-1]=='0')U.merge(id[i][j],id[i][j-1]);
            for(int j=0;j<min(len[i],len[i+1]);j++)if(a[i][j]=='0'&&a[i+1][j]=='0')U.merge(id[i][j],id[i+1][j]);
            for(int j=0;j<len[mid];j++){
                if(U[id[mid][j]]==id[mid][j])   f[i][j]=siz[id[mid][j]];
                s[i][en[U[id[mid][j]]]]|=1<<j;
            }
            mx[i]=mx[i+1];for(int j=0;j<len[i];j++)gmx(mx[i],siz[U[id[i][j]]]);
        }

        if(mid+1<=r){
        U.l=id[mid+1][0];U.r=id[mid+1][len[mid+1]-1];
        for(int i=mid+1;i<=r;i++)for(int j=0;j<len[i];j++)U.fa[id[i][j]]=id[i][j],siz[id[i][j]]=(a[i][j]=='0');
        for(int i=1;i<len[mid+1];i++)if(a[mid+1][i]=='0'&&a[mid+1][i-1]=='0')U.merge(id[mid+1][i],id[mid+1][i-1]);
        mx[mid+1]=0;for(int i=0;i<len[mid+1];i++){
            if(U[id[mid+1][i]]==id[mid+1][i])gmx(mx[mid+1],f[mid+1][i]=siz[id[mid+1][i]]);
            s[mid+1][en[U[id[mid+1][i]]]]|=1<<i;
        }
        for(int i=mid+2;i<=r;i++){
            for(int j=1;j<len[i];j++)if(a[i][j]=='0'&&a[i][j-1]=='0')U.merge(id[i][j],id[i][j-1]);
            for(int j=0;j<min(len[i],len[i-1]);j++)if(a[i][j]=='0'&&a[i-1][j]=='0')U.merge(id[i][j],id[i-1][j]);
            for(int j=0;j<len[mid+1];j++){
                if(U[id[mid+1][j]]==id[mid+1][j])   f[i][j]=siz[id[mid+1][j]];
                s[i][en[U[id[mid+1][j]]]]|=1<<j;
            }
            mx[i]=mx[i-1];for(int j=0;j<len[i];j++)gmx(mx[i],siz[U[id[i][j]]]);
        }
        }
        queue<pii> q;while(!q.empty())q.pop();
        for(auto [t,id]:Q[d][mid]){
            if(t.se==mid)   ans[id]=mx[t.fi];
            else{
                ans[id]=max(mx[t.fi],mx[t.se]);
                for(int i=0;i<len[mid];i++)if(a[mid][i]=='0'){
                    int st=s[t.fi][i];
                    while(st){
                        int x=__builtin_ctz(st);
                        bel[0][x]=i;
                        st^=(1<<x);
                    }
                }
                for(int i=0;i<len[mid+1];i++)if(a[mid+1][i]=='0'){
                    int st=s[t.se][i];
                    while(st){
                        int x=__builtin_ctz(st);
                        bel[1][x]=i;
                        st^=(1<<x);
                    }
                }
                int bl[2]={0,0};
                for(int i=0;i<len[mid];i++)if(a[mid][i]=='0'&&bel[0][i]==i&&!(bl[0]&(1<<i))){
                    int w=0;
                    {
                        int st=s[t.fi][i];
                        while(st){
                            int x=__builtin_ctz(st);
                            if(!(bl[0]&(1<<x))){
                                bl[0]|=1<<x;
                                q.ep(x,0);
                            }
                            st^=(1<<x);
                        }
                    }
                    while(!q.empty()){
                        int u=q.front().fi,o=q.front().se;q.pop();
                        if(!o)  w+=f[t.fi][u];
                        else    w+=f[t.se][u];
                        if(u<len[mid]&&a[mid][u]=='0'&&o&&!(bl[0]&(1<<bel[0][u]))){
                            int st=s[t.fi][bel[0][u]];
                            while(st){
                                int x=__builtin_ctz(st);
                                if(!(bl[0]&(1<<x))){
                                    bl[0]|=1<<x;
                                    q.ep(x,0);
                                }
                                st^=(1<<x);
                            }
                        }
                        if(u<len[mid+1]&&a[mid+1][u]=='0'&&!o&&!(bl[1]&(1<<bel[1][u]))){
                            int st=s[t.se][bel[1][u]];
                            while(st){
                                int x=__builtin_ctz(st);
                                if(!(bl[1]&(1<<x))){
                                    bl[1]|=1<<x;
                                    q.ep(x,1);
                                }
                                st^=(1<<x);
                            }
                        }
                    }
                    gmx(ans[id],w);
                }
            }
        }
        Q[d][mid].clear();
    }
    dvd(l,mid-1,d+1);dvd(mid+1,r,d+1);
}
void query(int l,int r,int d,int ql,int qr,int id){
    // if(l>r) assert(0);
    int mid=(l+r)>>1;
    if(ql<=mid&&qr>=mid)    return Q[d][mid].eb(pii(ql,qr),id),void();
    if(qr<mid)  return query(l,mid-1,d+1,ql,qr,id);
    return query(mid+1,r,d+1,ql,qr,id);
}
bool mem2;
void matt(int _cases){
    _c=_cases;
    tot=0;
    n=read();q=read();
    for(int i=1;i<=n;i++){
        len[i]=0;char c=getc();while(!isdigit(c))c=getc();
        while(isdigit(c))a[i][len[i]++]=c,c=getc();
        for(int j=0;j<len[i];j++)   id[i][j]=++tot,en[tot]=j;
    }
    for(int i=1;i<=q;i++){int l=read(),r=read();query(1,n,0,l,r,i);}
    U.init();
    dvd(1,n,0);
    for(int i=1;i<=q;i++)   print(ans[i],'\n');
}
int main(){freopen("data.in","r",stdin);freopen("data.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);Flush();}
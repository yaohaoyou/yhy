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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e5+10;
bool mem1;
int n,m,k;
char a[maxn],b[maxn],c[maxn];
int nx[maxn],ex[2][maxn],d[maxn];
struct List{
    int pre[maxn],nxt[maxn],siz;
    void init(){nxt[0]=m+1;pre[m+1]=0;siz=0;}
    inline void eb(int x){int y=pre[m+1];nxt[y]=x;pre[x]=y;nxt[x]=m+1;pre[m+1]=x;siz++;}
    inline void erase(int x){int pr=pre[x],nx=nxt[x];pre[nx]=pr;nxt[pr]=nx;siz--;}
    inline int hd(){return nxt[0];}
    inline int bck(){return pre[m+1];}
    inline int nx(int x){return nxt[x];}
    inline int pr(int x){return pre[x];}
    inline bool empty(){return nxt[0]==m+1;}
}ls;
vector<int> v[maxn];
int vec[maxn];
bool mem2;
void matt(int _cases){
    fll(d,0,max({n,m,k})+5);fll(vec,0,max({n,m,k})+5);
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s%s%s",a+1,b+1,c+1);
    int p,r=0;
    for(int i=2;i<=n;i++){
        if(i<=r)    nx[i]=min(r-i+1,nx[i-p+1]);
        else    nx[i]=0;
        while(i+nx[i]<=n&&a[i+nx[i]]==a[1+nx[i]])nx[i]++;
        if(i+nx[i]-1>r) r=i+nx[i]-1,p=i;
    }
    r=0;
    ls.init();
    for(int i=1;i<=m;i++){
        if(i<=r)    ex[0][i]=min(r-i+1,nx[i-p+1]);
        else    ex[0][i]=0;
        while(i+ex[0][i]<=m&&ex[0][i]<n&&b[i+ex[0][i]]==a[1+ex[0][i]])ex[0][i]++;
        if(i+ex[0][i]-1>r)  r=i+ex[0][i]-1,p=i;
        if(ex[0][i]){
            if(ls.bck())    vec[i-ls.bck()]++;
            v[ex[0][i]].eb(i),ls.eb(i);
        }
    }
    r=0;
    for(int i=1;i<=k;i++){
        if(i<=r)    ex[1][i]=min(r-i+1,nx[i-p+1]);
        else    ex[1][i]=0;
        while(i+ex[1][i]<=k&&ex[1][i]<n&&c[i+ex[1][i]]==a[1+ex[1][i]])ex[1][i]++;
        if(i+ex[1][i]-1>r)  r=i+ex[1][i]-1,p=i;
        if(ex[1][i])    d[1]++,d[ex[1][i]+1]--;
    }
    int cnt=0,sum=0;
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(ls.empty())  break;
        d[i]+=d[i-1];
        ans+=1ll*d[i]*((ls.siz-cnt)*i+sum);
        // printf("%d %d %d %d\n",d[i],ls.siz,cnt,sum);
        cnt+=vec[i];sum+=1ll*vec[i]*i;vec[i]=0;
        for(int j:v[i]){
            if(ls.nx(j)<=m){
                if(ls.nx(j)-j<=i)  cnt--,sum-=ls.nx(j)-j;
                else vec[ls.nx(j)-j]--;
            }
            if(ls.pr(j)){
                if(j-ls.pr(j)<=i) cnt--,sum-=j-ls.pr(j);
                else vec[j-ls.pr(j)]--;
            }
            ls.erase(j);
            if(ls.nx(j)<=m&&ls.pr(j)){
                int d=ls.nx(j)-ls.pr(j);
                if(d<=i)    cnt++,sum+=d;
                else    vec[d]++;
            }
        }
        v[i].clear();
    }
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1610,maxK=(1<<10)*20+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
bool mem1;
int n,k,K;
char a[maxn];
int pq[maxn];
int f[2][maxK][2];  // f[i][j][0/1] 表示前 i 个位，后 k 个的值为 j，是否顶到的方案数
bool en[maxK];
int tot,nex[maxK][2],fail[maxK];
bool mem2;
void insert(int x){
    int p=0;
    for(int i=k-1;~i;i--){
        bool o=x&(1<<i);int &t=nex[p][o];
        if(!t)  t=++tot;
        p=t;
    }
    en[p]=true;
}
queue<int> q;
void bfs(){
    for(int i:{0,1})if(nex[0][i])q.ep(nex[0][i]);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i:{0,1}){
            if(nex[u][i])   fail[nex[u][i]]=nex[fail[u]][i],q.ep(nex[u][i]);
            else    nex[u][i]=nex[fail[u]][i];
        }
    }
}
bool check(int s){
    for(int i=1,j=k;i<j;i++,j--)if(bool(s&(1<<i-1))^bool(s&(1<<j-1)))return false;
    return true;
}
inline void trans(int i,int j,bool o,bool o1,bool o2){
    if(en[nex[j][o]])   return;
    madd(f[i&1][nex[j][o]][o2],f[(i-1)&1][j][o1]);
}
int main(){
    // freopen("number.in","r",stdin);freopen("number.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%s",&n,&k,a+1);K=(1<<k-1)-1;
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    for(int i=0;i<=(K<<1|1);i++)if(check(i))insert(i);
    bfs();
    f[0][0][1]=1;
    for(int i=1;i<=n;i++){
        mems(f[i&1],0);
        for(int j=0;j<=tot;j++){
            if(a[i]=='0'||a[i]=='?'){
                trans(i,j,0,1,1);
                trans(i,j,0,0,0);
                trans(i,j,1,0,0);
            }
            if(a[i]=='1'||a[i]=='?'){
                trans(i,j,1,1,1);
                trans(i,j,0,1,0);
                trans(i,j,0,0,0);
                trans(i,j,1,0,0);
            }
        }
        // for(int j=0;j<=tot;j++)printf("%d %d\n",f[i&1][j][0],f[i&1][j][1]);puts("");
    }
    int ans=0;
    for(int i=0;i<=tot;i++)madd(ans,f[n&1][i][0]);
    printf("%d\n",ans);
}
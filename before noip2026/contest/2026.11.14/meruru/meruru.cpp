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
bool mem1;
const int maxn=1e5+10,maxm=810,dir[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
int n,m,k;
struct DSU{
    int fa[maxm*maxm];
    void init(){iota(fa+1,fa+n*m+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
unordered_map<char,int> O;
char a[maxn];
int b[maxm][maxm];
bool vis[maxm][maxm];
queue<pii> q;
inline int id(int x,int y){return (x-1)*m+y;}
int cnt[1<<4];
bool chk(int x,int y){
    if(!b[x][y])return 0;
    int sta=0;
    for(int i=0;i<4;i++){
        int xx=x+dir[i][0],yy=y+dir[i][1];
        if(xx<1||yy<1||xx>n||yy>m||!vis[xx][yy])  continue;
        sta|=1<<i;
    }
    return b[x][y]<=cnt[sta];
}
bool chk(int x,int y,int fx,int fy){
    if(!b[x][y])return 0;
    int sta=0;
    for(int i=0;i<4;i++){
        int xx=x+dir[i][0],yy=y+dir[i][1];
        if(xx==fx&&yy==fy){sta|=1<<i;break;}
    }
    return b[x][y]<=cnt[sta];
}
bool mem2;
int main(){
    // freopen("meruru.in","r",stdin);freopen("meruru.out","w",stdout);
    O['W']=0;O['E']=1;O['N']=2;O['S']=3;
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d%s",&k,&n,&m,a+1);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&b[i][j]);
    for(int s=0;s<(1<<4);s++){
        bool al=true;
        for(int i=1;i<=k;i++)if(!(s&(1<<O[a[i]]))){al=false;break;}
        if(al){cnt[s]=1e9;continue;}
        for(int i=1;i<=k;i++){
            int j=i;while(s&(1<<O[a[(j-1)%k+1]]))j++;
            if(i==j)    continue;
            gmx(cnt[s],j-i);
            i=j-1;
        }
    }
    U.init();
    while(true){
        bool flg=false;
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(b[i][j]&&U[id(i,j)]==id(i,j)){
            q.ep(i,j);vector<pii> vec;vis[i][j]=true;
            bool tg=false;
            while(!q.empty()){
                int x=q.front().fi,y=q.front().se;q.pop();
                vec.eb(x,y);if(tg)  continue;
                for(int d=0;d<4;d++){
                    int xx=x+dir[d][0],yy=y+dir[d][1];
                    if(xx<1||yy<1||xx>n||yy>m||vis[xx][yy]) continue;
                    if(chk(xx,yy)){
                        if(U[id(xx,yy)]^id(i,j)){U.merge(id(xx,yy),id(i,j));tg=true;break;}
                        vis[xx][yy]=true,q.ep(xx,yy);
                    }
                }
            }
            for(auto [x,y]:vec) vis[x][y]=false;
            if(tg)  flg=true;
        }
        if(!flg)    break;
    }
    // for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++)printf("%d ",U[id(i,j)]);puts("");
    pii ans=pii(1e9,0);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(b[i][j]&&U[id(i,j)]==id(i,j)){
        // printf("id = (%d,%d)\n",i,j);
        q.ep(i,j);vector<pii> vec;vis[i][j]=true;
        while(!q.empty()){
            int x=q.front().fi,y=q.front().se;q.pop();
            vec.eb(x,y);
            for(int d=0;d<4;d++){
                int xx=x+dir[d][0],yy=y+dir[d][1];
                if(xx<1||yy<1||xx>n||yy>m||vis[xx][yy]) continue;
                if(chk(xx,yy))  vis[xx][yy]=true,q.ep(xx,yy);
            }
        }
        for(auto [x,y]:vec) vis[x][y]=false;
        if(ans.fi>vec.size())   ans=pii(vec.size(),vec.size());
        else if(ans.fi==vec.size()) ans.se+=vec.size();
    }
    printf("%d\n%d\n",ans.fi,ans.se);
}
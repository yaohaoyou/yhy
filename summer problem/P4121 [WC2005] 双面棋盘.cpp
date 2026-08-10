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
const int maxn=210,maxm=maxn*maxn,maxq=1e4+10,dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int n,m,q;
int ans;
bool a[maxn][maxn];
int lst[maxn][maxn][4],id[maxn][maxn],out[2][maxq];
int s[2][maxq];
struct DSU{
    stack<int> stk;
    int fa[maxm],siz[maxm];
    void init(){iota(fa+1,fa+m+1,1);fill(siz+1,siz+m+1,1);}
    int find(int x){return fa[x]==x?x:find(fa[x]);}
    inline void merge(int x,int y){
        x=find(x);y=find(y);if(x==y)return;
        ans++;
        if(siz[x]>siz[y])   swap(x,y);
        siz[y]+=siz[x];fa[x]=y;stk.ep(x);
    }
    inline void bac(int k){while(stk.size()^k){int x=stk.top();stk.pop();ans--;siz[fa[x]]-=siz[x];fa[x]=x;}}
}U;
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,q
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    bool o;
    vector<pii> tr[maxq<<2];
    void upd(setpos,int pl,int pr,pii x){if(l>=pl&&r<=pr)return tr[p].eb(x),void();setmid;if(pl<=mid)upd(lson,pl,pr,x);if(pr>mid)upd(rson,pl,pr,x);}
    void dfs(setpos){
        int siz=U.stk.size();
        for(pii x:tr[p])    U.merge(x.fi,x.se);
        if(l==r)    out[o][l]=ans;
        else{setmid;dfs(lson);dfs(rson);}
        U.bac(siz);
    }
}T[2];
int main(){
    scanf("%d",&n);m=n*n;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
    {int cnt=0;for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)id[i][j]=++cnt,s[a[i][j]][0]++;}
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=0;k<4;k++){
                int x=i+dir[k][0],y=j+dir[k][1];
                if(x>0&&x<=n&&y>0&&y<=n&&a[i][j]==a[x][y])  lst[i][j][k]=1;
            }
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        s[0][i]=s[0][i-1];s[1][i]=s[1][i-1];
        int x,y;scanf("%d%d",&x,&y);
        s[a[x][y]][i]--;s[a[x][y]^1][i]++;
        for(int j=0;j<4;j++){
            int xx=x+dir[j][0],yy=y+dir[j][1];
            if(xx<=0||xx>n||yy<=0||yy>n) continue;
            if(a[xx][yy]==a[x][y]){
                if(i^1)   T[a[x][y]].upd(all,lst[x][y][j],i-1,pii(id[x][y],id[xx][yy]));
            }
            else    lst[x][y][j]=lst[xx][yy][j^1]=i;
        }
        a[x][y]^=1;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=0;k<4;k++){
                int x=i+dir[k][0],y=j+dir[k][1];
                if(x>0&&x<=n&&y>0&&y<=n&&a[i][j]==a[x][y])  T[a[i][j]].upd(all,lst[i][j][k],q,pii(id[i][j],id[x][y]));
            }
    U.init();T[0].o=0;T[0].dfs(all);T[1].o=1;T[1].dfs(all);
    for(int i=1;i<=q;i++)   printf("%d %d\n",s[1][i]-out[1][i],s[0][i]-out[0][i]);
}
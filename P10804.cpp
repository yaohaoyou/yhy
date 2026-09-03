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
const int maxn=1510,dir[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
int n,m,k,l,sx,sy,tx,ty;
char a[maxn][maxn];
set<int> H[maxn],W[maxn];
bool vis[maxn][maxn];
queue<pii> q;
void bfs(){
    q.ep(sx,sy);vis[sx][sy]=true;
    while(!q.empty()){
        int x=q.front().fi,y=q.front().se;q.pop();
        if(x==tx&&y==ty)    exit(puts("YES")&0);
        for(int d:{0,1}){
            int xx=x+dir[d][0],yy=y+dir[d][1];
            if(!xx||!yy||xx>n||yy>m||a[xx][yy]=='X'||vis[xx][yy])    continue;
            auto it=H[y].lower_bound(x);
            int up=0,dw=it==H[y].end()?n+1:*it;
            if(it!=H[y].begin())    up=*(--it);
            it=H[yy].lower_bound(x);
            if(it!=H[yy].end()) gmn(dw,*it);
            if(it!=H[yy].begin())   gmx(up,*(--it));
            up++;dw--;
            if(dw-up+1>=l)  q.ep(xx,yy),vis[xx][yy]=true;
        }
        for(int d:{2,3}){
            int xx=x+dir[d][0],yy=y+dir[d][1];
            if(!xx||!yy||xx>n||yy>m||a[xx][yy]=='X'||vis[xx][yy])    continue;
            auto it=W[x].lower_bound(y);
            int L=0,R=it==W[x].end()?m+1:*it;
            if(it!=W[x].begin())    L=*(--it);
            it=W[xx].lower_bound(y);
            if(it!=W[xx].end()) gmn(R,*it);
            if(it!=W[xx].begin())   gmx(L,*(--it));
            L++;R--;
            if(R-L+1>=k)  q.ep(xx,yy),vis[xx][yy]=true;
        }
    }
}
int main(){
    scanf("%d%d%d%d",&m,&n,&k,&l);
    scanf("%*d%d%d%*d",&sx,&sy);sx++;sy++;
    for(int i=1;i<=n;i++){
        scanf("%s",a[i]+1);
        for(int j=1;j<=m;j++)
            if(a[i][j]=='*'){tx=i;ty=j;}
            else if(a[i][j]=='X')   H[j].ep(i),W[i].ep(j);
    }
    bfs();
    puts("NO");
}
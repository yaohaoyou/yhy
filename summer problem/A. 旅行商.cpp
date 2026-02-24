#include<bits/stdc++.h>
#define db double
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
const int maxn=310,maxN=maxn*maxn,dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
const db eps=1e-10;
int n,L,q,N;
pii p[maxN];
int id[maxn][maxn];
bool used[maxn][maxn];
db bl[maxn],br[maxn];
set<pii> st;
void solve(int _cases){
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)used[i][j]=false;
    scanf("%d%d",&n,&L);N=n*n;
    db B=1.0*L/n;
    for(int i=1;i<=n;i++)bl[i]=br[i-1]+eps,br[i]=B*i;
    for(int i=1;i<=N;i++)   scanf("%d%d",&p[i].fi,&p[i].se);
    int x=1,y=1,sum=n*n;
    while(sum--){
        id[x][y]=n*n-sum;
        used[x][y]=true;
        for(int i=0;i<4;i++){
            int xx=x+dir[i][0],yy=y+dir[i][1];
            if(xx>0&&xx<=n&&yy>0&&yy<=n&&!used[xx][yy]){
                x=xx;y=yy;
                break;
            }
        }
    }
    st.clear();
    for(int i=1;i<=N;i++){
        int bx=lower_bound(br+1,br+n+1,p[i].fi)-br,by=lower_bound(br+1,br+n+1,p[i].se)-br;
        st.ep(id[bx][by],i);
    }
    for(pii i:st)   printf("%d ",i.se);puts("");
    scanf("%d",&q);
    while(q--){
        int i,a,b;scanf("%d%d%d",&i,&a,&b);
        int bx=lower_bound(br+1,br+n+1,p[i].fi)-br,by=lower_bound(br+1,br+n+1,p[i].se)-br;
        st.erase(pii(id[bx][by],i));
        p[i]=pii(a,b);
        bx=lower_bound(br+1,br+n+1,p[i].fi)-br,by=lower_bound(br+1,br+n+1,p[i].se)-br;
        auto it=st.ep(id[bx][by],i).fi;
        printf("%d\n",it==st.begin()?0:(--it)->se);
    }
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)solve(i);}
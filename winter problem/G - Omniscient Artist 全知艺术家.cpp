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
const int maxn=3e5+10,B=512,Block=maxn/B+10;
int n,m;
int a[maxn],b[maxn];
vector<pii> I[maxn],D[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
ll ans[maxn];
namespace Block_array{
    int id[maxn],bl[Block],br[Block],tag[Block],buc[Block][maxn],mn[Block],mx[Block];
    inline void broke(int x){for(int i=bl[x];i<=br[x];i++)buc[x][a[i]]=0,a[i]+=tag[x];tag[x]=0;}
    inline void rebuild(int x){
        int l=bl[x],r=br[x];
        mn[x]=1e9;mx[x]=0;
        for(int i=l;i<=r;i++)   buc[x][a[i]]++,gmn(mn[x],a[i]),gmx(mx[x],a[i]);
    }
    inline void upd(int l,int r,int s){
        int idl=id[l],idr=id[r];
        if(idl==idr){
            broke(idl);
            for(int i=l;i<=r;i++)   a[i]+=s;
            return rebuild(idl);
        }
        if(l==bl[idl])  idl--;
        else{
            broke(idl);
            for(int i=l;i<=br[idl];i++)   a[i]+=s;
            rebuild(idl);
        }
        if(r==br[idr])  idr++;
        else{
            broke(idr);
            for(int i=bl[idr];i<=r;i++)   a[i]+=s;
            rebuild(idr);
        }
        for(int i=idl+1;i<idr;i++)  tag[i]+=s;
    }
    inline void query(){
        for(int i=1;i<=id[n];i++){
            int l=mn[i]+tag[i],r=mx[i]+tag[i];
            for(int j=(l+m-1)/m*m;j<=r;j+=m)    ans[j]+=buc[i][j-tag[i]];
        }
    }
}
using namespace Block_array;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&x2,&y1,&y2);x2--;y2--;
        I[x1].eb(y1,y2);D[x2+1].eb(y1,y2);
    }
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,n),rebuild(i);
    for(int i=1;i<=n;i++){
        for(pii j:I[i]) upd(j.fi,j.se,1);
        for(pii j:D[i]) upd(j.fi,j.se,-1);
        query();
    }
    for(int i=m;i<=n;i+=m)   printf("%lld\n",ans[i]);
}
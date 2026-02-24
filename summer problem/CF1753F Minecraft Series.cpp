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
const int maxn=4e4+10,maxk=1e6+10;
int n,m,k,t;
vector<vector<vector<int>>> mp;
namespace Block_array{
    const int B=1024,Block=maxk/B+10;
    #define id(x) ((x-1>>10)+1)
    #define bl(x) ((x-1<<10)+1)
    #define br(x) min(k,(x<<10))
    int sum[2][Block],buc[2][maxk];
    bool flag,ret;
    inline void upd(int x){
        flag=false;
        bool o=0;
        if(x<0)x=-x,o=1;
        if(!buc[o][x])  sum[o][id(x)]++;
        buc[o][x]++;
    }
    inline void era(int x){
        flag=false;
        bool o=0;
        if(x<0)x=-x,o=1;
        buc[o][x]--;
        if(!buc[o][x])   sum[o][id(x)]--;
    }
    inline bool check(){
        if(flag)    return ret;
        flag=true;
        int idk=id(k),L=0,R=0;
        for(int i=1;i<=idk;i++){
            int bl=bl(i),br=br(i);
            if(sum[0][i]==br-bl+1){R=br;continue;}
            for(int j=bl;j<=br;j++)if(!buc[0][j]){R=j-1;break;}
            break;
        }
        for(int i=1;i<=idk;i++){
            int bl=bl(i),br=br(i);
            if(sum[1][i]==br-bl+1){L=-br;continue;}
            for(int j=bl;j<=br;j++)if(!buc[1][j]){L=-j+1;break;}
            break;
        }
        return ret=(R-L+1>=t);
    }
    void clear(){mems(sum,0);mems(buc,0);}
}
using namespace Block_array;
int main(){
    scanf("%d%d%d%d",&n,&m,&k,&t);
    mp=vector<vector<vector<int>>>(n+1,vector<vector<int>>(m+1,vector<int>()));
    for(int i=1;i<=k;i++){int x,y,w;scanf("%d%d%d",&x,&y,&w);if(abs(w)<=k)mp[x][y].eb(w);}
    ll ans=0;
    for(int i=1;i<=n;i++){
        // (i,1)
        int x=i,y=1,rx=x,ry=y;
        for(int j:mp[i][1])upd(j);
        while(x<=n&&y<=m){
            while(rx<n&&ry<m&&!check()){
                rx++;ry++;
                for(int k=x;k<=rx;k++)for(int j:mp[k][ry])upd(j);
                for(int k=y;k<ry;k++)for(int j:mp[rx][k])upd(j);
            }
            if(check())ans+=min(n-rx+1,m-ry+1);
            for(int k=x;k<=rx;k++)for(int j:mp[k][y])era(j);
            for(int k=y+1;k<=ry;k++)for(int j:mp[x][k])era(j);
            x++,y++;
        }
    }
    for(int i=2;i<=m;i++){
        // (1,i)
        int x=1,y=i,rx=x,ry=y;
        for(int j:mp[1][i])upd(j);
        while(x<=n&&y<=m){
            while(rx<n&&ry<m&&!check()){
                rx++;ry++;
                for(int k=x;k<=rx;k++)for(int j:mp[k][ry])upd(j);
                for(int k=y;k<ry;k++)for(int j:mp[rx][k])upd(j);
            }
            if(check())ans+=min(n-rx+1,m-ry+1);
            for(int k=x;k<=rx;k++)for(int j:mp[k][y])era(j);
            for(int k=y+1;k<=ry;k++)for(int j:mp[x][k])era(j);
            x++,y++;
        }
    }
    printf("%lld\n",ans);
}
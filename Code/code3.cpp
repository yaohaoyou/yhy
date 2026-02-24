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
const int maxn=20;
int n,m;
ll ss;
int a[maxn][maxn];
ll sh[maxn],sw[maxn];
bool inh[maxn],inw[maxn];
inline void chk(vector<int> H,vector<int> W){
    ll sum=0;
    for(int i:H)sum+=sh[i];
    for(int i:W)sum+=sw[i];
    if(sum<ss)  return;
    for(int i:H)for(int j:W)if((sum-=a[i][j])<ss)return;
    if(sum==ss){
        puts("YES");
        mems(inh,0);mems(inw,0);
        for(int i:H)inh[i]=true;for(int i:W)inw[i]=true;
        H.clear();W.clear();
        for(int i=1;i<=n;i++)if(!inh[i])H.eb(i);
        for(int i=1;i<=n;i++)if(!inw[i])W.eb(i);
        printf("%d\n",H.size()+W.size());
        for(int i:H)    printf("1 %d\n",i);
        for(int i:W)    printf("2 %d\n",i);
        exit(0);
    }
}
vector<int> H,W;
void check(){
    mems(inh,0);mems(inw,0);
    for(int i:H)inh[i]=true;for(int i:W)inw[i]=true;
    vector<int> oH,oW;oH.clear();oW.clear();
    for(int i=1;i<=n;i++)if(!inh[i])oH.eb(i);
    for(int i=1;i<=n;i++)if(!inw[i])oW.eb(i);
    chk(H,W);chk(oH,W);chk(H,oW);chk(oH,oW);
}
void dfs2(int x,int y){
    check();
    if(x>8) return;
    for(int i=y+1;i<=m;i++){
        W.eb(i);
        dfs2(x+1,i);
        W.pop_back();
    }
}
void dfs1(int x,int y){
    dfs2(1,0);
    if(x>8) return;
    for(int i=y+1;i<=n;i++){
        H.eb(i);
        dfs1(x+1,i);
        H.pop_back();
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&a[i][j]),sh[i]+=a[i][j],sw[j]+=a[i][j];
    scanf("%lld",&ss);
    dfs1(1,0);
}
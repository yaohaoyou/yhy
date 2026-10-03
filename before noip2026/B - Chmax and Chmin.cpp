#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=410,inf=1e9;
bool mem1;
int n;
int a[maxn],b[maxn],c[maxn],d[maxn];
int L[maxn],R[maxn];
int cmn[maxn][maxn],cmx[maxn][maxn];
vector<piii> ans;
bool mem2;
void matt(int _cases){
    ans.clear();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&c[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&d[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]),L[i]=R[i]=b[i];
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++){
        cmx[i][j]=cmn[i][j]=0;
        for(int k=i;k<=j;k++)cmx[i][j]+=c[j-i+1]>R[k];
        for(int k=i;k<=j;k++)cmn[i][j]+=d[j-i+1]<L[k];
    }
    while(true){
        bool fl=false;
        for(int i=1;i<=n;i++)for(int j=i;j<=n;j++){
            if(!cmx[i][j]){
                cmx[i][j]=-1;
                bool used=false;
                for(int k=i;k<=j;k++){
                    assert(c[j-i+1]<=R[k]);
                    if(c[j-i+1]>=L[k]&&L[k]!=-inf){
                        used=true;
                        L[k]=-inf;
                        for(int l=1;l<=k;l++)for(int r=k;r<=n;r++)cmn[l][r]-=d[r-l+1]<b[k];
                    }
                }
                if(used)    ans.eb(1,pii(i,j));
                fl=true;
                break;
            }
            if(!cmn[i][j]){
                cmn[i][j]=-1;
                bool used=false;
                for(int k=i;k<=j;k++){
                    assert(d[j-i+1]>=L[k]);
                    if(d[j-i+1]<=R[k]&&R[k]!=inf){
                        used=true;
                        R[k]=inf;
                        for(int l=1;l<=k;l++)for(int r=k;r<=n;r++)cmx[l][r]-=c[r-l+1]>b[k];
                    }
                }
                if(used)    ans.eb(0,pii(i,j));
                fl=true;
                break;
            }
        }
        if(!fl) break;
    }
    // for(int i=1;i<=n;i++)   printf("%d %d\n",L[i],R[i]);puts("");
    for(int i=1;i<=n;i++)if(!(L[i]<=a[i]&&a[i]<=R[i]))return puts("-1"),void();
    printf("%d\n",ans.size());
    reverse(ans.begin(),ans.end());
    for(auto [op,i]:ans){
        if(op)  printf("chmax ");
        else    printf("chmin ");
        printf("%d %d\n",i.fi,i.se);
    }
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
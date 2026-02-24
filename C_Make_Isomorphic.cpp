#include<bits/stdc++.h>
#define ll long long
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=100;
int n,m,M;
int a[maxn][maxn];
int ord[maxn],bac[maxn];
set<int> G[maxn],H[maxn];
set<int> son[maxn];
bool bk[maxn][maxn];
int ans=2e9;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);H[u].ep(v);H[v].ep(u);}
    scanf("%d",&M);
    for(int i=1;i<=M;i++){int u,v;scanf("%d%d",&u,&v);G[u].ep(v);G[v].ep(u);}
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            scanf("%d",&a[i][j]);a[j][i]=a[i][j];
        }
    for(int i=1;i<=n;i++)   ord[i]=i;
    do{
        mems(bk,0);
        for(int i=1;i<=n;i++)   bac[ord[i]]=i;
        for(int i=1;i<=n;i++)   son[i]=G[i];

        int res=0;bool fl=true;
        for(int u=1;u<=n;u++){
            int v=ord[u];
            for(int i:H[v]){
                int j=bac[i];
                if(son[u].find(j)==son[u].end()){
                    if(bk[u][j]){fl=false;break;}
                    res+=a[u][j];
                    son[u].ep(j);son[j].ep(u);bk[u][j]=bk[j][u]=true;
                }
            }
            if(!fl)break;
            vector<int> tmp;tmp.clear();
            for(int i:son[u])tmp.emplace_back(i);
            for(int i:tmp){
                if(son[u].find(i)==son[u].end())    continue;
                int j=ord[i];
                if(H[v].find(j)==H[v].end()){
                    if(bk[u][i]){fl=false;break;}
                    res+=a[u][i];
                    son[u].erase(i);son[i].erase(u);bk[u][i]=bk[i][u]=true;
                }
            }
            if(!fl)break;
        }
        if(!fl) continue;
        ans=min(ans,res);
    }while(next_permutation(ord+1,ord+n+1));
    printf("%d\n",ans);
}
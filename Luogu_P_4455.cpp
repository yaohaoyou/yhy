#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=260,mod=1e4+7;
int n,m,op;
int a[maxn][maxn];
int tot;
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=(1ll*x*y%mod+mod)%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
int calc(){
    int res=1,ans=1;
    tot=n-1;
    for(int i=1;i<=tot;i++){
        for(int j=i+1;j<=tot;j++){
            while(a[i][i]){
                int x=a[j][i]/a[i][i];
                for(int k=i;k<=tot;k++)
                    mdel(a[j][k],immul(x,a[i][k]));
                swap(a[i],a[j]);res*=-1;    
            }
            swap(a[i],a[j]);res*=-1;
        }
    }
    for(int i=1;i<=tot;i++) mmul(ans,a[i][i]);
    if(!~res)ans=imdel(0,ans);
    return ans;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<=m;i++){
        scanf("%d%d",&v,&u);
        u--;v--;
        madd(a[v][v],1);mdel(a[u][v],1);
    }
    printf("%d",calc());
}
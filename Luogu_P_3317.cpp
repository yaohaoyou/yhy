#include<bits/stdc++.h>
#define db double
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=260,mod=1e4+7;
const db eps=1e-6;
int n,m,op;
db sum=1;
db a[maxn][maxn];
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
db calc(){
    int res=1;
    db ans=1;
    tot=n-1;
    for(int i=1;i<=tot;i++){
        for(int j=i+1;j<=tot;j++){
            while(a[i][i]>eps){
                db x=a[j][i]/a[i][i];
                for(int k=i;k<=tot;k++)
                    a[j][k]-=x*a[i][k];
                swap(a[i],a[j]);res*=-1;
            }
            swap(a[i],a[j]);res*=-1;
        }
    }
    for(int i=1;i<=tot;i++) ans*=a[i][i];
    ans*=res;
    return ans;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            db x;
            scanf("%lf",&x);
            if(j>i){
                x+=eps;
                if(x<eps)   x=eps;
                else if(x>1-eps)    x=1-eps;
                sum*=(1-x);
                db w=x/(1-x);
                a[i][i]+=w;a[j][j]+=w;
                a[i][j]-=w;a[j][i]-=w;
            }
        }
    }
    printf("%.5f",sum*calc());
}
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
const int maxn=5010,B=64,V=2e9/B,A=2e9;
int n;
int a[maxn];
bool ntp[V+10];vector<int> p;
int phi[V+10];
vector<int> vec[50000];
int fac[maxn][maxn];
ll ans;
void init(){
    phi[1]=1;
    for(int i=2;i<=V;i++){
        if(!ntp[i]) p.eb(i),phi[i]=i-1;
        for(int j:p){
            if(1ll*i*j>V)   break;
            ntp[i*j]=true;
            if(i%j==0){
                phi[i*j]=phi[i]*j;
                break;
            }
            phi[i*j]=phi[i]*phi[j];
        }
    }
}
int main(){
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int l=0;while(p[l]<=B)l++;
    for(int i=l;i<p.size();i++){
        if(1ll*p[i]*p[i]>A) continue;
        for(int j=n;j;j--){
            vec[a[j]%p[i]].eb(j);
            int r=(p[i]-a[j]%p[i])%p[i];
            for(int k:vec[r])   fac[j][k]=p[i];
        }
        for(int j=0;j<p[i];j++)vec[j].clear();
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            int x=a[i]+a[j],w=1;
            if(x<=V){ans+=phi[x];continue;}
            if(fac[i][j]){
                assert(x%fac[i][j]==0);
                x/=fac[i][j];w=fac[i][j]-1;
                while(x%fac[i][j]==0)   x/=fac[i][j],w*=fac[i][j];
                ans+=phi[x]*w;
                continue;
            }
            for(int k=0;p[k]<=B;k++)if(x%p[k]==0){
                x/=p[k];w*=p[k]-1;
                while(x%p[k]==0&&x>V)x/=p[k],w*=p[k];
                if(x<=V){
                    if(x%p[k]==0)   ans+=w/(p[k]-1)*p[k]*phi[x];
                    else    ans+=w*phi[x];
                    break;
                }
            }
            if(x>V) ans+=(x-1)*w;
        }
    }
    printf("%lld\n",ans);
}
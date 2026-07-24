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
const int maxn=3010;
int n;
int f[maxn],g[maxn];
char a[maxn];
bool chk(char x,char y){return x==y||x=='?'||y=='?';}
void matt(int _cases){
    mems(f,0);mems(g,0);
    scanf("%s",a+1);n=strlen(a+1);
    for(int i=1;i<=n/2;i++){
        for(int l=1;l+i+i-1<=n;l++){
            int p=0;
            for(int j=l;j<=l+i-1;j++)if(!chk(a[j],a[j+i])){p=j;break;}
            if(p)   l=p;
            else{
                for(;l+i+i-1<=n;l++){
                    if(!chk(a[l+i-1],a[l+i+i-1]))   break;
                    f[l]++;g[l+i+i-1]++;
                }
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j+j<=n-i+1;j++){
    //         bool flag=true;
    //         for(int k=i;k<=i+j-1;k++)if(!chk(a[k],a[k+j])){flag=false;break;}
    //         if(flag)    f[i]++,g[i+j+j-1]++;
    //     }
    // }
    ll ans=0;
    for(int i=1;i<=n;i++)ans+=g[i]*f[i+1];
    printf("%lld\n",ans);
}
int main(){freopen("excellent.in","r",stdin);freopen("excellent.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
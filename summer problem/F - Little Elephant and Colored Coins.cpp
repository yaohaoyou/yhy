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
const int maxn=35,maxv=2e5+10;
int n,cnt;
pii a[maxn];
ll dis[2][maxv][maxn];
unordered_map<int,int> mp;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1);int m=a[1].fi;
    for(int i=1;i<=n;i++){int &j=mp[a[i].se];if(!j)j=++cnt;a[i].se=j;}
    // for(int i=0;i<m;i++){
    //     for(int j=2;j<=n;j++){
            // adde(i,(i+a[j].fi)%a[1].fi,1<<a[i].se);
    //     }
    // }
    mems(dis,0x3f);dis[0][0][0]=0;
    sort(a+1,a+n+1,[&](pii x,pii y){return x.se<y.se;});
    int c=0;bool o=true;
    for(int l=1;l<=n;l++,o^=1){
        memc(dis[o],dis[!o]);
        int r=l;while(r<=n&&a[r].se==a[l].se)r++;r--;
        c++;
        for(int i=l;i<=r;i++){
            for(int j=0,lim=__gcd(a[i].fi,m);j<lim;j++){
                int u=j;
                for(int k=0;k<=2;(u+=a[i].fi)%=m,k+=(u==j)){
                    int t=(u+a[i].fi)%m;
                    for(int x=1;x<=c;x++){
                        dis[o][t][x]=min(dis[o][t][x],dis[o][u][x]+a[i].fi);
                        dis[o][t][x]=min(dis[o][t][x],dis[!o][u][x-1]+a[i].fi);
                    }
                }
            }
        }
        l=r;
    }
    int q;scanf("%d",&q);
    while(q--){
        ll x;scanf("%lld",&x);
        int ans=-1;
        for(int i=c;i;i--)if(dis[!o][x%m][i]<=x){ans=i;break;}
        printf("%d\n",ans);
    }
}
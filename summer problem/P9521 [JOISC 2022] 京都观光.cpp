#include<bits/stdc++.h>
#define db double
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
const int maxn=1e5+10;
int n,m;
int a[maxn],b[maxn];
int sa[maxn],tpa;
int sb[maxn],tpb;
db slope(int x,int y,int x1,int y1){return 1.0*(y1-y)/(x1-x);}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=n;i++){
        while(tpa>1&&slope(i,a[i],sa[tpa],a[sa[tpa]])<=slope(sa[tpa],a[sa[tpa]],sa[tpa-1],a[sa[tpa-1]]))tpa--;sa[++tpa]=i;
    }
    for(int i=1;i<=m;i++){
        while(tpb>1&&slope(i,b[i],sb[tpb],b[sb[tpb]])<=slope(sb[tpb],b[sb[tpb]],sb[tpb-1],b[sb[tpb-1]]))tpb--;sb[++tpb]=i;
    }
    int x=1,y=1;
    ll ans=0;
    while(x^tpa||y^tpb){
        if(x==tpa)  ans+=1ll*a[sa[x]]*(sb[y+1]-sb[y]),y++;
        else if(y==tpb) ans+=1ll*b[sb[y]]*(sa[x+1]-sa[x]),x++;
        else{
            if(slope(sa[x],a[sa[x]],sa[x+1],a[sa[x+1]])>slope(sb[y],b[sb[y]],sb[y+1],b[sb[y+1]]))   ans+=1ll*a[sa[x]]*(sb[y+1]-sb[y]),y++;
            else    ans+=1ll*b[sb[y]]*(sa[x+1]-sa[x]),x++;
        }
    }
    printf("%lld\n",ans);
}
#pragma GCC optimize(2,3,"Ofast")
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e6+10,lim=1e7;
int n,m,k;
int a[maxn];
pii b[maxn];
int v[lim+2];
bool check(int x){
    for(int i=1;i<=x;i++)   v[b[i].fi]++;
    ll s=0;bool flag=true;
    for(int i=0;i<=lim;i++){
        s+=v[i];
        if(s>k){flag=false;break;}
        s-=k;
    }
    for(int i=1;i<=x;i++)   v[b[i].fi]--;
    return flag;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++){scanf("%d",&b[i].fi);b[i].se=i;}
    sort(b+1,b+m+1,greater<pii>());
    for(int i=1;i<=n;i++)   v[a[i]]++;
    int l=0,r=m,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){ans=mid;l=mid+1;}
        else    r=mid-1;
    }
    printf("%d\n",ans);
    for(int i=1;i<=ans;i++) printf("%d ",b[i].se);
    // printf("%d\n",ans);
}
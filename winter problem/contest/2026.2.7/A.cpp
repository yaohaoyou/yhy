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
const int maxn=5e5+10;
int c,n,t;
pii a[maxn];
priority_queue<int> pq;
int main(){
    scanf("%d%d%d",&c,&n,&t);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se),a[i].se=t-a[i].se;
    sort(a+1,a+n+1,[&](pii x,pii y){return x.se<y.se;});
    int now=0,ans=0;
    for(int i=1;i<=n;i++){
        if(now+a[i].fi<=a[i].se){
            now+=a[i].fi;ans++;
            pq.ep(a[i].fi);
        }
        else{
            if(!pq.empty()&&pq.top()>a[i].fi)   now-=pq.top(),pq.pop(),now+=a[i].fi,pq.ep(a[i].fi);
        }
    }
    printf("%d\n",ans);
}
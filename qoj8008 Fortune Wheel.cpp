#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10,maxk=510;
int n,x,k;
int a[maxn];
int dis[maxn];
queue<int> q;
int main(){
    q.push(0);
    scanf("%d%d%d",&n,&x,&k);
    for(int i=1;i<n;i++)    dis[i]=n-1;
    for(int i=1;i<=k;i++)   scanf("%d",&a[i]);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=1;i<=k;i++){
            int v=(u+n-a[i])%n;
            if(dis[v]>dis[u]+1){dis[v]=dis[u]+1;q.push(v);}
        }
    }
    ll dx=dis[x],dy=1,s=n;
    sort(dis,dis+n);
    for(int i=1;i<=n;i++){
        s+=dis[i-1];
        if(dx*i>dy*s){dx=s;dy=i;}
    }
    printf("%lld %lld\n",dx/__gcd(dx,dy),dy/__gcd(dx,dy));
}
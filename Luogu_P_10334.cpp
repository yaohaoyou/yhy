#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10,inf=1e9;
int n;
int a[maxn],t[maxn];
int dis[maxn],mx[maxn];
int ans;
#define pii pair<int,int>
priority_queue<pii> q;
vector<int> v[maxn];
#define eb emplace_back
stack<int> stk;
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&t[i]);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<n;i++)    dis[i]=t[i+1]-t[i]-1;
    dis[0]=t[1]-1;
    if(dis[0]>0)    stk.push(0);
    for(int i=1;i<=n;i++){
        if(t[i]!=t[i-1]){
            if(dis[i]>0)  stk.push(i);
            continue;
        }
        if(stk.empty())  return puts("-1")&0;
        int now=stk.top();
        dis[now]--;
        if(!dis[now]) stk.pop();
        v[now+1].eb(i);
        // printf("%lld %lld\n",now+1,i);
        if(dis[i]>0)  stk.push(i);
    }
    for(int i=1;i<=n;i++){
        for(int j:v[i]) q.push(pii(a[j],j));
        while(!q.empty()&&q.top().second<i) q.pop();
        if(!q.empty())  ans+=max(q.top().first,a[i]);
        else    ans+=a[i];
        // printf("%lld\n",ans);
    }
    printf("%lld\n",ans);
}
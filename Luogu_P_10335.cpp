#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10;
int n;
int a[maxn];
priority_queue<int,vector<int>,greater<int>> q;
int mx,s;
void solve(){
    while(!q.empty())   q.pop();
    scanf("%lld",&n);
    mx=0;s=0;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        q.push(a[i]);
        mx=max(mx,a[i]);
        s+=a[i];
    }
    if(mx*2>s)  return puts("YES"),void();
    int r=1;
    while(q.size()>1){
        int u=q.top();q.pop();
        int v=q.top();q.pop();
        if((u+v)*2>=s){
            if(r)   puts("NO");
            else    puts("YES");
            return;
        }
        q.push(u+v);
        r^=1;
    }
}
signed main(){
    int t;
    scanf("%lld",&t);
    while(t--) solve();
}
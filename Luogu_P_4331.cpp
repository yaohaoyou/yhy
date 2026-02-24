#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+10;
int n,ans;
int a[maxn];
priority_queue<int> q;
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;i++){
        q.push(a[i]);
        if(a[i]<q.top()){
            ans+=(q.top()-a[i]);
            q.pop();
            q.push(a[i]);
        }
    }
    printf("%lld",ans);
}
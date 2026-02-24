#include<bits/stdc++.h>
#define pii pair<int,int>
#define pb push_back
using namespace std;
const int maxn=1e5+10;
int n;
int a[maxn];
multiset<int> s;
int main(){
    // freopen("duel.in","r",stdin);freopen("duel.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        s.insert(a[i]);
    }
    sort(a+1,a+n+1);
    int ans=n;
    for(int i=1;i<=n;i++){
        auto it=s.upper_bound(a[i]);
        if(it==s.end()) continue;
        s.erase(it);
        ans--;
    }
    printf("%d\n",ans);
}
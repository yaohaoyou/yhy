#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e5+10;
int n;
int a[maxn],lst[maxn],bas[maxn];
ll c[maxn],ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        lst[i]=bas[a[i]];
        bas[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        // (lst[i]+1,i)+=(n-i+1);
        c[lst[i]+1]+=(n-i+1);
        c[i+1]-=(n-i+1);
    }
    for(int i=1;i<=n;i++){c[i]+=c[i-1];ans+=c[i];}
    printf("%lld\n",ans);
}
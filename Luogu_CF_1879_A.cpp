#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=110;
int n;
int a[maxn],b[maxn];
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    for(int i=2;i<=n;i++){
        if(a[i]>=a[1]&&b[i]>=b[1])   return puts("-1"),void();
    }
    printf("%d\n",a[1]);
}
int main(){int T;scanf("%d",&T);while(T--)solve();}
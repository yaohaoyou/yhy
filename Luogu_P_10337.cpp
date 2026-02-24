#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n;
int a[maxn];
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=2;i<=n;i++)
        if(a[i]!=a[i-1])    return printf("%d\n",n-1),void();
    printf("%d\n",n);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) solve();
}
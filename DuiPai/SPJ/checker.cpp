#include<bits/stdc++.h>
using namespace std;
const int maxn=1<<24;
int n;
int a[maxn],f[maxn],dp[maxn];
int ans;
int main(){
    freopen("D:\\yhy\\DuiPai\\SPJ\\mine.out","r",stdin);
    freopen("D:\\yhy\\DuiPai\\SPJ\\checker.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&f[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++)
            if(a[i]>a[j])   dp[i]=max(dp[i],dp[j]+1);
        if(dp[i]!=f[i]){puts("Wrong Answer");exit(0);}
    }
    puts("Accepted");
}
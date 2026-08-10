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
const int maxn=3e5+10;
int n,m,a[maxn];
char s[maxn];
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<n;i++){
        if(s[i]==s[i+1])    a[++m]=i;
    }
    ll ans=0;
    for(int i=1,j=1;i<=n;i++){
        while(j<=m&&a[j]<i) j++;
        if(j<=m)    ans+=a[j]-i+1;
        else    ans+=n-i+1;
    }
    cout<<ans%998244353;
}
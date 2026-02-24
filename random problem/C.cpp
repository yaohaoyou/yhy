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
const int maxn=7510;
int n;
int a[maxn],b[maxn],pre[maxn],suf[maxn];
int s[maxn];
int ans[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)   pre[i]=pre[i-1]+(a[i]==b[i]);
    for(int i=n;i;i--)  suf[i]=suf[i+1]+(a[i]==b[i]);
    ans[pre[n]]=n;
    for(int i=2;i<=n<<1;i++){
        for(int j=1;j<=n&&j<i;j++)
            s[j]=s[j-1]+(a[j]==b[i-j]);
        for(int l=1;l<=n&&i-l>l;l++){
            int r=i-l;
            if(r>n) continue;
            ans[pre[l-1]+s[r]-s[l-1]+suf[r+1]]++;
        }
    }
    for(int i=0;i<=n;i++) printf("%d\n",ans[i]);
}
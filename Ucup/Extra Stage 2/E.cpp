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
const int maxn=1e5+10;
int n;
int a[maxn],b[maxn];
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    sort(a+1,a+n+1);sort(b+1,b+n+1);
    bool flag=true;
    for(int i=1;i<=n;i++)flag&=(a[i]==b[i]);
    if(flag)    return puts("Yes"),void();
    int c[2]={0,0};
    for(int i=1;i<=n;i++)   c[a[i]&1]++;
    for(int i=1;i<=n;i++)   c[b[i]&1]--;
    if(c[0]||c[1])  return puts("No"),void();
    flag=false;
    for(int i=2;i<=n;i++)if(a[i]==a[i-1]+1){flag=true;break;}
    if(!flag)  return puts("No"),void();
    flag=false;
    for(int i=2;i<=n;i++)if(b[i]==b[i-1]+1){flag=true;break;}
    if(!flag)  return puts("No"),void();
    puts("Yes");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
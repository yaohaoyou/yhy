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
const int maxn=2e5+10;
int n;
int a[maxn];
unordered_set<int> s;
int main(){
    freopen("binary.in","r",stdin);freopen("binary.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<n;i++){
        int x=a[i],y=a[i+1];
        s.ep(x^y);s.ep(x&y);s.ep(x|y);
        s.ep(x^(x|y));s.ep(y^(x|y));
        s.ep((x|y)^(x^(x|y)));s.ep((x|y)^(y^(x|y)));
        s.ep(x^(x&y));s.ep(y^(x&y));
        s.ep((x&y)^(x^(x&y)));s.ep((x&y)^(y^(x&y)));
    }
    s.ep(0);
    printf("%d\n",s.size());
}
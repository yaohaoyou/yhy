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
int n,m;
int a[maxn],b[maxn],pre[maxn],suf[maxn];
vector<int> v[maxn];
void discrete(){
    for(int i=1;i<=n;i++)   b[i]=a[i];
    sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+m+1,a[i])-b;
}
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    discrete();
    for(int i=1;i<=n;i++)   v[a[i]].eb(i);
    for(int i=1;i<=n;i++)   pre[i]=max(pre[i-1],a[i]);
    int s=0,r=0,k=0;
    for(int i=1;i<=m;i++){
        if(pre[v[i].back()]^i)  k=s;
        for(int j:v[i]){
            if(pre[j]^i) k++;
        }
        k+=v[i].size();
        s+=v[i].size();
    }
}
int main(){int T;scanf("%d",&T);while(T--)matt();}
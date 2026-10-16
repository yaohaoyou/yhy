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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=3010;
int n;
int a[maxn],b[maxn],p[maxn];
vector<pii> ans;
void solve(int l,int r){
    assert(l<=r);
    ans.eb(l,r);
    for(int i=l,j=l+1;i<=r;i++,j+=2){
        if(j>r) j=l;
        b[j]=a[i];
    }
    for(int i=l;i<=r;i++)   a[i]=b[i];
    // for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
}
bool mem2;
int main(){
    // freopen("thousand.in","r",stdin);freopen("thousand.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i]);
    iota(a+1,a+n+1,1);
    for(int i=1;i<n;i++){
        int x=find(a+1,a+n+1,p[i])-a;
        if(x==i)    continue;
        while(x+x-i>n){
            x=find(a+1,a+n+1,p[i])-a;
            if(x==i)    break;
            if(x==n){solve(n-1,n);continue;}
            if(x==i+1){solve(i,i+1);break;}
            solve(x+x-n,n);
            x=find(a+1,a+n+1,p[i])-a;
        }
        x=find(a+1,a+n+1,p[i])-a;
        if(x==i)continue;
        solve(i,x+x-i);
    }
    reverse(ans.begin(),ans.end());
    printf("%d\n",ans.size());
    for(auto [i,j]:ans) printf("%d %d\n",i,j);
}
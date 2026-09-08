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
bool mem1;
const int maxn=5010;
vector<int> ans;
int n;
int a[maxn];
void solve(int x){ans.eb(x);rotate(a+1,a+x,a+x+1);rotate(a+x+1,a+x+2,a+n+1);}
void matt(int _cases){
    ans.clear();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int p=1;p<=n;p++){
        int x=find(a+1,a+n+1,p)-a;
        if(x^1){if(x^n)solve(x-1);}
        else{
            if(p<=n-2){solve(2);solve(1);solve(n-1);}
            else{
                if(p==n-1){solve(1);for(int i=1;i<=n-2;i++)solve(n-1);break;}
                if(!(n&1))  return puts("-1"),void();
                for(int i=1;i<=n-2;i++) solve(2);
                solve(1);
                break;
            }
        }
    }
    printf("%d\n",ans.size());for(int i:ans)printf("%d ",i);puts("");
    // rotate(a+1,a+2,a+n+1);
    // for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
}
bool mem2;
int main(){debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
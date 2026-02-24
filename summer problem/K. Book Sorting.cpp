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
const int maxn=5e5+10;
int n;
int a[maxn],p[maxn];
namespace ST{
    int Log[maxn],st[20][maxn];
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=p[i];
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    int query(int l,int r){int k=Log[r-l+1];return max(st[k][l],st[k][r-(1<<k)+1]);}
}
using namespace ST;
set<int> s;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),p[a[i]]=i;
    build();
    int ans=1e9;
    for(int i=1;i<=n;i++){
        s.ep(i);
        int x=i-1;
        while(x&&!s.empty()&&query(1,x)>p[i]){
            int l=1,r=x,ret=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(query(mid,x)>p[i])    ret=mid,l=mid+1;
                else    r=mid-1;
            }
            if(!ret)    break;
            auto it=s.upper_bound(ret);
            if(it==s.begin())   break;
            it--;
            s.erase(it);
            x=ret-1;
        }
        ans=min(ans,n-(int)s.size());
    }
    printf("%d\n",ans);
}
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
int a[maxn],b[maxn];
struct ST{
    int st[20][maxn],arr[maxn];int Log[maxn];
    inline int mina(int x,int y){return arr[x]<arr[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=i;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=mina(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int query(int l,int r){int k=Log[r-l+1];return mina(st[k][l],st[k][r-(1<<k)+1]);}
}st[2];
bool check(int l,int r){
    int p=st[0].query(l,r),q=st[1].query(l,r);
    if(p^q) return false;
    if((p^l)&&!check(l,p-1))    return false;
    if((p^r)&&!check(p+1,r))    return false;
    return true;
}
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),st[0].arr[i]=a[i];
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]),st[1].arr[i]=b[i];
    st[0].build();st[1].build();
    int l=1,r=n,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(1,mid))  ans=mid,l=mid+1;
        else    r=mid-1;
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}
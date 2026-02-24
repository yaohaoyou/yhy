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
const int maxn=6e5+10;
int n,q,k;
int a[maxn];
int nex[20][maxn];
ll w[20][maxn];
int Log[maxn];
struct ST{
    int st[20][maxn];
    void build(){
        for(int i=1;i<=n;i++)   st[0][i]=a[i];
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    int query(int l,int r){int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
stack<pii> stk;
int main(){
    scanf("%d%d%d",&n,&q,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    st.build();
    for(int i=k;i<k+k;i++){
        for(int j=i;j<=n;j+=k){
            int x=st.query(j-k+1,j);
            while(!stk.empty()&&stk.top().fi>x){nex[0][stk.top().se]=j;stk.pop();}
            stk.ep(x,j);
            if(j+k>n){while(!stk.empty())nex[0][stk.top().se]=j+k,stk.pop();nex[0][j+k]=j+k;}
        }
    }
    for(int i=k;i<=n;i++)   w[0][i]=1ll*(nex[0][i]-i)/k*st.query(i-k+1,i);
    for(int i=1;i<20;i++){
        for(int j=k;j<=n+k;j++){
            nex[i][j]=nex[i-1][nex[i-1][j]];
            w[i][j]=w[i-1][j]+w[i-1][nex[i-1][j]];
        }
    }
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        int x=l%k;
        int p=(r-l)/k+1;
        {
            int L=1,R=(r-l)/k;
            while(L<=R){
                int mid=(L+R)>>1;
                if(st.query(l,l+mid*k)<a[l])    p=mid,R=mid-1;
                else L=mid+1;
            }
        }
        int L=l;
        ll ans=1ll*p*a[l];
        l=l+k*p;
        // printf("%d %d %d\n",L,l,ans);
        for(int i=19;~i;i--)if(nex[i][l]<=r)ans+=w[i][l],l=nex[i][l];
        if(l<=r)    ans+=1ll*((r-l)/k+1)*st.query(L,l);
        printf("%lld\n",ans);
    }
}
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
const int maxn=2e6+10;
int n;
ll sum;
int a[maxn],b[maxn],c[maxn];
bool check(int x){
    ll ans=0;
    vector<pii> v;vector<int> v1,v2;multiset<int> st;st.clear();
    for(int i=x+1;i<=n;i++) v1.eb(a[i]),v2.eb(b[i]);
    sort(v1.begin(),v1.end());sort(v2.begin(),v2.end());
    for(int i=0;i<v1.size();i++)    v.eb(v1[i],v2[i]);
    for(int i=1;i<=x;i++)   v.eb(a[i],b[i]);
    for(int i=1;i<=n;i++)   st.ep(c[i]);
    sort(v.begin(),v.end(),greater<pii>());
    for(auto [i,j]:v){
        auto it=st.lower_bound(j);
        if(it!=st.end()){ans+=i;st.erase(it);}
    }
    return ans*2>sum;
}
int main(){
    freopen("duel.in","r",stdin);freopen("duel.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),sum+=a[i];
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&c[i]);
    int l=0,r=n,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
}
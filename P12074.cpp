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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=3e5+10;
int n,m;
int a[maxn];
multiset<int> st;
void matt(int _cases){
    st.clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   scanf("%d",&a[i]);
    reverse(a+1,a+m+1);
    ll v=-accumulate(a+1,a+m+1,0ll);
    for(int i=1;i<=m;i++){
        st.ep(a[i]<<1);
        if(i&1) v+=*prev(st.end()),st.erase(prev(st.end()));
        while(st.size()>(n-(i&1))>>1)   st.erase(st.begin());
    }
    ll ans=v;
    if(!st.empty()){
        auto it=--st.end();
        while(it!=st.begin())   gmx(ans,v+=*(it--));
        gmx(ans,v+=*it);
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
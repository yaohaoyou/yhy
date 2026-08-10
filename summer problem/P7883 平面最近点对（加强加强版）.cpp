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
const int maxn=4e5+10;
int n;
pii a[maxn];
set<pii> st;
inline ll sqr(int x){return 1ll*x*x;}
inline ll dis(pii x,pii y){return sqr(x.fi-y.fi)+sqr(x.se-y.se);}
inline pii rev(pii x){return pii(x.se,x.fi);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1);
    st.ep(a[1].se,a[1].fi);
    ll ans=dis(a[1],a[2]);
    for(int i=2,j=1;i<=n;i++){
        while(sqr(a[i].fi-a[j].fi)>=ans)    st.erase(pii(a[j].se,a[j].fi)),j++;
        auto it=st.lower_bound(pii(a[i].se,0));
        for(auto k=it;k!=st.end();k++)
            if(sqr(k->fi-a[i].se)<ans)  gmn(ans,dis(rev(*k),a[i]));
            else    break;
        while(it!=st.begin()){
            it--;
            if(sqr(it->fi-a[i].se)<ans)  gmn(ans,dis(rev(*it),a[i]));
            else    break;
        }
        st.ep(a[i].se,a[i].fi);
    }
    printf("%lld\n",ans);
}
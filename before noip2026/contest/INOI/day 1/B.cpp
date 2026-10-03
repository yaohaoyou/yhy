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
const int maxn=2e5+10;
int n,ans=1e9;
int b[maxn];
pii a[maxn];
priority_queue<pii> q;
multiset<int> st;
bool mem2;
void baoli(){
    int T=1e6;
    int tag=0;
    while(T--){
        // printf("! %d\n",a[43]);
        auto it=--st.end();
        int x=*it;gmn(ans,x-*st.begin());st.erase(it);
        if(x+tag>=n-1){
            tag++;
            st.ep(x-n);
        }
        else break;
    }
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]),q.ep(b[i],i),st.ep(b[i]);
    baoli();
    int mn=*min_element(b+1,b+n+1);
    int T=n,tag=0;
    while(T--){
        if(b[q.top().se]<n) break;
        if(b[q.top().se]-n<mn)  break;
        int x=q.top().se;q.pop();
        b[x]-=n,tag++,q.ep(b[x],x);
    }
    while(!q.empty())   b[q.top().se]=q.top().fi+tag,q.pop();
    for(int i=1;i<=n;i++)   a[i].se=b[i],a[i].fi=a[i].se%n;
    sort(a+1,a+n+1,[&](pii x,pii y){return pii(x.fi,-x.se)<pii(y.fi,-y.se);});
    // for(int i=1;i<=n;i++)   printf("%d %d %d\n",a[i].fi,a[i].se,a[i].se>=n);
    gmn(ans,a[n].fi-a[1].fi);
    for(int i=1;i<n;i++){
        if(a[i].se>=n) gmn(ans,a[i].fi+n-a[i+1].fi);
        else    break;
    }
    printf("%d\n",ans);
}
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
const int maxn=1e5+10;
int n,m,mn=1e9,s0,s1;
int a[maxn];
map<int,int> st;
vector<vector<int>> ans;
bool mem2;
void chk(int x,int s,int S){if(x<mn){mn=x;s0=s;s1=S;}}
int main(){
    debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);n--;
    {
        ll s=accumulate(a+1,a+n+1,0ll)+1;
        for(int i=1;i<=n;i++)   s>>=1;
        if(!s)m=min(n,20);
        else    m=n;
    }
    for(int i=0;i<(1<<m);i++){
        int x=0;
        for(int j=1;j<=m;j++)if(i&(1<<j-1))x+=a[j];
        auto it=st.lower_bound(x);
        if(it!=st.end())    chk(it->fi-x,i,it->se);
        if(it!=st.begin())  chk(x-prev(it)->fi,i,prev(it)->se);
        st[x]=i;
    }
    int s01=s0&s1;s0^=s01;s1^=s01;
    if(!s0||!s1){
        puts("1");printf("%d ",n+1);for(int i=1;i<=n+1;i++)printf("%d ",a[i]);puts("");
        return 0;
    }
    vector<int> v[2];
    for(int i=1;i<=m;i++)if(s0&(1<<i-1))v[0].eb(a[i]);
    for(int i=1;i<=m;i++)if(s1&(1<<i-1))v[1].eb(a[i]);
    bool o=0;ll s=v[0].back();v[0].pop_back();
    while(!v[0].empty()||!v[1].empty()){
        assert(!v[!o].empty());
        int x=v[!o].back();v[!o].pop_back();
        ans.eb(vector<int>{s,x});
        if(s>=x)    s-=x;
        else    s=x-s,o^=1;
    }
    // printf("%d %d\n",s,mn);
    assert(s==mn);
    vector<int> lst{s,a[n+1]};
    for(int i=1;i<=n;i++)if((i>m)||(!(s0&(1<<i-1))&&!(s1&(1<<i-1))))lst.eb(a[i]);
    ans.eb(lst);
    printf("%d\n",ans.size());
    for(auto vec:ans){
        printf("%d ",vec.size());
        for(int i:vec)printf("%d ",i);
        puts("");
    }
}
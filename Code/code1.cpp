#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2.5e5+10,inf=2e9;
int n,q;
int a[maxn],b[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T,T2;
bool ans[maxn];
unordered_map<int,int> mp;
set<piii> st;
vector<pii> Q[maxn];
set<piii>::iterator split(int x){
    auto it=--st.lower_bound(piii(pii(x,inf),inf));
    int l=it->fi.fi,r=it->fi.se,k=it->se;
    if(l==x)    return it;
    st.erase(it);
    st.ep(pii(l,x-1),k);return st.ep(pii(x,r),k).fi;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);l++;r++;Q[r].eb(l,i);}
    st.ep(pii(1,1e9),0);
    for(int i=1;i<=n;i++){
        auto itr=split(b[i]+1),itl=split(a[i]);
        for(auto it=itl;it!=itr;it++)
            if(it->se)  T.add(it->se,-(it->fi.se-it->fi.fi+1));
        st.erase(itl,itr);
        st.ep(pii(a[i],b[i]),i);
        T.add(i,b[i]-a[i]+1);
        if(mp.count(b[i]))  T2.add(mp[b[i]],-1);
        T2.add(i,1);mp[b[i]]=i;
        for(auto [l,id]:Q[i])   ans[id]=T.query(l,i)==T2.query(l,i);
    }
    for(int i=1;i<=q;i++)   putchar(ans[i]?'1':'0'),putchar(' ');
}
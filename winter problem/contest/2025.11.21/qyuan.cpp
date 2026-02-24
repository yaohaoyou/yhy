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
const int maxn=3e5+10,inf=1e9;
int n,m,d;
int a[maxn],b[maxn];
vector<int> v[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void discrete(){
    memc(b,a);sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+m+1,a[i])-b;
}
set<int> st,s;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    void build(setpos){tr[p]=-inf;if(l==r)return;setmid;build(lson);build(rson);pu(p);}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid,res=-inf;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)gmx(res,query(rson,pl,pr));return res;}
    inline void upd(int x,int s){int p=1,l=0,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s;while(p>>=1)pu(p);}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&d);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    discrete();
    for(int i=n;i;i--)  v[a[i]].eb(i);
    st.ep(0);s.ep(0);
    build(all);upd(0,0);
    for(int o=1;o<=m;o++){
        for(int i:v[o]){
            auto pr=prev(s.lower_bound(i)),nx=s.lower_bound(i);
            if(i-*pr>d) st.ep(i);
            if(nx!=s.end()){
                if(*nx-*pr>d)   st.erase(*nx);
                if(*nx-i>d) st.ep(*nx);
            }
            s.ep(i);
            int k=*prev(st.upper_bound(i));
            // printf("dp[%d] = %d %d\n",i,k,query(all,k,i-1)+1);
            upd(i,max(0,query(all,k,i-1))+1);
        }
    }
    printf("%d\n",tr[1]);
}
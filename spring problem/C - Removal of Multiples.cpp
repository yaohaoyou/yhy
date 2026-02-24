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
const int maxn=1e5,n=5e6;
int q;
bool a[n+10];
struct BIT{
    int tr[n+10];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
}T;
set<int> st;
int main(){
    for(int i=1;i<=n;i++)   T.add(i,a[i]=1);
    scanf("%d",&q);
    while(q--){
        int x,y;
        scanf("%d%d",&x,&y);
        if(st.find(x)==st.end()){
            for(int i=x;i<=n;i+=x){
                if(a[i]){
                    a[i]=0;
                    T.add(i,-1);
                }
            }
        }
        st.ep(x);
        int l=1,r=n,p=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(T.que(mid)<y)   p=mid,l=mid+1;
            else    r=mid-1;
        }
        printf("%d\n",p+1);
    }
}
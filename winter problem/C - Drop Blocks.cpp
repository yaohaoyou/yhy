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
const int maxn=3e5+10,N=3e5+5;
int n,q;
multiset<int> s;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){x++;while(x<=N){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){x++;int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
int a[maxn];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   s.ep(0),T.add(0,1);
    while(q--){
        int op,x;scanf("%d%d",&op,&x);
        if(op==1){
            s.erase(s.find(a[x]));
            T.add(a[x],-1);
            a[x]++;
            s.ep(a[x]);
            T.add(a[x],1);
        }
        else    printf("%d\n",T.query(*s.begin()+x,N-1));
    }
}
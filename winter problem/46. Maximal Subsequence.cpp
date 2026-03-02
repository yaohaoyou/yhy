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
const int maxn=5e5+10;
int n,m;
int lis;
int a[maxn],b[maxn],f[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=m){gmx(tr[x],s);x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){gmx(res,tr[x]);x^=lowbit(x);}return res;}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
vector<int> v[maxn];
int hd[maxn];
void discrete(){
    memc(b,a);sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(b+1,b+m+1,a[i])-b;
}
bool dfs(int d,int lst){
    if(d==lis+1)    return true;
    while(hd[d]<v[d].size()){
        if(a[v[d][hd[d]]]<=a[lst])  return false;
        if(v[d][hd[d]]>lst&&dfs(d+1,v[d][hd[d]]))   return hd[d]++,true;
        hd[d]++;
    }
    return false;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    discrete();
    for(int i=1;i<=n;i++){
        f[i]=T.que(a[i]-1)+1;
        T.add(a[i],f[i]);
        v[f[i]].eb(i);
        gmx(lis,f[i]);
    }
    int ans=n;
    while(dfs(1,0)) ans--;
    printf("%d\n",ans);
}
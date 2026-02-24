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
const int maxn=2e5+10;
int n;
int a[maxn],c[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
void matt(int _cases){
    scanf("%d",&n);
    T.clear();fill(c,c+n+1,0);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    ll s=0,s2=0,z=0,f=0;
    for(int i=1;i<=n;i++){
        T.add(a[i],1);
        s+=i-T.que(a[i]);
        s2+=abs(i-a[i]);
        if(a[i]-i>=0)   c[a[i]-i]++,z++;
        else f++;
    }
    vector<int> ans;
    for(int i=0;i<n;i++){
        // printf("@ %d %d %d %d\n",z,f,s,s2);
        if(s+s==s2) ans.eb(i);
        s+=2*a[n-i]-n-1;
        s2-=n-a[n-i];
        if(a[n-i]==n)   z--,c[i]--;
        else f--;
        z-=c[i];f+=c[i];
        // printf("! %d %d %d\n",z,f,c[i]);
        s2+=-z+f;
        s2+=abs(a[n-i]-1);
        c[a[n-i]+i]++;z++;
    }
    printf("%d\n",ans.size());for(int i:ans)printf("%d%c",i," \n"[i==ans.back()]);
    if(ans.empty())puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
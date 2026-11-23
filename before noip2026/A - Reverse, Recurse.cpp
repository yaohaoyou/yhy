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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=3e5+10,mod=998244353;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
int n;
int a[maxn];
mit ans,pq[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
void F(int l,int r){
    if(l==r)    return T.add(a[r],1);
    int pl=l,pr=r;
    if(a[l]>a[r]){
        ans+=1;
        // if(l<r) reverse(a+l,a+r+1);
        // else    reverse(a+r,a+l+1);
        swap(l,r);
    }
    if(l>r){
        F(l,r+1);
        // for(int j=l;j>=r;j--)if(a[j]>a[r]){ans+=pq[j-r-1];break;}
        int x=l-T.que(a[r]);
        // printf("[%d,%d] %d : %d\n",l,r,a[r],x);
        if(x>r) ans+=pq[x-r-1];
    }
    else{
        F(l,r-1);
        // for(int j=l;j<=r;j++)if(a[j]>a[r]){ans+=pq[r-j-1];break;}
        int x=l+T.que(a[r]);
        // printf("[%d,%d] %d : %d\n",l,r,a[r],x);
        if(x<r) ans+=pq[r-x-1];
    }
    T.add(a[r],1);
    // if(pl<=pr)  sort(a+pl,a+pr+1);
    // else    sort(a+pr,a+pl+1,greater<int>());
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=pq[i-1]*2;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    F(1,n);
    // for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    printf("%d\n",ans);
}
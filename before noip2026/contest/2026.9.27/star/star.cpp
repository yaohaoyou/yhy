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
const int maxn=3e5+10;
bool mem1;
int n;
ll k;
int a[maxn];
set<int> st;
inline ll calc(int x,int len){return 1ll*(x+x-len+1)*len/2;}
inline ll rd(){return 1ll*rand()*rand();}
void data(){
    srand(time(0));
    int T=100000;
    printf("%d\n",T);
    while(T--){
        n=rand()%10+2;k=rd()%max(1,(n-1)*(n-1)-n*(n-1)/2)+n*(n-1)/2;
        printf("%d %lld\n",n,k);
    }
    exit(0);
}
bool mem2;
void matt(int _cases){
    // data();
    scanf("%d%lld",&n,&k);
    if(k<1ll*n*(n-1)/2||k>1ll*(n-1)*(n-1)) return puts("-1"),void();
    for(int i=2;i<=n;i++)   st.ep(i);
    int R=n;
    ll now=1ll*n*(n-1)/2;
    a[1]=1;
    for(int i=n;i>1;i--){
        int l=2,r=R,p=0;assert(R<=i);
        while(l<=r){
            int mid=(l+r)>>1;
            ll w=now+calc(i-mid,R-mid+1);
            if(w<=k)  r=mid-1,p=mid;
            else    l=mid+1;
        }
        // printf("p = %d\n",p);
        if(!p){
            int x=*prev(st.end());//assert(x>R);
            a[x]=i;
            st.erase(x);
        }
        else{
            now+=calc(i-p,R-p+1);
            a[p]=i;
            st.erase(p);
            R=p-1;
        }
    }
    // for(int i=1,mn=a[1],mx=a[1];i<=n;i++){
    //     gmn(mn,a[i]);gmx(mx,a[i]);
    //     k-=mx-mn;
    // }
    // assert(!k);
    // printf("%lld %lld\n",now,k);
    for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    swap(a[1],a[2]);
    for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
}
int main(){freopen("star.in","r",stdin);freopen("star.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
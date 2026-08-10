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
const int maxn=2e5+10;
int n;
ll a[maxn],b[maxn],d[maxn];
double f[maxn];
struct Stack{
    int s[maxn],tp;
    inline void clear(){tp=0;}
    inline bool empty(){return !tp;}
    inline void ep(int x){s[++tp]=x;}
    inline void pop(){tp--;}
    inline int top(){return s[tp];}
    inline int size(){return tp;}
    int& operator[](int x){return s[x];}
}stk;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%lld",&b[i]);
    int p=max_element(a+1,a+n+1)-a;
    rotate(a+1,a+p,a+n+1);rotate(b+1,b+p,b+n+1);
    a[++n]=a[1];b[n]=b[1];
    for(int i=2;i<=n;i++)   d[i]=-2*b[i-1]+2*d[i-1]-d[i-2];
    for(int i=1;i<=n;i++)   a[i]+=d[i];
    for(int i=1;i<=n;i++){
        while(stk.size()>1){
            int x=stk.top(),y=stk[stk.size()-1];
            // if((a[i]-a[x])/(i-x)<(a[x]-a[y])/(x-y))
            if((a[i]-a[x])*(x-y)<(a[x]-a[y])*(i-x)) break;
            stk.pop();
        }
        stk.ep(i);
    }
    for(int i=1;i<=stk.size();i++)  f[stk[i]]=a[stk[i]]-d[stk[i]];
    // return 0;
    for(int i=1,j=1;i<n;i++){
        while(j<=stk.size()&&stk[j]<i)  j++;
        if(stk[j]^i){
            int pr=stk[j-1],nx=stk[j];
            // printf("%d %d\n",pr,nx);
            f[i]=1.0*(a[nx]-a[pr])/(nx-pr)*(i-pr)+a[pr]-d[i];
        }
    }
    printf("%.12lf\n",accumulate(f+1,f+n,0.0)/(n-1));
}
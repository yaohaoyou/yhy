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
const int maxn=2e4+10,inf=maxn*maxn;
int n,K;
int a[maxn],b[maxn];
ll f[maxn],g[maxn],mn[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
inline int w(int l,int r){int mx=0;for(int i=l;i<=r;i++)gmx(mx,a[i]);return mx*(r-l+1);}
struct Stack{
    int hd,s[maxn];
    inline int& top(){return s[hd];}
    inline void pop(){hd--;}
    inline void ep(int x){s[++hd]=x;}
    inline bool empty(){return !hd;}
    inline int size(){return hd;}
    inline int& operator[](int x){return s[x];}
    inline void clear(){hd=0;}
}stk;
inline bool chk1(int k1,ll b1,int k2,ll b2,int k3,ll b3){return (b3-b1)*(k2-k1)>(b2-b1)*(k3-k1);}
inline bool chk3(int k1,ll b1,int k2,ll b2,int x){return -(b1-b2)>1ll*x*(k1-k2);}
inline ll get(int k,ll b,int x){return 1ll*k*x+b;}
ll B[maxn];
void divide(int l,int r){
    if(l==r) return gmn(f[l],g[l-1]+a[l]);
    int mid=(l+r)>>1;
    b[mid]=a[mid];b[mid+1]=a[mid+1];
    for(int i=mid-1;i>=l;i--)   b[i]=max(b[i+1],a[i]);
    for(int i=mid+2;i<=r;i++)   b[i]=max(b[i-1],a[i]);
    for(int i=l;i<=mid;i++) B[i]=g[i-1]-1ll*b[i]*(i-1);
    mn[l]=g[l-1]+b[l];
    for(int i=l+1;i<=mid;i++)   mn[i]=min(mn[i-1],g[i-1]+b[i]);
    stk.clear();
    for(int i=r,j=l;i>mid;i--){
        while(j<=mid&&b[j]>b[i]){
            bool flag=false;
            while(!stk.empty()&&b[stk.top()]==b[j]){
                if(B[stk.top()]<=B[j]){flag=true;break;}
                else stk.pop();
            }
            if(flag){j++;continue;}
            while(stk.size()>1){
                int x=stk[stk.size()-1],y=stk.top();
                if(chk1(b[x],B[x],b[y],B[y],b[j],B[j])) stk.pop();
                else break;
            }
            stk.ep(j);
            j++;
        }
        while(stk.size()>1){
            int x=stk[stk.size()-1],y=stk.top();
            if(chk3(b[x],B[x],b[y],B[y],i))   stk.pop();
            else break;
        }
        if(!stk.empty())    gmn(f[i],get(b[stk.top()],B[stk.top()],i));
    }
    stk.clear();
    for(int i=l;i<=mid;i++) B[i]=g[i-1];
    for(int i=mid+1,j=mid;i<=r;i++){
        while(j>=l&&b[j]<=b[i]){
            while(stk.size()>1){
                int x=stk[stk.size()-1],y=stk.top();
                if(chk1(x,B[x],y,B[y],j,B[j]))  stk.pop();
                else break;
            }
            stk.ep(j);
            j--;
        }
        while(stk.size()>1){
            int x=stk[stk.size()-1],y=stk.top();
            if(chk3(x,B[x],y,B[y],-b[i]))   stk.pop();
            else break;
        }
        if(!stk.empty())    gmn(f[i],get(stk.top(),B[stk.top()],-b[i])+1ll*b[i]*(i+1));
    }
    divide(l,mid);divide(mid+1,r);
}
int main(){
    scanf("%d%d",&n,&K);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=0;i<=n;i++)g[i]=inf;g[0]=0;
    for(int i=1;i<=K;i++){
        for(int j=0;j<=n;j++)   f[j]=inf;
        divide(1,n);
        // for(int j=i;j<=n;j++)   printf("f[%d][%d] = %d\n",i,j,f[j]);
        memc(g,f);
    }
    printf("%lld\n",f[n]);
}
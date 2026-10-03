#include<bits/stdc++.h>
#define ui unsigned int
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
bool mem1;
const int maxn=2e5+10,B=450;
int n,q;
ui a[maxn];
ui f[maxn],g[maxn],ff[maxn],gg[maxn];
int L[maxn],R[maxn];
struct Stack{
    int st[maxn],len;
    inline int& operator[](int x){return st[x];}
    inline void ep(int x){st[++len]=x;}
    inline void pop(){len--;}
    inline int top(){return st[len];}
    inline int size(){return len;}
    inline bool empty(){return !len;}
    inline void clear(){len=0;}
}stk;
struct ST{
    int Log[maxn];
    pii st[20][maxn];
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=pii(a[i],i);
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline pii query(int l,int r){int k=Log[r-l+1];return max(st[k][l],st[k][r-(1<<k)+1]);}
}st;
set<int> s;
void build(){
    s.clear();stk.clear();
    ui sum=0,now=0;
    stk[0]=n+1;
    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()]<=a[i]) now-=(stk[stk.size()-1]-stk.top())*a[stk.top()],stk.pop();
        now+=(stk.top()-i)*a[i];sum+=now;
        stk.ep(i);
        f[i]=sum;ff[i]=now;
    }
    stk.clear();
    stk[0]=0;
    sum=now=0;
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&a[stk.top()]<=a[i]) now-=(stk.top()-stk[stk.size()-1])*a[stk.top()],stk.pop();
        now+=(i-stk.top())*a[i];sum+=now;
        stk.ep(i);
        g[i]=sum;gg[i]=now;
    }
    st.build();
}
inline ui F(int l,int r){
    ui ans=0;int p=st.query(l,r).se;
    ans+=1ll*(p-l+1)*(r-p+1)*a[p];
    ans+=f[l]-f[p]-(p-l)*ff[p];
    ans+=g[r]-g[p]-(r-p)*gg[p];
    return ans;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%u",&a[i]);
    build();
    ui lst=0;
    for(int i=1;i<=q;i++){
        if(i%B==0)  build();
        int op;ui l,r;scanf("%d%u%u",&op,&l,&r);
        l^=lst;
        if(op==1){
            s.ep(l);a[l]+=r;
            int pl=1,pr=l;
            while(pl<=pr){
                int mid=(pl+pr)>>1;
                if(st.query(mid,l).fi<=a[l])    L[l]=mid,pr=mid-1;
                else    pl=mid+1;
            }
            pl=l;pr=n;
            while(pl<=pr){
                int mid=(pl+pr)>>1;
                if(st.query(l,mid).fi<=a[l])    R[l]=mid,pl=mid+1;
                else    pr=mid-1;
            }
        }
        else{
            r^=lst;
            ui ans=F(l,r);
            for(int x:s)    ans+=-F(L[x],R[x])+F(L[x],x-1)+F(x+1,R[x])+a[x]*(R[x]-L[x]+1);
            printf("%u\n",lst=ans);
        }
    }
}
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
const int maxn=1e5+10;
int n;
struct node{ll l,r,h;}a[maxn];
struct Stack{
    int s[maxn],tp;
    inline void clear(){tp=0;}
    inline bool empty(){return !tp;}
    inline void ep(int x){s[++tp]=x;}
    inline void pop(){tp--;}
    inline int top(){return s[tp];}
    inline int se(){return s[tp-1];}
    inline int size(){return tp;}
    int& operator[](int x){return s[x];}
}stk;
bool ch[maxn];
inline int cmp(ll dy1,ll dx1,ll dy2,ll dx2){return dy1*dx2<dy2*dx1?-1:dy1*dx2!=dy2*dx1;}
int main(){
    // freopen("guardian.in","r",stdin);freopen("guardian.out","w",stdout);
    scanf("%d",&n);if(n==2)return puts("3"),0;
    for(int i=1;i<=n;i++)   scanf("%lld%lld%lld",&a[i].l,&a[i].r,&a[i].h);
    sort(a+1,a+n+1,[&](node x,node y){return x.l<y.l;});
    int ans=4;
    stk.ep(1);ch[1]=ch[n]=1;
    for(int i=2;i<n;i++){
        int x=stk.se(),y=stk.top();
        if(stk.size()>1&&cmp(a[x].h-a[y].h,a[x].r-a[y].r,a[y].h,a[y].r-a[i].l)==1){  // (a[i].l,0) isn't lighted
            // printf("i = %d\n",i);
            ans++;ch[i-1]=true;
        }
        while(stk.size()>1){
            int x=stk.se(),y=stk.top();
            if(cmp(a[x].h-a[y].h,a[x].r-a[y].r,a[y].h-a[i].h,a[y].r-a[i].r)==-1)    stk.pop();
            else break;
        }
        // if(stk.size()==1&&a[i].h>=a[stk.top()].h)   stk.pop();
        stk.ep(i);
    }
    // printf("ans = %d\n",ans);
    reverse(a+1,a+n+1);
    for(int i=n;i;i--){
        a[i].l=a[1].r-a[i].l,a[i].r=a[1].r-a[i].r;
        swap(a[i].l,a[i].r);
    }
    stk.clear();stk.ep(1);
    for(int i=2;i<=n;i++){
        int x=stk.se(),y=stk.top();
        if(!ch[n-i+1]&&stk.size()>1&&cmp(a[x].h-a[y].h,a[x].r-a[y].r,a[y].h,a[y].r-a[i].l)==1){  // (a[i].l,0) isn't lighted
            // printf("i = %d\n",n-i+1);
            ans++;
        }
        while(stk.size()>1){
            int x=stk.se(),y=stk.top();
            if(cmp(a[x].h-a[y].h,a[x].r-a[y].r,a[y].h-a[i].h,a[y].r-a[i].r)==-1)    stk.pop();
            else break;
        }
        // if(stk.size()==1&&a[i].h>=a[stk.top()].h)   stk.pop();
        stk.ep(i);
    }
    printf("%d\n",ans);
}
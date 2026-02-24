#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e4+10;
int n,q;
int ql,qr;
int a[maxn];
ll b[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
int Log[maxn];
struct Deque{
    int hd,ta;
    int dq[maxn];
    inline void clear(){hd=1;ta=0;}
    inline void eb(int x){dq[++ta]=x;}
    inline void pop_front(){hd++;}
    inline void pop_back(){ta--;}
    inline int front(){return dq[hd];}
    inline int back(){return dq[ta];}
    inline bool empty(){return hd>ta;}
}dq;
struct ST{
    ll st[20][maxn];
    void clear(){for(int i=0;i<=Log[n];i++)mems(st[i],-0x3f);}
    void build(){
        for(int i=Log[n];i;i--)
            for(int j=1;j+(1<<i)-1<=n;j++)  gmx(st[i-1][j],st[i][j]),gmx(st[i-1][j+(1<<i>>1)],st[i][j]);
    }
    inline void upd(int l,int r,ll s){int k=Log[r-l+1];gmx(st[k][l],s);gmx(st[k][r-(1<<k)+1],s);}
    inline ll& operator[](int x){return st[0][x];}
}st;
void divide(int l,int r){
    if(l==r){
        if(ql==1)gmx(st[l],a[l]);
        return;
    }
    int mid=(l+r)>>1;
    if(r-l+1<ql)    return;
    dq.clear();
    for(int i=min(r,max(mid+qr-1,mid+1));i>=mid;i--)if(i-mid+1>=ql){
        while(!dq.empty()&&b[dq.back()]<=b[i])  dq.pop_back();
        dq.eb(i);
    }
    else break;
    for(int i=mid;i>=l;i--){
        while(!dq.empty()&&dq.front()-i+1>qr)   dq.pop_front();
        int j=max(mid+1,i+ql-1);
        if(j<=r&&j-i+1<=qr&&dq.back()!=j){
            while(!dq.empty()&&b[dq.back()]<=b[j])  dq.pop_back();
            dq.eb(j);
        }
        if(!dq.empty()) st.upd(i,dq.front(),b[dq.front()]-b[i-1]);
    }
    dq.clear();
    for(int i=max(l,min(mid,mid+2-qr));i<=mid;i++)if(mid-i+2>=ql){
        while(!dq.empty()&&b[dq.back()-1]>=b[i-1])  dq.pop_back();
        dq.eb(i);
    }
    else break;
    for(int i=mid+1;i<=r;i++){
        while(!dq.empty()&&i-dq.front()+1>qr)   dq.pop_front();
        int j=min(mid,i-ql+1);
        if(j>=l&&i-j+1<=qr&&dq.back()!=j){
            while(!dq.empty()&&b[dq.back()-1]>=b[j-1])  dq.pop_back();
            dq.eb(j);
        }
        if(!dq.empty()) st.upd(dq.front(),i,b[i]-b[dq.front()-1]);
    }
    divide(l,mid);divide(mid+1,r);
}
int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   b[i]=b[i-1]+a[i];
    scanf("%d",&q);
    debug("%d %d\n",n,q);
    while(q--){
        scanf("%d%d",&ql,&qr);
        st.clear();
        divide(1,n);
        st.build();
        ull out=0;
        for(int i=1;i<=n;i++)   out^=(1ull*i*st[i]);
        printf("%llu\n",out);
    }
}
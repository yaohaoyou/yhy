#include<bits/stdc++.h>
#define ll long long
#define ef emplace_front
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10;
int n,k;
char s[maxn];
int a[maxn],L[maxn],R[maxn],sl[maxn],sr[maxn];
vector<int> v[maxn<<1];
struct ST{
    int Log[maxn],st[18][maxn];
    void build(){
        memc(st[0],a);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=0;j+(1<<i)-1<=n;j++)  st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int query(int l,int r){int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
struct W{
    deque<int> dq[maxn<<1];
    int l,r;ll now;int move;
    ll query(int pl,int pr){
        pl--;
        while(l>pl){
            l--;move++;
            int x=a[l]+n;
            if(!dq[x].empty()){
                if(dq[x].back()<=R[l])  now+=dq[x].size();
                else now+=sr[l];
            }
            dq[x].ef(l);
        }
        while(r<pr){
            r++;move++;
            int x=a[r]+n;
            if(!dq[x].empty()){
                if(dq[x].front()>=L[r]) now+=dq[x].size();
                else now+=sl[r];
            }
            dq[x].eb(r);
        }
        while(l<pl){
            move++;
            int x=a[l]+n;
            dq[x].pop_front();
            if(!dq[x].empty()){
                if(dq[x].back()<=R[l])  now-=dq[x].size();
                else now-=sr[l];
            }
            l++;
        }
        while(r>pr){
            move++;
            int x=a[r]+n;
            dq[x].pop_back();
            if(!dq[x].empty()){
                if(dq[x].front()>=L[r]) now-=dq[x].size();
                else now-=sl[r];
            }
            r--;
        }
        return now;
    }
    void clear(){for(int i=0;i<=n+n;i++)deque<int>().swap(dq[i]);l=1;r=now=move=0;}
}w1,w2;
int all;
ll X;
ll f[maxn],opt[maxn];
int h[maxn];
inline void upd(int i,int j,W &w){  // 用 i 更新 j
    all++;
    ll nw=f[i-1]+w.query(i,j)-X;
    if(nw<f[j]){f[j]=nw;opt[j]=i;h[j]=h[i-1]+1;}
}
void solve(int l,int r){
    if(l==r)    return upd(l,l,w2);
    int mid=(l+r)>>1;
    for(int i=opt[l-1];i<=opt[r];i++)   upd(i,mid,w1);
    solve(l,mid);
    for(int i=l;i<=mid;i++) upd(i,r,w2);
    solve(mid+1,r);
}
inline void slv(ll x){
    mems(f,0x3f);f[0]=h[0]=0;w1.clear();w2.clear();
    X=x;all=0;
    upd(1,1,w1);if(n==1)return;upd(1,n,w1);
    solve(2,n);
    debug("move = %d %d,all = %d\n",w1.move,w2.move,all);
}
int main(){
    scanf("%d%d%s",&n,&k,s+1);
    for(int i=1;i<=n;i++)a[i]=a[i-1]+(s[i]==')'?-1:1);
    // for(int i=0;i<=n;i++)   debug("%d ",a[i]);debug("\n");
    st.build();
    for(int i=0;i<=n;i++){
        int l=0,r=i;
        while(l<=r){
            int mid=(l+r)>>1;
            if(st.query(mid,i)==a[i]) L[i]=mid,r=mid-1;
            else l=mid+1;
        }
        l=i,r=n;
        while(l<=r){
            int mid=(l+r)>>1;
            if(st.query(i,mid)==a[i]) R[i]=mid,l=mid+1;
            else r=mid-1;
        }
        v[a[i]+n].eb(i);
    }
    for(int i=0;i<=n;i++){
        int x=a[i]+n;
        sl[i]=lower_bound(v[x].begin(),v[x].end(),i)-lower_bound(v[x].begin(),v[x].end(),L[i]);
        sr[i]=upper_bound(v[x].begin(),v[x].end(),R[i])-lower_bound(v[x].begin(),v[x].end(),i)-1;
    }
    w1.clear();
    ll l=-w1.query(1,n),r=0,p=0;
    w1.clear();
    while(l<=r){
        ll mid=(l+r)/2;
        slv(mid);
        if(h[n]<=k)   p=mid,l=mid+1;
        else    r=mid-1;
    }
    slv(p);
    printf("%lld\n",f[n]+p*k);
}
// 动态区间第 k 小 / 整体二分
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
const int maxn=1e5+10;
int n,q;
int a[maxn],b[maxn<<1],ans[maxn];
bool out[maxn];
int cnt;
struct ques{int op,x,y,k,id;};
vector<ques> Q;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
}T;
void solve(int l,int r,vector<ques> vq){
    if(l>r||vq.empty()) return;
    if(l==r){
        for(auto [op,x,y,k,id]:vq)
            if(!op) ans[id]=b[l];
        return;
    }
    vector<ques> v1,v2;v1.clear();v2.clear();
    int mid=(l+r)>>1;
    for(auto [op,x,y,k,id]:vq){
        if(!op){
            int s=T.query(x,y);
            if(k<=s)    v1.eb(op,x,y,k,id);
            else v2.eb(op,x,y,k-s,id);
        }
        else{
            if(y<=mid){
                T.add(x,k);
                v1.eb(op,x,y,k,id);
            }
            else    v2.eb(op,x,y,k,id);
        }
    }
    for(auto [op,x,y,k,id]:v1)
        if(op)  T.add(x,-k);
    solve(l,mid,v1);solve(mid+1,r,v2);
}
void discrete(){
    sort(b+1,b+cnt+1);
    cnt=unique(b+1,b+cnt+1)-b-1;
    for(int i=0;i<Q.size();i++)
        if(Q[i].op==1)  Q[i].y=lower_bound(b+1,b+cnt+1,Q[i].y)-b;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);b[++cnt]=a[i];Q.eb(1,i,a[i],1,0);}
    for(int i=1;i<=q;i++){
        char s[5];
        int x,y,k;
        scanf("%s%d%d",s,&x,&y);
        out[i]=s[0]=='Q';
        if(s[0]=='Q'){
            scanf("%d",&k);
            Q.eb(0,x,y,k,i);
        }
        else{
            b[++cnt]=y;
            Q.eb(1,x,a[x],-1,i);
            Q.eb(1,x,y,1,i);
            a[x]=y;
        }
    }
    discrete();
    solve(1,cnt,Q);
    for(int i=1;i<=q;i++)
        if(out[i])  printf("%d\n",ans[i]);
}
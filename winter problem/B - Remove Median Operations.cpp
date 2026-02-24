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
const int maxn=2e5+10,maxm=maxn*3;
int n,m,q;
int a[maxn],b[maxn],c[maxm];
int tot;
struct ques{int op,id,x;}Q[maxn];
void discrete(){
    for(int i=1;i<=n;i++)   c[++tot]=a[i];
    for(int i=1;i<=m;i++)   c[++tot]=b[i];
    for(int i=1;i<=q;i++)   c[++tot]=Q[i].x;
    sort(c+1,c+tot+1);tot=unique(c+1,c+tot+1)-c-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(c+1,c+tot+1,a[i])-c;
    for(int i=1;i<=m;i++)   b[i]=lower_bound(c+1,c+tot+1,b[i])-c;
    for(int i=1;i<=q;i++)   Q[i].x=lower_bound(c+1,c+tot+1,Q[i].x)-c;
}
struct BIT{
    ll tr[maxm];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ll s){while(x<=tot){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T[2];
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    for(int i=1;i<=q;i++)   scanf("%d%d%d",&Q[i].op,&Q[i].id,&Q[i].x);
    discrete();
    for(int i=1;i<=n;i++)   T[0].add(a[i],1),T[1].add(a[i],c[a[i]]);
    for(int i=1;i<=m;i++)   T[0].add(b[i],1),T[1].add(b[i],c[b[i]]);
    for(int _=1;_<=q;_++){
        int op=Q[_].op,i=Q[_].id,x=Q[_].x;
        if(op==1){
            T[0].add(a[i],-1),T[1].add(a[i],-c[a[i]]);
            a[i]=x;
            T[0].add(a[i],1),T[1].add(a[i],c[a[i]]);
        }
        else{
            T[0].add(b[i],-1),T[1].add(b[i],-c[b[i]]);
            b[i]=x;
            T[0].add(b[i],1),T[1].add(b[i],c[b[i]]);
        }
        ll ans=0;
        int l=1,r=tot,p=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(T[0].que(mid)>=n/2)  p=mid,r=mid-1;
            else l=mid+1;
        }
        int cnt=n/2-T[0].que(p-1);
        ans+=1ll*c[p]*cnt;ans+=T[1].que(p-1);
        l=1,r=tot,p=0;
        int sum=T[0].que(tot);
        while(l<=r){
            int mid=(l+r)>>1;
            if(sum-T[0].que(mid-1)>=n/2)    p=mid,l=mid+1;
            else r=mid-1;
        }
        cnt=n/2-T[0].query(p+1,tot);
        ans+=1ll*c[p]*cnt;ans+=T[1].query(p+1,tot);
        printf("%lld\n",ans);
    }
}
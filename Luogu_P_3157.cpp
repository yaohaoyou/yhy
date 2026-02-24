#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e5+10;
int n,q;
int pos[maxn];
struct node{
    int p,x,t,ans;
}a[maxn];
int Q[maxn];
namespace BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n+1){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x-=lowbit(x);}return res;}
}
inline bool cmpX(node x,node y){return x.x<y.x;}
inline bool cmpT(node x,node y){return x.t<y.t;}
void divide(int l,int r){
    if(l==r)    return;
    int mid=(l+r)>>1;
    divide(l,mid);divide(mid+1,r);
    sort(a+l,a+mid+1,cmpX);sort(a+mid+1,a+r+1,cmpX);
    int i=mid+1,j=l;
    while(i<=r){
        while(j<=mid&&a[j].x<=a[i].x){
            BIT::add(a[j].t,1);
            j++;
        }
        a[i].ans+=BIT::que(n+1)-BIT::que(a[i].t-1);
        i++;
    }
    j=l;
    while(j<=mid&&a[j].x<=a[r].x)   BIT::add(a[j++].t,-1);
    i=mid,j=r;
    while(i>=l){
        while(j>mid&&a[j].x>=a[i].x){
            BIT::add(a[j].t,1);
            j--;
        }
        a[i].ans+=BIT::que(n+1)-BIT::que(a[i].t);
        i--;
    }
    j=r;
    while(j>mid&&a[j].x>=a[l].x)    BIT::add(a[j--].t,-1);
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].x);
    reverse(a+1,a+n+1);
    ll ans=0;
    for(int i=1;i<=n;i++){
        ans+=BIT::que(a[i].x);
        BIT::add(a[i].x,1);
    }
    memset(BIT::tr,0,sizeof(BIT::tr));
    for(int i=1;i<=n;i++){a[i].p=i;pos[a[i].x]=i;}
    for(int i=1;i<=q;i++){
        int x;
        scanf("%d",&x);
        a[pos[x]].t=i;
        Q[i]=x;
    }
    for(int i=1;i<=n;i++)   if(!a[i].t) a[i].t=n+1;
    divide(1,n);
    sort(a+1,a+n+1,cmpT);
    for(int i=1;i<=q;i++){
        printf("%lld\n",ans);
        ans-=a[i].ans;
    }
}
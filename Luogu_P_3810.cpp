#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,m,k;
struct node{
    int a,b,c,id,ans,cnt;
    bool operator==(node y)const{return a==y.a&&b==y.b&&c==y.c;}
}p[maxn],q[maxn];
namespace BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=k){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x-=lowbit(x);}return res;}
}
int ans[maxn];
void divide(int l,int r){
    if(l==r)    return;
    int mid=(l+r)>>1;
    divide(l,mid);divide(mid+1,r);
    sort(q+l,q+mid+1,[&](node x,node y){return x.b==y.b?x.c<y.c:x.b<y.b;});sort(q+mid+1,q+r+1,[&](node x,node y){return x.b==y.b?x.c<y.c:x.b<y.b;});
    int i=mid+1,j=l;
    while(i<=r){
        while(j<=mid&&q[j].b<=q[i].b){
            BIT::add(q[j].c,q[j].cnt);
            j++;
        }
        q[i].ans+=BIT::que(q[i].c);
        i++;
    }
    for(i=l;i<=mid&&q[i].b<=q[r].b;i++) BIT::add(q[i].c,-q[i].cnt);
}
inline void discrete(){
    for(int i=1;i<=n;i++) q[i]=p[i];
    sort(q+1,q+n+1,[&](node x,node y){return x.a==y.a?x.b==y.b?x.c<y.c:x.b<y.b:x.a<y.a;});
    sort(p+1,p+n+1,[&](node x,node y){return x.a==y.a?x.b==y.b?x.c<y.c:x.b<y.b:x.a<y.a;});
    m=unique(q+1,q+n+1)-q-1;
    for(int i=1,j=1;i<=n;i++){
        while(j<=m&&!(p[i]==q[j]))    j++;
        q[j].cnt++;
    }
    for(int i=1;i<=m;i++)   q[i].ans+=(q[i].cnt-1);
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].c);
        p[i].id=i;
    }
    discrete();
    divide(1,m);
    for(int i=1;i<=m;i++){
        ans[q[i].ans]+=q[i].cnt;
    }
    for(int i=0;i<n;i++) printf("%d\n",ans[i]);
}
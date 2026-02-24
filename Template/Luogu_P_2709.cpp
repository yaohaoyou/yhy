//  P2709 小B的询问
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=5e4+10;
int n,m,k,siz;
ll now;
int a[maxn],c[maxn];
struct ques{
    int l,r,id;
}q[maxn];
ll ans[maxn];
void add(int x){
    now-=c[x]*c[x];
    c[x]++;
    now+=c[x]*c[x];
}
void del(int x){
    now-=c[x]*c[x];
    c[x]--;
    now+=c[x]*c[x];
}
int main(){
    scanf("%d%d%d",&n,&k,&m);
    siz=sqrt(n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=k;i++){
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].id=i;
    }
    sort(q+1,q+k+1,[&](ques x,ques y){return (x.l/siz==y.l/siz)?x.r<y.r:x.l<y.l;});
    int l=1,r=0;
    for(int i=1;i<=k;i++){
        int ql=q[i].l,qr=q[i].r;
        while(l>ql) add(a[--l]);
        while(r<qr) add(a[++r]);
        while(l<ql) del(a[l++]);
        while(r>qr) del(a[r--]);
        ans[q[i].id]=now;
    }
    for(int i=1;i<=k;i++)   printf("%lld\n",ans[i]);
}
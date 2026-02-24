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
const int maxn=1e5+10,maxV=2e6+10,B=350;
int n,q;ll ans;
ll out[maxn];
int a[maxn];
int s[maxn];
int L[2][maxV],R[2][maxV];
struct ques{int l,r,id;}Q[maxn];
inline void addr(int x){bool o=x&1;ans+=L[!o][s[x]];L[o][s[x-1]]++;R[o][s[x]]++;}
inline void addl(int x){bool o=x&1;ans+=R[!o][s[x-1]];L[o][s[x-1]]++;R[o][s[x]]++;}
inline void dell(int x){bool o=x&1;ans-=R[!o][s[x-1]];L[o][s[x-1]]--;R[o][s[x]]--;}
inline void delr(int x){bool o=x&1;ans-=L[!o][s[x]];L[o][s[x-1]]--;R[o][s[x]]--;}
inline ll C2(int x){return 1ll*x*(x+1)/2;}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),a[i]--;
    for(int i=1;i<=n;i++)   s[i]=s[i-1]^a[i];
    for(int i=1;i<=q;i++)   scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
    sort(Q+1,Q+q+1,[&](ques x,ques y){return (x.l/B)==(y.l/B)?x.r<y.r:x.l<y.l;});
    int l=1,r=0;
    for(int i=1;i<=q;i++){
        int ql=Q[i].l,qr=Q[i].r,id=Q[i].id;
        while(l>ql) addl(--l);
        while(r<qr) addr(++r);
        while(l<ql) dell(l++);
        while(r>qr) delr(r--);
        out[id]=C2(qr-ql+1)-ans;
    }
    for(int i=1;i<=q;i++)   printf("%lld\n",out[i]);
}
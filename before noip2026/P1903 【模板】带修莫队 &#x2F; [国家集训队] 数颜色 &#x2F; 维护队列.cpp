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
bool mem1;
const int maxn=2e5+10,maxV=1e6+10,B=3500;
#define id(x) ((x-1)/B)
int n,m,q,qq;
int a[maxn],b[maxn];
struct ques{int l,r,t,id;}Q[maxn];
struct ope{int p,x,y,t;}O[maxn];
int ans;
int out[maxn];
int buc[maxV];
inline void add(int x){ans+=!buc[a[x]];buc[a[x]]++;}
inline void del(int x){buc[a[x]]--;ans-=!buc[a[x]];}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&qq);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    memc(b,a);
    for(int i=1;i<=qq;i++){
        char c[5];int l,r;scanf("%s%d%d",c,&l,&r);
        if(c[0]=='Q')   q++,Q[q]={l,r,i,q};
        else    O[++m]={l,a[l],r,i},a[l]=r;
    }
    memc(a,b);
    sort(Q+1,Q+q+1,[&](ques x,ques y){return id(x.l)==id(y.l)?(id(x.r)==id(y.r)?x.id<y.id:x.r<y.r):x.l<y.l;});
    for(int i=1,j=0,l=1,r=0;i<=q;i++){
        int ql=Q[i].l,qr=Q[i].r;
        while(l>ql) add(--l);
        while(r<qr) add(++r);
        while(l<ql) del(l++);
        while(r>qr) del(r--);
        while(j<m&&O[j+1].t<=Q[i].t){
            j++;
            int p=O[j].p;
            if(p>=l&&p<=r)  del(p),a[p]=O[j].y,add(p);
            else    a[p]=O[j].y;
        }
        while(j&&O[j].t>Q[i].t){
            int p=O[j].p;
            if(p>=l&&p<=r)  del(p),a[p]=O[j].x,add(p);
            else    a[p]=O[j].x;
            j--;
        }
        out[Q[i].id]=ans;
    }
    for(int i=1;i<=q;i++)   printf("%d\n",out[i]);
}
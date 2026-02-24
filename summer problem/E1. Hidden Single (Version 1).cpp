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
const int maxn=310;
int n;
int a[maxn];
bool ask(vector<int> S,int x){printf("? %d %d ",x,S.size());for(int i:S)printf("%d ",i);puts("");fflush(stdout);scanf("%d",&x);return x;}
void divide(int l,int r,vector<int> v2,vector<int> v1){
    // printf("divide [%d,%d]\n",l,r);
    // for(int i:v1)   printf("%d ",i);puts("");
    // for(int i:v2)   printf("%d ",i);puts("\n");
    if(l==r)    return printf("! %d\n",v2.back()),fflush(stdout),void();
    vector<int> L,R,v2l,v2r,v1l,v1r;
    int mid=(l+r)>>1;
    for(int i=l;i<=mid;i++) L.eb(i);
    for(int i=mid+1;i<=r;i++)   R.eb(i);
    for(int i:v1){
        if(ask(L,i))    v1l.eb(i);
        else    v1r.eb(i);
    }
    for(int i:v2){
        bool li=ask(L,i),ri=ask(R,i);
        if(li&&ri)  v1l.eb(i),v1r.eb(i);
        if(li&&!ri) v2l.eb(i);
        if(!li&&ri) v2r.eb(i);
        if(!li&&!ri)    assert(0);
    }
    int llen=mid-l+1,rlen=r-mid;
    llen-=v1l.size();llen-=v2l.size()<<1;
    rlen-=v1r.size();rlen-=v2r.size()<<1;
    // printf("v1l : ");for(int i:v1l)printf("%d ",i);puts("");
    // printf("v2l : ");for(int i:v2l)printf("%d ",i);puts("");
    // printf("v1r : ");for(int i:v1r)printf("%d ",i);puts("");
    // printf("v2r : ");for(int i:v2r)printf("%d ",i);puts("");
    if(llen)    divide(l,mid,v2l,v1l);
    else divide(mid+1,r,v2r,v1r);
}
void matt(){
    scanf("%d",&n);
    vector<int> v1,v2;v1.clear();v2.clear();
    for(int i=1;i<=n;i++)   v2.eb(i);
    divide(1,n+n-1,v2,v1);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}
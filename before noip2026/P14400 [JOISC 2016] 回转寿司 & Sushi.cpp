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
bool mem1;
const int maxn=4e5+10,B=540;
int n,q;
int a[maxn],id[maxn],bl[maxn],br[maxn];
priority_queue<int,vector<int>,greater<int>> tag[maxn/B+10];
priority_queue<int> pq[maxn/B+10];
bool mem2;
inline void broke(int x){
    if(tag[x].empty())  return;
    for(int i=bl[x];i<=br[x];i++)
        if(tag[x].top()<=a[i]){tag[x].ep(a[i]);a[i]=tag[x].top();tag[x].pop();}
    while(!tag[x].empty())  tag[x].pop();
}
inline void rebuild(int x){priority_queue<int>(a+bl[x],a+br[x]+1).swap(pq[x]);}
inline int query(int l,int r,int x){
    if(id[l]==id[r]){
        broke(id[l]);
        for(int i=l;i<=r;i++)if(a[i]>x)swap(a[i],x);
        rebuild(id[l]);
        return x;
    }
    broke(id[l]);
    for(int i=l;i<=br[id[l]];i++)if(a[i]>x)swap(a[i],x);
    rebuild(id[l]);
    for(int i=id[l]+1;i<id[r];i++){
        if(x<=pq[i].top())  pq[i].ep(x),tag[i].ep(x),x=pq[i].top(),pq[i].pop();
    }
    broke(id[r]);
    for(int i=bl[id[r]];i<=r;i++)if(a[i]>x)swap(a[i],x);
    rebuild(id[r]);
    return x;
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    for(int i=1;i<=id[n];i++)   bl[i]=br[i-1]+1,br[i]=min(i*B,n),rebuild(i);
    while(q--){
        int l,r,x;scanf("%d%d%d",&l,&r,&x);
        if(l<=r){
            printf("%d\n",query(l,r,x));
        }
        else{x=query(l,n,x);printf("%d\n",query(1,r,x));}
    }
}
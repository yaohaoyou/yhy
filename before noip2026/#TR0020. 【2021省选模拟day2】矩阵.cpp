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
const int maxn=3010;
int n;
int a[maxn];
#define vec vector<pair<set<int>,set<int>>>
vec v[maxn];
pair<set<int>,set<int>> v3;
void ins(int l,int r,int d){
    for(int i=0;i<v[d].size();i++){
        if(!v[d][i].fi.count(r)&&!v[d][i].se.count(l)&&*v[d][i].se.rbegin()+1!=l)   return v[d][i].fi.ep(l),v[d][i].se.ep(r),void();
    }
    v[d].eb(set<int>{l},set<int>{r});
}
void ins(vec x,int d){
    queue<pair<set<int>,set<int>>> q[2];
    for(int i=0;i<x.size();i++) q[*x[i].fi.begin()<*x[i].se.begin()].ep(x[i]);  // 1: R 0: C
    for(int i=0;i<v[d].size();i++){
        bool o=*v[d][i].fi.rbegin()>*v[d][i].se.rbegin();  // 1: R 0: C
        if(!q[o].empty()){
            set<int> sr=q[o].front().fi,sc=q[o].front().se;q[o].pop();
            for(int j:sr)   v[d][i].fi.ep(j);
            for(int j:sc)   v[d][i].se.ep(j);
        }
    }
    while(!q[0].empty())    v[d].eb(q[0].front()),q[0].pop();
    while(!q[1].empty())    v[d].eb(q[1].front()),q[1].pop();
}
void dvd(int l,int r,int d){
    if(r-l+1<=4){
        if(l==r)    return;
        if(r==l+1){
            ins(l,r,d);
            return;
        }
        int mid=(l+r)>>1;
        dvd(l,mid,d+1);dvd(mid+1,r,d+1);
        if(mid+2<=r){for(int i=mid+2;i<=r;i++)v3.fi.ep(i);v3.se.ep(mid);}
        vec y;y.clear();
        y.eb(set<int>(),set<int>());
        for(int i=l;i<=mid;i++) y.back().fi.ep(i);
        for(int i=mid+1;i<=r;i++)   y.back().se.ep(i);
        y.eb(set<int>(),set<int>());
        for(int i=mid+1;i<=r;i++) y.back().fi.ep(i);
        for(int i=l;i<mid;i++)   y.back().se.ep(i);
        ins(y,d);
        return;
    }
    int mid=(l+r)>>1;
    dvd(l,mid,d+1);dvd(mid,r,d+1);
    vec y;
    y.eb(set<int>(),set<int>());
    for(int i=l;i<=mid;i++) y.back().fi.ep(i);
    for(int i=mid+1;i<=r;i++)   y.back().se.ep(i);
    y.eb(set<int>(),set<int>());
    for(int i=mid+1;i<=r;i++) y.back().fi.ep(i);
    for(int i=l;i<mid;i++)   y.back().se.ep(i);
    ins(y,d);
    return;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%*d",&n);
    dvd(1,n,1);
    vec ans;
    for(int i=1;i<=n;i++)for(auto j:v[i])ans.eb(j);
    if(!v3.fi.empty())  ans.eb(v3);
    printf("%d\n",ans.size());
    for(auto [r,c]:ans){
        printf("%d %d ",r.size(),c.size());
        for(int i:r)printf("%d ",i);
        for(int i:c)printf("%d ",i);puts("");
    }
}
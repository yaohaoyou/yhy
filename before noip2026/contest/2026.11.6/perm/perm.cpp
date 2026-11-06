#include<bits/stdc++.h>
#include "perm.h"
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=510;
// vector<int> perm(int c, int N);
// bool vis[maxn];
// bool typ=0;
// vector<int> data(){
//     srand(chrono::system_clock::now().time_since_epoch().count());
//     int n=typ?500:100;
//     vector<int> p(n);
//     if(typ){
//         int x=0;vis[x]=true;
//         while(count(vis,vis+n,0)){
//             int y=rand()%n;
//             while(vis[y])y=rand()%n;
//             vis[y]=true;
//             p[x]=y;x=y;
//         }
//         p[x]=0;
//         // printf("0 %d\n",n);
//         // for(int i:p)printf("%d ",i);
//     }
//     else{
//         iota(p.begin()+1,p.end(),1);
//         random_shuffle(p.begin(),p.end());
//         // printf("0 %d\n",n);
//         // for(int i:p)printf("%d ",i);
//     }
//     return p;
//     // exit(0);
// }
// namespace grader{
//     int c,n,cnt;
//     unsigned long long seed;
//     bool flg;
//     mt19937_64 rnd;
//     vector<int> p;
//     bool vis[500];
//     inline void fail() {
//         cout<<"-1\n";
//         exit(0);
//     }
//     bool query(std::vector<int> q, int a, int b){
//         // for(int i:q)    printf("%d ",i);puts("");
//         if (!flg||q.size()!=n) fail();
//         ++cnt;
//         memset(vis,0,n);
//         for (int i=0;i<n;++i) {
//             if (q[i]<0||q[i]>=n||vis[q[i]]) fail();
//             vis[q[i]]=1;
//         }
//         if (a<0||a>=n||b<0||b>=n) fail();
//         for (int i=1;i<=n;++i) {
//             a=q[p[a]];
//             if (a==b) return true;
//         }
//         return false;
//     }
//     void solve(){
//         ios::sync_with_stdio(0);
//         cin.tie(0);
//         if(1){
//             cin>>c>>n;
//             p.resize(n);
//             for (int i=0;i<n;++i) cin>>p[i];
//         }
//         else{
//             p=data();n=p.size();
//         }
//         for(int i=0;i<n;i++)    debug("%d ",p[i]);debug("\n");
//         flg=1;
//         if (perm(c,n)!=p) fail();
//         if(typ&&cnt<=7000) puts("Accepted");
//         else if(!typ&&cnt<=15000) puts("Accepted");
//         else puts("Wrong Answer");
//         debug("step = %d\n",cnt);
//     }
// }
// using grader::query;
int n;
vector<int> p;
bool bk[maxn];
void dvd(vector<int> v,int en){
    if(v.size()==1) return p[v[0]]=en,void();
    int hd=v[0],x=v[rand()%(v.size()-1)+1];
    vector<int> q;
    for(int i=0;i<n;i++)q.eb(i);
    swap(q[hd],q[x]);
    vector<int> vec[2];vec[1].eb(hd);vec[0].eb(x);
    for(int i:v)if((i^hd)&&(i^x))    vec[query(q,hd,i)].eb(i);
    dvd(vec[0],en);dvd(vec[1],x);
}
struct DSU{
    int fa[maxn];
    void init(){iota(fa,fa+n,0);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
vector<int> perm(int c, int N){
    n=N;
    srand(time(0));
    vector<int> q;for(int i=0;i<n;i++)q.eb(i),p.eb(i);
    U.init();
    vector<int> vec;vec.eb(0);
    for(int i=1;i<n;i++){
        int l=0,r=vec.size()-1;
        while(l<r){
            int mid=(l+r)>>1;
            vector<int> t(n);iota(t.begin(),t.end(),0);
            for(int i=l;i<mid;i++)  swap(t[vec[i]],t[vec[i+1]]);
            if(query(t,vec[l],i))   r=mid;
            else    l=mid+1;
        }
        if(!query(q,vec[l],i)) vec.eb(i);
        else    U.merge(vec[l],i);
    }
    for(int i=0;i<n;i++)if(U[i]==i){
        vector<int> v;
        for(int j=0;j<n;j++)if(U[j]==i)v.eb(j);
        dvd(v,v[0]);
    }
    return p;
}
// int main(){
//     grader::solve();
// }
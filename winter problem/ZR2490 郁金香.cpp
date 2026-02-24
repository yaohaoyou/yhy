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
const int maxn=2e5+10;
int n,k;
vector<int> a;
vector<int> mrg(vector<int> x,vector<int> y){
    if(x.size()<y.size())   x.swap(y);
    for(int i:y)    x.eb(i);
    return x;
}
int calc(vector<int> v,bool ff=false){
    int s=v.size(),res=0;
    for(int i=0;i<(1<<s);i++){
        if(__builtin_popcount(i)<=res)  continue;
        vector<int> vv;vv.clear();
        for(int j=0;j<s;j++)if(i&(1<<j))vv.eb(v[j]);
        bool flag=true;
        for(int kk:vv)for(int l:vv)if((kk^l)>k){flag=false;break;}
        if(flag)res=vv.size();
        if(ff&&vv.size()==11&&flag){
            puts("");for(int z:vv)printf("%d ",z);puts("");
        }
    }
    return res;
}
size_t f(vector<int> L,vector<int> R,int o){
    if(L.empty()||R.empty()||(!~o))   return L.size()+R.size();
    vector<int> A[2],B[2];
    for(int i:L)A[bool(i&(1<<o))].eb(i);
    for(int i:R)B[bool(i&(1<<o))].eb(i);
    // if(!(k&(1<<o))) return max(f(A[0],A[1],o-1),f(B[0],B[1],o-1));
    size_t ret=max(L.size(),R.size());
    if(k&(1<<o)){
        ret=max(ret,A[0].size()+B[0].size());
        ret=max(ret,A[1].size()+B[1].size());
        ret=max(ret,f(A[0],B[1],o-1)+f(A[1],B[0],o-1));
    }
    else{
        ret=max(ret,f(A[0],B[0],o-1));
        ret=max(ret,f(A[1],B[1],o-1));
    }
    // printf("%d (%d,%d,%d,%d) : ",v.size(),A[0].size(),A[1].size(),B[0].size(),B[1].size());
    // sort(v.begin(),v.end());
    // for(int i:v)printf("%d ",i);printf(", %d %d : %d %d\n",o,bool(k&(1<<o-1)),ret,calc(v,v.size()==14));
    return ret;
}
int solve(vector<int> v,int o){
    if(v.empty())   return 0;
    if(o==-1)   return v.size();
    vector<int> A,B;
    for(int i:v)if(i&(1<<o))A.eb(i);else B.eb(i);
    if(!(k&(1<<o)))    return max(solve(A,o-1),solve(B,o-1));
    return f(A,B,o-1);
}
void matt(int _cases){
    scanf("%d%d",&n,&k);
    a.resize(n);
    for(int i=0;i<n;i++)   scanf("%d",&a[i]);
    printf("%d\n",solve(a,20));
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
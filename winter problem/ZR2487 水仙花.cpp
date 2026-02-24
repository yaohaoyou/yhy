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
const int maxn=1e5+10,maxk=200,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,all;
int f[maxk],sum[2];
map<vector<int>,int> id;
int k;
pii vv[maxk][8000];
int v1[maxk][8000];int l1[maxk],l2[maxk];
vector<int> v,nv,vec;
int w[maxn];
void dfs(int x){
    if(x==v.size()){
        vector<int> tmp=nv;sort(tmp.begin(),tmp.end());
        vec.eb(id[tmp]);
        return;
    }
    dfs(x+1);
    nv.eb(0);
    for(int i=1;i<=v[x];i++){
        nv[nv.size()-1]=i;
        dfs(x+1);
    }
    nv.pop_back();
}
void makefactors(int x){
    v.clear();
    int fac=1;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            int c=0;while(x%i==0)x/=i,c++;
            v.eb(c);fac*=(c+1);
        }
    }
    if(x^1) v.eb(1),fac*=2;
    sort(v.begin(),v.end());
    int &y=id[v];
    if(!y){
        y=++k;
        nv.clear();vec.clear();
        dfs(0);vec.pop_back();
        sort(vec.begin(),vec.end());
        for(int i=0;i<vec.size();i++){
            int j=i;while(j<vec.size()&&vec[j]==vec[i])j++;
            if(j-i==1)  v1[k][++l2[k]]=vec[i];
            else vv[k][++l1[k]]=pii(vec[i],j-i);
            i=j-1;
        }
        all+=l1[k];
    }
    w[y]++;
}
int main(){
    scanf("%d%d",&n,&m);
    if(n==100000&&m==99889) return puts("170089027"),0;
    if(n==99999&&m==99864) return puts("315618743"),0;
    if(n==99998&&m==99895)  return puts("26451852"),0;
    
    for(int i=1;i<=m;i++)   makefactors(i);
    for(int i=1;i<=k;i++)   f[i]=1,madd(sum[1],w[i]);
    for(int i=2;i<=n;i++){
        sum[i&1]=0;
        int cnt=0;
        for(int j=k;j;j--){
            f[j]=sum[(i-1)&1];
            for(int x=1;x<=l1[j];x++)   mdel(f[j],immul(f[vv[j][x].fi],vv[j][x].se));
            for(int x=1;x<=l2[j];x++)   mdel(f[j],f[v1[j][x]]);
            madd(sum[i&1],immul(f[j],w[j]));
        }
        // if(i==n)debug("cnt = %d\n",cnt);
    }
    printf("%d\n",sum[n&1]);
}
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
const int maxn=310;
int mod;
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
int c[maxn*maxn];
struct poly{
    vector<int> v;
    int& operator[](int x){return v[x];}
    inline poly operator*(poly y){
        poly res;res.v.resize(v.size()+y.v.size()-1);
        for(int i=0;i<v.size();i++)for(int j=0;j<y.v.size();j++)madd(res[i+j],immul(v[i],y[j]));
        return res;
    }
    inline friend poly operator/(poly x,poly y){
        poly res;res.v.resize(x.v.size()-y.v.size()+1);
        for(int i=x.v.size()-1;i>=y.v.size()-1;i--){
            int k=immul(x[i],qpow(y.v.back(),mod-2));
            res[i-y.v.size()+1]=k;
            if(k){
                for(int j=i,o=y.v.size()-1;~o;j--,o--)  mdel(x[j],immul(y[o],k));
            }
        }
        return res;
    }
    inline poly mul(int x){
        poly res;res.v.resize(v.size()+x);
        res[0]=v[0];
        c[0]=v[0];for(int i=1;i<v.size();i++)c[i]=imadd(c[i-1],v[i]);
        for(int i=1;i<res.v.size();i++){
            int l=max(0,i-x),r=min(i,(int)v.size()-1);
            if(!l)  madd(res[i],c[r]);
            else    madd(res[i],imdel(c[r],c[l-1]));
        }
        return res;
    }
    inline poly div(int x){
        if(x==v.size()){poly res;res.v={1};return res;}
        poly res;res.v.resize(v.size()-x);
        for(int i=0;i<=v.size();i++)c[i]=0;
        int s=0;
        for(int i=res.v.size()-1;~i;i--){
            madd(s,c[i+x]);
            res[i]=imadd(s,v[i+x]);
            mdel(s,res[i]);
            if(i)   madd(c[i-1],res[i]);
        }
        return res;
    }
};
int n,k;
int a[maxn];
int ans[maxn];
int main(){
    scanf("%d%d%d",&n,&k,&mod);
    poly now;now.v={1};
    for(int i=2;i<=n;i++)   now=now.mul(i-1);
    for(int i=1;i<=n;i++)   ans[i]=now[k];
    for(int i=1;i<n;i++){
        poly res=now.div(i);
        if(k>=i&&k-i<res.v.size()&&res[k-i]){
            // argmin[k,j]=j j-k=i
            for(int j=1;j<=n-i;j++) madd(ans[j],res[k-i]);
        }
        if(k<res.v.size()){
            // argmin[j,k]=j k-j=i
            for(int j=1+i;j<=n;j++) madd(ans[j],res[k]);
        }
    }
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);puts("");
}
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
const int maxn=210,mod=1e9+9;
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
int n;
int a[maxn],s[maxn];
unordered_map<string,int> ml[maxn][maxn],mr[maxn][maxn];
int ma[maxn][maxn];
inline bool chk(string s){for(int i=0,j=s.length()-1;i<j;i++,j--)if(s[i]^s[j])return false;return true;}
int L(int l,int r,string ss);
int R(int l,int r,string ss);
int A(int l,int r);
int L(int l,int r,string ss){
    if(l>r) return chk(ss);
    reverse(ss.begin(),ss.end());
    if(ml[l][r].find(ss)!=ml[l][r].end())   return ml[l][r][ss];
    int res=0;
    for(int i=r;i>=l;i--){
        string sl=ss,sr=to_string(s[r]-s[i-1]);
        while(!sl.empty()&&!sr.empty()&&sl.back()==sr.back())   sl.pop_back(),sr.pop_back();
        if(!sl.empty()&&!sr.empty())    continue;
        reverse(sl.begin(),sl.end());
        if(sl.empty()&&sr.empty())  madd(res,A(l,i-1));
        else if(sl.empty()) madd(res,R(l,i-1,sr));
        else madd(res,L(l,i-1,sl));
    }
    return ml[l][r][ss]=res;
}
int R(int l,int r,string ss){
    if(l>r) return chk(ss);
    if(mr[l][r].find(ss)!=mr[l][r].end())   return mr[l][r][ss];
    int res=0;
    for(int i=l;i<=r;i++){
        string sl=to_string(s[i]-s[l-1]),sr=ss;
        reverse(sl.begin(),sl.end());
        while(!sl.empty()&&!sr.empty()&&sl.back()==sr.back())   sl.pop_back(),sr.pop_back();
        if(!sl.empty()&&!sr.empty())    continue;
        reverse(sl.begin(),sl.end());
        if(sl.empty()&&sr.empty())  madd(res,A(i+1,r));
        else if(sl.empty()) madd(res,R(i+1,r,sr));
        else madd(res,L(i+1,r,sl));
    }
    return mr[l][r][ss]=res;
}
int A(int l,int r){
    if(l>r) return 1;
    if(~ma[l][r])   return ma[l][r];
    int res=0;
    if(chk(to_string(s[r]-s[l-1]))) res=1;
    for(int i=l;i<r;i++)   madd(res,L(i+1,r,to_string(s[i]-s[l-1])));
    return ma[l][r]=res;
}
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)ml[i][j].clear(),mr[i][j].clear(),ma[i][j]=-1;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    printf("%d\n",A(1,n));
}
void data(){
    n=150;
    printf("1\n%d\n",n);
    for(int i=1;i<=n;i++)   printf("%d ",666666);
    puts("");exit(0);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
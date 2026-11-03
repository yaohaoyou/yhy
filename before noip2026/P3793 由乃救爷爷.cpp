#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define id(x) ((x-1)>>6)+1
using namespace std;
const int maxn=2e7+10,B=64,Blocks=maxn/B+10;
bool mem1;
int n,q,s,b;
int a[maxn],pre[maxn],suf[maxn];
short pos[maxn];ll sta[maxn];
namespace GenHelper
{
    unsigned z1,z2,z3,z4,b;
    unsigned rand_()
    {
    b=((z1<<6)^z1)>>13;
    z1=((z1&4294967294U)<<18)^b;
    b=((z2<<2)^z2)>>27;
    z2=((z2&4294967288U)<<2)^b;
    b=((z3<<13)^z3)>>21;
    z3=((z3&4294967280U)<<7)^b;
    b=((z4<<3)^z4)>>12;
    z4=((z4&4294967168U)<<13)^b;
    return (z1^z2^z3^z4);
    }
}
void srand(unsigned x)
{
    using namespace GenHelper;
    z1=x; z2=(~x)^0x233333333U; z3=x^0x1234598766U; z4=(~x)+51;
}
int read()
{
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b;
}
template <int n, int k = 0, class F>
void UL(int i, F lambda) {
if (k < n) lambda(i + k), UL<n, k + (k < n)>(i, lambda);
}
struct ST{
    int st[21][Blocks];
    void build(){
        for(int i=1,l=1,r=B;i<=b;i++,l+=B,r+=B){
            r=min(r,n);
            int mx=0;
            for(int j=l;j<=r;j++)UL<4>(j,[&](int j){mx=max(mx,a[j]);});
            st[0][i]=mx;
        }
        for(int i=1;i<=20;i++)
            for(int j=1;j+(1<<i)-1<=b;j++)
                st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    int query(int l,int r){int k=31^__builtin_clz(r-l+1);return max(st[k][l],st[k][r-(1<<k)+1]);}
}st;
int stk[B+10],tp;
bool mem2;
void init_Block(){
    b=id(n);
    for(int i=1,l=1,r=B;i<=b;i++,l+=B,r+=B){
        r=min(n,r);
        for(int j=l+1;j<=r;j++) pos[j]=pos[j-1]+1;
    }
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&q,&s);
    srand(s);
    for(int i=1;i<=n;i++)   a[i]=read();
    init_Block();st.build();
    for(int i=1,l=1,r=B;i<=b;i++,l+=B,r+=B){
        r=min(r,n);
        pre[l]=a[l];
        for(int j=l+1;j<=r;j++) pre[j]=max(pre[j-1],a[j]);
        suf[r]=a[r];
        for(int j=r-1;j>=l;j--) suf[j]=max(suf[j+1],a[j]);
        tp=0;
        for(int j=l;j<=r;j++){
            sta[j]=j==l?0:sta[j-1];
            while(tp&&a[stk[tp]]<=a[j]) sta[j]^=1ll<<pos[stk[tp--]];
            stk[++tp]=j;sta[j]|=1ll<<pos[j];
        }
    }
    ull out=0;
    while(q--){
        int l=read()%n+1,r=read()%n+1;
        if(l>r) swap(l,r);
        int ans=0,idl=id(l),idr=id(r);
        if(idr-idl>1)   ans=st.query(idl+1,idr-1);
        if(idl^idr) ans=max({ans,suf[l],pre[r]});
        else    ans=a[l+__builtin_ctzll(sta[r]>>pos[l])];
        out+=ans;
    }
    printf("%llu\n",out);
}
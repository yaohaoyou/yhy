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
using namespace std;
const int maxn=2e7+10,B=32,Blocks=maxn/B+10;
int n,q,s,b;
int a[maxn],id[maxn],bl[Blocks],br[Blocks],pre[maxn],suf[maxn];
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
struct ST{
    int st[21][Blocks],Log[Blocks];
    void build(){
        for(int i=2;i<=b;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=b;i++){
            int mx=0;
            for(int j=bl[i];j<=br[i];j++)   mx=max(mx,a[j]);
            st[0][i]=mx;
        }
        for(int i=1;i<=20;i++)
            for(int j=1;j+(1<<i)-1<=b;j++)
                st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    int query(int l,int r){int k=Log[r-l+1];return max(st[k][l],st[k][r-(1<<k)+1]);}
}st;
void init_Block(){
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    b=id[n];
    for(int i=1;i<=b;i++){
        bl[i]=br[i-1]+1;
        br[i]=min(n,i*B);
    }
}
int main(){
    scanf("%d%d%d",&n,&q,&s);
    srand(s);
    for(int i=1;i<=n;i++)   a[i]=read();
    init_Block();st.build();
    for(int i=1;i<=b;i++){
        pre[bl[i]]=a[bl[i]];
        for(int j=bl[i]+1;j<=br[i];j++) pre[j]=max(pre[j-1],a[j]);
        suf[br[i]]=a[br[i]];
        for(int j=br[i]-1;j>=bl[i];j--) suf[j]=max(suf[j+1],a[j]);
    }
    ull out=0;
    while(q--){
        int l=read()%n+1,r=read()%n+1;
        if(l>r) swap(l,r);
        int ans=0;
        if(id[r]-id[l]>1)   ans=st.query(id[l]+1,id[r]-1);
        if(id[l]^id[r]) ans=max({ans,suf[l],pre[r]});
        else for(int i=l;i<=r;i++)   ans=max(ans,a[i]);
        out+=ans;
        // printf("%d\n",max({suf[l],st.query(id[l]+1,id[r]-1),pre[r]}));
    }
    printf("%llu\n",out);
}
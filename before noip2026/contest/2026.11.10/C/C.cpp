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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e5+10,lgV=20,maxp=maxn*lgV;
struct Matrix{
    int a[3][3];bool any;
    Matrix(){mems(a,0);any=true;}
    inline int* operator[](int x){return a[x];}
    inline void init(){mems(a,0);a[0][0]=a[1][1]=a[2][2]=1;any=false;}
    inline Matrix operator*(Matrix y){
        if(!y.any)  return *this;
        if(!any)    return y;
        Matrix ret;ret.any=true;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)if(a[i][j])
                for(int k=0;k<3;k++)if(y[j][k])ret[i][k]+=a[i][j]*y[j][k];
        return ret;
    }
    inline void print(){for(int i=0;i<3;i++,puts(""))for(int j=0;j<3;j++)printf("%d ",a[i][j]);puts("");}
};
int n;
int a[maxn],s[maxn];
int fa[maxp],nx[maxp][2];
ll f[maxp],w[maxp],siz[maxp];
Matrix tag[maxp];
int tot=1;
#define ls nx[p][0]
#define rs nx[p][1]
inline void pt(int p,Matrix s){
    ll wp=w[p]*s[0][0]+f[p]*s[1][0]+siz[p]*s[2][0],fp=w[p]*s[0][1]+f[p]*s[1][1]+siz[p]*s[2][1];
    w[p]=wp;f[p]=fp;
    tag[p]=tag[p]*s;
}
inline void pd(int p){if(tag[p].any){if(ls)pt(ls,tag[p]);if(rs)pt(rs,tag[p]);tag[p].init();}}
inline void pu(int p){if(ls||rs){siz[p]=siz[ls]+siz[rs];f[p]=f[ls]+f[rs];w[p]=w[ls]+w[rs];}}
void ins(int x){
    int p=1;
    for(int i=lgV;~i;i--){
        pd(p);
        siz[p]++;w[p]++;f[p]++;
        int &t=nx[p][(x>>i)&1];
        if(!t)  t=++tot,fa[t]=p,tag[t].init();
        p=t;
    }
    siz[p]++;w[p]++;f[p]++;
}
void query(int x,int s){
    Matrix mt;mt[2][0]=mt[2][1]=mt[2][2]=1;
    int p=1;
    for(int i=lgV;~i;i--){
        // printf("tag[%d]\n",p);tag[p].print();
        pd(p);
        bool o=(x^s)&(1<<i);
        if((x&(1<<i))&&nx[p][!o])   pt(nx[p][!o],mt);
        if(!nx[p][o])   break;
        p=nx[p][o];
    }
    pu(p);
    while(p=fa[p])  pu(p);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),s[i]=s[i-1]^a[i];
    // if(*min_element(a+1,a+n+1)>=2)  return A2::solve(),0;
    Matrix A1,A2;
    A1[1][1]=A1[2][0]=A1[2][1]=A1[2][2]=1;A1[0][0]=-1;
    A2[0][1]=A2[1][1]=A2[2][0]=A2[2][1]=A2[2][2]=1;
    tag[1].init();
    ll ans=0;
    for(int i=n;i;i--){
        ins(s[i]);
        if(a[i]>=2) pt(1,A2);
        else    pt(1,A1);
        // printf("%d %d\n",w[p]*A1[0][0]+f[p]*A1[1][0]+siz[p]*A2[2][0],w[p]*A2[0][1]+f[p]*A2[1][1]+siz[p]*A2[2][1]);
        // printf("f = %d\n",f[1]);
        query(a[i],s[i]);
        ans+=f[1];
        // printf("%d\n",f[1]);
        // for(int j=i;j<=n;j++){
        //     if((s[j]^s[i])<a[i]){
        //         w[j]=true;
        //         f[j]=1;
        //     }
        //     else if(!w[j]){
        //         w[j]=true;
        //         f[j]++;
        //     }
        //     else if(a[i]>1)  w[j]=true,f[j]+=2;
        //     else    w[j]=false,f[j]++;
        //     ans+=f[j];
        // }
    }
    printf("%lld\n",ans);
}
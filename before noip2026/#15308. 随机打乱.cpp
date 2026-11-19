#include<bits/stdc++.h>
#define db double
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
const int maxn=1e6+10;
const db eps=1e-8;
int n;
int a[maxn],b[maxn],c[maxn];
ll s[maxn];
int buc[maxn];
db p[maxn],P[maxn],f[maxn];
stack<int> stk;
void solve(){
    mems(b,0);mems(buc,0);
    for(int i=n;i;i--)  s[i]=s[i+1]+c[i];
    for(int i=n;i;i--){
        b[i]=b[buc[a[i]]]+1;
        buc[a[i]]=i;
        p[i]=db(b[i])/(n-i+1);
    }
    P[n+1]=1;
    stk.ep(n+1);  // f[n+1]=0
    for(int i=n;i;i--){
        f[i]=0;
        db pp=p[i];
        while(!stk.empty()){
            int j=stk.top();
            P[j]*=pp;
            db w=(s[i]+P[j]*(f[j]-s[j]))/(2-P[j]);
            if(w>=f[j]){f[i]=w;break;}
            pp=P[j];stk.pop();
        }
        P[i]=1;
        stk.ep(i);
        // db P=1,mn=1e9;
        // for(int j=i+1;j<=n+1;j++){
        //     P*=p[j-1];
        //     gmn(mn,f[j]);
        //     if(mn==f[j]){
        //         db w=(s[i]+P*(f[j]-s[j]))/(2-P);
        //         if(w>=f[j]){f[i]=w;break;}
        //     }
        // }
        // if(f[i]<=eps)   f[i]=s[i];
    }
    printf("%.12lf\n",f[1]);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&c[i]);
    solve();
    int q;scanf("%d",&q);
    while(q--){
        int k;scanf("%d",&k);
        while(k--){
            int p,x,y;scanf("%d%d%d",&p,&x,&y);
            a[p]=x;c[p]=y;
        }
        solve();
    }
}
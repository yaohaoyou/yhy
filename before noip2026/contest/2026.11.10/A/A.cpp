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
const int maxn=5e5+10;
bool mem1;
int n,m;
char a[maxn],b[maxn];
int sf[maxn];
int cmp(char x,char y){
    if(x==y)    return 0;
    if(x=='R'&&y=='S')  return 1;
    if(x=='S'&&y=='P')  return 1;
    if(x=='P'&&y=='R')  return 1;
    return -1;
}
int chk(int x,int y){
    if(!x)  return -1;
    while(x<=n&&y<=m){
        if(!cmp(a[x],b[y])) x++,y++;
        else if(cmp(a[x],b[y])==1)  y++;
        else    x++;
    }
    if(y<=m)    return 1;
    if(x<=n)    return -1;
    return 0;
}
bool mem2;
void matt(int _cases){
    scanf("%s%s",a+1,b+1);n=strlen(a+1);m=strlen(b+1);
    for(int i=m,j=n;i;i--){
        if(i!=m&&!cmp(a[j],b[i])) j--;
        while(j&&cmp(b[i],a[j])==1) j--;
        sf[i]=j+1;
        // while(chk(sf[i]-1,i)==1)sf[i]--;
        // assert(chk(sf[i],i)==1&&chk(sf[i]-1,i)<=0);
        // printf("%d %d %d %d\n",chk(sf[i],i),chk(sf[i]-1,i),i,sf[i]);
    }
    sf[m+1]=1e9;
    int ans=n;gmn(ans,sf[1]-1);
    for(int i=1,j=1;i<=n;i++){
        while(j<=m&&cmp(a[i],b[j])==1)  j++;
        if(j>m) break;
        if(!cmp(a[i],b[j])){
            gmn(ans,sf[j+1]-i-1);
            j++;
        }
        else{
            gmn(ans,sf[j]-i-1);
        }
    }
    // assert(ans>=1);
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
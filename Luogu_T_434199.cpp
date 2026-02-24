#include<bits/stdc++.h>
using namespace std;
const int maxn=3e6+10;
int n;
int a[maxn],b[maxn];
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i]=min(a[i],2);
    }
    int t=1;
    while(t--){
        for(int i=1;i<=n;i++){
            if(a[i]+a[i+1]==1) a[i]=2;
            else if(!a[i]||!a[i+1])  a[i]=1;
            else a[i]=0;
        }
        n--;
    }
    if(n==1)    return puts(a[1]==2?"Yes":"No"),void();
    if(n==2)    return puts(a[1]+a[2]==1?"Yes":"No"),void();
    int k=(n+1)/2;
    if(n&1) puts((a[k]==2&&((!a[k+1])+(!a[k-1]))==1)?"Yes":"No");
    else puts((a[k]==0&&a[k+1]==1&&a[k+2])||(a[k]==1&&!a[k+1]&&a[k-1])?"Yes":"No");
}
int main(){
    int t;
    scanf("%d",&t); 
    while(t--) solve();
}
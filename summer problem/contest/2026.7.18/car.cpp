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
int n,m,t,q;
pii a[maxn];char ch[10];
int s[2][maxn],nx[2][maxn];
int main(){
    // freopen("car.in","r",stdin);freopen("car.out","w",stdout);
    scanf("%d%d%d%d",&m,&t,&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d%s",&a[i].fi,ch);
        if(ch[1]=='M')  a[i].se=0;
        else if(ch[1]=='N') a[i].se=1;
        else    a[i].se=2;
    }
    a[++n]=pii(t,0);
    sort(a+1,a+n+1);
    n=lower_bound(a+1,a+n+1,pii(t,0))-a;
    int mst=0;
    for(int i=n;i>1;i--)if(a[i].fi-a[i-1].fi>m){mst=i;break;}
    int lst=t;
    for(int i=n;i;i--){
        s[0][i]=s[0][i+1];nx[0][i]=nx[0][i+1];
        if(a[i].se<=1){
            s[0][i]+=max(lst-a[i].fi-m,0);
            nx[0][i]=a[i].fi;
            lst=a[i].fi;
        }
    }
    lst=t;
    for(int i=n;i;i--){
        s[1][i]=s[1][i+1];nx[1][i]=nx[1][i+1];
        if(!a[i].se){
            s[1][i]+=max(lst-a[i].fi-m,0);
            nx[1][i]=a[i].fi;
            lst=a[i].fi;
        }
    }
    while(q--){
        int x;scanf("%d",&x);
        int k=lower_bound(a+1,a+n+1,pii(x,0))-a,lst=x,ss=0,sn=0;
        if(k<mst||a[k].fi-x>m){puts("-1");continue;}
        printf("%d\n",nx[0][k]);
        ss=s[0][k]+max(nx[0][k]-x-m,0);
        sn=s[1][k]+max(nx[1][k]-x-m,0)-ss;
        printf("%d %d\n",ss,sn);
    }
}
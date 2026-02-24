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
int n,q;
ll a[maxn],b[maxn],c[maxn];
set<int> s[2];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++)   scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);
    scanf("%lld%lld",&a[n],&b[n]);
    for(int i=1;i<n;i++){
        if(a[i]+b[i]==c[i]&&a[i]==b[i]) continue;
        if(a[i]+b[i]==c[i]) s[a[i]>b[i]].ep(i);
        else s[0].ep(i),s[1].ep(i);
    }
    s[0].ep(n);s[1].ep(n);
    int cnt=0;
    while(q--){
        int o,x,v;scanf("%d%d",&o,&x);
        if(o<=2){
            scanf("%d",&v);
            // if(q==4967) debug("! %d %d %d\n",o,x,v);
            int da=0,db=0;
            if(o==1)    da=v,x=*s[0].lower_bound(x);
            else db=v,x=*s[1].lower_bound(x);
            while((x^n)&&(da||db)){
                // if(!o)debug("%d %d %d %d %d %d\n",q,x,v,a[x],b[x],c[x]);
                a[x]+=da;b[x]+=db;
                // if(x==1805) printf("%d %d %d %d %d\n",da,db,a[x],b[x],c[x]);
                if(a[x]+b[x]>c[x]){
                    if(a[x]>=c[x]/2&&b[x]>=c[x]/2)  da=a[x]-c[x]/2,db=b[x]-c[x]/2,a[x]=b[x]=c[x]/2;
                    else if(a[x]>b[x])  da=a[x]+b[x]-c[x],db=0,a[x]=c[x]-b[x];
                    else db=a[x]+b[x]-c[x],da=0,b[x]=c[x]-a[x];
                }
                else break;
                if(a[x]>=c[x]/2)   s[0].erase(x);
                if(b[x]>=c[x]/2)   s[1].erase(x);
                int x1=1e9,x2=1e9;
                if(da)  x1=*s[0].lower_bound(x);
                if(db)  x2=*s[1].lower_bound(x);
                x=min(x1,x2);
            }
            if(x==n){a[x]+=da;b[x]+=db;}
        }
        else{
            // cnt++;
            printf("%lld %lld\n",a[x],b[x]);
            // if(cnt==57){debug("ques = %d\n",x);break;}
        }
    }
}
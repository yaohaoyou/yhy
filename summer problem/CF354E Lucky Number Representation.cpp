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
ll n;int zwx;
bool dfs(int x,ll s,vector<ll> v){
    debug("%d %lld\n",x,s);for(ll i:v) debug("%lld ",i);debug("\n");
    if(s==0){
        for(ll i:v) printf("%lld ",i);
        for(int i=1;i<=6-v.size();i++)  printf("0 ");puts("");
        return true;
    }
    ll l=(s+6-x)/(6-x+1),r=s;
    short a[20];mems(a,0);
    ll t=s;int c=0;
    while(t){a[++c]=t%10;t/=10;}
    if(x==6){
        for(int i=1;i<=c;i++)
            if(a[i]&&a[i]!=4&&a[i]!=7)  return false;
        v.eb(s);
        return dfs(x+1,0,v);
    }
    for(int i=c;i;i--){
        if(a[i]==7||a[i]==4||a[i]==0)   continue;
        if(a[i]>7) a[i]=7;
        else if(a[i]>4) a[i]=4;
        else a[i]=0;
        for(int j=i-1;j;j--)    a[j]=7;
        break;
    }
    // debug("c = %d\n",c);
    // for(int i=c;i;i--)  debug("%d",a[i]);debug("\n");
    while(true){
        ll nw=0;
        for(int i=c;i;i--)  nw=nw*10+a[i];
        // debug("nw = %d\n",nw);
        // if(nw>s)  exit(0);
        if(nw<l||!nw)    return false;
        v.eb(nw);
        if(dfs(x+1,s-nw,v))   return true;
        v.pop_back();
        bool flag=true;
        for(int i=1;i<c;i++){
            if(a[i]!=0){
                a[i]=a[i]==7?4:0;
                for(int j=1;j<i;j++)    a[j]=0;
                flag=false;
                break;
            }
        }
        if(flag){
            for(int i=1;i<=c-1;i++)   a[i]=7;
            c--;
        }
    }
    return false;
}
void matt(){
    zwx=0;
    cin>>n;
    if(!dfs(1,n,vector<ll>()))  puts("-1");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}

/*
747777777777777777 777777777777777 777770000000000 777740000000000 777777400000000
*/